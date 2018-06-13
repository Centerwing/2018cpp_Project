#ifndef _USER_H__
#define _USER_H_

#include<string>

class User
{
public:
	User(User const &) = delete;
	void operator=(User const &) = delete;

	static User* getInstance()
	{
		static User* _instance = new User;
		return _instance;
	}

	bool _team;//true = terran , false = protoss

	void setName(const std::string& name) { this->_name = name; };
	std::string getName() const { return _name; };
private:
	User() {};

	std::string _name;
};

#endif // !_USER_H__

