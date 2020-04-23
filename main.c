#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "gotoXY.h"
#include "getch.h"
#include <termio.h>
#include <stdlib.h>

void Sudoku(int difficulty); // 스도쿠 실행
void SudokuMenu(void); // 스도쿠 메뉴
void SudokuInformation(void); // 스도쿠 정보
void SudokuStatistics(void); // 스도쿠 랭킹
void SudokuResult(int difficulty); // 스도쿠 결과 화면
void NumberBaseballMenu(void); // 베이스볼 게임 메뉴
void NumberBaseballGame(int difficulty); // 베이스볼 게임
void NumberBaseballResult(int difficulty, int count); // 숫자야구 결과
void NumberBaseballStatistics(void); // 숫자야구 통계
void NumberBaseballRule(void); // 숫자야구 룰
void UpDownGame(void);
void RSPGame(void);
void UpDonwGameMenu(void);
void UpDownStatistics (void);
void RSPGameMenu(void);
void UpDownResult(int cnt);
void UpDownRule(void);
void RSPGameStatistics(void);
void RSPGameRule(void);
void RSPGameResult(int cnt);

void main(void) {
// 메인 함수 변수 설정 & 커서 상태 //
    int selection = 1;
    int roop = 1;
    int design2 = 3; // 문자열 위치
    int design1 = 8;
    int check; // getch 값 받기
    int i, j = 0;
    int MenuNumber = 5;
    char MenuName[5][30] = {
        {"1. Number Base Ball"},
        {"2. UP & DOWN"},
        {"3. Sudoku"},
        {"4. R & S & P"},
        {"5. Quit"}
    };

    system("setterm -cursor off"); // 콘솔 창에서 커서 오프
//////////////////////////////////

// 화면 그림 & 조작 //
    while (roop){ // 화면 그림
        system("clear");

        printf("%c[1;34m", 27); // 파랑
        gotoXY(design1, design2);
        printf("Mini Game");
        printf("%c[0m\n", 27);

        for (i = 0; i < MenuNumber; i++){ //하늘
            if (selection == i+1){
                printf("%c[1;33m", 27);
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s\n", MenuName[i]);
                printf("%c[0m\n", 27);
            }
            else {
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s\n", MenuName[i]);
            }
            j ++;
        }
        j =0;

    // 화면 조작 //
        while (1) {
            check = getch(); // 받아오는 용도
        // 방향키 조작 위 & 아래 //
          if (check == 27) { // 방향키 조작
             check = getch(); // 24?
                check = getch(); // 분리
             switch (check) {
             case 65:
                selection -= 1;
                if (selection < 1) selection = MenuNumber;
                break;

             case 66:
                selection += 1;
                if (selection > MenuNumber) selection = 1;
                break;
             }
             break;
          }
        /////////////////////////

        // 엔터키로 해당하는 메뉴 실행 //
            if (check == 10) {
                switch (selection){
                    case 1:
                        NumberBaseballMenu();
                        break;
                    case 2:
                        UpDonwGameMenu();
                        break;
                    case 3:
                        SudokuMenu();
                        break;
                    case 4:
                        RSPGameMenu();
                        break;
                    case 5:
                        roop = 0;
                        system("clear");
                        break;
                break;
                }
            }
        ///////////////////////////////
        }
    }
    //////////////
/////////////////////
}

