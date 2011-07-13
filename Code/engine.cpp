#include "game_engine.h"
#include "game_view.h"


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile( LPCSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}


namespace game_engine {

Engine::Engine() : timer_(NULL),window_(NULL) {
}

Engine::~Engine() {

}

int Engine::Initialize() {
  global_time_ = 0;
  timer_->Calibrate();
  animation_.set_delta(1);
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
  
  
  return hr;
}

int Engine::Deinitialize() {
    // if( g_pImmediateContext ) g_pImmediateContext->ClearState();
    gfx_context_.Deinitialize();
    return S_OK;
}

void Engine::Loop() {
   //static float time = 0;
  //graphics::VertexBuffer<int> vb;
  animation_.Process();
  if (timer_->isTimeForUpdate(60) == true) {
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