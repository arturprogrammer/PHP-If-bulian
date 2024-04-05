// Karomatov Samandar
// 06.06.2023

// Ushbu dastur tizimdan ro'yxatdan o'tkazish
// Shaxsiy profilga kirish
// Adminlik huquqiniga ega bo'lish
// Adminlik asosida ma'lumotlarni olish
// kabi vazifalarni bajaradi!


#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct person
{
    string ism;
    string familya;
    string yosh;
    string email;
    string mutaxasislik;
    string fan;
    string login;
    string parol;
};

// Email, login va parolni tekshirish
bool search(string gmail)
{
    return gmail.find("@gmail.com") != string::npos;
}
bool check(string pasword)
{
    bool harflar = false, raqamlar = false;
    for(char a:pasword)
    {
        if(isalpha(a))
        {
            harflar = true;
        }else if(isdigit(a))
        {
            raqamlar = true;
        }
    }
    return (harflar && raqamlar);
}


// Email va login o'rnatuvchi funksiya
void registratsiya()
{
    int tip;
    string kalit;
    tip:
    cout << "\n1- Talaba\n2 - O'qituvchi\n3 - Admin\nKim bo'lib ro'yxatdan o'tmoqchisiz?..."; cin >> tip;


    if(tip > 3 && tip < 1)
    {
        cout << "Shaxs nomi topilmadi!Qayta urining!\n";
        goto tip;
    }

    if(tip == 3)
    {
        do
        {
            cout << "Adminlik huquqiga ega bo'lish  uchun maxsus kalit so'zni kiriting!(Bu kalit so'z dasturchi tomonidan maxsus kiritilgan!)\n";
            cout << "Kalit: "; cin.ignore();
            getline(cin, kalit);/// Maxsus kiritilgan kalit so'z
        }while(kalit != "data_admin");
        cout << "Kalit so'z kiritildi!Adminlik huquqini olishingiz mumkin!\n";
    }

    cout << "Eslatma!\n0 ni kiritsh bilan dasturdan chiqish mumkin!\n";
    person addPerson;
    cout << "Ma'lumotlarni to'ldiring!\n";
    cout << "\nIsmingiz: "; cin.ignore(); getline(cin, addPerson.ism);
    cout << "Familyangiz: "; getline(cin, addPerson.familya);
    cout << "Yoshingiz: "; getline(cin, addPerson.yosh);
    switch(tip)
    {
        case 1: cout << "Mutaxasislik: "; getline(cin, addPerson.mutaxasislik); break;
        case 2: cout << "Mutaxasislik fani: "; getline(cin, addPerson.fan); break;

    }
    if(addPerson.ism == "0"  ||  addPerson.familya == "0" ||  addPerson.yosh == "0")
    {
        exit(0);
    }


    do{
        cout << "Elektron pochta manzilizgiz:\t"; cin >> addPerson.email;
        if(!search(addPerson.email))
        {
            cout << "E.pochta manzilni kiritilishida xatolik!(Namuna: manzil.@gmail.com)\nQaytadan urib ko'ring!\n";
        }
    }while(!search(addPerson.email));
    sikl:
    do{
        cout << "\nIltimos, kuchliroq login parol o'rnatishga harakat qiling!\n";
        cout << "Buning uchun: harflar (A-Z, a-z), raqamlar (0-9) va belgilar (!, @, ... , &) kombinatsiyasidan foydalaning!\n";
        cout << "Login parol:\t"; cin >> addPerson.login;
    }while(!check(addPerson.login));
        // Loginning mavjuligini tekshiruvchi


    string line, login;
    ifstream chek("data.txt", ios::app);
    while(getline(chek, line))
    {
        login = line.substr(line.find(".")+1, line.find(",") - line.find(".") - 1 );
        if(login == addPerson.login){
            cout << "\nKiritilgan login egasi avvaldan mavjud!\nBoshqa login paroldan foydalanish zarur!\n";
            // Qaytish uchun sikl nomli goto dan foydalanish
            goto sikl;
            }
        }
    chek.close();


    cout << "Parol(ixtiyoriy): "; cin.ignore(); getline(cin, addPerson.parol);

    // Malumotlarni yozib borish uchun fayl ochish
    ofstream data("data.txt", ios::app);
    switch(tip)
    {
        case 1: data << "S."; break;
        case 2: data << "T."; break;
        case 3: data << "A."; break;
    }
    data << addPerson.login << "," << addPerson.ism << "|";
    data << addPerson.familya << "*"  << addPerson.yosh << "?";
    switch(tip)
    {
        case 1: data << addPerson.mutaxasislik << "?"; break;
        case 2: data << addPerson.fan << "?"; break;
    }
    data << addPerson.email << "!" << addPerson.parol << "\n";
    data.close();
    cout << "Ro'yxatdan o'tish muvaffaqqiyatli bajarildi!\n";
}