void Sudoku(int difficulty){
// 스도쿠 게임 변수 //
    system("clear");

    srand(time(NULL)); // 매번 다른 시드값 생성
    int random = 0;
    random = rand()%3 + 1; // 랜던값을 1~3을 받음

    int i, j, hor = 8, ver = 5; // 초기 위치 hor : 가로 위치, ver : 세로 위치
    int hor_2 = 8, ver_2 = 5;
    int check, CursorHorizonalLocation = hor + 2, CursorVerticalLocation = ver + 1; // 그리기 용도
    int HorizonalLocation = 0, VerticalLocation = 0; // 진짜 스도쿠위에서의 좌표
    int User_Answer [9][9] = {0,};
    int Sudoku_Question[9][9] = {0, };
    int Sudoku_Answer [9][9] = {0, };

    gotoXY(hor, ver - 2);
    printf("%c[1;34m", 27);
    printf("Sudoku");
    printf("%c[0m\n", 27);

////////////////////

// 스도쿠 문제지와 답지 //
    int Sudoku_Easy1[9][9] = {
        {0,0,0,0,0,0,0,8,0},
        {6,8,0,4,7,0,0,2,0},
        {0,1,9,5,0,8,6,4,7},
        {0,6,0,9,0,0,0,0,4},
        {3,4,2,6,8,0,0,0,0},
        {1,9,0,0,5,0,8,3,0},
        {0,0,0,7,2,0,4,0,3},
        {0,0,6,0,0,5,0,1,0},
        {0,0,3,8,9,1,5,0,0}
    };

    int Sudoku_Easy1_Answer[9][9] = {
        {7,3,4,1,6,2,9,0,5},
        {0,0,5,0,0,9,3,0,1},
        {2,0,0,0,3,0,0,0,0},
        {5,0,8,0,1,3,2,7,4},
        {0,0,0,0,0,7,1,5,9},
        {0,0,7,2,0,4,0,0,6},
        {8,5,1,0,0,6,0,9,0},
        {9,2,0,3,4,0,7,0,8},
        {4,7,0,0,0,0,0,6,2}
    };

    int Sudoku_Easy2[9][9] ={
        {0,1,0,0,8,6,0,3,2},
        {0,2,0,0,0,9,6,5,0},
        {6,0,3,0,0,0,9,1,0},
        {0,0,1,5,4,3,2,0,6},
        {0,4,0,0,2,0,0,8,1},
        {2,5,0,1,0,0,0,0,0},
        {7,0,0,0,0,5,0,0,0},
        {1,0,0,0,7,0,8,6,5},
        {0,9,8,0,0,1,3,0,4}
    };

    int Sudoku_Easy2_Answer[9][9] ={
        {9,0,5,7,0,0,4,0,0},
        {4,0,7,3,1,0,0,0,8},
        {0,8,0,4,5,2,0,0,7},
        {8,7,0,0,0,0,0,9,0},
        {3,0,9,6,0,7,5,0,0},
        {0,0,6,0,9,8,7,4,3},
        {0,6,4,8,3,0,1,2,9},
        {0,3,2,9,0,4,0,0,0},
        {5,0,0,2,6,0,0,7,0}
    };

    int Sudoku_Easy3[9][9] = {
        {0,4,0,0,0,7,1,0,0},
        {5,3,0,0,9,0,0,7,0},
        {0,0,7,0,6,0,9,4,0},
        {4,0,6,0,8,0,7,5,1},
        {0,1,0,0,0,0,6,9,0},
        {0,5,3,0,1,0,0,0,2},
        {9,6,0,0,3,0,0,1,0},
        {3,7,0,0,5,1,0,0,0},
        {1,0,0,2,0,9,3,6,7}
    };

    int Sudoku_Easy3_Answer[9][9] = {
        {6,0,9,5,2,0,0,3,8},
        {0,0,1,8,0,4,2,0,6},
        {8,2,0,1,0,3,0,0,5},
        {0,9,0,3,0,2,0,0,0},
        {2,0,8,4,7,5,0,0,3},
        {7,0,0,9,0,6,4,8,0},
        {0,0,2,7,0,8,5,0,4},
        {0,0,4,6,0,0,8,2,9},
        {0,8,5,0,4,0,0,0,0}
    };

    int Sudoku_Hard1 [9][9] = {
        {0,0,0,8,0,0,0,5,0},
        {0,0,8,0,4,0,0,9,0},
        {5,7,3,1,0,0,0,0,4},
        {0,0,0,0,0,8,0,0,0},
        {0,1,0,4,0,0,0,6,3},
        {0,0,0,5,6,0,9,0,0},
        {0,6,9,0,0,0,0,3,1},
        {0,0,1,0,0,0,0,7,2},
        {0,0,0,6,1,0,5,0,0}
    };

    int Sudoku_Hard1_Answer [9][9] = {
        {9,4,6,0,3,2,1,0,7},
        {1,2,0,7,0,5,3,0,6},
        {0,0,0,0,9,6,2,8,0},
        {6,9,2,3,7,0,4,1,5},
        {8,0,5,0,2,9,7,0,0},
        {7,3,4,0,0,1,0,2,8},
        {4,0,0,2,5,7,8,0,0},
        {3,5,0,9,8,4,6,0,0},
        {2,8,7,0,0,3,0,4,9}
    };

    int Sudoku_Hard2 [9][9] = {
        {0,8,0,4,0,0,0,0,2},
        {0,0,9,0,0,0,0,0,4},
        {7,3,0,0,0,0,0,0,8},
        {0,0,0,9,1,3,0,0,0},
        {0,4,2,6,0,0,0,0,0},
        {0,0,7,0,5,0,6,0,0},
        {0,5,0,0,0,6,3,0,9},
        {0,2,0,3,0,0,0,0,0},
        {4,0,0,0,0,1,0,0,0}
    };

    int Sudoku_Hard2_Answer [9][9] = {
        {6,0,5,0,7,8,1,3,0},
        {2,1,0,5,3,8,7,6,0},
        {0,0,4,1,6,2,5,9,0},
        {5,6,8,0,0,0,4,2,7},
        {3,0,0,0,8,7,9,1,5},
        {1,9,0,2,0,4,0,8,3},
        {8,0,1,7,2,0,0,4,0},
        {9,0,6,0,4,5,8,7,1},
        {0,7,3,8,9,0,2,5,6}
    };

    int Sudoku_Hard3 [9][9] = {
        {0,0,0,0,0,0,0,7,3},
        {0,8,0,6,0,0,5,0,0},
        {0,1,0,0,0,7,0,0,6},
        {1,0,0,0,4,0,6,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,2,0,5,0,0,9,0,0},
        {3,0,0,7,0,0,0,0,0},
        {4,0,0,0,0,5,3,9,0},
        {9,0,0,2,0,0,1,0,0}
    };

    int Sudoku_Hard3_Answer [9][9] = {
        {6,9,5,4,1,8,2,0,0},
        {7,0,4,0,2,3,0,1,9},
        {2,0,3,9,5,0,8,4,0},
        {0,3,7,8,0,9,0,5,2},
        {5,4,9,3,6,2,7,8,1},
        {8,0,6,0,7,1,0,3,4},
        {0,5,1,0,9,6,4,2,8},
        {0,6,2,1,8,0,0,0,7},
        {0,7,8,0,3,4,0,6,5}
    };

    int test [9][9] = {
        {0,1,2,3,4,5,6,7,8},
        {0,1,2,3,4,5,6,7,8},
        {0,1,2,3,4,5,6,7,8},
        {0,1,2,3,4,5,6,7,8},
        {0,1,2,3,4,5,6,7,8},
        {0,1,2,3,4,5,6,7,8},
        {0,1,2,3,4,5,6,7,8},
        {0,1,2,3,4,5,6,7,8},
        {0,1,2,3,4,5,6,7,8}
    };

    int test_answer [9][9] = {
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0}
    };
////////////////////////

