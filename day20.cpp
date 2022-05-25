#include "functions.h"

pair<int,int> Day20(string filename) {
	vector<string> imageData = getData(filename); //data is strings of . and # corresponding to off and on
  string imageEnhancement = getAlgorithm(imageData); //the first string is the algorithm
  vector<string> inputImage = getImage(imageData); //the image is a grid of . and #
  int numberOn = findNumberOn(inputImage, imageEnhancement, 2); //find the magnitude of the sum
  int max = findNumberOn(inputImage, imageEnhancement, 50);
  pair<int,int> pixelsAndMax = std::make_pair(numberOn, max);
  return pixelsAndMax;
}

//algorithm is 512 characters long and gives the on/off state of the center pixel by number 0-511
string getAlgorithm(vector<string> data){ 
  string algorithm = data[0];
  return algorithm;
}

vector<string> getImage(vector<string> data){ //load input image
  vector<string> image;
  for (int i = 2; i < data.size(); ++i){
    image.push_back(data[i]);
  }
  return image;
}

int findNumberOn(vector<string> image, string algorithm, int repetitions){
  int number = 0;
  vector<string> enlargedImage = enlargeImage(image, '.'); //enlarge twice to make border big enough (need 3 extra)
  vector<string> enhancedImage = enlargedImage;
  for (int i = 0; i < repetitions; ++i){
    enlargedImage = enlargeImage(enhancedImage, enhancedImage[0][0]);
    enhancedImage = enhanceImage(enlargedImage,algorithm);
  }
  //displayImage(enhancedImage);
  number = countLitPixels(enhancedImage);
  return number;
}

int countLitPixels(vector<string> image){
  int count = 0;
  for (int i = 0; i < image.size(); ++i){
    for (int j = 0; j < image[0].length(); ++j)
      if (image[i][j] == '#'){
        count ++;
      }
  }
  return count;
}

vector<string> enlargeImage(vector<string> image, char edge){ //add rows and columns of the char edge around the edges
  string edges(image[0].length()+4, edge);
  vector<string> newImage;
  for (int i = 0; i < 2; ++i){
    newImage.push_back(edges);
  }
  string shortEdges(2,edge);
  for (int i = 0; i < image.size(); ++i){
    image[i].insert(0,shortEdges);
    image[i].append(shortEdges);
    newImage.push_back(image[i]);
  }
  for (int i = 0; i < 2; ++i){
    newImage.push_back(edges);
  }
  return newImage;
}

vector<string> enhanceImage(vector<string> image, string algorithm){ //value at each pixel is given in binary by the 3x3 square of pixels
  vector<string> newImage;
  
  string currentLine;
  for (int i = 1; i < image.size() - 1; ++i){
    for (int j = 1; j < image[0].length() - 1; ++j){
      int value = findBinary(i,j, image);
      char newChar = algorithm[value];
      currentLine.push_back(newChar);
    }
    newImage.push_back(currentLine);
    currentLine.clear();
  }
  return newImage;
}

int findBinary(int i, int j, vector<string> image){
  int value = 0;
  int placeValue = 256;
  for (int k = 0; k < 3; ++k){
    for (int l = 0; l < 3; ++l){
      if (image[i-1+k][j-1+l] == '#'){
        value += placeValue;
      }
      placeValue /= 2; 
    }
  }
  return value;
}

void displayImage(vector<string> image){
  for (int i = 0; i < image.size(); ++i){
    std::cout << image[i] << std:: endl;
  }
}