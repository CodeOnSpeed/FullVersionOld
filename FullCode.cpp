#include<cstdlib>
#include<cstdio>
#include<limits.h>
#include<windows.h>
#include <cmath>    //For ln
#include <chrono>   //For timing stuff
#include <cstring>  //For memcypy for unoptimised memcpy_64
#include <cmath>    //For log for unoptimized DEPTH
#include <iostream> //For cin in testing::interactive | TODO: remove this dependency
#include <limits>   //For inf und -inf in internal::negamax
#include <alloca.h>

enum{EMPTY, PAWN_WHITE, PAWN_BLACK, KNIGHT_WHITE, KNIGHT_BLACK, BISHOP_WHITE, BISHOP_BLACK, ROOK_WHITE, ROOK_BLACK, QUEEN_WHITE, QUEEN_BLACK, KING_WHITE, KING_BLACK};
#define MATERIAL 35
#define CONNECT 6
#define OPENLINE 9
#define PASSED 18
#define SEVENTH 15
#define PROTEC 3
#define END_PAWN 4
#define CENTER 15
#define KING_POS 7
#define QUEEN_MOD 2
#define BISHOP_MOD 2
#define KNIGHT_STRENGTH 10
//char *globalfeld = (char *) malloc(sizeof(char) * 65);

#define DROPOUT_DEPTH 2
#define TIME_TYPE long long
#define BOARD char*
#define BOARDS char*
#define EVAL_TYPE int
#define MAX_NEXT_NODES 128
#define NEXT_MOVES_TYPE int

#define IND(r,c) (8*c+r)


long long int count = 0;
//int k = 0
//int *a = (char *) malloc(sizeof(int) * 32);
int max(char*, int, int, int);
int min(char*, int, int, int);
int possible_moves = 0;
char *globalfeld = (char *) malloc(sizeof(char) * 66);

char max_4(char v1, char v2, char v3, char v4){
  char ret = v1;
  ret = (ret>v1) ? ret : v2;
  ret = (ret>v2) ? ret : v3;
  ret = (ret>v3) ? ret : v4;
  return ret;
}

char min_2(char v1, char v2){
  char ret = (v1>v2) ? v2 : v1;
  return ret;
}

char max_2(char v1, char v2){
  char ret = (v1>v2) ? v1 : v2;
  return ret;
}
/*
int get_max_a(){
  int prev = 0;
  int i = 0;
  while(a != INT_MAX-4){
    if(*(a+i) < prev){
      prev = *(a+i++);
    }
  }
}*/
char *moves_bishop(char *feld, char f, bool is){
  char *res = (char *) malloc(sizeof(char) * 32);
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  int j = 0;
  char i1 = 7-(f&7);
  char i2 = (f&7);
  char i3 = 7-(f>>3);
  char i4 = (f>>3);
  if(is == true){
    for(int i = 1; i <= min_2(i2, i4); i++){
      if((*(feld + f - i*9)&1) == 1){
	break;
      }
      else if(*(feld + f - i*9) == 0){
	res[j++] = f - i*9;
      }
      else{
	res[j++] = f - i*9;
	break;
      }
    }
    for(int i = 1; i <= min_2(i2, i3); i++){
      if((*(feld + f + i*7)&1) == 1){
	break;
      }
      else if(*(feld + f + i*7) == 0){
	res[j++] = f + i*7;
      }
      else{
	res[j++] = f + i*7;
	break;
      }
    }
    for(int i = 1; i <= min_2(i1, i4); i++){
      if((*(feld + f - i*7)&1) == 1){
	break;
      }
      else if(*(feld + f - i*7) == 0){
	res[j++] = f - i*7;
      }
      else{
	res[j++] = f - i*7;
	break;
      }
    }
    for(int i = 1; i <= min_2(i1, i3); i++){
      if((*(feld + f + i*9)&1) == 1){
	break;
      }
      else if(*(feld + f + i*9) == 0){
	res[j++] = f + i*9;
      }
      else{
	res[j++] = f + i*9;
	break;
      }
    }
  }
  else{
    for(int i = 1; i <= min_2(i2, i4); i++){
      if((*(feld + f - i*9)) == 0){
	res[j++] = f - i*9;
      }
      else if((*(feld + f - i*9)&1) == 0){
	break;
      }
      else{
	res[j++] = f - i*9;
	break;
      }
    }
    for(int i = 1; i <= min_2(i2, i3); i++){
      if(*(feld + f + i*7) == 0){
	res[j++] = f + i*7;
      }
      else if((*(feld + f + i*7)&1) == 0){
	break;
      }
      else{
	res[j++] = f + i*7;
	break;
      }
    }
    for(int i = 1; i <= min_2(i1, i4); i++){
      if((*(feld + f - i*7)) == 0){
	res[j++] = f - i*7;
      }
      else if((*(feld + f - i*7)&1) == 0){
	break;
      }
      else{
	res[j++] = f - i*7;
	break;
      }
    }
    for(int i = 1; i <= min_2(i1, i3); i++){
      if(*(feld + f + i*9) == 0){
	res[j++] = f + i*9;
      }
      else if((*(feld + f + i*9)&1) == 0){
	break;
      }
      else{
	res[j++] = f + i*9;
	break;
      }
    }
  }
  return res;
}
//FIXIT
char *moves_rook(char *feld, char f, bool is){
  char *res = (char *) malloc(sizeof(char) * 32);
  int j = 0;
  char i1 = 7-(f&7);
  char i2 = (f&7);
  char i3 = 7-(f>>3);
  char i4 = (f>>3);
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  if(is == true){
    for(int i = 1; i <= i2; i++){
      if(*(feld + f - i) == 0){
	res[j++] = f - i;
      }
      else if((*(feld + f - i)&1) == 1){
	break;
      }
      else{
	res[j++] = f - i;
	break;
      }
    }
    for(int i = 1; i <= i1; i++){
      if(*(feld + f + i) == 0){
	res[j++] = f + i;
      }
      else if((*(feld + f + i)&1) == 1){
	break;
      }
      else{
	res[j++] = f + i;
	break;
      }
    }
    for(int i = 1; i <= i4; i++){
      if(*(feld + f - 8*i) == 0){
	res[j++] = f - 8*i;
      }
      else if((*(feld + f - 8*i)&1) == 1){
	break;
      }
      else{
	res[j++] = f - 8*i;
	break;
      }
    }
    for(int i = 1; i <= i3; i++){
      if(*(feld + f + 8*i) == 0){
	res[j++] = f + 8*i;
      }
      else if((*(feld + f + 8*i)&1) == 1){
	break;
      }
      else{
	res[j++] = f + 8*i;
	break;
      }
    }
  }
  else{
    for(int i = 1; i <= i2; i++){
      if(*(feld + f - i) == 0){
	res[j++] = f - i;
      }
      else if((*(feld + f - i)&1) == 0){
	break;
      }
      else{
	res[j++] = f - i;
	break;
      }
    }
    for(int i = 1; i <= i1; i++){
      if(*(feld + f + i) == 0){
	res[j++] = f + i;
      }
      else if((*(feld + f + i)&1) == 0){
	break;
      }
      else{
	res[j++] = f + i;
	break;
      }
    }
    for(int i = 1; i <= i4; i++){
      if(*(feld + f - 8*i) == 0){
	res[j++] = f - 8*i;
      }
      else if((*(feld + f - 8*i)&1) == 0){
	break;
      }
      else{
	res[j++] = f - 8*i;
	break;
      }
    }
    for(int i = 1; i <= i3; i++){
      if(*(feld + f + 8*i) == 0){
	res[j++] = f + 8*i;
      }
      else if((*(feld + f + 8*i)&1) == 0){
	break;
      }
      else{
	res[j++] = f + 8*i;
	break;
      }
    }
  }
  return res;
}

