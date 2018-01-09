#include <curses.h>
#include <time.h>
#include <stdlib.h>
#define ENTER 10
#define FOREVER 1
int a[5][5],score;
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
	int copie[5][5];
	copiere_matrice(copie);
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
	int copie[5][5];
	copiere_matrice(copie);
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
	int copie[5][5];
	copiere_matrice(copie);
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
	int copie[5][5];
	copiere_matrice(copie);
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
void print_square(int x, int y, int val)
{
	mvprintw((x-1)*4,(y-1)*5,"+----+");
	mvprintw((x)*4,(y-1)*5,"+----+");
	mvprintw((x-1)*4+1,(y-1)*5,"|    |");
	mvprintw((x)*4-1,(y-1)*5,"|    |");
	mvprintw((x-1)*4+2,(y-1)*5,"|    ");
	if(val!=0)
		mvprintw((x-1)*4+2,(y-1)*5,"|%d",val);
	mvprintw((x-1)*4+2,(y)*5,"|");
}
void print_table()
{
	int i,j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
		{
			print_square(i,j,a[i][j]);
		}
}
int main() 
{       
	int actiune,continuare,pozitie=1,res=0;
	int nfds, sel;
	int KEYBOARD=1;
	fd_set read_descriptors;
	struct timeval timeout;
	nfds = 1;
	FD_ZERO(&read_descriptors);
	FD_SET(KEYBOARD, &read_descriptors);


	continuare=1;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	srand(time(NULL));
	mvprintw(1,1,"-->");
	mvprintw(1,4,"New Game");
	mvprintw(2,4,"Resume*");
	mvprintw(3,4,"Quit");
	while(continuare==1)
	{
		actiune=getch();
		if(actiune==KEY_UP)
		{
			if(pozitie>1)
			{
				pozitie--;
				mvprintw(pozitie,1,"-->");
				mvprintw(pozitie+1,1,"   ");
			}
		}
		if(actiune==KEY_DOWN)
		{
			if(pozitie<3)
			{
				pozitie++;
				mvprintw(pozitie,1,"-->");
				mvprintw(pozitie-1,1,"   ");
			}
		}
		if(actiune==ENTER)
		{
			if(pozitie==1)
			{
				int stadiu=1;
				score=0;
				clear();
				init_matrice();
				generare();
				generare();
				print_table();
				mvprintw(0,24,"SCORE:");
				mvprintw(1,24,"%d",score);
				mvprintw(28,2,"USE THE ARROW KEYS TO MOVE THE TILES");
				mvprintw(29,2,"PRESS Q TO EXIT THE GAME (YOU'LL BE ABLE TO RESUME IT, IF YOU WANT)");
				do
				{
					int directie,aux,auxm=0;
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
									if(directie==113 || directie==81)
									{
										res=1;
										break;
									}
									else
										aux=0;
					if(aux==1)
						generare();
					print_table();
					if(check2048()==1)
					{
						mvprintw(26,2,"CONGRATULATIONS, YOU WON!");
						refresh();
						stadiu=0;
						res=0;
						getch();
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
								mvprintw(26,2,"TOUGH LUCK, YOU ARE OUT OF MOVES!");
								refresh();
								stadiu=0;
								res=0;
								getch();
								getch();
							}
					}
					mvprintw(1,24,"%d",score);
					refresh();
				}
				while(stadiu==1);
				clear();
				mvprintw(pozitie,1,"-->");
				mvprintw(1,4,"New Game");
				if(res==1)
					mvprintw(2,4,"Resume");
				else
					mvprintw(2,4,"Resume*");
				mvprintw(3,4,"Quit");
			}
			if(pozitie==2 && res==1)
			{
				int stadiu=1;
				clear();
				print_table();
				mvprintw(0,24,"SCORE:");
				mvprintw(1,24,"%d",score);
				mvprintw(28,2,"USE THE ARROW KEYS TO MOVE THE TILES");
				mvprintw(29,2,"PRESS Q TO EXIT THE GAME (YOU'LL BE ABLE TO RESUME IT, IF YOU WANT)");
				do
				{
					int directie,aux,auxm=0;
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
									if(directie==113 || directie==81)
									{
										res=1;
										break;
									}
									else
										aux=0;
					if(aux==1)
						generare();
					print_table();
					if(check2048()==1)
					{
						mvprintw(26,2,"CONGRATULATIONS, YOU WON!");
						refresh();
						stadiu=0;
						res=0;
						getch();
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
								mvprintw(26,2,"TOUGH LUCK, YOU ARE OUT OF MOVES!");
								refresh();
								stadiu=0;
								res=0;
								getch();
								getch();
							}
					}
					mvprintw(1,24,"%d",score);
					refresh();
				}
				while(stadiu==1);
				clear();
				mvprintw(pozitie,1,"-->");
				mvprintw(1,4,"New Game");
				if(res==1)
					mvprintw(2,4,"Resume");
				else
					mvprintw(2,4,"Resume*");
				mvprintw(3,4,"Quit");
			}
			if(pozitie==3)
			{
				continuare=0;
			}
		}
		refresh();
	}
	endwin();      
} 