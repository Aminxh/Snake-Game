#include <windows.h>
#include <iostream>
#include "clui.h"
#include <conio.h>
#include <string.h>
#include <ios>
#include <limits>
#include <cstdlib>
using namespace std;

void Hi();
int Len(int **arr);
void Play();
void Speed();
void Interaction();
void Table();
void Struct_sorter(struct user *str);

int delay_slow = 190;
int delay_medium = 80;
int delay_fast = 0;
int defult = delay_slow;
int number_menu;
int number_interaction;
int number_speed;
int number_escape;
int score_1 = 0;
int score_2 = 0;
int num_user = -2;
int count_num = 0;
int counter_table = 0;
int row_table = 0;
char *user_1 = new char[30];
char *user_2 = new char[30];
int **body_1 = new int *[1500];
int **body_2 = new int *[1500];

struct user
{
    int score;
    char *name = new char[30];
};

user arr_u[30];

// ---------------------------------------------------------------------------

int main()
{

    init_clui();
    Hi();

    if (number_menu == 1)
    {
        clear_screen();
        Play();
    }

    if (number_menu == 2)
    {
        clear_screen();
        Speed();
    }

    if (number_menu == 3)
        Table();

    if (number_menu == 4)
        quit();

    return 0;
}

void Hi()
{
    number_menu = 0;

    cursor_to_pos(get_window_rows() / 2 - 7, get_window_cols() / 2 - 5);
    change_color_rgb(255, 0, 0);
    cout << "Hello Friend !";

    cursor_to_pos(get_window_rows() / 2 - 3, get_window_cols() / 2 - 7);
    change_color_rgb(100, 100, 0);
    cout << "1) Start Playing";

    cursor_to_pos(get_window_rows() / 2 - 1, get_window_cols() / 2 - 7);
    cout << "2) Speed" << endl;

    cursor_to_pos(get_window_rows() / 2 + 1, get_window_cols() / 2 - 7);
    cout << "3) Scores Table" << endl;

    cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 2 - 7);
    cout << "4) Exit" << endl;

    cursor_to_pos(get_window_rows() / 2 + 6, get_window_cols() / 2 - 8);
    change_color_rgb(55, 204, 39);
    cout << "Please Enter A Number : ";

    cin >> number_menu;
}

//------------------------------------------------------------------------------

