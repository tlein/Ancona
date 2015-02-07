#ifndef Ancona_Game_Screens_GameScreen_H_
#define Ancona_Game_Screens_GameScreen_H_

#include <map>

#include <Ancona/Engine/Screens/AbstractScreen.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Game/Systems/GameSystems.hpp>

namespace ild
{

/**
 * @brief Screen used for core gameplay
 *
 * @author Tucker Lein
 */
class GameScreen : public AbstractScreen
{
    public:
        /**
         * @brief Default constructor for screen.
         *
         * @param manager ScreenManager instance for the game.
         */
        GameScreen(ScreenManager & manager);

        /**
         * @brief Updates the entity systems on the screen.
         *
         * @param delta seconds since last update.
         */
        void Update(float delta);

        /**
         * @brief Initialization logic for GameScreen, safe place
         *        to access resources brought in by the resource
         *        loader.
         */
        void Init();

        /**
         * @brief Draws the systems on the screen
         */
        void Draw();
    private:
        /**
         * @brief Container for all systems.
         */
        GameSystems * _systems;
        /**
         * @brief Holds references to entities that need to be access
         */
        std::map<std::string, Entity> _entities;
        /**
         * @brief Map containing all the collision types for the screen.
         */
        std::map<std::string, CollisionType> _collisionTypes;
};

}

#endif
