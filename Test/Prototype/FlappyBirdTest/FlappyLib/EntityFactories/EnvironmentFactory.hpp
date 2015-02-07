#ifndef Test_Prototype_FlappyBirdTest_EntityFactories_EnvironmentFactory_H_
#define Test_Prototype_FlappyBirdTest_EntityFactories_EnvironmentFactory_H_

#include <map>
#include <memory>
#include <string>

#include "../Systems/FlappyGameSystems.hpp"

namespace ild
{

namespace factories
{
    /**
     * @brief Creates the ground with all the default components setup.
     *
     * @param manager SystemManager for screen.
     * @param positionSystem PositionSystem for screen.
     * @param drawableSystem DrawableSystem for screen.
     * @param collisionSystem CollisionSystem for screen.
     * @param collisionTypes CollisionTypes for the screen.
     *
     * @return Entity that is the ground.
     */
    Entity CreateGround(
            SystemManager & manager,
            PositionSystem & positionSystem,
            DrawableSystem & drawableSystem,
            CollisionSystem & collisionSystem,
            std::map<std::string, CollisionType> collisionTypes);

    /**
     * @brief Creates the pipe spawner with all the default components setup.
     *
     * @param manager SystemManager for screen.
     * @param pipeSpawnerSystem pipeSpawnerSystem for screen.
     * @param positionSystem PositionSystem for screen.
     * @param drawableSystem DrawableSystem for screen.
     * @param collisionSystem CollisionSystem for screen.
     * @param collisionTypes CollisionTypes for the screen.
     *
     * @return Entity that is the ground.
     */
    Entity CreatePipeSpawner(
            SystemManager & manager,
            PipeSpawnerSystem & pipeSpawnerSystem,
            PositionSystem & positionSystem,
            DrawableSystem & drawableSystem,
            CollisionSystem & collisionSystem,
            std::map<std::string, CollisionType> collisionTypes);

    /**
     * @brief Creates the background with all the default components setup.
     *
     * @param manager SystemManager for screen.
     * @param positionSystem PositionSystem for screen.
     * @param drawableSystem DrawableSystem for screen.
     *
     * @return Entity that is the background.
     */
    Entity CreateBackground(
            SystemManager & manager,
            PositionSystem & positionSystem,
            DrawableSystem & drawableSystem);

    /**
     * @brief Creates the point counter with all the default components setup.
     *
     * @param manager SystemManager for screen.
     * @param positionSystem PositionSystem for screen.
     * @param drawableSystem DrawableSystem for screen.
     *
     * @return Entity that is the point counter.
     */
     Entity CreatePointCounter(
            SystemManager & manager,
            PositionSystem & positionSystem,
            DrawableSystem & drawableSystem);

    /**
     * @brief Creates the get ready entity with all the default components setup.
     *
     * @param manager SystemManager for screen.
     * @param positionSystem PositionSystem for screen.
     * @param drawableSystem DrawableSystem for screen.
     *
     * @return Entity for the get ready screen graphics.
     */
    Entity CreateGetReady(
            SystemManager & manager,
            PositionSystem & positionSystem,
            DrawableSystem & drawableSystem);

    /**
     * @brief Sets up the default ground position component.
     *
     * @param ground Entity that is the ground.
     * @param ground Entity that is the ground warp.
     * @param positionSystem PositionSystem for the screen.
     */
    void SetupGroundPosition(
            Entity ground,
            Entity groundWarp,
            PositionSystem & positionSystem);

    /**
     * @brief Sets up the default background position component.
     *
     * @param foreground Entity that is the background.
     * @param position PositionSystem for the screen.
     */
    void SetupBackgroundPosition(
            Entity background,
            PositionSystem & position);

    /**
     * @brief Sets up the default position for the get ready entity.
     *
     * @param getReady Entity that is the get ready overlay.
     * @param position PositionSystem for the screen.
     */
    void SetupGetReadyPosition(
            Entity getReady,
            PositionSystem & position);

    /**
     * @brief Sets up the default point counter position component.
     *
     * @param pointCounter Entity that is the point counter.
     * @param position PositionSystem for the screen.
     */
    void SetupPointCounterPosition(
            Entity pointCounter,
            PositionSystem & position);

    /**
     * @brief Sets up the default ground sprite component.
     *
     * @param ground Entity that is the ground.
     * @param drawableSystem DrawableSystem for the screen.
     */
    void SetupGroundSprite(
            Entity ground,
            DrawableSystem & drawableSystem); 

    /**
     * @brief Sets up the default background sprite component.
     *
     * @param background Entity that is the background.
     * @param drawableSystem DrawableSystem for the screen.
     */
    void SetupBackgroundSprite(
            Entity background,
            DrawableSystem & drawableSystem);

    /**
     * @brief Sets up the default sprite for the get ready screen.
     *
     * @param getReady Entity for the get ready screen.
     * @param drawableSystem DrawableSystem for the screen.
     */
    void SetupGetReadySprite(
            Entity getReady,
            DrawableSystem & drawableSystem);

    /**
     * @brief Sets up the default point counter text component.
     *
     * @param pointCounter Entity that is the point counter.
     * @param drawableSystem DrawableSystem for the screen.
     */
    void SetupPointCounterText(
            Entity pointCounter,
            DrawableSystem & drawableSystem);

    /**
     * @brief Sets up the collision component and handlers for the ground.
     *
     * @param ground Entity that is the ground.
     * @param ground Entity that is the ground warp.
     * @param collisionTypes CollisionTypes for the screen.
     * @param collisionSystem CollisionSystem for the screen.
     * @param positionSystem PositionSystem for the screen.
     */
    void SetupGroundCollisions(
            Entity ground,
            Entity groundWarp,
            std::map<std::string, CollisionType> collisionTypes,
            CollisionSystem & collisionSystem,
            PositionSystem & positionSystem);

    /**
     * @brief Handler function for when the ground collides with the ground warp.
     *
     * @param positionSystem PositionSystem for the screen.
     *
     * @return function to handle collision.
     */
    std::function< void(Entity ground, Entity groundWarp) > GroundToGroundWarpCollisionHandler(PositionSystem & positionSystem);

            

}

}

#endif
