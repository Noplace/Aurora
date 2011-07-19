#ifndef GAME_ENGINE_ENGINE_H
#define GAME_ENGINE_ENGINE_H

#include <WinCore/windows/windows.h>
#include <WinCore/timer/timer2.h>
#include <WinCore/animation/animation.h>
#include <VisualEssence/Code/context/contextd3d11.h>
//#include <Graphics/vertex.h>
#include <VisualEssence/Code/buffer/vertex_buffer.h>
#include <VisualEssence/Code/camera/camera2d.h>
//#include <Graphics/font/bmfont/font.h>
#include <VisualEssence/Code/effect/effect.h>
#include <VisualEssence/Code/font/writer.h>
#include "component.h"
#include "resource/resource_manager.h"


namespace game_engine {

class GameView;

class Engine {
 public:
  Engine();
  ~Engine();
  int Initialize();
  int Deinitialize();
  void Loop();
  game_engine::resource::ResourceManager resource_manager;
  utilities::Timer* timer() { return timer_; }
  void set_timer(utilities::Timer* timer) { timer_ = timer; }
  core::windows::Window* window() { return window_; }
  void set_window(core::windows::Window* window) { window_ = window; }
  core::animation::Context& animation() { return animation_; }
  graphics::ContextD3D11& gfx_context() { return gfx_context_; }
  uint64_t global_time() { return global_time_; }
  GameView* current_scene;
 private:
  utilities::Timer* timer_;
  core::windows::Window* window_;
  core::animation::Context animation_;
  graphics::ContextD3D11 gfx_context_;
  uint64_t global_time_;
  //graphics::Effect effect_;
  //graphics::GameVertexDecl vdecl;
  //graphics::VertexBuffer<graphics::GameVertex> vbuffer;
  //graphics::Camera2D camera2d;
};

}

#endif