// 스도쿠 문제랑 정답 복사 //

    if (difficulty == 1){
        switch (random) {
            case 1:
                for (i = 0; i < 9; i++){
                    for (j = 0; j<9; j++){
                        Sudoku_Question[i][j] = Sudoku_Easy1[i][j];
                        Sudoku_Answer[i][j] = Sudoku_Easy1_Answer[i][j];
                    }
                }
                break;
            case 2:
                for (i = 0; i < 9; i++){
                    for (j = 0; j<9; j++){
                        Sudoku_Question[i][j] = Sudoku_Easy2[i][j];
                        Sudoku_Answer[i][j] = Sudoku_Easy2_Answer[i][j];
                    }
                }
                break;
            case 3:
                for (i = 0; i < 9; i++){
                    for (j = 0; j<9; j++){
                        Sudoku_Question[i][j] = Sudoku_Easy3[i][j];
                        Sudoku_Answer[i][j] = Sudoku_Easy3_Answer[i][j];
                    }
                }
                break;
        }
    }

    if (difficulty == 2) {
        switch(random) {
            case 1:
                for (i = 0; i < 9; i++){
                    for (j = 0; j<9; j++){
                        Sudoku_Question[i][j] = Sudoku_Hard1[i][j];
                        Sudoku_Answer[i][j] = Sudoku_Hard1_Answer[i][j];
                    }
                }
                break;

            case 2:
                for (i = 0; i < 9; i++){
                    for (j = 0; j<9; j++){
                        Sudoku_Question[i][j] = Sudoku_Hard2[i][j];
                        Sudoku_Answer[i][j] = Sudoku_Hard2_Answer[i][j];
                    }
                }
                break;

            case 3:
                for (i = 0; i < 9; i++){
                    for (j = 0; j<9; j++){
                        Sudoku_Question[i][j] = Sudoku_Hard3[i][j];
                        Sudoku_Answer[i][j] = Sudoku_Hard3_Answer[i][j];
                    }
                }
                break;
        }
    }

    /*for (i = 0; i < 9; i++){ // 테스트
        for (j = 0; j<9; j++){
                Sudoku_Question[i][j] = test[i][j];
                Sudoku_Answer[i][j] = test_answer[i][j];
        }
    }*/
///////////////////////////

// 스도쿠 틀 //
    char Sudoku_Design1[] = "┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓";
    char Sudoku_Design2[] = "┃   │   │   ┃   │   │   ┃   │   │   ┃";
    char Sudoku_Design3[] = "┠───┼───┼───╂───┼───┼───╂───┼───┼───┨";
    char Sudoku_Design4[] = "┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫";
    char Sudoku_Design5[] = "┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛";
//////////////

// 스도쿠 틀 그리기 //
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design1);
    for ( i=0; i<2 ; i++){
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design2); // 2
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design3); // 3
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design2); // 2
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design3); // 3
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design2); // 2
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design4); // 4
    }
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design2); // 2
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design3); // 3
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design2); // 2
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design3); // 3
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design2); // 2
    gotoXY(hor, ver), ver++;
    printf("%s", Sudoku_Design5); // 5
////////////////////

// 스도쿠 숫자 그리기 //
    hor = hor_2, ver = ver_2;
    for (i = 0; i < 9; i++){ // 행에 대한 변화
        for (j = 0; j <9; j++){ // 열에 대한 변화
            gotoXY(hor+2, ver+1);

            switch(Sudoku_Question[i][j]) {
                case 0:
                    break;
                case 1:
                    printf("%s", "1");
                    break;
                case 2:
                    printf("%s", "2");
                    break;
                case 3:
                    printf("%s", "3");
                    break;
                case 4:
                    printf("%s", "4");
                    break;
                case 5:
                    printf("%s", "5");
                    break;
                case 6:
                    printf("%s", "6");
                    break;
                case 7:
                    printf("%s", "7");
                    break;
                case 8:
                    printf("%s", "8");
                    break;
                case 9:
                    printf("%s", "9");
                    break;
            }
            hor += 4;
        }
        ver += 2;
        hor = hor_2;
    }
//////////////////////

// 스도쿠 키보드 조작 //
    hor = hor_2, ver = ver_2;
    gotoXY(CursorHorizonalLocation, CursorVerticalLocation);

    while (1) {
        check = getch(); // 27

    // 화살표 방향키로 스도쿠판 위의 커서 이동 //
      if (check == 27) { // 방향키 조작
         check = getch(); // 24
            check = getch(); // 분리

         switch (check) {
         case 65: // up
            CursorVerticalLocation -= 2;
            if (CursorVerticalLocation < ver + 1) CursorVerticalLocation = ver + 1;
                VerticalLocation -= 1;
                if (VerticalLocation < 0) VerticalLocation = 0;
            break;

         case 66: // down
            CursorVerticalLocation += 2;
            if (CursorVerticalLocation > ver + 17) CursorVerticalLocation = ver + 17;
                VerticalLocation += 1;
                if (VerticalLocation > 8) VerticalLocation = 8;
            break;

            case 67: // right
                CursorHorizonalLocation += 4;
                if (CursorHorizonalLocation > hor + 34) CursorHorizonalLocation = hor + 34;
                HorizonalLocation += 1;
                if (HorizonalLocation > 8) HorizonalLocation = 8;
                break;

            case 68: // left
                CursorHorizonalLocation -= 4;
                if (CursorHorizonalLocation < hor + 2) CursorHorizonalLocation = hor + 2;
                HorizonalLocation -= 1;
                if (HorizonalLocation < 0) HorizonalLocation = 0;
                break;
         }   
      }
    //////////////////////////////////////////

    // q키로 스도쿠 강제 종료 //
        if (check == 113){ // q를 누르면 밖으로 나감
            break;
        }
    //////////////////////////

    // 숫자 판 조작, 노란 색//
        if (Sudoku_Question [VerticalLocation] [HorizonalLocation] == 0){
            printf("%c[1;33m",27);
            if (check == 49) {
                printf("%s", "1");
                User_Answer [VerticalLocation] [HorizonalLocation] = 1;
            }
            if (check == 50) {
                printf("%s", "2");
                User_Answer [VerticalLocation][HorizonalLocation] = 2;
            }
            if (check == 51) {
                printf("%s", "3");
                User_Answer [VerticalLocation][HorizonalLocation] = 3;
            }
            if (check == 52) {
                printf("%s", "4");
                User_Answer [VerticalLocation][HorizonalLocation] = 4;
            }
            if (check == 53) {
                printf("%s", "5");
                User_Answer [VerticalLocation][HorizonalLocation] = 5;
            }
            if (check == 54) {
                printf("%s", "6");
                User_Answer [VerticalLocation][HorizonalLocation] = 6;
            }
            if (check == 55) {
                printf("%s", "7");
                User_Answer [VerticalLocation][HorizonalLocation] = 7;
            }
            if (check == 56) {
                printf("%s", "8");
                User_Answer [VerticalLocation][HorizonalLocation] = 8;
            }
            if (check == 57) {
                printf("%s", "9");
                User_Answer [VerticalLocation][HorizonalLocation] = 9;
            }
            if (check == 127) {
                printf("  ");
                User_Answer [VerticalLocation][HorizonalLocation] = 0;
            }
            printf("%c[0m\n",27);
        }
    ////////////////////////

    // 엔터키로 User_Answer 와 Sudoku_Answer를 비교 //
        if (check == 10) { // 엔터키를 누르면 answer와 easy_answer를 비교
            int ErrorCount = 0;    
        
            for (i = 0; i < 9; i++){
                for (j = 0; j < 9; j++){
                    if (User_Answer[i][j] == Sudoku_Answer[i][j]){
                        continue;
                    }
                    else{
                        ErrorCount ++;
                    }
                }
            }

            if (ErrorCount == 0){
                SudokuResult(difficulty);
                break;
            }
            else{
                gotoXY(hor + 10,ver - 2);
                printf("%c[1;31m", 27); 
                printf("Error!");
                printf("%c[0m\n", 27);
            }
        }
    ////////////////////////////////////////////////
        gotoXY(CursorHorizonalLocation, CursorVerticalLocation);
    }
