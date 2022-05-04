// lab_4.cpp : Определяет точку входа для приложения.
//
#define Filter1     1
#define Filter2     2
#define Filter3     3
#define Filter4     4
#define Filter5     5
#define Filter6     6
#define Filter7     7
#define Lighteness  8


#include "framework.h"
#include "lab4.h"
#include "resource.h"

#define MAX_LOADSTRING 100

void MainWndAddMenu(HWND hWnd);
COLORREF** getNeighbours(HDC hdc, int x, int y);
COLORREF brightness(COLORREF source, float k);
COLORREF** multmatr(int matrix[3][3], COLORREF** matrix2);
COLORREF avr(COLORREF** matrix);
void func2(HDC hdc, int matrix[3][3], int XX, int YY);
void light(HDC hdc);
LONG width = 218, height = 290;
int flag = 0;
int arr1[3][3] = { {0,-1,0}, {-1,5,-1}, {0,-1,0} };
int arr2[3][3] = { {-1,-1,-1}, {-1,9,-1}, {-1,-1,-1} };
int arr3[3][3] = { { 1, -2, 1 }, { -2, 5, -2 }, { 1, -2, 1 } };
int arr4[3][3] = { { 0, -1, 0 }, { -1, 4, -1 }, { 1, -2, 1 } };
int arr5[3][3] = { { -1, -1, -1 }, { -1, 8, -1 }, { 0, -1, 0 } };
int arr6[3][3] = { { 1, -2, 1 }, { -2, 4, -2 }, { -1, -1, -1 } };
int arr7[3][3] = { { 1, -2, 1 }, { -2, 3, -2 }, { 1, -2, 1 } };

