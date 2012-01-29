#include "aurora.h"


namespace aurora {

Engine::Engine() :gfx_context_(nullptr), timer_(nullptr),window_(nullptr) {
  
}

Engine::~Engine() {

}

int Engine::Initialize() {
  memset(&timing,0,sizeof(timing));
  timer_->Calibrate();
  process_manager_.AddProcess(&animation_);
  gfx_context_ = new graphics::ContextD3D11();
  
  auto hr = gfx_context_->Initialize();
  if (hr != S_OK) {
    log.Channel("Engine").Log("ERROR: Engine::Initialize - gfx_context_->Initialize failed, ERROR Code = %08x\n",hr);
    return hr;
  }
  hr = gfx_context_->CreateDisplay(window_);
  if (hr != S_OK) {
    log.Channel("Engine").Log("ERROR: Engine::Initialize - gfx_context_->CreateDisplay failed, ERROR Code = %08x\n",hr);
    return hr;
  }
  resource_manager.set_engine(this);
  
  
  /*camera2d.Initialize(&gfx_context_);
  camera2d.SetupDisplay();

  effect_.Initialize(&gfx_context_);


  effect_.CreateFromMemory(res->data_pointer,res->data_length);


  */
 
  timing.prev_cycles = timer_->GetCurrentCycles();
  return hr;
}

int Engine::Deinitialize() {
  // if( g_pImmediateContext ) g_pImmediateContext->ClearState();
  resource_manager.UnloadAll();
  if (gfx_context_!=nullptr) {
    gfx_context_->Deinitialize();
    delete gfx_context_;
  }
  return S_OK;
}

void Engine::Loop() {
  const float dt =  16.667f;
  timing.current_cycles = timer_->GetCurrentCycles();
  uint64_t cycle_diff = (timing.current_cycles - timing.prev_cycles);
  float time_span =  cycle_diff * timer_->resolution();
  if (time_span > 250.0f) //clamping time
    time_span = 250.0f;
  //input_.Poll();

  //process_manager_.Update(time_span);
  
  timing.span_accumulator += time_span;
  while (timing.span_accumulator >= dt) {
    timing.span_accumulator -= dt;
    process_manager_.Update(dt);
    current_scene->Update(dt);
    timing.ups++;
  }
 
  current_scene->Interpolate(timing.span_accumulator/dt);

  if (timing.render_time_span > 16.667f) {

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    gfx_context_->ClearTarget();

    current_scene->Draw();

    gfx_context_->Render();

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

void Engine::HandleWindowMessages(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam) {
  if (message == WM_KEYDOWN) {
    input_.keyboard_buffer[wparam&0xff] = true;
    current_scene->Input();
  }
  if (message == WM_KEYUP) {
    input_.keyboard_buffer[wparam&0xff] = false;
    current_scene->Input();
  }
}

}