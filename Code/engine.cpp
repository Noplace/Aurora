#include "game_engine.h"
#include "game_view.h"


namespace game_engine {


Engine::Engine() : timer_(NULL),window_(NULL) {
  render_time_span = 0;
}

Engine::~Engine() {

}

int Engine::Initialize() {
  global_time_ = 0;
  timer_->Calibrate();

  gfx_context_.Initialize();
  gfx_context_.CreateDisplay(window_);
  resource_manager.set_engine(this);
  resource_manager.LoadXml("Content\\test.xml");
  
  /*camera2d.Initialize(&gfx_context_);
  camera2d.SetupDisplay();

  effect_.Initialize(&gfx_context_);


  effect_.CreateFromMemory(res->data_pointer,res->data_length);


  */
  
  HRESULT hr = S_OK;
  
  prev_time = timer_->GetCurrentCycles();
  return hr;
}

int Engine::Deinitialize() {
  // if( g_pImmediateContext ) g_pImmediateContext->ClearState();
  resource_manager.UnloadAll();
  gfx_context_.Deinitialize();
  return S_OK;
}

void Engine::Loop() {
 
  curr_time = timer_->GetCurrentCycles();

  float time_span = (curr_time - prev_time) * timer_->resolution();
  prev_time = curr_time;

  render_time_span += time_span;

  process_manager_.Update(1);
  animation_.Process(time_span);


  //if (timer_->isTimeForUpdate(60) == true) {
  if (render_time_span > 16.667f) {

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    gfx_context_.ClearTarget();

    current_scene->Draw();

    gfx_context_.Render();

  }
  global_time_++;
}

}