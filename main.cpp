
//C++ program that controls internet package and show information about user usage
// The units will in GB and day
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iomanip>
using namespace std;

// The user class
class User {
    //Declaring object with username value to access his file
public:
    User(string un) {
        this->user_name = un;
        this->password =get_password();
    }
private:
    //Member data
    string user_name;
    string password;
    string file_name;
    float ave_usage_per_day=0;
    float price_of_gb=1.25;
    float usage=0;
    int money_bocket = 0;
    int sizes = 0;
    int package =0;
    int remaining = 0; //remaining size of internet usage
    int current_day = 1;
    int remaining_days = 29; //the days left for expiration of the package
    int expected_days = 0; // the num of days program will expect the user end his internet in
    int total_usage = 0; //equals sum of usage_used's elemnts + remaining

    int num_of_lists = 6;
    vector<int> num_of_days; // the number of days that the user finished his package in
    vector<int> usage_size; // the size of the internet package
    vector<double> usage_per_day1; //of used
    vector<double> usage_per_day2; //of expected
    vector<int> usage_used; //when "is_expired" is ture
    vector<bool> is_expired; //when num_of_day >=30



public:
    move_days(int days){
         srand(time(0));
  float alpha = rand() % 66 + 60;
       for (int i = 0; i < sizes; i++) {
total_usage += usage_used[i];
}
double ave_usage_per_day = total_usage / (30 * sizes);

// Calculate internet usage for the given number of days
double used = days * ave_usage_per_day*(alpha/100);
usage += used;
bool p=false;
// Update current day, remaining days, and remaining internet usage
if (current_day + days >= 30) {
    p=true;
    current_day = 30;
    remaining_days = 0;
}
else {
    current_day += days;
    remaining_days -= days;
}
if (used >= remaining||p) {
    remaining = 0;
    int uu=usage;
    usage=0;
    update_history_usage(package, uu, current_day);
}
else {
    remaining -= used;

}

// Write updated data to file
write();
    }

    void update_history_usage( int dataa,int usaage, int days) {
                sizes++;
                usage_size.push_back(dataa);
                usage_used.push_back(usaage);
                num_of_days.push_back(days);
                current_day=1;
                remaining_days=30;
                write();

                cout << "\n\n\tMonth Ended!";
                cin.ignore(); cin.get();


    }

    //get password from the user
     string get_password(){
       ifstream f("passwords.txt",ios::in);
       string line,n,p;
       while(getline(f,line)){
        stringstream ss(line);
        ss>>n>>p;
        if(n==user_name){
            return p;
        }
       }
       f.close();
   }

