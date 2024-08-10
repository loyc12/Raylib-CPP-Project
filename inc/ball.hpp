#pragma once

#include "deps.hpp"

class Ball
{
	/* ======== fields ======== */
	private:
		int 	x;
		int 	y;
		int 	radius;
		Color color;

	public:
		int 	speedX;
		int 	speedY;

	/* ======== methods ======== */
	public:
		Ball();
		~Ball();

		void UpdateInputs();
		void UpdateScripts();
		void UpdatePhysics();
		void UpdateGraphics();

	protected:
		void ClampSelf();
		void DrawSelf();
};