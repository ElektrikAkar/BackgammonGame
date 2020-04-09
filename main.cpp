#include <cstdlib> //necessary for system function
#include <conio.h> //necessary for getch(); 
#include <stdio.h> //necessary for fundemental C codes (scanf printf etc.) 
#include <time.h>  // necessary for TIME function ---> random (srand TIME NULL) to roll different dices

// Author: VK
// Date:   2012.12.02

void rolldice(int zarlar[]); //function that rolls dices
void boardd(char pullar[24][15]); //function that shows screen
void pullaridiz(char pullar[24][15]); //it sets pieces
void informasiyon(int zarlar[], int wbr, int bbr, int wcl, int bcl, char turn); //informations about situation of the game at the end of the screen
void oyna(char pullar[24][15], int n1, int hamle, char sira); // function that moves the pieces 
int hamlekontrol(char pullar[24][15], int n1, int hamle, char sira, int bbr, int wbr, int wcl, int bcl); //function that control the moves
void siradegis(char *sira); // function that changes the order of game to one player to the other 
int zarkontrol(int zarlar[], int hamle); //function that controls whether the numbers of dices and movements of pieces are same or not
void pulkir(char pullar[24][15], int n1, int hamle, char sira, int* wbr, int* bbr); //function that is necessary to play for breaking pieces
int kirikkont(char sira, int wbr, int bbr); //function that controls whether there is a broken piece or not. if so, it doesn't allow to play as a normal 
void ozpulkir(char pullar[24][15], int hamle, char sira, int* wbr, int* bbr); //function that allows to broke pieces when we have a broken pieces that is outside
void ozoyna(char pullar[24][15], int hamle, char sira, int* wbr, int* bbr); // function that allows to play when we have a broken piece
int tkontrol(char pullar[24][15], char sira); //function that controls whether we collect the pieces or not
int tkontrol2(char pullar[24][15], char sira, int n1, int hamle); //if we can collect the pieces, it allows to collect only possible pieces
void topla(char pullar[24][15], int n1, int *wcl, int *bcl, char sira); //function that collects pieces
void Vk(char pullar[24][15], char sira, int bbr, int wbr, int wcl, int bcl, int zarlar[], int* kats, int* pbbr, int* pwbr, int* pwcl, int* pbcl); //Artifical intellegent
int hamlebul(int olasi[24][2], char pullar[24][15], int zarlar[], int wbr, char sira); // function that finds possible movements 
int hamleyapabilirmi(char pullar[24][15], int zarlar[], int bbr, char sira); /*if a player can not move or he do not have a possible movements, this
function change the order of game*/
int fkontrol1(char pullar[24][15], int n1, char *fsira); // Controls move for HOMEWORK
int TestMali(char pullar[24][15], int n1, int hamle, int *bbr, int *wbr, int *wcl, int *bcl); //Homework function

