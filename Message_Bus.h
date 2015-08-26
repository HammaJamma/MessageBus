#pragma once
#include <queue>
#include <string>
#include <memory>


///////////////////////////////////////////////
/////// Whenever I add a new message the type name will be declared here
///////////////////////////////////////////////

namespace MB //Message Bus typenames
{
	namespace TYPE
	{
		enum type {DEFAULT, BUTTON, ER, PLAYER};
	}
	namespace BUTTON
	{
		enum type {DEFAULT, PRESSED, RELEASED, GAINED_FOCUS, LOST_FOCUS};
	}
	namespace ER
	{
		enum type { DEFAULT, EMPTY_ARRAY, INVALID_OUTPUT};
	}
	namespace PLAYER
	{
		enum type {DEFAULT, MAX_WAYPOINTS, REACHED_WAYPOINT, WAYPOINT_CREATED, NEW_POSITION};
	}
	/*namespace WARNING
	{
		enum type {DEFAULT};
	}*/
};



///////////////////////////////////////////////////
/////// Base Class for any message sent to the bus
///////////////////////////////////////////////////

class Message
{
protected:
	std::string string_;
	int ID_;
	sf::Vector2f position_;
public:
	MB::TYPE::type type_;
	MB::BUTTON::type button_;
	MB::ER::type error_;
	MB::PLAYER::type player_;

	//the base class default contructor for all messages will initialize all members to default or 0
	Message(){
		type_ = MB::TYPE::DEFAULT;
		button_ = MB::BUTTON::DEFAULT;
		error_ = MB::ER::DEFAULT;
		player_ = MB::PLAYER::DEFAULT;
		string_ = "";
		ID_ = 0;
		position_ = sf::Vector2f(0,0);
	};
	int ID(){ return ID_; }
	sf::Vector2f position(){return position_;}
	std::string string(){ return string_;}
	MB::TYPE::type type(){return type_; }
	MB::BUTTON::type buttonMessage(){return button_;}
	MB::ER::type errorMessage(){return error_;}
	MB::PLAYER::type playerMessage(){return player_;}
};

///////////////////////////////////////////////////
/////// all derived message classes
///////////////////////////////////////////////////

	//the
 class Button_Message : public Message
{	
public:
	Button_Message(int ID, sf::Vector2f position, std::string string, MB::BUTTON::type type){
		ID_ = ID;
		position_ = position;
		string_ = string;
		button_ = type;

		type_ = MB::TYPE::BUTTON;
	}
};

class Error_Message : public Message
{
public:
	Error_Message(int ID, std::string string, MB::ERROR::type type){
		ID_ = ID;
		string_ = string;
		error_ = type;

		type_ = MB::TYPE::ERROR;
	}
};

 class Player_Message : public Message
{	
public:
	Player_Message(int ID, sf::Vector2f position, std::string string, MB::PLAYER::type type){
		ID_ = ID;
		position_ = position;
		string_ = string;
		player_ = type;

		type_ = MB::TYPE::PLAYER;
	}
};

///////////////////////////////////////////////////
/////// the actual message bus class
///////////////////////////////////////////////////

class Message_Bus
{
private:
	static std::queue<Message> Message_Bus::messageQueue_;
public:
	bool pollMessage(Message &message)
	{
		if(messageQueue_.empty() == false)
		{
			message = messageQueue_.front();
			messageQueue_.pop();
			return true;
		}
		else
			return false;
	}

	static void sendMessage(Message message)
	{
		messageQueue_.push(message);
		//std::cout << message.string() << std::endl;
	}
};



