#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"

double length1(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  return score;
}

double length2(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  return score;
}

double length3(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  return score;
}

double length4(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  return score;
}

double length5(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  return score;
}

double length6(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  return score;
}

double length7(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  return score;
}

double length8(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  return score;
}

double length9(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  return score;
}

double length10(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  return score;
}

double length11(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  return score;
}

double length12(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  return score;
}

double length13(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  return score;
}

double length14(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  return score;
}

double length15(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  return score;
}

double length16(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  return score;
}

double length17(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  return score;
}

double length18(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  return score;
}

double length19(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  return score;
}

double length20(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  return score;
}

double length21(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  return score;
}

double length22(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  return score;
}

double length23(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  return score;
}

double length24(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  return score;
}

double length25(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  return score;
}

double length26(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  return score;
}

double length27(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  return score;
}

double length28(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  return score;
}

double length29(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  return score;
}

double length30(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  return score;
}

double length31(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  return score;
}

double length32(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  return score;
}

double length33(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  return score;
}

double length34(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  return score;
}

double length35(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  return score;
}

double length36(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  return score;
}

double length37(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  return score;
}

double length38(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  return score;
}

double length39(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  return score;
}

double length40(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  return score;
}

double length41(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  return score;
}

double length42(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  if (*(collection+*base + 41) == *querytermid) score+=log10(1 + *(tf+*base + 41) / *prob) + *plus;
  return score;
}

double length43(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  if (*(collection+*base + 41) == *querytermid) score+=log10(1 + *(tf+*base + 41) / *prob) + *plus;
  if (*(collection+*base + 42) == *querytermid) score+=log10(1 + *(tf+*base + 42) / *prob) + *plus;
  return score;
}

double length44(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  if (*(collection+*base + 41) == *querytermid) score+=log10(1 + *(tf+*base + 41) / *prob) + *plus;
  if (*(collection+*base + 42) == *querytermid) score+=log10(1 + *(tf+*base + 42) / *prob) + *plus;
  if (*(collection+*base + 43) == *querytermid) score+=log10(1 + *(tf+*base + 43) / *prob) + *plus;

  return score;
}

double length45(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  if (*(collection+*base + 41) == *querytermid) score+=log10(1 + *(tf+*base + 41) / *prob) + *plus;
  if (*(collection+*base + 42) == *querytermid) score+=log10(1 + *(tf+*base + 42) / *prob) + *plus;
  if (*(collection+*base + 43) == *querytermid) score+=log10(1 + *(tf+*base + 43) / *prob) + *plus;
  if (*(collection+*base + 44) == *querytermid) score+=log10(1 + *(tf+*base + 44) / *prob) + *plus;

  return score;
}

double length46(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  if (*(collection+*base + 41) == *querytermid) score+=log10(1 + *(tf+*base + 41) / *prob) + *plus;
  if (*(collection+*base + 42) == *querytermid) score+=log10(1 + *(tf+*base + 42) / *prob) + *plus;
  if (*(collection+*base + 43) == *querytermid) score+=log10(1 + *(tf+*base + 43) / *prob) + *plus;
  if (*(collection+*base + 44) == *querytermid) score+=log10(1 + *(tf+*base + 44) / *prob) + *plus;
  if (*(collection+*base + 45) == *querytermid) score+=log10(1 + *(tf+*base + 45) / *prob) + *plus;

  return score;
}

double length47(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  if (*(collection+*base + 41) == *querytermid) score+=log10(1 + *(tf+*base + 41) / *prob) + *plus;
  if (*(collection+*base + 42) == *querytermid) score+=log10(1 + *(tf+*base + 42) / *prob) + *plus;
  if (*(collection+*base + 43) == *querytermid) score+=log10(1 + *(tf+*base + 43) / *prob) + *plus;
  if (*(collection+*base + 44) == *querytermid) score+=log10(1 + *(tf+*base + 44) / *prob) + *plus;
  if (*(collection+*base + 45) == *querytermid) score+=log10(1 + *(tf+*base + 45) / *prob) + *plus;
  if (*(collection+*base + 46) == *querytermid) score+=log10(1 + *(tf+*base + 46) / *prob) + *plus;

  return score;
}