//////////////////////
}

void SudokuMenu(void) {
    int roop = 1;
    int selection = 1;
    int check;
    int design1 = 8, design2 = 3, j = 0, i;
    int MenuNumber = 5;
    char MenuName[5][30] = {
        {"1. Easy"},
        {"2. Hard"},
        {"3. Statistics"},
        {"4. Information"},
        {"5. Quit"}
    };

    while (roop){ // 화면 그림
        system("clear");

        printf("%c[1;34m", 27); 
        gotoXY(design1, design2);
        printf("Sudoku");
        printf("%c[0m\n", 27);

        for (i = 0; i < MenuNumber; i++){ //하늘
            if (selection == i+1){
                printf("%c[1;33m", 27);
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s\n", MenuName[i]);
                printf("%c[0m\n", 27);
            }
            else {
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s\n", MenuName[i]);
            }
            j ++;
        }
        j =0;

    // 화면 조작 //
        while (1) {
            check = getch(); // 받아오는 용도
        // 방향키 조작 위 & 아래 //
          if (check == 27) { // 방향키 조작
             check = getch(); // 24?
                check = getch(); // 분리
             switch (check) {
             case 65:
                selection -= 1;
                if (selection < 1) selection = 5;
                break;

             case 66:
                selection += 1;
                if (selection > 5) selection = 1;
                break;
             }
             break;
          }
        /////////////////////////

        // 엔터키로 해당하는 메뉴 실행 //
            if (check == 10) {
                switch (selection){
                    case 1:
                        system("setterm -cursor on"); // 커서 위치 보임
                        Sudoku(1);
                        system("setterm -cursor off"); // 커서 숨김
                        break;
                    case 2:
                        system("setterm -cursor on"); // 커서 위치 보임
                        Sudoku(2);
                        system("setterm -cursor off"); // 커서 숨김
                        break;
                    case 3:
                        SudokuStatistics();
                        break;
                    case 4:
                        SudokuInformation();
                        break;
                    case 5:
                        roop = 0;
                        system("clear");
                        break;
                }
                break;
            }
        ///////////////////////////////
        }
    }
    //////////////
}

void SudokuInformation(void) {
    int design1 = 8, design2 = 3, stop;

    system("clear");

    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("Sudoku Rule");
    printf("%c[0m\n", 27);

    gotoXY(design1, design2 + 2);
    printf("1. 사용되는 숫자는 1~9이다.");

    gotoXY(design1, design2 + 4);
    printf("2. 각 행과 열, 그리고 3X3 상자에는 1~9의 숫자가 하나씩만 들어가야한다.");

    stop = getch();
}

void SudokuStatistics(void) {
    char temp[100];
    int col = 0; // statistics 파일 행 세는 용도
    int i;
    int design1 =8, design2 = 3, stop;

    system("clear");

    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("Sudoku Statistics");
    printf("%c[0m\n", 27);

    gotoXY(design1, design2 + 2);
    printf("Sn  Name     Difficulty");

    gotoXY(design1, design2 + 3);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━");

    FILE* fa = fopen("Sudoku Statistics.txt", "a"); // 스도쿠 읽기 오류 방지
    fclose(fa);

    FILE* fb = fopen("Sudoku Statistics.txt", "r");

    while (fgets(temp, 100, fb) != NULL) {
       col++;
   }
   fclose(fb);

    FILE* fc = fopen("Sudoku Statistics.txt", "r");
    for (i = 0; i<(col/2); i++) { // 정보를 2개 단위로 받아옴
        gotoXY(design1, design2 + 4);
        printf("%d", i+1);

        fgets(temp, 100, fc);
        gotoXY(design1 + 4, design2 + 4);
        printf("%s", temp);

        fgets(temp, 100, fc);
        gotoXY(design1 + 13, design2 +4);
        printf("%s", temp);
        design2 ++;
    }
    stop = getch();
}