void Play()
{
    num_user += 2;
    count_num += 1;

    score_1 = 0, score_2 = 0;

    int x_head_1 = (get_window_cols() / 2) - 2;
    int x_head_2 = (get_window_cols() / 2);
    int y_head_1 = (get_window_rows() / 4) + 2;
    int y_head_2 = (get_window_rows() / 4) * 3;

    char head_1 = 'X';
    char head_2 = 'X';

    int x_1_get = 0, y_1_get = 0, x_2_get = 0, y_2_get = 0;
    int x_1_end = 0, y_1_end = 0, x_2_end = 0, y_2_end = 0;
    int random_x_a, random_y_a, check_random = -1;
    int random_x_b, random_y_b, check_random_b = -1;

    for (int i = 0; i < 3; i++)
    {
        if (i == 2)
        {
            body_1[i + 1] = new int[2];
            body_1[i + 1][0] = 40000;
        }
        body_1[i] = new int[2];
        body_1[i][0] = x_head_1 - (i + 1);
        body_1[i][1] = y_head_1;
    }

    for (int i = 0; i < 3; i++)
    {
        if (i == 2)
        {
            body_2[i + 1] = new int[2];
            body_2[i + 1][0] = 40000;
        }
        body_2[i] = new int[2];
        body_2[i][0] = x_head_2 + (i + 1);
        body_2[i][1] = y_head_2;
    }

    int x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, y_prim_1 = 0, y_prim_2 = 0;

    fflush(stdin);

    cursor_to_pos(get_window_rows() / 2 - 3, get_window_cols() / 2 - 14);
    change_color_rgb(252, 25, 40);
    cout << "Please Enter User 1's Name : ";
    change_color_rgb(231, 237, 45);
    cin.getline(user_1, 30);

    cursor_to_pos(get_window_rows() / 2 - 1, get_window_cols() / 2 - 14);
    change_color_rgb(252, 25, 40);
    cout << "Please Enter User 2's Name : ";
    change_color_rgb(231, 237, 45);
    cin.getline(user_2, 30);

    strcpy(arr_u[num_user].name, user_1);
    strcpy(arr_u[num_user + 1].name, user_2);

    char *underline = new char[get_window_cols() - get_window_cols() / 2];
    for (int i = 0; i < get_window_cols() - get_window_cols() / 2; i++)
        underline[i] = '_';

    while (true)
    {
        arr_u[num_user].score = score_1;
        arr_u[num_user + 1].score = score_2;

        int len_1 = Len(body_1);
        int len_2 = Len(body_2);

        change_color_rgb(255, 255, 255);
        clear_screen();

        cursor_to_pos(5, get_window_cols() / 2 - get_window_cols() / 4);
        cout << underline;

        cursor_to_pos(5, 5);
        change_color_rgb(30, 255, 0);
        cout << user_1 << " : " << score_1;

        cursor_to_pos(5, get_window_cols() - get_window_cols() / 4 + 10);
        change_color_rgb(0, 17, 255);
        cout << user_2 << " : " << score_2;

// ---------------------------------------------------------------------------

        cursor_to_pos(y_head_1, x_head_1);
        change_color_rgb(30, 255, 0);
        cout << head_1;

        if (x_1 == 0 && y_1 == 0)
        {
            for (int i = 0; i < len_1; i++)
            {
                cursor_to_pos(body_1[i][1], body_1[i][0]);
                cout << "O";
            }
        }

        if (x_1 != 0 || y_1 != 0)
        {
            for (int j = len_1 - 1; j >= 0; j--)
            {
                if (j == 0)
                {
                    cursor_to_pos(y_1_get, x_1_get);
                    cout << "O";
                    body_1[j][0] = x_1_get;
                    body_1[j][1] = y_1_get;
                    break;
                }

                if (j == len_1 - 1)
                {
                    x_1_end = body_1[j][0];
                    y_1_end = body_1[j][1];
                }

                body_1[j][0] = body_1[j - 1][0];
                body_1[j][1] = body_1[j - 1][1];
            }

            for (int i = 1; i < len_1; i++)
            {
                if (i == len_1 - 1)
                {
                    cursor_to_pos(body_1[i][1], body_1[i][0]);
                    cout << "O";
                    break;
                }

                if (i != 0)
                {
                    cursor_to_pos(body_1[i][1], body_1[i][0]);
                    cout << "O";
                }
            }
        }

        if (GetAsyncKeyState(VK_UP))
        {
            x_1 = 0;
            y_1 = -1;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            x_1 = 0;
            y_1 = 1;
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            y_1 = 0;
            x_1 = -1;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            y_1 = 0;
            x_1 = 1;
        }

        x_1_get = x_head_1;
        y_1_get = y_head_1;

        x_head_1 += x_1;
        y_head_1 += y_1;

//--------------------------------------------------------------

        cursor_to_pos(y_head_2, x_head_2);
        change_color_rgb(0, 17, 255);
        cout << head_2;

        if (x_2 == 0 && y_2 == 0)
        {
            for (int i = 0; i < len_2; i++)
            {
                cursor_to_pos(body_2[i][1], body_2[i][0]);
                cout << "O";
            }
        }

        if (x_2 != 0 || y_2 != 0)
        {
            for (int j = len_2 - 1; j >= 0; j--)
            {
                if (j == 0)
                {
                    cursor_to_pos(y_2_get, x_2_get);
                    cout << "O";
                    body_2[j][0] = x_2_get;
                    body_2[j][1] = y_2_get;
                    break;
                }

                if (j == len_2 - 1)
                {
                    x_2_end = body_2[j][0];
                    y_2_end = body_2[j][1];
                }

                body_2[j][0] = body_2[j - 1][0];
                body_2[j][1] = body_2[j - 1][1];
            }

            for (int i = 1; i < len_2; i++)
            {
                if (i == len_2 - 1)
                {
                    cursor_to_pos(body_2[i][1], body_2[i][0]);
                    cout << "O";
                    break;
                }

                if (i != 0)
                {
                    cursor_to_pos(body_2[i][1], body_2[i][0]);
                    cout << "O";
                }
            }
        }

        if (GetAsyncKeyState(VK_NUMPAD5))
        {
            x_2 = 0;
            y_2 = -1;
        }
        if (GetAsyncKeyState(VK_NUMPAD2))
        {
            x_2 = 0;
            y_2 = 1;
        }
        if (GetAsyncKeyState(VK_NUMPAD1))
        {
            y_2 = 0;
            x_2 = -1;
        }
        if (GetAsyncKeyState(VK_NUMPAD3))
        {
            y_2 = 0;
            x_2 = 1;
        }

        x_2_get = x_head_2;
        y_2_get = y_head_2;

        x_head_2 += x_2;
        y_head_2 += y_2;

        check_random += 1;
        if (check_random % 80 == 0)
        {
            random_x_a = (rand() % (get_window_cols() - 2 + 1)) + 2;
            random_y_a = (rand() % (get_window_rows() - 7 + 1)) + 7;
        }

        cursor_to_pos(random_y_a, random_x_a);
        change_color_rgb(252, 252, 252);
        cout << "@";

        check_random_b += 1;
        if (check_random_b % 50 == 0)
        {
            random_x_b = (rand() % (get_window_cols() - 2 + 1)) + 2;
            random_y_b = (rand() % (get_window_rows() - 7 + 1)) + 7;
            if (random_x_a == random_x_b && random_y_a == random_y_b)
            {
                random_x_b = (rand() % (get_window_cols() - 2 + 1)) + 2;
                random_y_b = (rand() % (get_window_rows() - 7 + 1)) + 7;
            }
        }
        cursor_to_pos(random_y_b, random_x_b);
        change_color_rgb(255, 0, 30);
        cout << "#";

        if (x_head_1 == random_x_b && y_head_1 == random_y_b)
        {
            play_beep();
            delay(3500);
            Interaction();
        }

        if (x_head_2 == random_x_b && y_head_2 == random_y_b)
        {
            play_beep();
            delay(3500);
            Interaction();
        }

        if (x_head_2 == x_head_1 && y_head_2 == y_head_1)
        {
            play_beep();
            delay(3000);
            Interaction();
        }

        if (x_head_1 == random_x_a && y_head_1 == random_y_a)
        {
            play_beep();
            score_1 += 1;
            body_1[len_1 + 1] = new int[2];
            body_1[len_1 + 1][0] = 40000;
            body_1[len_1][0] = x_1_end;
            body_1[len_1][1] = y_1_end;
            cursor_to_pos(body_1[len_1][1], body_1[len_1][0]);
            cout << "O";
            random_x_a = (rand() % (get_window_cols() - 2 + 1)) + 2;
            random_y_a = (rand() % (get_window_rows() - 7 + 1)) + 7;
        }

        if (x_head_2 == random_x_a && y_head_2 == random_y_a)
        {
            play_beep();
            score_2 += 1;
            body_2[len_2 + 1] = new int[2];
            body_2[len_2 + 1][0] = 40000;
            body_2[len_2][0] = x_2_end;
            body_2[len_2][1] = y_2_end;
            cursor_to_pos(body_2[len_2][1], body_2[len_2][0]);
            cout << "O";
            random_x_a = (rand() % (get_window_cols() - 2 + 1)) + 2;
            random_y_a = (rand() % (get_window_rows() - 7 + 1)) + 7;
        }

        for (int i = 0; i < len_1; i++)
        {
            if (x_head_1 == body_1[i][0] && y_head_1 == body_1[i][1])
            {
                play_beep();
                delay(3500);
                Interaction();
            }
            if (x_head_2 == body_1[i][0] && y_head_2 == body_1[i][1])
            {
                play_beep();
                delay(3500);
                Interaction();
            }
        }

        for (int i = 0; i < len_2; i++)
        {
            if (x_head_2 == body_2[i][0] && y_head_2 == body_2[i][1])
            {
                play_beep();
                delay(3500);
                Interaction();
            }
            if (x_head_1 == body_2[i][0] && y_head_1 == body_2[i][1])
            {
                play_beep();
                delay(3500);
                Interaction();
            }
        }

        if (x_head_1 == 0 || x_head_1 == get_window_cols() || y_head_1 == 5 || y_head_1 == get_window_rows())
        {
            play_beep();
            delay(3500);
            Interaction();
        }
        if (x_head_2 == 0 || x_head_2 == get_window_cols() || y_head_2 == 5 || y_head_2 == get_window_rows())
        {
            play_beep();
            delay(3500);
            Interaction();
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            clear_screen();
            cursor_to_pos(9, get_window_cols() / 2 - 8);
            change_color_rgb(226, 3, 255);
            cout << "1) Resume ";

            cursor_to_pos(13, get_window_cols() / 2 - 8);
            cout << "2) Speed ";

            cursor_to_pos(17, get_window_cols() / 2 - 8);
            cout << "3) Main Menu ";

            cursor_to_pos(21, get_window_cols() / 2 - 8);
            cout << "4) Exit ";

            cursor_to_pos(25, get_window_cols() / 2 - 11);
            change_color_rgb(255, 99, 3);
            cout << "Choose What To Happen : ";
            cin >> number_escape;

            if (number_escape == 1){}

            if (number_escape == 2)
            {
                clear_screen();

                cursor_to_pos(9, get_window_cols() / 2 - 8);
                change_color_rgb(226, 3, 255);
                cout << "1) Slow " << endl;

                cursor_to_pos(14, get_window_cols() / 2 - 8);
                cout << "2) Medium " << endl;

                cursor_to_pos(19, get_window_cols() / 2 - 8);
                cout << "3) Fast " << endl;

                cursor_to_pos(23, get_window_cols() / 2 - 11);
                change_color_rgb(255, 99, 3);
                cout << "Choose Speed : ";
                cin >> number_speed;

                if (number_speed == 1)
                {
                    defult = delay_slow;
                }

                if (number_speed == 2)
                {
                    defult = delay_medium;
                }

                if (number_speed == 3)
                {
                    defult = delay_fast;
                }
            }

            if (number_escape == 3)
            {
                main();
            }

            if (number_escape == 4)
            {
                quit();
            }
        }

        cursor_to_pos(get_window_rows(), get_window_cols());
        cout << "";
        delay(defult);
    }
}