void login()
{
    string out_login, out_parol, satr;
    qayt:
    cout << "\n1 - Talaba\n2 - O'qituvchi\n3 - Admin\nShaxs: ";
    int tip;    cin >> tip;
    if(tip < 4 && tip > 0)
    {
        returnn:
        cout << "\nShaxsni tasdiqlash!(0 - Chiqish)\nLogin: ";
        cin >> out_login;
        if(out_login == "0")
        {
            exit(0);
        }
        cout << "Parol: "; cin >> out_parol;
        if(out_parol == "0")
        {
            exit(0);
        }
    ifstream read("data.txt", ios::app);
    if(read.is_open())
    {
        int i=0;
        while(getline(read, satr))
        {
            string login = satr.substr(satr.find(".")+1, satr.find(",") - satr.find(".") - 1);
            string ism = satr.substr(satr.find(",") + 1, satr.find("|") - satr.find(",") - 1);
            string familya = satr.substr(satr.find("|")+ 1, satr.rfind("*") - 1 - satr.find("|"));
            string mutaxasislik = satr.substr(satr.find("?")+1, satr.rfind("?") - satr.find("?") - 1);
            string fan = satr.substr(satr.find("?")+1, satr.rfind("?") - satr.find("?") - 1);
            string yosh = satr.substr(satr.rfind("*") + 1, satr.find("?") - satr.rfind("*") - 1);
            string email = satr.substr(satr.rfind("?")+1, satr.rfind("!") - satr.rfind("?")-1);
            string parol = satr.substr(satr.rfind("!")+1, satr.size() - satr.rfind("!")-1);

            if((login == out_login && parol == out_parol && tip == 1 && satr.substr(0,1) == "S") ||  (login == out_login && parol == out_parol && tip == 2 && satr.substr(0,1) == "T") || (login == out_login && parol == out_parol && tip == 3 && satr.substr(0,1) == "A"))
            {
                ///  Foydalanuvchining ma'lummotlarini chiqarish

                switch(tip)
                {
                    case 1: cout << "\n\tTalaba"; break;
                    case 2: cout << "\n\tO'qituvchi"; break;
                    case 3: cout << "\n\tAdmin"; break;
                }
                cout << "\nIsm: " << ism;
                cout << "\nFamilya: " << familya;
                cout << "\nYosh: " << yosh;
                if(tip == 1 && satr.substr(0,1) == "S")
                {
                    cout << "\nMutaxasislik: " << mutaxasislik;
               }
               if(tip == 2 && satr.substr(0,1) == "T")
               {
                 cout << "\nMutaxasislik fani: " << fan;
                 }
                cout << "\nE-mail: " << email;
                cout << "\n";

                if(tip == 3)
                {
                bajar:
                cout << "\nMa'lumotlarni olishni istaysizmi?\n1 - talabalar ma'lumotlari\n2 - o'qituvchilar ma'lumotlari\n3 - barcha shaxslarning ma'lumotlari\n0 - chiqish\n";
                int data;
                cout << "..."; cin >> data;
                if(data>3 || data < 0 )
                {
                    cout << "\nTanlovingiz xato!\n";
                    goto bajar;
                }

                ifstream open("data.txt", ios::app);
                while(getline(open, satr))
                {
                    string login = satr.substr(satr.find(".")+1, satr.find(",") - satr.find(".") - 1);
                    string ism = satr.substr(satr.find(",") + 1, satr.find("|") - satr.find(",") - 1);
                    string familya = satr.substr(satr.find("|")+ 1, satr.rfind("*") - 1 - satr.find("|"));
                    string mutaxasislik = satr.substr(satr.find("?")+1, satr.rfind("?") - satr.find("?") - 1);
                    string fan = satr.substr(satr.find("?")+1, satr.rfind("?") - satr.find("?") - 1);
                    string yosh = satr.substr(satr.rfind("*") + 1, satr.find("?") - satr.rfind("*") - 1);
                    string email = satr.substr(satr.rfind("?")+1, satr.rfind("!") - satr.rfind("?")-1);
                    string parol = satr.substr(satr.rfind("!")+1, satr.size() - satr.rfind("!")-1);
                    switch(data)
                    {
                        case 1:
                            if(satr.substr(0,1) == "S")

{
                            cout << "\nIsm: " << ism;
                            cout << "\nFamilya: " << familya;
                            cout << "\nYosh: " << yosh;
                            cout << "\nMutaxasislik: " << mutaxasislik;
                            cout << "\nE-mail: " << email;
                            cout << "\n";
                        }
                        break;
                        case 2:
                            if(satr.substr(0,1) == "T")
                        {
                            cout << "\nIsm: " << ism;
                            cout << "\nFamilya: " << familya;
                            cout << "\nYosh: " << yosh;
                            cout << "\nMutaxasislik fani: " << mutaxasislik;
                            cout << "\nE-mail: " << email;
                            cout << "\n";
                        }
                        break;
                        case 3:

                            if(satr.substr(0,1) == "S")
                        {
                            cout << "\n\tTalaba";
                            cout << "\nIsm: " << ism;
                            cout << "\nFamilya: " << familya;
                            cout << "\nYosh: " << yosh;
                            cout << "\nMutaxasislik: " << mutaxasislik;
                            cout << "\nE-mail: " << email;
                            cout << "\n";
                        }

                            if(satr.substr(0,1) == "T")
                        {
                            cout << "\n\tO'qituvchi";
                            cout << "\nIsm: " << ism;
                            cout << "\nFamilya: " << familya;
                            cout << "\nYosh: " << yosh;
                            cout << "\nMutaxasislik fani: " << mutaxasislik;
                            cout << "\nE-mail: " << email;
                            cout << "\n";
                        }
                        break;

                        }
                    }
                }
            i++;
            }
        }


        if(i == 0)
        {
            cout << "\nShaxsingiz aniqlanmadi!\n\n";
            goto returnn;
        }
    }
        else{
            cout << "\nMa'lumotlar mavjud emas!\n";
        }
        read.close();

    }
    else
    {
        goto qayt;
    }


}


int main()
{
    int tanlov;
    do {
        cout << "\n1 - Ro'yxatdan o'tish\n2 - Kirish\n0 - Chiqish\n";
        cout << "Tanlovingizni kiriting: "; cin >> tanlov;
        switch(tanlov)
        {
            case 1:
                registratsiya();
                do {
                    cout << "\n1 - Davom etish\n0 - Chiqish\n...";
                    cin >> tanlov;
                } while (tanlov != 0 && tanlov != 1);
                break;
            case 2:
                login();
                do {
                    cout << "\n1 - Davom etish\n0 - Chiqish\n...";
                    cin >> tanlov;
                } while (tanlov != 0 && tanlov != 1);
                break;
            case 0:
                exit(0);
                break;
            default:
                cout << "Tanlov noto'g'ri kritildi!\nQayta kiriting!\n";
                break;
        }
    } while (tanlov != 0);

    return 0;
}