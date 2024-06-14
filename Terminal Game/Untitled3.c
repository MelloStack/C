#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <stdint.h>
#include <time.h>


char * scale = "$czB%8&WM#*oahkbd#qwplcoQLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i! I;:,\"^`'. ";
char * scale2 = "$ B%8&WM#*oahkbd#qw    QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
int numScale;
int p = 1;

int life = 25;
int enemylifeTotal = 20;
int playerlifeTotal = 20;
int damage = 55;

char backGround;

wchar_t name[] = L" ";

int changeWId = 1;
char face[20] = "🎅";

bool finish = false;

int nScreenWidth = 168;
int nScreenHeigth = 46;

int weaponId = 1;


float fPlayerA = 0.0f;
bool found = false;

int mMapHeigth = 32;
int mMapWidthh = 70; //70 71

float fFOV = 3.14159 / 4.0;
float fDepth = 16.0f;
int  cp = 0;
int dungeonLevel = 1;

int enemyCount = 0;
int enemyTotal = 3;

int totalKeys = 0;

float fPlayerX = 3.0f;//+ rand() % 10
float fPlayerY = 2.0f;//+ rand() % 10
     wchar_t inveCopy[] = 
   L"                    _________________________________________________                                           \n"                        
L"                                                                / \                                             |.\n"
L"                                                               |   |                                            |.\n"
L"                                                                \_ |        n                                   |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |        v                                   |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |        l                                   |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |        p                                   |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |        g                                   |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |                                            |.\n"
L"                                                                   |   _________________________________________|___\n"
L"                                                                   |  /                                             /\n."
L"                                                                   \_/_____________________________________________/.\n";

wchar_t inve[5000];

void textcolor (int color)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}

typedef struct
{
    size_t width;
    size_t height;
    unsigned char * data;
} image;

typedef struct {
  char name[100];
  int life;
  int totalLife;
  int damage;
  int level;
  bool isAlive;
  char face[100];
} Enemy;

Enemy enemy[1000*1000];

typedef struct {
  wchar_t name[200];
  int life;
  int lifeTotal;
  int level;
  int xp;
  int enemysKilled;
  int gold;
  int weaponEquipped;
  int damage;
} Player;

int xpToUp = 20;

Player player;


typedef struct {
  char* name;
  int qnt;      
  int price;
  int priceTotal;
  int id;
} Heal;

typedef struct {
  char name[100];      
  int damage; 
  int price;
  int id;
} Weapon;


typedef struct {
  char name[100];      
  int damage; 
  int price;
  int id;
} AllWeapons;

AllWeapons weaponsAll[1000*1000];//COLOCAR INFINITO
 
void weaponFunction(int c)
{
    char prefixos[200][200] = 
    {
      "Martelo",
      "Lanca",
      "Faca",
      "Esapda Curta",
      "Espada Longa",
      "Cutelo",
      "Katana",
      "Arco e Flecha",
      "Cajado de Madeira",
      "Foice"
    };
    
    char sufixos[200][200] = 
    {
         "Flamejante",
         "Gelida",
         "Obscura",
         "Explosiva",
         "Al Ghaib",
         "Artreides",
         "Freeman",
         "Enferrujada",
         "Mortal",
         "Destruidora",
         "Sanguinaria",
         "Traidora",
    };
         int rndPref = rand() % 10;
         int rndSuf = rand() % 12;
         
         char* pref = prefixos[rndPref];
         char* suf = sufixos[rndSuf];
         
         char fullName[200] = "";
         
         memset(fullName, 0, sizeof(fullName));
         strcat(fullName, pref);
         strcat(fullName, " ");
         strcat(fullName, suf);
    
   Weapon weapon[1];;
   
   int i;
   
   
   for(i = 1; i <= 1; i++)
   {
    strcpy(weapon[i].name, fullName);
    
    if(strstr(weapon[i].name, "Enferrujada") != NULL)
    {
     weapon[i].damage = rand() % 25;
     weapon[i].price = 5 * weapon[i].damage;    
    }
    else if(strstr(weapon[i].name, "Traidora") != NULL)
    {
     weapon[i].damage = -(rand() % 100);
     weapon[i].price = 0;                 
    }
    else
    {
         weapon[i].damage = rand() % 100;
         weapon[i].price = 5 * weapon[i].damage;   
    } 
    weapon[i].id = c;    
    
    strcpy(weaponsAll[c].name, weapon[1].name);
    weaponsAll[c].damage = weapon[1].damage;
    weaponsAll[c].price = weapon[1].price;
    weaponsAll[c].id = weapon[1].id;
   }

}

