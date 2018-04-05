#include <stdio.h>
//#include <Windows.h>
#include <iostream>
//#include <GL\glew.h>
#include <GL\freeglut.h>
#include <math.h>

using namespace std;
using namespace std;

#define AND &&
#define OR ||
#define EPS 0.01

typedef struct { float x, y, z; }vertex;

typedef struct {
	vertex v_s, v_f;
	int ide;
}edge;

int e = 1;
edge p_edge[400];

int NOVF, NOVT, NOVS, NOEF, NOET, NOES;

/*********************************************
NAME : function_1()
ROOT : Front_Edge -> Top_Edge -> Side_Vertex
CASES DEALT:
***********************************************/

void function_1(edge fe, vertex sv[], edge te[], edge p_edge[])
{

	edge temp;
	int i, j;
	printf(" I am in FUNCTION - 1:\n");
	printf("-----------------------\n");
	for (i = 1; i <= NOET; i++)
	{
		if (te[i].ide == 1)
		{
			if ((fe.v_s.x == te[i].v_s.x AND fe.v_f.x == te[i].v_f.x) OR(fe.v_s.x == te[i].v_f.x AND
				fe.v_f.x == te[i].v_s.x))
			{


				for (j = 1; j <= NOVS; j++)
				{
					if (te[i].v_s.y == sv[j].y AND fe.v_s.z == sv[j].z)
					{
						temp.v_s.x = fe.v_s.x;
						temp.v_s.z = fe.v_s.z;
						temp.v_s.y = sv[j].y;

						temp.v_f.x = fe.v_f.x;
						temp.v_f.z = fe.v_f.z;
						temp.v_f.y = sv[j].y;
						p_edge[e++] = temp;
						printf("\t(*)\n");
						printf("%f %f %f\n", fe.v_s.x, sv[j].y, fe.v_s.z);
						printf("%f %f %f\n", fe.v_f.x, sv[j].y, fe.v_f.z);
					}
				}
			}
		}
	}
}

/*********************************************
NAME : function_2()
ROOT : Front_Edge -> Top_Edge -> Side_Edge
CASES DEALT:
********************************************/

void function_2(edge fe, edge se[], edge te[], edge p_edge[])
{
	int i, j;
	edge temp;
	printf("I am in FUNCTION - 2 :\n");
	printf("-----------------------\n");
	for (i = 1; i <= NOET; i++)
	{

		if (te[i].ide == 3)
		{
			if (fe.v_s.x == te[i].v_s.x AND fe.v_f.x == te[i].v_f.x)
			{


				for (j = 1; j <= NOES; j++)
				{
					if (se[j].ide == 5)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y AND fe.v_s.z == se[j].v_s.z)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y  AND fe.v_s.z == se[j].v_s.z))
						{
							printf("\t(*)\n");

							temp.v_s.x = fe.v_s.x;
							temp.v_s.z = fe.v_s.z;

							temp.v_f.x = fe.v_f.x;
							temp.v_f.z = fe.v_f.z;
							temp.v_f.y = te[i].v_f.y;
							temp.v_s.y = te[i].v_s.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fe.v_s.x, te[i].v_s.y, fe.v_s.z);
							printf("%f %f %f\n", fe.v_f.x, te[i].v_f.y, fe.v_f.z);
						}




					}
				}
			}
			/*seperate and insert for reversal */
			/*................................*/

			else if (fe.v_s.x == te[i].v_f.x AND fe.v_f.x == te[i].v_s.x)
			{


				for (j = 1; j <= NOES; j++)
				{
					if (se[j].ide == 5)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y AND fe.v_s.z == se[j].v_s.z)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y AND fe.v_s.z == se[j].v_s.z))
						{
							printf("\t(*)\n");
							//set_colour(0,1,0);

							temp.v_s.x = fe.v_s.x;
							temp.v_s.z = fe.v_s.z;

							temp.v_f.x = fe.v_f.x;
							temp.v_f.z = fe.v_f.z;
							temp.v_f.y = te[i].v_s.y;
							temp.v_s.y = te[i].v_f.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fe.v_s.x, se[j].v_s.y, fe.v_s.z);
							printf("%f %f %f\n", fe.v_f.x, se[j].v_f.y, fe.v_f.z);
						}




					}
				}
			}
			/*................................*/
		}
	}
}


/************************************************
NAME : function_3()
*************************************************/


