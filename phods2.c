/*Parallel Hierarchical One-Dimensional Search for motion estimation*/
/*Initial algorithm - Used for simulation and profiling             */

#include <stdio.h>
#include <stdlib.h>
/*------------------------------------------------------------------*/
#include <sys/time.h>
/*------------------------------------------------------------------*/
#define N 144     /*Frame dimension for QCIF format*/
#define M 176     /*Frame dimension for QCIF format*/
#define B 16      /*Block size*/
#define p 7       /*Search space. Restricted in a [-p,p] region around the
                    original location of the block.*/

void read_sequence(int current[N][M], int previous[N][M])
{ 
	FILE *picture0, *picture1;
	int i, j;

	if((picture0=fopen("akiyo0.y","rb")) == NULL)
	{
		printf("Previous frame doesn't exist.\n");
		exit(-1);
	}

	if((picture1=fopen("akiyo1.y","rb")) == NULL) 
	{
		printf("Current frame doesn't exist.\n");
		exit(-1);
	}

  	/*Input for the previous frame*/
  	for(i=0; i<N; i++)
 	{
    		for(j=0; j<M; j++)
    		{
      			previous[i][j] = fgetc(picture0);
    		}
  	}

	/*Input for the current frame*/
	for(i=0; i<N; i++)
  	{
		for(j=0; j<M; j++)
    		{
			current[i][j] = fgetc(picture1);
    		}
  	}

	fclose(picture0);
	fclose(picture1);
}


void phods_motion_estimation(int current[N][M], int previous[N][M], int vectors_x[N/B][M/B],int vectors_y[N/B][M/B])
{
  	long int t;
	struct timeval t0,t1;
  	
	//star timer	
	gettimeofday(&t0,NULL);

	/*-------- Function's Body starts-------- */
	int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;
  	int tempx[4], tempy[4];
	
  	/*For all blocks in the current frame*/
  	for(x=0; x<N/B; x++)
  	{ 		
		/*tempx*/
    		tempx[0] = B*x;

    		for(y=0; y<M/B; y++)
    		{

      			/*tempy*/
      			tempy[0] = B*y;

      			/*Initialize the vector motion matrices*/
      			vectors_x[x][y] = 0;
      			vectors_y[x][y] = 0;
      			S = 4;
      			while(S>0)
      			{
       				min1 = 255*B*B;
        			min2 = min1;
				
        			/*For all candidate blocks in X and Y dimension*/
        			for(i=-S; i<S+1; i+=S)     
        			{
	  				distx = 0;
	  				disty = 0;
          				/*For all pixels in the block*/
          				for(k=0; k<B; k++)     
          				{
	    					tempx[1] = tempx[0] + k; /*tempx[1] = B*x + k*/
	    					tempx[2] = tempx[1] + vectors_x[x][y]+ i; /*tempx[2] = B*x + vectors_x[x][y] + k + i*/
	    					tempx[3] = tempx[2] - i; /* B*x + k + vectors_x[x][y] */
            					for(l=0; l<B; l++)
            					{
							
	      						tempy[1] = tempy[0]+l; /*tempy[1] = B*y +l*/
	      						tempy[2] = tempy[1]+ vectors_y[x][y] + i; /*tempy[2] = B*y + vectors_y[x][y] +l +i */
	      						tempy[3] = tempy[2] - i; /* B*y + l + vectors_y[x][y] */

              						p1 = current[tempx[1]][tempy[1]];

              						if((tempx[2]) < 0 ||(tempx[2] ) > (N-1) || (tempy[3]) < 0 || (tempy[3]) > (M-1))
              						{
                						p2 = 0;
              						} 
							else 
							{
                						p2 = previous[tempx[2]][tempy[3]];
              						}

              						distx += abs(p1-p2);
	      						if(i==0) disty = distx;
							else
							{
	      							if((tempx[3]) <0 || (tempx[3]) > (N-1) || (tempy[2]) < 0 || (tempy[2]) > (M-1))
              							{
                							q2 = 0;
              							} 
								else 
								{
                							q2 = previous[tempx[3]][tempy[2]];
              							}

              							disty += abs(p1-q2);
              
	    						}
          					
						}
					}
					if(distx < min1)
          				{
            					min1 = distx;
            					bestx = i;
          				}
	  				if(disty < min2)
          				{
           			 		min2 = disty;
            					besty = i;
          				}
				}
				
				S = S/2;
          			vectors_x[x][y] += bestx;
        			vectors_y[x][y] += besty;
      			}
    		}
	}
	/*-------- Function's Body ends-------- */
	
	//Stop timer and print time
	gettimeofday(&t1,NULL);
	t=((t1.tv_sec*1000000)+(t1.tv_usec))-((t0.tv_sec*1000000)+(t0.tv_usec));
	printf("I needed %ld microseconds to complete my task\n",t );
} 

int main()
{  
  int current[N][M], previous[N][M], motion_vectors_x[N/B][M/B], motion_vectors_y[N/B][M/B], i, j;
  

	read_sequence(current,previous);
  	phods_motion_estimation(current,previous,motion_vectors_x,motion_vectors_y);
	
	
  return 0;
}
