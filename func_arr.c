#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"

double length0(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  return 0;
}

double length1(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  return score;
}

double length2(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  return score;
}

double length3(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  return score;
}

double length4(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  return score;
}

double length5(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  return score;
}

double length6(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  return score;
}

double length7(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  return score;
}

double length8(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  return score;
}

double length9(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  return score;
}

double length10(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  return score;
}

double length11(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  return score;
}

double length12(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  return score;
}

double length13(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  return score;
}

double length14(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  return score;
}

double length15(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  return score;
}

double length16(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  return score;
}

double length17(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  return score;
}

double length18(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  return score;
}

double length19(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  return score;
}

double length20(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  return score;
}

double length21(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  return score;
}

double length22(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  return score;
}

double length23(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  return score;
}

double length24(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  return score;
}

double length25(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  return score;
}

double length26(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  return score;
}

double length27(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  return score;
}

double length28(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  return score;
}

double length29(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  return score;
}

double length30(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  return score;
}

double length31(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  return score;
}

double length32(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  return score;
}

double length33(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  return score;
}

double length34(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  return score;
}

double length35(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  return score;
}

double length36(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  return score;
}

double length37(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  return score;
}

double length38(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  return score;
}

double length39(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  return score;
}

double length40(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  return score;
}

double length41(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  return score;
}

double length42(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  if (*(collection+base + 41) == querytermid) score+=log(1 + *(tf+base + 41) / prob) + plus;
  return score;
}

double length43(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  if (*(collection+base + 41) == querytermid) score+=log(1 + *(tf+base + 41) / prob) + plus;
  if (*(collection+base + 42) == querytermid) score+=log(1 + *(tf+base + 42) / prob) + plus;
  return score;
}

double length44(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  if (*(collection+base + 41) == querytermid) score+=log(1 + *(tf+base + 41) / prob) + plus;
  if (*(collection+base + 42) == querytermid) score+=log(1 + *(tf+base + 42) / prob) + plus;
  if (*(collection+base + 43) == querytermid) score+=log(1 + *(tf+base + 43) / prob) + plus;

  return score;
}

double length45(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  if (*(collection+base + 41) == querytermid) score+=log(1 + *(tf+base + 41) / prob) + plus;
  if (*(collection+base + 42) == querytermid) score+=log(1 + *(tf+base + 42) / prob) + plus;
  if (*(collection+base + 43) == querytermid) score+=log(1 + *(tf+base + 43) / prob) + plus;
  if (*(collection+base + 44) == querytermid) score+=log(1 + *(tf+base + 44) / prob) + plus;

  return score;
}

double length46(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  if (*(collection+base + 41) == querytermid) score+=log(1 + *(tf+base + 41) / prob) + plus;
  if (*(collection+base + 42) == querytermid) score+=log(1 + *(tf+base + 42) / prob) + plus;
  if (*(collection+base + 43) == querytermid) score+=log(1 + *(tf+base + 43) / prob) + plus;
  if (*(collection+base + 44) == querytermid) score+=log(1 + *(tf+base + 44) / prob) + plus;
  if (*(collection+base + 45) == querytermid) score+=log(1 + *(tf+base + 45) / prob) + plus;

  return score;
}

double length47(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  if (*(collection+base + 41) == querytermid) score+=log(1 + *(tf+base + 41) / prob) + plus;
  if (*(collection+base + 42) == querytermid) score+=log(1 + *(tf+base + 42) / prob) + plus;
  if (*(collection+base + 43) == querytermid) score+=log(1 + *(tf+base + 43) / prob) + plus;
  if (*(collection+base + 44) == querytermid) score+=log(1 + *(tf+base + 44) / prob) + plus;
  if (*(collection+base + 45) == querytermid) score+=log(1 + *(tf+base + 45) / prob) + plus;
  if (*(collection+base + 46) == querytermid) score+=log(1 + *(tf+base + 46) / prob) + plus;

  return score;
}