double length48(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  if (*(collection+*base + 41) == *querytermid) score+=log10(1 + *(tf+*base + 41) / *prob) + *plus;
  if (*(collection+*base + 42) == *querytermid) score+=log10(1 + *(tf+*base + 42) / *prob) + *plus;
  if (*(collection+*base + 43) == *querytermid) score+=log10(1 + *(tf+*base + 43) / *prob) + *plus;
  if (*(collection+*base + 44) == *querytermid) score+=log10(1 + *(tf+*base + 44) / *prob) + *plus;
  if (*(collection+*base + 45) == *querytermid) score+=log10(1 + *(tf+*base + 45) / *prob) + *plus;
  if (*(collection+*base + 46) == *querytermid) score+=log10(1 + *(tf+*base + 46) / *prob) + *plus;
  if (*(collection+*base + 47) == *querytermid) score+=log10(1 + *(tf+*base + 47) / *prob) + *plus;

  return score;
}

double length49(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) {
  double score = 0;
  if (*(collection+*base) == *querytermid) score+=log10(1 + *(tf+*base) / *prob) + *plus;
  if (*(collection+*base + 1) == *querytermid) score+=log10(1 + *(tf+*base + 1) / *prob) + *plus;
  if (*(collection+*base + 2) == *querytermid) score+=log10(1 + *(tf+*base + 2) / *prob) + *plus;
  if (*(collection+*base + 3) == *querytermid) score+=log10(1 + *(tf+*base + 3) / *prob) + *plus;
  if (*(collection+*base + 4) == *querytermid) score+=log10(1 + *(tf+*base + 4) / *prob) + *plus;
  if (*(collection+*base + 5) == *querytermid) score+=log10(1 + *(tf+*base + 5) / *prob) + *plus;
  if (*(collection+*base + 6) == *querytermid) score+=log10(1 + *(tf+*base + 6) / *prob) + *plus;
  if (*(collection+*base + 7) == *querytermid) score+=log10(1 + *(tf+*base + 7) / *prob) + *plus;
  if (*(collection+*base + 8) == *querytermid) score+=log10(1 + *(tf+*base + 8) / *prob) + *plus;
  if (*(collection+*base + 9) == *querytermid) score+=log10(1 + *(tf+*base + 9) / *prob) + *plus;
  if (*(collection+*base + 10) == *querytermid) score+=log10(1 + *(tf+*base + 10) / *prob) + *plus;
  if (*(collection+*base + 11) == *querytermid) score+=log10(1 + *(tf+*base + 11) / *prob) + *plus;
  if (*(collection+*base + 12) == *querytermid) score+=log10(1 + *(tf+*base + 12) / *prob) + *plus;
  if (*(collection+*base + 13) == *querytermid) score+=log10(1 + *(tf+*base + 13) / *prob) + *plus;
  if (*(collection+*base + 14) == *querytermid) score+=log10(1 + *(tf+*base + 14) / *prob) + *plus;
  if (*(collection+*base + 15) == *querytermid) score+=log10(1 + *(tf+*base + 15) / *prob) + *plus;
  if (*(collection+*base + 16) == *querytermid) score+=log10(1 + *(tf+*base + 16) / *prob) + *plus;
  if (*(collection+*base + 17) == *querytermid) score+=log10(1 + *(tf+*base + 17) / *prob) + *plus;
  if (*(collection+*base + 18) == *querytermid) score+=log10(1 + *(tf+*base + 18) / *prob) + *plus;
  if (*(collection+*base + 19) == *querytermid) score+=log10(1 + *(tf+*base + 19) / *prob) + *plus;
  if (*(collection+*base + 20) == *querytermid) score+=log10(1 + *(tf+*base + 20) / *prob) + *plus;
  if (*(collection+*base + 21) == *querytermid) score+=log10(1 + *(tf+*base + 21) / *prob) + *plus;
  if (*(collection+*base + 22) == *querytermid) score+=log10(1 + *(tf+*base + 22) / *prob) + *plus;
  if (*(collection+*base + 23) == *querytermid) score+=log10(1 + *(tf+*base + 23) / *prob) + *plus;
  if (*(collection+*base + 24) == *querytermid) score+=log10(1 + *(tf+*base + 24) / *prob) + *plus;
  if (*(collection+*base + 25) == *querytermid) score+=log10(1 + *(tf+*base + 25) / *prob) + *plus;
  if (*(collection+*base + 26) == *querytermid) score+=log10(1 + *(tf+*base + 26) / *prob) + *plus;
  if (*(collection+*base + 27) == *querytermid) score+=log10(1 + *(tf+*base + 27) / *prob) + *plus;
  if (*(collection+*base + 28) == *querytermid) score+=log10(1 + *(tf+*base + 28) / *prob) + *plus;
  if (*(collection+*base + 29) == *querytermid) score+=log10(1 + *(tf+*base + 29) / *prob) + *plus;
  if (*(collection+*base + 30) == *querytermid) score+=log10(1 + *(tf+*base + 30) / *prob) + *plus;
  if (*(collection+*base + 31) == *querytermid) score+=log10(1 + *(tf+*base + 31) / *prob) + *plus;
  if (*(collection+*base + 32) == *querytermid) score+=log10(1 + *(tf+*base + 32) / *prob) + *plus;
  if (*(collection+*base + 33) == *querytermid) score+=log10(1 + *(tf+*base + 33) / *prob) + *plus;
  if (*(collection+*base + 34) == *querytermid) score+=log10(1 + *(tf+*base + 34) / *prob) + *plus;
  if (*(collection+*base + 35) == *querytermid) score+=log10(1 + *(tf+*base + 35) / *prob) + *plus;
  if (*(collection+*base + 36) == *querytermid) score+=log10(1 + *(tf+*base + 36) / *prob) + *plus;
  if (*(collection+*base + 37) == *querytermid) score+=log10(1 + *(tf+*base + 37) / *prob) + *plus;
  if (*(collection+*base + 38) == *querytermid) score+=log10(1 + *(tf+*base + 38) / *prob) + *plus;
  if (*(collection+*base + 39) == *querytermid) score+=log10(1 + *(tf+*base + 39) / *prob) + *plus;
  if (*(collection+*base + 40) == *querytermid) score+=log10(1 + *(tf+*base + 40) / *prob) + *plus;
  if (*(collection+*base + 41) == *querytermid) score+=log10(1 + *(tf+*base + 41) / *prob) + *plus;
  if (*(collection+*base + 42) == *querytermid) score+=log10(1 + *(tf+*base + 42) / *prob) + *plus;
  if (*(collection+*base + 43) == *querytermid) score+=log10(1 + *(tf+*base + 43) / *prob) + *plus;
  if (*(collection+*base + 44) == *querytermid) score+=log10(1 + *(tf+*base + 44) / *prob) + *plus;
  if (*(collection+*base + 45) == *querytermid) score+=log10(1 + *(tf+*base + 45) / *prob) + *plus;
  if (*(collection+*base + 46) == *querytermid) score+=log10(1 + *(tf+*base + 46) / *prob) + *plus;
  if (*(collection+*base + 47) == *querytermid) score+=log10(1 + *(tf+*base + 47) / *prob) + *plus;
  if (*(collection+*base + 48) == *querytermid) score+=log10(1 + *(tf+*base + 48) / *prob) + *plus;

  return score;
}

double (*array_fun[DOC_LENGTH])(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus) = 
  {length1, length2, length3, length4, length5, length6, length7, length8, length9, length10, length11, 
    length12, length13, length14, length15, length16, length17, length18, length19, length20, length21, 
    length22, length23, length24, length25, length26, length27, length28, length29, length30, length31, 
    length32, length33, length34, length35, length36, length37, length38, length39, length40, length41, 
    length42, length43, length44, length45, length46, length47, length48, length49};