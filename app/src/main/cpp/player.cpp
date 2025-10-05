#include "player.h"
#include <cmath>

Player::Player()
    : rotation(0.0f)
    , state(PlayerState::IDLE)
    , health(100.0f)
    , stamina(100.0f)
    , walkSpeed(2.0f)
    , runSpeed(5.0f)
    , attackCooldown(0.0f) {
    
    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 0.0f;
    
    velocity[0] = 0.0f;
    velocity[1] = 0.0f;
    velocity[2] = 0.0f;
}

void Player::update(float deltaTime) {
    if (attackCooldown > 0.0f) {
        attackCooldown -= deltaTime;
        if (attackCooldown <= 0.0f) {
            state = PlayerState::IDLE;
        }
    }
    
    position[0] += velocity[0] * deltaTime;
    position[1] += velocity[1] * deltaTime;
    position[2] += velocity[2] * deltaTime;
    
    velocity[0] *= 0.9f;
    velocity[2] *= 0.9f;
    
    if (stamina < 100.0f) {
        stamina += deltaTime * 10.0f;
        if (stamina > 100.0f) stamina = 100.0f;
    }
}

void Player::setPosition(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

void Player::getPosition(float* pos) const {
    pos[0] = position[0];
    pos[1] = position[1];
    pos[2] = position[2];
}

void Player::move(float x, float z) {
    if (state == PlayerState::ATTACKING || state == PlayerState::BLOCKING) {
        return;
    }
    
    velocity[0] = x * walkSpeed;
    velocity[2] = z * walkSpeed;
    
    float speed = sqrt(velocity[0] * velocity[0] + velocity[2] * velocity[2]);
    if (speed > 0.1f) {
        state = PlayerState::WALKING;
        rotation = atan2(velocity[0], velocity[2]);
    } else {
        state = PlayerState::IDLE;
    }
}

void Player::attack() {
    if (attackCooldown <= 0.0f && stamina >= 20.0f) {
        state = PlayerState::ATTACKING;
        attackCooldown = 0.5f;
        stamina -= 20.0f;
    }
}

void Player::block(bool blocking) {
    if (blocking && stamina > 0.0f) {
        state = PlayerState::BLOCKING;
    } else if (state == PlayerState::BLOCKING) {
        state = PlayerState::IDLE;
    }
}
