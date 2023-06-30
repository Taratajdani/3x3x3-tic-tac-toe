#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

int table[3][3][3];
string user1, user2, player1, player2, s[6];
int user1wins = 0, user2wins = 0, player1wins = 0, player2wins = 0;

void print(){
    for (int i = 0; i < 3; i++){
        cout << i <<endl;
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                cout << j << " " << k;
                if (table[i][j][k] == 0){
                    cout << "|  |";
                }
                else if (table[i][j][k] == 1){
                    cout << "|R1|";
                }
                else if (table[i][j][k] == 2){
                    cout << "|R2|";
                }
                else if (table[i][j][k] == 3){
                    cout << "|R3|";
                }
                else if (table[i][j][k] == -1){
                    cout << "|B1|";
                }
                else if (table[i][j][k] == -2){
                    cout << "|B2|";
                }
                else if (table[i][j][k] == -3){
                    cout << "|B3|";
                }   
            }
            cout << endl;   
        } 
    }    
}

void play(int x, int y, int symbol){
    int i = 0;
    while (table[i][x][y] != 0){
        i++;
    }
    table[i][x][y] = symbol;            
}

int check(int cnt){
    //rows
    for (int j = 0; j < 3; j++){
        for (int k = 0; k < 3; k++){
            for (int l = 0; l < 3; l++){
                for (int i = 0; i < 3; i++){
                    if (table[j][i][0] > 0 && table[k][i][1] > 0 && table[l][i][2] > 0  ){
                        return table[j][i][0];
                    }
                    else if (table[j][i][0] < 0 && table[k][i][1] < 0 && table[l][i][2] < 0){
                        return table[j][i][0];
                    }
                }
            }    
        }    
    }

    //columns
    for (int j = 0; j < 3; j++){
        for (int i = 0; i < 3; i++){
            for (int k = 0; k < 3; k++){
                for (int l = 0; l < 3; l++){
                    if (table[j][0][i] > 0 && table[k][1][i] > 0 && table[l][2][i] > 0){
                        return table[j][0][i];
                    }
                    else if (table[j][0][i] < 0 && table[k][1][i] < 0 && table[l][2][i] < 0){
                        return table[j][0][i];
                    }   
                }   
            }     
        }
    }
    //diag
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                if (table[i][0][0] > 0 && table[j][1][1] > 0 && table[k][2][2] > 0){
                    return table[i][0][0];
                }
                else if (table[i][0][0] < 0 && table[j][1][1] < 0 && table[k][2][2] < 0){
                    return table[i][0][0];
                }
                else if (table[i][0][2] > 0 && table[j][1][1] > 0 && table[k][2][0]){
                    return table[i][0][2];
                }
                else if (table[i][0][2] < 0 && table[j][1][1] < 0 && table[k][2][0] < 0){
                    return table[i][0][2];
                }
            }   
        }
    }
    return 0;   
}
bool is_possible(int x, int y, int symbol ){// in ke har bazikon 2 mohre dare inja lahaz she.
    int count = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                if (table[i][j][k] == symbol){
                    count++;
                }   
            }    
        }   
    }
    if (count == 2){
        return false;
    }
    
    for (int i = 0; i < 2; i++){
        if (table[i][x][y] != 0){
            if (abs(symbol) <= abs(table[i][x][y])){
            return false;
            }
            else
            return true;
        }   
    }
    return true;
}

void execute(){
    int cnt = 0;
    int player = 1;
    while (check(cnt) == 0){
        print();
        int index;
        cin >> index; // {1, 2, 3}
        int symbol = player*index;
        int x, y;
        cin >> x >> y;
        if (x == -1 && y == -1 && index == -1){
            int index2, x2, y2;
            cin >> index2 >> x2 >> y2;
            int symbol2 = player*index2;
            
            for (int i = 0; i < 3; i++){
                if (table[i][x2][y2] == symbol2){
                    if (table[i+1][x2][y2] == 0){
                        table[i][x2][y2] = 0;
                        int x3, y3;
                        cin >> x3 >> y3;
                        if (is_possible(x3, y3, symbol2)){
                            play(x3, y3, symbol2);
                            cnt++;
                        if (player == 1) // switch players
                        player = -1;
                        else
                        player = 1;
                        } else{
                          cout << "try again!"<<endl;
                          continue;
                        }  
                    }
                    else
                    cout << "try again!"<<endl;
                    continue;
                }   
            }
            
        }
        else if (is_possible(x, y, symbol)){
             play(x, y, symbol);
             cnt++;
            if (player == 1) // switch players
                player = -1;
            else
                player = 1;
         } else{
            cout << "try again!"<<endl;
            continue;
            }    
    }
    print();
    if (check(cnt) > 0){
        cout << player1 << " won the game!" << endl;
        player1wins++ ;
    }
    else if (check(cnt) < 0){
        cout << player2 <<" won the game!" << endl;
        player2wins++ ;
    }   
}

int main(){

   
    cout << "user1's id : " ;
    cin >> user1 ;
    cout << "user2's id : " ;
    cin >> user2 ;

    string MyText ;
    ifstream Myfile("Data.txt") ;
    getline(Myfile,MyText);

    if(MyText[0] == 'u'){
        ifstream Myfile("Data.txt") ;
        for(int i =0;i<6;i++){
            getline(Myfile,MyText);
            s[i] = MyText ;
        }
        user1wins = stoi(s[4]) ;
        user2wins = stoi(s[5]) ;
        Myfile.close() ;
    }  
    if(user1wins == user2wins){
        player1 =user1 ;
        player2 =user2 ;
        player1wins = user1wins ;
        player2wins = user2wins ;
    }else if (user1wins > user2wins){
        player1 = user1 ;
        player2 =user2 ;
        player1wins = user1wins ;
        player2wins = user2wins ;
    }else{
        player1 =user2 ;
        player2 =user1 ;
        player1wins = user2wins ;
        player2wins = user1wins ;
    }
    execute();
    if(user1wins < user2wins){
        ofstream Myfile2("Data.txt");
        Myfile2 << "username :" <<endl;
        Myfile2 << user1  <<endl;
        Myfile2 << user2  <<endl;
        Myfile2 << "win :" <<endl;
        Myfile2 << to_string(player2wins) <<endl;
        Myfile2 << to_string(player1wins) <<endl;
        Myfile2.close();
    }else{
        ofstream Myfile2("Data.txt");
        Myfile2 << "username :" << endl;
        Myfile2 << user1  <<endl;
        Myfile2 << user2  <<endl;
        Myfile2 << "win :" <<endl;
        Myfile2 << to_string(player1wins) <<endl;
        Myfile2 << to_string(player2wins) <<endl;
        Myfile2.close() ;
    }
	return 0;
}
