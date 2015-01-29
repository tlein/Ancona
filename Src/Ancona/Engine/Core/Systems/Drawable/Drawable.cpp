#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>

using namespace ild;

Drawable::Drawable(
        const PositionComponent & positionComponent,
        const RenderPriorityEnum priority,
        int priorityOffset,
        sf::Vector2f positionOffset,
        const std::string key) :
    _positionComponent(positionComponent),
    _renderPriority(priority),
    _priorityOffset(priorityOffset),
    _positionOffset(positionOffset),
    _key(key)
{
}
