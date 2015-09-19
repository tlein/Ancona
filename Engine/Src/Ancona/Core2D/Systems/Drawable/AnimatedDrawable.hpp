#ifndef Ancona_Engine_Core_Systems_AnimatedDrawable_H_
#define Ancona_Engine_Core_Systems_AnimatedDrawable_H_

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>

namespace ild
{

/**
 * @brief Responsible for drawing an animation that is made up of multiple frames, each frame
 *        is its own drawable.
 *
 * @author Tucker Lein
 */
class AnimatedDrawable : public Drawable
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        AnimatedDrawable() {}

        /**
         * @brief Constructs an AnimatedDrawable
         *
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param duration Seconds per frame.
         * @param priorityOffset Optional offset to the render priority.
         * @param positionOffset Vector that defines the offset from its parent drawable.
         */
        AnimatedDrawable(
                const int priority,
                float duration,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));


        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /* getters and setters */
        sf::Vector2f size();
        int alpha();
        void alpha(int alpha);

    private:
        /**
         * Contains the drawables that will be displayed, the order in this list is the order they are displayed in.
         */
        std::vector<std::unique_ptr<Drawable>> _frames;
        /**
         * @brief Seconds per frame.
         */
        float _duration;
        /**
         * @brief time until the frame changes.
         */
        float _timeUntilChange;
        /**
         * @brief The current frame being shown.
         */
        int _curFrame = 0;

        /**
         * @brief Ticks the animation, will switch the frame when it is time to do so.
         */
        void Tick(float delta);
        void AdvanceFrame();
        void OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta) override;
};

}

#endif
