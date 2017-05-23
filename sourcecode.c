
/*Zipf's Law*/
#include<conio.h>
#include<dir.h>
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<graphics.h>
typedef struct word
	{
		int count;
		char word[45];
		struct word *next;
	}word;

void welcome()
	{

		int i;
		settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
		setbkcolor(DARKGRAY);

		for(i=0;i<450;i++)
			{

				outtextxy(250,250,"LOADING");
				rectangle(50,275,600,300);
				bar(50,275,150+i,300);
				delay(5);
				cleardevice();

			}

	     closegraph();

   }

void read_file(word **left, word **right)
	{


		 FILE *p;
		 word *q,*r,*s,*t=*left,*u=*left;
		 int flag=0;
		 char ch,wordread[45],filename[30] ,path[256],command[256];
		 int i;
		 if(u!=NULL)
			{
				while(t!=*right)
					{
						free(t);
						t=t->next;
					}
					*left=*right=NULL;
			}



				printf("\n\t\t\tEnter file name:");
				gets(filename);
				strcpy(path,searchpath(filename));
				p=fopen(path,"r+");
				if(p==NULL)
				printf("\n\t\t\tfile does not exist.\n");
				else
					{       ch=fgetc(p);
						if(ch==EOF)
						printf("\n\t\t\tFile is empty.\n");
						else

						{
							while(ch!=EOF)
							{

								 if((ch>=97 && ch<=122)||(ch>=65 && ch<=90))
									{





											i=0;
											strcpy(wordread,"");
											while(isalpha(ch)&&ch!=' ' &&( ch!='.'||ispunct(ch)==0)&&ch!=EOF)
												{
												  wordread[i]=ch;
												  i++;
												  ch=fgetc(p);
												}
											 wordread[i]='\0';
											 u=*left;
											 flag=0;
											 while(u!=NULL)
												{
													if(strcmpi(u->word,wordread)==0)
														{
															(u->count)++;
															flag++;

														}
													u=u->next;
												}
											 if(flag==0)
												{
													q=(word *)malloc(sizeof(word));

													if(q!=NULL)
														{
															q->next=NULL;
															q->count=1;
															strcpy(q->word,wordread);
														       if(*right==NULL)
														       *right=*left=q;
														       else
														       {
														       (*right)->next=q;
														       *right=q;
														       }
														 }


												 }



									}

							  ch=fgetc(p);
							}
							printf("\t\t\tPress any key to continue.");
							getch();
						}
						u=*left;
						while(u!=NULL)
							{    t=u->next;
							     while(t!=NULL)
								{
									if(t->count>u->count)
										{
											t->count=t->count+u->count;
											u->count=t->count-u->count;
											t->count=t->count-u->count;
											strcpy(wordread,t->word);
											strcpy(t->word,u->word);
											strcpy(u->word,wordread);
										}
									t=t->next;
								}
							     u=u->next;
							}






				fcloseall();
				q=*left;
				while(q!=NULL)
					{
						r=q->next;
						while(r!=NULL)

							{
								if(strcmp(q->word,r->word)==0)
									{
										(q->count)=(q->count)+1;
										(r->count)++;
										s=r->next;
										r->next=s->next;
										free(s);
									}
								 r=r->next;
							}
						q=q->next;
					}
					}

		 }

void print_table(word *left)

	{
		FILE *p;
		if(left==NULL)
			{
				clrscr();
				gotoxy(20,10);

				printf("\n\t\t\tNo content to show.Please try again.\n");
			}
		else
			{
				int i,j=1;
				char file[50],command[50];
				strcpy(file,"zipffreq.txt");
				p=fopen(file,"w+");


						clrscr();
						gotoxy(30,4);
						puts("FREQUENCY TABLE");




								for(i=1;left!=NULL;i++)
							       {
									if(i==21)
										{
											i=1;
											getch();
											clrscr();
											gotoxy(30,4);
											puts("FREQUENCY TABLE");
										}
									gotoxy(19,5);
									printf("Rank\tWord\t\t\t    Frequency");
									gotoxy(19,5+i);
									printf("%d\t%s",j,left->word);
									fprintf(p,"%d %s %d\n",j,left->word,left->count);
									j++;
									gotoxy(38,5+i);
									printf("|");
									gotoxy(40,5+i);
									printf("\t\t\t%d",left->count);



																		left=left->next;
								}



				fcloseall();



			}
		getch();

	 }

  void main()
	{
		int  gd = DETECT, gm;
		char c;
		FILE *fp;
		word *left=NULL,*right=NULL;
		char ch,filename[30];
		initgraph(&gd,&gm,"..\\BGI");
		welcome();
		lab:
		clrscr();
		gotoxy(35,5);
		printf("MENU\n\n\n\t\t\t1.Read from a file\n\t\t\t2.Create a file\n\t\t\t3.Print the frequency table\n\t\t\t4.Exit\n\n\t\t\tEnter your choice:");
		ch=getch();
		printf("%c",ch);
		getch();
		switch(ch)
			{
				case '1':
					read_file(&left,&right);
					break;
				case '2':
					clrscr();
					gotoxy(20,10);
					printf("Enter file name:");
					gets(filename);
					fp=fopen(filename,"w+");
					clrscr();
					gotoxy(20,5);
					printf("Enter the content.(Press '#' to save)\n");
					while((c=getchar())!='#')
					fprintf(fp,"%c",c);
					fcloseall();
					break;
				case '3':
					print_table(left);
					break;
				case '4':

					cleardevice();
					{
					word *p=left,*q;
					 while(p!=NULL)
					{
						q=p;
						free(q);
						p=p->next;
					}
					}

					delay(1000);
					 exit();
				default:
					printf("\n\t\t\tWrong choice.\n\t\t\tPlease choose a corret option.\n");
			}
			getch();
		goto lab;
	  }

