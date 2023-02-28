#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //clock function
#include <windows.h> //sleep function
#include <conio.h>

char *forKontrol(char *satir);
char *remove_white_space(char *str);
char *timeComplexity(FILE *file);
float gecenSure(float gecen_sure);
char *whileKontrol(char *satir);
char *fonksiyonKontrol(char *satir);
char *spaceComplexity(FILE *file);

int main()
{

    FILE *dosya;
    
    timeComplexity(dosya);
    printf("\n");
    spaceComplexity(dosya);
    

    getch();
}

char *forKontrol(char *satir)
{
    char *token = strtok(satir,";"); //parcalara ayirmak icin ; ile olan kisma kadar alir strtok fonksiyonu sınırlayıcı karaktere kadar olan kısmı alır
    //printf("%s\n",satir);

    while(token != NULL)
    {
        //printf("%s\n",satir);
        if(strstr(token,"<=") != NULL) //for dongosu icinde <= e kadar olan kısım strstr fonksiyonu stringin icerisinde belirtilen karakterin ilk yerini bulur
        {
            token = strtok(token,"<=");//<= ile parcalara ayirdik
            token = strtok(NULL,"<=");
            token = remove_white_space(token); //for dongusunde bosluk birakarak mi bitisik mi yazildi
            break;
        }
        else if(strstr(token,">=") != NULL) //for dongosu icinde >= var mi ?
        {
            token = strtok(token,">=");//>= ile parcalara ayirdik
            token = strtok(NULL,">=");
            token = remove_white_space(token); //for dongusunde bosluk birakarak mi bitisik mi yazildi
            break;
        }
        else if(strstr(token,"<") != NULL) //for dongosu icinde < var mi ?
        {
            token = strtok(token,"<");//< ile parcalara ayirdik
            token = strtok(NULL,"<");
            token = remove_white_space(token); //for dongusunde bosluk birakarak mi bitisik mi yazildi
            break;
        }
        else if(strstr(token,">") != NULL) //for dongosu icinde > var mi ?
        {
            token = strtok(token,">");//> ile parcalara ayirdik
            token = strtok(NULL,">");
            token = remove_white_space(token); //for dongusunde bosluk birakarak mi bitisik mi yazildi
            break;
        }
        else
        {
            token = strtok(NULL,";"); //hicbiri yoksa diger ;'e
        }
    }
    return token;
}

