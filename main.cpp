// in the name of God
// product by Seyyed Mahdi Maddah

#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <pthread.h>
#include <chrono>
#include <time.h>
#include <ctime>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
using namespace std;

#define setBrown setTextColor(6, 0)
#define setBlue setTextColor(1, 0)
#define setWhite setTextColor(15, 0)
#define setRed setTextColor(4, 0)

ALLEGRO_DISPLAY *alg_display;

void start_game();
void make_tree();
void menu();

const int max_tree_size = 20;
int tree[max_tree_size];
int player = 1;
int& base = tree[10]; // A place where players and branches are checked (tree 10)
int max_score = 0;
int score = 0;
int Time = 10;

// powering up item
int f_Flag = 0;
int x2_Flag = 0;
int freeze_Flag = 0;
// _________________

// graphics
	ALLEGRO_BITMAP *background;
	ALLEGRO_BITMAP *menu1;
	ALLEGRO_BITMAP *menu2;
	ALLEGRO_BITMAP *menu3;
	ALLEGRO_BITMAP *l_branch;
	ALLEGRO_BITMAP *r_branch;
	ALLEGRO_BITMAP *l_player;
	ALLEGRO_BITMAP *r_player;
	ALLEGRO_BITMAP *gl_player;
	ALLEGRO_BITMAP *gr_player;
	ALLEGRO_BITMAP *a_gameover;
	ALLEGRO_BITMAP *e_gameover;
	ALLEGRO_BITMAP *s_board;
	ALLEGRO_BITMAP *t_board;
	ALLEGRO_BITMAP *up_time;
	ALLEGRO_BITMAP *up_2x;
	ALLEGRO_BITMAP *up_speed;
	ALLEGRO_BITMAP *up_freeze;
//	ALLEGRO_BITMAP *time10;
	
	ALLEGRO_FONT *font;
	
	ALLEGRO_KEYBOARD_STATE kbdstate;
	
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT_QUEUE *event_queue2;
	
// end graphics

// profile
struct profile{
	int uscore;
	int umscore;
	int utime;
	int tree[20];
};
struct profile user;
// end prfile
void save_data(){
	ofstream file("data\\data.txt", std::ios::trunc);
	if (!file.is_open()) {
        std::cerr << "Could not open file!\n";
        return;
    }
    file << player << '\n';
    file << score << '\n';
    file << max_score << '\n';
    file << Time << '\n';
    for (int i = 1; i <= 10; i++){
    	file << tree[i] << '\n';
	}
	file.close();
}
void setTextColor(int textColor, int backColor) {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  int colorAttribute = backColor << 4 | textColor;
  SetConsoleTextAttribute(consoleHandle, colorAttribute);
}
void show_time_board(){
	string str_Time = to_string(Time);
	al_draw_bitmap(t_board, 30, 30, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), 125, 43, ALLEGRO_ALIGN_CENTER, str_Time.c_str());
	al_flip_display();
}

