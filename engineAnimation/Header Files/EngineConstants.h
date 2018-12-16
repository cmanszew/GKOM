#pragma once
#include <GL/glew.h>

namespace EngConst
{
	const GLfloat cylBore = 0.5f; //param
	const GLfloat pistonStroke = 0.6f; //param
	const GLfloat pistonHeight = 0.35f; //param
	const GLfloat conRodLen = 0.7f; //param

	const GLfloat conRodThck = 0.15f; //0.1f;
	const GLfloat rodConnectorThck = 0.15f;
	const GLfloat crankPinRad = 0.05f;
	const GLfloat crankShaftRad = 0.12f;// 16f;

	const GLfloat cylSpacing = cylBore + 0.1f;
	const GLfloat piston1x = -5.0f / 2.0f * (cylSpacing);
	const GLfloat crankX = piston1x - cylSpacing / 2;
	const GLfloat crankRad = pistonStroke / 2.0f;
	const GLfloat crankMainShaftComponent = cylSpacing - conRodThck - 2 * rodConnectorThck;
	const GLfloat rodConnectorRadL = crankRad;
	const GLfloat rodConnectorRadS = 0.8f * rodConnectorRadL;
}