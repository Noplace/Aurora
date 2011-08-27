#include "aurora.h"
#include "game_view.h"


namespace aurora {


Engine::Engine() : timer_(NULL),window_(NULL) {
  
}

Engine::~Engine() {

}

int Engine::Initialize() {
  memset(&timing,0,sizeof(timing));
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
  
  timing.prev_cycles = timer_->GetCurrentCycles();
  return hr;
}

int Engine::Deinitialize() {
  // if( g_pImmediateContext ) g_pImmediateContext->ClearState();
  resource_manager.UnloadAll();
  gfx_context_.Deinitialize();
  return S_OK;
}

void Engine::Loop() {
 
  timing.current_cycles = timer_->GetCurrentCycles();
  uint64_t cycle_diff = (timing.current_cycles - timing.prev_cycles);
  float time_span =  cycle_diff * timer_->resolution();
  
  process_manager_.Update(time_span);
  animation_.Process(time_span);
  current_scene->Update(time_span);

  if (timing.render_time_span > 16.667f) {

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    gfx_context_.ClearTarget();

    current_scene->Draw();

    gfx_context_.Render();

    timing.render_time_span = 0;
  }

  timing.fps_time_span += time_span;
  timing.render_time_span += time_span;
  timing.total_cycles += cycle_diff;
  timing.prev_cycles = timing.current_cycles;
  timing.fps_counter++;
  if (timing.fps_time_span >= 1000) {
    timing.fps = timing.fps_counter;
    timing.fps_counter = 0;
    timing.fps_time_span = 0;
  }
}

}