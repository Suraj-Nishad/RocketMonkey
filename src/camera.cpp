#include "camera.h"
#include "game_object.h"

Camera::Camera(const SDL_Rect& screen, const GameObject& target)
    : m_screen(screen), m_target(target)
{
}

void Camera::updatePosition()
{
    const SDL_Point target_pos = m_target.getPos();
    SDL_Point center;
    center.x = m_screen.x + m_screen.w / 2;
    center.y = m_screen.y + m_screen.h / 2;
    int x_dist = target_pos.x - center.x;
    int y_dist = target_pos.y - center.y;
    const int MAX_MOVEMENT = sqrt(x_dist * x_dist + y_dist * y_dist) / 100 + 1;
    if(abs(x_dist) > MAX_MOVEMENT) {
        m_screen.x += (x_dist > 0 ? 1 : -1) * MAX_MOVEMENT;
    } else if(abs(x_dist) < MAX_MOVEMENT) {
        m_screen.x += x_dist;
    }
    if(abs(y_dist) > MAX_MOVEMENT) {
        m_screen.y += (y_dist > 0 ? 1 : -1) * MAX_MOVEMENT;
    } else if(abs(y_dist) < MAX_MOVEMENT) {
        m_screen.y += y_dist;
    }
}
