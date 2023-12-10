#include<stdio.h>

char  playerField1[113] =  "\
| |Q|W|E|R|T|Y|\n\
|1| | | | | | |\n\
|2| | | | | | |\n\
|3| | | | | | |\n\
|4| | | | | | |\n\
|5| | | | | | |\n\
|6| | | | | | |\n";

char playerField2[113];
char hitField1[113];
char hitField2[113];

int coordinat1 = 0;
char coordinat2 = '\0';
char downORright = '\0';
int sizeShip = 4;
int field1ORfield2 = 0;
                
void upperChar();                
void playerInput();     
int checkInput = 1;
void printShip(int elemMas);
void installShip(int elemMas);           
int workCoordinat();
char * fire();
char * resFire;
int plrHits1 = 0, plrHits2 = 0;

int main()
{
    strcpy(playerField2, playerField1);
    strcpy(hitField1, playerField1);
    strcpy(hitField2, playerField1);
    
    // позиционка
    field1ORfield2 = 0;
    puts("Теперь ход игрока 1, введите любой символ...");
    while(getchar()!='\n');
    puts("Сначала берем координату и от нее ставим вправо или в низ корабль");
    while(sizeShip!=0)
    {    
        puts("ИГРОК 1");
        printf("%s", playerField1);
        playerInput();
        installShip(workCoordinat());
        system("clear");
    }   
    sizeShip = 4;
    field1ORfield2 = 1;
    puts("Теперь ход игрока 2, введите любой символ...");
    while(getchar()!='\n');
    while(sizeShip!=0)
    {
        puts("ИГРОК 2");
        printf("%s", playerField2);
        playerInput();
        installShip(workCoordinat());
        system("clear");
    }
    
    // Война
    puts("Теперь ход игрока 1, введите любой символ...");
    while(getchar()!='\n');
    while( (plrHits1!=9)&&(plrHits2!=9 ) )
    {
        puts("ИГРОК 1:");
        field1ORfield2 = 0;
        puts("Мой флот:");
        printf("%s", playerField1);
        puts("Удары по п*******!:"); // по поврагам!
        printf("%s", hitField1);
        printf("Куда жахнем, капитан?\n");
        resFire = fire();
        system("clear");
        printf("%d%c %s\n", coordinat1, coordinat2, resFire);
        printf("%s", hitField1);
        puts("Теперь очередь игрока 2");
        printf("Введите любой символ...");
        getchar();
        system("clear");
        
        puts("ИГРОК 2:");
        field1ORfield2 = 1;
        puts("Мой флот:");
        printf("%s", playerField2);
        puts("Удары по п*******!:"); // по поврагам!
        printf("%s", hitField2);
        printf("Куда жахнем, капитан?\n");
        resFire = fire();
        system("clear");
        printf("%d%c %s\n", coordinat1, coordinat2, resFire);
        printf("%s", hitField2);
        puts("Теперь очередь игрока 1");
        printf("Введите любой символ...");
        getchar();
        system("clear");
    }
    if(plrHits1 == 9)
        puts("Игра окончена, ПОБЕДИЛ ИГРОК 1");
    else if(plrHits2 == 9)
        puts("Игра окончена, ПОБЕДИЛ ИГРОК 2");
        
    return 0;
}

void upperChar()
{
    if(coordinat2=='q')
         coordinat2='Q';
    if(coordinat2=='w')
         coordinat2='W';
    if(coordinat2=='e')
         coordinat2='E';
    if(coordinat2=='r')
         coordinat2='R';
    if(coordinat2=='t')
         coordinat2='T';
    if(coordinat2=='y')
         coordinat2='Y';
    if(downORright=='r')
         downORright='R';
    if(downORright=='d')
         downORright='D';        
}        
void playerInput()
{
   while(checkInput)
   {
    puts("Пожалуйста введите координаты:");
    printf("цифру- ");
    scanf("%d", &coordinat1);
    while(getchar() != '\n');
    printf("букву- ");
    scanf("%c", &coordinat2);
    while(getchar() != '\n');
    printf("От %d%c вниз(d) или вправо(r)? Введите d или r: ", coordinat1, coordinat2);
    scanf("%c", &downORright);
    while(getchar() != '\n');
    upperChar();
    printf("%d %c %c\n", coordinat1, coordinat2, downORright);
    if( (coordinat1<1)||(coordinat1>6) )
        checkInput = 1;
    else if( !((coordinat2=='Q')||(coordinat2=='W')||(coordinat2=='E')||(coordinat2=='R')||(coordinat2=='T')||(coordinat2=='Y')) )
        checkInput = 1;
    else if( !((downORright=='R')||(downORright=='D')) )    
        checkInput = 1;
    else 
        checkInput = 0;    
    if(checkInput==1)
        printf("Упс... Туда нельзя - минное поле.\nУкажите другое место\n");
    //while(getchar()!='\n');  
   }   
   checkInput = 1;
    //обработать ошибки, регистр, повторить ввод в этом случа
}    
    
