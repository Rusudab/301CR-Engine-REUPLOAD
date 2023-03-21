#include "EventQueue.h"

using namespace std;

vector <Event> EventQueue::queue;

EventQueue::EventQueue()
{

}

EventQueue::~EventQueue()
{

}

/*
	So, how the event queue works is that, I divided it firstly by what subsystems the event needs to use
	Afterwards, I check to see what type of event is actually happening.
	An example: If the player presses something on the keyboard, it will firstly be detected as using the INPUT subsystem,
	and then it will look for which type of event the INPUT subsystem can do.
*/
void EventQueue::EventUpdate()
{
	CheckCollider();
	while (queue.size() != 0)
	{

		switch (queue[queue.size() - 1].subType)
		{

		case Event::INPUT:
		{
			switch (queue[queue.size() - 1].eventType)
			{
			case Event::EventType::KEYPRESS:
			{
				switch (queue[queue.size() - 1].keyPress)
				{
				case sf::Keyboard::Escape:
				{
					queue.pop_back();
					shutdown = true;
					break;
				}
				case 'w':
				{
					queue.pop_back();
					Event movement = Event('w', Event::PHYSICS, Event::EventType::MOVEMENT);
					AddEvent(movement);
					break;
				}
				case 'a':
				{
					queue.pop_back();
					Event movement = Event('a', Event::PHYSICS, Event::EventType::MOVEMENT);
					AddEvent(movement);
					break;
				}
				case 'd':
				{
					queue.pop_back();
					Event movement = Event('d', Event::PHYSICS, Event::EventType::MOVEMENT);
					AddEvent(movement);
					break;
				}
				case 's':
				{
					queue.pop_back();
					Event movement = Event('s', Event::PHYSICS, Event::EventType::MOVEMENT);
					AddEvent(movement);
					break;
				}
				case sf::Keyboard::F3:
				{
					queue.pop_back();
					Event showfps = Event('F', Event::GRAPHICS, Event::EventType::SHOWFPS);
					AddEvent(showfps);
					break;
				}
				case sf::Keyboard::F4:
				{
					queue.pop_back();
					Event dontshowfps = Event('F', Event::GRAPHICS, Event::EventType::DONTSHOWFPS);
					AddEvent(dontshowfps);
					break;
				}
				case sf::Keyboard::Comma:
				{
					queue.pop_back();
					Event startmusic = Event(',', Event::AUDIO, Event::EventType::PLAYSOUND);
					AddEvent(startmusic);
					break;
				}
				case sf::Keyboard::Period:
				{
					queue.pop_back();
					Event stopmusic = Event('.', Event::AUDIO, Event::EventType::DONTPLAYSOUND);
					AddEvent(stopmusic);
					break;
				}
				case sf::Keyboard::M:
				{
					queue.pop_back();
					Event changescore = Event('m', Event::NETWORK, Event::EventType::CHANGESCORE);
					AddEvent(changescore);
					break;
				}
				}
			}
			}
			break;
		}
		case Event::GRAPHICS:
		{
			switch (queue[queue.size() - 1].eventType)
			{
			case Event::EventType::SHOWFPS:
			{
				queue.pop_back();
				showfps = true;
				break;
			}
			case Event::EventType::DONTSHOWFPS:
			{
				queue.pop_back();
				showfps = false;
				break;
			}
			case Event::EventType::SHOWSCORE:
			{
				queue.pop_back();
				GraphicsSub::scoreboardOn = true;
				break;
			}
			break;
			}
			break;
		}
		case Event::PHYSICS:
		{
			switch (queue[queue.size() - 1].eventType)
			{
			case Event::EventType::MOVEMENT:
			{
				GameObject::PlayerMovement(queue[queue.size() - 1].keyPress);
				queue.pop_back();
				break;
			}
			case Event::EventType::COLLIDE:
			{
				queue.pop_back();
				Event collide = Event('1', Event::GRAPHICS, Event::EventType::SHOWSCORE);
				AddEvent(collide);
				break;
			}
			}
			break;
		}
		case Event::AUDIO:
		{
			switch (queue[queue.size() - 1].eventType)
			{
				case Event::EventType::PLAYSOUND:
				{
					queue.pop_back();
					AudioSub::SetListening(true);
					break;
				}
				case Event::EventType::DONTPLAYSOUND:
				{
					queue.pop_back();
					AudioSub::SetListening(false);
					break;
				}
				break;
				}
			break;
		}
		case Event::NETWORK:
		{
			switch (queue[queue.size() - 1].eventType)
			{
				case Event::EventType::CHANGESCORE:
				{
					queue.pop_back();
					Networking::change++;
					break;
				}
				break;
			}
			break;
		}
		}
	}
}

void EventQueue::AddEvent(Event event)
{
	queue.push_back(event);
}

//This function was created in order to make an Event for the moment when the player collides with my endgame box
void EventQueue::CheckCollider()
{
	if (PhysicsSub::isColliding)
	{
		Event test = Event('1', Event::PHYSICS, Event::EventType::COLLIDE);
		AddEvent(test);
	}
}