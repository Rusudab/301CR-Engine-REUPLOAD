#include "InputSub.h"

InputSub::InputSub()
{

}

InputSub::~InputSub()
{

}

//This is where I check for all of the inputs (to see all of the controls better, look into the bottom right corner of he game engine after it runs)
void InputSub::InputUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Event test = Event('w', Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Event test = Event('s', Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Event test = Event('a', Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Event test = Event('d', Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Event test = Event(sf::Keyboard::Escape, Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
	{
		Event test = Event(sf::Keyboard::F3, Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
	{
		Event test = Event(sf::Keyboard::F4, Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
	{
		Event test = Event(sf::Keyboard::Comma, Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
	{
		Event test = Event(sf::Keyboard::Period, Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		Event test = Event(sf::Keyboard::M, Event::INPUT, Event::EventType::KEYPRESS);
		EventQueue::queue.push_back(test);
	}
}