    //reading the data of the user from his file
    void read() {
        //opening file with username name
        string file = "Users/";
        file += this->user_name;
        file += ".bin";
        ifstream in(file, ios::binary);

        //reading variables
        in.read((char*)&remaining, sizeof(int));
        in.read((char*)&current_day, sizeof(int));
        in.read((char*)&remaining_days, sizeof(int));
        in.read((char*)&expected_days, sizeof(int));
        in.read((char*)&sizes, sizeof(int));

        //resizing vectors to fit the input data
        num_of_days.resize(sizes);
        usage_size.resize(sizes);
        usage_per_day1.resize(sizes);
        usage_per_day2.resize(sizes);
        usage_used.resize(sizes);
        is_expired.resize(sizes);

        //reading vectors' values
        in.read((char*)num_of_days.data(), sizes * sizeof(int));
        in.read((char*)usage_size.data(), sizes * sizeof(int));
        in.read((char*)usage_per_day1.data(), sizes * sizeof(double));
        in.read((char*)usage_per_day2.data(), sizes * sizeof(double));
        in.read((char*)usage_used.data(), sizes * sizeof(int));
        //money bocket
        in.read((char*)&money_bocket, sizeof(int));
        in.read((char*)&usage,sizeof(float));
        in.read((char*)&package,sizeof(int));
        in.close();
    }
    //Writing the data of the user into his file
    void write() {
        //opening file with username name
        string file = "Users/";
        file += this->user_name;
        file += ".bin";
        ofstream out(file, ios::binary);

        //writing variables
        out.write((char*)&remaining, sizeof(int));
        out.write((char*)&current_day, sizeof(int));
        out.write((char*)&remaining_days, sizeof(int));
        out.write((char*)&expected_days, sizeof(int));
        out.write((char*)&sizes, sizeof(int));

        //writing vectors' values
        out.write((char*)num_of_days.data(), sizes * sizeof(int));
        out.write((char*)usage_size.data(), sizes * sizeof(int));
        out.write((char*)usage_per_day1.data(), sizes * sizeof(double));
        out.write((char*)usage_per_day2.data(), sizes * sizeof(double));
        out.write((char*)usage_used.data(), sizes * sizeof(int));
        //money bocket
        out.write((char*)&money_bocket, sizeof(int));
        out.write((char*)&usage,sizeof(float));
        out.write((char*)&package,sizeof(int));
        out.close();
    }
    int get_size_of_h() { return sizes; }//use it to print it when show hist. of selected month
    void set_username(string u) { user_name=u; }
    void set_password(string p) { password=p; }
    string get_username() { return user_name; }
    void show_usage() { //user usage and experetion data
        system("cls");
        expect_days();
        cout << "\n\n\t\tThe remaining of your data : " << remaining;
        cout << "\n\n\t\tThe current day is : " << current_day;
        cout << "\n\n\t\tThe days left for expiration of data : " << remaining_days;
        cout << "\n\n\t\tThe days expected to finish is : " << expected_days;
        cout << "\n\n\nPress any key to return \n";
        cin.ignore(); cin.get();
    }
    //expect the days of the current month
    void expect_days() {

        int sum_usage_used = 0;
        int sum_num_of_days = 0;
        for (int i = 0; i < sizes; i++) {
            sum_usage_used += usage_used[i];
            sum_num_of_days += num_of_days[i];
        }

        double mean_usage_used = static_cast<double>(sum_usage_used) / usage_used.size();
        double mean_num_of_days = static_cast<double>(sum_num_of_days) / num_of_days.size();


        double sum_sq_diff_usage_used = 0;
        double sum_prod_diff = 0;
        for (int i = 0; i < sizes; i++) {
            double diff_usage_used = usage_used[i] - mean_usage_used;
            double diff_num_of_days = num_of_days[i] - mean_num_of_days;
            sum_sq_diff_usage_used += diff_usage_used * diff_usage_used;
            sum_prod_diff += diff_usage_used * diff_num_of_days;
        }


        double slope = sum_prod_diff / sum_sq_diff_usage_used;
        double intercept = mean_num_of_days - slope * mean_usage_used;
        if (remaining == 0)expected_days = 0;
        else
            expected_days = (int)(intercept + slope * remaining);


    }
    int expect_days(int); //expect the days of any given month from 1 to sizes -which is the number of months-.
    void show_history_usage() {
    system("cls");
    cout << setw(5) << "Month" << setw(15) << "Size (GB)" << setw(15) << "Used (GB)" << setw(15) << "Days" << endl;
    for (int i = 0; i < sizes; i++) {
        cout << setw(5) << i + 1 << setw(15) << usage_size[i] << setw(15) << usage_used[i] << setw(15) << num_of_days[i] << endl;
    }
    cout << "\n\nPress any key to return" << endl;
    cin.ignore(); cin.get();
}

