#include "D3DApp.h"

#include "Renderer.h"
#include <sstream>

namespace
{
	CD3DApp* g_D3DApp = nullptr;
}

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	return g_D3DApp->MsgProc(hWnd, msg, wParam, lParam);
}


CD3DApp::CD3DApp(HINSTANCE hInstance)
{
	m_AppInstance = hInstance;
	g_D3DApp = this;
}

CD3DApp::~CD3DApp()
{
}

HINSTANCE CD3DApp::GetInstance() const
{
	return m_AppInstance;
}

HWND CD3DApp::GetMainWindowHandler() const
{
	return m_MainWnd;
}

float CD3DApp::GetAspectRatio() const
{
	return (float)m_ClientWidth / m_ClientHeight;
}

int CD3DApp::Run()
{
	MSG msg = { 0 };
	m_Timer.Reset();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_Timer.Tick();
			if (!m_AppPaused)
			{
				CalculateFrameStats();
				UpdateScene(m_Timer.GetDeltaTime());
				DrawScene();
			}
			else
			{
				Sleep(100);
			}
		}
	}

	return (int)msg.wParam;
}

bool CD3DApp::Init()
{
	if (InitMainWindow())
		return InitRenderer();

	return false;
}

void CD3DApp::OnResize()
{

}

void CD3DApp::UpdateScene(float dt)
{
	if (m_Renderer)
		m_Renderer->Update(dt);
}

void CD3DApp::DrawScene()
{
	if (m_Renderer)
		m_Renderer->Render();
}

LRESULT CD3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			m_AppPaused = true;
			m_Timer.Stop();
		}
		else
		{
			m_AppPaused = false;
			m_Timer.Start();
		}
		return 0;

	case WM_SIZE:
		m_ClientHeight = HIWORD(lParam);
		m_ClientWidth = LOWORD(lParam);

		if (wParam == SIZE_MINIMIZED)
		{
			m_AppPaused = true;
			m_Minimized = true;
			m_Maximized = false;
		}
		else if (wParam == SIZE_MAXIMIZED)
		{
			m_AppPaused = false;
			m_Minimized = false;
			m_Maximized = true;
		}
		else if (wParam == SIZE_RESTORED)
		{
			if (m_Minimized)
			{
				m_AppPaused = false;
				m_Minimized = false;
				OnResize();
			}
			else if (m_Maximized)
			{
				m_AppPaused = false;
				m_Maximized = false;
				OnResize();
			}
			else if (m_Resizing)
			{
				// Skipped on purpose
			}
			else
			{
				OnResize();
			}
		}
		return 0;

	case WM_ENTERSIZEMOVE:
		m_AppPaused = true;
		m_Resizing = true;
		m_Timer.Stop();
		return 0;

	case WM_EXITSIZEMOVE:
		m_AppPaused = false;
		m_Resizing = false;
		m_Timer.Start();
		OnResize();
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_MENUCHAR:
		return MAKELRESULT(0, MNC_CLOSE);

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool CD3DApp::InitMainWindow()
{
	WNDCLASS wc;
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= NULL;
	wc.cbWndExtra		= NULL;
	wc.hInstance		= m_AppInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= L"D3D";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass failed.", 0, 0);
		return false;
	}

	m_MainWnd = CreateWindow(
		L"D3D",
		(LPCWSTR)m_MainWindowCaption.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_ClientWidth,
		m_ClientHeight,
		NULL,
		NULL,
		m_AppInstance,
		NULL
	);

	if (!m_MainWnd)
	{
		MessageBox(0, L"CreateWindow failed.", 0, 0);
		return false;
	}

	return true;
}

bool CD3DApp::InitRenderer()
{
	m_Renderer = new CD3DX11Renderer(m_MainWnd);
	m_Renderer->SetWindowWidth(m_ClientWidth);
	m_Renderer->SetWindowHeight(m_ClientHeight);

	return m_Renderer->Init();
}

void CD3DApp::CalculateFrameStats()
{
	static int frame_count = 0;
	static float time_elapsed = 0.f;

	frame_count++;

	if (m_Timer.GetTotalTime() - time_elapsed >= 1.0f)
	{
		float fps = (float)frame_count;
		float mspf = 1000.f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << m_MainWindowCaption << L" "
			<< L"FPS: " << fps << L" "
			<< L"Czas klatki: " << mspf << "L (ms)";

		SetWindowText(m_MainWnd, outs.str().c_str());

		frame_count = 0;
		time_elapsed += 1.0f;
	}
}