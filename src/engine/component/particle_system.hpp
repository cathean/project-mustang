#include <vector>

#include "engine/core/component.hpp"
#include "raylib.h"

namespace Component {
enum EmissionShape { CIRCLE, CONE } typedef EmissionShape;

struct ParticleEmission {
  float rate_over_time = 10;
};

struct ParticleShape {
  float radius = 20.0f;
  Vector2 offset{};
};

struct Particle {
  bool alive = false;
  Transform2D transform;
  Color color = WHITE;
  float lifetime = 0;
};

class ParticleSystem : public Engine::Core::Component {
 public:
  ParticleSystem() {}
  ~ParticleSystem() = default;

  bool debug_mode = false;
  float duration = 5.0f;
  bool looping = true;
  float lifetime = 5.0f;
  float speed = 5.0f;
  float size = 10.0f;
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

  void update(float dt) override {
    elapsed_rate_time += dt;
    elapsed_duration_time += dt;

    if (elapsed_duration_time >= duration) {
      elapsed_duration_time = 0.0f;

      if (!looping) return;
    }

    if (elapsed_rate_time >= 1.0f) {
      is_emitting = true;
      elapsed_rate_time = 0.0f;
    }
  }

  void draw() override {
    if (is_emitting) {
      for (int i = 0; i < emission.rate_over_time; i++) {
        DrawCircle(int centerX, int centerY, float radius, Color color)
      }
    }

    if (debug_mode) {
      // Draw the particle shape spawner
      DrawCircleLines(gameobject->transform.position.x,
                      gameobject->transform.position.y, shape.radius, RED);
    }
  }

 private:
  Texture2D* texture_ = nullptr;
  std::vector<Particle> particles_{};
  int particles_count_ = 0;

  bool is_emitting = false;
  float elapsed_rate_time = 0.0f;
  float elapsed_duration_time = 0.0f;
};
}  // namespace Component