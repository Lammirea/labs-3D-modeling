// lab 1.cpp : Определяет точку входа для приложения.
//
#define OnMenuAction1     1
#define OnMenuAction2     2
#define OnMenuAction3     3
#define OnMenuAction4     4

#include "framework.h"
#include "lab 1.h"
#include <wingdi.h>
#include <Windows.h>
#include <cmath>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void MainWndAddMenu(HWND hWnd);
void DrawPlane(HWND hWnd);
void ChangeCoordinates_y_1(HWND hWnd);
void Mirror_OX(HWND hWnd);
void Rotate_Plane_110(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(CreateSolidBrush(RGB(133, 191, 241)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case OnMenuAction1:
                DrawPlane(hWnd);
                break;
            case OnMenuAction2:
                ChangeCoordinates_y_1(hWnd);
                break;
            case OnMenuAction3:
                Mirror_OX(hWnd);
                break;
            case OnMenuAction4:
                Rotate_Plane_110(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
        MainWndAddMenu(hWnd);
        //DrawPlane(hWnd);
        
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



void  MainWndAddMenu(HWND hWnd) {
    HMENU RootMenu = CreateMenu();
    HMENU SubMenu = CreateMenu();

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Действия");
    AppendMenu(SubMenu, MF_STRING, OnMenuAction1, L"Нарисовать самолёт");
    AppendMenu(SubMenu, MF_STRING, OnMenuAction2, L"Перенос на y-1");
    AppendMenu(SubMenu, MF_STRING, OnMenuAction3, L"Отображение относительно оси X");
    AppendMenu(SubMenu, MF_STRING, OnMenuAction4, L"Поворот фигуры на 110 градусы");

    SetMenu(hWnd, RootMenu);
}
void DrawPlane(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    RECT rect;
 
    GetWindowRect(hWnd, &rect);
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;

    //переносим началы координат в середину экрана
    SetMapMode(hdc, MM_ANISOTROPIC);
    SetViewportOrgEx(hdc, width / 2, height / 2, NULL);
    //ставим точку в начало координат
    SetPixel(hdc, 0, 0, RGB(255, 0, 0));

    //Правая часть самолёта
    const int n = 9;
    int RightmoveX[n] = { 530,560,560,530,560,630,560,560,750 }, RightmoveY[n] = { 110,160,460,460,460,460,430,360,380 };
    int RightLineX[n] = { 560,560,530,530,630,560,560,750,560 }, RightLineY[n] = { 160,460,460,410,460,430,360,390,240 };
    for (int i = 0; i < n; i++)
    {
        RightmoveX[i] /= 2;
        RightLineX[i] /= 2;
        RightmoveY[i] /= 2;
        RightLineY[i] /= 2;
       
        MoveToEx(hdc, RightmoveX[i], RightmoveY[i], NULL);
        LineTo(hdc, RightLineX[i], RightLineY[i]);
    }
    //Левая часть самолёта
    const int m = 9;
    int LeftmoveX[n] = { 530,500,500,530,500,430,500,500,310 }, LeftmoveY[n] = { 110,160,460,460,460,460,430,360,380 };
    int LeftLineX[n] = { 500,500,530,530,430,500,500,310,500 }, LeftLineY[n] = { 160,460,460,475,460,430,360,380,240 };
    for (int j = 0; j < m; j++)
    {
        LeftmoveX[j] /= 2;
        LeftLineX[j] /= 2;
        LeftmoveY[j] /= 2;
        LeftLineY[j] /= 2;

        MoveToEx(hdc, LeftmoveX[j], LeftmoveY[j], NULL);
        LineTo(hdc, LeftLineX[j], LeftLineY[j]);
    }

    EndPaint(hWnd, &ps);

}

void ChangeCoordinates_y_1(HWND hWnd) {

    //UpdateWindow(hWnd);
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    RECT rect;

    GetWindowRect(hWnd, &rect);
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;

    //переносим началы координат в середину экрана
    SetMapMode(hdc, MM_ANISOTROPIC);
    SetViewportOrgEx(hdc, width / 2, height / 2, NULL);
    //ставим точку в начало координат
    SetPixel(hdc, 0, 0, RGB(255, 0, 0));

    const int n = 9;
    int RightmoveX[n] = { 530,560,560,530,560,630,560,560,750 }, RightmoveY[n] = { 110,160,460,460,460,460,430,360,380 };
    int RightLineX[n] = { 560,560,530,530,630,560,560,750,560 }, RightLineY[n] = { 160,460,460,410,460,430,360,390,240 };
    for (int i = 0; i < n; i++)
    {
        RightmoveX[i] /= 2;
        RightLineX[i] /= 2;
        RightmoveY[i] /= 2;
        RightLineY[i] /= 2;

        RightmoveY[i] -= 10;
        RightLineY[i] -= 10;
        MoveToEx(hdc, RightmoveX[i], RightmoveY[i], NULL);
        LineTo(hdc, RightLineX[i], RightLineY[i]);
    }
    //Левая часть самолёта
    
    int LeftmoveX[n] = { 530,500,500,530,500,430,500,500,310 }, LeftmoveY[n] = { 110,160,460,460,460,460,430,360,380 };
    int LeftLineX[n] = { 500,500,530,530,430,500,500,310,500 }, LeftLineY[n] = { 160,460,460,475,460,430,360,380,240 };
    for (int j = 0; j < n; j++)
    {
        LeftmoveX[j] /= 2;
        LeftLineX[j] /= 2;
        LeftmoveY[j] /= 2;
        LeftLineY[j] /= 2;

        LeftmoveY[j] -= 10;
        LeftLineY[j] -= 10;
        MoveToEx(hdc, LeftmoveX[j], LeftmoveY[j], NULL);
        LineTo(hdc, LeftLineX[j], LeftLineY[j]);
    }
    EndPaint(hWnd, &ps);
}

void Mirror_OX(HWND hWnd){
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    RECT rect;

    GetWindowRect(hWnd, &rect);
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;

    //переносим началы координат в середину экрана
    SetMapMode(hdc, MM_ANISOTROPIC);
    SetViewportOrgEx(hdc, width / 2, height / 2, NULL);
    //ставим точку в начало координат
    SetPixel(hdc, 0, 0, RGB(255, 0, 0));

    const int n = 9;
    int RightmoveX[n] = { 530,560,560,530,560,630,560,560,750 }, RightmoveY[n] = { 110,160,460,460,460,460,430,360,380 };
    int RightLineX[n] = { 560,560,530,530,630,560,560,750,560 }, RightLineY[n] = { 160,460,460,410,460,430,360,390,240 };
    for (int i = 0; i < n; i++)
    {
        RightmoveX[i] /= 2;
        RightLineX[i] /= 2;
        RightmoveY[i] /= 2;
        RightLineY[i] /= 2;

        RightmoveY[i] *= -1;
        RightLineY[i] *= -1;

        MoveToEx(hdc, RightmoveX[i], RightmoveY[i], NULL);
        LineTo(hdc, RightLineX[i], RightLineY[i]);
    }
    //Левая часть самолёта
    const int m = 9;
    int LeftmoveX[m] = { 530,500,500,530,500,430,500,500,310 }, LeftmoveY[m] = { 110,160,460,460,460,460,430,360,380 };
    int LeftLineX[m] = { 500,500,530,530,430,500,500,310,500 }, LeftLineY[m] = { 160,460,460,475,460,430,360,380,240 };
    for (int j = 0; j < m; j++)
    {
        LeftmoveX[j] /= 2;
        LeftLineX[j] /= 2;
        LeftmoveY[j] /= 2;
        LeftLineY[j] /= 2;

        LeftmoveY[j] *= -1;
        LeftLineY[j] *= -1;

        MoveToEx(hdc, LeftmoveX[j], LeftmoveY[j], NULL);
        LineTo(hdc, LeftLineX[j], LeftLineY[j]);
    }
    EndPaint(hWnd, &ps);
}

void Rotate_Plane_110(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    RECT rect;

    GetWindowRect(hWnd, &rect);
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;

    //переносим началы координат в середину экрана
    SetMapMode(hdc, MM_ANISOTROPIC);
    SetViewportOrgEx(hdc, width / 2, height / 2, NULL);
    //ставим точку в начало координат
    SetPixel(hdc, 0, 0, RGB(255, 0, 0));

    const int m = 9;
    int RightmoveX[m] = { 530,560,560,530,560,630,560,560,750 }, RightmoveY[m] = { 110,160,460,460,460,460,430,360,380 };
    int RightLineX[m] = { 560,560,530,530,630,560,560,750,560 }, RightLineY[m] = { 160,460,460,410,460,430,360,390,240 };
    for (int i = 0; i < m; i++)
    {
        RightmoveX[i] /= 2;
        RightLineX[i] /= 2;
        RightmoveY[i] /= 2;
        RightLineY[i] /= 2;


        MoveToEx(hdc, RightmoveX[i] * cos(110) - RightmoveY[i] * sin(110), RightmoveX[i] * sin(110) + RightmoveY[i] * cos(110), NULL);
        LineTo(hdc, RightLineX[i] * cos(110) - RightLineY[i] * sin(110), RightLineX[i] * sin(110) + RightLineY[i] * cos(110));
    }
    //Левая часть самолёта
   
    int LeftmoveX[m] = { 530,500,500,530,500,430,500,500,310 }, LeftmoveY[m] = { 110,160,460,460,460,460,430,360,380 };
    int LeftLineX[m] = { 500,500,530,530,430,500,500,310,500 }, LeftLineY[m] = { 160,460,460,475,460,430,360,380,240 };
    for (int j = 0; j < m; j++)
    {
        LeftmoveX[j] /= 2;
        LeftLineX[j] /= 2;
        LeftmoveY[j] /= 2;
        LeftLineY[j] /= 2;

        MoveToEx(hdc, LeftmoveX[j] * cos(110) - LeftmoveY[j] * sin(110), LeftmoveX[j] * sin(110) + LeftmoveY[j] * cos(110), NULL);
        LineTo(hdc, LeftLineX[j] * cos(110) - LeftLineY[j] * sin(110), LeftLineX[j] * sin(110) + LeftLineY[j] * cos(110));
    }

    EndPaint(hWnd, &ps);
}