void function_3(edge fe, vertex tv[], edge se[], edge p_edge[])
{
	int i, j;
	edge temp;
	printf(" I am in FUNCTION - 3:\n");
	printf("-----------------------\n");
	for (j = 1; j <= NOES; j++)
	{
		if (se[j].ide == 2)
		{
			if ((fe.v_s.z == se[j].v_s.z AND fe.v_f.z == se[j].v_f.z) OR(fe.v_s.z == se[j].v_f.z AND
				fe.v_f.z == se[j].v_s.z))
			{
				for (i = 1; i <= NOET; i++)
				{
					if (se[j].v_s.y == tv[i].y AND fe.v_s.x == tv[i].x)
					{

						printf("\t(*)\n");
						printf("%f %f %f\n", fe.v_s.x, tv[i].y, fe.v_s.z);
						printf("%f %f %f\n", fe.v_f.x, tv[i].y, fe.v_f.z);
						/* CREATING A 3D POSSIBLE EDGE */
						temp.v_s.x = fe.v_s.x;
						temp.v_s.z = fe.v_s.z;
						temp.v_s.y = tv[i].y;

						temp.v_f.x = fe.v_f.x;
						temp.v_f.z = fe.v_f.z;
						temp.v_f.y = tv[i].y;
						p_edge[e++] = temp;
					}
				}
			}
		}
	}
}


/*****************************/
/*  FUNCTION-4 */
/*****************************/

void function_4(edge fe, edge te[], edge se[], edge p_edge[]) {
	int i, j;
	edge temp;
	printf(" I am in FUNCTION - 4:\n");
	printf("-----------------------\n");
	for (j = 1; j <= NOES; j++)
	{

		if (se[j].ide == 3)
		{
			if (fe.v_s.z == se[j].v_s.z AND fe.v_f.z == se[j].v_f.z)
			{


				for (i = 1; i <= NOET; i++)
				{
					if (te[i].ide == 5)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y AND fe.v_s.x == te[i].v_s.x)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y AND fe.v_s.x == te[i].v_s.x))
						{
							printf("\t(*)\n");

							temp.v_s.x = fe.v_s.x;
							temp.v_s.z = fe.v_s.z;
							temp.v_s.y = se[j].v_s.y;

							temp.v_f.x = fe.v_f.x;
							temp.v_f.z = fe.v_f.z;
							temp.v_f.y = se[j].v_f.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fe.v_s.x, se[j].v_s.y, fe.v_s.z);
							printf("%f %f %f\n", fe.v_f.x, se[j].v_f.y, fe.v_f.z);
						}
					}
				}
			}

			//-----------------------//

			if (fe.v_s.z == se[j].v_f.z AND fe.v_f.z == se[j].v_s.z)
			{


				for (i = 1; i <= NOET; i++)
				{
					if (te[i].ide == 5)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y  AND fe.v_s.x == te[i].v_s.x)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y  AND fe.v_s.x == te[i].v_s.x))
						{
							printf("\t(*)\n");

							temp.v_s.x = fe.v_s.x;
							temp.v_s.z = fe.v_s.z;
							temp.v_s.y = se[j].v_f.y;

							temp.v_f.x = fe.v_f.x;
							temp.v_f.z = fe.v_f.z;
							temp.v_f.y = se[j].v_s.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fe.v_s.x, se[j].v_s.y, fe.v_s.z);
							printf("%f %f %f\n", fe.v_f.x, se[j].v_f.y, fe.v_f.z);
						}
					}
				}
			}
			/*_______________________*/
		}
	}
}
/************************************************/
/*         FUNCTION--5   */

/*************************************************/

