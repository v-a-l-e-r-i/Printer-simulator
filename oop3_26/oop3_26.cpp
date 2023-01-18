#include<iostream>
#include <windows.h>
#include <ctime>

using namespace std;

const int MAXPAPER = 100;
const int MAXINK = 50;
const float PROBERROR = 0.05;
int q = 1;
int main();

class printer
{
    bool power;
    string state;
    float ink;
    int paper;
    
public:
    int operator+=(int sheet);
    int operator-=(int sheet);
    float operator*=(float n_ink);
    bool operator=(bool p);

    void set() 
    {
        power = false;
        set_state("Вимкнений");
        ink = 0;
        paper = 0;
    }

    void set_state(string s)
    {
        state = s;
    }

    /*void turn_on()
    {
        if (!power) 
        {
            power = true;
            set_state("Готовий");
        }
    }

    void turn_off()
    {
        if (power) 
        {
            power = false;
            set_state("Вимкнений");
        }
    }*/

    /*int load_paper(int sheets)
    {
        
        if (sheets <= 0)
        {
            cout << "Будь ласка введіть кількість листків" << endl;
            return 0;
        }

        int n_p = paper + sheets;

        if (n_p > MAXPAPER)
        {
            n_p = MAXPAPER;
            cout << "Забагато бумаги. Повертаємо " << sheets - MAXPAPER << endl;
            //return MAXPAPER - sheets;
        }
        paper = n_p;
        return paper;
    }*/

    /*int unload_paper(int sheets)
    {
        if (sheets <= 0)
        {
            cout << "Будь ласка введіть кількість листків" << endl;
            return 0;
        }

        int p = paper - sheets;

        if (p < 0)
        {
            p = 0;
            //return p;
        }
        paper = p;
        return paper;
    }*/

    /*float load_ink(float n_ink)
    {
        if (!power)
        {
            if (n_ink < 0) 
            {
                cout << "Будь ласка введіть кількість мл чорнила" << endl;
                return 0;
            }
            float i = ink + n_ink;
            if (i > MAXINK)
            {
                i = MAXINK;
                cout << "Забагато чорнила. Повертаємо " << n_ink - MAXINK << endl;;
                //return MAXINK - n_ink;
            }
            ink = i;
            return ink;
        }
        else
        {
            cout << "Будь ласка вимкніть принтер" << endl;
            return 0;
        }
    }*/

    int print(int sheets, float k)
    {
        cout << "Кількість чорнил: " << ink << endl;
        cout << "Кількість паперу: " << paper << endl;

        srand(static_cast<unsigned int>(time(0)));
        int err = rand() % 100;
        int filled_paper, pos_sheets = 0;

        if ((!power) and (state != "Готовий"))
        {
            cout << "Будь ласка перевірте готовність принтеру!" << endl;
            return 0;
        }
        if ((sheets < 0) or (k < 0) or (k > 100))
        {
            cout << "Не коректно введені дані!" << endl;
            return 0;
        }
        if (err < PROBERROR * 100)
            filled_paper = rand() % sheets;
        else
            filled_paper = sheets;

        float p_s = k * 0.02;

        if (p_s > ink)
        {
            set_state("Відсутні чорнила");
            cout << "Не вистачає чорнил!" << endl;
        }
        else if (paper < filled_paper)
        {
            set_state("Відсутній папір");
            cout << "Не вистачає паперу!" << endl;
        }
        else
        {
            pos_sheets = filled_paper;
            set_state("Готовий");
            cout << "Надруковано: " << pos_sheets << " сторінок" << endl;
        }

        if (state == "Відсутні чорнила")
            ink = 0;
        else
        {
            ink -= p_s * pos_sheets;
        }

        if (state == "Відсутній папір")
            paper = 0;
        else
        {
            paper -= pos_sheets;
        }

        if (filled_paper < sheets)
        {
            set_state("Аварія");
            cout << "Трапилась аварія" << endl;
            return 0;
        }
        return pos_sheets;
    }

