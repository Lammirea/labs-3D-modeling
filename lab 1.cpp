// lab 1.cpp : Определяет точку входа для приложения.
//
#define OnMenuAction1     1
#define OnMenuAction2     2
#define OnMenuAction3     3
#define OnMenuAction4     4

#define _USE_MATH_DEFINES

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
double DrawPlane(HWND hWnd, double arr[20][4]);
double Multiply_matrix(HWND hWnd, double arr[20][4], double matrix[3][3]);

/*double ChangeCoordinates_y_1(HWND hWnd, int arr1[20][4], double arrRes[20][4], double mat1[3][3]);
double Mirror_OX(HWND hWnd, int arr1[20][4],double mat2[3][3], double arrRes[20][4]);
double Rotate_Plane_110(HWND hWnd, int arr1[20][4], double mat3[3][3], double arrRes[20][4]);*/

const int n = 20;
double arr1[20][4] = { {530,110,1,0},{560,160,1,1},{560,460,1,1},{630,460,1,1},{560,430,1,1},{560,390,1,0},{750,410,1,1},{560,240,1,1},{530,110,1,0},{500,160,1,1},{500,460,1,1},{430,460,1,1},{500,430,1,1},{500,390,1,0},{330,410,1,1},{500,240,1,1},{530,420,1,0},{530,480,1,1},{500,460,1,0},{560,460,1,1} };
//int arr1[18][3] = { {530,110,1},{560,160,1},{560,460,1},{530,460,1},{560,460,1},{630,460,1},{560,430,1},{560,360,1},{750,390,1},{530,110,1},{500,160,1},{500,460,1},{530,460,1},{500,460,1},{430,460,1},{500,430,1},{500,360,1},{310,380,1} };
//int arr1[32][3] = { {530,110,1},{560,160,1},{560,160,1},{560,460,1},{560,460,1},{630,460,1},{630,460,1},{560,430,1},{560,430,1},{560,390,1},{560,390,1},{750,410,1},{750,410,1},{560,240,1},{530,110,1},{500,160,1},{500,160,1},{500,460,1},{500,460,1},{430,460,1},{430,460,1},{500,430,1},{500,430,1},{500,390,1},{500,390,1},{310,410,1},{310,410,1},{500,240,1},{530,420,1},{530,480,1},{500,460,1},{560,460,1} };
//double arrRes[18][4] = { 0 };
double arrRes[20][4] = { {0,0,0,0}, {0,0,0,1},{0,0,0,1}, {0,0,0,1},{0,0,0,1}, {0,0,0,0},{0,0,0,1}, {0,0,0,1},{0,0,0,0}, {0,0,0,1},{0,0,0,1}, {0,0,0,1},{0,0,0,1}, {0,0,0,0},{0,0,0,1}, {0,0,0,1},{0,0,0,0}, {0,0,0,1}, {0,0,0,0},{0,0,0,1} };
//arrSecRes[32][4] = { {0,0,0,0}, {0,0,0,1},  {0,0,0,0},  {0,0,0,1}, {0,0,0,0},   {0,0,0,1},  {0,0,0,0},  {0,0,0,1},  {0,0,0,0},  {0,0,0,1},  {0,0,0,0},  {0,0,0,1},  {0,0,0,0},  {0,0,0,1},  {0,0,0,0},  {0,0,0,1},  {0,0,0,0},  {0,0,0,1},  {0,0,0,0},  {0,0,0,1},   {0,0,0,0},  {0,0,0,1}, {0,0,0,0},  {0,0,0,1},  {0,0,0,0},  {0,0,0,1},  {0,0,0,0}, {0,0,0,1},   {0,0,0,0},  {0,0,0,1},  {0,0,0,0},   {0,0,0,1} };
double a = 90 * M_PI / 180;
double mat1[3][3] = { {0.5,0,0},{0,0.5,0},{0,350,1} };
double mat2[3][3] = { {0.5,0,0},{0,-0.5,0},{0,0,1} };
double mat3[3][3] = { {cos(a),sin(a),0},{-sin(a),cos(a),0},{-arr1[0][0] * (cos(a) - 1) + arr1[0][1] * sin(a),-arr1[0][1] * (cos(a) - 1) - arr1[0][0] * sin(a),1} };

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
    if (!InitInstance(hInstance, nCmdShow))
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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(133, 191, 241)));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
            DrawPlane(hWnd, arr1);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case OnMenuAction2:
            Multiply_matrix(hWnd, arr1, mat1);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case OnMenuAction3:
            Multiply_matrix(hWnd, arr1, mat2);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case OnMenuAction4:
            Multiply_matrix(hWnd, arr1, mat3);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        MainWndAddMenu(hWnd);
        RECT rect;

        GetWindowRect(hWnd, &rect);
        LONG width = rect.right - rect.left;
        LONG height = rect.bottom - rect.top;

        //переносим началы координат в середину экрана
        SetMapMode(hdc, MM_ANISOTROPIC);
        SetViewportOrgEx(hdc, width / 2, height / 2, NULL);

        //ставим точку в начало координат
        SetPixel(hdc, 0, 0, RGB(255, 0, 0));

        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (arr1[i][3] == 0) {
                    MoveToEx(hdc, arr1[i][0], arr1[i][1], NULL);
                }
                else if (arr1[i][3] == 1) {
                    LineTo(hdc, arr1[i][0], arr1[i][1]);
                }

            }
        }

        //DrawPlane(hWnd);
        EndPaint(hWnd, &ps);
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
    AppendMenu(SubMenu, MF_STRING, OnMenuAction4, L"Поворот фигуры на 110 градусов");

    SetMenu(hWnd, RootMenu);
}

