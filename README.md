# Creative coding using openFrameworks - Workshop: Simple Object Detection using OpenCV

**openFrameworks version**: 0.9.6

The purpose of this project is to illustrate and teach the access of connected cameras, basic image manipulation as well as some simple object detection capabilities of the OpenCV addon using the the creative coding toolkit [openFrameworks](http://openframeworks.cc). This activity is meant to be held in a workshop-like format and steb by step to the participants using live coding, supported by summarizing slides.

Following, a brief overview about the project's content is given in order as they are illustrated during the workshop:

1. Setup a *camera* input source and draw the camera input to the application window. Furthermore, a helper function is created in order to log information about *available camera devices*.
2. Create a *HSV* representation of the original camera input image as well as extracting *hue*, *saturation* and *value* color channel information into separate image instances.
3. Simple *Image manipulation* in order to assist the later object detection by taking the difference between a registered background and the saturation color channel image. Additionally, the contrast is increased via defined threshold value.
4. Using the OpenCV *[Contour Finder](http://openframeworks.cc/documentation/ofxOpenCv/ofxCvContourFinder.html)* instance, objects ("blobs") are detected and visualized accordingly.
5. Using the *center point* of each detected object ("blob"), the *color* is extracted and visualized as a circle overlay.


## License
MIT License, see [LICENSE.md](LICENSE.md)
