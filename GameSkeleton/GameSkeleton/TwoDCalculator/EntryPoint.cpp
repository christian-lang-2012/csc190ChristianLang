#include "RenderUI.h"
#include "Engine.h"
#include "Vector2.h"
using Engine::Vector2;

Vector2 leftVector;
Vector2 rightVector;
Vector2 resultVector;
void myBasicVectorEquationData(const BasicVectorEquationInfo& data)
{
	leftVector = data.scalar1 * Vector2(data.x1, data.y1);
	rightVector = data.scalar2 * Vector2(data.x2, data.y2);

	resultVector = data.add ? leftVector + rightVector : leftVector - rightVector;
}

Vector2 originalVector;
Vector2 normalVector;
Vector2 cwPerpindicularVector;
Vector2 ccwPerpendicularVector;
void myPerpendicularDataCallback(const PerpendicularData& data)
{
	originalVector = Vector2(data.x, data.y);
	normalVector = originalVector.Normalized();
	cwPerpindicularVector = originalVector.PerpCW();
	ccwPerpendicularVector = originalVector.PerpCCW();
}

Vector2 dotProductVector1;
Vector2 dotProductVector2;
Vector2 dotProductProjectionVector;
Vector2 dotProductRejectionVector;
void myDotProductDataCallback(const DotProductData& data)
{
	dotProductVector1 = Vector2(data.v1i, data.v1j);
	dotProductVector2 = Vector2(data.v2i, data.v2j);

	if(data.projectOntoLeftVector)
	{
		dotProductProjectionVector = dotProductVector1.Normalized() * Engine::Dot(dotProductVector2, dotProductVector1.Normalized());
		dotProductRejectionVector = dotProductVector2 - dotProductProjectionVector;
	}
	else
	{
		dotProductProjectionVector = dotProductVector2.Normalized() * Engine::Dot(dotProductVector1, dotProductVector2.Normalized());
		dotProductRejectionVector = dotProductVector1 - dotProductProjectionVector;
	}
}

Vector2 lerpAVector;
Vector2 lerpBVector;
Vector2 lerpAMinusBVector;
Vector2 lerpAVectorLerpPortion;
Vector2 lerpBVectorLerpPortion;
Vector2 lerpLerpResultVector;
void myLerpDataCallback(const LerpData& data)
{
	lerpAVector = Vector2(data.a_i, data.a_j);
	lerpBVector = Vector2(data.b_i, data.b_j);

	lerpAMinusBVector = lerpBVector - lerpAVector;
	
	lerpAVectorLerpPortion = lerpAVector * (1 - data.beta);
	lerpBVectorLerpPortion = lerpBVector * data.beta;

	lerpLerpResultVector = lerpAVectorLerpPortion + lerpBVectorLerpPortion;

}


int main(int argc, char* argv[])
{
	Engine::Init();

	RenderUI renderUI;


	renderUI.setBasicVectorEquationData(myBasicVectorEquationData, &leftVector.X, &rightVector.X, &resultVector.X);
	renderUI.setPerpendicularData(&originalVector.X, &normalVector.X, &cwPerpindicularVector.X, &ccwPerpendicularVector.X, myPerpendicularDataCallback);
	renderUI.setDotProductData(&dotProductVector1.X, &dotProductVector2.X, &dotProductProjectionVector.X, &dotProductRejectionVector.X, myDotProductDataCallback);
	renderUI.setLerpData(&lerpAVector.X, &lerpBVector.X, &lerpAMinusBVector.X, &lerpAVectorLerpPortion.X, &lerpBVectorLerpPortion.X, &lerpLerpResultVector.X, myLerpDataCallback);

	if( ! renderUI.initialize(argc, argv))
		return -1;
	return renderUI.run();
}