void timer(){
	time_t startTime = time(nullptr);
	while (Time){
		time_t nowTime = time(nullptr);
		double diff = difftime(nowTime, startTime);
		if (diff >= 1 && freeze_Flag == 0){
			startTime = nowTime;
//			show_time_board();
			Time--;
		}
	}
}
void show_score_board(){
	
	
	al_draw_bitmap(s_board, 1000, 30, 0);
	
	string str_score = to_string(score);
	string str_max_score = to_string(max_score);
	
	al_draw_text(font, al_map_rgb(249, 219, 36), 1150, 37, ALLEGRO_ALIGN_CENTER, str_score.c_str());
    al_draw_text(font, al_map_rgb(153, 50, 204), 1150, 68, ALLEGRO_ALIGN_CENTER, str_max_score.c_str());
	
	al_flip_display();	
	
	
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
	// allgero option
	ALLEGRO_COLOR balck = al_map_rgb(0,0,0);	
	// end allgero option
	
	system("cls");
	al_draw_bitmap(background, 0, 0, 0);
//	al_draw_bitmap(l_player, 500, 515, 0);
//	al_draw_bitmap(r_player, 660, 515, 0);
//	al_draw_bitmap(l_branch, 490, i * 50, 0);
//	al_draw_bitmap(r_branch, 650, i * 50, 0);
	setBrown;
	cout << "\t _______________________________\n";
	setBrown;
	for (int i = 1; i <= 9; i++){
		if (tree[i] == 1){
			cout << "\t|\t     |||||||     \t|\n";
		}else if (tree[i] == 2){
			cout << "\t|\t     |||||||=====\t|\n";
			al_draw_bitmap(r_branch, 650, i * 50, 0);
		}else if (tree[i] == 3){
			cout << "\t|\t=====|||||||     \t|\n";
			al_draw_bitmap(l_branch, 490, i * 50, 0);
		}else if (tree[i] == 11){
			al_draw_bitmap(up_speed, 530, i * 50, 0);
		}else if (tree[i] == 4){
			al_draw_bitmap(up_speed, 670, i * 50, 0);
		}else if (tree[i] == 5){
			al_draw_bitmap(up_freeze, 530, i * 50, 0);
		}else if (tree[i] == 6){
			al_draw_bitmap(up_freeze, 670, i * 50, 0);
		}else if (tree[i] == 7){
			al_draw_bitmap(up_2x, 530, i * 50, 0);
		}else if (tree[i] == 8){
			al_draw_bitmap(up_2x, 670, i * 50, 0);
		}else if (tree[i] == 9){
			al_draw_bitmap(up_time, 530, i * 50, 0);
		}else if (tree[i] == 10){
			al_draw_bitmap(up_time, 670, i * 50, 0);
		}else{
			cout << "Eror 404   " << tree[i] << '\n';
		}
	}
	if (player == 1){
		cout << "\t|\t";
		setBlue;
		cout << "  #  ";
		al_draw_bitmap(l_player, 500, 515, 0);
		setBrown;
		if (base == 1){
			cout << "|||||||     \t|\n";
		}else if (base == 2){
			cout << "|||||||=====\t|\n";
			al_draw_bitmap(r_branch, 650, 10 * 50, 0);
		}else{
			cout << "|||||||     \t|\n"; // game over
		}
		
		
		if (base == 4){
			al_draw_bitmap(up_speed, 670, 10 * 50, 0);
		}else if (base == 6){
			al_draw_bitmap(up_freeze, 670, 10 * 50, 0);
		}else if (base == 8){
			al_draw_bitmap(up_2x, 670, 10 * 50, 0);
		}else if (base == 10){
			al_draw_bitmap(up_time, 670, 10 * 50, 0);
		}
		
		
	}else if (player == 2){
		if (base == 1){
			cout << "\t|\t     |||||||";
		}else if (base == 3){
			cout << "\t|\t=====|||||||";
			al_draw_bitmap(l_branch, 490, 10 * 50, 0);
		}else{
			cout << "\t|\t     |||||||"; // game over
		}
		setBlue;
		cout << "  #  ";
		al_draw_bitmap(r_player, 680, 515, 0);
		setBrown;
		cout << "\t|\n";
		
		
		if (base == 11){
			al_draw_bitmap(up_speed, 530, 10 * 50, 0);
		}else if (base == 5){
			al_draw_bitmap(up_freeze, 530,10 * 50, 0);
		}else if (base == 7){
			al_draw_bitmap(up_2x, 530, 10 * 50, 0);
		}else if (base == 9){
			al_draw_bitmap(up_time, 530, 10 * 50, 0);
		}
		
	}
	cout << "\t|_______________________________|\n";
//	setRed;
	show_score_board();
	show_time_board();
	al_flip_display();
}

void game_over_display(){
	
	system("cls");
	al_draw_bitmap(background, 0, 0, 0);
//	al_draw_bitmap(l_player, 500, 515, 0);
//	al_draw_bitmap(r_player, 660, 515, 0);
//	al_draw_bitmap(l_branch, 490, i * 50, 0);
//	al_draw_bitmap(r_branch, 650, i * 50, 0);
	setBrown;
	cout << "\t _______________________________\n";
	setBrown;
	for (int i = 1; i <= 9; i++){
		if (tree[i] == 1){
			cout << "\t|\t     |||||||     \t|\n";
		}else if (tree[i] == 2){
			cout << "\t|\t     |||||||=====\t|\n";
			al_draw_bitmap(r_branch, 650, i * 50, 0);
		}else if (tree[i] == 3){
			cout << "\t|\t=====|||||||     \t|\n";
			al_draw_bitmap(l_branch, 490, i * 50, 0);
		}else{
			cout << "Eror 404   " << tree[i] << '\n';
		}
	}
	if (player == 1){
		cout << "\t|\t";
		setBlue;
		cout << "  #  ";
		al_draw_bitmap(gl_player, 450, 515, 0);
		setBrown;
		if (base == 1){
			cout << "|||||||     \t|\n";
		}else if (base == 2){
			cout << "|||||||=====\t|\n";
			al_draw_bitmap(r_branch, 650, 10 * 50, 0);
		}else{
			cout << "|||||||     \t|\n"; // game over
		}
	}else if (player == 2){
		if (base == 1){
			cout << "\t|\t     |||||||";
		}else if (base == 3){
			cout << "\t|\t=====|||||||";
			al_draw_bitmap(l_branch, 490, 10 * 50, 0);
		}else{
			cout << "\t|\t     |||||||"; // game over
		}
		setBlue;
		cout << "  #  ";
		al_draw_bitmap(gr_player, 680, 515, 0);
		setBrown;
		cout << "\t|\n";
	}
	cout << "\t|_______________________________|\n";
//	setRed;
	show_score_board();
	al_flip_display();	
}