double length48(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  if (*(collection+base + 41) == querytermid) score+=log(1 + *(tf+base + 41) / prob) + plus;
  if (*(collection+base + 42) == querytermid) score+=log(1 + *(tf+base + 42) / prob) + plus;
  if (*(collection+base + 43) == querytermid) score+=log(1 + *(tf+base + 43) / prob) + plus;
  if (*(collection+base + 44) == querytermid) score+=log(1 + *(tf+base + 44) / prob) + plus;
  if (*(collection+base + 45) == querytermid) score+=log(1 + *(tf+base + 45) / prob) + plus;
  if (*(collection+base + 46) == querytermid) score+=log(1 + *(tf+base + 46) / prob) + plus;
  if (*(collection+base + 47) == querytermid) score+=log(1 + *(tf+base + 47) / prob) + plus;

  return score;
}

double length49(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) {
  double score = 0;
  if (*(collection+base) == querytermid) score+=log(1 + *(tf+base) / prob) + plus;
  if (*(collection+base + 1) == querytermid) score+=log(1 + *(tf+base + 1) / prob) + plus;
  if (*(collection+base + 2) == querytermid) score+=log(1 + *(tf+base + 2) / prob) + plus;
  if (*(collection+base + 3) == querytermid) score+=log(1 + *(tf+base + 3) / prob) + plus;
  if (*(collection+base + 4) == querytermid) score+=log(1 + *(tf+base + 4) / prob) + plus;
  if (*(collection+base + 5) == querytermid) score+=log(1 + *(tf+base + 5) / prob) + plus;
  if (*(collection+base + 6) == querytermid) score+=log(1 + *(tf+base + 6) / prob) + plus;
  if (*(collection+base + 7) == querytermid) score+=log(1 + *(tf+base + 7) / prob) + plus;
  if (*(collection+base + 8) == querytermid) score+=log(1 + *(tf+base + 8) / prob) + plus;
  if (*(collection+base + 9) == querytermid) score+=log(1 + *(tf+base + 9) / prob) + plus;
  if (*(collection+base + 10) == querytermid) score+=log(1 + *(tf+base + 10) / prob) + plus;
  if (*(collection+base + 11) == querytermid) score+=log(1 + *(tf+base + 11) / prob) + plus;
  if (*(collection+base + 12) == querytermid) score+=log(1 + *(tf+base + 12) / prob) + plus;
  if (*(collection+base + 13) == querytermid) score+=log(1 + *(tf+base + 13) / prob) + plus;
  if (*(collection+base + 14) == querytermid) score+=log(1 + *(tf+base + 14) / prob) + plus;
  if (*(collection+base + 15) == querytermid) score+=log(1 + *(tf+base + 15) / prob) + plus;
  if (*(collection+base + 16) == querytermid) score+=log(1 + *(tf+base + 16) / prob) + plus;
  if (*(collection+base + 17) == querytermid) score+=log(1 + *(tf+base + 17) / prob) + plus;
  if (*(collection+base + 18) == querytermid) score+=log(1 + *(tf+base + 18) / prob) + plus;
  if (*(collection+base + 19) == querytermid) score+=log(1 + *(tf+base + 19) / prob) + plus;
  if (*(collection+base + 20) == querytermid) score+=log(1 + *(tf+base + 20) / prob) + plus;
  if (*(collection+base + 21) == querytermid) score+=log(1 + *(tf+base + 21) / prob) + plus;
  if (*(collection+base + 22) == querytermid) score+=log(1 + *(tf+base + 22) / prob) + plus;
  if (*(collection+base + 23) == querytermid) score+=log(1 + *(tf+base + 23) / prob) + plus;
  if (*(collection+base + 24) == querytermid) score+=log(1 + *(tf+base + 24) / prob) + plus;
  if (*(collection+base + 25) == querytermid) score+=log(1 + *(tf+base + 25) / prob) + plus;
  if (*(collection+base + 26) == querytermid) score+=log(1 + *(tf+base + 26) / prob) + plus;
  if (*(collection+base + 27) == querytermid) score+=log(1 + *(tf+base + 27) / prob) + plus;
  if (*(collection+base + 28) == querytermid) score+=log(1 + *(tf+base + 28) / prob) + plus;
  if (*(collection+base + 29) == querytermid) score+=log(1 + *(tf+base + 29) / prob) + plus;
  if (*(collection+base + 30) == querytermid) score+=log(1 + *(tf+base + 30) / prob) + plus;
  if (*(collection+base + 31) == querytermid) score+=log(1 + *(tf+base + 31) / prob) + plus;
  if (*(collection+base + 32) == querytermid) score+=log(1 + *(tf+base + 32) / prob) + plus;
  if (*(collection+base + 33) == querytermid) score+=log(1 + *(tf+base + 33) / prob) + plus;
  if (*(collection+base + 34) == querytermid) score+=log(1 + *(tf+base + 34) / prob) + plus;
  if (*(collection+base + 35) == querytermid) score+=log(1 + *(tf+base + 35) / prob) + plus;
  if (*(collection+base + 36) == querytermid) score+=log(1 + *(tf+base + 36) / prob) + plus;
  if (*(collection+base + 37) == querytermid) score+=log(1 + *(tf+base + 37) / prob) + plus;
  if (*(collection+base + 38) == querytermid) score+=log(1 + *(tf+base + 38) / prob) + plus;
  if (*(collection+base + 39) == querytermid) score+=log(1 + *(tf+base + 39) / prob) + plus;
  if (*(collection+base + 40) == querytermid) score+=log(1 + *(tf+base + 40) / prob) + plus;
  if (*(collection+base + 41) == querytermid) score+=log(1 + *(tf+base + 41) / prob) + plus;
  if (*(collection+base + 42) == querytermid) score+=log(1 + *(tf+base + 42) / prob) + plus;
  if (*(collection+base + 43) == querytermid) score+=log(1 + *(tf+base + 43) / prob) + plus;
  if (*(collection+base + 44) == querytermid) score+=log(1 + *(tf+base + 44) / prob) + plus;
  if (*(collection+base + 45) == querytermid) score+=log(1 + *(tf+base + 45) / prob) + plus;
  if (*(collection+base + 46) == querytermid) score+=log(1 + *(tf+base + 46) / prob) + plus;
  if (*(collection+base + 47) == querytermid) score+=log(1 + *(tf+base + 47) / prob) + plus;
  if (*(collection+base + 48) == querytermid) score+=log(1 + *(tf+base + 48) / prob) + plus;

  return score;
}

