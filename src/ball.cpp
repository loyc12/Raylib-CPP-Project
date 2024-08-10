#include "../inc/ball.hpp"

Ball::Ball()
{
	this->x = GetScreenWidth() / 2;
	this->y = GetScreenHeight() / 2;
	this->speedX = 8;
	this->speedY = 4;
	this->radius = 16;
	this->color = Color{ 2, 126, 252, 255 };
}
Ball::~Ball() = default;

void Ball::UpdateInputs()
{
	static int acc = 2;

	if ( IsKeyDown( KEY_RIGHT ) )
		this->speedX += acc;
	if ( IsKeyDown( KEY_LEFT ) )
		this->speedX -= acc;

	if ( IsKeyDown( KEY_DOWN ) )
		this->speedY += acc;
	if ( IsKeyDown( KEY_UP ) )
		this->speedY -= acc;
}

void Ball::UpdateScripts()
{
	if ( this->x - this->radius <= 0 )
		INFO( "Ball hit left wall", "Ball::updateScripts" );
	if ( this->x + this->radius >= GetScreenWidth() )
		INFO( "Ball hit right wall", "Ball::updateScripts" );

	if ( this->y - this->radius <= 0  )
		INFO( "Ball hit top wall", "Ball::updateScripts" );
	if ( this->y + this->radius >= GetScreenHeight()  )
		INFO( "Ball hit bottom wall", "Ball::updateScripts" );
}

void Ball::UpdatePhysics()
{
	static int grav = 1;
	static int absorb = 1;

	this->speedY += grav;

	this->ClampSelf();

	this->x += speedX;
	this->y += speedY;

	if ( this->x + this->radius >= GetScreenWidth() || this->x - this->radius <= 0 )
	{
		if ( this->speedX > 0 )
			this->speedX -= absorb;
		else if ( this->speedX < 0 )
			this->speedX += absorb;

		this->speedX *= -1;
	}

	if ( this->y + this->radius >= GetScreenHeight() || this->y - this->radius <= 0 )
	{
		if ( this->speedY > 0 )
			this->speedY -= absorb;
		else if ( this->speedY < 0 )
			this->speedY += absorb;

		this->speedY *= -1;
	}
}

void Ball::UpdateGraphics()
{
	static int deltaR = 1;
	static int deltaG = 1;
	static int deltaB = 1;

	static int max = 252;
	static int min = 2;

	if ( this->color.r >= max )
		deltaR = -1;
	if ( this->color.r <= min )
		deltaR = 1;

	if ( this->color.g >= max )
		deltaG = -1;
	if ( this->color.g <= min )
		deltaG = 1;

	if ( this->color.b >= max )
		deltaB = -1;
	if ( this->color.b <= min )
		deltaB = 1;

	this->color.r += deltaR;
	this->color.g += deltaG;
	this->color.b += deltaB;

	this->DrawSelf();
}

void Ball::ClampSelf()
{
	static int speedLimit = 24;

	if ( this->x + this->radius >= GetScreenWidth() )
		this->x = GetScreenWidth() - this->radius;
	if ( this->x - this->radius <= 0 )
		this->x = this->radius;
	if ( this->y + this->radius >= GetScreenHeight() )
		this->y = GetScreenHeight() - this->radius;
	if ( this->y - this->radius <= 0 )
		this->y = this->radius;

	if ( this->speedX > speedLimit )
		this->speedX = speedLimit;
	if ( this->speedX < -speedLimit )
		this->speedX = -speedLimit;

	if ( this->speedY > speedLimit )
		this->speedY = speedLimit;
	if ( this->speedY < -speedLimit )
		this->speedY = -speedLimit;
}

void Ball::DrawSelf()
{
  DrawCircle( x, y, radius, this->color );
}