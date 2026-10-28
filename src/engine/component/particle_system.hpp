#include "engine/core/component.hpp"
#include "raylib.h"
namespace Component {
enum EmissionShape { CIRCLE, CONE } typedef EmissionShape;

struct ParticleEmission {
  float rate_over_time = 0;
};

struct ParticleShape {
  float radius = 5.0f;
  Vector2 offset{};
};

class ParticleSystem : public Engine::Core::Component {
 public:
  ParticleSystem() {}
  ~ParticleSystem() = default;

  float duration = 5.0f;
  bool looping = true;
  float lifetime = 5.0f;
  float speed = 5.0f;
  float size = 1.0f;
  float rotation = 0.0f;
  Color color = WHITE;
  int max_particles = 1000;
  ParticleEmission emission{};
  ParticleShape shape{};

  void set_texture(std::string path) {}
  Texture2D* get_texture() { return texture_; }
  const int get_particle_count() { return particles_count_; }
  void play(bool is_loop) {}
  void pause() {}
  void stop() {}

 protected:
  void start() override {}

  void update(float dt) override {}

  void draw() override {}

 private:
  Texture2D* texture_ = nullptr;
  int particles_count_ = 0;
};
}  // namespace Component