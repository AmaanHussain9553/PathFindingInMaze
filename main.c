#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct mazeStruct
{
	char arr[32][32];  /* allows for a dynamic 2-D maze of any size */
	int xsize, ysize;
	int xstart, ystart;
	int xend, yend;
	int **visited;
} maze;

struct theStruct
{
	int xValue, yValue;
	struct theStruct* next;
};

typedef struct theStruct Coordinates;
typedef Coordinates* s;

/* function for initializing the maze */
void createMaze(maze *maze, int xsize, int ysize, int xstart, int ystart, int xend, int yend)
{
	maze->xsize = xsize;
	maze->ysize = ysize;
	maze->xstart = xstart;
	maze->ystart = ystart;
	maze->xend = xend;
	maze->yend = yend;
	maze->visited = (int **) malloc(sizeof(int *) *(xsize + 2));
	
	int i = 0;
	while(i < xsize + 2)
	{
		maze->visited[i] = (int *) malloc(sizeof(int) * (ysize + 2));
    i++;
	}
}

/* function for pushing coordinates onto the stack */
void push(Coordinates **stack, int xInsert, int yInsert)
{
	int debugMode;
	Coordinates *ptr = (Coordinates*) malloc(sizeof(Coordinates));

	ptr->xValue = xInsert;
	ptr->yValue = yInsert;

	ptr->next = *stack;
	*stack = ptr;
}

/* function for popping coordinates off of the stack */
/* function for popping coordinates off of the stack */
void pop(Coordinates **hd)
{
	int debugMode;
	Coordinates *tmp = *hd;
	
	*hd = (*hd)->next;
	free(tmp);
}

/* function for checking if the stack is empty */
int isEmpty(Coordinates *stack)
{
	if(stack == NULL)
		return true;
	else
		return false;
}

/* function for displaying stack */
void displayStack(Coordinates *stack)
{
	Coordinates *temp = stack;

	while(temp->next != NULL)
	{
		printf("(%d, %d)\n", temp->xValue, temp->yValue);
		temp = temp->next;
	}
	printf("(%d, %d)\n", temp->xValue, temp->yValue);
}

Coordinates* FindPathToEnd(Coordinates* s, maze m1, int xCurrent, int yCurrent){
  while(isEmpty(s) != 1)
	{
		/* check if top is same as ending position */
		if(s->xValue == m1.xend && s->yValue == m1.yend)
		{
			break;
		}
		
    bool case1 = false;
    bool case2 = false;
    bool case3 = false;
    bool case4 = false;

    if(m1.visited[xCurrent][yCurrent + 1] == 0){
      case1 = true;
    }else if(m1.visited[xCurrent + 1][yCurrent] == 0){
      case2 = true;
    }else if(m1.visited[xCurrent][yCurrent - 1] == 0){
      case3 = true;
    }else if(m1.visited[xCurrent - 1][yCurrent] == 0){
      case4 = true;
    }
    

		/* 1. mark visited if going RIGHT 'R' */
		if(case1 == true)
		{
			yCurrent = yCurrent + 1;
			push(&s, xCurrent, yCurrent);
			m1.visited[xCurrent][yCurrent] = 1; /* UNVISITED to VISITED */
			m1.arr[xCurrent][yCurrent] = 'R';
		}
		
		/* 2. mark visited if going DOWN 'D' */
		else if(case2 == true)
		{
			xCurrent = xCurrent + 1;
			push(&s, xCurrent, yCurrent);
			m1.visited[xCurrent][yCurrent] = 1;
			m1.arr[xCurrent][yCurrent] = 'D';
		}
		
		/* 3. mark visited if going LEFT 'L' */
		else if(case3 == true)
		{
			yCurrent = yCurrent - 1;
			push(&s, xCurrent, yCurrent);
			m1.visited[xCurrent][yCurrent] = 1;
			m1.arr[xCurrent][yCurrent] = 'L';
		}
		
		/* 4. mark visited if going UP 'U' */
		else if(case4 == true)
		{
			xCurrent = xCurrent - 1;
			push(&s, xCurrent, yCurrent);
			m1.visited[xCurrent][yCurrent] = 1;
			m1.arr[xCurrent][yCurrent] = 'U';
		}
		
		else
		{
			pop(&s); 
			if(isEmpty(s))
				continue;
				xCurrent = s->xValue;
				yCurrent = s->yValue;
		}
  }
  return s;
}


/* function for resetting the stack */
void reset(maze *maze)
{
	int i = 0;
	while(i < maze->xsize + 2)
	{
		free(maze->arr[i]);
		free(maze->visited[i]);
    i++;
	}
	free(maze->arr);
	free(maze->visited);
}
 