void printShip(int elemMas)    
{
    if(downORright=='R')
    {
        for(int i=0;i<sizeShip*2;i++,i++)
        {
            if(field1ORfield2==0)
            {
                playerField1[elemMas+i]='@';
                printf("%d size-%d\n", elemMas+i, sizeShip);
            }
            else if(field1ORfield2==1)
            {
               playerField2[elemMas+i]='@';
               printf("%d size-%d\n", elemMas+i, sizeShip);
            }
        }   
    }
    else if(downORright=='D')
    {
        int offset = 0;
        for(int i=0;i<sizeShip*2;i++,i++)
        {
            if(field1ORfield2==0)
            {
                playerField1[elemMas+offset]='@';
                printf("%d size-%d\n", elemMas+i, sizeShip);
                offset += 16;
            }
            else if(field1ORfield2==1)
            {
                playerField2[elemMas+offset]='@';
                printf("%d size-%d\n", elemMas+i, sizeShip);
                offset += 16;
            }
        }   
    }
}

void installShip(int elemMas)
{       
    if(downORright=='R')
    {
        if( (sizeShip==4)&&(coordinat2=='E')||(sizeShip==4)&&(coordinat2=='W')||(sizeShip==4)&&(coordinat2=='Q') )
        {
            printShip(elemMas);
            sizeShip = 3;
        }    
        else if( (sizeShip==3)&&(coordinat2=='R')||(sizeShip==3)&&(coordinat2=='E')||(sizeShip==3)&&(coordinat2=='W')||(sizeShip==3)&&(coordinat2=='Q') )
        {
            printShip(elemMas);
            sizeShip = 2;
        }    
        else if( (sizeShip==2)&&(coordinat2=='T')||(sizeShip==2)&&(coordinat2=='R')||(sizeShip==2)&&(coordinat2=='E')||(sizeShip==2)&&(coordinat2=='W')||(sizeShip==2)&&(coordinat2=='Q') )
        {
            printShip(elemMas);    
            sizeShip = 0;
        }    
    }
    else if(downORright=='D')
    {
        if( (sizeShip==4)&&(coordinat1==3)||(sizeShip==4)&&(coordinat1==2)||(sizeShip==4)&&(coordinat1==1) )
        {
            printShip(elemMas);
            sizeShip = 3;
        }    
        else if( (sizeShip==3)&&(coordinat1==4)||(sizeShip==3)&&(coordinat1==3)||(sizeShip==3)&&(coordinat1==2)||(sizeShip==3)&&(coordinat1==1) )
        {
            printShip(elemMas);
            sizeShip = 2;
        }    
        else if( (sizeShip==2)&&(coordinat1==5)||(sizeShip==2)&&(coordinat1==4)||(sizeShip==2)&&(coordinat1==3)||(sizeShip==2)&&(coordinat1==2)||(sizeShip==2)&&(coordinat1==1) )
        {
            printShip(elemMas);    
            sizeShip = 0;
        }    
    }
}
    
