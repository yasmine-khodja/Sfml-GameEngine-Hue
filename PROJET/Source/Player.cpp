#include <Book/Player.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/PlayerHue.hpp>

#include <map>
#include <string>
#include <algorithm>


struct PlayerHueMover
{
	PlayerHueMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (PlayerHue& playerhue, sf::Time) const
	{
		playerhue.marcher(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Space] = Jump;

	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's aircraft
	for(auto& pair : mActionBinding)
		pair.second.category = Category::PlayerHue;
}

Player::~Player()
{
	
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);

		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for(auto pair : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for(auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{

	sf::Vector2f playerSpeed(100.f, 0.f);
	// mActionBinding[Jump].action = derivedAction<PlayerHue>(PlayerHueMover( 0.f, -playerSpeed));

	mActionBinding[MoveLeft].action    	 = derivedAction<PlayerHue>([playerSpeed] (PlayerHue& h, sf::Time){ h.marcher(-playerSpeed);});
	mActionBinding[MoveRight].action     = derivedAction<PlayerHue>([playerSpeed] (PlayerHue& h, sf::Time){ h.marcher(playerSpeed);});
	//mActionBinding[Jump].action    	 = derivedAction<PlayerHue>([] (PlayerHue& h, sf::Time){ h.jump();});
	//mActionBinding[Jump].action    	 = derivedAction<PlayerHue>([] (PlayerHue& h, sf::Time){ h.jump();});
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case Jump:
			return true;

		default:
			return false;
	}
}
