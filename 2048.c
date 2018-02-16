#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ENTER 10
#define FOREVER 1
#define KEYBOARD 0
#define S_TO_WAIT 10
#define MILIS_TO_WAIT 0
#define SELECT_EVENT		1
#define SELECT_NO_EVENT		0

int a[5][5],score,prev[5][5],prevscore;
void draw_box(int l, int c, int x, int y)
{
	int i;
	mvaddch(x,y,ACS_ULCORNER);
	mvaddch(x+l-1,y+c-1,ACS_LRCORNER);
	mvaddch(x,y+c-1,ACS_URCORNER);
	mvaddch(x+l-1,y,ACS_LLCORNER);
	for(i=1;i<c-1;i++)
		{
			mvaddch(x,y+i,ACS_HLINE);
			mvaddch(x+l-1,y+i,ACS_HLINE);
		}
	for(i=1;i<l-1;i++)
	{
		mvaddch(x+i,y,ACS_VLINE);
		mvaddch(x+i,y+c-1,ACS_VLINE);
	}
}
void draw_menu(int position,int res)
{
	clear();
	if(res==0)
	{
		mvprintw(4,10,"New Game");
		mvprintw(5,10,"Resume*");
		mvprintw(6,10,"Quit");
		mvaddch(3+position,7,ACS_HLINE);
		mvaddch(3+position,8,ACS_HLINE);
		mvaddch(3+position,9,ACS_RARROW);
	}
	else
	{
		mvprintw(4,10,"New Game");
		mvprintw(5,10,"Resume");
		mvprintw(6,10,"Quit");
		mvaddch(3+position,7,ACS_HLINE);
		mvaddch(3+position,8,ACS_HLINE);
		mvaddch(3+position,9,ACS_RARROW);
	}
	mvaddch(2,12,ACS_HLINE);
	mvaddch(2,13,ACS_HLINE);
	mvaddch(2,14,ACS_RARROW);
	mvaddch(2,40,ACS_LARROW);
	mvaddch(2,41,ACS_HLINE);
	mvaddch(2,42,ACS_HLINE);
	mvprintw(2,15,"WELCOME TO THE GAME 2048!");
	mvprintw(10,9,"NAVIGATE THE MENU USING THE ARROW KEYS");
	mvprintw(11,9,"SELECT A MENU BY PRESSING ENTER");
	mvprintw(12,9,"*=THE MENU IS NOT ACCESSIBLE");
	draw_box(13,43,1,6);
	refresh();
}
int check2048()
{
	int i,j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			if(a[i][j]>=2048)
				return 1;
	return 0;
}
int comparare_matrice(int x[5][5],int y[5][5])
{
	int i,j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			if(x[i][j]!=y[i][j])
				return 0;
	return 1;
}
void copiere_matrice(int loc[5][5])
{
	int i,j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			loc[i][j]=a[i][j];
}
void miscare_sus(int scop, int *rezultat, int *miscari)//scop=1 pentru mutare, 0 pentru evaluare
{
	int copie[5][5],prevbak[5][5];
	copiere_matrice(copie);
	if(scop==1)
		{
		    int i,j;
			for(i=1;i<=4;i++)
				for(j=1;j<=4;j++)
					prevbak[i][j]=prev[i][j];
			copiere_matrice(prev);
			prevscore=score;
		}
	int i,locscore=0;
	for(i=1;i<=4;i++)
	{
		int cont=0,j,v[5];
		for(j=1;j<=4;j++)
			if(copie[j][i]!=0)
			{
				cont++;
				v[cont]=copie[j][i];
			}
		for(j=1;j<cont;j++)
			if(v[j]==v[j+1])
			{
				v[j+1]=2*v[j+1];
				(*miscari)++;
				locscore=locscore+v[j+1];
				int k;
				for(k=j;k<cont;k++)
					v[k]=v[k+1];
				cont--;
			}
		for(j=1;j<=cont;j++)
			copie[j][i]=v[j];
		for(j=cont+1;j<=4;j++)
			copie[j][i]=0;
	}
	if(comparare_matrice(a,copie)==1)
		*(rezultat)=0;
	else
		*(rezultat)=1;
	if(*(rezultat)==0 && scop==1)
	{
		int i,j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				prev[i][j]=prevbak[i][j];
	}
	if(scop==1)
	{
		int j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				a[i][j]=copie[i][j];
		score=score+locscore;
	}
}
void miscare_stanga(int scop, int *rezultat, int *miscari)//1 pentru mutare, 0 pentru evaluare
{
	int copie[5][5],prevbak[5][5];
	copiere_matrice(copie);
	if(scop==1)
		{
			int i,j;
			for(i=1;i<=4;i++)
				for(j=1;j<=4;j++)
					prevbak[i][j]=prev[i][j];
			copiere_matrice(prev);
			prevscore=score;
		}
	int i,locscore=0;
	for(i=1;i<=4;i++)
	{
		int cont=0,j,v[5];
		for(j=1;j<=4;j++)
			if(copie[i][j]!=0)
			{
				cont++;
				v[cont]=copie[i][j];
			}
		for(j=1;j<cont;j++)
			if(v[j]==v[j+1])
			{
				v[j+1]=2*v[j+1];
				(*miscari)++;
				locscore=locscore+v[j+1];
				int k;
				for(k=j;k<cont;k++)
					v[k]=v[k+1];
				cont--;
			}
		for(j=1;j<=cont;j++)
			copie[i][j]=v[j];
		for(j=cont+1;j<=4;j++)
			copie[i][j]=0;
	}
	if(comparare_matrice(a,copie)==1)
		*(rezultat)=0;
	else
		*(rezultat)=1;
	if(*(rezultat)==0 && scop==1)
	{
		int i,j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				prev[i][j]=prevbak[i][j];
	}
	if(scop==1)
	{
		int j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				a[i][j]=copie[i][j];
		score=score+locscore;
	}

}
void miscare_jos(int scop, int *rezultat, int *miscari)//1 pentru mutare, 0 pentru evaluare
{
	int copie[5][5],prevbak[5][5];
	copiere_matrice(copie);
	if(scop==1)
		{
		    int i,j;
			for(i=1;i<=4;i++)
				for(j=1;j<=4;j++)
					prevbak[i][j]=prev[i][j];
			copiere_matrice(prev);
			prevscore=score;
		}
	int i,locscore=0;
	for(i=1;i<=4;i++)
	{
		int cont=0,j,v[5];
		for(j=4;j>=1;j--)
			if(copie[j][i]!=0)
			{
				cont++;
				v[cont]=copie[j][i];
			}
		for(j=1;j<cont;j++)
			if(v[j]==v[j+1])
			{
				v[j+1]=2*v[j+1];
				(*miscari)++;
				locscore=locscore+v[j+1];
				int k;
				for(k=j;k<cont;k++)
					v[k]=v[k+1];
				cont--;
			}
		for(j=1;j<=cont;j++)
			copie[4-j+1][i]=v[j];
		for(j=cont+1;j<=4;j++)
			copie[4-j+1][i]=0;
	}
	if(comparare_matrice(a,copie)==1)
		*(rezultat)=0;
	else
		*(rezultat)=1;
	if(*(rezultat)==0 && scop==1)
	{
		int i,j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				prev[i][j]=prevbak[i][j];
	}
	if(scop==1)
	{
		int j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				a[i][j]=copie[i][j];
		score=score+locscore;
	}
}
void miscare_dreapta(int scop, int *rezultat, int *miscari)//1 pentru mutare, 0 pentru evaluare
{
	int copie[5][5],prevbak[5][5];
	copiere_matrice(copie);
	if(scop==1)
		{
		    int i,j;
			for(i=1;i<=4;i++)
				for(j=1;j<=4;j++)
					prevbak[i][j]=prev[i][j];
			copiere_matrice(prev);
			prevscore=score;
		}
	int i,locscore=0;
	for(i=1;i<=4;i++)
	{
		int cont=0,j,v[5];
		for(j=4;j>=1;j--)
			if(copie[i][j]!=0)
			{
				cont++;
				v[cont]=copie[i][j];
			}
		for(j=1;j<cont;j++)
			if(v[j]==v[j+1])
			{
				v[j+1]=2*v[j+1];
				(*miscari)++;
				locscore=locscore+v[j+1];
				int k;
				for(k=j;k<cont;k++)
					v[k]=v[k+1];
				cont--;
			}
		for(j=1;j<=cont;j++)
			copie[i][4-j+1]=v[j];
		for(j=cont+1;j<=4;j++)
			copie[i][4-j+1]=0;
	}
	if(comparare_matrice(a,copie)==1)
		*(rezultat)=0;
	else
		*(rezultat)=1;
	if(*(rezultat)==0 && scop==1)
	{
		int i,j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				prev[i][j]=prevbak[i][j];
	}
	if(scop==1)
	{
		int j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				a[i][j]=copie[i][j];
		score=score+locscore;
	}
}
void init_matrice()
{
	int i,j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			a[i][j]=0;
}
void generare()
{
	int val,loc=0,aux=0;
	val=rand();
	if(val%4==0)
		val=4;
	else
		val=2;
	int i,j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			if(a[i][j]==0)
				loc++;
	loc=(rand()%loc)+1;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			{
				if(a[i][j]==0)
				{
					aux++;
					if(aux==loc)
						{
							a[i][j]=val;
							break;
						}

				}
			}
}
int color_codesv(int val)
{
	switch(val)
	{
		case 2:return 1;break;
		case 4:return 2;break;
		case 8:return 3;break;
		case 16:return 4;break;
		case 32:return 5;break;
		case 64:return 6;break;
		case 128:return 7;break;
		case 256:return 8;break;
		case 512:return 9;break;
		case 1024:return 10;break;
		case 2048:return 11;break;
	}
	return 12;
}
void print_square(int x, int y, int val)
{
	int i,xi;
	xi=color_codesv(val);
	if(xi!=12)
		attron(COLOR_PAIR(xi));
	mvprintw(4*(x-1)+2,5*(y-1)+2,"    ");
	mvprintw(4*(x-1)+3,5*(y-1)+2,"    ");
	mvprintw(4*(x-1)+4,5*(y-1)+2,"    ");
	if(val!=0)
		mvprintw(4*(x-1)+3,5*(y-1)+2,"%d",val);
	if(xi!=12)
		attroff(COLOR_PAIR(xi));
	for(i=1;i<=4;i++)
	{
		mvaddch((x-1)*4+1,(y-1)*5+1+i,ACS_HLINE);
		mvaddch((x)*4+1,(y-1)*5+1+i,ACS_HLINE);
	}
	mvaddch((x-1)*4+1+1,(y-1)*5+1,ACS_VLINE);
	mvaddch((x-1)*4+1+1,(y-1)*5+1+5,ACS_VLINE);
	mvaddch((x)*4-1+1,(y-1)*5+1,ACS_VLINE);
	mvaddch((x)*4-1+1,(y-1)*5+1+5,ACS_VLINE);
	mvaddch((x-1)*4+2+1,(y-1)*5+1,ACS_VLINE);
	mvaddch((x-1)*4+2+1,(y)*5+1,ACS_VLINE);
	if(x==1 && y==1)
	{
		mvaddch(4*(x-1)+1,5*(y-1)+1,ACS_ULCORNER);
		mvaddch(4*(x-1)+1+4,5*(y-1)+1,ACS_LTEE);
		mvaddch(4*(x-1)+1+4,5*(y-1)+1+5,ACS_PLUS);
		mvaddch(4*(x-1)+1,5*(y-1)+1+5,ACS_TTEE);
	}
	else
		if(x==1 && y==4)
		{
			mvaddch(4*(x-1)+1,5*(y-1)+1,ACS_TTEE);
			mvaddch(4*(x-1)+1+4,5*(y-1)+1,ACS_PLUS);
			mvaddch(4*(x-1)+1+4,5*(y-1)+1+5,ACS_RTEE);
			mvaddch(4*(x-1)+1,5*(y-1)+1+5,ACS_URCORNER);
		}
		else
			if(x==4 && y==1)
			{
				mvaddch(4*(x-1)+1,5*(y-1)+1,ACS_LTEE);
				mvaddch(4*(x-1)+1+4,5*(y-1)+1,ACS_LLCORNER);
				mvaddch(4*(x-1)+1+4,5*(y-1)+1+5,ACS_BTEE);
				mvaddch(4*(x-1)+1,5*(y-1)+1+5,ACS_PLUS);
			}
			else
				if(x==4 && y==4)
				{
					mvaddch(4*(x-1)+1,5*(y-1)+1,ACS_PLUS);
					mvaddch(4*(x-1)+1+4,5*(y-1)+1,ACS_BTEE);
					mvaddch(4*(x-1)+1+4,5*(y-1)+1+5,ACS_LRCORNER);
					mvaddch(4*(x-1)+1,5*(y-1)+1+5,ACS_RTEE);
				}
				else
					if(x==1)
					{
							mvaddch(4*(x-1)+1,5*(y-1)+1+5,ACS_TTEE);
					}
					else
						if(y==1)
						{
							mvaddch(4*(x-1)+1+4,5*(y-1)+1,ACS_LTEE);
						}
						else
							if(x==4)
							{
								mvaddch(4*(x-1)+1+4,5*(y-1)+1,ACS_BTEE);
							}
							else
								if(y==4)
								{
									mvaddch(4*(x-1)+1+4,5*(y-1)+1+5,ACS_RTEE);
								}
								else
								{
									mvaddch(4*(x-1)+1,5*(y-1)+1,ACS_PLUS);
									mvaddch(4*(x-1)+1+4,5*(y-1)+1,ACS_PLUS);
									mvaddch(4*(x-1)+1+4,5*(y-1)+1+5,ACS_PLUS);
									mvaddch(4*(x-1)+1,5*(y-1)+1+5,ACS_PLUS);
								}
}
void print_date(int year,int month, int day)
{
	char *mon=NULL;
	mon=malloc(15*sizeof(char));
	switch(month)
	{
		case 1:strcpy(mon,"January");break;
		case 2:strcpy(mon,"February");break;
		case 3:strcpy(mon,"March");break;
		case 4:strcpy(mon,"April");break;
		case 5:strcpy(mon,"May");break;
		case 6:strcpy(mon,"June");break;
		case 7:strcpy(mon,"July");break;
		case 8:strcpy(mon,"August");break;
		case 9:strcpy(mon,"September");break;
		case 10:strcpy(mon,"October");break;
		case 11:strcpy(mon,"November");break;
		case 12:strcpy(mon,"December");break;
	}
	if(day%10==1 && day!=11)
		mvprintw(3,35,"%dst of %s, %d",day,mon,year);
	else
		if(day%10==2 && day!=12)
			mvprintw(3,35,"%dnd of %s, %d",day,mon,year);
		else
			if(day%10==3 && day!=13)
				mvprintw(3,35,"%drd of %s, %d",day,mon,year);
			else
				mvprintw(3,35,"%dth of %s, %d",day,mon,year);
	free(mon);
}
void print_table(int score,int highscore)
{
	int i,j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
		{
			print_square(i,j,a[i][j]);
		}
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	mvprintw(2,35,"DATE:");
	print_date(tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
	mvprintw(6,35,"TIME:");
	mvprintw(7,35,"%d:%d",tm.tm_hour,tm.tm_min);
	draw_box(4,26,1,34);
	draw_box(5,10,5,23);//hiscore
	mvprintw(6,24,"HISCORE:");
	mvprintw(8,24,"%d",highscore);
	draw_box(4,8,5,34);
	mvprintw(2,24,"SCORE:");
	mvprintw(3,24,"%d",score);
	draw_box(4,10,1,23);//score
	draw_box(24,71,0,0);
	int aux1,aux2,aux3,aux4,aux;
	miscare_jos(0,&aux1,&aux);
	miscare_sus(0,&aux2,&aux);
	miscare_dreapta(0,&aux3,&aux);
	miscare_stanga(0,&aux4,&aux);
	mvprintw(6,44,"POSSIBLE MOVES:");
	if(aux2==1)
		mvaddch	(7,51,ACS_UARROW);
	else
		mvprintw(7,51," ");
	if(aux1==1)
		mvprintw(9,51,"v");
	else
		mvprintw(9,51," ");
	if(aux3==1)
		mvaddch(8,53,ACS_RARROW);
	else
		mvprintw(8,53," ");
	if(aux4==1)
		mvaddch(8,49,ACS_LARROW);
	else
		mvprintw(8,49," ");
	if(aux1+aux2+aux3+aux4==0)
		mvprintw(8,51,"X");
	else
		mvprintw(8,51," ");
	draw_box(6,17,5,43);
	mvaddch(12,26-1,ACS_ULCORNER);
	mvaddch(12,27-1,ACS_HLINE);
	mvaddch(12,28-1,ACS_URCORNER);
	mvaddch(13,28-1,ACS_VLINE);
	mvaddch(14,28-1,ACS_LRCORNER);
	mvaddch(14,27-1,ACS_HLINE);
	mvaddch(14,26-1,ACS_ULCORNER);
	mvaddch(15,26-1,ACS_VLINE);
	mvaddch(16,26-1,ACS_LLCORNER);
	mvaddch(16,27-1,ACS_HLINE);
	mvaddch(16,28-1,ACS_LRCORNER);
	draw_box(5,3,12,30-1);
	mvaddch(12,34-1,ACS_TTEE);
	mvaddch(13,34-1,ACS_VLINE);
	mvaddch(14,34-1,ACS_LLCORNER);
	mvaddch(14,35-1,ACS_HLINE);
	mvaddch(14,36-1,ACS_PLUS);
	mvaddch(15,36-1,ACS_VLINE);
	mvaddch(16,36-1,ACS_BTEE);
	draw_box(3,3,12,38-1);
	draw_box(3,3,14,38-1);
	mvaddch(14,38-1,ACS_LTEE);
	mvaddch(14,40-1,ACS_RTEE);
	attron(A_BOLD);
	mvprintw(12,41,"2+2=4");
	mvprintw(13,41,"4+4=8");
	mvprintw(14,41,"8+8=16");
	mvprintw(15,41,". . . ");
	mvprintw(12,47," COMBINE THE");
	mvprintw(13,47,"EQUAL NUMBERS");
	attroff(A_BOLD);
	mvprintw(14,52,"and");
	attron(A_BOLD);
	mvprintw(15,47," REACH 2048!!");
	attroff(A_BOLD);
	draw_box(7,40,11,23);
	refresh();
}
int main() 
{   
	FILE *f;   
	int actiune,continuare,pozitie=1,res=0,highscore=0;
	int nfds, sel;
	fd_set read_descriptors;
	struct timeval timeout;
	nfds = 1;
	FD_ZERO(&read_descriptors);
	FD_SET(KEYBOARD, &read_descriptors);
	timeout.tv_sec = S_TO_WAIT;
	timeout.tv_usec = MILIS_TO_WAIT;
	continuare=1;
	f=fopen("savegame","r");
	fscanf(f,"%d",&res);
	if(res==1)
	{
		int i,j;
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				fscanf(f,"%d",&a[i][j]);
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
				fscanf(f,"%d",&prev[i][j]);
		fscanf(f,"%d%d",&score,&prevscore);
	}
	fscanf(f,"%d",&highscore);
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	init_pair(1,COLOR_BLACK,COLOR_YELLOW);
	init_pair(2,COLOR_BLACK,COLOR_RED);
	init_pair(3,COLOR_BLACK,COLOR_GREEN);
	init_pair(4,COLOR_BLACK,COLOR_MAGENTA);
	init_pair(5,COLOR_BLACK,COLOR_CYAN);
	init_pair(6,COLOR_BLACK,COLOR_BLUE);
	init_pair(7,COLOR_BLUE,COLOR_YELLOW);
	init_pair(8,COLOR_BLUE,COLOR_RED);
	init_pair(9,COLOR_BLUE,COLOR_GREEN);
	init_pair(10,COLOR_BLUE,COLOR_MAGENTA);
	init_pair(11,COLOR_BLUE,COLOR_CYAN);
	srand(time(NULL));
	draw_menu(pozitie,res);
	while(continuare==1)
	{
		actiune=getch();
		if(actiune==KEY_UP)
		{
			if(pozitie>1)
			{
				pozitie--;
				draw_menu(pozitie,res);
			}
		}
		if(actiune==KEY_DOWN)
		{
			if(pozitie<3)
			{
				pozitie++;
				draw_menu(pozitie,res);
			}
		}
		if(actiune==ENTER)
		{
			if(pozitie==1)
			{
				int stadiu=1;
				score=0;
				prevscore=0;
				clear();
				init_matrice();
				generare();
				generare();
				print_table(score,highscore);
				mvprintw(20,2,"USE THE ARROW KEYS TO MOVE THE TILES");
				mvprintw(21,2,"PRESS Q TO EXIT THE GAME (YOU'LL BE ABLE TO RESUME IT, IF YOU WANT)");
				mvprintw(22,2,"PRESS Z TO UNDO THE LAST MOVE (YOU CANNOT UNDO TWICE IN A ROW)");
				copiere_matrice(prev);
				refresh();
				do
				{
					int directie,aux,auxm=0;
					int aux1,aux2,aux3,aux4,miscari1,miscari2,miscari3,miscari4;
					sel=select(nfds, &read_descriptors, NULL, NULL, &timeout);
					switch(sel)
					{
						case SELECT_EVENT:
							directie=getch();
							if(directie==KEY_DOWN)
								miscare_jos(1,&aux,&auxm);
							else
								if(directie==KEY_UP)
									miscare_sus(1,&aux,&auxm);
								else
									if(directie==KEY_LEFT)
										miscare_stanga(1,&aux,&auxm);
									else
										if(directie==KEY_RIGHT)
											miscare_dreapta(1,&aux,&auxm);
										else
											if(directie==122 || directie==90)
											{
												int i,j;
												for(i=1;i<=4;i++)
													for(j=1;j<=4;j++)
														a[i][j]=prev[i][j];
												score=prevscore;
												aux=0;
											}
											else	
												if(directie==113 || directie==81)
												{
													res=1;
													goto Continue1;
												}
												else
													aux=0;
							break;
						case SELECT_NO_EVENT:
							miscari1=0;miscari2=0;miscari3=0;miscari4=0;
							miscare_jos(0,&aux1,&miscari1);
							miscare_sus(0,&aux2,&miscari2);
							miscare_stanga(0,&aux3,&miscari3);
							miscare_dreapta(0,&aux4,&miscari4);
							if(aux1==1 && miscari1>=miscari2 && miscari1>=miscari3 && miscari1>=miscari4)
								miscare_jos(1,&aux,&miscari1);
							else
								if(aux4==1 && miscari4>=miscari1 && miscari4>=miscari2 && miscari4>=miscari3)
									miscare_dreapta(1,&aux,&miscari4);
								else
									if(aux2==1 && miscari2>=miscari1 && miscari2>=miscari3 && miscari2>=miscari4)
										miscare_sus(1,&aux,&miscari2);
									else
										if(aux3==1 && miscari3>=miscari1 && miscari3>=miscari2 && miscari3>=miscari4)
											miscare_stanga(1,&aux,&miscari3);
									
										
							break;
					}
					if(aux==1)
						generare();
					if(score>highscore)
						highscore=score;
					print_table(score,highscore);
					if(check2048()==1)
					{
						mvprintw(20,2,"                                      ");
						mvprintw(21,2,"                                                                   ");
						mvprintw(19,2,"CONGRATULATIONS, YOU WON!");
						mvprintw(20,2,"PRESS ANY KEY TO CONTINUE ...");
						mvprintw(22,2,"                                                                ");
						refresh();
						stadiu=0;
						res=0;
						getch();
					}
					else
					{
						auxm=0;
						int aux1,aux2,aux3,aux4;
						miscare_jos(0,&aux1,&auxm);
						miscare_sus(0,&aux2,&auxm);
						miscare_stanga(0,&aux3,&auxm);
						miscare_dreapta(0,&aux4,&auxm);
						if(aux1+aux2+aux3+aux4==0)
							{
								int z;
								mvprintw(20,2,"                                      ");
								mvprintw(21,2,"                                                                   ");
								mvprintw(19,2,"TOUGH LUCK, YOU ARE OUT OF MOVES!");
								mvprintw(20,2,"PRESS ANY KEY TO CONTINUE ...");
								refresh();
								z=getch();
								if(z==122 || z==90)
								{
									int i,j;
									for(i=1;i<=4;i++)
										for(j=1;j<=4;j++)
											a[i][j]=prev[i][j];
									score=prevscore;
									mvprintw(19,2,"                                     ");
									mvprintw(20,2,"USE THE ARROW KEYS TO MOVE THE TILES");
									mvprintw(21,2,"PRESS Q TO EXIT THE GAME (YOU'LL BE ABLE TO RESUME IT, IF YOU WANT)");
									if(score>highscore)
										highscore=score;
									print_table(score,highscore);
									refresh();
								}
								else
								{
									stadiu=0;
									res=0;
								}
							}
					}
					FD_SET(KEYBOARD, &read_descriptors);
					timeout.tv_sec = S_TO_WAIT;
					timeout.tv_usec = MILIS_TO_WAIT;
					refresh();
				}
				while(stadiu==1);
				Continue1: ;
				draw_menu(pozitie,res);
			}
			if(pozitie==2 && res==1)
			{
				int stadiu=1;
				clear();
				print_table(score,highscore);
				mvprintw(20,2,"USE THE ARROW KEYS TO MOVE THE TILES");
				mvprintw(21,2,"PRESS Q TO EXIT THE GAME (YOU'LL BE ABLE TO RESUME IT, IF YOU WANT)");
				mvprintw(22,2,"PRESS Z TO UNDO THE LAST MOVE (YOU CANNOT UNDO TWICE IN A ROW)");
				refresh();
				do
				{
					int directie,aux,auxm=0;
					int aux1,aux2,aux3,aux4,miscari1,miscari2,miscari3,miscari4;
					sel=select(nfds, &read_descriptors, NULL, NULL, &timeout);
					switch(sel)
					{
						case SELECT_EVENT:
							directie=getch();
							if(directie==KEY_DOWN)
								miscare_jos(1,&aux,&auxm);
							else
								if(directie==KEY_UP)
									miscare_sus(1,&aux,&auxm);
								else
									if(directie==KEY_LEFT)
										miscare_stanga(1,&aux,&auxm);
									else
										if(directie==KEY_RIGHT)
											miscare_dreapta(1,&aux,&auxm);
										else	
											if(directie==122 || directie==90)
											{
												int i,j;
												for(i=1;i<=4;i++)
													for(j=1;j<=4;j++)
														a[i][j]=prev[i][j];
												score=prevscore;
												aux=0;
											}
											else	
												if(directie==113 || directie==81)
												{
													res=1;
													goto Continue2;
												}
												else
													aux=0;
							break;
						case SELECT_NO_EVENT:
							miscari1=0;miscari2=0;miscari3=0;miscari4=0;
							miscare_jos(0,&aux1,&miscari1);
							miscare_sus(0,&aux2,&miscari2);
							miscare_stanga(0,&aux3,&miscari3);
							miscare_dreapta(0,&aux4,&miscari4);
							if(aux1==1 && miscari1>=miscari2 && miscari1>=miscari3 && miscari1>=miscari4)
								miscare_jos(1,&aux,&miscari1);
							else
								if(aux2==1 && miscari2>=miscari1 && miscari2>=miscari3 && miscari2>=miscari4)
									miscare_sus(1,&aux,&miscari2);
								else
									if(aux3==1 && miscari3>=miscari1 && miscari3>=miscari2 && miscari3>=miscari4)
										miscare_stanga(1,&aux,&miscari3);
									else
										if(aux4==1 && miscari4>=miscari1 && miscari4>=miscari2 && miscari4>=miscari3)
											miscare_dreapta(1,&aux,&miscari4);
							break;
					}
					if(aux==1)
						generare();
					if(score>highscore)
						highscore=score;
					print_table(score,highscore);
					if(check2048()==1)
					{
						mvprintw(20,2,"                                      ");
						mvprintw(21,2,"                                                                   ");
						mvprintw(19,2,"CONGRATULATIONS, YOU WON!");
						mvprintw(20,2,"PRESS ANY KEY TO CONTINUE ...");
						mvprintw(22,2,"                                                                ");
						refresh();
						stadiu=0;
						res=0;
						getch();
					}
					else
					{
						auxm=0;
						int aux1,aux2,aux3,aux4;
						miscare_jos(0,&aux1,&auxm);
						miscare_sus(0,&aux2,&auxm);
						miscare_stanga(0,&aux3,&auxm);
						miscare_dreapta(0,&aux4,&auxm);
						if(aux1+aux2+aux3+aux4==0)
							{
								int z;
								mvprintw(20,2,"                                      ");
								mvprintw(21,2,"                                                                   ");
								mvprintw(19,2,"TOUGH LUCK, YOU ARE OUT OF MOVES!");
								mvprintw(20,2,"PRESS ANY KEY TO CONTINUE ...");
								refresh();
								z=getch();
								if(z==122 || z==90)
								{
									int i,j;
									for(i=1;i<=4;i++)
										for(j=1;j<=4;j++)
											a[i][j]=prev[i][j];
									score=prevscore;
									mvprintw(19,2,"                                     ");
									mvprintw(20,2,"USE THE ARROW KEYS TO MOVE THE TILES");
									mvprintw(21,2,"PRESS Q TO EXIT THE GAME (YOU'LL BE ABLE TO RESUME IT, IF YOU WANT)");
									mvprintw(22,2,"PRESS Z TO UNDO THE LAST MOVE (YOU CANNOT UNDO TWICE IN A ROW)");
									if(score>highscore)
										highscore=score;
									print_table(score,highscore);
									refresh();
								}
								else
								{
									stadiu=0;
									res=0;
								}
							}
					}
					FD_SET(KEYBOARD, &read_descriptors);
					timeout.tv_sec = S_TO_WAIT;
					timeout.tv_usec = MILIS_TO_WAIT;
					refresh();
				}
				while(stadiu==1);
				Continue2: ;
				draw_menu(pozitie,res);
			}
			if(pozitie==3)
			{
				fclose(f);
				continuare=0;
				f=fopen("savegame","w");
				fprintf(f,"%d\n",res);
				if(res==1)
				{
					int i,j;
					for(i=1;i<=4;i++)
						{
							for(j=1;j<=4;j++)
								fprintf(f,"%d ",a[i][j]);
							fprintf(f,"\n");
						}
					for(i=1;i<=4;i++)
					{
						for(j=1;j<=4;j++)
							fprintf(f,"%d ",prev[i][j]);
						fprintf(f,"\n");
					}
					fprintf(f,"%d %d\n",score,prevscore);
				}
				fprintf(f,"%d",highscore);
				fclose(f);
			}
		}
		refresh();
	}
	endwin();
	return 0;      
} 