void SudokuResult(int difficulty){
    system("clear");

    int temp;
    char name[10];
    char difficulty_name1[] = "Easy\n";
    char difficulty_name2[] = "Hard\n";
    char difficulty_name[10];
    int design1 = 8, design2 = 3;

    if (difficulty == 1) {
        strcpy(difficulty_name, difficulty_name1);
    }
    if (difficulty == 2) {
        strcpy(difficulty_name, difficulty_name2);
    }

    gotoXY(design1,design2);
    printf("%c[1;33m", 27);
    printf("Clear!");
    printf("%c[0m\n", 27);

    gotoXY(design1,design2 + 2);
    printf("Name : ");
    scanf("%s", &name);

    gotoXY(design1, design2 + 3);
    printf("Difficulty : %s", difficulty_name);

    FILE* fd = fopen("Sudoku Statistics.txt", "a");
    strcat(name, "\n");
    fputs(name, fd);

    fputs(difficulty_name, fd);

    fclose(fd);

    temp = getch();
    temp = getch();
}

void NumberBaseballMenu(void) {
    int roop = 1;
    int selection = 1;
    int check, j = 0;
    int design1 = 8, design2 = 3;
    int MenuNumber = 6, i;
    char MenuName[6][20] ={
        {"1. Easy - 3Number"},
        {"2. Nomal - 4Number"},
        {"3. Hard - 5Number"},
        {"4. Statistics"},
        {"5. Information"},
        {"6. Quit"}
    };

    while (roop){ // 화면 그림
        system("clear");

        gotoXY(design1, design2);
        printf("%c[1;34m", 27);
        printf("Number Baseball");
        printf("%c[0m\n", 27);

        for (i = 0; i < MenuNumber; i++){
            if (selection == i+1){
                printf("%c[1;33m", 27);
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s", MenuName[i]);
                printf("%c[0m\n", 27);
            }
            else {
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s", MenuName[i]);
            }
            j++;
        }
        
        j = 0;

    // 화면 조작 //
        while (1) {
            check = getch(); // 받아오는 용도
        // 방향키 조작 위 & 아래 //
          if (check == 27) { // 방향키 조작
             check = getch(); // 24?
                check = getch(); // 분리
             switch (check) {
             case 65:
                selection -= 1;
                if (selection < 1) selection = MenuNumber;
                break;

             case 66:
                selection += 1;
                if (selection > MenuNumber) selection = 1;
                break;
             }
             break;
          }
        /////////////////////////

        // 엔터키로 해당하는 메뉴 실행 //
            if (check == 10) {
                switch (selection){
                    case 1:
                        NumberBaseballGame(selection);
                        break;
                    case 2:
                        NumberBaseballGame(selection);
                        break;
                    case 3:
                        NumberBaseballGame(selection);
                        break;
                    case 4:
                        NumberBaseballStatistics();
                        break;
                    case 5:
                        NumberBaseballRule();
                        break;
                    case 6:
                        roop = 0;
                        system("clear");
                        break;
                }
                break;
            }
        ///////////////////////////////
        }
    }
    //////////////
}

void NumberBaseballGame(int difficulty) {
    int random1, random2, random3, random4, random5, roop = 1, check, stop;
    int X_location = 8, Y_location = 3, StrikeCount = 0, BallCount = 0, QuestionCount = 0;
    char RandomNumber1[10], RandomNumber2[5], RandomNumber3[6], buffer[10], Answer[10];
    system("setterm -cursor on");

// 난이도에 따른 랜덤 값 생성
    srand(time(NULL)); // 매번 다른 시드값 생성

    if (difficulty == 1) {
        random1 = rand()%10; // 첫번째 랜덤 값
        random2 = rand()%10; // 두번째 랜덤 값
        while (random1 == random2) { // 만약 첫번째와 두번째가 같다면 계속 실행
            random2 = rand()%10;
        }
        random3 = rand()%10; // 세번째 랜덤 값
        while (random1 == random3 || random2 == random3){
            random3 = rand()%10;
        }
        sprintf(buffer, "%d", random1);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random2);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random3);
        strcat(RandomNumber1, buffer);
    }

    if (difficulty == 2) {
        random1 = rand()%10; // 첫번째 랜덤 값
        random2 = rand()%10; // 두번째 랜덤 값
        while (random1 == random2) { // 만약 첫번째와 두번째가 같다면 계속 실행
            random2 = rand()%10;
        }
        random3 = rand()%10; // 세번째 랜덤 값
        while (random1 == random3 || random2 == random3){
            random3 = rand()%10;
        }
        random4 = rand()%10; // 네번째 랜덤 값
        while (random1 == random4 || random2 == random4 || random3 == random4){
            random4 = rand()%10;
        }
        sprintf(buffer, "%d", random1);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random2);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random3);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random4);
        strcat(RandomNumber1, buffer);

    }

    if (difficulty == 3) {
        random1 = rand()%10; // 첫번째 랜덤 값
        random2 = rand()%10; // 두번째 랜덤 값
        while (random1 == random2) { // 만약 첫번째와 두번째가 같다면 계속 실행
            random2 = rand()%10;
        }
        random3 = rand()%10; // 세번째 랜덤 값
        while (random1 == random3 || random2 == random3){
            random3 = rand()%10;
        }
        random4 = rand()%10; // 네번째 랜덤 값
        while (random1 == random4 || random2 == random4 || random3 == random4){
            random4 = rand()%10;
        }
        random5 = rand()%10; // 다섯번째 랜덤 값
        while (random1 == random5 || random2 == random5 || random3 == random5 || random4 == random5){
            random5 = rand()%10;
        }

        sprintf(buffer, "%d", random1);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random2);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random3);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random4);
        strcat(RandomNumber1, buffer);
        sprintf(buffer, "%d", random5);
        strcat(RandomNumber1, buffer);
    }

    system("clear");

