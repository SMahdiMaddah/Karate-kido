// in the name of God
// product by Seyyed Mahdi Maddah

#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
using namespace std;

#define setBrown setTextColor(6, 0)
#define setBlue setTextColor(1, 0)
#define setWhite setTextColor(15, 0)
#define setRed setTextColor(4, 0)

ALLEGRO_DISPLAY *alg_display;

void start_game();


const int max_tree_size = 20;
int tree[max_tree_size];
int player = 1;
int& base = tree[10]; // A place where players and branches are checked (tree 10)
int max_score = 0;
int score = 0;


// powering up item
int f_Flag = 0;
int x2_Flag = 0;


// _________________



void setTextColor(int textColor, int backColor) {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  int colorAttribute = backColor << 4 | textColor;
  SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void show_score_board(){
	setRed;
	cout << "\n";
	cout << "\t _______________________________\n";
	cout << "\t|Score: " <<setw(7)<< score << " |  Max = " << setw(7) << max_score << "|\n";
	cout << "\t|_______________|_______________|\n";
}
void update_score(){
//	score += 30;
	if (score < 1e3){
		score += 30;
		if (x2_Flag){
			x2_Flag--;
			score += 30;
		}
	}else if (score < 1e4){
		score += 50;
		if (x2_Flag){
			x2_Flag--;
			score += 50;
		}
	}else if (score < 1e5){
		score += 100;
		if (x2_Flag){
			x2_Flag--;
			score += 100;
		}
	}
	max_score = max(score, max_score);
}
void display(){
	system("cls");
	setBrown;
	cout << "\t _______________________________\n";
	setBrown;
	for (int i = 1; i <= 9; i++){
		if (tree[i] == 1){
			cout << "\t|\t     |||||||     \t|\n";
		}else if (tree[i] == 2){
			cout << "\t|\t     |||||||=====\t|\n";
		}else if (tree[i] == 3){
			cout << "\t|\t=====|||||||     \t|\n";
		}else{
			cout << "Eror 404   " << tree[i] << '\n';
		}
	}
	if (player == 1){
		cout << "\t|\t";
		setBlue;
		cout << "  #  ";
		setBrown;
		if (base == 1){
			cout << "|||||||     \t|\n";
		}else if (base == 2){
			cout << "|||||||=====\t|\n";
		}else{
			cout << "|||||||     \t|\n"; // game over
		}
	}else if (player == 2){
		if (base == 1){
			cout << "\t|\t     |||||||";
		}else if (base == 3){
			cout << "\t|\t=====|||||||";
		}else{
			cout << "\t|\t     |||||||"; // game over
		}
		setBlue;
		cout << "  #  ";
		setBrown;
		cout << "\t|\n";
	}
	cout << "\t|_______________________________|\n";
//	setRed;
	show_score_board();
}
void display_game_over(){
	
}
void game_over(){
	setWhite;
	int choose = 1;
	while (true){
		display();
		cout << "\t Game Over!\n";
		cout << "\t Do you want to Play again?   ";
		setWhite;
		if (choose == 1){
			setTextColor(0, 15);
			cout << "Yes";
			setWhite;
			cout << "   ";
			cout << "No\n";
		}else{
			setWhite;
			cout << "Yes";
			cout << "   ";
			setTextColor(0, 15);
			cout << "No\n";
			setWhite;
		}
		int c = getch();
		if (c == 13){
			if (choose == 1){
				start_game();
			}else if (choose == 2){
				exit(0);
			}
		}else if (c == 224){
			c = getch();
			if (c == 75)choose = 1; // left
			else if (c == 77)choose = 2; // right
		}
	}
	exit(0);
}
void check_encounter(){
	if (base == 2 && player == 2){
		game_over();
	}else if (base == 3 && player == 1){
		game_over();
	}
}
void move(){
	if (f_Flag){
		f_Flag--;
		if (tree[9] == 1)return;
		else if (tree[9] == 2){
			player = 1;
		}else if (tree[9] == 3){
			player = 2;
		}
		return;
	}
	int c = getch();
	if (c == 224){
		c = getch();
		if (c == 75)player = 1; // left
		else if (c == 77)player = 2; // right
		else move();
	}else move();
}
void update_tree(){
	// tree 1 equal to tree trunk
	// tree 2 equal to right branch
	// tree 3 equal to left branch
	for (int i = 10; i >= 2; i--){
		tree[i] = tree[i-1];
	}
	tree[1] = (rand()%3) + 1;
	if ((tree[1] == 2 && tree[2] == 3) || (tree[1] == 3 && tree[2] == 2)){
		tree[1] = 1;
	}
	if (tree[1] == 1){
		int power_up = (rand()%35) + 1;
		if (power_up == 5){
			tree[1] = 3; // speed
		}else if (power_up == 15){
			tree[1] = 4; // freeze
		}else if (power_up == 25){
			tree[1] = 5; // 2x
		}else if (power_up == 35){
			tree[1] = 6; // +2s
		}
	}
}
void make_tree(){
	// tree 1 equal to tree trunk
	for (int i = 1; i < 10; i++){
		tree[i] = (rand()%3) + 1;
		if ((tree[i] == 2 && tree[i-1] == 3) || (tree[i] == 3 && tree[i-1] == 2)){
			tree[i] = 1;
		}
	}
	tree[10] = 1;
}
void start_game(){
	
	make_tree();
	score = 0;
	while (true){
		display();
		move();
		check_encounter();
		update_tree();
		check_encounter();
		update_score();
	}

}
int main(){
	al_init();

	alg_display = al_create_display(1280, 720);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_flip_display();

	
	start_game(); 
}