    void show_history_usage(int); //shows the usage for selected month
    void delete_history_usage() {     //delete usage for selected month
        system("cls"); int k, c;
        cout << "\n\tEnter number of number of month to delete : "; cin >> k; k--;
        do {
            system("cls");
            cout << "\n\n\n\tAre you sure ? : ";
            cout << "\n\t\t1-Yes";
            cout << "\n\t\t2-return\n";
            cin >> c;
            if (c == 1) {
                usage_size.erase(usage_size.begin() + k);
                usage_used.erase(usage_used.begin() + k);
                num_of_days.erase(num_of_days.begin() + k);
                usage_size.shrink_to_fit();
                usage_used.shrink_to_fit();
                num_of_days.shrink_to_fit();
                sizes--;
                write();
                cout << "\n\n\tDeleted!";
            }
        } while (c != 1 && c != 2);
        cout << "\n\n\npress any key to return\n";
        cin.ignore(); cin.get();

    } //delete usage for selected month
    void update_history_usage() {    //add usage history usage list after the month ends
        system("cls"); int dataa, usage, days, c;
        cout << "\n\t\t\tadd history for this month \n\n";
        cout << "\n\tEnter the type of data subscribed : "; cin >> dataa;
        cout << "\n\tEnter your usage in this month : "; cin >> usage;
        cout << "\n\tEnter days in use of that data : "; cin >> days;
        do {
            system("cls");
            cout << "\n\n\n\tAre you sure ? : ";
            cout << "\n\t\t1-Yes";
            cout << "\n\t\t2-return\n";
            cin >> c;
            if (c == 1) {
                sizes++;
                usage_size.push_back(dataa);
                usage_used.push_back(usage);
                num_of_days.push_back(days);
                write();
                cout << "\n\n\tSaved!";
            }
        } while (c != 1 && c != 2);
        cout << "\n\n\npress any key to return\n";
        cin.ignore(); cin.get();
    }
    void Internet_package() {
     int c;
     do{
            system("cls");
        cout<< "\n\n\t\tSize\tCost\n";
        cout<< "\n\t1\t100\t95\n";
        cout<< "\n\t2\t140\t120\n";
        cout<< "\n\t3\t200\t170\n";
        cout<< "\n\t4\t300\t250\n";
        cout<< "\n\t5-Custom package\n";
        cout<< "\n\t6-Return\n\t";
        cin>>c;
        bool b=false;
        switch(c){
        case 1:
            if(money_bocket>=95){
                b=true;
                money_bocket-=95; remaining=100; package=100;
            }
            break;
         case 2:
            if(money_bocket>=120){
                  b=true;
                money_bocket-=120; remaining=140; package=140;

            }
            break;
         case 3:
            if(money_bocket>=170){
                  b=true;
                money_bocket-=170; remaining=200; package=200;

            }
            break;
         case 4:
            if(money_bocket>=250){
                  b=true;
                money_bocket-=250; remaining=300; package=300;

            }
            break;
         case 5:
             b=true;
            custom();
            break;
         case 6:
            break;
        }
        if(b){
            int s;
            do{
            system("cls");
        cout<< "\n\tAre you sure?\n";
        cout<< "\n\t1-Yes\n";
        cout<< "\n\t2-Return\n\t";
        cin>>s;
        switch(s){
        case 1:
            system("cls");
             cout<< "\n\n\n\tDone!";
            write();
            cin.ignore(); cin.get();
            break;
        case 2:
        break;
        }
     }while(s!=1&&s!=2);
    }
        else if(c>=1&&c<=4){
                    do{
            system("cls");
            cout<< "\n\n\tYou don't have enough money!!\n";
           cout<< "\n\t1-Try again\n";
           cout<< "\n\t2-Return\n\t";
           cin>>c;
           switch(c){
           case 1:
            Internet_package();
            break;
           case 2:
            break;
           }
        }while(c!=1&&c!=2);
        }

     }while(c!=1&&c!=2&&c!=3&&c!=4&&c!=5&&c!=6);

    }
    void custom(){
        system("cls");
        float s,cost; int c;
        cout<< "\n\n\tChose the size :"; cin>>s;
        cost=s*price_of_gb;
        cout<< "\n\tCost : "<<cost<<endl;
        cin.ignore();cin.get();

        if(money_bocket>=cost){
            do{
        cout<< "\n\tAre you sure?\n";
        cout<< "\n\t1-Yes\n";
        cout<< "\n\t2-Return\n\t";
        cin>>c;
        switch(c){
        case 1:
            money_bocket-=cost; package=s; remaining=s;
            system("cls");
             cout<< "\n\n\n\tDone!";
                write();
            cin.ignore(); cin.get();
            break;
        case 2:
            break;
        }
        }while(c!=2&&c!=1);
        }
        else{
        do{
            system("cls");
            cout<< "\n\n\tYou don't have enough money!!\n";
           cout<< "\n\t1-Try again\n";
           cout<< "\n\t2-Return\n\t";
           cin>>c;
           switch(c){
           case 1:
            custom();
            break;
           case 2:
            break;
           }
        }while(c!=1&&c!=2);
    }
}

