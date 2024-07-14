#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class User {
public:
    User(std::string name, std::string login, std::string pass) :
    _name(name), _login(login), _pass(pass) {}

    friend std::fstream& operator >>(std::fstream& is, User& obj) {
        is >> obj._name;
        is >> obj._login;
        is >> obj._pass;
        return is;
    }

    friend std::ostream& operator <<(std::ostream& os, const User obj) {
        os << obj._name;
        os << std::endl;
        os << obj._login;
        os << std::endl;
        os << obj._pass;
        os << std::endl;
        return os;
    }
private:
    std::string _name;
    std::string _login;
    std::string _pass;
};

class Message {
public:
    Message(std::string text, std::string sender, std::string receiver) :
    _text(text), _sender(sender), _receiver(receiver) {}

    friend std::fstream& operator >>(std::fstream& is, Message& obj) {
        is >> obj._text;
        is >> obj._sender;
        is >> obj._receiver;
        return is;
    }

    friend std::ostream& operator <<(std::ostream& os, const Message obj) {
        os << obj._text;
        os << std::endl;
        os << obj._sender;
        os << std::endl;
        os << obj._receiver;
        os << std::endl;
        return os;
    }
private:
    std::string _text;
    std::string _sender;
    std::string _receiver;
};

void demo_perms(fs::perms p) {
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
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


int main() {
    std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
    if(!user_file) {
        user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);
    }
    demo_perms(fs::status("users.txt").permissions());
    fs::permissions("users.txt", 
        fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
    if(user_file) {
        User obj("Fedor", "qwerty", "12345");
        user_file << obj << std::endl;
        user_file.seekg(0, std::ios_base::beg);
		user_file >> obj;
		std::cout << obj << std::endl;
    } 
    else {
		std::cout << "Could not open file users.txt !" << '\n';
		return 0;
	}

    std::fstream message_file = std::fstream("message.txt", std::ios::in | std::ios::out);
    if(!message_file) {
        message_file = std::fstream("message.txt", std::ios::in | std::ios::out | std::ios::trunc);
    }
    demo_perms(fs::status("message.txt").permissions());
    fs::permissions("message.txt", 
        fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
    if(message_file) {
        Message obj("Hi, Fedor", "qwerty", "user");
        message_file << obj << std::endl;
        message_file.seekg(0, std::ios_base::beg);
		message_file >> obj;
		std::cout << obj << std::endl;
    } 
    else {
		std::cout << "Could not open file users.txt !" << '\n';
		return 0;
	}
    return 0;
}
