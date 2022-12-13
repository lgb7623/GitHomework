#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

HINSTANCE _hInstance;
HWND _hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpszCmdParam,
    _In_ int nCmdShow)

{
    _hInstance = hInstance;

    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = (WNDPROC)WndProc;
    wndClass.lpszClassName = WIN_NAME;
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;


    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WIN_NAME,
        WIN_NAME,
        WINSTYLE,
        WINSTART_X,
        WINSTART_Y,
        WINSIZE_X,
        WINSIZE_Y,
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);

    if (FAILED(ShowWindow))
    {
        return 0;
    }

    MSG message;

    while (GetMessage(&message, 0, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    UnregisterClass(WIN_NAME, hInstance);
    return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_SPACE:

            break;
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0, width, height };
    AdjustWindowRect(&rc, WINSTYLE, false);

    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}