// 숫자야구 질문 반복 //

    gotoXY(X_location, Y_location);
    printf("%c[1;34m", 27); // 파랑
    printf("Number Baseball");
    printf("%c[0m\n", 27);
    Y_location += 2;

    while (roop) {

        gotoXY(X_location, Y_location);
        printf("Number : ");
        scanf("%s", Answer);
        QuestionCount++;

        for (int i = 0; i < difficulty + 2; i++){
            if (Answer[i] == RandomNumber1[i]){
                StrikeCount ++;
            }
            else{
                for(int j = 0; j < difficulty + 2; j++){
                    if (Answer[i] == RandomNumber1[j]){
                        BallCount++;
                    }
                }
            }
        }

        if (strlen(Answer) == difficulty + 2){

            if (StrikeCount == difficulty + 2){
                gotoXY(X_location, Y_location + 1);
                system("setterm -cursor off");
                roop = 0;
                NumberBaseballResult(difficulty, QuestionCount);
            }
            else if(StrikeCount == 0 && BallCount == 0){
                gotoXY(X_location, Y_location + 1);
                printf("%c[1;31m", 27); 
                printf("OUT!");
                printf("%c[0m\n", 27);
            }
            else{
                gotoXY(X_location, Y_location + 1);
                printf("%c[1;33m", 27);
                printf("Strike : %d ", StrikeCount);
                printf("%c[1;36m", 27);
                printf("Ball : %d", BallCount);
                printf("%c[0m\n", 27);
            }
        }
        else{
            gotoXY(X_location, Y_location + 1); // 에러는 빨강
            printf("%c[1;31m", 27); 
            printf("Error");
            printf("%c[0m\n", 27);
        }

        StrikeCount = 0, BallCount = 0, Y_location += 3;
    }
/////////////////////////
}

void NumberBaseballResult(int difficulty, int count){
    int design1 =8, design2 = 3, stop;
    char Difficulty1[] = "Easy\n",Difficulty2[] = "Nomal\n", Difficulty3[] = "Hard\n", name[100], DifficultyName[10];

    if (difficulty == 1) strcpy(DifficultyName, Difficulty1);
    if (difficulty == 2) strcpy(DifficultyName, Difficulty2);
    if (difficulty == 3) strcpy(DifficultyName, Difficulty3);

    system("clear");

    gotoXY(design1, design2), design2 += 2;
    printf("%c[1;33m", 27);
    printf("Clear!");
    printf("%c[0m\n", 27);
    gotoXY(design1, design2);
    printf("Name : ");
    scanf("%s", name);

    gotoXY(design1, design2 + 1);
    printf("Difficulty : %s", DifficultyName);

    gotoXY(design1, design2 + 2);
    printf("Count : %d", count);

    FILE* fd = fopen("NumberBaseballStatistics.txt", "a");
    strcat(name, "\n");
    fputs(name, fd);

    fputs(DifficultyName, fd);

    char buffer[34];
    sprintf(buffer, "%d", count);
    strcat(buffer, "\n");
    fputs(buffer, fd);

    fclose(fd);

    stop = getch();
    stop = getch();
}

void NumberBaseballStatistics(void) {
    int design1 =8, design2 = 3, stop;
    char temp[100];
    int col = 0; // statistics 파일 행 세는 용도
    int i;

    system("clear");

    FILE* fa = fopen("NumberBaseballStatistics.txt", "a"); // 읽기 오류 방지
    fclose(fa);

    FILE* fb = fopen("NumberBaseballStatistics.txt", "r");

    while (fgets(temp, 100, fb) != NULL) {
       col++;
   }
   fclose(fb);
    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("Number Baseball Statistics");
    printf("%c[0m\n", 27);

    gotoXY(design1, design2 + 2);
    printf("Sn  Name     Difficulty     Count");

    gotoXY(design1, design2 + 3);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");

    FILE* fc = fopen("NumberBaseballStatistics.txt", "r");
    for (i = 0; i<(col/3); i++) { // 정보를 3개 단위로 받아옴
        gotoXY(design1, design2 + 4);
        printf("%d", i+1);

        fgets(temp, 100, fc);
        gotoXY(design1 + 4, design2 + 4);
        printf("%s", temp);

        fgets(temp, 100, fc);
        gotoXY(design1 + 13, design2 +4);
        printf("%s", temp);

        fgets(temp, 100, fc);
        gotoXY(design1 + 28, design2 + 4);
        printf("%s", temp);
        design2 ++;
    }
    stop = getch();
}

void NumberBaseballRule(void) {
    int design1 = 8, design2 = 3, stop;

    system("clear");

    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("Number Baseball Rule");
    printf("%c[0m\n", 27);

    gotoXY(design1, design2 + 2);
    printf("1. 사용되는 숫자는 0~9, 숫자는 중복되지 않는다.");

    gotoXY(design1, design2 + 4);
    printf("2. 위치가 다른 숫자를 맞췄을때는 Ball, 위치와 숫자가 일치할때는 Strike.");

    gotoXY(design1, design2 + 6);
    printf("3. 만약 모든 숫자가 틀릴경우 Out");

    gotoXY(design1, design2 + 8);
    printf("EX) 숫자 = 1234, 입력한 숫자 1452");
    gotoXY(design1 + 4, design2 + 9);
    printf("Strike : 1, Ball : 2");
    stop = getch();
}

void UpDownGame(void){
    int ai; // 랜덤숫자   
    int user; // 유저의 입력 숫 자  
    int count=0; // 카운트 용
    int stop;
    int design1 = 8, design2 = 3;

    system("clear");

    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("UP & DOWN");
    printf("%c[0m\n", 27);
   
    srand(time(NULL)); // 랜덤숫자 갱신 
    ai = rand() % 50 + 1; // ai의 숫자를 1~50으로 제한함 
   
    while(1){
        gotoXY(design1, design2 + 2);
        printf("1~50 사이의 숫자를 입력하여 주세요 : ");
        scanf("%d", &user);
        count+=1;
      
        if(user<1 || user>50){
            gotoXY(design1, design2 + 3);
            printf("%c[1;31m", 27);
            printf("숫자의 범위가 일치하지 않습니다");
            printf("%c[0m\n", 27);
        } 
        else if (user < ai){
            if(user<ai){
                gotoXY(design1, design2 + 3);
                printf("%c[1;33m", 27); 
                printf("UP!!");
                printf("%c[0m\n", 27);
            }
        }
        else if(user>ai){
            gotoXY(design1, design2 + 3);
            printf("%c[1;33m", 27); 
            printf("Down!!");
            printf("%c[0m\n", 27);
        }
        else{
            break;
        }
        design2 += 3;
    }
    UpDownResult(count);
}

