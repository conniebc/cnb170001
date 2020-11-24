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
#define MATRIX_NAME_STRING "Test Matrix"

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

  const char *rowTitles[MATRIX_ROWS + 1] = {"IGNORE", "R1", "R2", "R3", "R4", "R5", "R6"};
  const char *columnTitle[MATRIX_COLS + 1] = {"IGNORE", "C1", "C2", "C3"};
  int colWidths[MATRUX_COLS + 1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_COLS + 1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  //The Binary File IO is being process
  ifstream infile;

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  infile.open("cs3377.bin", ios::in | ios::binary);

  infile.read((char *) myHeader, sizeof(BinaryFileRecord));

  int num = myHeader->numRecords;





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

  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);

  sleep(10);

  endCDK();
}