    bool is_first_time() {
        string file = "Users/";
        file += this->user_name;
        file += ".bin";
        ifstream f(file);
        if (f.good())return false;
        else return true;
    }
    void read_if_new() {
        string file = "Users/";
        file += this->user_name;
        file += ".bin";
        ofstream out(file, ios::binary);
        sizes = 0;
        num_of_days.resize(sizes);
        usage_size.resize(sizes);
        usage_per_day1.resize(sizes);
        usage_per_day2.resize(sizes);
        usage_used.resize(sizes);
        is_expired.resize(sizes);

        out.write((char*)&remaining, sizeof(int));
        out.write((char*)&current_day, sizeof(int));
        out.write((char*)&remaining_days, sizeof(int));
        out.write((char*)&expected_days, sizeof(int));
        out.write((char*)&sizes, sizeof(int));

        //writing vectors' values
        out.write((char*)num_of_days.data(), sizes * sizeof(int));
        out.write((char*)usage_size.data(), sizes * sizeof(int));
        out.write((char*)usage_per_day1.data(), sizes * sizeof(double));
        out.write((char*)usage_per_day2.data(), sizes * sizeof(double));
        out.write((char*)usage_used.data(), sizes * sizeof(int));
        //money bocket
        out.write((char*)&money_bocket, sizeof(int));
        out.write((char*)&usage,sizeof(float));
        out.write((char*)&package,sizeof(int));
        out.close();

    }

    void show_balance() {//info of money
        system("cls");
        cout << "\n\n\t\tyour balance = " << money_bocket;
        cout << "\n\n\n\nPress any key to return\n";
        cin.ignore(); cin.get();
    }
    void recharge_balance() {
        system("cls");
        int k;
        string t;
        do{
        system("cls");
        cout << "\n\n\tEnter the amount to recharge your balance \n\t\t";
        cin >> k;
        }while(k<0);
        cout << "\n\tEnter your password ";
        cin >> t;
        if (t == password) {
            money_bocket += k;
            write();
            cout<<"\n\t\tMoney added successfully\n\n\nPress any key to return ";
            cin.ignore(); cin.get();
        }
        else { cout << "\n\tWrong password\n\n\nPress any key to return ";
               cin.ignore(); cin.get();
        }
    }

    void reset_package(){
        current_day=1;
        remaining_days=30;
        usage=0;
        remaining=0;
        write();
        cout<< "\n\n\tDone!";
        cin.ignore(); cin.get();
    }

};



//declaring functions that controls the menus menu
void login();
void regist();
void mainmenu(string);
void lmenu();
void info(User*);
void manage(User*);
void userName(User*);
void New_password(User*);
void change_u_or_p(User*);
void Move_forward(User*);
//main function
int main()
{
    srand(time(NULL));
    lmenu();
    return 0;
}

//First menu
void lmenu() {
    char c;
    do {
        system("cls");
        cout << "\n\t1-Login\n";
        cout << "\n\t2-Register\n";
        cout << "\n\t3-Exit\n\t\t";
        cin >> c;
        system("cls");
        switch (c) {
        case '1':
            login();
            break;
        case '2':
            regist();
            break;
        case '3':
            exit(0);
            break;
        }
    } while (c != '3');
}

void mainmenu(string p) {

    system("cls");
    User kk(p);
    if (kk.is_first_time()) {
        kk.read_if_new();
    }
    else kk.read();

    char c;
    do {
        cout << "\n\t\t\tWelcome " << kk.get_username() << endl;
        cout << "\n\t1-Move_forward\n";
        cout << "\n\t2-Info\n";
        cout << "\n\t3-Manage\n";
        cout << "\n\t4-logout\n\t\t";
        cin >> c;
        switch (c) {
        case '1':
            Move_forward(&kk);
            break;
        case '2':
            info(&kk);
            break;
        case '3':
            manage(&kk);
            break;
        case '4':
            lmenu();
            break;
        }
    } while (c != '1' && c != '2' && c != '3'&&c!='4');
}

