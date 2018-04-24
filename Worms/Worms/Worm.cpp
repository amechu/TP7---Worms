#include "Worm.h"
#include "GameSettings.h"

Worm::Worm(unsigned int id, Point position, WormDirection direction)
{
	this->id = id;
	this->Position = position;
	this->Direction = direction;
}


Worm::~Worm()
{
}

unsigned int Worm::getId()
{
	return this->id;
}

int Worm::getTickCount()
{
	return tickCount;
}

Point Worm::getPosition()
{
	return (this->Position);
}

WormState Worm::getState()
{
	return State;
}

WormDirection Worm::getDirection()
{
	return Direction;
}

void Worm::toggle()
{
	if (this->State == WormState::Iddle) {
		if (this->Direction == WormDirection::Left) //Para mas tarde: pensar como hacer esto en una linea
			this->Direction = WormDirection::Right;
		else
			this->Direction = WormDirection::Left;
	}
}

void Worm::moveLeft(bool callFromRefresh)
{
	if (this->State == WormState::Iddle || this->State == WormState::Walking) {
		if (this->Direction == WormDirection::Left) {
		this->State = WormState::Walking;
			if (this->Position.X >= gameSettings::LeftWall) {
				if (tickCount == 16 || tickCount == 31 || tickCount == 44) {
					this->Position.X -= gameSettings::WalkVelocity;
				}
			}
			this->tickCount++;
			if (this->tickCount == 44 && callFromRefresh == false) {
				this->tickCount = 0;
			}
		}
	}
}

void Worm::moveRight(bool callFromRefresh)
{
	if (this->State == WormState::Iddle || this->State == WormState::Walking) {
		if (this->Direction == WormDirection::Right) {
			this->State = WormState::Walking;
			if (this->Position.X <= gameSettings::RightWall) {
				if (tickCount == 16 || tickCount == 31 || tickCount == 44) {
					this->Position.X += gameSettings::WalkVelocity;
				}
			}
			this->tickCount++;
			if (this->tickCount == 44 && callFromRefresh == false) {
				this->tickCount = 0;
			}
		}
	}
}

void Worm::jump()
{

	double Linear;
	double Cuadratic;

	if (this->State == WormState::Iddle || this->State == WormState::Jumping) {

		if (this->State == WormState::Iddle)
			this->State = WormState::Jumping;

		this->tickCount++;
		if (this->Direction == WormDirection::Left) {

			if (this->tickCount <= 32) {
				if (Position.X > gameSettings::LeftWall + (gameSettings::Velocity * cos(M_PI / 3))) {
					this->Position.X -= (gameSettings::Velocity * cos(M_PI / 3));
				}
				Linear = gameSettings::Velocity * sin(M_PI / 3) * tickCount;
				Cuadratic = (((gameSettings::Gravity) / 2) * tickCount * tickCount);
				this->Position.Y = gameSettings::GroundLevel - Linear + Cuadratic;
			}
			else {
				this->tickCount = 0;
				this->State = WormState::Iddle;
			}
		}
		else if (this->Direction == WormDirection::Right) {

			if (this->tickCount <= 32) {
				if (Position.X < gameSettings::RightWall - (gameSettings::Velocity * cos(M_PI / 3))) {
					this->Position.X += (gameSettings::Velocity * cos(M_PI / 3));
				}
				Linear = gameSettings::Velocity * sin(M_PI / 3) * tickCount;
				Cuadratic = (((gameSettings::Gravity) / 2) * tickCount * tickCount);
				this->Position.Y = gameSettings::GroundLevel - Linear + Cuadratic;
			}
			else {
				this->tickCount = 0;
				this->State = WormState::Iddle;
			}
		}
	}
}

void Worm::refresh()
{
	switch (this->State) {
		case WormState::Iddle: {
			break;
		}
		case WormState::Jumping: {
			jump();
			break;
		}
		case WormState::Walking: {
			switch (this->Direction) {
				case WormDirection::Left: {
					moveLeft(REFRESH_DRIVEN);
					break;
				}
				case WormDirection::Right: {
					moveRight(REFRESH_DRIVEN);
					break;
				}
			}
		}
	}
}