COLORREF tmp[3][3] = { 0 };
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB4);
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
        CW_USEDEFAULT, 0, 1920 /*ширина экрана CW_USEDEFAULT*/, 900, nullptr, nullptr, hInstance, nullptr);

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
        case Filter1:
            //DrawPlane(hWnd, arr1);
            flag = 1;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case Filter2:
            // Multiply_matrix(hWnd, arr1, mat1);
            flag = 2;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case Filter3:
            //Multiply_matrix(hWnd, arr1, mat2);
            flag = 3;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case Filter4:
            //Multiply_matrix(hWnd, arr1, mat3);
            flag = 4;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case Filter5:
            //Multiply_matrix(hWnd, arr1, mat3);
            flag = 5;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case Filter6:
            //Multiply_matrix(hWnd, arr1, mat3);
            flag = 6;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case Filter7:
            //Multiply_matrix(hWnd, arr1, mat3);
            flag = 7;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        case Lighteness:
            //Multiply_matrix(hWnd, arr1, mat3);
            flag = 8;
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

        HBITMAP bmw = (HBITMAP)LoadImage(NULL, L"D:\\универ\\edited_venya.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
        HDC memdc;
        memdc = CreateCompatibleDC(hdc);
        SelectObject(memdc, bmw);
        BitBlt(hdc, 10, 10, width, height, memdc, 0, 0, SRCCOPY);

        HBITMAP bmw1 = (HBITMAP)LoadImage(NULL, L"D:\\универ\\edited_venya.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
        SelectObject(memdc, bmw1);
        BitBlt(hdc, 30 + width, 10, width, height, memdc, 0, 0, SRCCOPY);

        HBITMAP bmw2 = (HBITMAP)LoadImage(NULL, L"D:\\универ\\edited_venya.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
        SelectObject(memdc, bmw2);
        BitBlt(hdc, 50 + width * 2, 10, width, height, memdc, 0, 0, SRCCOPY);

        //HBITMAP bmw = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PNG1));
        //изменение второго изображения

        switch (flag)
        {
        case 1:
            func2(hdc, arr1, width, height);
            break;
        case 2:
            func2(hdc, arr2, width, height);
            break;
        case 3:
            func2(hdc, arr3, width, height);
            break;
        case 4:
            func2(hdc, arr4, width, height);
            break;
        case 5:
            func2(hdc, arr5, width, height);
            break;
        case 6:
            func2(hdc, arr6, width, height);
            break;
        case 7:
            func2(hdc, arr7, width, height);
            break;
        case 8:
            light(hdc);
            break;
        default:
            break;
        }
        //func2(hdc, arr2, width, height);

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
void  MainWndAddMenu(HWND hWnd) {
    HMENU RootMenu = CreateMenu();
    HMENU SubMenu = CreateMenu();

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Выберите нужную маску");
    AppendMenu(SubMenu, MF_STRING, Filter1, L"Маска 1");
    AppendMenu(SubMenu, MF_STRING, Filter2, L"Маска 2");
    AppendMenu(SubMenu, MF_STRING, Filter3, L"Маска 3");
    AppendMenu(SubMenu, MF_STRING, Filter4, L"Маска 4");
    AppendMenu(SubMenu, MF_STRING, Filter5, L"Маска 5");
    AppendMenu(SubMenu, MF_STRING, Filter6, L"Маска 6");
    AppendMenu(SubMenu, MF_STRING, Filter7, L"Маска 7");
    AppendMenu(SubMenu, MF_STRING, Lighteness, L"Градация яркости");
    SetMenu(hWnd, RootMenu);
}
void light(HDC hdc) {
    int averege = 0;
    int col, r, g, b;
    for (int i = width + 30; i < 30 + 2 * width; i++)
    {
        for (int j = 0; j < height + 10; j++)
        {
            //найти ср.арифм каждого пиксела
            col = GetPixel(hdc, i, j);

            averege = (GetRValue(col) + GetGValue(col) + GetBValue(col)) / 3;
            if (averege <= 128) //условие с тем самым порогом
            {
                SetPixel(hdc, i, j, 0x000000);
            }
            else
                SetPixel(hdc, i, j, 0xffffff);
            if (averege <= 100) //условие с тем самым порогом
            {
                SetPixel(hdc, i + 330, j, 0x000000);
            }
            else
                SetPixel(hdc, i + 330, j, 0xffffff);
            if (averege <= 150) //условие с тем самым порогом
            {
                SetPixel(hdc, i + 660, j, 0x000000);
            }
            else
                SetPixel(hdc, i + 660, j, 0xffffff);

        }
    }
    /*for (int i = width + 30; i < 30 + 2 * width; i++)
    {
        for (int j = 0; j < height + 10; j++)
        {
            col = GetPixel(hdc, i, j);
            r = GetRValue(col);
            g = GetGValue(col);
            b = GetBValue(col);
            col = RGB(r, g, b);
            SetPixel(hdc, i, j, col);
        }
    }*/
    //изменение третьего изображения
    //for (int i = 50 + width * 2; i < 50 + 3 * width; i++)
    //{
    //    for (int j = 0; j < height + 10; j++)
    //    {
    //        if (GetPixel(hdc, i, j) <= 0xc0c0c0) //условие с тем самым порогом
    //        {
    //            SetPixel(hdc, i, j, 0x000000);
    //        }
    //        else
    //            SetPixel(hdc, i, j, 0xffffff);
    //    }
    //}
    //for (int i = 50 + width * 2; i < 50 + 3 * width; i++)
    //{
    //    for (int j = 0; j < height + 10; j++)
    //    {
    //        col = GetPixel(hdc, i, j);
    //        r = GetRValue(col);
    //        g = GetGValue(col);
    //        b = GetBValue(col);
    //        col = RGB(r, g, b);
    //        SetPixel(hdc, i, j, col);
    //    }
    //}
    col = 0;
    //рисуем систему координат для первого изображения:
    MoveToEx(hdc, 30 + width, height + 30, NULL);
    LineTo(hdc, 30 + width, 2 * height + 30);
    LineTo(hdc, 30 + 2 * width, 2 * height + 30);
    int aver_sum = 0, aver_per_pix = 0, aver_col = 0;

    for (int i = width + 30; i < 30 + 2 * width; i++)
    {
        aver_sum = 0;
        MoveToEx(hdc, i + 10, 300, NULL);
        for (int j = 0; j < height + 10; j++)
        {
            col = GetPixel(hdc, i, j);
            aver_per_pix = (GetRValue(col) + GetGValue(col) + GetBValue(col)) / 3;
            aver_sum += aver_per_pix; //сумма пикселей каждого столбца
            //высота столбика равна aver_sum? , а по x их размещать на каждмо пикселе
        }
        aver_col = aver_sum / height;//среднее арифм. каждого столбца
        LineTo(hdc, i + 10, (aver_sum / 100) + height);
    }

    //рисуем систему координат для второго изображения:
    MoveToEx(hdc, 60 + width * 2, height + 30, NULL);
    LineTo(hdc, 60 + width * 2, 2 * height + 30);
    LineTo(hdc, 60 + 3 * width, 2 * height + 30);

    for (int i = 2 * width + 60; i < 60 + 3 * width; i++)
    {
        aver_sum = 0;
        for (int j = 0; j < 2 * height + 30; j++)
        {
            //col = GetPixel(hdc, i, j);
            //aver = (GetRValue(col) + GetGValue(col) + GetBValue(col)) / 3;
            ////aver_arr[i][j] = (GetRValue(col) + GetGValue(col) + GetBValue(col)) / 3;
            //aver_sum += aver;
            //MoveToEx(hdc, i + 10, 90, NULL);
            //LineTo(hdc, i + 10, (int)aver_sum / 100);
        }
    }
    //рисуем систему координат для третьего изображения:
    MoveToEx(hdc, 90 + width * 3, height + 30, NULL);
    LineTo(hdc, 90 + width * 3, 2 * height + 30);
    LineTo(hdc, 90 + 4 * width, 2 * height + 30);

    for (int i = 90 + width * 3; i < 90 + 4 * width; i++)
    {
        for (int j = 0; j < 2 * height + 30; j++)
        {

        }
    }
}

void func2(HDC hdc, int matrix[3][3], int XX, int YY)
{
    COLORREF color;
    int R = 0, sumR = 0;
    int G = 0, sumG = 0;
    int B = 0, sumB = 0;
    int res = 0;
    for (int x = 50 + XX * 2; x < 50 + 3 * XX; x++) {
        for (int y = 10; y < YY + 10; y++)
        {
            R = 0, G = 0, B = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    color = GetPixel(hdc, x + i, y + j);
                    R = GetRValue(color);
                    sumR += R * matrix[i + 1][j + 1];
                    G = GetGValue(color);
                    sumG += G * matrix[i + 1][j + 1];
                    B = GetBValue(color);
                    sumB += B * matrix[i + 1][j + 1];
                }
            }
            //контролируем переполнение переменных
            if (sumR < 0) sumR = 0;
            if (sumR > 255) sumR = 255;
            if (sumG < 0) sumG = 0;
            if (sumG > 255) sumG = 255;
            if (sumB < 0) sumB = 0;
            if (sumB > 255) sumB = 255;

            SetPixel(hdc, x, y, RGB(sumR, sumG, sumB));
            sumR = sumG = sumB = 0;
            //вычисление нового цвета
            COLORREF NewColor = GetPixel(hdc, x, y);
            //повышение резкости
            COLORREF resColor = (GetRValue(color) + GetGValue(color) + GetBValue(color)) / 3;
            res += resColor;
            //COLORREF color = GetPixel(hdc, x, y);
            //COLORREF** neighbours = getNeighbours(hdc, x, y);
            //SetPixel(hdc, x, y, avr(multmatr(matrix, neighbours)));

            //SetPixel(hdc,x,y, (-neighbours[0][1] - neighbours[1][0] - neighbours[2][1] - neighbours[1][2] + 5* neighbours[1][1])/5);
        }
        res /= 310;
        //MoveToEx(hdc, x, YY + 15, NULL);
        //LineTo(hdc, x, YY + res);
        res = 0;
    }
    int aver_sum = 0, aver_per_pix = 0, aver_col = 0, col = 0;
    for (int i = 2 * width + 50; i < 50 + 3 * width; i++)
    {
        aver_sum = 0;
        MoveToEx(hdc, i, 300, NULL);
        for (int j = 0; j < height + 10; j++)
        {
            col = GetPixel(hdc, i, j);
            aver_per_pix = (GetRValue(col) + GetGValue(col) + GetBValue(col)) / 3;
            aver_sum += aver_per_pix; //сумма пикселей каждого столбца
            //высота столбика равна aver_sum? , а по x их размещать на каждмо пикселе
        }
        aver_col = aver_sum / height;//среднее арифм. каждого столбца
        LineTo(hdc, i, (aver_sum / 260) + height);
    }
}

COLORREF brightness(COLORREF source, float k)
{
    BYTE red = GetRValue(source);
    BYTE green = GetGValue(source);
    BYTE blue = GetBValue(source);
    return RGB(((int)((int)red + k < 255 ? (int)red + k : 255)),
        ((int)((int)green + k < 255 ? (int)green + k : 255)),
        ((int)((int)blue + k < 255 ? (int)blue + k : 255)));
}

COLORREF** getNeighbours(HDC hdc, int x, int y)
{
    COLORREF** res = new COLORREF * [3]();
    for (int i = 0; i < 3; i++)
        res[i] = new COLORREF[3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (x + i < 0 || y + j < 0 || y + j > 290 || x + i>310) res[i][j] = GetPixel(hdc, x, y);
            res[i][j] = GetPixel(hdc, i, j);
        }
    return res;
}

COLORREF** multmatr(int matrix[3][3], COLORREF** matrix2)
{
    int tmpH = height + 2 * 3, tmpW = width + 2 * 3;

    COLORREF** res = new COLORREF * [3]();
    for (int i = 0; i < 3; i++)
        res[i] = new COLORREF[3];
    int k = 0;
    for (k = -1; k < 2; k++) {
        for (int j = -1; j < 2; j++) {
            res[k][j] = RGB(matrix[k + 1][j + 1] * GetRValue(matrix2[k][j]), matrix[k + 1][j + 1] * GetGValue(matrix2[k][j]), matrix[k + 1][j + 1] * GetBValue(matrix2[k][j]));
        }
    }
    return res;
}

COLORREF avr(COLORREF** matrix)
{
    int sumR = 0;
    int sumG = 0;
    int sumB = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            sumR += GetRValue(matrix[i][j]);
            sumG += GetGValue(matrix[i][j]);
            sumB += GetBValue(matrix[i][j]);

        }
        /*if (sumR < 0) sumR = 0;
        if (sumR > 255) sumR = 255;
        if (sumG < 0) sumG = 0;
        if (sumG > 255) sumG = 255;
        if (sumB < 0) sumB = 0;
        if (sumB > 255) sumB = 255;*/
    }
    sumR = sumR / 9;
    sumG = sumG / 9;
    sumB = sumB / 9;

    return RGB(sumR, sumG, sumB);
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

