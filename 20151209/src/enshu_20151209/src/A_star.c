#include <stdio.h>
#include <stdlib.h>

struct BOARD {
  char cell[9];
  struct BOARD *next;
  struct BOARD *back;
  int depth, f;
};

struct BOARD BS = {
  2,1,3,4,0,6,7,8,5,NULL,NULL,0,0
};

struct BOARD BG = {
  1,2,3,4,5,6,7,8,0
};

struct BOARD *q0 = NULL, *q2 = &BS;

struct BOARD *getq(){
  struct BOARD *q;
  if (q2==NULL) return NULL;
  q = q2;
  q2 = q2->next;
  return q;
}

int ns = 0;

void readdata(struct BOARD *b, char *buf){
  FILE*fn;
  int num[9], k;

  if ((fn = fopen(buf, "r")) == (FILE *)NULL) return;
  fscanf(fn, "%1d %1d %1d %1d %1d %1d %1d %1d %1d",
	 num, num+1, num+2, num+3, num+4, num+5, num+6, num+7, num+8);

  for(k=0;k<8;k++) b->cell[k] = *(num+k);

  fclose(fn);
}

int diff(struct BOARD *b1, struct BOARD *b2){
  int ans=0,k;
  for(k=0;k<9;k++) if(b1->cell[k] != b2->cell[k]) ans++;
  return(ans);
}

void f_value(struct BOARD *b){
  b->f = b->depth + diff(b,&BG);
}

void printboard(struct BOARD *b){
  int i;
  for(i=0;i<9;i++){
    printf("%1d",b->cell[i]);
    if(i%3==2) printf("\n");
  }
  printf("\n");
}

void traceback(struct BOARD *b){
  for(;b!=NULL;b=b->back){
    ns++;
    printboard(b);
  }
}

void exchange(struct BOARD *b, int i, int j){
  struct BOARD *m;
  int k;
  // printf("ffffffffffffffffffff\n");
  m =(struct BOARD*) malloc (sizeof(struct BOARD));
  if(m==NULL){
    printf("error\n");
    exit(2);
  }
  for(k=0;k<9;k++) m->cell[k] = b->cell[k];
  m->cell[i] = b->cell[j];
  m->cell[j] = 0;
  m->back = b;
  m->next = NULL;
  m->depth = b->depth + 1;
  //  printf("ggggggggggggggggggggg\n");
  if(equal(m,&BG)){
    f_value(b);
    printboard(m);
    printf("終了\n");
    traceback(m);
    printf("手数:%d\n",ns-1);
    exit(0);
  }
  putq(m);
}


void expand(struct BOARD *b){
  int i;
  for(i=0;i<9;i++)
    if(b->cell[i]==0) break;
  //  printf("eeeeeeeeeeeeeeeeeeeeeee\n");
  if(i%3>0) exchange(b,i,i-1);
  if(i>2) exchange(b,i,i-3);
  if(i%3<2) exchange(b,i,i+1);
  if(i<6) exchange(b,i,i+3);
}

int equal(struct BOARD *b1, struct BOARD *b2){
  int i;
  for(i=0;i<9;i++){
    if (b1->cell[i]!=b2->cell[i]) return 0;
  }
  return 1;
}

printQ(struct BOARD *b){
  printboard(b->back);
  printf(" %d--------------->%d \n", b->back->f, b->f);
  printboard(b);
  printf("\n");
}

int putq(struct BOARD *b){
  struct BOARD *n, *oldn=NULL;
  for(n=q0;n!=NULL;n=n->next)
    if(equal(b,n)) {free(b); return;}
  if(q2==NULL){
    f_value(b);
    q2 = b;
    printboard(b);
  }
  else{
    f_value(b);
    for(n=q2;n->next!=NULL;n=n->next) 
      if (equal(b,n)) {free(b); return;}
    for(n=q2; n!=NULL; oldn=n,n=n->next)
      if(n->f > b->f) break;
    b->next = n;
    if(oldn != NULL) oldn->next = b;
    else q2 = b;
    printboard(b);
  }
}

int main(){
  struct BOARD *b;
  struct BOARD *q1;

  readdata(&BS,"Init");
  readdata(&BS,"goal");
  
  BS.depth = 1;
  
  printf("初期状態\n");
  printboard(&BS);
  printf("目標状態\n");
  printboard(&BG);
  //printf("aaaaaaaaaaaaaa\n");

  f_value(&BS);

  // printf("bbbbbbbbbbbbbbbbb\n");

  while ((q1 = getq()) != NULL){
    // printf("dddddddddddddddddddd\n");
    expand(q1);
    // printf("cccccccccccccccccccc\n");
    if (q0==NULL) q0 = q1;
    else {
      q1 -> next = q0;
      q0 = q1;
    }
  }
}



