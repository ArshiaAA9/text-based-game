#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <list>

// ANSI escape codes for text color
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

/*
-main game logic 
-something like undertale

*/


class Entity{
public:
    std::string name;
    int hp;

    void takeDmg(int amount){
        this->hp -= amount;
        if (this->hp < 0)
        {
            std::cout << this->name << " has died!";
        }
        
    }

};


class Slime : public Entity{
    
public:
    int attackDmg;
    std::string type;

    Slime(int attackDmg, std::string type, std::string name, int hp){
        this->name = name;
        this->hp = hp;
        this->attackDmg = attackDmg;
        this->type = type;
    }

    ~Slime(){
        std::cout << "Slime type " << this->type << " has been killed" << std::endl;
    }

private:

};


class Player : public Entity{
public:

    int attackDmg;
    std::string race;

    Player(std::string name, std::string race){
        this->name = name;
        this->hp = 100;
        this->attackDmg = 20;
        this->race = race;

    }

    void attacking(Entity* entity){
        entity->takeDmg(this->attackDmg);
    }

};

char takeAction(char userInput, Entity* entity , Player* player);
void printText(std::string text, int speed = 4);

int main(){

    std::string startingDialogue = "once upon a time a man was born famous for "
    "the name that his parents had given him 'Cockus'.Cockus was the grand grand grand "
    "child of the great famous 'KurtMurat' known for his famous watch and Cockus just "
    "like his grand grand grand father was famous as well but not for his watch but "
    "for his frankness and his desires to do everything possible in the world."
    "then we have you, you are the friend of the legend Cockus and his companion"
    "in these hard tough days";
    printText(startingDialogue);

    std::string firstActionDialogue = "\n\nOn your way to the castle of king smith "
    "with the big Cockus when you guys got tiered and"
    "lied down to reset you fell sleep for a short while but when you woke up you "
    "were really surprised because you couldn't find Mr.Cockus next to yourself. "
    "you started heading for the nearby hill to try and see Cockus from there.\n";
    printText(firstActionDialogue);

    std::string userName, race;

    char answer;
    
    while (true){
        std::cout << RED <<"<<Character Building>>\n\n" << YELLOW 
        << "Enter your username: " << RESET;
        std::cin >> userName;
        std::cout << YELLOW <<"Enter your race: " << RESET;
        std::cin >> race;


        std::cout << "\nAre you sure you want to commit? [Y/n]:";
        std::cin >> answer;

        if (answer == 'Y'|| answer == 'y')
        {
            break;
        }
    }

    Player mainPlayer(userName, race);
        
    std::string afterWakingUp = "As you are heading for the hill you saw a slime "
    "when you tried to talk to the slime the slime took aggressive stance "
    "and instantly tried attacking you. \n\n";
    printText(afterWakingUp);

    char action;
    std::cout << "So what will you do?" << GREEN 
    << "\nA/a for attack G/g for guard T/t for talk: " << RESET;
    std::cin >> action;

    Slime slime1(10, "brown", "slim", 100);
    takeAction(action, &slime1, &mainPlayer);
    

    return 0;
}

void printText(std::string text,int speed){
    int i;
    for ( i = 0; i < text.size(); i++)
    {
        std::cout << text[i];
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
    std::cout << std::endl;
}           

char takeAction(char userInput, Entity* entity , Player* player){

    if (userInput == 'A' || userInput == 'a')
    {
        player->attacking(entity);
        printText("You attacked the "+entity->name);


    }
    else if (userInput == 'G' || userInput == 'g')
    {
        return 'g';
    }
    else if (userInput == 'T' || userInput == 't')
    {
        return 't';
    }
    else{
        return 'n';
    }
    return 'n';
}