void game_over(){
	setWhite;
	int choose = 1;
	while (true){
		game_over_display();
		cout << "\t Game Over!\n";
		cout << "\t Do you want to Play again?   ";
		setWhite;
		if (choose == 1){
			al_draw_bitmap(a_gameover, 200, 100, 0);
			al_flip_display();
			
			setTextColor(0, 15);
			cout << "Yes";
			setWhite;
			cout << "   ";
			cout << "No\n";
		}else{
			al_draw_bitmap(e_gameover, 200, 100, 0);
			al_flip_display();
			
			setWhite;
			cout << "Yes";
			cout << "   ";
			setTextColor(0, 15);
			cout << "No\n";
			setWhite;
		}
		
//		al_get_keyboard_state(&kbdstate);
//		
//		if (al_key_down(&kbdstate , ALLEGRO_KEY_LEFT)){
//			choose = 1;
//			cout << "KHIHIH\n";
//		}else if (al_key_down(&kbdstate , ALLEGRO_KEY_RIGHT)){
//			choose = 2;
//		}
		
		ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) {
            if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        choose = 1;
                        break;
                    case ALLEGRO_KEY_RIGHT:
						choose = 2;
                        break;
                    case ALLEGRO_KEY_ENTER:
                    	if (choose == 1){
//                    		make_tree();
//							start_game();
							menu();
						}else if (choose == 2){
							exit(0);
						}
						break;
                }
            }
        }
		
