#pragma once

#include "collision_system.hpp"
#include "core/common.hpp"
#include "render_system.hpp"

#include <SDL.h>
#include <SDL_mixer.h>
/**
 * Container for all our entities and game logic.
 */
class WorldSystem
{
public:
	explicit WorldSystem(RenderSystem* renderer);
	~WorldSystem();
	bool step(float elapsed_ms);
	bool is_over()const;
	void set_renderer(RenderSystem* renderer);
	void handle_movements(float elapsed_ms_since_last_update);
	void handle_timers(float elapsed_ms_since_last_update);
	void initialize();
	Entity getPlayer();

private:
	// helper functions to set the world
	Entity createPlayer();
	void createEnemy(vec2 position, vec2 velocity);

	Mix_Music* background_music;

	GLFWwindow* window{};
	RenderSystem* renderer;
	CollisionSystem* collision_system;
	InputHandler inputHandler;
	Entity player_mage;
};