void login() {
    system("cls");
    string un, p;
    cout << "\n\tEnter the username : ";
    cin >> un;
    cout << "\n\tEnter the password : ";
    cin >> p;
    string line;
    bool found = false;
    fstream f("passwords.txt", ios::in);
    while (!f.eof()) {
        string name, pass;
        getline(f, line);
        stringstream ss(line);
        ss >> name >> pass;
        if (pass == p && name == un) {
            found = true;
            mainmenu(un);
            f.close();
            break;
        }
    }
    if (!found) {
        cout << "\n\t Either Username or password is wrong \n";
        f.close();
        cin.ignore();
        cin.get();
        char c;
        do {
            system("cls");
            cout << "\n\t1-try again\n";
            cout << "\n\t2-return\n\t\t";

            cin >> c;
            switch (c) {
            case '1':
                login(); break;
            case '2':
                lmenu();
            }
        } while (c != '1' && c != '2');

    }
}
void regist() {
    system("cls");
    ifstream f1("passwords.txt", ios::in);
    ofstream f2("passwords.txt", ios::app);
    string un, p1, p2;
    cout << "\n\tEnter your username\n\t\t";
    cin >> un;
    cout << "\n\tEnter a new password\n\t\t";
    cin >> p1;
    cout << "\n\tRenter the passwoerd\n\t\t";
    cin >> p2;
    if (p1 == p2) {
        string line, name, pass;
        while (!f1.eof()) {

            getline(f1, line);
            stringstream ss(line);
            ss >> name >> pass;
            if (name == un) {
                cout << "\n\t\tThe user name is already exit chose another or return\n";
                cin.ignore();
                cin.get();
                char c;
                do {
                    system("cls");
                    cout << "\n\t1-try again\n";
                    cout << "\n\t2-return\n\t\t";

                    cin >> c;
                    switch (c) {
                    case '1':
                        regist(); break;
                    case '2':
                        lmenu();
                    }
                } while (c != '1' && c != '2');

            }
        }
        f2 << un << " " << p1 << endl;
    }

    else {
        system("cls");
        cout << "\n\tThe two passwords does not match \n";
        cin.ignore();
        cin.get();
        char c;
        do {
            system("cls");
            cout << "\n\t1-try again\n";
            cout << "\n\t2-return\n\t\t";
            cin >> c;
            switch (c) {
            case '1':
                regist(); break;
            case '2':
                lmenu();
            }
        } while (c != '1' && c != '2');
    }
    f1.close();
    f2.close();
    cout << "\n\t\tYou registered successfully \n";
    cin.ignore();
    cin.get();
    lmenu();
}

