// in the name of God
// product by Seyyed Mahdi Maddah

#include <bits/stdc++.h>
#include<conio.h>

using namespace std;
const int max_tree_size = 20;
int tree[max_tree_size];
int player = 1;
int& base = tree[10]; // A place where players and branches are checked (tree 10)
void display(){
	system("cls");
	cout << "\t _______________________________\n";
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
		if (base == 1){
			cout << "\t|\t  #  |||||||     \t|\n";
		}else if (base == 2){
			cout << "\t|\t  #  |||||||=====\t|\n";
		}
	}else if (player == 2){
		if (base == 1){
			cout << "\t|\t     |||||||  #  \t|\n";
		}else if (base == 3){
			cout << "\t|\t=====|||||||  #  \t|\n";
		}
	}
	cout << "\t|_______________________________|\n";
}
void game_over(){
	cout << "\tGame Over\n";
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
	char c = getch();
	if (c == 'a' || c == 'A')player = 1;
	else if (c == 'd' || c == 'D')player = 2;
	else move();
}
void update_tree(){
	// tree 1 equal to tree trunk
	// tree 2 equal to right branch
	// tree 3 equal to left branch
	for (int i = 10; i >= 2; i--){
		tree[i] = tree[i-1];
	}
	tree[1] = (rand()%3) + 1;
}
void make_tree(){
	// tree 1 equal to tree trunk
	for (int i = 1; i <= 10; i++){
		tree[i] = 1;
	}
}
int main(){
	make_tree();
	while (true){
		move();
		update_tree();
		display();
		check_encounter();
	}
}