void healFunction(int c, int qnt)
{
    Heal heal;
    
    heal.price = 5;
    heal.name = "Cura";
    heal.id = c;
    heal.qnt = qnt;
    heal.priceTotal = heal.price * heal.qnt;    
        
}

void inicilizerPlayerFunction()
{
     
     printf("Qual sera seu nome aventureiro?");
     wscanf(L"%ls", player.name);
     //player.damage = all[weaponEquipped].damage ALL ESTA NO ITEMS, QUANDO PASSAR TUDO PARA 1 ARQUIVO FUNCIONARA
     
     player.level = 1;
     player.lifeTotal = 25 * 1;
     player.life = player.lifeTotal;
     player.gold = 0;
     player.enemysKilled = 0;
     player.weaponEquipped = 0;
     player.xp = 19;
}

void damagePlayerLife(int lifeUpdate)
{
      player.life -= lifeUpdate;
}

void addXP(int valueToXp)
{
    player.xp += valueToXp;
}

void healPlayerLife(int lifeUpdate)
{
     player.life += lifeUpdate;   
}

void levelUp(int levelUpdate)
{
     player.level += levelUpdate;    
}

void updateEnemysKilled(int killsUpdate)
{
     player.enemysKilled += killsUpdate;
}

void minusGoldChange(int goldChange)
{
     player.gold -= goldChange;     
}

void plusGoldChange(int goldChange)
{
     player.gold += goldChange;
}

void changeWeaponEquipped(int weaponChange)
{
     player.weaponEquipped = weaponChange;
     //player.damage = all[player.weaponEquipped].damage
}

void enemyFunction(int c)
{
     char faces[200][200] = 
     {
      "💀",
      "🧟",
      "👿",
      "👻",
      "👽",
      "🧛",
      "🐊",
      "🐺",
      "🕷",
      "🦂",
     };
     
     char prefixos[200][200] = 
     {
      "Esqueleto",
      "Zumbi",
      "Demonio",
      "Fantasma",
      "Alien",
      "Vampiro",
      "Jacare",
      "Lobo",
      "Aranha",
      "Escorpiao",     
     };
     
     char sufixos[200][200] = 
     {
      "Gigante",
      "Radiativo",
      "Triste",
      "Machucado",
      "Raivoso",
      "Pacifico"
     };
     
    while(enemyCount < enemyTotal)
    {
     
    int rndPref = rand() % 10;
    int rndSuf = rand() % 6;

  
         
    char* pref = prefixos[rndPref];
    char* suf = sufixos[rndSuf];
         
    char fullName[200];
    memset(fullName, 0, sizeof(fullName));
    strcat(fullName, pref);
    strcat(fullName, " ");
    strcat(fullName, suf);
         
    strcpy(enemy[enemyCount].name, fullName);
    enemy[enemyCount].level = c;
    strcpy(enemy[enemyCount].face, faces[rndPref]);
    
    if(strstr(enemy[enemyCount].name, "Pacifico") != NULL)
    {
     enemy[enemyCount].damage = 0 * enemy[enemyCount].level;  
     enemy[enemyCount].life = 10 * enemy[enemyCount].level;   
    }
    else if(strstr(enemy[enemyCount].name, "Machucado") != NULL)
    {
     enemy[enemyCount].damage = 5 * enemy[enemyCount].level;
     enemy[enemyCount].life = 5 * enemy[enemyCount].level;           
    }
    else
    {
         enemy[enemyCount].damage = 5 * enemy[enemyCount].level;
         enemy[enemyCount].life = 10 * enemy[enemyCount].level; 
    }
    
    enemy[enemyCount].totalLife = enemy[enemyCount].life;
    enemy[enemyCount].isAlive = true;
    //printf("Nome: %s\nDano:%d\nVida: %d\nLevel:%d\n%s\n", enemy[i].name, enemy[i].damage, enemy[i].life, enemy[i].level, enemy[i].face);
    enemyCount++;
  }
}
unsigned char luminanceFromRGB(unsigned char r, unsigned char g, unsigned char b)
{
  return (unsigned char) (0.2126 * r + 0.7152 * g + 0.0722 * b);
}

