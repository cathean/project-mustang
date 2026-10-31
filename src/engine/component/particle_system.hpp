#include <boost/circular_buffer.hpp>
#include <boost/circular_buffer/base.hpp>
#include <cmath>

#include "engine/core/component.hpp"
#include "engine/utils.hpp"
#include "raylib.h"
#include "raymath.h"

namespace Component {
enum EmissionShape { CIRCLE, CONE } typedef EmissionShape;

struct BurstEmitter {
  int count = 0;
  float time = 0.0f;
};

struct ParticleEmitter {
  int rate_over_time = 10;
  BurstEmitter burst;
};

enum SpawnType { CENTER, RANDOM, BURST_SPREAD };

struct ParticleShape {
  float radius = 50.0f;
  Transform2D transform{};
  int radial_direction = 1;
  SpawnType spawn_type = CENTER;

  std::tuple<Vector2, Vector2> gen_spawn_particle_data(int particle_index,
                                                       int max_particles) {
    Vector2 pos{};
    Vector2 dir{};
    Vector2 random_circle_unit_pos =
        Engine::Utility::Random::inside_unit_circle();

    switch (spawn_type) {
      case CENTER: {
        pos = transform.position;
        dir = get_direction(random_circle_unit_pos);
        return {pos, dir};
        break;
      }
      case RANDOM: {
        float random_radius = Engine::Utility::Random::range(0.0f, radius);
        pos = random_circle_unit_pos * random_radius;
        dir = get_direction(random_circle_unit_pos);
        return {pos, dir};
        break;
      }
      case BURST_SPREAD: {
        pos = transform.position;
        dir = get_direction_spread(particle_index, max_particles);
        return {pos, dir};
        break;
      }
    }

    return {Vector2Zero(), Vector2{0, 1}};
  }

  Vector2 get_direction(Vector2 particle_pos) {
    Vector2 normal =
        Vector2Normalize(Vector2Subtract(particle_pos, transform.position));
    Vector2 dir = Vector2Lerp(Vector2{0, 1}, normal, radial_direction);
    return dir;
  }

  Vector2 get_direction_spread(int idx, int max) {
    float rad = DEG2RAD * (360.0f / max) * idx;
    Vector2 dir = {cos(rad), sin(rad)};
    return dir;
  }
};

struct Particle {
  Transform2D transform{};
  float radius;
  Vector2 velocity{};
  Color color = WHITE;

  bool alive = false;
  float lifetime = 0;
};

class ParticleSystem : public Engine::Core::Component {
 public:
  ParticleSystem() = default;
  ~ParticleSystem() = default;

  bool debug_mode = false;
  bool running = true;
  float duration = 5.0f;
  bool looping = true;
  float lifetime = 2.0f;
  Vector2 start_speed = {50.0f, 50.0f};
  float start_size = 10.0f;
  float start_rotation = 0.0f;
  Color color = WHITE;
  int max_particles = 1000;
  ParticleEmitter emitter{};
  ParticleShape shape{};

  void set_texture(std::string path) {}
  Texture2D* get_texture() { return texture_; }
  const int get_particle_count() { return particles_count_; }
  void play(bool is_loop) {}
  void pause() {}
  void stop() {}

 protected:
  void start() override {
    particles_.set_capacity(max_particles);
    emitter_duration = 1.0f / emitter.rate_over_time;
  }

  void update(float dt) override {
    if (!running) return;

    elapsed_duration += dt;
    if (elapsed_duration <= duration) {
      is_emitting = true;
      emit_particles_rate(dt);
      emit_particles_burst(dt);
    } else {
      if (looping) {
        elapsed_duration = 0.0f;
        running = true;
      } else {
        running = false;
      }
    }
    update_particles(dt);
    update_buffer();
    is_emitting = false;
  }

  void draw() override {
    if (!running) return;
    draw_particles();

    if (debug_mode) {
      draw_shape_debug();
    }
  }

 private:
  Texture2D* texture_ = nullptr;
  boost::circular_buffer<Particle> particles_;
  int particles_count_ = 0;

  bool is_emitting = false;
  float emitter_duration = 0.0f;
  float elapsed_rate_time = 0.0f;
  float elapsed_burst_time = 0.0f;
  float elapsed_duration = 0.0f;

  void emit_particles_rate(float dt) {
    elapsed_rate_time += dt;
    if (elapsed_rate_time <= emitter_duration) return;
    if (emitter.rate_over_time <= 0) return;
    elapsed_rate_time = 0.0f;

    spawn_particle(0);
  };

  void emit_particles_burst(float dt) {
    elapsed_burst_time += dt;
    if (elapsed_burst_time <= emitter.burst.time) return;
    if (emitter.burst.count == 0) return;
    elapsed_burst_time = 0.0f;

    for (int i = 0; i < emitter.burst.count; i++) {
      spawn_particle(i);
    }
  }

  void spawn_particle(int idx) {
    Particle p{};
    auto [pos, dir] = shape.gen_spawn_particle_data(idx, emitter.burst.count);

    p.transform.position = pos + gameobject->transform.position;
    p.transform.scale = {start_size, start_size};
    p.transform.rotation = start_rotation;
    p.alive = true;
    p.lifetime = 0.0f;
    p.velocity.x = start_speed.x * dir.x;
    p.velocity.y = start_speed.y * dir.y;
    p.radius = start_size;

    particles_.push_back(p);
  }

  void update_particles(float dt) {
    for (auto it = particles_.begin(); it != particles_.end(); ++it) {
      it->lifetime += dt;
      it->transform.position.x += it->velocity.x * dt;
      it->transform.position.y += it->velocity.y * dt;

      if (it->lifetime >= lifetime) {
        it->alive = false;
      }
    };
  }

  void update_buffer() {
    while (!particles_.empty() && !particles_.front().alive) {
      particles_.pop_front();
    }
  }

  void draw_particles() {
    for (auto it = particles_.cbegin(); it != particles_.cend(); ++it) {
      if (it->alive) {
        DrawCircle(it->transform.position.x, it->transform.position.y,
                   it->radius, color);
      }
    }
  }

  void draw_shape_debug() {
    auto shape_pos = get_shape_world_pos();
    DrawCircleLines(shape_pos.x, shape_pos.y, shape.radius, RED);
  }

  Vector2 get_shape_world_pos() {
    return shape.transform.position + gameobject->transform.position;
  }

  Vector2 get_shape_world_scale() {
    return shape.transform.scale * gameobject->transform.scale;
  }
};
}  // namespace Component