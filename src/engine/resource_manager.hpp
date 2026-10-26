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
  };

 private:
  ResourceManager() { spdlog::info("[ResourceManager] initializing"); };
  ~ResourceManager() { spdlog::info("[ResourceManager] cleaning up"); };

  std::unordered_map<std::string, std::unique_ptr<Texture2D>> textures_;

  Texture& load_texture(const std::string& path) {
    auto tex = std::make_unique<Texture2D>(LoadTexture(path.c_str()));
    auto [it, inserted] = textures_.try_emplace(path, std::move(tex));

    if (!inserted) {
      throw std::runtime_error("Texture path is not exist!");
    }

    return *it->second.get();
  }
};
}  // namespace Engine