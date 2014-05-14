#include "RenderUI.h"
#include "Engine.h"
#include "Vector2.h"
#include "Matrix2.h"
#include "Matrix3.h"
using Engine::Vector2;
using Engine::Matrix3;

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
		dotProductProjectionVector = dotProductVector1.Normalized() * (Engine::Dot(dotProductVector2, dotProductVector1.Normalized()));
		dotProductRejectionVector = dotProductVector2 - dotProductProjectionVector;
	}
	else
	{
		dotProductProjectionVector = dotProductVector2.Normalized() * (Engine::Dot(dotProductVector1, dotProductVector2.Normalized()));
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

Vector2 basicMatrixMultiplyResultVector;
void myLinearTransformationCallback(const LinearTransformationData& data)
{
	Vector2 col1(data.m00, data.m01);
	Vector2 col2(data.m10, data.m11);
	Vector2 vect(data.v0, data.v1);
	basicMatrixMultiplyResultVector = Matrix2(col1, col2) * vect;
}

float affineResult[15];
void myAffineTransformationCallback(const AffineTransformationData& data)
{
	Matrix3 matrix;
	matrix.x1 = data.data[0];
	matrix.x2 = data.data[1];
	matrix.x3 = data.data[2];
	matrix.y1 = data.data[3];
	matrix.y2 = data.data[4];
	matrix.y3 = data.data[5];
	matrix.z1 = data.data[6];
	matrix.z2 = data.data[7];
	matrix.z3 = data.data[8];

	Vector3 v1 = matrix * Vector3(data.data[9], data.data[10], data.data[11]);
	Vector3 v2 = matrix * Vector3(data.data[12], data.data[13], data.data[14]);
	Vector3 v3 = matrix * Vector3(data.data[15], data.data[16], data.data[17]);
	Vector3 v4 = matrix * Vector3(data.data[18], data.data[19], data.data[20]);
	Vector3 v5 = matrix * Vector3(data.data[21], data.data[22], data.data[23]);
	affineResult[0] = v1.X;
	affineResult[1] = v1.Y;
	affineResult[2] = v1.Z;
	affineResult[3] = v2.X;
	affineResult[4] = v2.Y;
	affineResult[5] = v2.Z;
	affineResult[6] = v3.X;
	affineResult[7] = v3.Y;
	affineResult[8] = v3.Z;
	affineResult[9] = v4.X;
	affineResult[10] = v4.Y;
	affineResult[11] = v4.Z;
	affineResult[12] = v5.X;
	affineResult[13] = v5.Y;
	affineResult[14] = v5.Z;
}

const float span = 0.3f;
Vector2 bottomLeft(-span, -span);
Vector2 topLeft(-span, span);
Vector2 topRight(span, span);
Vector2 bottomRight(span, -span);
Vector2 roofTop(0, span + .25f);

Vector2 lines[] = {
bottomLeft, 
topLeft,
topLeft, 
topRight,
topRight, 
bottomRight,
bottomRight, 
bottomLeft,
topLeft, 
roofTop,
topRight, 
roofTop
};

int numLines = sizeof(lines) / (sizeof(*lines) * 2);
Matrix3 matrices[10];
Matrix3 currentTransform;

void myMatrixTransformCallback2D(const MatrixTransformData2D& data)
{
	currentTransform = Matrix3();
	matrices[data.selectedMatrix] = matrices[data.selectedMatrix].Rotation(data.rotate);
	matrices[data.selectedMatrix] = matrices[data.selectedMatrix].ScaleX(data.scaleX);
	matrices[data.selectedMatrix] = matrices[data.selectedMatrix].ScaleY(data.scaleY);
	matrices[data.selectedMatrix] = matrices[data.selectedMatrix].Translation(Vector2(data.translateX, data.translateY));
	for(int i = 0; i < 10; i++)
	{
		currentTransform = currentTransform * matrices[i];
	}
}

void myMatrixTransformCallback3D(const MatrixTransformData3D& data)
{

}

int main(int argc, char* argv[])
{
	Engine::Init();

	RenderUI renderUI;

	//Setting the callbacks for the methods above.
	renderUI.setBasicVectorEquationData(myBasicVectorEquationData, &leftVector.X, &rightVector.X, &resultVector.X);
	renderUI.setPerpendicularData(&originalVector.X, &normalVector.X, &cwPerpindicularVector.X, &ccwPerpendicularVector.X, myPerpendicularDataCallback);
	renderUI.setDotProductData(&dotProductVector1.X, &dotProductVector2.X, &dotProductProjectionVector.X, &dotProductRejectionVector.X, myDotProductDataCallback);
	renderUI.setLerpData(&lerpAVector.X, &lerpBVector.X, &lerpAMinusBVector.X, &lerpAVectorLerpPortion.X, &lerpBVectorLerpPortion.X, &lerpLerpResultVector.X, myLerpDataCallback);
	renderUI.setLinearTransformationData(&basicMatrixMultiplyResultVector.X, myLinearTransformationCallback);
	renderUI.setAffineTransformationData(affineResult, myAffineTransformationCallback);
	renderUI.set2DMatrixVerticesTransformData(reinterpret_cast<float*>(lines), numLines, reinterpret_cast<float*>(matrices), currentTransform, myMatrixTransformCallback2D);

	if( ! renderUI.initialize(argc, argv))
		return -1;
	return renderUI.run();
}