int workCoordinat()
{        
    if( (coordinat1==1)&&(coordinat2=='Q') )
        return(19);
    else if( (coordinat1==1)&&(coordinat2=='W') )
        return(21);
    else if( (coordinat1==1)&&(coordinat2=='E') )
        return(23);
    else if( (coordinat1==1)&&(coordinat2=='R') )   
        return(25);
    else if( (coordinat1==1)&&(coordinat2=='T') )
        return(27);
    else if( (coordinat1==1)&&(coordinat2=='Y') )
        return(29);
    else if( (coordinat1==2)&&(coordinat2=='Q') )
        return(35);
    else if( (coordinat1==2)&&(coordinat2=='W') )
        return(37);
    else if( (coordinat1==2)&&(coordinat2=='E') )
        return(39);
    else if( (coordinat1==2)&&(coordinat2=='R') )   
        return(41);
    else if( (coordinat1==2)&&(coordinat2=='T') )
        return(43);
    else if( (coordinat1==2)&&(coordinat2=='Y') )
        return(45);
    else if( (coordinat1==3)&&(coordinat2=='Q') )
        return(51);
    else if( (coordinat1==3)&&(coordinat2=='W') )
        return(53);
    else if( (coordinat1==3)&&(coordinat2=='E') )
        return(55);
    else if( (coordinat1==3)&&(coordinat2=='R') )   
        return(57);
    else if( (coordinat1==3)&&(coordinat2=='T') )
        return(59);
    else if( (coordinat1==3)&&(coordinat2=='Y') )
        return(61);
    else if( (coordinat1==4)&&(coordinat2=='Q') )
        return(67);
    else if( (coordinat1==4)&&(coordinat2=='W') )
        return(69);
    else if( (coordinat1==4)&&(coordinat2=='E') )
        return(71);
    else if( (coordinat1==4)&&(coordinat2=='R') )   
        return(73);
    else if( (coordinat1==4)&&(coordinat2=='T') )
        return(75);
    else if( (coordinat1==4)&&(coordinat2=='Y') )
        return(77);
    else if( (coordinat1==5)&&(coordinat2=='Q') )
        return(83);
    else if( (coordinat1==5)&&(coordinat2=='W') )
        return(85);
    else if( (coordinat1==5)&&(coordinat2=='E') )
        return(87);
    else if( (coordinat1==5)&&(coordinat2=='R') )   
        return(89);
    else if( (coordinat1==5)&&(coordinat2=='T') )
        return(91);
    else if( (coordinat1==5)&&(coordinat2=='Y') )
        return(93);
    else if( (coordinat1==6)&&(coordinat2=='Q') )
        return(99);
    else if( (coordinat1==6)&&(coordinat2=='W') )
        return(101);
    else if( (coordinat1==6)&&(coordinat2=='E') )
        return(103);
    else if( (coordinat1==6)&&(coordinat2=='R') )   
        return(105);
    else if( (coordinat1==6)&&(coordinat2=='T') )
        return(107);
    else if( (coordinat1==6)&&(coordinat2=='Y') )
        return(109);
}    

char * fire()
{
    printf("цифру- ");
    scanf("%d", &coordinat1);
    while(getchar() != '\n');
    printf("букву- ");
    scanf("%c", &coordinat2);
    while(getchar() != '\n');
    upperChar();
  
    char ch1 = playerField1[workCoordinat()];
    char ch2 = playerField2[workCoordinat()];
    int ShipORno1 = 0;
    int ShipORno2 = 0;
    if(ch1 == '@')
        ShipORno1 = 1;
    if(ch2 == '@')
        ShipORno2 = 1;    
    printf("ch1%cshp1%dch2%cshp2%d", ch1, ShipORno1, ch2, ShipORno2);
    if(field1ORfield2==0)
    {    
        if(ShipORno2 == 1)
        {
            hitField1[workCoordinat()] = '+';
            plrHits1++;
            return "Браво, туда их, ахаха!!!";
        }    
        else if(ShipORno2 == 0);
        {
            hitField1[workCoordinat()] = '-';
            return "Промах.";
        }    
    }    
    else if(field1ORfield2==1)
    {
        if(ShipORno1 == 1)
        {
            hitField2[workCoordinat()] = '+';
            plrHits2++;
            return "Попали-попали, давай еще!!!";
        }
        else if(ShipORno1 == 0);
        {
            hitField2[workCoordinat()] = '-';
            return "Промах.";
        } 
    }
}
    