long loadImage(image ** img, char * location)
{
  FILE *f = fopen(location, "rb");

  if (f == NULL)
  {
    puts("Opening failed...");
    return 0;
  }

  unsigned char * result;
  fseek(f, 0, SEEK_END);
  long size = ftell(f);

  if(size > SIZE_MAX)
  {
    puts("Size is too big!");
	fclose(f);	
    return 0;
  }

  fseek(f, 0, SEEK_SET);
  result = (unsigned char *) malloc((size_t) size);

  if (size != fread(result, sizeof(unsigned char), (size_t) size, f))
  {
    free(result);
    puts("Reading failed...");
	fclose(f);
    return 0;
  }

  fclose (f);

  if (size < 54)
  {
    free(result);
    puts("Invalid file...");
    return 0;
  }

  if (result[0] != 'B' || result[1] != 'M')
  {
    free(result);
    puts("Incorrect file header...");
    return 0;
  }

  size_t specifiedSize = result[2] | result[3] << 8 | result[4] << 16 | result[5] << 24;

  if (specifiedSize != size)
  {
    free(result);
    puts("File sizes don't match...");
    return 0;
  }

  size_t pdOffset = result[10] | result[11] << 8 | result[12] << 16   | result[13] << 24;

  unsigned long width = result[18] | result[19] << 8 | result[20] << 16   | result[21] << 24;
  unsigned long height = result[22] | result[23] << 8 | result[24] << 16 | result[25] << 24;

  unsigned long bpp = result[28] | result[29] << 8;
  int noCompression = result[30] == 0 && result[31] == 0 && result[32] == 0   && result[33] == 0;

  if (bpp != 24 || !noCompression || width < 1 || height < 1 || width > 64000 || height > 64000)
  {
    free(result);
    puts("Unsupported BMP format, only 24 bits per pixel are supported...");
    return 0;
  }

  int bytesPerPixel = (int) (bpp / 8);

  size_t rowBytes = (width * bytesPerPixel + 3) / 4 * 4;

  size_t usedRowBytes = width * bytesPerPixel;
  size_t imageBytes = rowBytes * height;

  if (pdOffset > size || pdOffset + imageBytes > size)
  {
    free(result);
    puts("Invalid offset specified...");
    return 0;
  }

  *img = malloc(sizeof(image));
  (*img)->height = height;
  (*img)->width = width;

  size_t imgSize = width * height;

  (*img)->data = (unsigned char *) malloc(imgSize);


  unsigned char * ptr = (*img)->data;
  unsigned char * srcPtr = &result[pdOffset];
  size_t i = 0;
  for (i = 0; i < imgSize; ++i)
  {
    unsigned char r = *srcPtr;
    unsigned char g = *(srcPtr + 1);
    unsigned char b = *(srcPtr + 2);

    *ptr = luminanceFromRGB(r, g, b);
    ptr++;
    srcPtr += bytesPerPixel;

    if (i % width == 0)
    {
      srcPtr += rowBytes - usedRowBytes;
    }
  }

  free(result);

  return size;
}