void RSPGame(void) {
    int com;
    int user;
    char name[100];
    char s;
    int b=1;
    int a=1;  // 반복문용 a
    int count=0; // 연승 카운트
    int stop;
    int design1 = 8, design2 = 3;

    system("clear");
    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("R & P S");
    printf("%c[0m\n", 27);

    while(a=1){
        srand(time(NULL)); // 가위바위보 갱신 
        com = rand() % 3; // 0 = 주먹, 1 = 가위, 2 = 보

        gotoXY(design1, design2 + 2);
        printf("0,1,2 중 하나를 입력하여 주십시오(0 = 주먹, 1 = 가위, 2 = 보) : ");
        scanf("%d", &user);
        

        if(user>2){
            gotoXY(design1, design2 + 3);
            printf("잘못된 숫자를 입력하셨습니다 다시입력하여 주십시오.");
        }
        else if(com==0){
            if(user==0){
                gotoXY(design1, design2 + 3);
                printf("%c[1;36m", 27);
                printf("비겼습니다!\n");
                printf("%c[0m\n", 27);
            }
            else if(user==1){
                break;
            }
            else{
                gotoXY(design1, design2 + 3);
                printf("%c[1;33m", 27);
                printf("승리하였습니다!!\n");
                printf("%c[0m\n", 27);
                count+=1;
            }
        }

       else if(com==1){
            if(user==0){
                gotoXY(design1, design2 + 3);
                printf("%c[1;33m", 27);
                printf("승리하였습니다!!\n");
                printf("%c[0m\n", 27);
                count+=1;
            }
            else if(user==1){
                gotoXY(design1, design2 + 3);
                printf("%c[1;36m", 27);
                printf("비겼습니다!\n");
                printf("%c[0m\n", 27);
            }
            else{
                break;
            }
        }

        else{
            if(user==0){
                break;
            }
            else if(user==1){
                gotoXY(design1, design2 + 3);
                printf("%c[1;33m", 27);
                printf("승리하였습니다!!\n");
                printf("%c[0m\n", 27);
                count+=1;
            }
            else{
                gotoXY(design1, design2 + 3);
                printf("%c[1;36m", 27);
                printf("비겼습니다!\n");
                printf("%c[0m\n", 27);
            }
        }
        design2 += 3;
        sleep(1);
    }
    RSPGameResult(count);
}

void UpDonwGameMenu(void) {
    int selection = 1;
    int roop = 1;
    int design2 = 3; // 문자열 위치
    int design1 = 8;
    int check; // getch 값 받기
    int i, j = 0;
    int MenuNumber = 4;
    char MenuName[4][30] = {
        {"1. Play"},
        {"2. Statistics"},
        {"3. Information"},
        {"4. Quit"}
    };

    // 화면 그림 & 조작 //
    while (roop){ // 화면 그림
        system("clear");

        printf("%c[1;34m", 27); // 파랑
        gotoXY(design1, design2);
        printf("UP & DOWN");
        printf("%c[0m\n", 27);

        for (i = 0; i < MenuNumber; i++){ //하늘
            if (selection == i+1){
                printf("%c[1;33m", 27);
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s\n", MenuName[i]);
                printf("%c[0m\n", 27);
            }
            else {
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s\n", MenuName[i]);
            }
            j ++;
        }
        j =0;

    // 화면 조작 //
        while (1) {
            check = getch(); // 받아오는 용도
        // 방향키 조작 위 & 아래 //
          if (check == 27) { // 방향키 조작
             check = getch(); // 24?
                check = getch(); // 분리
             switch (check) {
             case 65:
                selection -= 1;
                if (selection < 1) selection = MenuNumber;
                break;

             case 66:
                selection += 1;
                if (selection > MenuNumber) selection = 1;
                break;
             }
             break;
          }
        /////////////////////////

        // 엔터키로 해당하는 메뉴 실행 //
            if (check == 10) {
                switch (selection){
                    case 1:
                        UpDownGame();
                        break;
                    case 2:
                        UpDownStatistics ();
                        break;
                    case 3:
                        UpDownRule();
                        break;
                    case 4:
                        roop = 0;
                        system("clear");
                        break;
                }
                break;
            }
        ///////////////////////////////
        }
    }
    //////////////
/////////////////////
}

void UpDownStatistics (void) {
    int design1 =8, design2 = 3, stop;
    char temp[100];
    int col = 0; // statistics 파일 행 세는 용도
    int i;

    system("clear");

    FILE* fa = fopen("UpDownStatistics.txt", "a"); // 읽기 오류 방지
    fclose(fa);

    FILE* fb = fopen("UpDownStatistics.txt", "r");

    while (fgets(temp, 100, fb) != NULL) {
       col++;
   }
   fclose(fb);
    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("Up & Down Statistics");
    printf("%c[0m\n", 27);

    gotoXY(design1, design2 + 2);
    printf("Sn  Name     Count");

    gotoXY(design1, design2 + 3);
    printf("━━━━━━━━━━━━━━━━━━━");

    FILE* fc = fopen("UpDownStatistics.txt", "r");
    for (i = 0; i<(col/2); i++) { // 정보를 3개 단위로 받아옴
        gotoXY(design1, design2 + 4);
        printf("%d", i+1);

        fgets(temp, 100, fc);
        gotoXY(design1 + 4, design2 + 4);
        printf("%s", temp);

        fgets(temp, 100, fc);
        gotoXY(design1 + 13, design2 +4);
        printf("%s", temp);

        design2 ++;
    }
    stop = getch();
}

