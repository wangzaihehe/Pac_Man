#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
int playGame(const char* filename) {
    int kuan,gao;
    FILE * fp;
    char kong[60];
    char left[]="a";
    char right[]="d";
    char up[]="w";
    char down[]="s" ;
    char quit[]="q" ;
    char player[]="A";
    char xiongqiplayer[]="B";
    int startx,starty;
  //  int numE=0;
    int numI=0;
   // int numP=0;
    char panduan[]="C";
    int x,y;
    char input[100];
    int score=0;
    int supersteps=-1;
    int superstatus=-1;
    fp = fopen(filename,"r");
    fscanf(fp,"%d %d",&gao,&kuan);
    char *graph[gao+2][kuan+2];
    for(int v=0;v<gao+2;v++){
        for(int u=0;u<kuan+2;u++) {
            graph[v][u]="*";
        }
    }
    for(int o=1;o<=gao;o++){
  for(int i=1;i<=kuan;i++){
         graph[o][i]=" ";          
  }
   }

    if(fgets(kong,60,fp)!=NULL) {
        fgets(kong,60,fp);
        if(strcmp(kong,"\n")!=0){
           // puts(kong);
            left[0]=kong[0];
            right[0]=kong[2];
            up[0]=kong[4];
            down[0]=kong[6];
            quit[0]=kong[8];
        }   
    }
    fscanf(fp,"%s %s %d %d",player,xiongqiplayer,&startx,&starty);
    int xx=startx+1;
    int yy=starty+1;
    
    
    while(!feof(fp) ) {

        fscanf(fp,"%s %d %d",panduan,&x,&y);
        if(strcmp(panduan,"B")==0){
            for(int bchang=0;bchang<4;bchang++){

                for(int bkuan=0;bkuan<6;bkuan++) {
                                            if(bchang==2&&bkuan==2) {
                            graph[x+1+bchang][y+1+bkuan]="&";
                            continue;
                                            }
                                                 if(bchang == 2 && bkuan == 3) {
                         graph[x+1+bchang][y+1+bkuan]="&";
                         continue;
                     }
            
                        if(bchang==3 && bkuan == 2) {
                            graph[x+1+bchang][y+1+bkuan]="&";
                            continue;
                }
                     if(bchang == 3 && bkuan==3) {
                         graph[x+1+bchang][y+1+bkuan]="&";
                         continue;
                     }
                   graph[x+1+bchang][y+1+bkuan]="-";
                   
                }
            }
            

        }

        if(strcmp(panduan,"I")==0){
            //printf("item +1\n");
            numI+=1;
            graph[x+1][y+1]="$";

        }

        if(strcmp(panduan,"E")==0){
            graph[x+1][y+1]="X";

        }
        if(strcmp(panduan,"P")==0){
            graph[x+1][y+1]="*";

        }
        strcpy(panduan,"C");
    }
    graph[xx][yy]=player;


    fclose(fp);

    while( 1>0 ) {
                printf("Score: %d",score);
        printf("\nItems remaining: %d\n",numI);
        for(int z=0;z<gao+2;z++){
        for(int b=0;b<kuan+2;b++){
            printf("%s",graph[z][b]);
        }
        printf("\n");
    }
        printf("Enter input: ");
        scanf("%s",input);
        if((strcmp(input,up)!=0)&&(strcmp(input,down)!=0)&&(strcmp(input,left)!=0)&&(strcmp(input,right)!=0)&&(strcmp(input,quit)!=0)){
            printf("Invalid input.\n");
            fflush(stdin);
            continue;
        }
        if(strcmp(input,quit)==0){
            printf("You have quit.\n");
            printf("Final score: %d",score);
            break;
        }
      
      if(supersteps-1==0){
          graph[xx][yy]=player;
          superstatus=0;
      }
      
        if(numI==0){
            break;
        }
        if(strcmp(input,left)==0){

            if((yy-1)==0){
               // printf("limit~!\n");
                supersteps-=1;
                continue;
            }
            if(superstatus==1){
            if((yy-2)==-1){
               // printf("limit~!\n");
                supersteps-=1;
                continue;
            }
                if(strcmp(graph[xx][yy-1]," ")==0){
            graph[xx][yy]=" ";
            //printf("LEFT~!\n");
            graph[xx][yy-1]=xiongqiplayer;
            yy=yy-1;
            supersteps-=1;
            continue;
        

                }
                if(strcmp(graph[xx][yy-1],"$")==0){
                    numI-=1;
                    score+=1;
                }
            if(strcmp(graph[xx][yy-1],"-")==0){
              //  printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            if(strcmp(graph[xx][yy-1],"X")==0){
                score+=1;

            }
                graph[xx][yy]=" ";
                graph[xx][yy-1]=xiongqiplayer;
                yy-=1;
                supersteps -=1;
                continue;
            }

            if(strcmp(graph[xx][yy-1],"-")==0){
              //  printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            if(strcmp(graph[xx][yy-1],"X")==0){
                if(superstatus==1){
                  //  printf("GOOOOOOT u!!!!!\n");
                graph[xx][yy]=" ";
                graph[xx][yy-1]=player;
                yy-=1;
                score+=1;
                supersteps-=1;
                continue;
                }else{
                    printf("Score: %d",score);
                     printf("\nItems remaining: %d\n",numI);
                graph[xx][yy]=" ";
                graph[xx][yy-1]="@";
                for(int zzz=0;zzz<gao+2;zzz++){
                for(int bbb=0;bbb<kuan+2;bbb++){
                printf("%s",graph[zzz][bbb]);
                }
                 printf("\n");
            }
                }
                printf("You have died.\n");
                printf("Final score: %d",score);
                break;
            }
            
            if(strcmp(graph[xx][yy-1],"$")==0){
                
                graph[xx][yy]=" ";
                graph[xx][yy-1]=player;
                numI=numI-1;
                score+=1;
                supersteps-=1;
            }
            if(strcmp(graph[xx][yy-1],"*")==0&&(yy-2)!=-1){
                
                graph[xx][yy]=" ";
                graph[xx][yy-1]=xiongqiplayer;
                yy-=1;
                superstatus =1;
                supersteps =7;
            }
            graph[xx][yy]=" ";
          //  printf("LEFT~!\n");
            graph[xx][yy-1]=player;
            yy=yy-1;
            supersteps-=1;
        }
        if(strcmp(input,right)==0){

            if((yy+1)==kuan+1){
              //  printf("limit~!\n");
                supersteps-=1;
                continue;
            }
            if(superstatus==1){
                if(strcmp(graph[xx][yy+1],"$")==0){
                    numI-=1;
                    score+=1;
                }
            if(strcmp(graph[xx][yy+1],"-")==0){
               // printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            if(strcmp(graph[xx][yy+1],"X")==0){
                score+=1;
            }
            graph[xx][yy]=" ";
          //  printf("RIGHT~!\n");
            graph[xx][yy+1]=xiongqiplayer;
            yy+=1;
            supersteps-=1;
            continue;
            
            }
            if(strcmp(graph[xx][yy+1],"-")==0){
               // printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            
            if(strcmp(graph[xx][yy+1],"X")==0){
                if(superstatus==1){
                    printf("GOOOOOOT u!!!!!\n");
                graph[xx][yy]=" ";
                graph[xx][yy+1]=player;
                yy+=1;
                printf("JIAFEN JIAFEN!!\n");
                score+=1;
                supersteps-=1;
                continue;
                }else{
                    printf("Score: %d",score);
                     printf("\nItems remaining: %d\n",numI);
                graph[xx][yy]=" ";
                graph[xx][yy+1]="@";
                for(int zzz=0;zzz<gao+2;zzz++){
                for(int bbb=0;bbb<kuan+2;bbb++){
                printf("%s",graph[zzz][bbb]);
                }
                 printf("\n");
            }
                }
                printf("You have died.\n");
                printf("Final score: %d",score);
                break;
            }
            if(strcmp(graph[xx][yy+1],"$")==0){
                graph[xx][yy]=" ";
                graph[xx][yy+1]=player;
                numI=numI-1;
                score+=1;
                supersteps-=1;
                
            }
            if(strcmp(graph[xx][yy+1],"*")==0&&(yy+1)!=kuan){
                graph[xx][yy]=" ";
                graph[xx][yy+1]=xiongqiplayer;
                yy+=1;
                superstatus = 1;
                supersteps =7;
                continue;
            }
            graph[xx][yy]=" ";
          //  printf("RIGHT~!\n");
            graph[xx][yy+1]=player;
            yy=yy+1;
            supersteps-=1;
        }
         if(strcmp(input,up)==0){
             if((xx-1)==0){
               // printf("limit~!\n");
                supersteps-=1;
                continue;      
             }
            if(superstatus==1){
                if(strcmp(graph[xx-1][yy],"$")==0){
                    numI-=1;
                    score+=1;
                }
            if(strcmp(graph[xx-1][yy],"-")==0){
               // printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            if(strcmp(graph[xx-1][yy],"X")==0){
                score+=1;
            }
            graph[xx][yy]=" ";
          //  printf("RIGHT~!\n");
            graph[xx-1][yy]=xiongqiplayer;
            xx-=1;
            supersteps-=1;
            continue;
            
            }
            if(strcmp(graph[xx-1][yy],"-")==0){
               // printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            if(strcmp(graph[xx-1][yy],"&")==0){
               // printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }

            if(strcmp(graph[xx-1][yy],"X")==0){
                if(superstatus==1){
                graph[xx][yy]=" ";
                graph[xx-1][yy]=player;
                xx-=1;
                score+=1;
                supersteps-=1;
                continue;
                }
                                    printf("Score: %d",score);
                     printf("\nItems remaining: %d\n",numI);
                graph[xx][yy]=" ";
                graph[xx-1][yy]="@";
                for(int zzz=0;zzz<gao+2;zzz++){
                for(int bbb=0;bbb<kuan+2;bbb++){
                printf("%s",graph[zzz][bbb]);
                }
                 printf("\n");
            }
                printf("You have died.\n");
                printf("Final score: %d",score);
                break;
            }
            if(strcmp(graph[xx-1][yy],"$")==0){
                graph[xx][yy]=" ";
                graph[xx-1][yy]=player;
                numI=numI-1;
                score+=1;
                supersteps-=1;
            }
            if(strcmp(graph[xx-1][yy],"*")==0&&(yy-1)!=0){
               // printf("SUPER!!\n");
                graph[xx][yy]=" ";
                graph[xx-1][yy]=xiongqiplayer;
                superstatus =1;
                supersteps =7;
            }
            graph[xx][yy]=" ";
           // printf("UP~!\n");
            graph[xx-1][yy]=player;
            xx=xx-1;
            supersteps-=1;
         }
          if(strcmp(input,down)==0){
             if((xx+1)==gao+1){
               // printf("limit~!\n");
                supersteps-=1;
                continue;      
             }
            if(superstatus==1){
                if(strcmp(graph[xx+1][yy],"$")==0){
                    numI-=1;
                    score+=1;
                }
            if(strcmp(graph[xx+1][yy],"-")==0){
              //  printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            if(strcmp(graph[xx+1][yy],"X")==0){
                score+=1;
            }
            graph[xx][yy]=" ";
          //  printf("RIGHT~!\n");
            graph[xx+1][yy]=xiongqiplayer;
            xx+=1;
            supersteps-=1;
            continue;
            
            }
            if(strcmp(graph[xx+1][yy],"-")==0){
              //  printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            if(strcmp(graph[xx+1][yy],"&")==0){
              //  printf("hit the wall!\n");
                supersteps-=1;
                continue;
            }
            if(strcmp(graph[xx+1][yy],"X")==0){
                if(superstatus==1){
                graph[xx][yy]=" ";
                graph[xx+1][yy]=player;
                xx+=1;
                score+=1;
                supersteps-=1;
                continue;
                }
                                    printf("Score: %d",score);
                     printf("\nItems remaining: %d\n",numI);
                graph[xx][yy]=" ";
                graph[xx+1][yy]="@";
                for(int zzz=0;zzz<gao+2;zzz++) {
                for(int bbb=0;bbb<kuan+2;bbb++) {
                printf("%s",graph[zzz][bbb]);
                }
                 printf("\n");
            }
                printf("You have died.\n");
                printf("Final score: %d",score);
                break;
            }
            if(strcmp(graph[xx+1][yy],"$")==0) {
                graph[xx][yy]=" ";
                graph[xx+1][yy]=player;
                numI=numI-1;
                score+=1;
                supersteps-=1;
            }
            if(strcmp(graph[xx+1][yy],"*") == 0 && (xx+1) != gao+1) {
                //printf("xiongqile !!\n");
                graph[xx][yy]=" ";
                graph[xx+1][yy]=xiongqiplayer;
                xx+=1;
                superstatus =1;
                supersteps =7;
                continue;
            }
            graph[xx][yy]=" ";
            graph[xx+1][yy]=player;
            xx=xx+1;
            supersteps-=1;
          }

      if( numI==0 ) {
         printf("Congratulations! You have won.\n");
         printf("Final score: %d",score);
          break;
      }
    }




    return 0;
}