void asciify(image * img, char * scale, int isCalling)
{
  size_t y;
  for (y = img->height - 1; y > 0; --y)
  {
    size_t x;
    for (x = 0; x < img->width; ++x)
    {
      unsigned char c = *(img->data + x + img->width * y);
      int rescaled = c * numScale / 256;
       if(isCalling == 2 || isCalling == 4 || isCalling == 5)
       {
          textcolor(WHITE);
       }
       else
       {
          textcolor(4);
       }
       if(scale[numScale - rescaled] == '^')
       {
         printf("█");
       }else
       {
        if(isCalling == 2)
        {
          if(scale[numScale - rescaled] == ' ')
          {
            putchar(scale[numScale - rescaled]);
          }else
          {
            printf("█");
          }
        }
        else if(isCalling == 5 && scale[numScale - rescaled] != 'c')
        {
         printf("█");
        }
        else if(isCalling == 3 && scale[numScale - rescaled] != 'c' && scale[numScale - rescaled] != '<')
        {
          printf("█");
        }
        else if(isCalling == 4 && scale[numScale - rescaled] == 'B')
        {
          printf("█");
        }
        else if(isCalling == 4 && scale[numScale - rescaled] != 'B')
        {
          putchar(scale[numScale - rescaled]);
        }
        else
        {
           printf(" ");
        }
       }
    }
    if(isCalling == 2)
    {
     int pickRndEnemy = enemyTotal;
     while(enemy[pickRndEnemy].isAlive != true)
     {
       pickRndEnemy--;
     }
    while(p == 5)
    {
      if(enemy[pickRndEnemy].life < enemy[pickRndEnemy].totalLife)
      {
            int diference = enemy[pickRndEnemy].totalLife - enemy[pickRndEnemy].life;
      int critico = diference - 5;
      printf("                       👍%d critico: %d", diference, critico);
      }
      
      enemy[pickRndEnemy].totalLife = enemy[pickRndEnemy].life;
      p++;
    }
    while(p == 4)
    {
       if(life < playerlifeTotal)
       {
         int diference = playerlifeTotal - life;
         printf("                       👎%d", diference);
         
         playerlifeTotal = life;
       }
       
       p++;
    }
     while(p == 3)
    {
     printf("                                 ");
     p++;
    }
    while(p == 2)
    {
     printf("            %s %s: 💙%d",enemy[pickRndEnemy].name,enemy[pickRndEnemy].face,enemy[pickRndEnemy].life);
     p++;
    }
    while(p == 1)
    {
     printf("             %s %s: 💙%d",player.name,face,player.life);
     p++;
    }
 
    }
    else if(isCalling == 5)
    {
       char key;
       int j;
       int size = sizeof(inve) / sizeof(wchar_t);
                
        while(p == 25)
        {
             int i;
             for(i = 0; i < size; i++)
             {
                printf("%lc", inve[i]);
                if(inve[i] == 'w')
                {
                  printf("%d", changeWId);
                }
             }
             
             p++;
        }
        while(p == 1)
        {
         p = 25;
        }
    }
    else if(isCalling == 4)
    {
    while(p == 5)
    {
      p++;
    }
    while(p == 4)
    {
       p++;
    }
     while(p == 3)
    {
     p++;
    }
    while(p == 2)
    {
     p++;
    }
    while(p == 1)
    {
         int rndItemDrop = rand() % 2;
      if(rndItemDrop == 0)
      {
            weaponFunction(weaponId);
            int j;
            for(j = 1; j <= weaponId; j++)
            {
              printf("           Voce Ganhou:  %s", weaponsAll[j].name);
            }
            weaponId++;
      }else if(rndItemDrop == 1)
      {
            healFunction(weaponId++, 2);
            printf("           Voce Ganhou:  %d de Cura", 2);
      }else if(rndItemDrop == 2)
      {
        addXP(15);
        printf("           Voce Ganhou:  %d de XP", 15);
      }
     p++;
    }
    }
    putchar('\n');
  }
}


void release(image * img)
{
  if (img)
  {
    if (img->data)
      free(img->data);

    free(img);
  }
}

void printInvetory()
{
     system("cls");

    numScale = strlen(scale) - 1;
    p = 1;
      char key;
    image *img = NULL;
     while(1)
     {
       int i;
       while(1)
       {
         if(kbhit()){
                    key = getch();
           
                    if(key == 'z')
                    {
                     changeWId++;
                     
                    }
                    
                    if(key == 'c')
                    {
                       break;
                    }
         
         }
                
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        COORD coord;
        coord.X = 0;
        coord.Y = 0;
        
        SetConsoleCursorPosition(hConsole, coord);
        char mapa[] = "0000P";
        char numberString[100];
        char bmp[] = ".bmp";
        sprintf(numberString, "%d", 2);
     
       strcat(mapa, numberString);
       strcat(mapa, bmp);
     
      char *filename = mapa;
      if (loadImage(&img, filename))
      {
        printf("\n\n");
         
        asciify(img, scale, 5);
    
        release(img);
     
     }
    

     }
   break;      
 }
}