    string get_state()
    {
        return state;
    }

    float get_ink()
    {
        return ink;
    }

    int get_paper()
    {
        return paper;
    }
};

int printer::operator+=(int sheets)
{
    if (sheets <= 0)
    {
        cout << "Будь ласка введіть кількість листків" << endl;
        return 0;
    }

    int n_p = paper + sheets;

    if (n_p > MAXPAPER)
    {
        n_p = MAXPAPER;
        cout << "Забагато бумаги. Повертаємо " << sheets - MAXPAPER << endl;
        //return MAXPAPER - sheets;
    }
    paper = n_p;
    return paper;
}
int printer::operator-=(int sheets)
{
    if (sheets <= 0)
    {
        cout << "Будь ласка введіть кількість листків" << endl;
        return 0;
    }

    int p = paper - sheets;

    if (p < 0)
    {
        p = 0;
        //return p;
    }
    paper = p;
    return paper;
}

float printer::operator*=(float n_ink)
{
    if (!power)
    {
        if (n_ink < 0)
        {
            cout << "Будь ласка введіть кількість мл чорнила" << endl;
            return 0;
        }
        float i = ink + n_ink;
        if (i > MAXINK)
        {
            i = MAXINK;
            cout << "Забагато чорнила. Повертаємо " << n_ink - MAXINK << endl;;
            //return MAXINK - n_ink;
        }
        ink = i;
        return ink;
    }
    else
    {
        cout << "Будь ласка вимкніть принтер" << endl;
        return 0;
    }
}

bool printer::operator=(bool p)
{
    if (p)
    {
        power = true;
        set_state("Готовий");
    }
    else
    {
        power = false;
        set_state("Вимкнений");
    }

    return p;
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char n;
    printer ob1;
    if (q == 1)
    {
        ob1.set();
        q++;
    }

    while (true)
    {
        cout << "***********************Принтер***********************" << endl;
        cout << "************** М Е Н Ю **************" << endl;
        cout << "1: Ввімкнути принтер" << endl;
        cout << "2: Вимкнути принтер" << endl;
        cout << "3: Завантажити папір" << endl;
        cout << "4: Вивантажити папір" << endl;
        cout << "5: Заправити чорнила" << endl;
        cout << "6: Друкувати" << endl;
        cout << "7: Кількість чорнил" << endl;
        cout << "8: Кількість паперу" << endl;
        cout << "0: Вихід" << endl;
        cout << "*************************************" << endl;
        cout << "*****************************************************" << endl;
        cout << "Оберіть дію: ";
        cin >> n;
        switch (n)
        {
        case '1': ob1 = true; Sleep(500); system("cls"); break;
        case '2': ob1 = false; Sleep(500); system("cls"); break;
        case '3':
        {
            int i;
            cout << "Введіть кількість паперу" << endl;
            cin >> i;
            ob1 += i;
            break;
        }
        case '4':
        {
            int i;
            cout << "Введіть кількість паперу" << endl;
            cin >> i;
            ob1 -= i;
            break;
        }
        case '5':
        {
            float i;
            cout << "Введіть кількість мл чорнила" << endl;
            cin >> i;
            ob1 *= i;
            break;
        }
        case '6':
        {
            int i;
            float kf;
            cout << "Введіть кількість паперу" << endl;
            cin >> i;
            cout << "Введіть коефіцієнт середнього заповнення аркуша, %" << endl;
            cin >> kf;
            kf /= 100;
            ob1.print(i, kf);
            break;
        }
        case '0':
            exit(0);
        case '7':
            cout << ob1.get_ink() << endl; /*Sleep(500); system("cls");*/ break;
        case '8':
            cout << ob1.get_paper() << endl; /*Sleep(500); system("cls");*/ break;
        default:
            cout << "Не правильно введені дані, спробуйте знову" << endl;
            Sleep(1000);
            system("cls");
            break;
        }
    }
    

    system("PAUSE");
}