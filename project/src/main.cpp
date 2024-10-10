#define GL3W_IMPLEMENTATION

#include "core/render_system.hpp"
#include "core/world_system.hpp"
#include "utils/game_assets.hpp"

#define ERROR_SUCCESS 0 // For Mac OS

int main(int argc, char* argv[])
{
	AssetManager asset_manager;
	RenderSystem renderer;
	InputHandler input_handler;
	WorldSystem world = WorldSystem(&renderer);

	renderer.initialize(input_handler, window_width_px, window_height_px, "Soulless"); // must be called at the beginning of the program
	GLFWwindow* window = renderer.getGLWindow();

	GameAssets gameAssets = initializeGameAssets(asset_manager); // Initialize the asset manager
	renderer.setAssetManager(&asset_manager);
	world.set_renderer(&renderer);
	world.initialize(); // Initialize the game world

	auto t = std::chrono::high_resolution_clock::now();
	while (!glfwWindowShouldClose(window)) { // Game loop
		// IMPORTANT: The following lines order are CRUCIAL to the rendering process
		renderer.setUpView(); // (1) clear the screen

		auto now = std::chrono::high_resolution_clock::now();
		const float elapsed_ms = static_cast<float>((std::chrono::duration_cast<std::chrono::microseconds>(now - t)).count()) / 1000.0f;
		t = now;

		world.step(elapsed_ms); // (2) Update the game state
		renderer.drawFrame(); // (3) Re-render the scene (where the magic happens)
		glfwSwapBuffers(window); // (4) swap front and back buffers
		glfwPollEvents(); // (5) poll for and process events
	}

	// TODO: Add cleanup code here
	return ERROR_SUCCESS;
}