void printCombat()
{
  p = 1;
  system("cls");
  numScale = strlen(scale) - 1;
  
  int pickRndEnemy = enemyTotal;
  while(enemy[pickRndEnemy].isAlive != true)
  {
     pickRndEnemy--;
  }

  image *img = NULL;
  int i;
  bool isPlayerTurn = true;
  
  for(i = 1; i <= 30; i++)
  {
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

   COORD coord;
   coord.X = 0;
   coord.Y = 0;

  SetConsoleCursorPosition(hConsole, coord);
     char mapa[] = "0000";
     char bmp[] = ".bmp";
     char numberString[100];
     sprintf(numberString, "%d", i);
     
     strcat(mapa, numberString);
     strcat(mapa, bmp);
     
     char *filename = mapa;
      if (loadImage(&img, filename))
      {
        printf("\n\n");
        //printf("\n\n%d", i + 1);
    
        asciify(img, scale2, 2);
    
        release(img);
      }
      
      if(enemy[pickRndEnemy].life > 0 && i == 11 && player.life > 0)
      {
       i = 4;
      }
      
      if(enemy[pickRndEnemy].life <= 0)
      {
           if(i == 20)
           {
              finish = true;
              int rndXpDrop = rand() % 10;
              printf("\n");
              printf("Voce Ganhou: %d 💵\n", 10);
              plusGoldChange(10);
              printf("Voce Ganhou: %d de XP\n", rndXpDrop);
              addXP(rndXpDrop);
              int rndKeyDrop = rand() % 10;
              if(rndKeyDrop == 1)
              {
              printf("Voce Ganhou: %d 🗝", 1);
              totalKeys+= 1;
              }
              updateEnemysKilled(1);
              enemyCount--;
              enemy[pickRndEnemy].isAlive = false;
              i = 19;
              
              Sleep(2000);
              system("cls");
              break;
              //SAIR PARA O MAPA
           }  
      }
      
      if(player.life <= 0 && i < 21)
      {
        i = 21;
        
      }
      
      if(i == 30)
      {
           i = 29;
           //REINICAR TODO O JOGO
           Sleep(2000);
           main();
      }
      
      while(1 && i % 4 == 0 && enemy[pickRndEnemy].life > 0 && player.life > 0 && player.life > 0 || i == 1)
      {
                    
         char test;
         scanf("%c", &test); //LIMTAR PARA UM CARACTER E NAO CONSEGUIR FAZER ENQUANTO INIMIGO ATACAconst char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

         if(test == 'a' && isPlayerTurn)
         {
                 int critDamage = rand() % 10;
                 int crit = rand() % 10;
                 
                 if(crit == 5 || crit == 2)
                 {
                  damage = 15 + critDamage;                 
                 }
                 else
                 {
                  damage = 15; // MUDAR PARA UMA VARIAVEL DE DANO GLOBAL;
                 }
                 
                 enemy[pickRndEnemy].life-= damage;
                 p = 1;
                 isPlayerTurn = false;
                 break;
         }else if(!isPlayerTurn)
         {     
               isPlayerTurn = true;
               p = 1;
               player.life-=enemy[pickRndEnemy].damage; // MUDAR PARA UMA VARIAVEL DE DANO DO INIMIGO;
               break;
         }

         
          
      }
      
 }  
      
}

void printLevelUp()
{
  system("cls");
  numScale = strlen(scale) - 1;
  image *img = NULL;
  int i;
  
  for(i = 1; i <= 1; i++)
  {
    
     char mapa[] = "levelUp";
     char bmp[] = ".bmp";

     strcat(mapa, bmp);
     
     char *filename = mapa;
      if (loadImage(&img, filename))
      {
        printf("\n\n");
         
        asciify(img, scale, 3);
    
        release(img);
        
        printf("Agora voce esta no level: %d", player.level);
        Sleep(3000);
      }
      
      
  }
}

void printChest()
{
  system("cls");
  p = 1;
  numScale = strlen(scale) - 1;

  image *img = NULL;
  int i;
  
  for(i = 1; i <= 17; i++)
  {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coord;
    coord.X = 0;
    coord.Y = 0;

    SetConsoleCursorPosition(hConsole, coord);
    
     char mapa[] = "chest";
     char bmp[] = ".bmp";
     char numberString[100];
     sprintf(numberString, "%d", i);
     
     strcat(mapa, numberString);
     strcat(mapa, bmp);
     
     char *filename = mapa;
      if (loadImage(&img, filename))
      {
        printf("\n\n");
         
        asciify(img, scale, 4);
    
        release(img);
      }
      
      if(i == 17)
      {
        i = 16;
        Sleep(2000);
        break;
      }
      
      
  }
  
}

void printDanger()
{
  system("cls");
  numScale = strlen(scale) - 1;

  image *img = NULL;
  int i;
  
  for(i = 1; i <= 1; i++)
  {
     char mapa[] = "0000f";
     char bmp[] = ".bmp";

     strcat(mapa, bmp);
     
      char *filename = mapa;
      if (loadImage(&img, filename))
      {
        printf("\n\n");
    
        asciify(img, scale, 1);
    
        release(img);
      }
      
      Sleep(2000);
  }
  
}

