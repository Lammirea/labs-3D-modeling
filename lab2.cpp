// lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab2.h"

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
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
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
    LRESULT IDT_TIMER1 = NULL;
    SetTimer(hWnd,             // handle to main window 
        IDT_TIMER1,            // timer identifier 
        3000,                 // 10-second interval 
        (TIMERPROC)NULL);     // no timer callback 
    int i = 0;
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
    {
        //i = i++;
        //InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            //считываем ширину экрана
            RECT rect;

            GetWindowRect(hWnd, &rect);
            LONG width = rect.right - rect.left;
            LONG height = rect.bottom - rect.top;
            //////////////////////////////////////////////

            HBITMAP bmw, bmw1, bmw2, bmw3, bmw4, bmw5, bmw6, bmw7, bmw8, bmw9, bmw10, bmw11, bmw12, bmw13, bmw14, bmw15, bmw16, bmw17;
            bmw = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\контуры.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw1 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw2 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw3 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw4 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw5 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw6 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw7 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_7.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw8 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_8.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw9 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_9.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw10 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_10.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw11 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_11.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw12 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_12.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw13 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_13.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw14 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_14.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw15 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_15.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw16 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_16.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bmw17 = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Asus\\Documents\\Алиночкины_документы\\универ\\2 курс\\КГ_3D\\самолёт_кадр_17.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

            HDC memdc;
            memdc = CreateCompatibleDC(hdc);
            SelectObject(memdc, bmw);
            BitBlt(hdc, 0, 0, width, height, memdc, 0, 0, SRCCOPY);
            int j = 0;
            while (true) {
                for (int k = 0; k < 18; k++)
                {
                    if (k == 1)
                    {
                        SelectObject(memdc, bmw1);
                        BitBlt(hdc, 550, 150, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 150, width, height, memdc, 0, 0, SRCINVERT);

                        // break;
                    }
                    else if (k == 2) {
                        SelectObject(memdc, bmw2);
                        BitBlt(hdc, 550, 148, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 148, width, height, memdc, 0, 0, SRCINVERT);
                        // break;
                    }
                    else if (k == 3) {
                        SelectObject(memdc, bmw3);
                        BitBlt(hdc, 550, 146, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 146, width, height, memdc, 0, 0, SRCINVERT);
                        // break;
                    }
                    else if (k == 4) {
                        SelectObject(memdc, bmw4);
                        BitBlt(hdc, 550, 144, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 144, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 5) {
                        SelectObject(memdc, bmw5);
                        BitBlt(hdc, 550, 142, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 142, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 6) {
                        SelectObject(memdc, bmw6);
                        BitBlt(hdc, 550, 140, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 140, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 7) {
                        SelectObject(memdc, bmw7);
                        BitBlt(hdc, 550, 138, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 138, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 8) {
                        SelectObject(memdc, bmw8);
                        BitBlt(hdc, 550, 136, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 136, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 9) {
                        SelectObject(memdc, bmw9);
                        BitBlt(hdc, 550, 134, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 134, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 10) {
                        SelectObject(memdc, bmw10);
                        BitBlt(hdc, 550, 132, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 132, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 11) {
                        SelectObject(memdc, bmw11);
                        BitBlt(hdc, 550, 130, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 130, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 12) {
                        SelectObject(memdc, bmw12);
                        BitBlt(hdc, 550, 128, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 128, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 13) {
                        SelectObject(memdc, bmw13);
                        BitBlt(hdc, 550, 126, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 126, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 14) {
                        SelectObject(memdc, bmw14);
                        BitBlt(hdc, 550, 124, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 124, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 15) {
                        SelectObject(memdc, bmw15);
                        BitBlt(hdc, 550, 122, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 122, width, height, memdc, 0, 0, SRCINVERT);
                        //break
                    }
                    else if (k == 16) {
                        SelectObject(memdc, bmw16);
                        BitBlt(hdc, 550, 120, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 120, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 17) {
                        SelectObject(memdc, bmw17);
                        BitBlt(hdc, 550, 118, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 118, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }
                    else if (k == 18) {
                        SelectObject(memdc, bmw2);
                        BitBlt(hdc, 550, 116, width, height, memdc, 0, 0, SRCINVERT);
                        Sleep(50);
                        BitBlt(hdc, 550, 116, width, height, memdc, 0, 0, SRCINVERT);
                        //break;
                    }

                    j++;
                }
            }
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        //KillTimer(hWnd, ID_TIMER);
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