void info(User* u) {
    char c;
    do {
        system("cls");
        cout << "\n\t1-Show usage\n";
        cout << "\n\t2-Show history\n";
        cout << "\n\t3-show money bocket balance\n";
        cout << "\n\t4-return\n\t\t";
        cin >> c;
        switch (c) {
        case '1':
            u->show_usage();
            break;
        case '2':
            u->show_history_usage();
            break;
        case'3':
             u->show_balance();
            break;

        case '4':
            mainmenu(u->get_username());
            break;

        }
        c = 'q';
    } while (c != '1' && c != '2' && c != '3' && c != '4');
}
void manage(User* k) {
    char c;
    do {
        system("cls");
        cout << "\n\t1-change or subscribe in data\n";
        cout << "\n\t2-Unsubscribe the package\n";
        cout << "\n\t3-Modify history\n";
        cout << "\n\t4-delete history\n";
        cout << "\n\t5-recharge money pocket balance\n";
        cout << "\n\t6-Change username or password\n";
        cout << "\n\t7-Return\n\t\t";
        cin >> c;
        system("cls");
        switch (c) {
        case '1':k->Internet_package();
            break;
        case'2':
            k->reset_package();
            break;
        system("cls");
            k->Internet_package();
            break;
        case'3':
            k->update_history_usage();

            break;
        case '4':
             k->delete_history_usage();

            break;
        case'5':
            k->recharge_balance();
            break;
        case '6':
           change_u_or_p(k);
            break;
        case'7':mainmenu(k->get_username());
            break;
        }
        c = 'q';
    } while (c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7');
}
void userName(User *k)
{   system("cls");
    vector<string>user_password(3);
    vector<string>user(3);
    vector<string>password1(3);
    ifstream file("passwords.txt");
    ifstream f1("passwords.txt");
    int i=0;
    cout<<"\n\tEnter the new username :";
    string u; cin>>u;
    while(!file.eof())
    {
        getline(file,user_password[i]);
        i++;
        if(i==3)
            break;
    }
    file.close();
    for(i=0;i<3;i++)
    {
    stringstream s(user_password[i]);
        s>>user[i]>>password1[i];
    }
    for(i=0;i<3;i++)
    {
        if(k->get_username()==user[i])
        {
            string line, name, pass;
        while (!f1.eof()) {

            getline(f1, line);
            stringstream ss(line);
            ss >> name >> pass;
            if (name == u) {
                cout << "\n\t\tThe user name is already exit chose another or return\n";
                cin.ignore();
                cin.get();
                char c;
                do {
                    system("cls");
                    cout << "\n\t1-try again\n";
                    cout << "\n\t2-return\n\t\t";

                    cin >> c;
                    switch (c) {
                    case '1':
                        userName(k); break;
                    case '2':
                        manage(k);
                    }
                } while (c != '1' && c != '2');

            }
        }
            k->set_username(u);
            user[i]=u;
            break;
        }
    }
    ofstream outfile("passwords.txt",ios::in);
    for(i=0;i<3;i++)
    {
        outfile<<user[i]<<" "<<password1[i]<<endl;
    }
    outfile.close();
    cout<< "\n\n\tDone!";
    cin.ignore(); cin.get();
}
void New_password(User *k)
{
    vector<string>user_password(3);
    vector<string>user(3);
    vector<string>password1(3);
    ifstream file("passwords.txt");
    int i=0;
    system("cls");
    cout<<"\n\tEnter old password :";
    string p; cin>>p;
    while(!file.eof())
    {
        getline(file,user_password[i]);
        i++;
        if(i==3)
            break;
    }
    file.close();
    for(i=0;i<3;i++)
    {
    stringstream s(user_password[i]);
        s>>user[i]>>password1[i];
    }
    for(i=0;i<3;i++)
    {
        if(password1[i]==p)
        {
            system("cls");
            cout<<"\n\tEnter a new password :";
            string p1,p2;
            cin>>p1;
            cout<<"\n\tEnter the password again :";
            cin>>p2;
            if(p1==p2)
            {
            k->set_password(p1);
            password1[i]=p1;
            break;
            }
            else {system("cls");
                cout<<"\n\tWrong password\n";
                cout<<"\n\tPress any key to return\n";
                cin.ignore();  cin.get();
                i=0;  continue;
            }


        }
    }
    if(i==3)
    {
        system("cls");
        cout<<"\n\tWrong password\n";
        cout<<"\n\tPress any key to move\n";
        cin.ignore();  cin.get();
        system("cls");
        cout<<"\n\t1-try again\n";
        cout<<"\n\t2-return\n";
        char c;
        do{
            cin>>c;
            switch(c){
            case'1':New_password(k);
            manage(k);
            break;
            case'2':manage(k);
            break;
            }
            c='q';
        }while(c!='1'&&c!='2');
    }
    ofstream outfile("passwords.txt",ios::in);
    for(i=0;i<3;i++)
    {
        outfile<<user[i]<<" "<<password1[i]<<endl;
    }
    outfile.close();
    cout<< "\n\n\tDone!";
    cin.ignore(); cin.get();
}

void change_u_or_p(User *k){
    system("cls");
    char c;
    do{
    cout<< "\n\n\t1-Change Passwords\n";
    cout<< "\n\t2-Change Username\n\t";
    cout<< "\n\t3-Return\n\t";
    cin>>c;
    switch(c){
    case '1':
        New_password(k);
        break;
    case '2':
        userName(k);
    case '3':
        manage(k);
    }
    }while(c!='1'&&c!='2');
}

void Move_forward(User* u){
    int d;
    system("cls");
    cout<< "\n\n\tThis is just a simulation of how Internet using work";
    cout<< "\n\tby moving forward in days to show average usage in these days\n ";
    cout<< "\n\t Days : "; cin>>d;
    u->move_days(d);
    u->write();
    mainmenu(u->get_username());
}