double DrawPlane(HWND hWnd, double arr[20][4]) {
    /*for (int i = 0; i < 18; i++)
    {
        arr1[i][0] /= 2;
        arr1[i][1] /= 2;
        for (int j = 0; j < 4; j++)
        {
            arrSecRes[i][j] = arr1[i][j];
        }
        if (i % 2 == 0) {
            arrSecRes[i][3] = 0;
        }
        else arrSecRes[i][3] = 1;
    }*/
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            return arr[i][j];
        }
    }

}

double Multiply_matrix(HWND hWnd, double arr[20][4], double matrix[3][3]) {
    double arrRes[20][4] = { {0,0,0,0}, {0,0,0,1},{0,0,0,1}, {0,0,0,1},{0,0,0,1}, {0,0,0,0},{0,0,0,1}, {0,0,0,1},{0,0,0,0}, {0,0,0,1},{0,0,0,1}, {0,0,0,1},{0,0,0,1}, {0,0,0,0},{0,0,0,1}, {0,0,0,1},{0,0,0,0}, {0,0,0,1}, {0,0,0,0},{0,0,0,1} };
    for (int i = 0; i < 20; i++)
    {
        //arr1[i][0] /= 2;
        //arr1[i][1] /= 2;
        //buf = arr[i][0];
        for (int j = 0; j < 3; j++)
        {
            //arrRes[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                arrRes[i][j] += arr[i][k] * matrix[k][j];
            }
        }
    }
    /*for (int i = 0; i < 32; i++)
    {
        arrRes[i][0] /= 2;
        arrRes[i][1] /= 2;
        for (int j = 0; j < 4; j++)
        {
            arrSecRes[i][j] = arrRes[i][j];
        }
        if (i % 2 == 0) {
            arrSecRes[i][3] = 0;
        }
        else arrSecRes[i][3] = 1;
    }*/
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arr1[i][j]=arrRes[i][j];
        }
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            return arr1[i][j];
        }
    }

}

/*double Mirror_OX(HWND hWnd, int arr1[20][4], double mat2[3][3], double arrRes[20][4]) {
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            arrRes[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                arrRes[i][j] += arr1[i][k] * mat2[k][j];
            }
        }
    }
    /*for (int i = 0; i < 32; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            arrSecRes[i][j] = arrRes[i][j];
        }
        if (i % 2 == 0) {
            arrSecRes[i][3] = 0;
        }
        else arrSecRes[i][3] = 1;
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            return arrRes[i][j];
        }
    }
}

double Rotate_Plane_110(HWND hWnd, int arr1[20][4], double mat3[3][3], double arrRes[20][4]) {
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            arrRes[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                arrRes[i][j] += arr1[i][k] * mat3[k][j];
            }
        }
    }
    /*for (int i = 0; i < 32; i++)
    {
        //arrRes[i][0] /= 2;
        //arrRes[i][1] /= 2;
        for (int j = 0; j < 4; j++)
        {
            arrSecRes[i][j] = arrRes[i][j];
        }
        if (i % 2 == 0) {
            arrSecRes[i][3] = 0;
        }
        else arrSecRes[i][3] = 1;
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            return arrRes[i][j];
        }
    }

}*/