void function_5(edge fe, edge te[], edge se[], edge p_edge[]) {
	int i, j;
	edge temp;
	printf(" I am in FUNCTION - 5:\n");
	printf("-----------------------\n");
	for (i = 1; i <= NOET; i++)
	{

		if (te[i].ide == 1)
		{
			if (fe.v_s.x == te[i].v_s.x AND fe.v_f.x == te[i].v_f.x)
			{


				for (j = 1; j <= NOES; j++)
				{
					if (se[j].ide == 2)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y))
						{
							printf("\t(*)\n");

							temp.v_s.x = fe.v_s.x;
							temp.v_s.z = fe.v_s.z;
							temp.v_s.y = te[i].v_s.y;

							temp.v_f.x = fe.v_f.x;
							temp.v_f.z = fe.v_f.z;
							temp.v_f.y = te[i].v_f.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fe.v_s.x, te[i].v_s.y, fe.v_s.z);
							printf("%f %f %f\n", fe.v_f.x, te[i].v_f.y, fe.v_f.z);
							printf("%f\t", se[j].v_s.y);
							printf("%f\t", se[j].v_s.y);
						}
					}
				}
			}


			/*   INSERT HERE */

			if (fe.v_s.x == te[i].v_f.x AND fe.v_f.x == te[i].v_s.x)
			{


				for (j = 1; j <= NOES; j++)
				{
					if (se[j].ide == 2)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y))
						{
							printf("\t(*)\n");

							temp.v_s.x = fe.v_s.x;
							temp.v_s.z = fe.v_s.z;
							temp.v_s.y = te[i].v_f.y;

							temp.v_f.x = fe.v_f.x;
							temp.v_f.z = fe.v_f.z;
							temp.v_f.y = te[i].v_s.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fe.v_s.x, te[i].v_s.y, fe.v_s.z);
							printf("%f %f %f\n", fe.v_f.x, te[i].v_f.y, fe.v_f.z);
							printf("%f\t", se[j].v_s.y);
							printf("%f\t", se[j].v_s.y);
						}
					}
				}
			}
			/*..............*/

		}
	}
}
/************************************************/
/* FUNCYION - 6 */
/*************************************************/

void function_6(edge fe, edge te[], edge se[], edge p_edge[]) {
	int i, j;
	edge temp;
	printf(" I am in FUNCTION - 6:\n");
	printf("-----------------------\n");
	for (i = 1; i <= NOET; i++)
	{

		if (te[i].ide == 3)
		{
			if (fe.v_s.x == te[i].v_s.x AND fe.v_f.x == te[i].v_f.x)
			{


				for (j = 1; j <= NOES; j++)
				{
					if (se[j].ide == 3)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y))
						{
							printf("\t(*)\n");

							temp.v_s.x = fe.v_s.x;
							temp.v_s.z = fe.v_s.z;
							temp.v_s.y = te[i].v_s.y;

							temp.v_f.x = fe.v_f.x;
							temp.v_f.z = fe.v_f.z;
							temp.v_f.y = te[i].v_f.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fe.v_s.x, te[i].v_s.y, fe.v_s.z);
							printf("%f %f %f\n", fe.v_f.x, te[i].v_f.y, fe.v_f.z);
						}
					}
				}
			}
			/*   INSERT here */

			if (fe.v_s.x == te[i].v_f.x AND fe.v_f.x == te[i].v_s.x)
			{


				for (j = 1; j <= NOES; j++)
				{
					if (se[j].ide == 3)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y))
						{
							printf("\t(*)\n");

							temp.v_s.x = fe.v_s.x;
							temp.v_s.z = fe.v_s.z;
							temp.v_s.y = te[i].v_f.y;

							temp.v_f.x = fe.v_f.x;
							temp.v_f.z = fe.v_f.z;
							temp.v_f.y = te[i].v_s.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fe.v_s.x, te[i].v_s.y, fe.v_s.z);
							printf("%f %f %f\n", fe.v_f.x, te[i].v_f.y, fe.v_f.z);
						}
					}
				}
			}
			/*--------------------------*/


		}
	}
}
/************************************************/
/* FUNCTION - 7 */
/*************************************************/

void function_7(vertex fv, edge te[], edge se[], edge p_edge[]) {
	int i, j;
	edge temp;
	printf(" I am in FUNCTION - 7:\n");
	printf("-----------------------\n");
	for (i = 1; i <= NOET; i++)
	{

		if (te[i].ide == 5)
		{
			if ((fv.x == te[i].v_s.x AND fv.x == te[i].v_f.x)
				OR
				(fv.x == te[i].v_f.x AND fv.x == te[i].v_s.x))
			{


				for (j = 1; j <= NOES; j++)
				{
					if (se[j].ide == 5)
					{
						if ((te[i].v_s.y == se[j].v_s.y AND te[i].v_f.y == se[j].v_f.y AND fv.z == se[j].v_s.z)
							OR
							(te[i].v_s.y == se[j].v_f.y AND te[i].v_f.y == se[j].v_s.y AND fv.z == se[j].v_s.z))
						{
							printf("\t(*)\n");

							temp.v_s.x = fv.x;
							temp.v_s.z = fv.z;
							temp.v_s.y = te[i].v_s.y;

							temp.v_f.x = fv.x;
							temp.v_f.z = fv.z;
							temp.v_f.y = te[i].v_f.y;
							p_edge[e++] = temp;
							printf("%f %f %f\n", fv.x, te[i].v_s.y, fv.z);
							printf("%f %f %f\n", fv.x, te[i].v_f.y, fv.z);
							/*		printf("%f\t",se[j].v_s.y);
							printf("%f\t",se[j].v_s.y); */
						}
					}
				}
			}
		}
	}
}


