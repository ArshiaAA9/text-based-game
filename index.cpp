#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <list>
#include <vector>
#include <unordered_map>

// ANSI escape codes for text color
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"


//class declaration
class Slime; 
class Player;


//Entity BASE class 
class Entity{
public:
    std::string name;
    int hp, playerArmor;
    int blindStatus; //standard is 2

    void takeDmg(int amount, int attackedEntitiesArmor){
        
        int reducedDmg = (amount * (attackedEntitiesArmor / 100.0));
        this->hp -= (amount - reducedDmg);
        if (this->hp < 0)
        {
            std::cout << this->name << " has died!";
        }        
    }


};


//make the player class and then update the methods later on
class Player : public Entity{
public:

    class Inventory{ //inventory class used to gather item related info like attackDmg health buffer 
        private: //kinda the guideline of what a item is 


            struct ArmorItem{ // struct for armor items
                std::string  name, itemType = "armor";
                int armorBuff; 

                ArmorItem(std::string name, int aBuff) : name(name) , armorBuff(aBuff) {} 
            };


            struct WeaponItem{ // struct for weapons they give attackBuff
                std::string itemType = "weapon";
                std::string name;
                int dmgBuff;
                
                WeaponItem(std::string name, int dBuff) : name(name), dmgBuff(dBuff) {}
            };
            

            struct MixedItem{ // they give attackBuff healthBuff hpBuff 
                std::string itemType = "mixed";
                std::string name;
                int dmgBuff;
                int armorBuff;
                int healthBuff;

                MixedItem(std::string name, int dBuff, int aBuff, int hBuff) 
                    : name(name), dmgBuff(dBuff), armorBuff(aBuff),  healthBuff(hBuff) {}
            };

            // a vector which is in this case is a list of structs
            std::unordered_map<std::string, ArmorItem> armorItems; 
            std::unordered_map<std::string, WeaponItem> weaponItems;
            std::unordered_map<std::string, MixedItem> mixedItems;


        public: // functions that add item structs to the   vector

            //adds a armor to player inventory
            void addArmorItem(std::string name, int armorBuff) {
                armorItems[name] = {name, armorBuff};
                printText("you picked up an armor piece!\nname: "+ name +"\narmor: " + std::to_string(armorBuff));
            }

            //adds weapon item to player inventory
            void addWeaponItem(std::string name, int dmgBuff) {
                weaponItems[name] = {name, dmgBuff};
                printText("you picked up a weapon!\nname: "+ name +"\nAttack Damage: " + std::to_string(dmgBuff));
            
            }
            //adds mixed item to player inventory
            void addMixedItem(std::string name, int dmgBuff, int armorBuff, int healthBuff) {
                mixedItems[name] = {name, dmgBuff, armorBuff, healthBuff};
                printText("you picked up mixed weapon!\nname: "+ name +"\nAttack Damage: " + std::to_string(dmgBuff)+"\nArmor: "+ std::to_string(armorBuff) +"\nHealth Buff:"+ std::to_string(healthBuff));

            }
            // functions to work with inventory

            //print inventory items using for loops
            void printInventoryItems(){
                //prints armorItems
                std::cout << "Armors:\n" << std::endl;
                for (const auto& pair : armorItems){
                    std::cout << "Name: " <<pair.first << " Armor" << pair.second.armorBuff << std::endl;
                
                }

                std::cout << "\nWeapons:" << std::endl; 
                for (const auto& pair : weaponItems){
                    std::cout << "Name: " <<pair.first << " Attack Damage:" << pair.second.dmgBuff << std::endl;
                
                }
                
                std::cout << "\nWeapons:" << std::endl; 
                for (const auto& pair : mixedItems){
                    std::cout << "Name: " <<pair.first << " Attack Damage:" << pair.second.dmgBuff << " Armor:" << pair.second.armorBuff << " Heal Buff" << pair.second.healthBuff <<std::endl;
                
                }
                    std::cout << "\n" << std::endl;
            }
            //function to get the weapon attack damage

            
    
    };
private:
    int originalArmor;

public:
    Inventory inventory;
    std::string race;
    int attackDmg;