/* main function */
int main(int argc, char **argv)
{
	
  //Declaring a maze
	maze m1;
	
  
	int xpos, ypos;
	int i, j;
	
	int xsize = -1, ysize = -1; 
	int xstart = -1, ystart = -1; 
	int xend = -1, yend = -1;
	
	Coordinates *s = NULL;

	FILE *src;
	
	/* verify the proper number of command line arguments were given */
	if(argc != 2) 
	{
		printf("Usage: %s <input file name>\n", argv[0]);
		exit(-1);
	}

	/* Try to open the input file. */
	if ( ( src = fopen( argv[1], "r" )) == NULL )
	{
		printf ( "Can't open input file: %s\n", argv[1] );
		exit(-1);
	}
	
	/* while loops to read in the size, starting and ending positions in the maze */
	while(fscanf (src, "%d %d", &xsize, &ysize) != EOF)
	{
		if(xsize > 0 && ysize > 0)
		{
			break;
		}
		else
		{
			printf("Cannot use as size: (%d, %d)\n", xsize, ysize);
			xsize = -1;
			ysize = -1;
		}
	}
	
	while(fscanf (src, "%d %d", &xstart, &ystart) != EOF)
	{
		if(xstart <= xsize && ystart <= ysize)
		{
			break;
		}
		else{
			printf("Cannot use as starting position: (%d, %d)\n", xstart, ystart);
			xstart = -1;
			ystart = -1;
		}
	}
	
	while(fscanf (src, "%d %d", &xend, &yend) != EOF)
	{
		if(xend <= xsize && yend <= ysize)
		{
			break;
		}
		else
		{
			printf("Cannot use as ending position: (%d, %d)\n", xend, yend);
			xend = -1;
			yend = -1;
		}
	}
	
	/* print them out to verify the input */
	printf ("\nsize: %d, %d\n", xsize, ysize);
	printf ("start: %d, %d\n", xstart, ystart);
	printf ("end: %d, %d\n\n", xend, yend);
	
	createMaze(&m1, xsize, ysize, xstart, ystart, xend, yend);
		
	/* initialize the maze to empty */
	i = 0;
  while(i < m1.xsize + 2)
	{
		j = 0;
    while(j < m1.ysize + 2)
		{
			m1.arr[i][j] = '.';
			m1.visited[i][j] = 0; /* UNVISITED POSITION */
      j++;
		}
    i++;
	}
	
	/* mark the borders of the maze with *'s */
	i = 0;
  while(i < m1.xsize + 2)
	{
		m1.arr[i][0] = '*';
		m1.arr[i][m1.ysize + 1] = '*';
		m1.visited[i][0] = 1; 
		m1.visited[i][m1.ysize + 1] = 1;
    i++; 
	}
	
  i = 0;
	while (i < m1.ysize + 2)
	{
		m1.arr[0][i] = '*';
		m1.arr[m1.xsize + 1][i] = '*';
		m1.visited[0][i] = 1; 
		m1.visited[m1.xsize + 1][i] = 1;
    i++;
	}	
	
	/* mark the starting and ending positions in the maze */
	m1.arr[m1.xstart][m1.ystart] = 's';
	m1.arr[m1.xend][m1.yend] = 'e';
	
	/* mark the starting position in the maze as VISITED */
	m1.visited[m1.xstart][m1.ystart] = 1;

  	/* mark the blocked positions in the maze with *'s */
	while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
	{
		/* check if starting blocked position is valid */
 		if(xpos == xstart && ypos == ystart)
		{
			printf("Cannot use as starting blocked position: (%d, %d)\n", xpos, ypos);
			continue;
		}
		
		/* check if ending blocked position is valid */
		if(xpos == xend && ypos == yend)
		{
			printf("Cannot use as ending blocked position: (%d, %d)\n", xpos, ypos);
			continue;
		}
		
		/* check if blocked position is outside of maze */
		if(xpos > xsize || ypos > ysize)
		{
			printf("Cannot use (outside of maze): (%d, %d)\n", xpos, ypos);
			continue;
		}
		m1.arr[xpos][ypos] = '*';
		m1.visited[xpos][ypos] = 1;
	}
	
	/* print out the initial maze */
	printf("\nGenerated maze: \n");
  i = 0;
	while(i < m1.xsize + 2)
	{
		for (j = 0; j < m1.ysize + 2; j++)
			printf ("%c", m1.arr[i][j]);
			printf("\n");
      i++;
	}
	
	push(&s, xstart, ystart);

	int xCurrent = xstart;
	int yCurrent = ystart;
	
	/* Function to read if stack is not empty */
	/* 1. RIGHT 2. DOWN 3. LEFT 4. UP */
	s = FindPathToEnd(s,m1,xCurrent,yCurrent);
	
	/* if stack is empty, then maze has no solution */
	if(isEmpty(s))
	{
		printf("\nThe maze has no solution\n\n");
		exit(1);
	}
	
	else
	{
		printf("\nSolution: \n");
		/* print out the solution to maze */
		i = 0;
    while(i < m1.xsize + 2)
		{
			for (j = 0; j < m1.ysize + 2; j++)
				printf ("%c", m1.arr[i][j]);
				printf("\n");
        i++;
		}
		
		printf("\nEach point visited from starting to ending: \n");
		/* call displayStack function to show every point visited */
		displayStack(s);
		exit(1);
	}
	reset(&m1); /* reset the stack so that it is empty and ready to be used again */
}