//		int c = getch();
//		if (c == 13){
//			if (choose == 1){
//				start_game();
//			}else if (choose == 2){
//				exit(0);
//			}
//		}else if (c == 224){
//			c = getch();
//			if (c == 75)choose = 1; // left
//			else if (c == 77)choose = 2; // right
//		}
	}
	exit(0);
}
void pu_speed(){
	f_Flag = 7;
}
void pu_2x(){
	x2_Flag = 7;
}
void pu_time(){
	Time = min(Time+2, 10);
}
void pu_freeze(){
	freeze_Flag = 10;
}
void check_encounter(){
	if (base == 2 && player == 2){
		game_over();
	}else if (base == 3 && player == 1){
		game_over();
	}else if (base == 11 && player == 1){
		pu_speed();
	}else if (base == 4 && player == 2){
		pu_speed();
	}else if (base == 5 && player == 1){
		pu_freeze();
	}else if (base == 6 && player == 2){
		pu_freeze();
	}else if (base == 7 && player == 1){
		pu_2x();
	}else if (base == 8 && player == 2){
		pu_2x();
	}else if (base == 9 && player == 1){
		pu_time();
	}else if (base == 10 && player == 2){
		pu_time();
	}else if (Time <= 0){
		game_over();
	}
}
void move(){
	if (freeze_Flag)freeze_Flag--;
	if (f_Flag){
		f_Flag--;
		if (tree[9] == 1)return;
		else if (tree[9] == 2){
			player = 1;
		}else if (tree[9] == 3){
			player = 2;
		}
		Sleep(1000);
		return;
	}
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	int sw = 0;
	while(1){
		ALLEGRO_EVENT ev;
	    
		if (al_get_next_event(event_queue, &ev)) {
			if (ev.type == ALLEGRO_EVENT_KEY_UP) {
	    		switch (ev.keyboard.keycode) {
	                case ALLEGRO_KEY_LEFT:
	                    player = 1;
	                    sw = 1;
	                    ev.keyboard.keycode = ALLEGRO_KEY_UP;
	                    break;
	                case ALLEGRO_KEY_RIGHT:
						player = 2;
						sw = 1;
	                    ev.keyboard.keycode = ALLEGRO_KEY_UP;
						break;
					case ALLEGRO_KEY_ESCAPE:
						save_data();
						menu();
						break;
	            }
	        }
	    }
	    if (sw)break;
	}
//	int c = getch();
//	if (c == 224){
//		c = getch();
//		if (c == 75)player = 1; // left
//		else if (c == 77)player = 2; // right
//		else move();
//	}else move();
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
		int power_up = (rand()%40) + 1;
		if (power_up == 5 ){
			tree[1] = 11; // speed left
		}else if (power_up == 6){
			tree[1] = 4; // speed right
		}else if (power_up == 15){
			tree[1] = 5; // freeze left
		}else if (power_up == 16){
			tree[1] = 6; // freeze right
		}else if (power_up == 25){
			tree[1] = 7; // 2x left
		}else if (power_up == 26){
			tree[1] = 8; // 2x right
		}else if (power_up == 35){
			tree[1] = 9; // +2s left
		}else if (power_up == 36){
			tree[1] = 10; // +2s right
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
	score = 0;
	Time = 10;
}
void start_game(){
	thread timerThread(timer);
	while (true){
		display();
		move();
		check_encounter();
		update_tree();
		check_encounter();
		update_score();
	}
//	timerThread.join();
}
void load_data(){
	ifstream file("data\\data.txt");
	if (!file.is_open()) {
        std::cerr << "Could not open file!\n";
        exit(0);
    }
    vector<int> data_number; 
    int num;
    while (file >> num) {
        data_number.push_back(num);
    }
    player = data_number[0];
    score = data_number[1];
    max_score = data_number[2];
    Time = data_number[3];
    for (int i = 1; i <= 10; i++){
    	tree[i] = data_number[i + 3];
	}
	file.close();
}
void menu(){
	int choose = 1;
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	 
	while (1) {
		if (choose == 1){
			al_draw_bitmap(menu1, 0, 0, 0);
		}else if (choose == 2){
			al_draw_bitmap(menu2, 0, 0, 0);
		}else if (choose == 3){
			al_draw_bitmap(menu3, 0, 0, 0);
		}
		al_flip_display();
		
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) {
            if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        choose = max(choose - 1, 1);
                        break;
                    case ALLEGRO_KEY_DOWN:
						choose = min(choose + 1 , 3);
                        break;
                    case ALLEGRO_KEY_ENTER:
                    	if (choose == 1){
                    		make_tree();
							start_game();
						}else if (choose == 2){
							load_data();
							start_game();
						}else if (choose == 3){
							exit(0);
						}
						break;
                }
            }
        }
    }
}
int main(){
	if (!al_init()){
		cout << "Could not init allegro!\n";
		return 0;
	}

	alg_display = al_create_display(1280, 720);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_flip_display();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    
    
	// load images
	menu1 = al_load_bitmap("icon\\menu1.png");
	menu2 = al_load_bitmap("icon\\menu2.png");
	menu3 = al_load_bitmap("icon\\menu3.png");
	background = al_load_bitmap("icon\\background.png");
	a_gameover = al_load_bitmap("icon\\GameOver1.png");
	e_gameover = al_load_bitmap("icon\\GameOver2.png");
	s_board = al_load_bitmap("icon\\scoreboard.png");
	t_board = al_load_bitmap("icon\\timeboard.png");
	up_time = al_load_bitmap("icon\\uptime.png");
	up_2x = al_load_bitmap("icon\\up2x.png");
	up_speed = al_load_bitmap("icon\\upspeed.png");
	up_freeze = al_load_bitmap("icon\\upfreeze.png");
	if (!background) {
        cout << "could not load image of backgrond!\n";
        return 0;
    }
	l_player = al_load_bitmap("icon\\player1.png");
	r_player = al_load_bitmap("icon\\player2.png");
	gl_player = al_load_bitmap("icon\\gplayer1.png");
	gr_player = al_load_bitmap("icon\\gplayer2.png");
	if (!r_player) {
        cout << "could not load image of player!\n";
        return 0;
    }
    l_branch = al_load_bitmap("icon\\lbranch.png");
    if (!l_branch) {
        cout << "could not load image of left branch!\n";
        return 0;
    }
    r_branch = al_load_bitmap("icon\\rbranch.png");
	if (!r_branch) {
        cout << "could not load image of right branch!\n";
        return 0;
    }
    font = al_load_ttf_font("font\\arial.ttf", 16, 0);
    if (!font) {
        cout << "could not load font!\n";
        return 0;
    }
    event_queue = al_create_event_queue();
    event_queue2 = al_create_event_queue();
    
    
    
	// end loading images
//	al_draw_bitmap(background, 0, 0, 0);
////	al_draw_bitmap(p_player, 500, 515, 0);
////	al_draw_bitmap(l_branch, 490, 50, 0);
////	al_draw_bitmap(r_branch, 650, 50, 0);
//	for (int i = 1 ;  i <= 10; i++){
//		al_draw_bitmap(l_branch, 490, i * 50, 0);
//		al_draw_bitmap(r_branch, 650, i * 50, 0);
//	}
//    al_flip_display();
	
	menu();
	start_game(); 
}