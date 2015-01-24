#include "PlayerFactory.hpp"
#include "../Systems/FlappyInputComponent.hpp"
#include <Ancona/Engine/Core/Systems/Drawable/TextComponent.hpp>

#include <string>
#include <sstream>

using namespace ild;

Entity factories::CreatePlayer(
        FlappyGameSystems * gameSystems,
        std::map<std::string, CollisionType> collisionTypes,
        std::map<std::string, Entity> entities,
        FlappyInputHandler & inputHandler)
{
    Entity player = gameSystems->GetManager().CreateEntity();

    // position component
    factories::SetupPlayerPosition(
            player,
            gameSystems->GetPosition());

    // sprite component
    factories::SetupPlayerSprite(
            player,
            gameSystems->GetDrawable());

    // rotate component
    factories::SetupPlayerRotate(
            player,
            gameSystems);

    // input component
    factories::SetupPlayerInput(
            player,
            gameSystems,
            inputHandler);

    // gravity component
    factories::SetupPlayerGravity(
            player,
            gameSystems->GetSimpleGravity(),
            gameSystems->GetPosition());

    // collision component
    factories::SetupPlayerCollisions(
            player,
            gameSystems,
            collisionTypes,
            entities,
            inputHandler);

    return player;
}

void factories::SetupPlayerPosition(
        Entity player,
        PositionSystem & positionSystem)
{
    PositionComponent * position = positionSystem.CreateComponent(player);
    position->Position.x = 100;
    position->Position.y = 220;
}

void factories::SetupPlayerSprite(
        Entity player,
        DrawableSystem & drawableSystem)
{
    SpriteComponent * sprite = drawableSystem.CreateSpriteComponent(
            player,
            "flappy",
            RenderPriority::Player);
    sprite->SetRotation(-30.0f);
}

void factories::SetupPlayerRotate(
        Entity player,
        FlappyGameSystems * gameSystems)
{
    gameSystems->GetFlappyRotate().CreateComponent(
            player,
            *gameSystems->GetDrawable().at(player),
            *gameSystems->GetPosition().at(player));
}

void factories::SetupPlayerInput(
        Entity player,
        FlappyGameSystems * gameSystems,
        FlappyInputHandler & inputHandler)
{
    FlappyInputComponent * inputComponent = 
        new FlappyInputComponent(
                player,
                *gameSystems->GetPosition().at(player),
                *gameSystems->GetFlappyRotate().at(player),
                inputHandler);
    gameSystems->GetInput().AddComponent(player, inputComponent);
}

void factories::SetupPlayerGravity(
        Entity player,
        SimpleGravitySystem & gravitySystem,
        PositionSystem & positionSystem)
{
    gravitySystem.CreateComponent(player, *positionSystem.at(player));
}

void factories::SetupPlayerCollisions(
        Entity player,
        FlappyGameSystems * gameSystems,
        std::map<std::string, CollisionType> collisionTypes,
        std::map<std::string, Entity> entities,
        FlappyInputHandler & inputHandler)
{
    gameSystems->GetCollision().CreateComponent(
            player,
            sf::Vector3f(14.0f, 14.0f, 0),
            collisionTypes["player"]);

    /* Collision Handlers */
    // ground collision
    gameSystems->GetCollision().SetHandler(
            collisionTypes["player"],
            collisionTypes["ground"],
            factories::PlayerToGroundCollisionHandler(
                gameSystems, 
                entities, 
                inputHandler));

    // pipe collision
    gameSystems->GetCollision().SetHandler(
            collisionTypes["player"],
            collisionTypes["pipe"],
            factories::PlayerToPipeCollisionHandler(
                gameSystems,
                entities,
                inputHandler));

    // point collision
    gameSystems->GetCollision().SetHandler(
            collisionTypes["player"],
            collisionTypes["point"],
            factories::PlayerToPointCollisionHandler(
                gameSystems,
                entities));
}

std::function< void(Entity player, Entity ground) > factories::PlayerToGroundCollisionHandler(
        FlappyGameSystems * gameSystems,
        std::map<std::string, Entity> entities,
        FlappyInputHandler & inputHandler)
{
    Entity pipeSpawner = entities["pipeSpawner"];
    return [gameSystems, pipeSpawner, &inputHandler](Entity player, Entity ground)
    {
        StopAllMovement(
                gameSystems, 
                player,
                ground,
                pipeSpawner,
                inputHandler);
        gameSystems->GetPosition().at(player)->Velocity.y = 0;
    };
}

std::function< void(Entity player, Entity ground) > factories::PlayerToPipeCollisionHandler(
        FlappyGameSystems * gameSystems,
        std::map<std::string, Entity> entities,
        FlappyInputHandler & inputHandler)
{
    Entity ground = entities["ground"];
    Entity pipeSpawner = entities["pipeSpawner"];
    return [gameSystems, ground, pipeSpawner, &inputHandler](Entity player, Entity pipe)
    {
        StopAllMovement(
                gameSystems, 
                player,
                ground,
                pipeSpawner,
                inputHandler);
    };
}

std::function< void(Entity player, Entity ground) > factories::PlayerToPointCollisionHandler(
        FlappyGameSystems * gameSystems,
        std::map<std::string, Entity> entities)
{
    Entity pointCounterPlain = entities["pointCounterPlain"];
    Entity pointCounterBorder = entities["pointCounterBorder"];
    Entity pipeSpawner = entities["pipeSpawner"];
    return [gameSystems, pointCounterPlain, pointCounterBorder, pipeSpawner](Entity player, Entity point)
    {
        // TODO: Android won't compile this correctly even  with C++11 flags 
        //int points = std::stoi(gameSystems->GetDrawable().at(pointCounterPlain)->GetText());
        std::string pointStr = static_cast<TextComponent *>(gameSystems->GetDrawable().at(pointCounterPlain))->GetText();
        std::istringstream is(pointStr);
        int points;
        is >> points;
        points++;
        std::ostringstream os;
        os << points; 
        static_cast<TextComponent *>(gameSystems->GetDrawable().at(pointCounterPlain))->SetText(os.str());
        static_cast<TextComponent *>(gameSystems->GetDrawable().at(pointCounterBorder))->SetText(os.str());
        gameSystems->GetPipeSpawner().at(pipeSpawner)->DespawnPoint(point);
    };
}

void factories::StopAllMovement(
        FlappyGameSystems * gameSystems,
        Entity player,
        Entity ground,
        Entity pipeSpawner,
        FlappyInputHandler & inputHandler)
{
    gameSystems->GetPipeSpawner().at(pipeSpawner)->StopMovingPipes();
    gameSystems->GetPosition().at(ground)->Velocity.x = 0;
    if(gameSystems->GetPosition().at(player)->Velocity.y < 0)
    {
        gameSystems->GetPosition().at(player)->Velocity.y = 0;
    }
    inputHandler.ChangeState(FlappyStates::OnGround);
}