// ---------------------------------------------------------------------------

int Len(int **arr)
{
    int x = 0;
    while (arr[x][0] != 40000)
    {
        x++;
    }
    return x;
}

// ---------------------------------------------------------------------------

void Interaction()
{
    clear_screen();
    if (score_1 > score_2)
    {
        cursor_to_pos(5, (get_window_cols() / 2) - 15);
        change_color_rgb(217, 255, 3);
        cout << "THE WINNER IS : ";
        change_color_rgb(3, 255, 255);
        cout << arr_u[num_user].name << " ";
        change_color_rgb(217, 255, 3);
        cout << "WITH ";
        change_color_rgb(255, 3, 188);
        cout << score_1;
        change_color_rgb(217, 255, 3);
        if (score_1 == 1)
            cout << " SCORE";
        if (score_1 != 1)
            cout << " SCORES";
    }

    if (score_2 > score_1)
    {
        cursor_to_pos(5, (get_window_cols() / 2) - 15);
        change_color_rgb(217, 255, 3);
        cout << "THE WINNER IS : ";
        change_color_rgb(3, 255, 255);
        cout << arr_u[num_user + 1].name << " ";
        change_color_rgb(217, 255, 3);
        cout << "WITH ";
        change_color_rgb(255, 3, 188);
        cout << score_2;
        change_color_rgb(217, 255, 3);
        if (score_2 == 1)
            cout << " SCORE";
        if (score_2 != 1)
            cout << " SCORES";
    }

    if (score_1 == score_2)
    {
        cursor_to_pos(5, (get_window_cols() / 2) - 12);
        change_color_rgb(217, 255, 3);
        cout << "THIS GAME HAD NO ";
        change_color_rgb(255, 3, 3);
        cout << "WINNER";
    }

    cursor_to_pos(9, get_window_cols() / 2 - 8);
    change_color_rgb(226, 3, 255);
    cout << "1) Main Menu" << endl;

    cursor_to_pos(14, get_window_cols() / 2 - 8);
    cout << "2) Play Again" << endl;

    cursor_to_pos(19, get_window_cols() / 2 - 8);
    cout << "3) Exit" << endl;

    cursor_to_pos(23, get_window_cols() / 2 - 11);
    change_color_rgb(255, 99, 3);
    cout << "Choose What To Happen : ";

    fflush(stdin);

    cin >> number_interaction;

    if (number_interaction == 1)
    {
        main();
    }

    if (number_interaction == 2)
    {
        clear_screen();
        Play();
    }

    if (number_interaction == 3)
    {
        quit();
    }
}