void displayStats()
{
          wchar_t conteudoName[200] = L"Nome: ";
          wcscat(conteudoName, player.name);
          int tamanhoConteudoName = wcslen(conteudoName);
          wchar_t* posicaoName = wcsstr(inve, L"n");
          
          if (posicaoName != NULL)
          {
                  wchar_t* meioLinha = wcschr(posicaoName, L'n');
                  int meio = (meioLinha - posicaoName) / 2;
                  memmove(posicaoName + meio, posicaoName + meio - tamanhoConteudoName / 2, wcslen(posicaoName + meio) + 1);
                  memcpy(posicaoName + meio - tamanhoConteudoName / 2, conteudoName, tamanhoConteudoName * sizeof(wchar_t));
                  memmove(posicaoName + meio + tamanhoConteudoName / 2, posicaoName + meio + tamanhoConteudoName, wcslen(posicaoName + meio + tamanhoConteudoName / 2) + 1);           
         }
        
          wchar_t conteudoLife[200] = L"Vida: ";
          wchar_t lifeToString[100];
          
          swprintf(lifeToString, L"%d", player.life);
          
          wcscat(conteudoLife, lifeToString);
          int tamanhoConteudoLife = wcslen(conteudoLife);
          wchar_t* posicaoLife = wcsstr(inve, L"v");
          
          if (posicaoLife != NULL)
          {
                  wchar_t* meioLinha = wcschr(posicaoLife, L'v');
                  int meio = 0;
                  memmove(posicaoLife + meio, posicaoLife + meio - tamanhoConteudoLife / 2, wcslen(posicaoLife + meio) + 1);
                  memcpy(posicaoLife + meio - tamanhoConteudoLife / 2, conteudoLife, tamanhoConteudoLife * sizeof(wchar_t));
                  memmove(posicaoLife + meio + tamanhoConteudoLife / 2, posicaoLife + meio + tamanhoConteudoLife, wcslen(posicaoLife + meio + tamanhoConteudoLife / 2) + 1);           
        }
        
          wchar_t conteudoLevel[200] = L"Level: ";
          wchar_t levelToString[100];
          
          swprintf(levelToString, L"%d", player.level);
          
          wcscat(conteudoLevel, levelToString);
          int tamanhoConteudoLevel = wcslen(conteudoLevel);
          wchar_t* posicaoLevel = wcsstr(inve, L"l");
          
          if (posicaoLevel != NULL)
          {
                  wchar_t* meioLinha = wcschr(posicaoLevel, L'l');
                  int meio = (meioLinha - posicaoLevel) / 2;
                  memmove(posicaoLevel + meio, posicaoLevel + meio - tamanhoConteudoLevel / 2, wcslen(posicaoLevel + meio) + 1);
                  memcpy(posicaoLevel + meio - tamanhoConteudoLevel / 2, conteudoLevel, tamanhoConteudoLevel * sizeof(wchar_t));
                  memmove(posicaoLevel + meio + tamanhoConteudoLevel / 2, posicaoLevel + meio + tamanhoConteudoLevel, wcslen(posicaoLevel + meio + tamanhoConteudoLevel / 2) + 1);           
        }
        
          wchar_t conteudoKills[200] = L"Kills: ";
          wchar_t killsToString[100];
          
          swprintf(killsToString, L"%d", player.enemysKilled);
          
          wcscat(conteudoKills, killsToString);
          int tamanhoConteudokills = wcslen(conteudoKills);
          wchar_t* posicaoKills = wcsstr(inve, L"p");
          if (posicaoKills != NULL)
          {
                  wchar_t* meioLinha = wcschr(posicaoKills, L'p');
                  int meio = (meioLinha - posicaoKills) / 2;
                  memmove(posicaoKills + meio, posicaoKills + meio - tamanhoConteudokills / 2, wcslen(posicaoKills + meio) + 1);
                  memcpy(posicaoKills + meio - tamanhoConteudokills / 2, conteudoKills,tamanhoConteudokills * sizeof(wchar_t));
                  memmove(posicaoKills + meio + tamanhoConteudokills / 2, posicaoKills + meio + tamanhoConteudokills, wcslen(posicaoKills + meio + tamanhoConteudokills / 2) + 1);           
         }
        
          wchar_t conteudoGold[200] = L"Gold: ";
          wchar_t goldToString[100];
          
          swprintf(goldToString, L"%d", player.gold);
          
          wcscat(conteudoGold, goldToString);
          int tamanhoConteudoGold = wcslen(conteudoGold);
          wchar_t* posicaoGold = wcsstr(inve, L"g");
          
          if (posicaoGold != NULL)
          {
                  wchar_t* meioLinha = wcschr(posicaoGold, L'g');
                  int meio = (meioLinha - posicaoGold) / 2;
                  memmove(posicaoGold + meio, posicaoGold + meio - tamanhoConteudoGold / 2, wcslen(posicaoGold + meio) + 1);
                  memcpy(posicaoGold + meio - tamanhoConteudoGold / 2, conteudoGold,tamanhoConteudoGold * sizeof(wchar_t));
                  memmove(posicaoGold + meio + tamanhoConteudoGold / 2, posicaoGold + meio + tamanhoConteudoGold, wcslen(posicaoGold + meio + tamanhoConteudoGold / 2) + 1);           
        }
        


}

