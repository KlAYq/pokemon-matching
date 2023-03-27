#include "menu.h"
#include "draw.cpp"
/*
Page 1 = Log in / Register / Quit
Page 2 = Log in page
Page 3 = Register page
Page 4 = Start / Leaderboard / Credit / Quit
Page 5 = Difficulty choice
Page 6 = Custom board page
Page 7 = Show leaderboard
Page 8 = Show game credit
Page 9 = Gameplay
*/

void processReg(savefile &player, bool &isLogged)
{
    fstream file("account.bin", ios::binary | ios::in | ios::out); // open file in read and write mode

    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! File cannot be opened.";
        return;
    }

    bool isExist = false;
    savefile tempPlayer;
    //cout << tempPlayer.name << " " << tempPlayer.password << endl;
    while (file.read((char*)&tempPlayer, sizeof(tempPlayer))) // read data from file
    {
        if (strcmp(tempPlayer.name, player.name) == 0) // check if username already exists
        {
            isExist = true;
            cout << "Username already exists. Press any key to go back...";
            getch();
            break;
        }
    }

    if (!isExist) // if username does not exist, write player data to file
    {
        file.clear();
        file.seekp(0, ios::end);
        file.write((char*)&player, sizeof(player));
        cout << "Registration successful! Press any key to continue...";
        getch();
        isLogged = true;
    }

    file.close(); // close file
}

void processLogin(savefile player, bool &isLogged)
{
    ifstream file("account.bin", ios::binary);
    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! File cannot be opened.";
        return;
    }

    savefile tempPlayer;
    while (file.read((char*)&tempPlayer, sizeof(tempPlayer))) // read data from file
    {
        if (strcmp(tempPlayer.password, player.password) == 0) // check if username exists
        {
            if (strcmp(tempPlayer.password, player.password) == 0) //check if password matches
            {
                cout << "Login successful! Press any key to continue...";
                getch();
                isLogged = true;
                break;
            }
            else
            {
                break;
            }
        }
    }

    if(isLogged == false)
    {
        cout << "Username or Password is not correct! Press any key to go back.";
        getch();
    }
    
    file.close();  
}

void displayForm(savefile player,int choice, bool &isLogged)
{
    clear();
    string title = "";
    if (choice == 1)
        title = "LOG IN";
    else
        title = "REGISTER";
    int box_size = 20;

    GoTo(0, (WinColumn - title.length()) / 2);
    cout << title;
    
    GoTo(4, (WinColumn - 10 - box_size) / 2);
    cout << "Username: ";
    drawCell(" ", 3, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);

    GoTo(7, (WinColumn - 10 - box_size) / 2);
    cout << "Password: ";
    drawCell(" ", 6, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);

    GoTo(4, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(player.name, 20);

    GoTo(7, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(player.password, 20);

    GoTo(9, (WinColumn - 10 - box_size) / 2 + 12);

    if (choice == 1)
        processLogin(player, isLogged);
    else
        processReg(player, isLogged);
}

void displayLoginRegisterMenu(savefile &player)
{
    string title = "POKEMON PUZZLE!";
    string username;

    int cellRowSize = 3;
    int cellColumnSize = 15;

    vector<string> options;
    options.push_back("LOG IN");
    options.push_back("REGISTER");
    options.push_back("QUIT");

    int choice = 1;
    bool isLogged = false;
    bool displayMenu = true;
    
    while (!isLogged)
    {
        if (displayMenu)
        {
            clear();
            GoTo(0, (WinColumn - title.length()) / 2);
            cout << title;

            int posX = 2, posY = (WinColumn - cellColumnSize) / 2;
            for (int i = 0; i < options.size(); i++)
            {
                if (choice == i + 1)
                {
                    drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, yellow, black);
                    posX += 4;
                }
                else
                {
                    drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, white, black);
                    posX += 4;
                }
            }
            char input = getch();
            input = toupper(input);
            switch(input)
            {
                case 'W':
                    if (choice > 1 )
                        choice --;
                    break;
                case 'S':
                    if (choice < options.size())
                        choice ++;
                    break;
                case ' ':
                    if (choice == 1 || choice == 2)
                    {
                        displayForm(player, choice, isLogged);
                    }
                    else
                    {
                        //QUIT?
                    }
                    break;
            }
        }
    }
}

void displayMenu(int page, int choice)
{
    clear();
    string gname = "POKEMON PUZZLE!";

    vector<string> options;
    options.push_back("START");
    options.push_back("LEADERBOARD");
    options.push_back("CREDIT");
    options.push_back("QUIT");
    
    
    vector<string> difficulty;
    difficulty.push_back("EASY");
    difficulty.push_back("MEDIUM");
    difficulty.push_back("HARD");
    difficulty.push_back("CUSTOM");

    int cellRowSize = 3;
    int cellColumnSize = 15;

    GoTo(0, (WinColumn - gname.length()) / 2);
    cout << gname;

    int posX = 2, posY = (WinColumn - cellColumnSize) / 2;

    if (page == 4)
    {
        for (int i = 0; i < options.size(); i++)
        {
            if (choice == i + 1)
            {
                drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, yellow, black);
                posX += cellRowSize;
            }
            else
            {
                drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, white, black);
                posX += cellRowSize;
            }
            
        }
    }
    else if (page == 5)
    {
        for (int i = 0; i < difficulty.size(); i++)
        {
            if (choice - 1 == i)
            {
                drawCell(difficulty[i], posX, posY, cellRowSize, cellColumnSize, yellow, black);
                posX += cellRowSize;
            }
            else
            {
                drawCell(difficulty[i], posX, posY, cellRowSize, cellColumnSize, white, black);
                posX += cellRowSize;
            }
            
        }
    }
}

void generateMenu(int &page, int &choice)
{
    displayMenu(page, choice);
    char input = getch();
    input = toupper(input);

    if (page == 4)
    {
        switch(input)
        {
            case 'W':
                if (choice > 1)
                    choice --;
                break;
            case 'S':
                if (choice < 3)
                    choice ++;
                break;
            case ' ':
                if (choice == 1)
                    page = 2;
                else if (choice == 2)
                    page = 4;
                else
                    page = 0;
                choice = 1;
                break;
        }
    }
    else if (page == 5)
    {
        switch (input)
        {
            case 'W':
                if (choice > 1)
                    choice --;
                break;
            case 'S':
                if (choice < 4)
                    choice ++;
                break;
            case ' ':
                page = choice;
                break;
        }
    }
    else 
    {
        cout << "Error!";
    }
}


int main()
{
    SetWindowSize(120, 30);
    // clear();
    // int page = 1, choice = 1;
    // while (page <= 4 && choice <= 4)
    // {
    //     generateMenu(page, choice);
    //     if (page == 0)
    //         break;
    // }
    savefile player;
    displayLoginRegisterMenu(player);

    return 0;
}