    Player(std::string name, std::string race){ //player object constructor
        inventory.addWeaponItem("Basic Dagger", 5);
        this->name = name;
        this->race = race;
        this->hp = 100;
        this->attackDmg = 20;
        this->playerArmor = 20;

    }

    void attacking(Entity* entity);

    void onGuard(){ // adds extra armor 
        originalArmor = this->playerArmor;
        this->playerArmor += this->playerArmor; 
    }

    void unGuard(){ // removes the extra armor
        this->playerArmor = originalArmor;
    }


};


//Slime class with methods
class Slime : public Entity{
public:
    int attackDmg;
    std::string type;

    Slime(int attackDmg, std::string type, std::string name, int hp){
        this->name = name;
        this->hp = hp;
        this->attackDmg = attackDmg;
        this->type = type;
        this->playerArmor = 0;
        
    }

    ~Slime(){
        std::cout << "Slime named " << this->name << " has been killed" << std::endl;
    }

    void attack(Player* player,bool blindStatus=false){
        if (blindStatus == true){

            std::cout << "no damage was dealt cause of blind" << std::endl;
            return; 
        }
        player->takeDmg(this->attackDmg, player->playerArmor);
        return;
    }

private:

};


void Player::attacking(Entity* entity){
    std::cout << "player attacking" << std::endl;
    entity->takeDmg(this->attackDmg, entity->playerArmor);
}





char takeAction(char userInput, Slime* slime , Player* player);
void printText(std::string text, int speed = 4);
char enemyAction(Player* player, Slime* slime,bool guarded=false);


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


    std::string userName, race; // character making
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

    Slime slime1(10, "brown", "slim", 40); // creating slime

    while (true){ // fight mechanic

        char action; // taking user input
        std::cout << "So what will you do?" << GREEN 
        << "\nA/a for attack G/g for guard S/s for shotting the enemy in the eye and blinding them: " << RESET;
        std::cin >> action;

        takeAction(action, &slime1, &mainPlayer); //take action based on user input  
    

        if(slime1.hp <= 0){
            printText("You Killed The Slime!",100); //is the base for kill msgs
            printText(std::string("You found a new item called the ")+ MAGENTA +" Wand" + RESET);



            break;
        }else{
            printText(("Slime has "+ std::to_string(slime1.hp) + " left"));
        }
    }// end of the first fight with the slime



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
    return;
}           

char takeAction(char userInput, Slime* slime , Player* player){ //checks the user input for a,g,s
    
    if (userInput == 'A' || userInput == 'a'){ // attacking
        printText("You attacked the "+slime->name);
        player->attacking(slime);

        if(slime->hp <= 0){ //checks if the slime is alive
            
            return 'a';
            
        }else{
            
            enemyAction(player, slime);
            return 'a';
        }
    }
    else if (userInput == 'G' || userInput == 'g') // guarding 
    {
        enemyAction(player, slime, true);
        return 'g';

    }
    else if (userInput == 'S' || userInput == 's')
    {
        printText("you shot the "+slime->name+" and blinded them");
        slime->blindStatus += 2;
        enemyAction(player, slime);
        return 's';
    }
    else{

        printText("Enter a valid input!");
        return 'n';
    }
    enemyAction(player, slime);
    return 'n';
}

char enemyAction(Player* player, Slime* slime,bool guarded){

    if(slime->blindStatus > 0){ //check if slime is blinded

        slime->attack(player, true);
        slime->blindStatus--;
        
    }else if(guarded){ // if guarded remove the extra armor

        player->onGuard();
        
        slime->attack(player);

        player->unGuard();

    
    }else{

        slime->attack(player);
    }
    
    printText("You got attacked by "+slime->name+ "\nyour hp is "+ GREEN + std::to_string(player->hp) + RESET);
    return 'n';
}