void clearInve()
{
wcscpy(inve,inveCopy);
}

void game()
{
   weaponFunction(weaponId);
   weaponId++;
    
    POINT pt;
    int MonitorWidth = GetSystemMetrics(SM_CXSCREEN);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };

    wchar_t map[] =
L"#####################################################################\n"
L"#                     ##                                            #\n"
L"#                      #######            ##########      ###########\n"
L"#                      #    ####################                    #\n"
L"w#  ##  ##             #                #        #           #########\n"
L"#  #       ##                                   #               #####\n"
L"#  ####   #  ##                         #       #                   #\n"
L"# #             ##        ## #      #############       ######      #\n"
L"##                 ###                 #        # #                 #\n"
L"###########         #                  #        ######              #\n"
L"###  #        ######                                    #           #\n"
L"######      ##################         #                ##         ##\n"
L"#  ###               #                  #                ## #########\n"
L"#   # #                       #    #######               ##        ##\n"
L"#     ################# #     #           #####          #### #######\n"
L"#                      ###    ##      #####              # ##### ####\n"
L"#                     #        ######   #      ###########        ###\n"
L"#                      #                #      ##                   #\n"
L"#                       #               #                           #\n"
L"#   ##########               #   #          ####    #               #\n"
L"#       #               #      #       #   ####                     #\n"
L"#       #               #         ##  ##   #                        #\n"
L"#       #               #         ##                    #####   ## ##\n"
L"#       #              ##     #############  ####                   #\n"
L"#       #              #      ####                                ##\n"
L"#                       #            ##   ##########################\n"
L"#                         #      ###      ###########################\n"
L"#                         #            ##############################\n"
L"#         ########                 #      ###########################\n"
L"#                #           #            ###########################\n"
L"#                 #         #       #################################\n"
L"#####################################################################\n";
    
     wchar_t screen[nScreenWidth * nScreenHeigth];
     //map[(int)fPlayerY * mMapWidthh + (int)fPlayerX] == '#' ? fPlayerX = numero, fPlayerY = numero MUDAR POSICAO DO PERSONAGEM QUANDO MATAR TODOS INIMGISO E PEGAR TODOS OS BAUS
    char key;
    
    if(dungeonLevel / 5 != 0)
    {
              enemyTotal = (rand() % enemyTotal) + 1;
              enemyTotal++;
    }
    
    
    while(1)
    {
        int rndPosX = rand() % mMapWidthh;
        int rndPosY = rand() % mMapHeigth;
        
        if(map[rndPosX * rndPosY] != '#')
        {
          fPlayerX = rndPosX;
          fPlayerY = rndPosY;
          
          break;       
        }else
        {
        }
    }
    
    enemyFunction(1*dungeonLevel);
    
    while(1)
    {
        GetCursorPos(&pt);
        if(enemyCount <= 0)
        {
            dungeonLevel++;
            game();
        }
        
        
        if(player.xp >= xpToUp)
        {
          levelUp(1);
          player.xp = 0;
          player.lifeTotal = 25 * player.level;
          printLevelUp();
          textcolor(WHITE);
        }   
        if(pt.x == 0)
        {
           fPlayerA -=0.3f;
        }else if(pt.x > MonitorWidth - 5){
           fPlayerA +=0.3f;
        }
        
        if(kbhit())
        {
            key = getch();
            if(key == 'c')
            {
               clearInve();
               displayStats();
               printInvetory();
            }
            if(key == 'w' || key == 's')
            {
              int rndEnemyAppers = rand() % 2;
              int rndChestAppers = rand() % 15;
              
              if(totalKeys > 0  && rndChestAppers == 1)
              {
                 printChest();
              }
              
              if(rndEnemyAppers == 1 && enemyTotal > 0)
              {
                 printDanger();
                 printCombat();
                 
                 textcolor(WHITE);
              }
            }
            if(key == 'w')
            {
               fPlayerX += sinf(fPlayerA) * 1.0f;
               fPlayerY += cosf(fPlayerA) * 1.0f;
               
               if(map[(int)fPlayerY * mMapWidthh + (int)fPlayerX] == '#')
               {
               fPlayerX-= sinf(fPlayerA)* 1.0f;
               fPlayerY-= cosf(fPlayerA)* 1.0f;
               }
               
               if(player.life < player.lifeTotal)
               {
                  player.life += 5;
               }
               
            }
            else if(key == 's')
            {
               fPlayerX-= sinf(fPlayerA)* 1.0f;
               fPlayerY-= cosf(fPlayerA)* 1.0f;
            
               if(map[(int)fPlayerY * mMapWidthh + (int)fPlayerX] == '#')
               {
               fPlayerX+= sinf(fPlayerA)* 1.0f;
               fPlayerY+= cosf(fPlayerA)* 1.0f;
               }
               
               if(player.life < player.lifeTotal)
               {
                  player.life += 5;
               }
            }
            
        }
        
        int x;
        for(x = 0; x < nScreenWidth; x++)
        {
           float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
           float fDistanceToWall = 0;
           
           bool hitWall = false;
           bool hitChest = false;
           
           float fEyeX = sinf(fRayAngle);
           float fEyeY = cosf(fRayAngle);

           
           while(!hitWall && fDistanceToWall < fDepth)
           {
             fDistanceToWall += 0.1f;
             
             int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
             int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);
             
             if(nTestX < 0 || nTestX >= mMapWidthh || nTestY < 0 || nTestY >= mMapHeigth)
             {
                       hitWall = true;
                       fDistanceToWall = fDepth; 
             }else
             {
              if(map[nTestY * mMapWidthh + nTestX] == '#')
              {
                     hitWall = true;
              }      
             
             }
           }
        
           int nCelling = (float)(nScreenHeigth / 2.0) - nScreenHeigth / ((float)fDistanceToWall);
           int nFloor = nScreenHeigth - nCelling;
           wchar_t nShade;
                    if(fDistanceToWall <= fDepth / 4.0f){nShade = 'c';}
                    else if(fDistanceToWall < fDepth / 3.0f){nShade = 'a';}
                    else if(fDistanceToWall < fDepth / 2.0f){nShade = 's';}
                    else if(fDistanceToWall < fDepth){nShade = 'd';}
                    else{nShade = ' ';}
                    
           int y;
           for(y = 0; y < nScreenHeigth; y++)
           {
              if(y < nCelling)
              {
                   screen[y*nScreenWidth+x] = ' ';
              }
              else if(y > nCelling && y <= nFloor)
              {    
               screen[y*nScreenWidth+x] = nShade;
              }
              else
              {
                  char nShade2;
                  float b = 1.0f -  (((float)y - nScreenHeigth / 2.0f) / ((float)nScreenHeigth / 2.0f));
                  if(b < 0.25) {nShade2 = '#';}
                  else if(b < 0.5){nShade2 = 'x';}
                  else if(b < 0.75){nShade2 = '.';}
                  else if(b < 0.9){nShade2 = '-';}
                  else {nShade2 = ' ';}
                  screen[y*nScreenWidth+x] = nShade2;
              }
           }
           
        }
        
        
        
        int enemys;
        for(enemys = 0; enemys < enemyCount; enemys++)
        {
            screen[0+enemys] = 'v';
            if(enemys == enemyTotal)
            {
              screen[0+enemys+1] = 'p';
            }
            
        }
        
        int keysCounter;
        
        for(keysCounter = 0; keysCounter < totalKeys; keysCounter++)
        {
            screen[180+keysCounter] = 'l';
            
        }
          
        screen[nScreenWidth * nScreenHeigth - 1] = '\0';
        //WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeigth, coordScreen, &dwBytesWritten);
        int c;
        int b = 0;
        for(c = 0; c < nScreenWidth * nScreenHeigth; c++)
        {                         
             if(screen[c] == 'c')
             {
                printf("█");
                backGround = 'c';
             }
             else if(screen[c] == 'a')
             {
                printf("▓");
                backGround = 'a';
             }else if(screen[c] == 's')
             {
              printf("▒");
              
              backGround = 's';
             }
             else if(screen[c] == 'd')
             {
                  printf("░");
                  backGround = 'd';
             }
             else if(screen[c] == 'v')
             {
                printf("💀");
             }
             else if(screen[c] == 'p')
             {
                if(enemyCount > 20)
                {
                  printf("+");
                }
             }
             else if(screen[c] == 'l')
             {
                 printf("🗝");
             }
             else
             {
              wprintf(L"%lc", screen[c]);
             }
        }
        SetConsoleCursorPosition(hConsole, coordScreen);
    }
}
 
int main()
{
  setlocale(LC_ALL, "UTF-8");
  srand(time(0));
  
  inicilizerPlayerFunction();
  game();

 system("PAUSE");
 return 0;
}
