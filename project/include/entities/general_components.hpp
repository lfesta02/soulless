#pragma once

#include <core/common.hpp>
#include <utils/constants.hpp> 
#include <utils/spell_queue.hpp>
#include <graphics/asset_manager.hpp>

// Motion Component
struct Motion {
    vec2 position = { 0, 0 };
    vec2 velocity = { 0, 0 };
    vec2 scale = { 1, 1 };
    vec2 collider = { 100, 100 };
    float mass = 0;
    float speedModifier = 1.f;
    float angle = 0;
};

// Resistance Modifier
struct ResistanceModifier {};


// Health Component
struct Health
{
    float health = 0;
    float maxHealth = 0;
    ResistanceModifier resistance_modifier;
};

// Damage Component
struct Damage
{
    float value = 0;
    DamageType type = DamageType::enemy;
};

// Type Components
struct Enemy {
    bool is_ranged = false;
    float range = 0;
};
struct Player {
    DamageType right_hand;
    DamageType left_hand;
    float cooldown = -1.f;
    unsigned int health_gauge = 0;
    SpellQueue spell_queue;
};

struct Projectile {
    DamageType type;
    float range = 0;
    vec2 init_pos = { 0, 0 }; // Needed to compare with its (current) position to calculate range travelled
};

// Timed Component
struct Timed { }; // include temporary effects and counters

// Structure to store collision information
struct Collision
{
    // Note, the first object is stored in the ECS container.entities
    Entity other{}; // the second object involved in the collision
    explicit Collision(Entity& other) { this->other = other; };
};

// Structure to store information on being hit
struct OnHit
{
    float invincibility_timer = 0;
};

// Structure to store entities marked to die
struct Death
{
    float timer = 10;
};

// Structure to store what entites affect/damage other entities
struct Deadly
{
    bool to_player = false;
    bool to_enemy = false;
    bool to_projectile = false;
};

struct RenderRequest
{
    AssetId mesh = "";
    AssetId texture = "";
    AssetId shader = "";
};