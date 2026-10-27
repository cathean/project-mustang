#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "raylib.h"
#include "spdlog/spdlog.h"

namespace Engine {
class ResourceManager {
 public:
  static ResourceManager& get() {
    static ResourceManager instance;
    return instance;
  }

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  Texture& tryget_texture(const std::string& path) {
    auto it = textures_.find(path);

    if (it != textures_.end()) {
      return *it->second.get();
    } else {
      return load_texture(path);
    }
  }

  Shader& tryget_shader(const std::string& path) {
    auto it = shaders_.find(path);

    if (it != shaders_.end()) {
      return *it->second.get();
    } else {
      return load_shader(path);
    }
  }

 private:
  ResourceManager() { spdlog::info("[ResourceManager] Initializing"); };
  ~ResourceManager() {
    spdlog::info("[ResourceManager] Start destructing");
    cleanup_textures();
    cleanup_shaders();
  };

  std::unordered_map<std::string, std::unique_ptr<Texture2D>> textures_;
  std::unordered_map<std::string, std::unique_ptr<Shader>> shaders_;

  Texture& load_texture(const std::string& path) {
    auto tex = std::make_unique<Texture2D>(LoadTexture(path.c_str()));
    auto [it, inserted] = textures_.try_emplace(path, std::move(tex));

    if (!inserted) {
      throw std::runtime_error("Texture file is not exist!");
    }

    return *it->second.get();
  }

  Shader& load_shader(const std::string& path) {
    auto shader = std::make_unique<Shader>(LoadShader(nullptr, path.c_str()));
    auto [it, inserted] = shaders_.try_emplace(path, std::move(shader));

    if (!inserted) {
      throw std::runtime_error("Shader file is not exist!");
    }

    return *it->second.get();
  }

  void cleanup_textures() {
    spdlog::info("[ResourceManager] Cleaning up textures");
    for (const auto& [id, tex] : textures_) {
      if (tex) {
        UnloadTexture(*tex);
      }
    }
  }

  void cleanup_shaders() {
    spdlog::info("[ResourceManager] Cleaning up shaders");
    for (const auto& [id, shader] : shaders_) {
      if (shader) {
        UnloadShader(*shader);
      }
    }
  }
};
}  // namespace Engine