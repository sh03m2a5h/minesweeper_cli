#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

//※(x,y)の順番にしたかったので[x][y]となっていますが逆です
//※したがってWIDTHとHEIGHTも逆です。そこだけ気を付けてください。

//WIDTHと言いながら高さ
#define WIDTH 12
//HEIGHTと言いながら幅
#define HEIGHT 12
//簡単さ加減、1にすると全部地雷、0はエラー
#define SIMPLICITY 10

int mine[WIDTH][HEIGHT],mask[WIDTH][HEIGHT];

//選択した部分を開ける関数
void open(int x,int y);

int main(){
    int x,y,key,i,j,mine_cnt=0,clear_cnt=0;
    char number[][3] = {"　","１","２","３","４","５","６","７","８"};
    int cursor_x=0,cursor_y=0;

    //乱数シードの設定
    srand(time(NULL));

    //初期化&地雷設置ループ
    for(x=0;x<HEIGHT;x++)
        for(y=0;y<WIDTH;y++){
            if(rand()%SIMPLICITY==0){
                //地雷設置
                mine[x][y] = -1;
                //地雷カウント
                mine_cnt++;
            }
            else
                mine[x][y] = 0;
            //開けてないとこは覆っときましょう
            mask[x][y]=1;
        }
    
    //地雷に隣接したとこに++しまくるループ
    for(x=0;x<HEIGHT;x++)
        for(y=0;y<WIDTH;y++)
            if(mine[x][y] == -1)
                for(i=(x==0?0:-1);i<=(x==HEIGHT-1?0:1);i++)
                    for(j=(y==0?0:-1);j<=(y==WIDTH-1?0:1);j++){
                        if((i==0&&j==0)||(mine[x+i][y+j]==-1))
                            //自分自身には加算しない&地雷にも加算しない
                            continue;
                        mine[x+i][y+j]++;
                    }

    //無限ループ
    while(1){
        //コンソール画面クリア
        system("cls");

        //画面描画
        for(x=0;x<WIDTH;x++){
            for(y=0;y<HEIGHT;y++){
                if(cursor_x==x&&cursor_y==y)
                    //選択中の場所は◎
                    printf("◎");
                else if(mask[x][y]){
                    //覆われてるとこ
                    if(mask[x][y]==-1)
                        //フラグ立ってたら△
                        printf("△");
                    else
                        //開けてないだけのとこは■
                        printf("■");
                }
                else{
                    //開いてるとき
                    printf("%s",number[mine[x][y]]);
                }
            }
            printf("\n");
        }

        //実質デバッグ用 地雷数と開封済み表示
        printf("mine_cnt = %d\n",mine_cnt);
        printf("clear_cnt = %d\n",clear_cnt);

        //キー入力されるまで待機&されたらkeyに値を入れる
        key = getch();

        //入力されたキーによって分岐
        switch (key)
        {
            case 'w':
                //wでカーソルを上に動かす
                cursor_x-=cursor_x<=0?0:1;
                break;
            case 's':
                //sでカーソルを下に動かす
                cursor_x+=cursor_x>=WIDTH-1?0:1;
                break;
            case 'a':
                //aでカーソルを左に動かす
                cursor_y-=cursor_y<=0?0:1;
                break;
            case 'd':
                //dでカーソルを右に動かす
                cursor_y+=cursor_y>=HEIGHT-1?0:1;
                break;
            case ' ':
                //スペースで開ける
                if(mask[cursor_x][cursor_y]!=-1)
                    //フラグ立って無ければ開ける
                    open(cursor_x,cursor_y);
                break;
            case 'f':
                //fでフラグを立てたり倒したり
                mask[cursor_x][cursor_y] = mask[cursor_x][cursor_y] == 0 ? 0 : mask[cursor_x][cursor_y] == 1 ? -1 : 1;
                break;
        }
        
        //空いてる数カウントループ
        for(x=0,clear_cnt=0;x<WIDTH;x++)
            for(y=0;y<HEIGHT;y++){
                if(!mask[x][y])
                    //覆われていなかったらカウントアップ
                    clear_cnt++;
            }

        //zでゲーム終了
        if(key=='z')
            break;
        else if(!mask[cursor_x][cursor_y]&&mine[cursor_x][cursor_y]==-1){
            //地雷踏んだらGAME OVER
            printf("  _____ ___    __  ___ ____  ____  _   __ ____ ___ \n");
            printf(" / ___// _ |  /  |/  // __/ / __ \\| | / // __// _ \\\n");
            printf("/ (_ // __ | / /|_/ // _/  / /_/ /| |/ // _/ / , _/\n");
            printf("\\___//_/ |_|/_/  /_//___/  \\____/ |___//___//_/|_| \n");
            break;
        }else if(WIDTH*HEIGHT-mine_cnt==clear_cnt){
            //総数-地雷数=空いてるとこの数でCLEAR
            printf("  _____ __    ____ ___    ___ \n");
            printf(" / ___// /   / __// _ |  / _ \\\n");
            printf("/ /__ / /__ / _/ / __ | / , _/\n");
            printf("\\___//____//___//_/ |_|/_/|_| \n");
            break;
        }

    }
    //キー入力待機
    system("pause");
    return 0;
}

//選択した部分を開ける関数
void open(int x,int y){
    int i,j;
    //自分自身を開ける
    mask[x][y] = 0;

    //隣接していなければ
    if(mine[x][y]==0)
        for(i=(x==0?0:-1);i<=(x==HEIGHT-1?0:1);i++)
            for(j=(y==0?0:-1);j<=(y==WIDTH-1?0:1);j++){
                if(mask[x+i][y+j]==0);
                    //自分自身はもう空いてるからスルー
                else if(mine[x+i][y+j]!=0)
                    //地雷に隣接していれば自分のみ開ける
                    mask[x+i][y+j]=0;
                else
                    //自身が地雷に隣接していなければ周りも開ける(再帰)
                    open(x+i,y+j);
            }
}