int main(int argc, char *argv[])
{
    int zarlar[2]; //dice
    int n1,hamle; //position and move
    int wbr=0; //broken whites
    int bbr=0; //broken blacks
    int wcl=0; //collected whites
    int bcl=0; //collected blacks
    char sira=' '; //turn
    int kats=0; //to play with couple dices (cift zar) 
    char pullar[24][15]; // list of pieces
    int style;
    int uuu =1;
    pullaridiz(pullar);
    rolldice(zarlar);
    if(zarlar[0]>=zarlar[1]) //a player that has a big number of dieces can start first
    {
        sira = 'B';
    }else
    {
        sira = 'W';
    }
    printf("---------------------- WELCOME TO THE BACKGAMMON GAME ----------------------\n\n");
    printf("! Please read the instructions TO PLAY CORRECTLY !\n\n\n");
    printf("If it is your turn(i.e., Blacks), enter your numbers in form of a,b to play:\n");
    printf("a= location of the piece you will play and b= number of change in location\n\n");
    printf("If it is CPU's turn (e.g., Whites), just click any button to see and pass its move\n\n");
    printf("And in your turn, please DO NOT ENTER A STRING\n\n\n\n");
    printf("If you have a broken piece and you want to go in, you should play like: \na=0 and b is the dice you want to start with (e.g. 0,4) \n\n");
    printf("If you do not have a possible move:\nEnter a random number and a NEGATIVE NUMBER (e.g. 2,-4)\n\n");
	printf("VK, 2012.12.02\n\n");
    printf("------------------------- CLICK ANY BUTTON TO START -------------------------\n\n");
    getch();
    
    system("CLS"); //to clean the screen

    printf("Please enter 1 for normal game,\n2 for homework type game,\nother number to exit game : ");
    scanf("%d",&style);
    if((style==1)||(style==2))
    {}
    else    
    { printf("You inputted other value, game will exit\n"); getch(); exit(EXIT_FAILURE);}
    system("CLS"); //to clean the screen
    boardd(pullar);
    informasiyon(zarlar, wbr, bbr, wcl, bcl, sira);
    system("color 27"); //to change the background color and the text color (2 = background, 7 = text color)
    while(!(wcl==15 || bcl==15)) // loop that continues until the end of the game
    {
        if(style==1)
        {
        
        if(kats==7)
        {
            kats=0;
        }else
        {
            if(((zarlar[0]!=0)||(zarlar[1]!=0))&&(zarlar[0]==zarlar[1]))
            {
                kats=zarlar[0];
            }
        }
         
        if((zarlar[0]!=0)||(zarlar[1]!=0))
        {
            if(sira=='B')
            {
            printf("Move : ");
            scanf("%d,%d",&n1,&hamle); //it asks how many location you want to move
            }else
            {
                Vk(pullar, sira, bbr, wbr, wcl, bcl, zarlar, &kats, &bbr, &wbr, &wcl, &bcl);
            }
        }
    
        
        if((zarlar[0]==0)&&(zarlar[1]==0))
        {
            if(kats==0)
            {
                siradegis(&sira);
                rolldice(zarlar);
                boardd(pullar);
                informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
            }else if(kats!=0) 
            {
                zarlar[0]=kats;
                zarlar[1]=kats;
                kats=7;
                boardd(pullar);
                informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
            }
        }else
        {if(sira=='B'){
            int yap=hamleyapabilirmi(pullar, zarlar, bbr, sira);
            if(hamle<0)
            {
                if(yap==0)
                {
                zarlar[0]=0; zarlar[1]=0; kats=0;
                }else
                {
                    boardd(pullar);
                    informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                    printf("Invalid move! Because you can make a move.\n");
                }
            } //if move is negative, order will change
            else if((hamlekontrol(pullar, (n1-1), hamle, sira, bbr, wbr, wcl, bcl)==0)||(zarkontrol(zarlar, hamle)==0))
            {
                if(sira=='B')
                {
                boardd(pullar);
                informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                printf("Invalid move!\n");
                }
            }else
            {
                int x2 = hamlekontrol(pullar, (n1-1), hamle, sira, bbr, wbr, wcl, bcl);
                if(x2>9)
                {
                    if(x2==20)
                    {
                        if(hamle==zarlar[0])
                        {
                            ozpulkir(pullar, hamle, sira, &wbr, &bbr);
                            zarlar[0]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }else if(hamle==zarlar[1])
                        {
                            ozpulkir(pullar, hamle, sira, &wbr, &bbr);
                            zarlar[1]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }
                    }else if(x2==10)
                    {
                        if(hamle==zarlar[0])
                        {
                            ozoyna(pullar, hamle, sira, &wbr, &bbr);
                            zarlar[0]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }else if(hamle==zarlar[1])
                        {
                            ozoyna(pullar, hamle, sira, &wbr, &bbr);
                            zarlar[1]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }
                    }
                    
                    
                }else
                {
                    if(x2==2)
                    {
                        if(hamle==zarlar[0])
                        {
                            pulkir(pullar,(n1-1),hamle,sira, &wbr, &bbr);
                            zarlar[0]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }else if(hamle==zarlar[1])
                        {
                            pulkir(pullar,(n1-1),hamle,sira, &wbr, &bbr);
                            zarlar[1]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }
                                      
                    }else if(x2==4)
                    {
                        if(hamle==zarlar[0])
                        {
                            topla(pullar, (n1-1), &wcl, &bcl, sira);
                            zarlar[0]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }else if(hamle==zarlar[1])
                        {   
                            topla(pullar, (n1-1), &wcl, &bcl, sira);
                            zarlar[1]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }
                    
                    }
                    else
                    {
                        if(hamle==zarlar[0])
                        {
                            oyna(pullar,(n1-1),hamle,sira);
                            zarlar[0]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }else if(hamle==zarlar[1])
                        {
                            oyna(pullar,(n1-1),hamle,sira);
                            zarlar[1]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }
                    }
                }
                
                
            }}
        }   
    }else
    {
        zarlar[0] = 0;
        zarlar[1] = 0;
        sira ='?';
        system("CLS"); //to clean the screen
        boardd(pullar);
        informasiyon(zarlar, wbr, bbr, wcl, bcl, sira);
        if(uuu==0)
        {printf("Invalid Move!\n");}
        printf("Move : ");
        scanf("%d,%d",&n1,&hamle); //it asks how many location you want to move
        uuu = TestMali(pullar, (n1-1), hamle, &bbr, &wbr, &wcl, &bcl);
        if(uuu==10){ printf("Oyundan cikmak istediniz, cikmak icin bir tusa basin."); getch(); exit(EXIT_FAILURE);}
    }          
    }
    
    if(wcl==15)
    {
        printf("Whites WON\n");
    }else if(bcl==15)
    {
        printf("Blacks WON\n");
    }else
    {
        printf("HATA\n");
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}

int TestMali(char pullar[24][15], int n1, int hamle, int *bbr, int *wbr, int *wcl, int *bcl)
{
    int zarlar[2];
    zarlar[0] =0;
    zarlar[1] =0;
    char fsira ='?';
    int fk1 = fkontrol1(pullar, n1, &fsira);
    if((hamle==100)&&(n1==99))
    {
        return 10;
    }else if(fk1==0)
    {
        return 0;
    }else
    {
        
        int x2 = hamlekontrol(pullar, n1, hamle, fsira, *bbr, *wbr, *wcl, *bcl);
        if(x2==0)
        {
            return 0;
        }
        else
        {
        if(x2>9)
                {
                    if(x2==20)
                    {
                            ozpulkir(pullar, hamle, fsira, wbr, bbr);
                            boardd(pullar);
                            informasiyon(zarlar, *wbr, *bbr, *wcl, *bcl, fsira);
                    }else if(x2==10)
                    {
                            ozoyna(pullar, hamle, fsira, wbr, bbr);
                            boardd(pullar);
                            informasiyon(zarlar, *wbr, *bbr, *wcl, *bcl, fsira);
                    }
                    
                    
                }else
                {
                    if(x2==2)
                    {
                            pulkir(pullar, n1,hamle, fsira, wbr, bbr);
                            boardd(pullar);
                            informasiyon(zarlar, *wbr, *bbr, *wcl, *bcl, fsira);

                                      
                    }else if(x2==4)
                    {
                            topla(pullar, n1, wcl, bcl, fsira);
                            boardd(pullar);
                            informasiyon(zarlar, *wbr, *bbr, *wcl, *bcl, fsira);
                    }
                    else
                    {
                            oyna(pullar, n1,hamle, fsira);
                            boardd(pullar);
                            informasiyon(zarlar, *wbr, *bbr, *wcl, *bcl, fsira);
                    }
                }
        }
    }
}

int fkontrol1(char pullar[24][15], int n1, char *fsira)
{
        if(n1==-1)
        {
            return 3;
        }
        else if(pullar[n1][0]==' ')
        {
            return 0;
        }else if(pullar[n1][0]=='B')
        {
            *fsira ='B';
            return 1;
        }else if(pullar[n1][0]=='W')
        {
            *fsira = 'W';
            return 1;
        }
}

int hamleyapabilirmi(char pullar[24][15], int zarlar[], int bbr, char sira)
{
    int uhu=1;
    if(bbr>0)
    {
        int a=1;
        if((pullar[zarlar[0]-1][1]!='W')&&(zarlar[0]!=0))
        { a++;}
        if((pullar[zarlar[1]-1][1]!='W')&&(zarlar[1]!=0))
        { a++;}
        if(a==1){uhu = 0;}
    }else
    {
        if(tkontrol(pullar, sira)==1)
        {
            int a=1;
            int zar1,zar2;
            zar1 = zarlar[0];
            zar2 = zarlar[1];
            bool u1,u2; 
            if(zar1==0)
            {
                u1 = false;
            }else
            {
                u1 = (pullar[24-zar1][0]=='B');
            }
            if(zar2==0)
            {
                u2 = false;
            }else
            {
                u2 = (pullar[24-zar2][0]=='B');
            }
            if(u1||u2)
            {
                if(u1)
                { a++;}
                if(u2)
                { a++; }
            }
            else
            {
                int red=1;
                if(zar1!=0)
                {
                    for(int i=18; i<(24-zar1); i++)
                    {
                        if(pullar[i][0]=='B')
                        {red=0;}
                    }
                    if(red==1)
                    {  a++; }
                }
                if(zar2!=0)
                {
                    for(int i=18; i<(24-zar2); i++)
                    {
                        if(pullar[i][0]=='B')
                        {red=0;}
                    }
                    if(red==1)
                    {  a++; }
                }
            }
            
        }
        else
        {
            int a=1;
            if(zarlar[0]!=0)
            {
                for(int x1=(23-zarlar[0]); x1>0; x1--)
                {
                    if(((pullar[x1+(zarlar[0])][1])!='W') &&(pullar[x1][0]=='B'))
                    {
                        a++;
                    }
                }
            }
        
            if(zarlar[1]!=0)
            {
                for(int x2=(23-zarlar[1]); x2>0; x2--)
                {
                    if((pullar[x2+(zarlar[1])][1]!='W') &&(pullar[x2][0]=='B'))
                    {
                        a++;
                    }
                }
            }
            if(a==1){uhu =  0;}
        }
    }
    return uhu;
}

void Vk(char pullar[24][15], char sira, int bbr, int wbr, int wcl, int bcl, int zarlar[], int* kats, int* pbbr, int* pwbr, int* pwcl, int* pbcl)
{
    int cpu=0;
    int n1,hamle;
    int olasi[24][2];
    olasi[0][0]=0;
    olasi[0][1]=-1;
    getch();
    int mali = hamlebul(olasi, pullar, zarlar, wbr, sira); 
    n1 = olasi[mali][0];
    hamle = olasi[mali][1];
    
    while(cpu==0)
    {if(hamle<0){zarlar[0]=0; zarlar[1]=0; (*kats)=0; cpu=1;//if "hamle" is negative, order will change
        }else if((hamlekontrol(pullar, (n1-1), hamle, sira, bbr, wbr, wcl, bcl)==0)||(zarkontrol(zarlar, hamle)==0))
            {
                boardd(pullar);
                informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                printf("Invalid move!\n");
            }else
            {
                int x2 = hamlekontrol(pullar, (n1-1), hamle, sira, bbr, wbr, wcl, bcl);
                if(x2>9)
                {
                    if(x2==20)
                    {
                        if(hamle==zarlar[0])
                        {
                            cpu=1;
                            ozpulkir(pullar, hamle, sira, &wbr, &bbr);
                            zarlar[0]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }else if(hamle==zarlar[1])
                        {
                            cpu=1;
                            ozpulkir(pullar, hamle, sira, &wbr, &bbr);
                            zarlar[1]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }
                    }else if(x2==10)
                    {
                        if(hamle==zarlar[0])
                        {
                            cpu=1;
                            ozoyna(pullar, hamle, sira, &wbr, &bbr);
                            zarlar[0]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }else if(hamle==zarlar[1])
                        {
                            cpu=1;
                            ozoyna(pullar, hamle, sira, &wbr, &bbr);
                            zarlar[1]=0;
                            boardd(pullar);
                            informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                        }
                    }
                    
                    
                }else
                {
                if(x2==2)
                {
                    if(hamle==zarlar[0])
                    {
                        cpu=1;
                        pulkir(pullar,(n1-1),hamle,sira, &wbr, &bbr);
                        zarlar[0]=0;
                        boardd(pullar);
                        informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                    }else if(hamle==zarlar[1])
                    {
                        cpu=1;
                        pulkir(pullar,(n1-1),hamle,sira, &wbr, &bbr);
                        zarlar[1]=0;
                        boardd(pullar);
                        informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                    }
                                      
                }else if(x2==4)
                {
                    if(hamle==zarlar[0])
                    {
                        cpu=1;
                        topla(pullar, (n1-1), &wcl, &bcl, sira);
                        zarlar[0]=0;
                        boardd(pullar);
                        informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                    }else if(hamle==zarlar[1])
                    {
                        cpu=1;
                        topla(pullar, (n1-1), &wcl, &bcl, sira);
                        zarlar[1]=0;
                        boardd(pullar);
                        informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                    }
                    
                }
                else
                {
                    if(hamle==zarlar[0])
                    {
                        cpu=1;
                        oyna(pullar,(n1-1),hamle,sira);
                        zarlar[0]=0;
                        boardd(pullar);
                        informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                    }else if(hamle==zarlar[1])
                    {
                        cpu=1;
                        oyna(pullar,(n1-1),hamle,sira);
                        zarlar[1]=0;
                        boardd(pullar);
                        informasiyon(zarlar, wbr, bbr, wcl, bcl,sira);
                    }
                }
                }
                
                
            }
           
    }
    *pwbr = wbr;
    *pbbr = bbr;
    *pwcl = wcl;
    *pbcl = bcl;
}

int hamlebul(int olasi[24][2], char pullar[24][15], int zarlar[], int wbr, char sira)
{
    int uhu;
    
    if(wbr>0)
    {
        int a=1;
        olasi[1][0] = 0; 
        if((pullar[24-(zarlar[0])][1]!='B')&&(zarlar[0]!=0))
        {
            olasi[a][0] = 0;
            olasi[a][1]=zarlar[0];
            a++;
        }
        
        if((pullar[24-(zarlar[1])][1]!='B')&&(zarlar[1]!=0))
        {
            olasi[a][0] = 0;
            olasi[a][1]=zarlar[1];
            a++;
        }
        if(a==1){uhu = 0;}
        else
        {
        srand ( (unsigned)time( NULL ) ); // for different dices 
        uhu = (rand()%(a-1))+1;
        }
    }else
    {
        if(tkontrol(pullar, sira)==1)
        {
            int a=1;
            int zar1,zar2;
            zar1 = zarlar[0];
            zar2 = zarlar[1];
            bool u1,u2; 
            if(zar1==0)
            {
                u1 = false;
            }else
            {
                u1 = (pullar[zar1-1][0]=='W');
            }
            if(zar2==0)
            {
                u2 = false;
            }else
            {
                u2 = (pullar[zar2-1][0]=='W');
            }
            if(u1||u2)
            {
                if(u1)
                {
                    olasi[a][0] = zar1;
                    olasi[a][1] = zar1;
                    a++;
                }
                if(u2)
                {
                    olasi[a][0] = zar2;
                    olasi[a][1] = zar2;
                    a++;
                }
                if(a==1){uhu = 0;}
                else
                {
                    srand ( (unsigned)time( NULL ) );
                    uhu = (rand()%(a-1))+1;
                }
            }
            else
            {
                int red=1;
                if(zar1!=0)
                {
                    for(int i=5; i>(zar1-1); i--)
                    {
                        if(pullar[i][0]=='W')
                        {red=0;}
                    }
                    if(red==1)
                    {
                        olasi[a][0] = zar1;
                        olasi[a][1] = zar1;
                        a++;
                    }
                }
                if(zar2!=0)
                {
                    for(int i=5; i>(zar2-1); i--)
                    {
                        if(pullar[i][0]=='W')
                        {red=0;}
                    }
                    if(red==1)
                    {
                        olasi[a][0] = zar2;
                        olasi[a][1] = zar2;
                        a++;
                    }
                }
                if(a==1){uhu = 0;}
                else
                {
                    srand ( (unsigned)time( NULL ) );
                    uhu = (rand()%(a-1))+1;
                }
            }
            
        }
        else
        {
            int a=1;
            if(zarlar[0]!=0)
            {
                for(int x1=zarlar[0]; x1<24; x1++)
                {
                    if(((pullar[x1-(zarlar[0])][1])!='B') &&(pullar[x1][0]=='W'))
                    {
                        olasi[a][0]= x1+1;
                        olasi[a][1]= zarlar[0];
                        a++;
                    }
                }
            }
        
            if(zarlar[1]!=0)
            {
                for(int x2=zarlar[1]; x2<24; x2++)
                {
                    if((pullar[x2-(zarlar[1])][1]!='B') &&(pullar[x2][0]=='W'))
                    {
                        olasi[a][0]= x2+1;
                        olasi[a][1]= zarlar[1];
                        a++;
                    }
                }
            }
            if(a==1){uhu =  0;}
            else
            {
            srand ( (unsigned)time( NULL ) );
            uhu = (rand()%(a-1))+1;
            }
        }
    }
    return uhu;
}
void topla(char pullar[24][15], int n1, int *wcl, int *bcl, char sira)
{
    int kont1=0;
    int kont2=14;
    while(kont1==0)
    {
        if(pullar[n1][kont2]==sira)
        {
            pullar[n1][kont2]=' ';
            kont1=1;
            if(sira=='B')
            {
                (*bcl)++;
                  
            }else if(sira=='W')
            {
                (*wcl)++;
            }
        }
        kont2--;
    }
}

int tkontrol2(char pullar[24][15], char sira, int n1, int hamle)
{
    int ret=1;
    if(sira =='W')
    {
        if((n1-hamle)==-1)
        {
            ret=1;
        }else
        {
            for(int i=5; i>(hamle-2); i--)
            {
                if(pullar[i][0]==sira)
                {ret=0;}
            }
            for(int i=5; i>n1; i--)
            {
                if(pullar[i][0]==sira)
                {ret=0;}
            }
        }
    }else if(sira =='B')
    {
        if((n1+hamle)==24)
        {
            ret=1;
        }else
        {
            for(int i=18; i<(25-hamle); i++)
            {
                if(pullar[i][0]==sira)
                {ret=0;}
            }
            for(int i=18; i<n1; i++)
            {
                if(pullar[i][0]==sira)
                {ret=0;}
            }
        }
    }
    return ret;
}

int tkontrol(char pullar[24][15], char sira)
{
    int ret=0;
    int t=0;
    if(sira=='W')
    {
        for(int i=6; i<24; i++)
        {
            if(pullar[i][0]=='W')
            {t++;}
    
        }       
    }else if(sira=='B')
    {
        
        for(int i=0; i<18; i++)
        {
                if(pullar[i][0]=='B')
                {t++;}
        }
    }
    if(t==0)
    {//if there are 15 pieces, this function allows to collect them
        ret=1;
    }
    return ret;
}


void ozoyna(char pullar[24][15], int hamle, char sira, int* wbr, int* bbr)
{
        int kont3=0;
        int kont4=0;
        while(kont3==0)
        {
            if(sira=='B')
            {
                if(pullar[hamle-1][kont4]==' ')
                {
                    pullar[hamle-1][kont4]='B';
                    (*bbr)--;
                    kont3=1;
                }
                
            }else if(sira=='W')
            {
                if(pullar[24-hamle][kont4]==' ')
                {
                    pullar[24-hamle][kont4]='W';
                    (*wbr)--;
                    kont3=1;
                }
                
            }kont4++;
        }
}

int kirikkont(char sira, int wbr, int bbr)
{
    int retur;
    if(sira=='B')
    {
        if(bbr==0)
        {
            retur=1;
        }else
        {
            retur=0;
        }
    }else
    {
        if(wbr==0)
        {
            retur=1;
        }else
        {
            retur=0;
        }
    }
    return retur;
} 

void ozpulkir(char pullar[24][15], int hamle, char sira, int* wbr, int* bbr)
{
    if(sira=='B')
    {      
        pullar[hamle-1][0]='B';
        (*bbr)--;
        (*wbr)++;
    }else if(sira=='W')
    {
        pullar[24-hamle][0]='W';
        (*wbr)--;
        (*bbr)++;
    }
    
}
void pulkir(char pullar[24][15], int n1, int hamle, char sira, int* wbr, int* bbr)
{
    
    int kont1=0;
    int kont2=14;
    while(kont1==0)
    {
        if(pullar[n1][kont2]==sira)
        {
            pullar[n1][kont2]=' ';
            kont1=1;
            if(sira=='B')
            {
                
                pullar[n1+hamle][0]='B';
                (*wbr)++;
                  
            }else if(sira=='W')
            {
                pullar[n1-hamle][0]='W';
                (*bbr)++;

            }
        
        }
        kont2--;
    }
}


int zarkontrol(int zarlar[], int hamle)
{
    int retu;
    if(!((hamle==zarlar[0])||(hamle==zarlar[1])))
    {
        retu=0;
    }else
    {
        retu=1;
    }
    return retu;
}


void siradegis(char *sira)
{
    if((*sira)=='B')
    {(*sira)='W';}
    else if((*sira)=='W')
    {(*sira)='B';}
}
int hamlekontrol(char pullar[24][15], int n1, int hamle, char sira, int bbr, int wbr, int wcl, int bcl)
{
    int ret;
    int x = kirikkont(sira, wbr, bbr);
    
    if(x==0)
    {
        if(n1==-1)
        {
            if(sira=='W')
            {
                if(pullar[24-hamle][1]=='B')
                {
                    ret=0; //there is more than one another piecees, movement is invalid
                }else if((pullar[24-hamle][0]=='B')&&(pullar[24-hamle][1]==' '))
                {
                    ret=20; //they can be broken
                }else
                {
                    ret=10;
                }      
            }else if(sira=='B')
            {
                if(pullar[hamle-1][1]=='W')
                {
                    ret=0; //there is more than one another piecees, movement is invalid
                }else if((pullar[hamle-1][0]=='W')&&(pullar[hamle-1][1]==' '))
                {
                    ret=20; // they can be broken
                }else
                {
                    ret=10;
                }      
            }
            
        }else
        {
            ret=0;
        }
        
    }else
    {
            if(!(pullar[n1][0]==sira))
        {
            ret=0; 
        }else
        {
            if(sira=='W')
            {
                if((n1-hamle)<0)
                {
                    if(tkontrol(pullar, sira)==1)
                    {
                        if(tkontrol2(pullar, sira, n1, hamle)==1)
                        {
                            ret=4;
                        }else
                        {
                           
                            ret=0;
                        }
                    }
                     else
                    {ret=0;}
                }
                else if((pullar[n1-hamle][0]=='B')&&(pullar[n1-hamle][1]=='B'))
                {
                    
                    ret=0; //there is more than one another piecees, movement is invalid
                }else if((pullar[n1-hamle][0]=='B')&&(pullar[n1-hamle][1]==' '))
                {
                    ret=2; //it can be broken
                }else
                {
                    ret=1;
                }      
            }
            if(sira=='B')
            {
                if((n1+hamle)>23)
                {
                    if(tkontrol(pullar, sira)==1)
                    {
                        if(tkontrol2(pullar, sira, n1, hamle)==1)
                        {
                            ret=4;
                        }else
                        {
                            
                            ret=0;
                        }
                    }
                    else
                    {ret=0; }
                }
                else if((pullar[n1+hamle][0]=='W')&&(pullar[n1+hamle][1]=='W'))
                {
                    ret=0; //there is more than one another piecees, movement is invalid
                }else if((pullar[n1+hamle][0]=='W')&&(pullar[n1+hamle][1]==' '))
                {
                    ret=2; // it can be broken
                }else
                {
                    ret=1;
                }      
            }
        }
    }
    
    return ret;   
}

void informasiyon(int zarlar[], int wbr, int bbr, int wcl, int bcl, char sira)
{
    
    printf("Broken Whites:    %d                Turn: %c\n",wbr,sira);
    printf("Broken Blacks:    %d                Dice Trown: %d  %d\n",bbr,zarlar[0],zarlar[1]);
    printf("Collected whites: %d\n",wcl);
    printf("Collected blacks: %d\n",bcl);    
}

void boardd(char pullar[24][15])//to draw the board
{
    system("CLS");
    printf("                                         White Home Base            \n\n");
    printf("      12  11  10   9   8   7          6   5   4   3   2   1       \n");
    printf("||||---|---|---|---|---|---|---||||---|---|---|---|---|---|---||||\n");
    for(int i=0; i<15; i++)
    {
        printf("||||   ");
        for(int j=11; j>=0; j--)
        {
            printf("%c   ",pullar[j][i]);
            if(j==6)
            {
                printf("||||   ");
            }else if(j==0)
            {
                printf("||||\n");
            }                        
        }             
    }
//------------------------------------   
    for(int i=14; i>=0; i--)
    {
        printf("||||   ");
        for(int j=12; j<24; j++)
        {
            printf("%c   ",pullar[j][i]);
            if(j==17)
            {
                printf("||||   ");
            }else if(j==23)
            {
                printf("||||\n");
            }                        
        }             
    }
    printf("||||---|---|---|---|---|---|---||||---|---|---|---|---|---|---||||\n");
    printf("       13  14  15  16  17  18         19  20  21  22  23  24       \n\n");
    printf("                                         Black Home Base          \n\n");
}

void rolldice(int zarlar[])
{
    srand ( (unsigned)time( NULL ) );
      zarlar[0] = rand() % 6 + 1;
      zarlar[1] = rand() % 6 + 1;            
       
}




void oyna(char pullar[24][15], int n1, int hamle, char sira)
{
    
    int kont1=0;
    int kont2=14;
    while(kont1==0)
    {
        if(pullar[n1][kont2]==sira)
        {
            pullar[n1][kont2]=' ';
            kont1=1;
        
        int kont3=0;
        int kont4=0;
        while(kont3==0)
        {
            if(sira=='B')
            {
                if(pullar[n1+hamle][kont4]==' ')
                {
                    pullar[n1+hamle][kont4]='B';
                    kont3=1;
                }
                
            }else if(sira=='W')
            {
                if(pullar[n1-hamle][kont4]==' ')
                {
                    pullar[n1-hamle][kont4]='W';
                    kont3=1;
                }
                
            }kont4++;
        }
        }
        kont2--;
    }
    
}

void pullaridiz(char pullar[24][15])
{
    for(int i=0; i<24; i++)
    {
        for(int j=0; j<15; j++)
        {
            pullar[i][j]=' ';
        }
    }
    for(int i=0; i<2; i++)
    {pullar[0][i] = 'B';}
    
    for(int i=0; i<5; i++)
    {pullar[11][i] = 'B';}
    
    for(int i=0; i<3; i++)
    {pullar[16][i] = 'B';}
    
    for(int i=0; i<5; i++)
    {pullar[18][i] = 'B';}

    for(int i=0; i<5; i++)
    {pullar[5][i] = 'W';}
    
    for(int i=0; i<3; i++)
    {pullar[7][i] = 'W';}
    
    for(int i=0; i<5; i++)
    {pullar[12][i] = 'W';}
    
    for(int i=0; i<2; i++)
    {pullar[23][i] = 'W';}
    
}