char *moves_pawn(char *feld, char f, bool is){
  char *res = (char *) malloc(sizeof(char) * 32);
  int i = 0;
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  i = 0;
  if(is == true){
    if((f&7) == 1){
      if(*(feld + f + 1) == EMPTY){
	res[i++] = f + 1;
	if(*(feld + f + 2) == EMPTY){
	  res[i++] = f + 2;
	}
      }
      if(f > 8){
	if(*(feld + f - 7) == 0){
	  ;
	}
	else if((*(feld + f - 7) & 1) == 0){
	  res[i++] = f - 7;
	}
      }
      if(*(feld + f + 9) == 0);
      else if(f < 55 && (*(feld + f + 9) & 1) == 0){
	res[i++] = f + 9;
      }
    }
    else{
      if(*(feld + f + 1) == EMPTY){
	res[i++] = f + 1;
      }
      if(*(feld + f - 7) == 0);
      else if(f > 7 && (*(feld + f - 7) & 1) == 0){
	res[i++] = f - 7;
      }
      if(*(feld + f + 9) == 0);
      else if(f < 56 && (*(feld + f + 9) & 1) == 0){
	res[i++] = f + 9;
      }
    }
  }
  else{
    if((f&7) == 6){
      if(*(feld + f - 1) == EMPTY){
	res[i++] = f - 1;
	if(*(feld + f - 2) == EMPTY){
	  res[i++] = f - 2;
	}
      }
      if(f < 56){
	if((*(feld + f + 7) & 1) == 1){
	  res[i++] = f + 7;
	}
      }
      if(f > 9 && (*(feld + f - 9) & 1) == 1){
	res[i++] = f - 9;
      }
    }
    else{
      if(*(feld + f - 1) == EMPTY){
	res[i++] = f - 1;
      }
      if(f > 9 && (*(feld + f - 9) & 1) == 1){
	res[i++] = f - 9;
      }
      if(f < 56 && (*(feld + f + 7) & 1) == 1){
	res[i++] = f + 7;
      }
    }
  }
  return res;
}

char *moves_knight(char *feld, char f, bool is){
  int i = 0;
  char *res = (char *) malloc(sizeof(char) * 32);
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  if(is == true){
    if(f+2*8 < 63){
      if(((f+1)&7) > (f&7)){
	if((*(feld + f + 2*8 + 1)&1) == 0){
	  res[i++] = f + 2*8 + 1;
	}
      }
      if(((f-1)&7) < (f&7)){
	if((*(feld + f + 2*8 - 1)&1) == 0){
	  res[i++] = f + 2*8 - 1;
	}
      }
    }
    if(f-2*8 >= 0){
      if(((f+1)&7) > (f&7)){
	if((*(feld + f - 2*8 + 1)&1) == 0){
	  res[i++] = f - 2*8 + 1;
	}
      }
      if(((f-1)&7) < (f&7)){
	if((*(feld + f - 2*8 - 1)&1) == 0){
	  res[i++] = f - 2*8 - 1;
	}
      }
    }
    if(f+8 < 64){
      if(((f+2)&7) > (f&7)){
	if((*(feld + f + 1*8 + 2)&1) == 0){
	  res[i++] = f + 1*8 + 2;
	}
      }
      if(((f-2)&7) < (f&7)){
	if((*(feld + f + 1*8 - 2)&1) == 0){
	  res[i++] = f + 1*8 - 2;
	}
      }
    }
    if(f-8 >= 0){
      if(((f+2)&7) > (f&7)){
	if((*(feld + f - 1*8 + 2)&1) == 0){
	  res[i++] = f - 1*8 + 2;
	}
      }
      if(((f-2)&7) < (f&7)){
	if((*(feld + f - 1*8 - 2)&1) == 0){
	  res[i++] = f - 1*8 - 2;
	}
      }
    }
  }
  else{
    if(f+2*8 < 64){
      if(((f+1)&7) > (f&7)){
	if((*(feld + f + 2*8 + 1)&1) == 1 || *(feld + f +2*8 + 1) == 0){
	  res[i++] = f + 2*8 + 1;
	}
      }
      if(((f-1)&7) < (f&7)){
	if((*(feld + f + 2*8 - 1)&1) == 1 || *(feld + f +2*8 - 1) == 0){
	  res[i++] = f + 2*8 - 1;
	}
      }
    }
    if(f-2*8 >= 0){
      if(((f+1)&7) > (f&7)){
	if((*(feld + f - 2*8 + 1)&1) == 1 || *(feld + f -2*8 + 1) == 0){
	  res[i++] = f - 2*8 + 1;
	}
      }
      if(((f-1)&7) < (f&7)){
	if((*(feld + f - 2*8 - 1)&1) == 1 || *(feld + f -2*8 - 1) == 0){
	  res[i++] = f - 2*8 - 1;
	}
      }
    }
    if(f+8 <= 63){
      if(((f+2)&7) > (f&7)){
	if((*(feld + f + 1*8 + 2)&1) == 1 || *(feld + f +1*8 + 2) == 0){
	  res[i++] = f + 1*8 + 2;
	}
      }
      if(((f-2)&7) < (f&7)){
	if((*(feld + f + 1*8 - 2)&1) == 1 ||*(feld + f +1*8 - 2) == 0){
	  res[i++] = f + 1*8 - 2;
	}
      }
    }
    if(f-8 >= 0){
      if(((f+2)&7) > (f&7)){
	if((*(feld + f - 1*8 + 2)&1) == 1 || *(feld + f -1*8 + 2) == 0){
	  res[i++] = f - 1*8 + 2;
	}
      }
      if(((f-2)&7) < (f&7)){
	if((*(feld + f - 1*8 - 2)&1) == 1 || *(feld + f -1*8 - 2) == 0){
	  res[i++] = f - 1*8 - 2;
	}
      }
    }
  }
  return res;
}

