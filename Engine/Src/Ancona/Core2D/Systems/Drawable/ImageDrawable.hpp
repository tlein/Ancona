#ifndef Ancona_Engine_Core_Systems_ImageDrawable_H_
#define Ancona_Engine_Core_Systems_ImageDrawable_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>

namespace ild
{

/**
 * @brief A drawable which can display either a whole image or a portion of an image.
 *
 * @author Tucker Lein
 */
class ImageDrawable : public Drawable
{
    public:
        /**
         * @brief Blank constructor needed for serializing.
         */
        ImageDrawable() { }

        /**
         * @brief Constructs a TileImageDrawable
         *
         * @param textureKey Key for the texture
         * @param textureRect IntRect that describes the rectangle of the texture to display.
         */
        ImageDrawable(
                const int priority,
                int priorityOffset,
                sf::Vector2f positionOffset,
                std::string textureKey,
                sf::IntRect textureRect);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc) override;

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity) override;

        /* getters and setters */
        sf::Vector2f size() override;
        void alpha(int newAlpha) override;
        int alpha() override;
    private:
        std::string _textureKey;
        sf::IntRect _textureRect;
        bool _isWholeImage;
        std::unique_ptr<sf::Sprite> _sprite;

        void SetupSprite();
        void OnDraw(sf::RenderWindow &window, sf::Transform transform, float delta) override;
};

}

#endif
