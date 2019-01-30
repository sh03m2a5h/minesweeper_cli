#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

//��(x,y)�̏��Ԃɂ����������̂�[x][y]�ƂȂ��Ă��܂����t�ł�
//������������WIDTH��HEIGHT���t�ł��B���������C��t���Ă��������B

//WIDTH�ƌ����Ȃ��獂��
#define WIDTH 12
//HEIGHT�ƌ����Ȃ��畝
#define HEIGHT 12
//�ȒP�������A1�ɂ���ƑS���n���A0�̓G���[
#define SIMPLICITY 10

int mine[WIDTH][HEIGHT],mask[WIDTH][HEIGHT];

//�I�������������J����֐�
void open(int x,int y);

int main(){
    int x,y,key,i,j,mine_cnt=0,clear_cnt=0;
    char number[][3] = {"�@","�P","�Q","�R","�S","�T","�U","�V","�W"};
    int cursor_x=0,cursor_y=0;

    //�����V�[�h�̐ݒ�
    srand(time(NULL));

    //������&�n���ݒu���[�v
    for(x=0;x<HEIGHT;x++)
        for(y=0;y<WIDTH;y++){
            if(rand()%SIMPLICITY==0){
                //�n���ݒu
                mine[x][y] = -1;
                //�n���J�E���g
                mine_cnt++;
            }
            else
                mine[x][y] = 0;
            //�J���ĂȂ��Ƃ��͕����Ƃ��܂��傤
            mask[x][y]=1;
        }
    
    //�n���ɗאڂ����Ƃ���++���܂��郋�[�v
    for(x=0;x<HEIGHT;x++)
        for(y=0;y<WIDTH;y++)
            if(mine[x][y] == -1)
                for(i=(x==0?0:-1);i<=(x==HEIGHT-1?0:1);i++)
                    for(j=(y==0?0:-1);j<=(y==WIDTH-1?0:1);j++){
                        if((i==0&&j==0)||(mine[x+i][y+j]==-1))
                            //�������g�ɂ͉��Z���Ȃ�&�n���ɂ����Z���Ȃ�
                            continue;
                        mine[x+i][y+j]++;
                    }

    //�������[�v
    while(1){
        //�R���\�[����ʃN���A
        system("cls");

        //��ʕ`��
        for(x=0;x<WIDTH;x++){
            for(y=0;y<HEIGHT;y++){
                if(cursor_x==x&&cursor_y==y)
                    //�I�𒆂̏ꏊ�́�
                    printf("��");
                else if(mask[x][y]){
                    //�����Ă�Ƃ�
                    if(mask[x][y]==-1)
                        //�t���O�����Ă��灢
                        printf("��");
                    else
                        //�J���ĂȂ������̂Ƃ��́�
                        printf("��");
                }
                else{
                    //�J���Ă�Ƃ�
                    printf("%s",number[mine[x][y]]);
                }
            }
            printf("\n");
        }

        //�����f�o�b�O�p �n�����ƊJ���ςݕ\��
        printf("mine_cnt = %d\n",mine_cnt);
        printf("clear_cnt = %d\n",clear_cnt);

        //�L�[���͂����܂őҋ@&���ꂽ��key�ɒl������
        key = getch();

        //���͂��ꂽ�L�[�ɂ���ĕ���
        switch (key)
        {
            case 'w':
                //w�ŃJ�[�\������ɓ�����
                cursor_x-=cursor_x<=0?0:1;
                break;
            case 's':
                //s�ŃJ�[�\�������ɓ�����
                cursor_x+=cursor_x>=WIDTH-1?0:1;
                break;
            case 'a':
                //a�ŃJ�[�\�������ɓ�����
                cursor_y-=cursor_y<=0?0:1;
                break;
            case 'd':
                //d�ŃJ�[�\�����E�ɓ�����
                cursor_y+=cursor_y>=HEIGHT-1?0:1;
                break;
            case ' ':
                //�X�y�[�X�ŊJ����
                if(mask[cursor_x][cursor_y]!=-1)
                    //�t���O�����Ė�����ΊJ����
                    open(cursor_x,cursor_y);
                break;
            case 'f':
                //f�Ńt���O�𗧂Ă���|������
                mask[cursor_x][cursor_y] = mask[cursor_x][cursor_y] == 0 ? 0 : mask[cursor_x][cursor_y] == 1 ? -1 : 1;
                break;
        }
        
        //�󂢂Ă鐔�J�E���g���[�v
        for(x=0,clear_cnt=0;x<WIDTH;x++)
            for(y=0;y<HEIGHT;y++){
                if(!mask[x][y])
                    //�����Ă��Ȃ�������J�E���g�A�b�v
                    clear_cnt++;
            }

        //z�ŃQ�[���I��
        if(key=='z')
            break;
        else if(!mask[cursor_x][cursor_y]&&mine[cursor_x][cursor_y]==-1){
            //�n�����񂾂�GAME OVER
            printf("  _____ ___    __  ___ ____  ____  _   __ ____ ___ \n");
            printf(" / ___// _ |  /  |/  // __/ / __ \\| | / // __// _ \\\n");
            printf("/ (_ // __ | / /|_/ // _/  / /_/ /| |/ // _/ / , _/\n");
            printf("\\___//_/ |_|/_/  /_//___/  \\____/ |___//___//_/|_| \n");
            break;
        }else if(WIDTH*HEIGHT-mine_cnt==clear_cnt){
            //����-�n����=�󂢂Ă�Ƃ��̐���CLEAR
            printf("  _____ __    ____ ___    ___ \n");
            printf(" / ___// /   / __// _ |  / _ \\\n");
            printf("/ /__ / /__ / _/ / __ | / , _/\n");
            printf("\\___//____//___//_/ |_|/_/|_| \n");
            break;
        }

    }
    //�L�[���͑ҋ@
    system("pause");
    return 0;
}

//�I�������������J����֐�
void open(int x,int y){
    int i,j;
    //�������g���J����
    mask[x][y] = 0;

    //�אڂ��Ă��Ȃ����
    if(mine[x][y]==0)
        for(i=(x==0?0:-1);i<=(x==HEIGHT-1?0:1);i++)
            for(j=(y==0?0:-1);j<=(y==WIDTH-1?0:1);j++){
                if(mask[x+i][y+j]==0);
                    //�������g�͂����󂢂Ă邩��X���[
                else if(mine[x+i][y+j]!=0)
                    //�n���ɗאڂ��Ă���Ύ����̂݊J����
                    mask[x+i][y+j]=0;
                else
                    //���g���n���ɗאڂ��Ă��Ȃ���Ύ�����J����(�ċA)
                    open(x+i,y+j);
            }
}