char *moves_king(char *feld, char f, bool is){
  char *res = (char *) malloc(sizeof(char) * 32);
  char i1 = (f&7);
  char i3 = (f>>3);
  int j = 0;
  for(int i = 0; i < 32; i++){
    *(res + i) = -1;
  }
  if(is == true){
    if((i1 < 7)){
      if((*(feld + f + 1)&1) == 0){
	res[j++] = f + 1;
      }
      if(i3 < 7){
	if((*(feld + f + 8)&1) == 0){
	  res[j++] = f + 8;
	}
	if((*(feld + f + 9)&1) == 0){
	  res[j++] = f + 9;
	}
	if(i1 > 0){
	  if((*(feld + f + 7)&1) == 0){
	    res[j++] = f + 7;
	  }
	  if((*(feld + f - 1)&1) == 0){
	    res[j++] = f - 1;
	  }
	}
      }
      if(i3>0){
	if((*(feld + f - 8)&1) == 0){
	  res[j++] = f - 8;
	}
	if((*(feld + f - 7)&1) == 0){
	  res[j++] = f - 7;
	}
	if(i1 > 0){
	  if((*(feld + f - 9)&1) == 0){
	    res[j++] = f - 9;
	  }
	}
      }
    }
    else if(i3 > 0){ 
      if((*(feld + f - 1)&1) == 0){
	res[j++] = f - 1;
      }
      if((*(feld + f - 8)&1) == 0){
	res[j++] = f - 8;
      }
      if((*(feld + f - 9)&1) == 0){
	res[j++] = f - 9;
      }
      if(i3 < 7){
	if((*(feld + f + 8)&1) == 0){
	  res[j++] = f + 8;
	}
	if((*(feld + f + 7)&1) == 0){
	  res[j++] = f + 7;
	}
      }
    }
    else{
      if((*(feld + f - 1)&1) == 0){
	res[j++] = f - 1;
      }
      if((*(feld + f + 8)&1) == 0){
	res[j++] = f + 8;
      }
      if((*(feld + f + 9)&1) == 0){
	res[j++] = f + 9;
      }
    }
  }
  else{
    if((i1 < 7)){
      if((*(feld + f + 1)&1) == 1 || *(feld + f + 1) == 0){
	res[j++] = f + 1;
      }
      if(i3 < 7){
	if((*(feld + f + 8)&1) == 1 || *(feld + f + 8) == 0 ){
	  res[j++] = f + 8;
	}
	if((*(feld + f + 9)&1) == 1 || *(feld + f + 9) == 0){
	  res[j++] = f + 9;
	}
	if(i1 > 0){
	  if((*(feld + f + 7)&1) == 1 || *(feld + f + 7) == 0){
	    res[j++] = f + 7;
	  }
	  if((*(feld + f - 1)&1) == 1 || *(feld + f - 1) == 0 ){
	    res[j++] = f - 1;
	  }
	}
      }
      if(i3>0){
	if((*(feld + f - 8)&1) == 1 || *(feld + f - 8) == 0 ){
	  res[j++] = f - 8;
	}
	if((*(feld + f - 7)&1) == 1 || *(feld + f - 7) == 0){
	  res[j++] = f - 7;
	}
	if(i1 > 0){
	  if((*(feld + f - 9)&1) == 1 || *(feld + f - 9) == 0){
	    res[j++] = f - 9;
	  }
	}
      }
    }
    else if(i3 > 0){
      if((*(feld + f - 1)&1) == 1 || *(feld + f - 1) == 0){
	res[j++] = f - 1;
      }
      if((*(feld + f - 8)&1) == 1 || *(feld + f - 8) == 0){
	res[j++] = f - 8;
      }
      if((*(feld + f - 9)&1) == 1 || *(feld + f - 9) == 0){
      res[j++] = f - 9;
      }
      if(i3 < 7){
	if((*(feld + f + 8)&1) == 1 || *(feld + f + 8) == 0){
	  res[j++] = f + 8;
	}
	if((*(feld + f + 7)&1) == 1 || *(feld + f + 7) == 0){
	  res[j++] = f + 7;
	}
      }
    }
    else{
      if((*(feld + f - 1)&1) == 1 || *(feld + f - 1) == 0){
	res[j++] = f - 1;
      }
      if((*(feld + f + 8)&1) == 1 || *(feld + f + 8) == 0){
	res[j++] = f + 8;
      }
      if((*(feld + f + 7)&1) == 1 || *(feld + f + 7) == 0){
	res[j++] = f + 7;
      }
    }
  }
  return res;
}
char *moves_queen(char *feld, char f, bool is){
  char *ret = (char *) malloc(sizeof(char) * 32);
  char *temp = (char *) malloc(sizeof(char) * 16);
  int j = 0;
  for(int i = 0; i < 32; i++){
    *(ret + i) = -1;
  }
  temp = moves_bishop(feld, f, is);
  ret = moves_rook(feld, f, is);
  while(*(ret + (j++)) >= 0);
  for(int i = 0; i < 16; i++){
    *(ret + i + j - 1) = *(temp + i);
  }
  free(temp);
  return ret;
}
char *next_positions(char *feld, bool is){
  count++;
  char king_flag_white = 0;
  int i;
  char king_flag_black = 0;
  char *ret = (char *) malloc(sizeof(char) * 66 * 100);
  char *save = (char *) malloc(sizeof(char) * 32);
  int j2 = 0;
  int j = 0;
  if(is == true){
    for(int ii = 16; ii < 80; ii++){
      i = ii % 64;
      /*if(ii < 24){
	i = ii + 24;
      }
      else if(ii < 32){
	i = ii - 8;
      }
      else if(ii < 40){
	i = ii + 16;
      }
      else if(ii < 48){
	i = ii - 32;
      }
      else if(ii < 56){
	i = ii + 8;
      }
      else{
	i = ii - 56;
	}*/
      if(*(feld + i) == KING_BLACK){
	king_flag_black = 1;
	continue;
      }
      else if((*(feld + i)&1) == 0){
	continue;
      }
      else if(*(feld + i) == PAWN_WHITE){
	save = moves_pawn(feld, i, true);
	while(*(save + j)  >= 0){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);;
	  }
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = PAWN_WHITE;
	  if(*(save + j) - i == 2){
	    *(ret + 65 + (j2)*66) -= (*(ret + 65 + (j2)*66)&0b1111);
	    *(ret + 65 + (j2)*66) += 1 + 2*(i>>3);
	  }
	  if((*(save + j)&7) == 7){
	    *(ret + *(save + j) + (j2)*66) = QUEEN_WHITE;
	  }
	  j2++;
	  j++;
	}
	if((*(feld + 65)&1) == 1){
	  if((i&7) == 4 && ((i>>3) == ((*(feld + 65)&0b1110)>>1) - 1)){
	    for(int i1 = 0; i1 < 66; i1++){
	      *(ret + i1 + (j2)*66) = *(feld + i1);
	    }
	    *(ret + i + (j2)*66) = 0;
	    *(ret + 65 + (j2)*66) -= 1;
	    *(ret + i + 9 + (j2++)*66) = PAWN_WHITE;
	  }
	  else if((i&7) == 4 && (i>>3) == ((*(feld + 65)&0b1110)>>1) + 1){
	    for(int i1 = 0; i1 < 66; i1++){
	      *(ret + i1 + (j2)*66) = *(feld + i1);
	    }
	    *(ret + i + (j2)*66) = 0;
	    *(ret + 65 + (j2)*66) -= 1;
	    *(ret + i - 7 + (j2++)*66) = PAWN_WHITE;
	  }
	}//
	/*if(((*save)&7) == 7){
	  *(ret + i) = 0;
	  *(ret + *save + (j2++)*66) = QUEEN_WHITE;
	  }*/
      }
      else if(*(feld + i) == KNIGHT_WHITE){
	save = moves_knight(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = KNIGHT_WHITE;
	  j++;
	  *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == BISHOP_WHITE){
	save = moves_bishop(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = BISHOP_WHITE;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == ROOK_WHITE){
	save = moves_rook(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = ROOK_WHITE;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == QUEEN_WHITE){
	save = moves_queen(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = QUEEN_WHITE;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == KING_WHITE){
	king_flag_white = 1;
	save = moves_king(feld, i, true);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = KING_WHITE;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      j = 0;
    }
  }
  else{
    for(int ii = 16; ii < 80; ii++){
      i = ii % 64;
      /*if(ii < 24){
	i = ii + 24;
      }
      else if(ii < 32){
	i = ii - 8;
      }
      else if(ii < 40){
	i = ii + 16;
      }
      else if(ii < 48){
	i = ii - 32;
      }
      else if(ii < 56){
	i = ii + 8;
      }
      else{
	i = ii - 56;
	}*/
      if(*(feld + i) == KING_WHITE){
	king_flag_white = 1;
	continue;
      }
      if(*(feld + i) == EMPTY ||(*(feld + i)&1) == 1){
	continue;
      }
      else if(*(feld + i) == PAWN_BLACK){
	save = moves_pawn(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = PAWN_BLACK;
	  if(*(save + j) - i == -2){
	    *(ret + 65 + (j2)*66) -= (*(ret + 65 + (j2)*66)&0b1111);
	    *(ret + 65 + (j2)*66) += 1 + 2*(i>>3);
	  }
	  if((*(save + j)&7) == 0){
	    *(ret + *(save + j) + (j2)*66) = QUEEN_BLACK;
	  }
	  j++;
	  j2++;
	}
	if((*(feld + 65)&1) == 1){
	  if((i&7) == 3 && ((i>>3) == ((*(feld + 65)&0b1110)>>1) - 1)){
	    for(int i1 = 0; i1 < 66; i1++){
	      *(ret + i1 + (j2)*66) = *(feld + i1);
	    }
	    *(ret + i + (j2)*66) = 0;
	    *(ret + 65 + (j2)*66) -= 1;
	    *(ret + i + 7 + (j2++)*66) = PAWN_BLACK;
	  }
	  else if((i&7) == 3 && (i>>3) == ((*(feld + 65)&0b1110)>>1) + 1){
	    for(int i1 = 0; i1 < 66; i1++){
	      *(ret + i1 + (j2)*66) = *(feld + i1);
	    }
	    *(ret + i + (j2)*66) = 0;
	    *(ret + 65 + (j2)*66) -= 1;
	    *(ret + i - 9 + (j2++)*66) = PAWN_BLACK;
	  }
	}
	/*if(((*save)&7) == 0){
	  *(ret + i) = 0;
	  *(ret + *save + (j2++)*66) = QUEEN_BLACK;
	  }*/
      }
      else if(*(feld + i) == KNIGHT_BLACK){
	save = moves_knight(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	  *(ret + i + (j2)*66) = 0;
	  *(ret + *(save + j) + (j2)*66) = KNIGHT_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == BISHOP_BLACK){
	save = moves_bishop(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	      *(ret + i + (j2)*66) = 0;
	      *(ret + *(save + j) + (j2)*66) = BISHOP_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == ROOK_BLACK){
	save = moves_rook(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	      *(ret + i + (j2)*66) = 0;
	      *(ret + *(save + j) + (j2)*66) = ROOK_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == QUEEN_BLACK){
	save = moves_queen(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	      *(ret + i + (j2)*66) = 0;
	      *(ret + *(save + j) + (j2)*66) = QUEEN_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      else if(*(feld + i) == KING_BLACK){
	king_flag_black = 1;
	save = moves_king(feld, i, false);
	while(*(save + j) != -1){
	  for(int i1 = 0; i1 < 66; i1++){
	    *(ret + i1 + (j2)*66) = *(feld + i1);
	  }
	  
	      *(ret + i + (j2)*66) = 0;
	      *(ret + *(save + j) + (j2)*66) = KING_BLACK;
	  j++;
	   *(ret + 65 + (j2++)*66) = 0;
	}
      }
      j=0;
    }
  }
  if(king_flag_white == 0 || king_flag_black == 0){
    possible_moves = 0;
  }
  else{
    possible_moves = j2;
  }
  free(save);
  return ret;
}
/* c__attribute__((always_inline))*/int eval(char *feld /*protec*/){
  int material_weiss = 0;
  int material_schwarz = 0;
  char koenig_schwarz_b = 0;
  char koenig_weiss_b = 0;
  char flag = 0;
  char flag1 = 0;
  char flag2 = 0;
  char flag3 = 0;
  char flag4 = 0;
  char *pawn_white = (char *) alloca(sizeof(char) * 8);
  int j1 = 0;
  char *knight_white = (char *) alloca(sizeof(char) * 2);
  int j2 = 0;
  char *bishop_white = (char *) alloca(sizeof(char) * 2);
  int j3 = 0;
  char *rook_white = (char *) alloca(sizeof(char) * 2);
  int j4 = 0;
  char *queen_white = (char *) alloca(sizeof(char) * 2);
  char queen_white_free = 0;
  char queen_black_free = 0;
  *(queen_white) = 0;
  *(queen_white + 1) = 0;
  char king_white;
  char *pawn_black = (char *) alloca(sizeof(char) * 8);
  int j5 = 0;
  char *knight_black = (char *) alloca(sizeof(char) * 2);
  int j6 = 0;
  char *bishop_black = (char *) alloca(sizeof(char) * 2);
  int j7 = 0;
  char *rook_black = (char *) alloca(sizeof(char) * 2);
  int j8 = 0;
  char *queen_black = (char *) alloca(sizeof(char) * 2);
  *knight_black = 0;
  *knight_white = 0;
  char king_black;
  char bishop_black_free = 0;
  char bishop_white_free = 0;
  char connect_rooks_white = 0;
  char connect_rooks_black = 0;
  char seventh_white = 0;
  char seventh_black = 0;
  char knight_pos_white = 0;
  char knight_pos_black = 0;
  char temp1;
  char temp2;
  char temp_feld;
  char temp = 0;
  char tmp = 0;
  char rook_open_white = 0;
  char rook_open_black = 0;
  int j9 = 0;
  int j10 = 0;
  char center_pawn_white = 0;
  char center_pawn_black = 0;
  char pawn_close_white = 0;
  char pawn_close_black = 0;
  char white_king_pos = 0;
  char black_king_pos = 0;
  char passed_pawn_black = 0;
  char passed_pawn_white = 0;
  *(knight_white + 1) = 0;
  *(knight_black + 1) = 0;
  
  *(queen_black) = 0;
  *(queen_black + 1) = 0;
  for(int i = 0; i < 64; i++){ //no need to check for pawns on 1 or 8 line
    temp_feld = *(feld + i);
    if(temp_feld == EMPTY){
      continue;
    }
    else if(temp_feld == PAWN_WHITE){
      material_weiss++;
      pawn_white[j1++] = i;
    }
    else if(temp_feld == PAWN_BLACK){
      material_schwarz++;
      pawn_black[j2++] = i;
    }
    else if(temp_feld == KNIGHT_WHITE){
      material_weiss+=3;
      knight_white[j3++] = i;
    }
    else if(temp_feld == KNIGHT_BLACK){
      material_schwarz+=3;
      knight_black[j4++] = i;
    }
    else if(temp_feld == BISHOP_WHITE){
      material_weiss+=3;
      bishop_white[j5++] = i;
    }
    else if(temp_feld == BISHOP_BLACK){
      material_schwarz+=3;
      bishop_black[j6++] = i;
    }
    else if(temp_feld == ROOK_WHITE){
      material_weiss+=5;
      rook_white[j7++] = i;
    }
    else if(temp_feld == ROOK_BLACK){
      material_schwarz+=5;
      rook_black[j8++] = i;
    }
    else if(temp_feld == QUEEN_WHITE){
      material_weiss+=8;
      queen_white[j9++] = i;
    }
    else if(temp_feld == QUEEN_BLACK){
      material_schwarz+=8;
      queen_black[j10++] = i;
    }
    else if(temp_feld == KING_WHITE){
      koenig_weiss_b = 1;
      king_white = i;
    }
    else if(temp_feld == KING_BLACK){
      koenig_schwarz_b = 1;
      king_black = i;
    }
  }
  if(koenig_schwarz_b != 1){
    return INT_MAX - 1;
  }
  else if(koenig_weiss_b != 1){
    return -INT_MAX + 1;
  }
  if(j7 >= 1){//possibly better: check how many pawns there are
    temp1 = rook_white[0];
    if(j7 == 2){ //Checking if Rooks are connected
      temp2 = rook_white[1];

      
      //fix of the white one

      
      temp = 0;
      if((temp1&7)==(temp2&7)){
	for(int k = 1; k < (temp2>>3)-(temp1>>3) - 1; k++){
	  if(*(feld + temp1 + 8*k) != 0){
	    temp = 1;
	    break;
	  }
	}
	if(temp == 0){
	  connect_rooks_white = 2;
	}
	else{
	  temp = 0;
	}
      }
      
      if((temp1>>3)==(temp2>>3)){
	for(int k = 1; k < (temp2&7)-(temp1&7); k++){
	  if(*(feld + temp1 + k) != 0){
	    temp = 1;
	    break;
	  }
	}
	if(temp == 0){
	  connect_rooks_white = 3;
	}
	else{
	  temp = 0;
	}
      }

      
      //fix of the white one

      
      if((temp1&7)==6||(temp2&7)==6){
	seventh_white = 1;
	if((temp1&7)==(temp2&7)){         
	  seventh_white = 3;
	}
      }
      for(int i = 0; i < j1; i++){
	if((temp1>>3)==(pawn_white[i]>>3)){
	  temp = 1;
	}
	if((temp2>>3)==(pawn_white[i]>>3)){
	  tmp = 1;
	}
      }
      if(temp == 0){//it goes in here
	rook_open_white++;
	if(tmp == 0){
	  rook_open_white+=2;
	}
      }
      else if(tmp == 0){
        rook_open_white++;
      }
      tmp = 0;
    }
    else{
      if((temp1&7)==6){
	seventh_white = 1;
      }
      for(int i = 0; i < j1; i++){
	if((temp1>>3)==(pawn_white[i]>>3)){
	  temp = 1;
	}
      }
      if(temp==0){
	rook_open_white = 1;
      }
    }
  }
  
  if(j8 >= 1){//possibly better: check how many pawns there are
    temp1 = rook_black[0];
    if(j8 == 2){ //Checking if Rooks are connected
      temp2 = rook_black[1];


      //fix of connect_rooks

      temp = 0;
      if((temp1&7)==(temp2&7)){
	for(int k = 1; k < (temp2>>3)-(temp1>>3) - 1; k++){
	  if(*(feld + temp1 + 8*k) != 0){
	    temp = 1;
	    break;
	  }
	}
	if(temp == 0){
	  connect_rooks_black = 2;
	}
	else{
	  temp = 0;
	}
      }
      
      if((temp1>>3)==(temp2>>3)){
	for(int k = 1; k < (temp2&7)-(temp1&7); k++){
	  if(*(feld + temp1 + k) != 0){
	    temp = 1;
	    break;
	  }
	}
	if(temp == 0){
	  connect_rooks_black = 3;
	}
	else{
	  temp = 0;
	}
      }
      //fix if connext_rooks

      
      if((temp1&7)==1||(temp2&7)==1){
	seventh_black = 1;
	if((temp1&7)==(temp2&7)){         
	  seventh_black = 3;
	}
      }
      temp = 0;
      for(int i = 0; i < j2; i++){
	if((temp1>>3)==(pawn_black[i]>>3)){
	  temp = 1;
	}
	if((temp2>>3)==(pawn_black[i]>>3)){
	  tmp = 1;
	}
      }
      if(temp == 0){
	rook_open_black++;
	if(tmp == 0){
	  rook_open_black+=2;
	}
      }
      else if(tmp == 0){
	rook_open_black++;
      }
    }
    else{
      if((temp1&7)==1){
	seventh_black = 1;
      }
      temp = 0;
      for(int i = 0; i < j2; i++){
	if((temp1>>3)==(pawn_black[i]>>3)){
	  temp = 1;
	}
      }
      if(temp == 0){
	rook_open_black++;
      }
    }
  }
  if(queen_black != 0){
    for(int i = 0; i < j1; i++){
      temp1 = pawn_white[i];
      if((temp1&7) < 6 && (temp1&7) > 1 && (temp1>>3) > 1 && (temp1>>3) < 6){
	if((temp1&7) < 5 && (temp1&7) > 2 && (temp1>>3) > 2 && (temp1>>3) < 5){
	  center_pawn_white+=2;
	}
	else{
	  center_pawn_white++;
	}
      }
    }
    flag1 = 7-(*queen_black&7);
    flag2 = (*queen_black&7);
    flag3 = 7-(*queen_black>>3);
    flag4 = (*queen_black>>3);
    for(int i = 1; i <= min_2(flag2, flag4); i++){
      if(*(feld + *queen_black - i*9) != 0){
	break;
      }
      else{
	queen_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1, flag4); i++){
      if(*(feld + *queen_black - i*7) != 0){
	break;
      }
      else{
	queen_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag2, flag3); i++){
      if(*(feld + *queen_black + i*7) != 0){
	break;
      }
      else{
	queen_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1,flag3); i++){
      if(*(feld + *queen_black + i*9) != 0){
	break;
      }
      else{
	queen_black_free++;
      }
    }
  }
    

    
  else{
    for(int i = 0; i < j1; i++){
      material_weiss++;//pawns are worth more
      pawn_close_white += (pawn_white[i]&7);
    }
    if(*(queen_black) == 0 && (king_white>>3) > 2 && (king_white>>3) < 6 && (king_white&7) > 2 && (king_white&7) < 6){
      white_king_pos = 1;
    }
  }
  if(queen_white != 0){
    for(int i = 0; i < j2; i++){
      temp1 = pawn_black[i];
      if(((temp1&7) < 6) && ((temp1&7) > 1) && ((temp1>>3) > 1) && ((temp1>>3) < 6)){
	if(((temp1&7) < 5) &&((temp1&7) > 2) && ((temp1>>3) > 2) && ((temp1>>3) < 5)){
	  center_pawn_black+=2;
	}
	else{
	  center_pawn_black++;
	}
      }
    }
    
    flag1 = 7-(*queen_white&7);
    flag2 = (*queen_white&7);
    flag3 = 7-(*queen_white>>3);
    flag4 = (*queen_white>>3);
    for(int i = 1; i <= min_2(flag2, flag4); i++){
      if(*(feld + *queen_white - i*9) != 0){
	break;
      }
      else{
	queen_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1, flag4); i++){
      if(*(feld + *queen_white - i*7) != 0){
	break;
      }
      else{
	queen_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag2, flag3); i++){
      if(*(feld + *queen_white + i*7) != 0){
	break;
      }
      else{
	queen_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1,flag3); i++){
      if(*(feld + *queen_white + i*9) != 0){
	break;
      }
      else{
	queen_white_free++;
      }
    }
  }
  for(int a = 0; a < 2; a++){
    flag = 0;
    if(*(knight_black + a) != 0){
      if(*(knight_black + a) > 7 && *(knight_black + a)< 56){
	temp = *(knight_black + a);
	for(int i = temp; ((i)&7) < ((i + 1)&7); i--){
	  if(*(feld - 7 + i + temp) == PAWN_WHITE || *(feld + 9 + i + temp) == PAWN_WHITE){
	    flag = 1;
	  }
	}
	if(flag == 0){
	  for(int i = temp; ((i)&7) < ((i + 1)&7); i--){
	    if(*(feld+i) == PAWN_WHITE){
	      flag = 1;
	    }
	  }
	  if(flag == 1){
	    knight_pos_black = 1;
	  }
	}
      }
    }
  }
  
  for(int z = 0; z < 2; z++){
    flag1 = 7-(bishop_white[z]&7);
    flag2 = (bishop_white[z]&7);
    flag3 = 7-(bishop_white[z]>>3);
    flag4 = (bishop_white[z]>>3);
    for(int i = 1; i <= min_2(flag2, flag4); i++){
      if(*(feld + bishop_white[z] - i*9) != 0){
	break;
      }
      else{
	bishop_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1, flag4); i++){
      if(*(feld + bishop_white[z] - i*7) != 0){
	break;
      }
      else{
	bishop_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag2, flag3); i++){
      if(*(feld + bishop_white[z] + i*7) != 0){
	break;
      }
      else{
	bishop_white_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1,flag3); i++){
      if(*(feld + bishop_white[z] + i*9) != 0){
	break;
      }
      else{
	bishop_white_free++;
      }
    }
  }

  for(int z = 0; z < 2; z++){
    flag1 = 7-(bishop_black[z]&7);
    flag2 = (bishop_black[z]&7);
    flag3 = 7-(bishop_black[z]>>3);
    flag4 = (bishop_black[z]>>3);
    for(int i = 1; i <= min_2(flag2, flag4); i++){
      if(*(feld + bishop_black[z] - i*9) != 0){
	break;
      }
      else{
	bishop_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1, flag4); i++){
      if(*(feld + bishop_black[z] - i*7) != 0){
	break;
      }
      else{
	bishop_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag2, flag3); i++){
      if(*(feld + bishop_black[z] + i*7) != 0){
	break;
      }
      else{
	bishop_black_free++;
      }
    }
    for(int i = 1; i <= min_2(flag1,flag3); i++){
      if(*(feld + bishop_black[z] + i*9) != 0){
	break;
      }
      else{
	bishop_black_free++;
      }
    }
  }
  
  if(*(queen_black) != 0){
    if((king_white&7)<((king_white + 1)&7)){
      for(int i = 0; i < j1; i++){
	if(pawn_white[i] == king_white + 1){
	  white_king_pos++;
	}
      }
      if((king_white + 8) < 64){
	for(int i = 0; i < j1; i++){
	  if(pawn_white[i] == king_white + 9){
	    white_king_pos++;
	  }
	}
      }
      if((king_white - 8) > 0){
	for(int i = 0; i < j1; i++){
	  if(pawn_white[i] == king_white - 7){
	    white_king_pos++;
	  }
	}
      }
    }
  }
  else{
    flag1 = 0;
    for(int o = 0; o < j1; o++){
      for(int z = (pawn_white[o]&7); z > 0; z--){
	if((pawn_white[o]&7)-z == PAWN_BLACK){
	  flag1 = 1;
	}
      }
    }
    if(flag1 == 0){
      passed_pawn_black++;
    }
    white_king_pos = 0;
  }
  if(*(queen_white) != 0){
    if((king_black&7)>((king_black - 1)&7)){
      for(int i = 0; i < j2; i++){
	if(pawn_black[i] == king_black - 1){
	  black_king_pos ++;
	}
      }
      if((king_black + 8) < 64){
	for(int i = 0; i < j2; i++){
	  if(pawn_black[i] == king_black + 7){
	    black_king_pos++;
	  }
	}
      }
      if((king_black - 8) > 0){
	for(int i = 0; i < j2; i++){
	  if(pawn_black[i] == king_black - 9){
	    black_king_pos++;
	  }
	}
      }
    }
  }
  else{
    flag1 = 0;
    for(int o = 0; o < j2; o++){
      for(int z = (pawn_black[o]&7); z > 0; z--){
	if((pawn_black[o]&7)-z == PAWN_WHITE){
	  flag1 = 1;
	}
      }
    }
    if(flag1 == 0){
      passed_pawn_black++;
    }
    black_king_pos = 0;
  }
  /*printf("%i\n", (passed_pawn_white - passed_pawn_black));
  printf("%i\n", (material_weiss - material_schwarz));
  printf("%i\n", (connect_rooks_white - connect_rooks_black));
  printf("%i\n", (center_pawn_white - center_pawn_black));
  printf("%i\n", (seventh_white - seventh_black));
  printf("%i\n", (rook_open_white - rook_open_black));
  printf("%i\n", (pawn_close_white - pawn_close_black));
  printf("%i\n", (white_king_pos - black_king_pos));
  printf("%i\n", (queen_white_free - queen_black_free));
  printf("%i\n", (knight_pos_white - knight_pos_black));
  printf("%i\n", (bishop_white_free - bishop_black_free));*/
  int aq = PASSED*(passed_pawn_white-passed_pawn_black)+MATERIAL*(material_weiss-material_schwarz)+CONNECT*(connect_rooks_white-connect_rooks_black)+SEVENTH*(seventh_white-seventh_black)+OPENLINE*(rook_open_white-rook_open_black)/*+PROTEC*(protec_white-protec_black)*/+CENTER*(center_pawn_white-center_pawn_black)+END_PAWN*(pawn_close_white-pawn_close_black)+KING_POS*(white_king_pos-black_king_pos)+QUEEN_MOD*(queen_white_free-queen_black_free)+KNIGHT_STRENGTH*(knight_pos_white-knight_pos_black)+BISHOP_MOD*(bishop_white_free-bishop_black_free);
  //printf("%i\n", aq);
  return aq;
}


#define IND(r,c) (8*c+r)
#define OUTPUT(board);	\
  for (int r = 7; r >= 0; r--) {		\
    for (int c = 0; c != 8; c++) {              \
      printf(" | ");					\
      switch (board[IND(r, c)]) {			\
      case EMPTY: printf("  ");break;			\
      case PAWN_WHITE: printf("PW");break;		\
      case PAWN_BLACK: printf("PB");break;		\
      case KNIGHT_WHITE: printf("KW");break;		\
      case KNIGHT_BLACK: printf("KB");break;		\
      case BISHOP_WHITE: printf("BW");break;		\
      case BISHOP_BLACK: printf("BB");break;		\
      case ROOK_WHITE: printf("RW");break;		\
      case ROOK_BLACK: printf("RB");break;		\
      case QUEEN_WHITE: printf("QW");break;		\
      case QUEEN_BLACK: printf("QB");break;		\
      case KING_WHITE: printf("kw");break;		\
      case KING_BLACK: printf("kb");break;		\
      }							\
    }							\
    printf("|\n------------------------------------------\n");		\
  }

inline void copy_board(char * dst, char * src) {    //Copy 64-Bytes from src to dst
  memcpy((void*)(dst), (void*)(src), 66);        //TODO: kill string.h dependency
}
inline unsigned DEPTH(unsigned sec) {    //Berechnungstiefe, wenn noch sec Sekunden über
  return log(sec + 1);                           //TODO: kill string.h dependency
}
char IS_GAME_FINISHED(BOARD board) {//Returned 1, wenn weiß matt, 2, wenn schwarz matt, 3 wenn unentschieden und sonst 0 
  return 0; //TODO
}
int evaltry(char *feld){
  char king_w_flag = 0;
  char king_b_flag = 0;
  for(int i = 0; i < 64; i++){
    if(*(feld + i) == KING_WHITE){
      king_w_flag = 1;
    }
    if(*(feld + i) == KING_BLACK){
      king_b_flag = 1;
    }
  }
  if(king_w_flag == 0){
    return -1;
  }
  else if(king_b_flag == 0){
    return 1;
  }
  else{
    return 0;
  }
}
/*

int min(char *board, int depthleft){
  char *next;
  int pm, numcur;
  int prev = INT_MAX - 1;
  if(depthleft == 0){
    return eval(board);
  }
  next = next_positions(board, false);
  pm = possible_moves;
  for(int i = 0; i < pm; i++){
    numcur = max(next + i*66, depthleft-1);
    if(numcur < prev){
      prev = numcur;
    }
  }
free(next);
  return prev;
}

int max(char *board, int depthleft){
  char *next;
  int pm, numcur;
  int prev = 1 - INT_MAX;
  if(depthleft == 0){
    return eval(board);
  }
  next = next_positions(board, true);
  pm = possible_moves;
  for(int i = 0; i < pm; i++){
    numcur = min(next + i*66, depthleft-1);
    if(numcur > prev){
      prev = numcur;
    }
  }
free(next);
  return prev;
}
*/
/*läuft aber ist lahm*/

int min(char *board, int depthleft, int alpha, int beta){
  int pm, prev;
  int val;
  if(depthleft == 0){
    return eval(board);
  }
  char *next;
  next = next_positions(board, false);
  pm = possible_moves;
  if(pm == 0){
    free(next);
    return 0;
  }
  prev = alpha;
  for(int i = 0; i < pm; i++){
    val = max((next + i*66), depthleft-1, prev, beta);
    if(val > alpha){
      break;
    }
    if(prev > val){
      prev = val;
    }
  }
  free(next);
  return prev;
}

int max(char *board, int depthleft, int alpha, int beta){
  int pm, prev;
  int val;
  if(depthleft == 0){
    return eval(board);
  }
  char *next;
  next = next_positions(board, true);
  pm = possible_moves;
  if(pm == 0){
    free(next);
    return eval(board);
  }//no stalemate, but it allows for deeper opt
  prev = beta;
  for(int i = 0; i < pm; i++){
    val = min((next + i*66), depthleft-1, alpha, prev);
    if(val < beta){
      break; 
    }
    if(val > prev){
      prev = val;
    }
  }
  free(next);
  return prev;
}

namespace internal {  
  
  int negascout(int depthleft, char* board, int alpha, int beta, char color)
  {                     
    int a, b, t, i, w;
    bool x = false ;
    if(color == 1){
      x = true;
    }
    char *next;
    if (depthleft == 0){
      return eval(board);
    }
    next = next_positions(board, x);
    if(possible_moves == 0){
      return eval(board);
    }
    w = possible_moves;
    a = alpha;
    b = beta;
    for (i = 0; i < w; i++) {
      t = -negascout (depthleft-1, next + 66*i, -b, -a, -color);
      if ((t > a) && (t < beta) && (i > 1) && (1 < depthleft) )
	a = -negascout (depthleft-1, next + 66*i, -beta, -t, -color);
      a = max_2( a, t );
      if ( a > beta )
	return a;
      b = a + 1;                   
    }
    return a;
  }
  /*EVAL_TYPE negamax(BOARD b, unsigned char depth_left, EVAL_TYPE alpha, EVAL_TYPE beta, char color){
    int i = alpha;
    if (depth_left == 0){
      return eval(b)*color;
    }
    BOARDS next = next_positions(b , color);
    NEXT_MOVES_TYPE pm = possible_moves;
    if (pm == 0) //Patt
      {
	return 0;
      }
    EVAL_TYPE val = 1-INT_MAX;
    for (int h = 0; h != pm; h++){
      val = max_2(val, -negamax(next+66*h, depth_left - 1, -beta, -i, -color));
      i = max_2(i, val);

      if (i >= beta){
	break;
      }
    }
    return val;
    }*/
  /*int negascout(int depthleft, char* board, int alpha, int beta, char color)
  {   
    if(depthleft == 0){
      
    }
  }*/
  BOARD suggest(BOARD board, TIME_TYPE sec_left, bool x) {
    int num = INT_MAX - 1;
    int pos = 0;
    int prev = INT_MAX - 1;
    int pm;
    if(x == true){
      num = INT_MAX-1;
      prev = INT_MAX-1;
    }
    char *trye;
    trye = next_positions(board, false);
    pm = possible_moves;
    for(int j = 0; j < pm; j++){
      num = max((trye + j*66), 5, num, 1-INT_MAX);
      OUTPUT((trye + j*66));
      if(num < prev){
	prev = num;
	pos = j;
	//OUTPUT((trye + j*66));
	printf("%i\n", j);
      }
    }
    printf("\n\n\n%i\n", pos);
    printf("%i\n\n\n\n", prev);
    return trye+pos*66;
  }//works very slowly

  BOARD suggestnega(BOARD board, TIME_TYPE sec_left, bool x) {
    int num = INT_MAX - 1;
    int pos = 0;
    int prev = INT_MAX - 1;
    int pm;
    if(x == true){
      num = INT_MAX-1;
      prev = INT_MAX-1;
    }
    char *trye;
    trye = next_positions(board, false);
    pm = possible_moves;
    for(int j = 0; j < pm; j++){
      num = negascout(5, (trye + j*66), num, 1-INT_MAX, 1);
      OUTPUT((trye + j*66));
      if(num < prev){
	prev = num;
	pos = j;
	//OUTPUT((trye + j*66));
	printf("%i\n", j);
      }
    }
    printf("\n\n\n%i\n", pos);
    printf("%i\n\n\n\n", prev);
    return trye+pos*66;
  }
}
/*
namespace testing {
#define move0();						\
  auto sta = std::chrono::high_resolution_clock::now();		\
  char* new_board = internal::suggest<0>(board, time[0],0);		\
  auto sto = std::chrono::high_resolution_clock::now();			\
  time[0] -= std::chrono::duration_cast<std::chrono::nanoseconds>(sto - sta).count(); \
  copy_board(board, new_board);
  */
#define move1();						\
  char* new_board = internal::suggest(board, 1, false);		\
  for(int i = 0; i < 66; i++){                                  \
    *(board + i) = *(new_board + i);				\
  }

#define negamove();\
  char* new_board = internal::suggestnega(board, 1, false); \
  for(int i = 0; i < 66; i++){                              \
    *(board + i) = *(new_board + i);			    \
  }                                                         \
  /*
  //Lässt zwei eval-Versionen gegeneinandr antreten
  inline unsigned* versus(unsigned _games, TIME_TYPE t) {
    unsigned games2 = _games >> 1;
    unsigned* ret = (unsigned*)malloc(3 * sizeof(unsigned));
    for (unsigned i = 0; i != games2; i++) {
      char board[66];
      copy_board(board, (char*)globalfeld);
      TIME_TYPE time[2] = { t,t };
      while (true) {
	if (IS_GAME_FINISHED(board)) { goto end1; }
	else { move0(); }
	if (IS_GAME_FINISHED(board)) { goto end1; }
	else { move1(); }
      }
    end1:
      ret[IS_GAME_FINISHED(board) - 1]++;
      

      copy_board(board, (char*)globalfeld);
      time[0] = t;
      time[1] = t;
      move1();
	if (IS_GAME_FINISHED(board)) { goto end2; }
	else { move0(); }
	if (IS_GAME_FINISHED(board)) { goto end2; }
	else { move1(); }
    end2:
      ret[IS_GAME_FINISHED(board) - 1]++;
    }
    return ret;
  }*/
  /*
  //Lässt Person gegen Engine spielen
  inline void interactive(TIME_TYPE player_time, TIME_TYPE engine_time) {
    char board[66];
    copy_board(board,(char*)globalfeld);
    //TIME_TYPE time[2] = { player_time, engine_time }; 
    while (true) {
      if (IS_GAME_FINISHED(board)) { goto end1; }
      else { 
	OUTPUT(board);
	printf("Reached!"); fflush(stdout);
	//auto  sta = std::chrono::high_resolution_clock::now();
	char r1, c1, r2, c2;
	do{
	c1 = getchar()-97;
	}
	while(c1 == -87);
	r1 = getchar()-49;
	c2 = getchar()-97;
	r2 = getchar()-49;
	printf("%d %d %d %d", c1, r1, c2, r2);
	//auto  sto = std::chrono::high_resolution_clock::now();
	board[IND(r2, c2)] = board[IND(r1, c1)];
	board[IND(r1, c1)] = 0;
	//	time[0] -= std::chrono::duration_cast<std::chrono::nanoseconds>(sto - sta).count();
      }
      if (IS_GAME_FINISHED(board)) { goto end1; }
      else { move1(); }
    }
  end1:
    printf("%d",IS_GAME_FINISHED(board)-1);
  }
  */
void tryout(char *feld, bool is){
  char *ret = (char *) malloc(sizeof(char) * 66 * 128);
  ret = next_positions(feld, is);
  for(int i = 0; i<possible_moves; i++){
    OUTPUT((ret + i * 66));
    printf("%i\n", eval(ret + i*66));
  }
  free(ret);
}
int main(){
  int i;
  int a;
  char *board = (char *) malloc(sizeof(char) * 66);
  for(int j = 0; j < 65; j++){
    *(globalfeld + j) = 0;
  }
  for(int a = 0; a < 8; a++){
    *(globalfeld + 1 + a*8) = 1;
    *(globalfeld + 6 + a*8) = 2;
  }
  *(globalfeld + 8) = 3;
  *(globalfeld + 6*8) = 3;
  *(globalfeld + 8*2) = 5;
  *(globalfeld + 8*5) = 5;
  *(globalfeld) = ROOK_WHITE;
  *(globalfeld + 8*7) = ROOK_WHITE;
  *(globalfeld + 8*3) = QUEEN_WHITE;
  *(globalfeld + 8*4) = KING_WHITE;
  *(globalfeld + 8 + 7) = 4;
  *(globalfeld + 6*8 + 7) = 4;
  *(globalfeld + 8*2 + 7) = 6;
  *(globalfeld + 8*5 + 7) = 6;
  *(globalfeld + 7) = ROOK_BLACK;
  *(globalfeld + 8*7 + 7) = ROOK_BLACK;
  *(globalfeld + 8*3 + 7) = QUEEN_BLACK;
  *(globalfeld + 8*4 + 7) = KING_BLACK;
  /*(globalfeld + 8*3 + 1) = 1;
  *(globalfeld + 8*3 + 3) = 0;*/
  /*(globalfeld + 8*5 + 1) = 0;
  *(globalfeld + 8*6 + 1) = 0;
  *(globalfeld + 8*4 + 6) = 0;*/
  *(globalfeld + 8*3 + 1) = 0;
  *(globalfeld + 8*3 + 3) = 1;
  for(i = 0; i < 66; i++){
    *(board + i) = *(globalfeld + i);
  }
  OUTPUT(board);
  //i = eval(globalfeld);
  //printf("%i\n", i);
  //tryout(globalfeld, false);

  move1();
  OUTPUT(board);
  //a = eval(globalfeld);
  //printf("%i\n", a);
  printf("%lld\n", count);
  return 0;
}
