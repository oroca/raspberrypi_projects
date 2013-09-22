#include "highgui.h"
#include "cv.h"

int main(void)
{
  double wsize = 320;
  double hsize = 240;

  cvNamedWindow("FaceDetection", CV_WINDOW_AUTOSIZE);

  CvCapture* capture = NULL;

  capture = cvCreateCameraCapture(0);
  cvSetCaptureProperty (capture, CV_CAP_PROP_FRAME_WIDTH,  wsize);
  cvSetCaptureProperty (capture, CV_CAP_PROP_FRAME_HEIGHT, hsize);

  IplImage* frame;
  CvHaarClassifierCascade* cvHCC = (CvHaarClassifierCascade*)cvLoad("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml");
  CvMemStorage* cvMStr = cvCreateMemStorage(0);
  CvSeq* face;

  while(1)
  {
    frame = cvQueryFrame(capture);
    if(!frame) break;

    face = cvHaarDetectObjects(frame, cvHCC, cvMStr);

    for (int i = 0; i < face->total; i++)
    {
      CvRect* faceRect = (CvRect*)cvGetSeqElem(face, i);
      cvRectangle(frame,
                  cvPoint(faceRect->x, faceRect->y),
                  cvPoint(faceRect->x + faceRect->width, faceRect->y + faceRect->height),
                  CV_RGB(255, 0 ,0),
                  2, CV_AA);
    }

    cvShowImage("FaceDetection", frame);

    if(cvWaitKey(33)==27) break;
  }

  cvReleaseMemStorage(&cvMStr);
  cvReleaseHaarClassifierCascade(&cvHCC);
  cvReleaseCapture( &capture );

  cvDestroyWindow("FaceDetection");
}
