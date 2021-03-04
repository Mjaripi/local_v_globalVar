/*
 * FILE: sum-G.c
 *
 * DESCRIPTION: computes a0 + a1 + ... + an
 *              using Divide et Impera approach
 *              with a global variable that save
 *              the result.
 *
 * AUTHOR: Ruben Carvajal Schiaffino
 * Edited by: Alonso Maripi Vallejos and Silvana Cerda Aravena.
 *
 * LAST REVISED: Santiago de Chile, 10/10/2016
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>


int *a;


/*
 *
 */
int RecSum(unsigned int l, unsigned int r) {

     unsigned int l1, l2, r1, r2;

     if (l == r) return a[l];
     if (l + 1 == r) return a[l] + a[r];
     l1 = l;
     r1 = floor((float)((l + r)) / 2.0) - 1;
     l2 = floor((float)((l + r)) / 2.0);
     r2 = r;
     return RecSum(l1,r1) + RecSum(l2,r2);
}

int RecCounter(unsigned int l, unsigned int r,int cont) {

     unsigned int l1, l2, r1, r2;
     int A,B;

     if (l == r)
        return cont;
     if (l + 1 == r) return cont;
     l1 = l;
     r1 = floor((float)((l + r)) / 2.0) - 1;
     l2 = floor((float)((l + r)) / 2.0);
     r2 = r;
     A=RecCounter(l1,r1,cont+1);
     B=RecCounter(l2,r2,cont+1);
     if(A>B)
        return A;
     else
        return B;

}

/*
 *
 */
int main(int argc,char **argv) {

     unsigned int x ,n, i;
     int sum,cont;
     float E_cpu;
     clock_t cs, ce;
     long E_wall;
     time_t ts, te;
     FILE *save;

     save=fopen("sum-G.txt","a");
     x=atoi(argv[1]);
     for(n = 2;n <= x;n = n * 2){
        a = calloc(n,sizeof(int));
        for (i = 0; i < n; i = i + 1)
            a[i]=0;
        ts = time(NULL);
        cs = clock();
        sum = RecSum(0,n - 1);
        ce = clock();
        te = time(NULL);
        E_wall = (long) (te - ts);
        E_cpu = (float)(ce - cs) / CLOCKS_PER_SEC;
        cont=RecCounter(0,n-1,0);
        fprintf(save,"%d %d\n",n,cont);
        //printf("Max. Cycles: %d Size Problem: %d Solution: %d Elapsed CPU Time: %f [Secs] Elapsed Wall Time: %ld [Secs]\n",cont,n,sum,E_cpu,E_wall);
      }
      fclose(save);
}
