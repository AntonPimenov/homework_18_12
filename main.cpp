#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

class User
{
    string name_;
    string login_;
    string pass_;

    public:

        User(string name, string login, string pass) : name_(name), login_(login), pass_(pass) {};

        friend fstream& operator >>(fstream& isUser, User& obj);
        friend ostream& operator <<(ostream& osUser, User& obj);
};

fstream& operator>>(fstream& isUser, User& obj)
{
    isUser >> obj.name_;
    isUser >> obj.login_;
    isUser >> obj.pass_;
    return isUser;
}

ostream& operator<<(ostream& osUser, User& obj)
{
    osUser << obj.name_;
    osUser << " ";
    osUser << obj.login_;
    osUser << " ";
    osUser << obj.pass_;
    return osUser;
}

class Message
{
    string text_;
    string sender_;
    string receiver_;

    public:
        Message(string text, string sender, string receiver) : text_(text), sender_(sender), receiver_(receiver) {};
        friend fstream& operator>>(fstream& isMessage, Message& mess);
        friend ostream& operator<<(ostream& osMessage, Message& mess);

};

fstream& operator>>(fstream& isMessage, Message& mess)
{
    isMessage >> mess.text_;
    isMessage >> mess.sender_;
    isMessage >> mess.receiver_;
    return isMessage;
}

ostream& operator<<(ostream& osMessage, Message& mess)
{
    osMessage << mess.text_;
    osMessage << "\n";
    osMessage << mess.sender_;
    osMessage << "\n";
    osMessage << mess.receiver_;
    return osMessage;
}

void demo_perms(fs::perms p)
{
    cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
         << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
         << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
         << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
         << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
         << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
         << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
         << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
         << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
         << '\n';
}
int main()
{
    fstream user_file = fstream("user.txt", ios::in | ios::out);
    if(!user_file)
    {
        user_file = fstream("user.txt", ios::in | ios::out | ios::trunc);
    }
    if(user_file)
    {
        User obj("Anton", "Tony", "123");
        //записать данные в файл
        user_file << obj << endl;
        //считать данные - установить указатель на начало файла
        user_file.seekg(0, ios::beg);
        //считаем данные
        user_file >> obj;
        cout << obj<< endl;
    }
    else
    {
        cout << "could not open file user.txt\n";
    }

    fs::permissions("user.txt", fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
    fs::permissions("user.txt", fs::perms::owner_exec, fs::perm_options::remove);
    
    fstream mess_file = fstream("message.txt", ios::in | ios::out);
    if(!mess_file)
    {
        mess_file = fstream("message.txt", ios::in | ios::out | ios::trunc);
    }
    if(mess_file)
    {
        Message mess("Dropbox_объявил_о_сокращении_20%_сотрудников",
        "anton", "vasy");
        mess_file << mess << endl;
        mess_file.seekg(0, ios::beg);
        mess_file >> mess;
        cout << mess << endl;
    }
    else 
    {
        cout << "could not open message.txt" << endl;
    }
    fs::permissions("message.txt", fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);    

}