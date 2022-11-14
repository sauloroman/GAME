#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void heading_game();
void exit_game();
void validate_move();
void show_board();
void get_position();
void apply_move();
void determine_winner();
void show_result();
void computer_move();
void choose_random_coord();

char Matriz[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

char start;
char player1[20];
char player2[20];
char computer[] = "COMPUTADORA";
int type_of_game;

int turn = 1;
bool winner = false;
int player_winner = 0;
int move = 0;
int quantityMoves = 0;
int x, y;

// It starts the application 
int main () {
	
	srand(time(NULL));
	heading_game();
	
	cout<<"Iniciar juego [S] / [N]: ";
	cin>>start;
	
	if ( start == 'S' || start == 's' ) {
		
		cout<<"\n[1] JUGAR DOS JUGADORES";
		cout<<"\n[2] JUGAR CONTRA COMPUTADORA";
		cout<<"\nDecision: ";
		cin>>type_of_game;
		
		if ( type_of_game == 1 ) {
			cout<<"\nIngrese nombre del jugador [1]: ";
			cin>>player1;
					
			cout<<"Ingrese nombre del jugador [2]: ";
			cin>>player2;
					
			do {
				
				validate_move();	
				apply_move();	
				determine_winner();
				quantityMoves++;
						
				if ( quantityMoves == 9 ) break;
				
				turn == 1 ? turn = 2 : turn = 1;
						
			} while( !winner );
			
			show_result();	
		} else {
			
			cout<<"\nIngrese nombre de jugador: ";
			cin>>player1;
			
			do {		
					
				if ( turn == 1 ) 
					validate_move();					
				else 
					computer_move();
				
				apply_move();	
				determine_winner();
				quantityMoves++;
						
				if ( quantityMoves == 9 ) break;
				
				turn == 1 ? turn = 3 : turn = 1;
						
			} while( !winner );
		
			show_result();
		}

	} else {
		system("cls");
		system("Color 70");
		cout<<"JUEGO TERMINADO."<<endl;
	} 
		
	return 0;
}

void show_result() {
	
	cout<<"\n";
	
	for ( int i = 1; i <= 3; i++ ) {
		if ( i == 1 || i == 3 ) {
			for( int j = 0; j <= 48; j++ ) {
				if ( j == 0 || j == 48 ) {
					cout<<"x";
				} else {
					cout<<"-";	
				}
			}	
			
			cout<<endl;	
		} else {
			if ( player_winner == 0 ) {
				system("Color 70");
				cout<<"\n|\tEMPATE"<<"\t\t|"<<endl;
			} else if ( player_winner == 1 ) {
				system("Color A0");
				cout<<"|\tEl JUGADOR GANADOR ES: "<<player1<<"\t\t|"<<endl;	
			} else if ( player_winner == 2 ) {
				system("Color 50");
				cout<<"|\tEl JUGADOR GANADOR ES: "<<player2<<"\t\t|"<<endl;	
			} else {
				system("Color 50");
				cout<<"|\tEl JUGADOR GANADOR ES: "<<computer<<"\t\t|"<<endl;
			}		
		}
	}
	
	cout<<"\n";

}

void computer_move() {
	
	int k1, k2, u = -1, v = -1;
	
//	cout<<"ANTES DE TOMAR DECISION"<<endl;
//	cout<<"\nU: "<<u<<endl;
//	cout<<"V: "<<v<<endl;
//	system("pause");
	
	for ( int i = 0; i < 3; i++ ) {	
		switch( i ) {
			case 0:
				k1 = i + 1;
				k2 = i + 2;
			break;
			case 1:
				k1 = i - 1;
				k2 = i + 1;
			break;
			case 2:
				k1 = i - 1;
				k2 = i - 2;
			break;
		}
		
//		MODO FACIL
		if ( i == 1 ) {
			if ( Matriz[i][i] == 'X' && Matriz[k2][k1] == 'X' ) {
				if ( Matriz[k1][k2] != 'X' && Matriz[k1][k2] != 'O' ) {
					u = k1; v = k2;
					break;
				}
			}
		}
		
		if ( Matriz[i][i] == 'X' && Matriz[i][k1] == 'X' ) {
			if ( Matriz[i][k2] != 'X' && Matriz[i][k2] != 'O' ) {
				u = i; v = k2;
				break;	
			}
		} else if ( Matriz[i][i] == 'X' && Matriz[k1][i] == 'X' ) {
			if ( Matriz[k2][i] != 'X' && Matriz[k2][i] != 'O' ) {
				u = k2; v = i;
				break;
			}	
		} else if ( Matriz[i][i] == 'X' && Matriz[k1][k1] == 'X' ) {
			if ( Matriz[k2][k2] != 'X' && Matriz[k2][k2] != 'O' ) {
				u = k2; v = k2;
				break;	
			}
		} 
	}
	
	if ( u == -1 && v == -1 ) {
		choose_random_coord();	
	} else {
//		cout<<"DESPUES DE TOMAR DECISION"<<endl;
//		cout<<"\nU: "<<u<<endl;
//		cout<<"V: "<<v<<endl;
//		system("pause");
		x = u; y = v;
	}
}

void choose_random_coord() {
	
	do {
		x = rand() % (3);
		y = rand() % (3);
	} while ( Matriz[x][y] == 'X' || Matriz[x][y] == 'O' );
	
//	cout<<"\nX: "<<x<<endl;
//	cout<<"Y: "<<y<<endl;
//	system("pause");
}

void determine_winner() {
	
	int k1, k2;
	
	for ( int i = 0; i < 3; i++ ) {
		
		switch( i ) {
			case 0:
				k1 = i + 1;
				k2 = i + 2;
			break;
			case 1:
				k1 = i - 1;
				k2 = i + 1;
			break;
			case 2:
				k1 = i - 1;
				k2 = i - 2;
			break;
		}
		
		if ( i != 1 ) {
			
			if (  
				Matriz[i][i] == 'X' && Matriz[i][k1] == 'X' && Matriz[i][k2] == 'X' ||
				Matriz[i][i] == 'X' && Matriz[k1][i] == 'X' && Matriz[k2][i] == 'X' ||
				Matriz[i][i] == 'X' && Matriz[k1][k1] == 'X' && Matriz[k2][k2] == 'X' 
			) {
				
				winner = true;
				player_winner = 1;
				break;
				
			} else if (
				Matriz[i][i] == 'O' && Matriz[i][k1] == 'O' && Matriz[i][k2] == 'O' ||
				Matriz[i][i] == 'O' && Matriz[k1][i] == 'O' && Matriz[k2][i] == 'O' ||
				Matriz[i][i] == 'O' && Matriz[k1][k1] == 'O' && Matriz[k2][k2] == 'O' 
			) {
				
				winner = true;
				
				if ( type_of_game == 1 ) {
					player_winner = 2;
				} else {
					player_winner = 3;
				}
				
				break;
	 		}
				
		} else {
			
			if (  
				Matriz[i][i] == 'X' && Matriz[i][k1] == 'X' && Matriz[i][k2] == 'X' ||
				Matriz[i][i] == 'X' && Matriz[k1][i] == 'X' && Matriz[k2][i] == 'X' ||
				Matriz[i][i] == 'X' && Matriz[k1][k1] == 'X' && Matriz[k2][k2] == 'X' ||
				Matriz[i][i] == 'X' && Matriz[k2][k1] == 'X' && Matriz[k1][k2] == 'X'
			) {
				
				winner = true;
				player_winner = 1;
				break;
				
			} else if (
				Matriz[i][i] == 'O' && Matriz[i][k1] == 'O' && Matriz[i][k2] == 'O' ||
				Matriz[i][i] == 'O' && Matriz[k1][i] == 'O' && Matriz[k2][i] == 'O' ||
				Matriz[i][i] == 'O' && Matriz[k1][k1] == 'O' && Matriz[k2][k2] == 'O' ||
				Matriz[i][i] == 'O' && Matriz[k2][k1] == 'O' && Matriz[k1][k2] == 'O'
			) {
				
				winner = true;
				
				if ( type_of_game == 1 ) {
					player_winner = 2;
				} else {
					player_winner = 3;
				}
				
				break;
	 		}	
		}	
	}
}

void apply_move () {
	if ( turn == 1 ) {
		Matriz[x][y] = 'X';
	} else {
		Matriz[x][y] = 'O';
	}	
	show_board();	
}

void get_position() {	
	
	switch( move ) {
		case 1:
			x = 0; y = 0;
		break;
		case 2: 
			x = 0; y = 1;
		break;
		case 3:
			x = 0; y = 2;
		break;
		case 4:
			x = 1; y = 0;
		break;
		case 5:
			x = 1; y = 1;
		break;
		case 6: 
			x = 1; y = 2;
		break;
		case 7:
			x = 2; y = 0;
		break;
		case 8: 
			x = 2; y = 1;
		break;
		case 9:
			x = 2; y = 2;
		break;
	}
	
}

void heading_game() {
	system("cls");
	
	for ( int i = 1; i <= 3; i++ ) {
		if ( i == 1 || i == 3 ) {
			for( int j = 0; j <= 50; j++ ) {
				if ( j == 0 || j == 50 ) {
					cout<<"x";
				} else {
					cout<<"-";	
				}
			}	
			
			cout<<endl;	
		} else {
			printf("|");
			printf("%31s", "JUEGO DEL GATO" );
			printf("%20s", "|\n");
		}
	}
	
	cout<<"\n";
}

void show_board() {
	system("cls");
	cout<<"============= TABLERO DE JUEGO =============\n"<<endl;
	cout<<"Este es el tablero de juego para colocar tus movimientos.\n\n";
	
//	cout<<"\n";
//	cout<<"x:"<<x<<endl;
//	cout<<"y:"<<y<<endl;
		
	for( int i = 0; i <= 2; i++ ) {
		
		if ( i == 0 ) {
			cout<<"\t";
			for( int k = 1; k <= 19; k++ ) {
				if( k == 1 || k == 19 ) {
					cout<<"*";
				} else {
					cout<<"-";		
				}
			}
			cout<<"\n";
		}
		
		
		cout<<"\t";
		for ( int j = 0; j <= 2; j++ ) {
			if ( j == 0 ) {
				cout<<"|";
			}
					
			if ( Matriz[i][j] == 'X' ) {
				cout<<"  "<<"\033[1;32m"<<Matriz[i][j]<<"\033[0m"<<"  |";
			} else if ( Matriz[i][j] == 'O' ) {
				
				if ( type_of_game == 1 ) {
					cout<<"  "<<"\033[0;35m"<<Matriz[i][j]<<"\033[0m"<<"  |";
				} else {
					cout<<"  "<<"\033[0;34m"<<Matriz[i][j]<<"\033[0m"<<"  |";	
				}
				
			} 
			else {
				cout<<"  "<<Matriz[i][j]<<"  |";
			}				
		}
				
		cout<<"\n";
		cout<<"\t";
		for( int k = 1; k <= 19; k++ ) {
			if( k == 1 || k == 19 ) {
				cout<<"*";
			} else {
				cout<<"-";		
			}
		}
		cout<<"\n";
	}
			
	cout<<"\n";
	
	cout<<"\033[1;32m"<<player1<<"\033[0m"<<" juega con"<<"\033[1;32m"<<" X "<<"\033[0m"<<endl;
		
	if ( type_of_game == 1 ) {
		cout<<"\033[0;35m"<<player2<<"\033[0m"<<" juega con"<<"\033[0;35m"<<" O "<<"\033[0m"<<endl;		
	} else {
		cout<<"\033[0;34m"<<computer<<"\033[0m"<<" juega con"<<"\033[0;34m"<<" O "<<"\033[0m"<<endl;
	}

}

void validate_move () {
	
	do {
		show_board();	
		
		if ( turn == 1 ) {
			cout<<"\nTurno de "<<"\033[1;32m"<<player1<<"\033[0m"<<": ";
		} else if ( turn == 2 ) {
			cout<<"\nTurno de "<<"\033[0;35m"<<player2<<"\033[0m"<<": ";
		} else {
			cout<<"\nTurno de "<<"\033[0;34m"<<computer<<"\033[0m"<<": ";
		}
					
		cin>>move;
		
		get_position();	
							
	} while( move < 1 || move > 9 || Matriz[x][y] == 'X' || Matriz[x][y] == 'O' );
	
}












