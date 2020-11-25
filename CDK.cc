/* Filename:   cdk.cc
 * Date:       11/23/20
 * Auhtor:     Connie Bardalez
 * Email:      cnb170001@utdallas.edu
 * Version:    1.0
 * Copyright:  2020, All Rights Reserved
 *
 * Description:
 * A source code that displays and builds a matrix
 * using curses and the CDK.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include "cdk.h"

#define MATRIX_ROWS 5
#define MATRIX_COLS 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader{
public:
 
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord{
public:

  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main(){
  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;

  const char *rowTitles[MATRIX_ROWS + 1] = {"IGNORE", "a", "b", "c"};
  const char *columnTitle[MATRIX_COLS + 1] = {"IGNORE", "a", "b", "c"};
  int colWidths[MATRUX_COLS + 1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_COLS + 1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  //The Binary File IO is being process
  ifstream infile;

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  infile.open("cs3377.bin", ios::in | ios::binary);

  infile.read((char *) myHeader, sizeof(BinaryFileRecord));

  int num = myHeader->numRecords;

  BinaryFileRecord myRecord[num];

  for(int i = 0; i < num; i++){
    inFile.read((char *) &myRecord[i], sizeof(BinaryFileRecord));
  }

  inFile.close();
  //End

  window = initscr();
  cdkscreen = initCDKScreen(window);

  initCDKColor();

  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_ROWS, MATRIX_COLS, MATRIX_ROWS, MATRIX_COLS, MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, colWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);

  if(myMatrix == NULL){
    printf("Error creating Matrix\n");
    _exit(1);
  }

  drawCDKMatrix(myMatrix, true);
  
  //Set each cell
  setCDKMatrixCell(myMatrix, 1, 1, myHeader->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 2, myHeader->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 3, myHeader->numRecords);
  setCDKMatrixCell(myMatrix, 2, 1, myRecord->strLength);
  setCDKMatrixCell(myMatrix, 2, 2, myRecord->stringBuffer);
  setCDKMatrixCell(myMatrix, 3, 1, myRecord->strLength);
  setCDKMatrixCell(myMatrix, 3, 2, myRecord->stringBuffer);
  setCDKMatrixCell(myMatrix, 4, 1, myRecord->strLength);
  setCDKMatrixCell(myMatrix, 4, 2, myRecord->stringBuffer);
  setCDKMatrixCell(myMatrix, 5, 1, myRecord-> strLength);
  setCDKMatrixCell(myMatrix, 5, 2, myRecord->stringBuffer);  
  //End

  drawCDKMatrix(myMatrix, true);

  sleep(10);

  endCDK();
  delete myHeader;

  return 0;
}
