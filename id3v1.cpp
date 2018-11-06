#include<iostream>
#include <conio.h>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


string arrayGenre [192]=
{
        "BLUES","CLASSICAL ROCK","COUNTRY","DANCE","DISCO","FUNK","GRUNGE","HIP-HOP","JAZZ","METAL","NEW AGE",
        "OLDIES","OTHER","POP","RHYTHM AND BLUES","RAP","REGGAE","ROCK","TECHNO","INDUSTRIAL","ALTERNATIVE",
        "SKA","DEATH METAL","PRANKS","SOUNDTRACK","EUROTECHNO","AMBIENT","TRIP-HOP","VOCAL","JAZZ AND FUNK",
        "FUSION","TRANCE","CLASSICAL","INSTRUMENTAL","ACID","HOUSE","GAME","SOUNDCLIP","GOSPEL","NOISE","ALTERNATIVE ROCK",
        "BASS","SOUL","PUNK","SPACE","MEDITATIVE","INSTRUMENTAL POP","INSTRUMENTAL ROCK","ETHNIC","GOTHIC","DARKWAVE",
        "TECHNO INDUSTRIAL","ELECTRONIC","POP FOLK","EURO DANCE","DREAM","SOUTHERN ROCK","COMEDY","CULT","GANGSTA","TOP 40",
        "CHRISTIAN RAP","POP/FUNK","JUNGLE","NATIVE US","CABARET","NEW WAVE","PSYCHEDLIC","RAVE","SHOW TUNES","LO-FI","TRIBAL",
        "ACID PUNK","ACID JAZZ","POLKA","RETRO","MUSICAL","ROCK 'N' ROLL","HARD ROCK","FOLK","FOLK ROCK","NATIONAL FOLK","SWING",
        "FAST FUSION","BEBOP","LATIN","REVIVAL","CELTIC","BLUE GRASS","AVANTGARDE","GOTHIC ROCK","PROGRESSIVE ROCK",
        "PSYCHEDELIC ROCK","SYMPHONIC ROCK","SLOW ROCK","BIG BAND","CHORUS","EASY LISTENING","ACOUSTIC","HUMOUR","SPEECH",
        "CHANSON","OPERA","CHAMBER MUSIC","SONATA","SYMPHONY","BOOTY BASS","PRIMUS","PORN GROOVE","SATIRE",
        "SLOW JAM","CLUB","TANGO","SAMBA","FOLKLORE","BALLAD","POWER BALLAD","RHYTHMIC SOUL","FREESTYLE","DUET","PUNK ROCK",
        "DRUM SOLO","ACAPELLA","EURO HOUSE","DANCE HALL","GOA","DRUM & BASS","CLUB HOUSE","HARDCORE TECHNO","TERROR","INDIE",
        "BRITPOP","NEGERPUNK","POLSKPUNK","BEAT","CHRISTIAN GANGSTA RAP","HEAVY METAL","BLACK METAL","CROSSOVER",
        "CONTEMPORARY CHRISTIAN","CHRISTIAN ROCK","MERENGUE","SALSA","THRASH METAL","ANIME","JPOP","SYNTHPOP","ABSTACT",
        "ART ROCK","BAROQUE","BHANGRA","BIG BEAT","BREAKBEAT","CHILLOUT","DOWNTEMPO","DUB","EBM","ECLECTRIC","ELECTRO",
        "ELECTRODASH","EMO","EXPERIMENTAL","GARBAGE","GLOBAL","IDM","ILLBIENT","INDUSTRO GOTH","JAM BAND","KAUTROCK","LEFTFIELD",
        "LOUNGE","MATH ROCK","NEW ROMANTIC","NU BREAKZ","POST PUNK","POST ROCK","PSYTRANCE","SPACE ROCK","TROP ROCK",
        "WORLD MUSIC","NEO CLASSICAL","AUDIOBOOK","AUDIO THEATRE","NEUE DEUTSCHE WELLE","PODCAST","INDIE ROCK","G-FUNK",
        "DUBSTEP","GARAGE ROCK","PSYBIENT"
};

struct info{
   char tag[4];
   char title[31];
   char artist[31];
   char album[31];
   char year[5];
   char comment[31];
   char zero, track, genre;

}mp3Info;

void showAndManageID3v1(char *ss)
{
    printf("ID3v1 Manager\n");
    char fileName[100];
    strcpy(fileName, ss);
    FILE *fp, *out = stdout,*fp1,*fp2;
   // printf("Enter File Name: ");
    //scanf("%s", fileName);
    fp = fopen(fileName, "rb");
    fp1=fopen(fileName,"rb+");

    int pos;

    char ch;
    int size = 0;

    //fp = fopen("Bon Jovi - Bon Jovi - It`s My Life [mp3clan].mp3", "rb");
    //fp1 = fopen("Bon Jovi - Bon Jovi - It`s My Life [mp3clan].mp3", "rb+");

    if (fp == NULL or fp1 == NULL)
    {
        printf("Failed to open file\n ");
    }
    else
    {
        printf("File has been successfully opened\n");
    }


    fseek(fp, -128, SEEK_END);
    fseek(fp1, -128, SEEK_END);


    int cnt = 0, i;
    int z;
    int j = 0;
    for(i = 0; i < 3; i++)
    {
        ch = fgetc(fp);
        z = (int)ch;
        fputc(z, fp1);

        mp3Info.tag[i] = ch;
    }
    mp3Info.tag[i] = '\0';
    printf("Tag: %s\n", mp3Info.tag);

    for(i = 0; i < 30; i++)
    {
        ch = fgetc(fp);
        mp3Info.title[i] = ch;
    }

    mp3Info.title[i] = '\0';
    printf("Title: %s\n", mp3Info.title);

//    printf("Do you want to change the title? Press y for yes and any other key for no\n");

    char falseCharacter;
  //  scanf("%c%c", &ch, &falseCharacter);



    for(i = 0; i < 30; i++)
    {
        ch = fgetc(fp);
        mp3Info.artist[i] = ch;
    }

    mp3Info.artist[i] = '\0';
    printf("Artist: %s\n", mp3Info.artist);


    for(i = 0; i < 30; i++)
    {
        ch = fgetc(fp);
        mp3Info.album[i] = ch;
    }

    mp3Info.album[i] = '\0';
    printf("Album: %s\n", mp3Info.album);

    for(i = 0; i < 4; i++)
    {
        ch = fgetc(fp);
        mp3Info.year[i] = ch;
    }

    mp3Info.year[i] = '\0';
    printf("Year: %s\n", mp3Info.year);

    for(i = 0; i < 28; i++)
    {
        ch = fgetc(fp);
        mp3Info.comment[i] = ch;

    }

    mp3Info.comment[i] = '\0';
    printf("Comment: %s\n", mp3Info.comment);



    ch = fgetc(fp);
    mp3Info.zero = ch;
    printf("Zero: %d\n", (int)mp3Info.zero);

    if(mp3Info.zero == 1)
    {
       printf("Zero track not listed\n");
    }

    else
    {
       printf("Zero track is stored\n");
    }

    ch = fgetc(fp);
    mp3Info.track = ch;
    printf("Track: %d\n", (int)mp3Info.track);

    ch = fgetc(fp);
    mp3Info.genre = ch;
    printf("Genre: %d ", (int)mp3Info.genre);
    int genreIndex=(int)mp3Info.genre;
    for(int i=0;i<192;i++){
    if (i==genreIndex)
        cout << arrayGenre[i] << endl;

    }

}

int main(int argc, char *argv[])
{
  int optionNumber;

        showAndManageID3v1(argv[1]);


    return 0;
}

