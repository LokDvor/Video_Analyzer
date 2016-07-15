#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>  

typedef struct My_frame{
	int marker;
	char* filename;
	int num_frame;
}My_frame;

int findCompleteMarkOnFrame(IplImage* image){
	
	int value = 0;

	for( int y=0; y<image->height; y++ ) {
     	uchar* ptr = (uchar*) (image->imageData + y * image->widthStep);
    		for( int x=0; x<image->width; x++ ) {
       		if ((ptr[3*x] == 0) && (ptr[3*x+1] == 0)){
				value++;	
			}
  }
}	
	
	return value;	
	
}

IplImage* getNextFrame( CvCapture* capture ){
	IplImage* tmp_frame = 0;

	if(tmp_frame = cvQueryFrame( capture )){
	
		return tmp_frame;
	} 
	else{
		
		return NULL;
	
	}
	
}

int main(int argc, char* argv[]){
	IplImage* frame =0;
	IplImage* tmp_frame =0;

	char* str_frame;	
	
	const char * str_name = "FRAME_";

	My_frame arr_frame[512];
	int i = 0;
	// имя файла задаётся первым параметром
	char* filename = argv[1];

	printf("[i] file: %s\n", filename);

	// окно для отображения картинки
	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("tmp", CV_WINDOW_AUTOSIZE);	
	

	// получаем информацию о видео-файле
	CvCapture* capture = cvCreateFileCapture( filename );

	frame = getNextFrame(capture);	

	while(frame){
		
		
		if(i%1 == 0){
			
			tmp_frame = cvCreateImage( cvSize(frame->width, frame->height), IPL_DEPTH_8U, 3);
			cvThreshold(frame , tmp_frame, 80, 256, CV_THRESH_BINARY);		
				
			arr_frame[i].marker = findCompleteMarkOnFrame(tmp_frame);
			cvShowImage( "tmp", tmp_frame );
				
//			strcpy(arr_frame[i].filename, str_name);
			
			arr_frame[i].num_frame = i;	
	
			printf("=========================================\n %d\n", arr_frame[i].marker);
//			printf("%s%d marker = %d\n", arr_frame[i].filename, arr_frame[i].num_frame, arr_frame[i].marker);
//			cvWaitKey(0);
		}
	
		
//		arr_frame[i].marker = findCompleteMarkOnFrame(frame);
		
//		strcpy(arr_frame[i].filename, str_name);
//		strcat(arr_frame[i].filename, (char*)i);

		printf("==========================87777===============\n");
//		printf("%s marker = %d\n", arr_frame[i].filename, arr_frame[i].marker);
		
		

		cvShowImage( "original", frame );
		
//		strcpy(str_frame, arr_frame[i].filename);
//		strcat(str_frame, ".png");
	
//		cvSaveImage("Frame_.png", frame);
		

		frame = getNextFrame(capture);
		i++;
		char c = cvWaitKey(33);
		if (c == 27) { // если нажата ESC - выходим
			break;
		}
	}
	
	printf("%d\n", i);
	// освобождаем ресурсы
	cvReleaseCapture( &capture );
	// удаляем окно
	cvDestroyWindow("original");
	return 0;
}
