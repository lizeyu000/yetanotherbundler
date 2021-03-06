#include "utils.h"

void norm(CvMat *mat)
{
  double norm = 0;
  
  for(int i = 0; i < mat->rows; i++)
    for(int j = 0; j < mat->cols; j++)
      norm += cvmGet(mat, i, j) * cvmGet(mat, i, j);
      
  double scale = 1 / sqrt(norm);
  
  cvScale(mat, mat, scale);
}

/**************************************************************************************************
 * Returns the integer inhomogeneous coordinates of a homogeneous 2D point
 **************************************************************************************************/
CvPoint get2DPoint(CvMat *hom2DPoint)
{
  CvPoint point = cvPoint((int)(cvmGet(hom2DPoint, 0, 0) / cvmGet(hom2DPoint, 2, 0)),
                          (int)(cvmGet(hom2DPoint, 1, 0) / cvmGet(hom2DPoint, 2, 0)));
  
  return point;
}

/**************************************************************************************************
 * Returns the integer inhomogeneous coordinates of a homogeneous 2D Harris corner
 **************************************************************************************************/
CvPoint get2DPoint(Corner *corner)
{
  return get2DPoint(corner->imagePoint);
}

/**************************************************************************************************
 * Returns the double inhomogeneous coordinates of a homogeneous 2D point
 **************************************************************************************************/
CvPoint2D64f get2DPointf(CvMat *hom2DPoint)
{
  CvPoint2D64f point = cvPoint2D64f(cvmGet(hom2DPoint, 0, 0) / cvmGet(hom2DPoint, 2, 0),
                                    cvmGet(hom2DPoint, 1, 0) / cvmGet(hom2DPoint, 2, 0));
  
  return point;
}

/**************************************************************************************************
 * Returns the double inhomogeneous coordinates of a homogeneous 2D Harris corner
 **************************************************************************************************/
CvPoint2D64f get2DPointf(Corner *corner)
{  
  return get2DPointf(corner->imagePoint);
}

void normInhomogeneous(CvMat *mat)
{
  double norm = 0;
  
  for(int i = 0; i < mat->rows - 1; i++)
    for(int j = 0; j < mat->cols; j++)
      norm += cvmGet(mat, i, j) * cvmGet(mat, i, j);
  
  for(int j = 0; j < mat->cols - 1; j++)
    norm += cvmGet(mat, mat->rows - 1, j) * cvmGet(mat, mat->rows - 1, j);
  
  double scale = 1 / sqrt(norm);
  
  cvScale(mat, mat, scale);
}

CvMat *getHomogeneous2DPoint(double x, double y)
{
  CvMat *point = cvCreateMat(3, 1, CV_64FC1);
  
  cvmSet(point, 0, 0, x);
  cvmSet(point, 1, 0, y);
  cvmSet(point, 2, 0, 1);
  
  return point;
}

void scaleToInhomogeneous(CvMat *mat)
{
  double scale = 1 / cvmGet(mat, mat->rows - 1, mat->cols - 1);
  
  cvScale(mat, mat, scale);
}

int saveCvMat2MATLAB(CvMat* mat, char* fileName)
{
	FILE* fp = fopen(fileName,"wb");

	if(fp == NULL)
	{
		/// failed.
		return -1;
	}

	for(int i = 0;i<mat->rows; i++)
	{
		for(int j=0;j< mat->cols; j++)
		{
			if(j != (mat->cols-1))
				fprintf(fp,"%e,",cvmGet(mat,i,j));
			else
				fprintf(fp,"%e",cvmGet(mat,i,j));
		}

		if(i != (mat->rows-1))
			fprintf(fp,"\n");
	}

	fclose(fp);

	return 0;
}

/// 파일 필드 구성.
///
///    x1 y1 isMatched isInliers x2(-1), y2(-1)
int saveInliersPts2MATLAB(Frame* frame,char* fileName)
{
	FILE *fp = fopen(fileName,"wb");

	if(fp == NULL)
		return -1;

	Corner *currentPoint = frame->firstPoint;

	double nothing = -1.0;

	while (currentPoint != NULL)
	{
		if(currentPoint->nextPoint != NULL)
		{
			if(currentPoint->matchNextFrame != NULL)
				fprintf(fp,"%e,%e,1,%d,%e,%e\n",cvmGet(currentPoint->imagePoint,0,0),cvmGet(currentPoint->imagePoint,1,0),currentPoint->isInlier?1:0,cvmGet(currentPoint->matchNextFrame->imagePoint,0,0),cvmGet(currentPoint->matchNextFrame->imagePoint,1,0));
			else // NULL
				fprintf(fp,"%e,%e,0,%d,%e,%e\n",cvmGet(currentPoint->imagePoint,0,0),cvmGet(currentPoint->imagePoint,1,0),currentPoint->isInlier?1:0,nothing,nothing);
		}
		else
		{
			if(currentPoint->matchNextFrame != NULL)
				fprintf(fp,"%e,%e,1,%d,%e,%e",cvmGet(currentPoint->imagePoint,0,0),cvmGet(currentPoint->imagePoint,1,0),currentPoint->isInlier?1:0,cvmGet(currentPoint->matchNextFrame->imagePoint,0,0),cvmGet(currentPoint->matchNextFrame->imagePoint,1,0));
			else // NULL
				fprintf(fp,"%e,%e,0,%d,%e,%e",cvmGet(currentPoint->imagePoint,0,0),cvmGet(currentPoint->imagePoint,1,0),currentPoint->isInlier?1:0,-nothing,nothing);
		}

		currentPoint = currentPoint->nextPoint;
	}

	fclose(fp);

	return 0;
}