double (*array_fun[DOC_UNIQUE_TERM_LENGTH])(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus) = 
  {length0, length1, length2, length3, length4, length5, length6, length7, length8, length9, length10, length11, 
    length12, length13, length14, length15, length16, length17, length18, length19, length20, length21, 
    length22, length23, length24, length25, length26, length27, length28, length29, length30, length31, 
    length32, length33, length34, length35, length36, length37, length38, length39, length40, length41, 
    length42, length43, length44, length45, length46, length47, length48, length49};

void mapping() {
  int i;
  printf("-> Start mapping\n");
  for (i = 0; i < NUM_DOCS; i ++) {
    if (doclengths_ordered[i] == 0) {
      array_fun_direct[i] = length0;
    } else if (doclengths_ordered[i] == 1) {
      array_fun_direct[i] = length1;
    } else if (doclengths_ordered[i] == 2) {
      array_fun_direct[i] = length2;
    } else if (doclengths_ordered[i] == 3) {
      array_fun_direct[i] = length3;
    } else if (doclengths_ordered[i] == 4) {
      array_fun_direct[i] = length4;
    } else if (doclengths_ordered[i] == 5) {
      array_fun_direct[i] = length5;
    } else if (doclengths_ordered[i] == 6) {
      array_fun_direct[i] = length6;
    } else if (doclengths_ordered[i] == 7) {
      array_fun_direct[i] = length7;
    } else if (doclengths_ordered[i] == 8) {
      array_fun_direct[i] = length8;
    } else if (doclengths_ordered[i] == 9) {
      array_fun_direct[i] = length9;
    } else if (doclengths_ordered[i] == 10) {
      array_fun_direct[i] = length10;
    } else if (doclengths_ordered[i] == 11) {
      array_fun_direct[i] = length11;
    } else if (doclengths_ordered[i] == 12) {
      array_fun_direct[i] = length12;
    } else if (doclengths_ordered[i] == 13) {
      array_fun_direct[i] = length13;
    } else if (doclengths_ordered[i] == 14) {
      array_fun_direct[i] = length14;
    } else if (doclengths_ordered[i] == 15) {
      array_fun_direct[i] = length15;
    } else if (doclengths_ordered[i] == 16) {
      array_fun_direct[i] = length16;
    } else if (doclengths_ordered[i] == 17) {
      array_fun_direct[i] = length17;
    } else if (doclengths_ordered[i] == 18) {
      array_fun_direct[i] = length18;
    } else if (doclengths_ordered[i] == 19) {
      array_fun_direct[i] = length19;
    } else if (doclengths_ordered[i] == 20) {
      array_fun_direct[i] = length20;
    } else if (doclengths_ordered[i] == 21) {
      array_fun_direct[i] = length21;
    } else if (doclengths_ordered[i] == 22) {
      array_fun_direct[i] = length22;
    } else if (doclengths_ordered[i] == 23) {
      array_fun_direct[i] = length23;
    } else if (doclengths_ordered[i] == 24) {
      array_fun_direct[i] = length24;
    } else if (doclengths_ordered[i] == 25) {
      array_fun_direct[i] = length25;
    } else if (doclengths_ordered[i] == 26) {
      array_fun_direct[i] = length26;
    } else if (doclengths_ordered[i] == 27) {
      array_fun_direct[i] = length27;
    } else if (doclengths_ordered[i] == 28) {
      array_fun_direct[i] = length28;
    } else if (doclengths_ordered[i] == 29) {
      array_fun_direct[i] = length29;
    } else if (doclengths_ordered[i] == 30) {
      array_fun_direct[i] = length30;
    } else if (doclengths_ordered[i] == 31) {
      array_fun_direct[i] = length31;
    } else if (doclengths_ordered[i] == 32) {
      array_fun_direct[i] = length32;
    } else if (doclengths_ordered[i] == 33) {
      array_fun_direct[i] = length33;
    } else if (doclengths_ordered[i] == 34) {
      array_fun_direct[i] = length34;
    } else if (doclengths_ordered[i] == 35) {
      array_fun_direct[i] = length35;
    } else if (doclengths_ordered[i] == 36) {
      array_fun_direct[i] = length36;
    } else if (doclengths_ordered[i] == 37) {
      array_fun_direct[i] = length37;
    } else if (doclengths_ordered[i] == 38) {
      array_fun_direct[i] = length38;
    } else if (doclengths_ordered[i] == 39) {
      array_fun_direct[i] = length39;
    } else if (doclengths_ordered[i] == 40) {
      array_fun_direct[i] = length40;
    } else if (doclengths_ordered[i] == 41) {
      array_fun_direct[i] = length41;
    } else if (doclengths_ordered[i] == 42) {
      array_fun_direct[i] = length42;
    } else if (doclengths_ordered[i] == 43) {
      array_fun_direct[i] = length43;
    } else if (doclengths_ordered[i] == 44) {
      array_fun_direct[i] = length44;
    } else if (doclengths_ordered[i] == 45) {
      array_fun_direct[i] = length45;
    } else if (doclengths_ordered[i] == 46) {
      array_fun_direct[i] = length46;
    } else if (doclengths_ordered[i] == 47) {
      array_fun_direct[i] = length47;
    } else if (doclengths_ordered[i] == 48) {
      array_fun_direct[i] = length48;
    } else if (doclengths_ordered[i] == 49) {
      array_fun_direct[i] = length49;
    }
    if (i % 1000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms mapped\n\n", i);
}