void RSPGameMenu(void) {
    int selection = 1;
    int roop = 1;
    int design2 = 3; // 문자열 위치
    int design1 = 8;
    int check; // getch 값 받기
    int i, j = 0;
    int MenuNumber = 4;
    char MenuName[4][30] = {
        {"1. Play"},
        {"2. Statistics"},
        {"3. Information"},
        {"4. Quit"}
    };

    // 화면 그림 & 조작 //
    while (roop){ // 화면 그림
        system("clear");

        printf("%c[1;34m", 27); // 파랑
        gotoXY(design1, design2);
        printf("R & S & P");
        printf("%c[0m\n", 27);

        for (i = 0; i < MenuNumber; i++){ //하늘
            if (selection == i+1){
                printf("%c[1;33m", 27);
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s\n", MenuName[i]);
                printf("%c[0m\n", 27);
            }
            else {
                gotoXY(design1, design2 + i + 2 + j);
                printf("%s\n", MenuName[i]);
            }
            j ++;
        }
        j =0;

    // 화면 조작 //
        while (1) {
            check = getch(); // 받아오는 용도
        // 방향키 조작 위 & 아래 //
          if (check == 27) { // 방향키 조작
             check = getch(); // 24?
                check = getch(); // 분리
             switch (check) {
             case 65:
                selection -= 1;
                if (selection < 1) selection = MenuNumber;
                break;

             case 66:
                selection += 1;
                if (selection > MenuNumber) selection = 1;
                break;
             }
             break;
          }
        /////////////////////////

        // 엔터키로 해당하는 메뉴 실행 //
            if (check == 10) {
                switch (selection){
                    case 1:
                        RSPGame();
                        break;
                    case 2:
                        RSPGameStatistics ();
                        break;
                    case 3:
                        RSPGameRule();
                        break;
                    case 4:
                        roop = 0;
                        system("clear");
                        break;
                break;
                }
                break;
            }
        ///////////////////////////////
        }
    }
    //////////////
/////////////////////
}

void UpDownResult(int cnt){
    int design1 =8, design2 = 3, stop;
    char name[30];

    system("clear");

    gotoXY(design1, design2), design2 += 2;
    printf("%c[1;33m", 27);
    printf("Clear!");
    printf("%c[0m\n", 27);
    gotoXY(design1, design2);
    printf("Name : ");
    scanf("%s", name);
    gotoXY(design1, design2 + 1);
    printf("Count : %d", cnt);

    FILE* fd = fopen("UpDownStatistics.txt", "a");
    strcat(name, "\n");
    fputs(name, fd);

    char buffer[34];
    sprintf(buffer, "%d", cnt);
    strcat(buffer, "\n");
    fputs(buffer, fd);

    fclose(fd);

    stop = getch();
    stop = getch();
}

void UpDownRule(void) {
    int design1 = 8, design2 = 3, stop;

    system("clear");

    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("Sudoku Rule");
    printf("%c[0m\n", 27);

    gotoXY(design1, design2 + 2);
    printf("1. 1~50의 숫자중 랜덤인 숫자를 맞추는 게임이다.");

    gotoXY(design1, design2 + 4);
    printf("2. 유저는 숫자를 말하고 UP,DOWN중 정보를 얻어가며 숫자를 유추한다.");

    stop = getch();

}

void RSPGameStatistics(void) {
    int design1 =8, design2 = 3, stop;
    char temp[100];
    int col = 0; // statistics 파일 행 세는 용도
    int i;

    system("clear");

    FILE* fa = fopen("RPSStatistics.txt", "a"); // 읽기 오류 방지
    fclose(fa);

    FILE* fb = fopen("RPSStatistics.txt", "r");

    while (fgets(temp, 100, fb) != NULL) {
       col++;
   }
   fclose(fb);
    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("R & S & P Statistics");
    printf("%c[0m\n", 27);

    gotoXY(design1, design2 + 2);
    printf("Sn  Name     Count");

    gotoXY(design1, design2 + 3);
    printf("━━━━━━━━━━━━━━━━━━━");

    FILE* fc = fopen("RPSStatistics.txt", "r");
    for (i = 0; i<(col/2); i++) { // 정보를 3개 단위로 받아옴
        gotoXY(design1, design2 + 4);
        printf("%d", i+1);

        fgets(temp, 100, fc);
        gotoXY(design1 + 4, design2 + 4);
        printf("%s", temp);

        fgets(temp, 100, fc);
        gotoXY(design1 + 13, design2 +4);
        printf("%s", temp);

        design2 ++;
    }
    stop = getch();

}

void RSPGameRule(void) {
        int design1 = 8, design2 = 3, stop;

    system("clear");

    gotoXY(design1, design2);
    printf("%c[1;34m", 27);
    printf("Sudoku Rule");
    printf("%c[0m\n", 27);

    gotoXY(design1, design2 + 2);
    printf("1. 유저는 가위바위보 중 하나를 선택하여 AI와 대결한다.");

    gotoXY(design1, design2 + 4);
    printf("2. 가위는 보를 이기고 보는 주먹을 이기며 주먹은 가위를 이긴다.");

    stop = getch();

}

void RSPGameResult(int cnt) {
    int design1 =8, design2 = 3, stop;
    char name[30];

    system("clear");

    gotoXY(design1, design2), design2 += 2;
    printf("%c[1;36m", 27);
    printf("lose..");
    printf("%c[0m\n", 27);
    gotoXY(design1, design2);
    printf("Name : ");
    scanf("%s", name);
    gotoXY(design1, design2 + 1);
    printf("Count : %d", cnt);

    FILE* fd = fopen("RPSStatistics.txt", "a");
    strcat(name, "\n");
    fputs(name, fd);

    char buffer[34];
    sprintf(buffer, "%d", cnt);
    strcat(buffer, "\n");
    fputs(buffer, fd);

    fclose(fd);

    stop = getch();
}
