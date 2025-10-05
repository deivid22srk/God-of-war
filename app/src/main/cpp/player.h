#ifndef PLAYER_H
#define PLAYER_H

enum class PlayerState {
    IDLE,
    WALKING,
    RUNNING,
    ATTACKING,
    BLOCKING
};

class Player {
public:
    Player();
    
    void update(float deltaTime);
    void setPosition(float x, float y, float z);
    void getPosition(float* pos) const;
    void move(float x, float z);
    void attack();
    void block(bool blocking);
    
    PlayerState getState() const { return state; }
    float getHealth() const { return health; }
    
private:
    float position[3];
    float velocity[3];
    float rotation;
    
    PlayerState state;
    float health;
    float stamina;
    
    float walkSpeed;
    float runSpeed;
    float attackCooldown;
};

#endif