void wire()
{

	vertex tv[100], fv[100], sv[100], p_vertex[400], temp1;
	edge  te[100], fe[100], se[100], temp;
	int i, n1, n2, index, flag;
	float xdiff, ydiff, zdiff;
/*	void function_1();
	void function_2();
	void function_3();
	void function_4();
	void function_5();
	void function_6();
	void function_7();*/
	printf("MAIN:\n");

	printf("ENTER THE NO OF VERTICES  IN FRONT VIEW :\t");
	cin >> NOVF;
	printf("\n");
	printf("Read The Front Vertices Set:\n");
	printf("x_coordinate       z_coordinate\n");
	for (i = 1; i <= NOVF; i++)
		scanf_s("%f%f", &fv[i].x, &fv[i].z);

	printf("ENTER THE NO OF VERTICES  IN TOP VIEW :\t");
	scanf_s("%d", &NOVT);
	printf("\n");
	printf("Read The Top Vertices Set:\n");
	printf("x_coordinate       y_coordinate\n");
	for (i = 1; i <= NOVT; i++)
		scanf_s("%f%f", &tv[i].x, &tv[i].y);

	printf("ENTER THE NO OF VERTICES  IN SIDE VIEW :\t");
	scanf_s("%d", &NOVS);
	printf("\n");
	printf("Read The Side Vertices Set:\n");
	printf("y_coordinate       z_coordinate\n");
	for (i = 1; i <= NOVS; i++)
		scanf_s("%f%f", &sv[i].y, &sv[i].z);

	printf("(Front Vertices Set:)\n");
	printf("x_coordinate       z_coordinate\n");
	for (i = 1; i <= NOVF; i++)
		printf("%f   %f\n", fv[i].x, fv[i].z);


	printf("(Top Vertices Set:)\n");
	printf("(x_coordinate       y_coordinate)\n");
	for (i = 1; i <= NOVT; i++)
		printf("%f      %f\n", tv[i].x, tv[i].y);

	printf("(Side Vertices Set:)\n");
	printf("y_coordinate       z_coordinate\n");
	for (i = 1; i <= NOVS; i++)
		printf("%f    %f\n", sv[i].y, sv[i].z);

	printf("EDGE INPUT:-->\n");



	printf("ENTER THE NO OF EDGES IN TOP  VIEW :\t");
	scanf_s("%d", &NOET);
	printf("\n");
	printf("TOP EDGE\n");
	printf("start_vertex_no            finish_vertex_no\n");
	for (i = 1; i <= NOET; i++)
	{
		scanf_s("%d%d", &n1, &n2);
		te[i].v_s.x = tv[n1].x;
		te[i].v_s.y = tv[n1].y;
		te[i].v_f.x = tv[n2].x;
		te[i].v_f.y = tv[n2].y;


		// set_colour(1,0,0);
		//  line_draw(te[i].v_s.x,te[i].v_s.y,0,te[i].v_f.x,te[i].v_f.y,0);
		ydiff = tv[n1].y - tv[n2].y;
		xdiff = tv[n1].x - tv[n2].x;
		if (fabs(ydiff) < EPS)
		{
			te[i].ide = 1;  index = 1;
		}
		else   if (fabs(xdiff) < EPS)
		{
			te[i].ide = 5;  index = 5;
		}
		else
		{
			te[i].ide = 3;  index = 3;
		}
	}

	printf("SIDE EDGE\n");
	printf("ENTER THE NO OF EDGES IN SIDE  VIEW :\t");
	scanf_s("%d", &NOES);
	printf("\n");
	printf("start_vertex_no            finish_vertex_no\n");
	for (i = 1; i <= NOES; i++)
	{
		scanf_s("%d%d", &n1, &n2);
		se[i].v_s.y = sv[n1].y;
		se[i].v_s.z = sv[n1].z;
		se[i].v_f.y = sv[n2].y;
		se[i].v_f.z = sv[n2].z;
		ydiff = sv[n1].y - sv[n2].y;
		zdiff = sv[n1].z - sv[n2].z;
		if (fabs(ydiff) < EPS)
		{
			se[i].ide = 2;  index = 2;
		}
		else   if (fabs(zdiff) < EPS)
		{
			se[i].ide = 5;  index = 5;
		}
		else
		{
			se[i].ide = 3;  index = 3;
		}
		//  set_colour(1,0,0);
		//  line_draw(0,sv[n1].y,sv[n1].z,0,sv[n2].y,sv[n2].z);
	}


	printf("ENTER THE NO OF EDGES IN FRONT VIEW :\t");
	scanf_s("%d", &NOEF);
	printf("\n");
	printf("FRONT EDGE\n");
	printf("start_vertex_no            finish_vertex_no\n");
	for (i = 1; i <= NOEF; i++)
	{
		scanf_s("%d%d", &n1, &n2);
		fe[i].v_s.x = fv[n1].x;
		fe[i].v_s.z = fv[n1].z;
		fe[i].v_f.x = fv[n2].x;
		fe[i].v_f.z = fv[n2].z;
		zdiff = fv[n1].z - fv[n2].z;
		xdiff = fv[n1].x - fv[n2].x;
		if (fabs(zdiff) < EPS)
		{
			fe[i].ide = 1;  index = 1;
		}
		else if (fabs(xdiff) < EPS)
		{
			fe[i].ide = 2;  index = 1;
		}
		else
		{
			fe[i].ide = 3;  index = 1;
		}
		temp = fe[i];
		temp1 = fv[i];
		flag = temp.ide;


		printf("This edge belongs to the case  : %d \n", flag);
		//   set_colour(1,0,0);
		//   line_draw(fe[i].v_s.x,0,fe[i].v_s.z,fe[i].v_f.x,0,fe[i].v_f.z);
		switch (flag)
		{

		case 1:    	
			function_1(temp, sv, te, p_edge);
			function_2(temp, se, te, p_edge);
			break;
		case 2: 	
			function_3(temp, tv, se, p_edge);
			function_4(temp, te, se, p_edge);
			break;
		case 3:     	
			function_5(temp, te, se, p_edge);
			function_6(temp, te, se, p_edge);
			break;

		}
		function_7(temp1, te, se, p_edge);

	}
	//sleep(1);
	//clear_window();
	//  set_colour(1,1,0);
	//  line_draw(0,0,0,20,0,0);
	//  set_colour(1,0,0);
	//  line_draw(0,0,0,0,20,0);
	//  set_colour(0,0,1);
	//  line_draw(0,0,0,0,0,20);
	for (i = 1; i<e; i++)
	{


		printf("s.no. %d  %f  %f  %f", i, p_edge[i].v_s.x, p_edge[i].v_s.y, p_edge[i].v_s.z);
		printf("\t%f  %f  %f\n", p_edge[i].v_f.x, p_edge[i].v_f.y, p_edge[i].v_f.z);
		//  set_colour(0,1,0);
		//  line_draw(p_edge[i].v_s.x,p_edge[i].v_s.y,p_edge[i].v_s.z, p_edge[i].v_f.x,p_edge[i].v_f.y,p_edge[i].v_f.z);

	}
	//final_val = p_edge;
	/*END OF THE MAIN */
}

/*

int main(int argc, char **argv) {
	wire();
	return 0;
}


*/





GLfloat xRotated, yRotated, zRotated;
void init(void)
{
	glClearColor(0, 0, 0, 0);

}

void DrawCube(void)
{

	glMatrixMode(GL_MODELVIEW);
	// clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.5);
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);        // Draw The Cube Using quads
	
	glColor3f(0.0f, 1.0f, 0.0f);    // Color Blue
	int i;

	for (i = 0; i < e; i++) {
		glVertex3f(p_edge[i].v_s.x, p_edge[i].v_s.y, p_edge[i].v_s.z); glVertex3f(p_edge[i].v_f.x, p_edge[i].v_f.y, p_edge[i].v_f.z);
	}
	glEnd();            // End Drawing The Cube
	glFlush();
}


void animation(void)
{

	yRotated += 0.01;
	xRotated += 0.02;
	DrawCube();
}


void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
								   //Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0

	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);  //Use the whole window for rendering
}

int main(int argc, char** argv) {
	
	wire();
	
	glutInit(&argc, argv);
	//we initizlilze the glut. functions
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(DrawCube);
	glutReshapeFunc(reshape);
	//Set the function for the animation.
	glutIdleFunc(animation);
	glutMainLoop();
	return 0;
}