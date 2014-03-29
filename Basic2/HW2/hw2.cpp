
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int Matching(IplImage *origImg, IplImage *templet)
{
	int y, x;
	int i, j;
	int tot_or = 0;
	int tot_te = 0;
	double avg_or; //DB에 있는 이미지들의 밝기 평균 
	double avg_te; //검색하려는 이미지의 밝기 평균
	double e;

	double cov = 0;
	double var_or = 0;
	double var_te = 0;
	double var;
	double result;

	//밝기의 평균값 구하기.
	for ( y = 0 ; y < origImg->height ; y ++ )
	{
		for ( x = 0 ; x < origImg ->width ; x ++ )
		{
			CvScalar itensity = cvGet2D(origImg, y, x);
			tot_or += itensity.val[0];
		}
	}

	avg_or = (double)tot_or / (double)(origImg->height * origImg ->width);
	

	for ( y = 0 ; y < templet->height ; y ++ )
	{
		for ( x = 0 ; x < templet ->width ; x ++ )
		{
			CvScalar itensity = cvGet2D(templet, y, x);
			tot_te += itensity.val[0];
		}
	}
	avg_te = (double)tot_te / (double)(templet->height * templet->width);


	//cov부분 구하기
	for ( y = 0 ; y < templet->height ; y ++ )
	{
		for ( x = 0 ; x < templet ->width ; x ++ )
		{
			CvScalar itensity1 = cvGet2D(origImg, y, x);
			CvScalar itensity2 = cvGet2D(templet, y, x);
			
			cov += abs(itensity1.val[0] - avg_or) * abs(itensity2.val[0] - avg_te);
		}
	}
	//DB에 있는 영상 var구하기
	for ( y = 0 ; y < origImg->height ; y ++ )
	{
		for ( x = 0 ; x < origImg ->width ; x ++ )
		{
			CvScalar itensity1 = cvGet2D(origImg, y, x);
			
			var_or += (itensity1.val[0] - avg_or) * (itensity1.val[0] - avg_or);
		}
	}
	
	//Templet의 var구하기
	for ( y = 0 ; y < templet->height ; y ++ )
	{
		for ( x = 0 ; x < templet ->width ; x ++ )
		{
			CvScalar itensity1 = cvGet2D(templet, y, x);
			
			var_te += (itensity1.val[0] - avg_te) * (itensity1.val[0] - avg_te);
		}
	}

	//최종 var 구하기

	var = sqrt(var_or * var_te);
	
	result = cov / var;
	if(result < 0 )
	{
		result *= -1;
	}

	return (int)(result * 100);
}

int main()
{
	int i,j;
	int mat_result[10][10];
	IplImage *billy = cvLoadImage("orig.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	FILE * result1 = fopen("result1.txt", "w");
	FILE * result2 = fopen("result2.txt", "w");
	FILE * result3 = fopen("result3.txt", "w");
	
	IplImage *img1[13];
	
	for ( i = 1 ; i <= 10 ; i ++ )
	{
		char file[100];
		sprintf(file, "./pro1/%d.jpg", i);
		img1[i] = cvLoadImage(file, CV_LOAD_IMAGE_GRAYSCALE);
		fprintf(result1, "(친구얼굴)%2d.jpg : %d", i, Matching(img1[i], billy));
		if( i == 1)
		{
			fprintf(result1, "(다르게 찍은 본인 얼굴)");
		}
		fprintf(result1, "\n");
		cvReleaseImage(&img1[i]);
	}

	IplImage *img2[13];
	for ( i = 1 ; i <= 10 ; i ++ )
	{
		char file[100];
		sprintf(file, "./pro2/%d.jpg", i);
		img2[i] = cvLoadImage(file, CV_LOAD_IMAGE_GRAYSCALE);
		fprintf(result2, "(연예인얼굴)%2d.jpg : %d\n", i, Matching(img2[i], billy));
		
		cvReleaseImage(&img2[i]);
	}
	

	for ( i = 1 ; i <= 10 ; i ++ )
	{
		char file1[100];
		char file2[100];
		sprintf(file1, "./pro2/%d.jpg", i);
		img1[i] = cvLoadImage(file1, CV_LOAD_IMAGE_GRAYSCALE);
		for ( j = 1 ; j <= 10 ; j ++ )
		{
			sprintf(file2, "./pro2/%d.jpg", j);
			img2[j] = cvLoadImage(file2, CV_LOAD_IMAGE_GRAYSCALE);
			mat_result[i-1][j-1] = Matching(img2[j], img1[i]);
			cvReleaseImage(&img2[j]);
		}
		cvReleaseImage(&img1[i]);
	}

	for ( i = 0 ; i < 10 ; i ++ )
	{
		for ( j = 0 ; j < 10 ; j ++ )
		{
			fprintf(result3, "%4d", mat_result[i][j]);
		}
		fprintf(result3, "\n");
	}


	cvReleaseImage(&billy);
	fclose(result1);
	fclose(result2);
	fclose(result3);

	return 0;
}