#include "core/world_system.hpp"

#include "entities/ecs_registry.hpp"

WorldSystem::WorldSystem(RenderSystem* renderer)
{
	this->renderer = renderer;
	this->collision_system = new CollisionSystem(renderer);
}

WorldSystem::~WorldSystem() {}

// Should the game be over ?
bool WorldSystem::is_over() const {
	return bool(glfwWindowShouldClose(window));
}

// Update our game world
bool WorldSystem::step(float elapsed_ms_since_last_update) {

	this->handle_movements(elapsed_ms_since_last_update);
	this->collision_system->handle_collisions();
	return true;
}

void WorldSystem::set_renderer(RenderSystem* renderer)
{
	this->renderer = renderer;
}

/**
 * @brief In charge of updating the position of all entities with a motion component
 * @param elapsed_ms_since_last_update
 */
void WorldSystem::handle_movements(float elapsed_ms_since_last_update)
{
	ComponentContainer<Motion> &motions_registry = registry.motions;
	// Update all motions
	for (Entity entity : motions_registry.entities) {
		Motion& motion = motions_registry.get(entity);
		motion.position += motion.velocity * elapsed_ms_since_last_update;
	}
}


/**
 * Initialize the game world
 * TODO: Add your game initialization code here!
 */
void WorldSystem::initialize()
{
	// Create a player
	this->createPlayer();

	// Create an enemy
	constexpr int num_enemies = 10;
	std::random_device rd;  // Random device
	std::mt19937 gen(rd()); // Mersenne Twister generator
	std::uniform_real_distribution<float> dis(-1.0f, 1.0f); // Distribution range [-1, 1]

	for (int i = 0; i < num_enemies; i++)
	{
		float x = dis(gen);
		float y = dis(gen);
		// float vx = dis(gen);
		// float vy = dis(gen);
		this->createEnemy({ x, y }, { 0.3f, 0.1f });
	}
}


// On key callback
void WorldSystem::on_key(int key, int, int action, int mod) {
}

void WorldSystem::on_mouse_move(vec2 mouse_position) {
}


void WorldSystem::createPlayer() {
	const Entity player;
	registry.players.emplace(player);
	Motion& motion = registry.motions.emplace(player);
	motion.position = { 0.0f, 0.0f };  // Center of the screen
	motion.velocity = { 0.0f, 0.0f };
	motion.scale = { 0.1f, 0.1f };

	Health& health = registry.healths.emplace(player);
	health.health = 100;
	health.maxHealth = 100;
	// TODO: Add resistances here!


	// Player& player_component = registry.players.emplace(player);
	// // TODO: Add player initialization code here!


	// Player itself has no damage on other entities
	Deadly& deadly = registry.deadlies.emplace(player);
	deadly.to_projectile = false;
	deadly.to_enemy = false;
	deadly.to_player = false;

	this->renderer->addRenderRequest(player, "basic");
}


void WorldSystem::createEnemy(vec2 position, vec2 velocity)
{
	const Entity enemy;
	registry.enemies.emplace(enemy);
	Motion& motion = registry.motions.emplace(enemy);
	motion.position = position;
	motion.velocity = velocity;
	motion.scale = { 0.1f, 0.1f };

	Health& health = registry.healths.emplace(enemy);
	health.health = 100;
	health.maxHealth = 100;

	Deadly& deadly = registry.deadlies.emplace(enemy);
	deadly.to_projectile = true;
	deadly.to_enemy = false;
	deadly.to_player = true;

	Damage& damage = registry.damages.emplace(enemy);
	damage.value = 10.f;
	damage.type = DamageType::enemy;

	this->renderer->addRenderRequest(enemy, "basic");
}