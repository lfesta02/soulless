// // Header
// #include "core/world_system.hpp"
// // #include "core/world_init.hpp"
//
// // stlib
// #include <cassert>
// #include <sstream>
//
// //#include "physics_system.hpp"
//
// // create the underwater world
// WorldSystem::WorldSystem()
// 	: points(0)
// 	, next_eel_spawn(0.f)
// 	, next_fish_spawn(0.f) {
// 	// Seeding rng with random device
// 	rng = std::default_random_engine(std::random_device()());
// }
//
// WorldSystem::~WorldSystem() {
//
// 	// destroy music components
// 	// if (background_music != nullptr)
// 	// 	Mix_FreeMusic(background_music);
// 	// if (salmon_dead_sound != nullptr)
// 	// 	Mix_FreeChunk(salmon_dead_sound);
// 	// if (salmon_eat_sound != nullptr)
// 	// 	Mix_FreeChunk(salmon_eat_sound);
// 	//
// 	// Mix_CloseAudio();
//
// 	// Destroy all created components
// 	// registry.clear_all_components();
//
// 	// Close the window
// 	glfwDestroyWindow(window);
// }
//
// // Debugging
// namespace {
// 	void glfw_err_cb(int error, const char *desc) {
// 		fprintf(stderr, "%d: %s", error, desc);
// 	}
// }
//
// // World initialization
// // Note, this has a lot of OpenGL specific things, could be moved to the renderer
// GLFWwindow* WorldSystem::create_window() {
// 	///////////////////////////////////////
// 	// Initialize GLFW
// 	glfwSetErrorCallback(glfw_err_cb);
// 	if (!glfwInit()) {
// 		fprintf(stderr, "Failed to initialize GLFW");
// 		return nullptr;
// 	}
//
// 	//-------------------------------------------------------------------------
// 	// If you are on Linux or Windows, you can change these 2 numbers to 4 and 3 and
// 	// enable the glDebugMessageCallback to have OpenGL catch your mistakes for you.
// 	// GLFW / OGL Initialization
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// 	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
// #if __APPLE__
// 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif
// 	glfwWindowHint(GLFW_RESIZABLE, 0);
//
// 	// Create the main window (for rendering, keyboard, and mouse input)
// 	window = glfwCreateWindow(window_width_px, window_height_px, "Soulless", nullptr, nullptr);
// 	if (window == nullptr) {
// 		fprintf(stderr, "Failed to glfwCreateWindow");
// 		return nullptr;
// 	}
//
// 	// Setting callbacks to member functions (that's why the redirect is needed)
// 	// Input is handled using GLFW, for more info see
// 	// http://www.glfw.org/docs/latest/input_guide.html
// 	glfwSetWindowUserPointer(window, this);
// 	auto key_redirect = [](GLFWwindow* wnd, int _0, int _1, int _2, int _3) { ((WorldSystem*)glfwGetWindowUserPointer(wnd))->on_key(_0, _1, _2, _3); };
// 	auto cursor_pos_redirect = [](GLFWwindow* wnd, double _0, double _1) { ((WorldSystem*)glfwGetWindowUserPointer(wnd))->on_mouse_move({ _0, _1 }); };
// 	glfwSetKeyCallback(window, key_redirect);
// 	glfwSetCursorPosCallback(window, cursor_pos_redirect);
// 	return window;
// }
//
// void WorldSystem::init(RenderSystem* renderer_arg) {
// 	this->renderer = renderer_arg;
// 	// Playing background music indefinitely
// 	// Mix_PlayMusic(background_music, -1);
// 	// fprintf(stderr, "Loaded music\n");
//
// 	// Set all states to default
//     restart_game();
// }
//
// // Update our game world
// bool WorldSystem::step(float elapsed_ms_since_last_update) {
// 	// Updating window title with points
// 	std::stringstream title_ss;
// 	title_ss << "Points: " << points;
// 	glfwSetWindowTitle(window, title_ss.str().c_str());
// 	return true;
// }
//
// // Reset the world state to its initial state
// void WorldSystem::restart_game() {
// 	// Debugging for memory/component leaks
// 	// registry.list_all_components();
// 	// printf("Restarting\n");
//
// 	// Reset the game speed
// 	// current_speed = 1.f;
//
// 	// Remove all entities that we created
// 	// All that have a motion, we could also iterate over all fish, eels, ... but that would be more cumbersome
// 	// while (registry.motions.entities.size() > 0)
// 	//     registry.remove_all_components_of(registry.motions.entities.back());
// 	//
// 	// // Debugging for memory/component leaks
// 	// registry.list_all_components();
// 	//
// 	// // create a new Salmon
// 	// player_salmon = createSalmon(renderer, { window_width_px/2, window_height_px - 200 });
// 	// registry.colors.insert(player_salmon, {1, 0.8f, 0.8f});
//
// 	// !! TODO A2: Enable static eggs on the ground, for reference
// 	// Create eggs on the floor, use this for reference
// 	/*
// 	for (uint i = 0; i < 20; i++) {
// 		int w, h;
// 		glfwGetWindowSize(window, &w, &h);
// 		float radius = 30 * (uniform_dist(rng) + 0.3f); // range 0.3 .. 1.3
// 		Entity egg = createEgg({ uniform_dist(rng) * w, h - uniform_dist(rng) * 20 },
// 			         { radius, radius });
// 		float brightness = uniform_dist(rng) * 0.5 + 0.5;
// 		registry.colors.insert(egg, { brightness, brightness, brightness});
// 	}
// 	*/
// }
//
// // Compute collisions between entities
// void WorldSystem::handle_collisions() {
// 	// Loop over all collisions detected by the physics system
// 	// auto& collisionsRegistry = registry.collisions;
// 	// for (uint i = 0; i < collisionsRegistry.components.size(); i++) {
// 	// 	// The entity and its collider
// 	// 	Entity entity = collisionsRegistry.entities[i];
// 	// 	Entity entity_other = collisionsRegistry.components[i].other;
// 	//
// 	// 	// for now, we are only interested in collisions that involve the salmon
// 	// 	if (registry.players.has(entity)) {
// 	// 		//Player& player = registry.players.get(entity);
// 	//
// 	// 		// Checking Player - Deadly collisions
// 	// 		if (registry.deadlys.has(entity_other)) {
// 	// 			// initiate death unless already dying
// 	// 			if (!registry.deathTimers.has(entity)) {
// 	// 				// Scream, reset timer, and make the salmon sink
// 	// 				registry.deathTimers.emplace(entity);
// 	// 				Mix_PlayChannel(-1, salmon_dead_sound, 0);
// 	//
// 	// 				// !!! TODO A1: change the salmon's orientation and color on death
// 	// 			}
// 	// 		}
// 	// 		// Checking Player - Eatable collisions
// 	// 		else if (registry.eatables.has(entity_other)) {
// 	// 			if (!registry.deathTimers.has(entity)) {
// 	// 				// chew, count points, and set the LightUp timer
// 	// 				registry.remove_all_components_of(entity_other);
// 	// 				Mix_PlayChannel(-1, salmon_eat_sound, 0);
// 	// 				++points;
// 	//
// 	// 				// !!! TODO A1: create a new struct called LightUp in components.hpp and add an instance to the salmon entity by modifying the ECS registry
// 	// 			}
// 	// 		}
// 	// 	}
// 	// }
// 	//
// 	// // Remove all collisions from this simulation step
// 	// registry.collisions.clear();
// }
//
// // Should the game be over ?
// bool WorldSystem::is_over() const {
// 	return bool(glfwWindowShouldClose(window));
// }
//
// // On key callback
// void WorldSystem::on_key(int key, int, int action, int mod) {
// 	// // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 	// // TODO A1: HANDLE SALMON MOVEMENT HERE
// 	// // key is of 'type' GLFW_KEY_
// 	// // action can be GLFW_PRESS GLFW_RELEASE GLFW_REPEAT
// 	// // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  //
// 	// // Resetting game
// 	// if (action == GLFW_RELEASE && key == GLFW_KEY_R) {
// 	// 	int w, h;
// 	// 	glfwGetWindowSize(window, &w, &h);
//  //
//  //        restart_game();
// 	// }
//  //
// 	// // Debugging
// 	// if (key == GLFW_KEY_D) {
// 	// 	if (action == GLFW_RELEASE)
// 	// 		debugging.in_debug_mode = false;
// 	// 	else
// 	// 		debugging.in_debug_mode = true;
// 	// }
//  //
// 	// // Control the current speed with `<` `>`
// 	// if (action == GLFW_RELEASE && (mod & GLFW_MOD_SHIFT) && key == GLFW_KEY_COMMA) {
// 	// 	current_speed -= 0.1f;
// 	// 	printf("Current speed = %f\n", current_speed);
// 	// }
// 	// if (action == GLFW_RELEASE && (mod & GLFW_MOD_SHIFT) && key == GLFW_KEY_PERIOD) {
// 	// 	current_speed += 0.1f;
// 	// 	printf("Current speed = %f\n", current_speed);
// 	// }
// 	// current_speed = fmax(0.f, current_speed);
// }
//
// void WorldSystem::on_mouse_move(vec2 mouse_position) {
// 	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 	// TODO A1: HANDLE SALMON ROTATION HERE
// 	// xpos and ypos are relative to the top-left of the window, the salmon's
// 	// default facing direction is (1, 0)
// 	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
// 	(vec2)mouse_position; // dummy to avoid compiler warning
// }