char *remove_white_space(char *str) //bosluk kontrolu
{
    int i = 0, j = 0;

    while(str[i])
    {
        if(str[i] != ' ')
        {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
    return str;
}

char *timeComplexity(FILE *file)
{
     FILE *dosya = fopen("input.txt","r");

     double gecen_sure = 0.0;
     clock_t baslangic = clock();

    int satirUzunlugu = 255; //1 satirda max 255 karakter olarak aldim
    char satir [satirUzunlugu]; //diziye attim.
    int satirSayisi = 0;

    while(fgets(satir,satirUzunlugu,dosya))//count-1 karakter okur.Satiri tek tek okuyacak.
    {
        //printf("satir:%s\n",satir);
        //printf("satir sayisi : %d\n",satirSayisi);
        if(satirSayisi >= 0)//0.satir fonksiyon tanimi 1.satir { baslangici o yüzden 2. ve üstü satir aldim
        {            
            char tokenn[255][255];

            if(strstr(satir,"for")) //eger satir icinde for varsa
            {
                
                char *token = forKontrol(satir); //forkontrolde amacım dongude bir sayimi var yoksa bir karakter mi onu bulmak n mi yada 5mi ?
                strcat(tokenn,token); //karakter dizisini diger karakter dizisinin sonuna eklemeye yarıyor. tokeni tokenn sonuna ekledi

                while(fgets(satir,satirUzunlugu,dosya))
                {
                    if(strstr(satir,"for"))
                    {
                        char *temp = forKontrol(satir);
                        strcat(tokenn,temp);
                    }
                }
                printf("Time Complexity : ");
                int i,j,number = 0;
                int sayi = 1;

                for(i = 0; i < strlen(tokenn); i++)
                {
                    for(j = 0; j < strlen(tokenn[i]); j++)
                    {
                     
                        if( tokenn[i][j] == 'n') //kac kere n gectigine gore number++ ic ice ise n^2 vs bulmak icin
                        {
                            number++;
                        }
                        else
                        {
                            sayi = sayi * (tokenn[i][j]-'0');
                            //printf("%d",sayi);
                        }
                    }
                }
                if(number>0)
                {
                    printf("O(%dn^%d) --> ",sayi,number);
                    printf("O(n^%d)",number);
                }
                else
                {
                    printf("O(%d)",sayi);
                }
                //printf("%s\n",satir);
            }

            else if(strstr(satir,"switch"))
            {
                printf("Time Complexity --> O(n)");
                printf("Space Complexity --> O(n)");
            }

            else if(strstr(satir,"while"))
            {
                char *token = whileKontrol(satir);
                strcat(tokenn,token);

                while(fgets(satir,satirUzunlugu,dosya))
                {
                    if(strstr(satir,"while"))
                    {
                        char *temp = whileKontrol(satir);
                        strcat(tokenn,temp);
                    }
                }
                printf("Time Complexity : ");
                int i,j,number = 0;
                int sayi = 1;

                for(i = 0; i < strlen(tokenn); i++)
                {
                    for(j = 0; j < strlen(tokenn[i]); j++)
                    {
                     
                        if( tokenn[i][j] == 'n')
                        {
                            number++;
                        }
                        else
                        {
                            sayi = sayi * (tokenn[i][j] - '0');
                            //printf("%d",sayi);
                        }
                    }
                }
                if(number>0)
                {
                    printf("O(%dn^%d) --> ",sayi,number);
                    printf("O(n^%d)",number);
                }
                else
                {
                    printf("O(%d)",sayi);
                }
            }
            else if(strstr(satir,"return n"))
            {
                printf("Time Complexity ---> O(n)");

            }
        }
        satirSayisi++;
    }
     fclose(dosya);
    Sleep(1);
    clock_t bitis = clock(); //bitis zamani
    gecen_sure += ((double)(bitis - baslangic) / CLOCKS_PER_SEC)- 0.01;//bitis - baslangic ile arada gecen sureyi saniye cinsinden hesaplama
    printf("\nDosyadan Okunan Kodun Calisma Suresi : %f Saniye",gecen_sure); //sleep de gecen sureyi cikarttim sleep olmadan genelde 0.000 sn hesapliyor.
    gecenSure(gecen_sure);
}

float gecenSure(float gecen_sure)
{
    if(gecen_sure <= 0.00250) //2.5 milisaniye ve alti
    {
        printf("\nRunning Time Complexity ---> Best Case...");
    }
    else if (gecen_sure > 0.00250 && gecen_sure <0.005) //2.5 ve 5 milisaniye arasi
    {
        printf("\nRunning Time Complexity ---> Avarege Case...");
    }
    else
    {
        printf("\nRunning Time Complexity ---> Worst Case....");
    }
}

char *whileKontrol(char *satir)
{
    char *token = strtok(satir,")");
    //printf("%s",token);
    while(token != NULL)
    {
        if(strstr(token,"<=") != NULL) //for dongosu icinde <= e kadar olan kısım
        {
            token = strtok(token,"<=");//<= ile parcalara ayirdik
            //printf("\n%s",token);
            token = strtok(NULL,"<=");
            //printf("\n%s",token);
            token = remove_white_space(token); //for dongusunde bosluk birakarak mi bitisik mi yazildi
            //printf("\n%s",token);
            break;
        }
        else if(strstr(token,">=") != NULL) //for dongosu icinde >= var mi ?
        {
            token = strtok(token,">=");//>= ile parcalara ayirdik
            token = strtok(NULL,">=");
            token = remove_white_space(token); //for dongusunde bosluk birakarak mi bitisik mi yazildi
            break;
        }
        else if(strstr(token,"<") != NULL) //for dongosu icinde < var mi ?
        {
            token = strtok(token,"<");//< ile parcalara ayirdik
            token = strtok(NULL,"<");
            token = remove_white_space(token); //for dongusunde bosluk birakarak mi bitisik mi yazildi
            break;
        }
        else if(strstr(token,">") != NULL) //for dongosu icinde > var mi ?
        {
            token = strtok(token,">");//> ile parcalara ayirdik
            token = strtok(NULL,">");
            token = remove_white_space(token); //for dongusunde bosluk birakarak mi bitisik mi yazildi
            break;
        }
    }
    //printf("\n%s",token);
    return token;
}

char *spaceComplexity(FILE *file2)
{
    FILE *dosya = fopen("input.txt","r");

    int satirUzunlugu = 255; //1 satirda max 255 karakter olarak aldim
    char satir [satirUzunlugu]; //diziye attim.
    int satirSayisi = 0;
    int byte = 0;


    while(fgets(satir,satirUzunlugu,dosya))//count-1 karakter okur.Satiri tek tek okuyacak.
    {
        //printf("satir:%s\n",satir);
        //printf("satir sayisi : %d\n",satirSayisi);
        if(satirSayisi >= 0)//0.satir fonksiyon tanimi 1.satir { baslangici o yüzden 2. ve üstü satir aldim
        {   
            char tokenn[255][255];

            if(strstr(satir,"int"))
            {
                byte++;
            }

            if(strstr(satir,"while"))
            {
                char *token = whileKontrol(satir);
                strcat(tokenn,token);

                while(fgets(satir,satirUzunlugu,dosya))
                {
                    if(strstr(satir,"while"))
                    {
                        char *temp = whileKontrol(satir);
                        strcat(tokenn,temp);
                    }
                }
                printf("Space Complexity : ");
                int i,j,number2 = 0;
                int sayi = 1;

                for(i = 0; i < strlen(tokenn); i++)
                {
                    for(j = 0; j < strlen(tokenn[i]); j++)
                    {
                     
                        if( tokenn[i][j] == 'n')
                        {
                            number2++;
                        }
                        else
                        {
                            sayi = sayi * (tokenn[i][j] - '0');
                            //printf("%d",sayi);
                        }
                    }
                }
                if(number2>0)
                {
                    printf("O(4n^%d+%d)",number2,(byte-1)*4);
                    printf("\nRunning Time T(%d(n+1)+%d)",number2,satirSayisi-4);
                }
                else
                {
                    printf("O(%d)",sayi);
                }
            }
            else if(strstr(satir,"for"))
            {
                char *token = forKontrol(satir);
                strcat(tokenn,token);

                while(fgets(satir,satirUzunlugu,dosya))
                {
                    if(strstr(satir,"for"))
                    {
                        char *temp = forKontrol(satir);
                        strcat(tokenn,temp);
                    }
                }
                printf("Space Complexity : ");
                int i,j,number2 = 0;
                int sayi = 1;

                for(i = 0; i < strlen(tokenn); i++)
                {
                    for(j = 0; j < strlen(tokenn[i]); j++)
                    {
                     
                        if( tokenn[i][j] == 'n')
                        {
                            number2++;

                        }
                        else
                        {
                            sayi = sayi * (tokenn[i][j]-'0');
                            //printf("%d",sayi);
                        }
                    }
                }
                if(number2>0)
                {
                    printf("O(4n^%d+%d)",number2,(byte-1)*4);
                    printf("\nRunning Time T(%d(n)+%d)",number2,satirSayisi);
                }
                else
                {
                    printf("O(%d)",sayi);
                }
            
            }
            else if(strstr(satir,"return n"))
            {
                printf("Space Complexity ---> O(n + %d)",byte*4);
            }

    }
    satirSayisi++;
}
fclose(dosya);
}