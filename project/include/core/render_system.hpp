#pragma once

#include <array>
#include <utility>
#include <vector>
#include <algorithm>
#include "common.hpp"
#include "input/input_handler.hpp"
#include "graphics/asset_manager.hpp"

#include <map>
#include "../ext/project_path.hpp"		// built by CMake, contains project path

/**
 * System responsible for setting up OpenGL and for rendering all the visual entities in the game
 */
class RenderSystem {

public:
	bool initialize(InputHandler& input_handler, int width = 480, int height = 500, const char* title = "OpenGL Example");
	void setUpView() const;
	// void setUpFont();
	GLFWwindow* getGLWindow() const;
	void drawFrame();
	void drawText(const std::string& text, const std::string& fontName, float x, float y, float scale, const glm::vec3& color);
	float getTextWidth(const std::string& text, const std::string& fontName, float scale);
	void setAssetManager(AssetManager* asset_manager) { this->asset_manager = *asset_manager; }
	// void removeRenderRequest(Entity entity);
	InputHandler input_handler;

	void updateRenderOrder(ComponentContainer<RenderRequest>& render_requests) {
		// Clear and repopulate the sorted_indices
		sorted_indices.clear();
		for (size_t i = 0; i < render_requests.components.size(); ++i) {
			sorted_indices.emplace_back(i, render_requests.components[i].smooth_position.render_y);
		}

		// Sort the indices based on render_y
		std::sort(sorted_indices.begin(), sorted_indices.end(),
			[](const RenderIndex& a, const RenderIndex& b) {
				return a.render_y < b.render_y;
			});
	}

	mat4 getProjectionMatrix() {
		return projectionMatrix;
	}

	mat4 getViewMatrix() {
		return viewMatrix;
	}

private:
	struct RenderIndex {
		size_t index;
		float render_y;

		RenderIndex(size_t i, float y) : index(i), render_y(y) {}
	};

	void updateCameraPosition(float x, float y);

	std::vector<RenderIndex> sorted_indices;
	// GLuint frame_buffer = 0;
	Entity screen_state_entity;
	GLFWwindow* window = nullptr;
	AssetManager asset_manager; // Holds all the assets
	std::vector<RenderRequest> render_requests; // Holds all the render requests
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	Entity camera;
};
