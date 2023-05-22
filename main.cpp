#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>
using namespace std;

class Board {
  public:
    string name;
};

void create_board() {
  cout << "What would you like to name your board?" << endl;
  string board_name;
  cin >> board_name;
  //Create a new board
  Board new_board = Board();
  new_board.name = board_name;

  ifstream data_file;
  data_file.open("data.txt");
  string board_count;
  data_file >> board_count;
  data_file.close();
  int boards;
  try {
    boards = stoi(board_count);
  }
  catch (invalid_argument) {
    boards = 0;
  }
  boards++;
  ofstream data_file_out;
  data_file_out.open("data.txt", ofstream::trunc);
  data_file_out << boards;
  data_file_out.close();
  //Increment board count, get board count to name new board file

  ofstream board_file;
  struct stat sb;
  if (stat("boards", &sb) == 0) {
    board_file.open("boards\\" + to_string(boards - 1) + ".txt");
    board_file << board_name << ":";
    board_file.close();
  }
  else {
    mkdir("boards");
    board_file.open("boards\\" + to_string(boards - 1) + ".txt");
    board_file << board_name << ":";
    board_file.close();
  }


  cout << "Board created! (" << board_name << ")" << endl;
}

void open_board() {
  cout << "Which board would you like to open?" << endl;
  string board_count;
  ifstream data_file;
  data_file.open("data.txt");
  data_file >> board_count;
  data_file.close();
  int boards = stoi(board_count);
  if (boards == 0) cout << "No boards created. Please create a board first.";
  for (int i = 0; i < boards; i++) {
    string board_name;
    ifstream board_file;
    board_file.open("boards\\" + to_string(i) + ".txt");
    board_file >> board_name;
    board_file.close();
    for (int j = 0; i < board_name.length(); j++) {
      if (board_name[j] == ':') {
        board_name = board_name.substr(0, j);
        break;
      }
    }
    cout << to_string(i + 1) + ". " + board_name << endl;
  }
}

string menu_choice() {
  cout << "What would you like to do?" << endl;
  cout << "1. Create a new board" << endl;
  cout << "2. Open an existing board" << endl;
  cout << "3. Exit" << endl;
  cout << "4. Delete all saved data" << endl;
  string user_in;
  cin >> user_in;
  return user_in;
}

void main_menu() {
  string user_choice = menu_choice();
  while (user_choice != "1" && user_choice != "2" && user_choice != "3" && user_choice != "4") {
    cout << "Invalid input. Please try again." << endl;
    user_choice = menu_choice();
  }
  //Get valid user input
  if (user_choice == "1") {
    create_board();
  }
  else if (user_choice == "2") {
    open_board();
  }
  else if (user_choice == "3") {
    exit(0);
  }
  else if (user_choice == "4") {
    ifstream data_file_in;
    data_file_in.open("data.txt");
    string board_count;
    data_file_in >> board_count;
    int boards = stoi(board_count);
    for (int i = 0; i < boards; i++) {
      remove(("boards\\" + to_string(i) + ".txt").c_str());
    }
    ofstream data_file;
    data_file.open("data.txt", ofstream::trunc);
    data_file << "0";
    data_file.close();
    cout << "All data deleted." << endl;
  }
}

int main() {
  cout << "------------------------------------------------------------------" << endl;
  cout << "PRODUC++IVITY - Optimize your work time with open-source software." << endl;
  cout << "------------------------------------------------------------------" << endl;
  //Welcome message

  while (true) main_menu();
  //Run main menu
}