// ---------------------------------------------------------------------------

void Speed()
{

    cursor_to_pos(9, get_window_cols() / 2 - 8);
    change_color_rgb(226, 3, 255);
    cout << "1) Slow " << endl;

    cursor_to_pos(14, get_window_cols() / 2 - 8);
    cout << "2) Medium " << endl;

    cursor_to_pos(19, get_window_cols() / 2 - 8);
    cout << "3) Fast " << endl;

    cursor_to_pos(23, get_window_cols() / 2 - 10);
    change_color_rgb(255, 99, 3);
    cout << "Choose Speed : ";
    cin >> number_speed;

    if (number_speed == 1)
    {
        defult = delay_slow;
    }

    if (number_speed == 2)
    {
        defult = delay_medium;
    }

    if (number_speed == 3)
    {
        defult = delay_fast;
    }

    number_menu = 0;
    main();
}

// ---------------------------------------------------------------------------

void Table()
{

    if (num_user != -2)
    {
        Struct_sorter(arr_u);
    }

    while (true)
    {

        clear_screen();
        if (num_user == -2)
        {
            while (true)
            {
                clear_screen();
                cursor_to_pos(get_window_rows() / 2 - 5, get_window_cols() / 2 - 7);
                change_color_rgb(250, 2, 27);
                cout << "NO PLAYER FOUND !";

                cursor_to_pos(get_window_rows() / 2, get_window_cols() / 2 - 15);
                change_color_rgb(136, 232, 135);
                cout << "Please Press TAB To Get Back To Menu";

                if (GetAsyncKeyState(VK_TAB))
                    main();
                delay(300);
            }
        }
        row_table = 0;

        for (int i = 0; i < count_num * 2; i++)
        {

            counter_table = 0;
            if (i == 0)
            {
                cursor_to_pos(get_window_rows() / 2 - 7, get_window_cols() / 2 - 6);
                change_color_rgb(246, 255, 0);
                cout << arr_u[i].name << " <---------> " << arr_u[i].score;
            }

            for (int j = 0; j < i; j++)
            {
                if (i != 0 && strcmp(arr_u[j].name, arr_u[i].name) == 0)
                {
                    continue;
                }
                if (i != 0 && strcmp(arr_u[j].name, arr_u[i].name) != 0)
                {
                    counter_table++;
                }

                if (counter_table == i)
                {
                    row_table += 2;
                    cursor_to_pos(get_window_rows() / 2 - 7 + row_table, get_window_cols() / 2 - 6);
                    change_color_rgb(246, 255, 0);
                    cout << arr_u[i].name << " <---------> " << arr_u[i].score;
                }
            }
        }

        cursor_to_pos(get_window_rows() - 5, get_window_cols() / 2 - 15);
        change_color_rgb(136, 232, 135);
        cout << "Please Press TAB To Get Back To Menu";

        if (GetAsyncKeyState(VK_TAB))
            main();

        delay(33);
    }
}

// ---------------------------------------------------------------------------

void Struct_sorter(struct user *str)
{
    user tmp;
    for (int k = 0; k < count_num * 2; k++)
    {
        if (strcmp(user_1, arr_u[k].name) == 0 && num_user != 0)
        {
            arr_u[k].score += score_1;
            break;
        }
        if (strcmp(user_2, arr_u[k].name) == 0 && num_user != 0)
        {
            arr_u[k].score += score_2;
            break;
        }
    }

    for (int i = 0; i < count_num * 2 - 1; i++)
    {
        for (int j = 0; j < count_num * 2 - 1; j++)
        {
            if (str[j].score < str[j + 1].score)
            {
                tmp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = tmp;
            }
        }
    }

    score_1 = 0;
    score_2 = 0;
}