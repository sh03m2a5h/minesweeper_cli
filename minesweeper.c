#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 12
#define HEIGHT 12
#define SIMPLICITY 10

void open(int mine[WIDTH][HEIGHT],int mask[WIDTH][HEIGHT],int x,int y){
    int i,j;
    mask[x][y] = 0;
    if(mine[x][y]==0)
        for(i=(x==0?0:-1);i<=(x==HEIGHT-1?0:1);i++)
            for(j=(y==0?0:-1);j<=(y==WIDTH-1?0:1);j++){
                if(mask[x+i][y+j]==0);
                else if(mine[x+i][y+j]!=0)
                    mask[x+i][y+j]=0;
                else
                    open(mine,mask,x+i,y+j);
            }
}

int main(){
    int x,y,key,i,j,mine_cnt=0,clear_cnt=0;
    int mine[WIDTH][HEIGHT],mask[WIDTH][HEIGHT];
    int cursor_x=0,cursor_y=0;

    srand(time(NULL));

    for(x=0;x<HEIGHT;x++)
        for(y=0;y<WIDTH;y++){
            if(rand()%SIMPLICITY==0){
                mine[x][y] = -1;
                mine_cnt++;
            }
            else
                mine[x][y] = 0;
            mask[x][y]=1;
        }
    
    for(x=0;x<HEIGHT;x++)
        for(y=0;y<WIDTH;y++)
            if(mine[x][y] == -1)
                for(i=(x==0?0:-1);i<=(x==HEIGHT-1?0:1);i++)
                    for(j=(y==0?0:-1);j<=(y==WIDTH-1?0:1);j++){
                        if((i==0&&j==0)||(mine[x+i][y+j]==-1))
                            continue;
                        mine[x+i][y+j]++;
                    }

    while(1){
        system("cls");
        for(x=0;x<WIDTH;x++){
            for(y=0;y<HEIGHT;y++){
                if(cursor_x==x&&cursor_y==y)
                    printf(" ◎ ");
                else if(mask[x][y]){
                    if(mask[x][y]==-1)
                        printf(" △ ");
                    else
                        printf(" ■ ");
                }
                else if(mine[x][y]==-1)
                    printf(" ▲ ");
                else{
                    if(mine[x][y]==0)
                        printf("   ");
                    else
                        printf(" %d ",mine[x][y]);
                }
            }
            printf("\n");
        }
        printf("mine_cnt = %d\n",mine_cnt);
        printf("clear_cnt = %d\n",clear_cnt);

        key = getch();
        switch (key)
        {
            case 'w':
                cursor_x--;
                break;
            case 's':
                cursor_x++;
                break;
            case 'a':
                cursor_y--;
                break;
            case 'd':
                cursor_y++;
                break;
            case ' ':
                open(mine,mask,cursor_x,cursor_y);
                break;
            case 'f':
                mask[cursor_x][cursor_y] = mask[cursor_x][cursor_y] == 0 ? 0 : mask[cursor_x][cursor_y] == 1 ? -1 : 1;
                break;
        }
        if(cursor_x<0)
            cursor_x++;
        else if(cursor_x>=WIDTH)
            cursor_x--;
        else if(cursor_y<0)
            cursor_y++;
        else if(cursor_y>=HEIGHT)
            cursor_y--;
        
        clear_cnt=0;
        for(x=0;x<WIDTH;x++)
            for(y=0;y<HEIGHT;y++){
                if(!mask[x][y])
                    clear_cnt++;
            }

        if(key=='z')
            break;
        else if(!mask[cursor_x][cursor_y]&&mine[cursor_x][cursor_y]==-1){
            printf("  _____ ___    __  ___ ____  ____  _   __ ____ ___ \n");
            printf(" / ___// _ |  /  |/  // __/ / __ \\| | / // __// _ \\\n");
            printf("/ (_ // __ | / /|_/ // _/  / /_/ /| |/ // _/ / , _/\n");
            printf("\\___//_/ |_|/_/  /_//___/  \\____/ |___//___//_/|_| \n");
            break;
        }else if(WIDTH*HEIGHT-mine_cnt==clear_cnt){
            printf("  _____ __    ____ ___    ___ \n");
            printf(" / ___// /   / __// _ |  / _ \\\n");
            printf("/ /__ / /__ / _/ / __ | / , _/\n");
            printf("\\___//____//___//_/ |_|/_/|_| \n");
            break;
        }

    }

    return 0;
}