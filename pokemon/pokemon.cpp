#include <iostream>

// file lib
#include <fstream>

// data struct lib
#include <vector>
#include <map>

// for split func
#include <sstream>

// for random
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

struct Pokemon
{
    // header
    vector<string> header;

    // list of pokemon names
    vector<string> pokemon_name;

    // converting pokemon to id and vice versa
    map<string, int> pokemon_to_id;
    map<int, string> id_to_pokemon;
    
    // stats
    map<string, string> pokemon_type1;
    map<string, string> pokemon_type2;
    map<string, string> pokemon_Total;
    map<string, string> pokemon_HP;
    map<string, string> pokemon_ATK;
    map<string, string> pokemon_DEF;
    map<string, string> pokemon_SpATK;
    map<string, string> pokemon_SpDEF;
    map<string, string> pokemon_SPEED;
    map<string, string> pokemon_GEN;
    map<string, bool> pokemon_LEGENDARY;

    map<string, string> Types_to_num;
    
};

const int MAX_SCORE = 100; // Max to win
const int MIN_SCORE = -20; // Max to lose
const int START_SCORE = 0; // Starting score
const int ADD_SCORE = 5; // per right question
const int REM_SCORE = 0; // per wrong question

Pokemon fill_pokemon();
vector<string> split(string text, char del = ' ');
void print_all_pokemon(Pokemon pokemon);



int main(){
    /*
    TODO:
    1. Making a file of pokemon names and types 
    2. Reading the file using a list dict
    3. shuffle the list of names
    4. Reading the logic
    5. Making a score based system
    */

    // define the score
    int score = START_SCORE;
    int add = ADD_SCORE;
    int rem = REM_SCORE;
    int max_sc = MAX_SCORE;
    int min_sc = MIN_SCORE; 

    // getting the pokemon names
    Pokemon pokemon = fill_pokemon();
    
    // shuffling pokemon_name
    vector<string> name = pokemon.pokemon_name;
    
    auto rng = default_random_engine {};
    rng.seed(time(0));
    uniform_int_distribution<int> distribution(0, pokemon.header.size() - 1);
    auto picker = bind(distribution, rng);

    shuffle(name.begin(),name.end(), rng);

    cout<< "\nPOKEMON QUIZ\nMade by Nickson\n\n";

    int number = 1;
    // making the quizz
    while (true)
    {
        // handle score
        if (score >= max_sc)
        {
            cout<< "YOU WIN!!!"<<endl;
            return 0;
        }
        else if (score < min_sc)
        {
            cout<< "YOU LOSE!!!"<<endl;
            return 1; 
        }
        
        // incase name is empty
        if (name.empty())
        {
            cout<< "YOU WIN!!!"<< endl;
            return 0;
        }


        // pick random header category type with int
        int pick = picker();
        
        string topic = pokemon.header[pick];

        string cur_pok = name.back();

        if (topic == "Type 1" || topic == "Type 2" || topic == "Name") // boosting the chance of Type
        {
            topic = "Type";
        }
        else if (topic == "Total")
        {
            topic = "Total Stat";
        }
        else if (topic == "HP")
        {
            topic = "HP Stat";
        }
        else if (topic == "Attack")
        {
            topic = "Attack Stat";
        }
        else if (topic == "Defense")
        {
            topic = "Defense Stat";
        }
        else if (topic == "Sp. Atk")
        {
            topic = "Sp. Atk Stat";
        }
        else if (topic == "Sp. Def")
        {
            topic = "Sp. Def Stat";
        }
        else if (topic == "Speed")
        {
            topic = "Speed Stat";
        }


        // removing the pokemon on the list
        name.pop_back();

        // showing
        cout<< number <<". Pokemon Question:\n";
        
        if (topic != "Legendary")
        { 
            cout<< "What is the "<< topic << " of "<< cur_pok<<"?\n";
        }
        else
        {
            cout<<"Is "<< cur_pok<<" a "<< topic<<"?\n";
        }
        string answer;
        unsigned int num;
        bool is_correct;

        // what is the topic?
        if (topic == "id")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (pokemon.pokemon_to_id[cur_pok] == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "Type")
        {
            cout<<"Option:"<<endl;
            cout<<"1. Normal"<<endl;
            cout<<"2. Fire"<<endl;
            cout<<"3. Water"<<endl;
            cout<<"4. Electric"<<endl;
            cout<<"5. Grass"<<endl;
            cout<<"6. Ice"<<endl;
            cout<<"7. Fighting"<<endl;
            cout<<"8. Poison"<<endl;
            cout<<"9. Ground"<<endl;
            cout<<"10. Flying"<<endl;
            cout<<"11. Psychic"<<endl;
            cout<<"12. Bug"<<endl;
            cout<<"13. Rock"<<endl;
            cout<<"14. Ghost"<<endl;
            cout<<"15. Dragon"<<endl;
            cout<<"16. Dark"<<endl;
            cout<<"17. Steel"<<endl;
            cout<<"18. Fairy"<<endl;
            while (true)
            {
                cout<<"Please put the number in the answer or the type.\nAnswer: "<<endl;

                getline(cin, answer);

                // modifying user input
                answer.resize(distance(answer.begin(), remove_if(answer.begin(), answer.end(), [](unsigned char c){ return c == ' ';})));
                transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char c){ return tolower(c);});
                answer.front() = toupper(answer.front());
                string type1 = pokemon.pokemon_type1[cur_pok];
                string type2 = pokemon.pokemon_type2[cur_pok]; 

                // checking
                if (type1 == answer || type2 == answer || pokemon.Types_to_num[type1] == answer || pokemon.Types_to_num[type2] == answer)
                {
                    is_correct = true;
                    break;
                }
                else
                {
                    // checking if input in map
                    if (pokemon.Types_to_num.count(answer))
                    {
                        is_correct = false;
                        break;
                    }
                    // checking if a num
                    try
                    {
                        num = stoi(answer);
                        if (num < 19 && num > 0)
                        {
                            is_correct = false;
                            break;
                        }
                    }
                    catch(const invalid_argument){}
                    cout<< "Invalid Input. Please put a number between 1-18 or a Type.\n";
                }
            }

        }
        else if (topic == "Total Stat")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (stoi(pokemon.pokemon_Total[cur_pok]) == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "HP Stat")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (stoi(pokemon.pokemon_HP[cur_pok]) == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "Attack Stat")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (stoi(pokemon.pokemon_ATK[cur_pok]) == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "Defense Stat")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (stoi(pokemon.pokemon_DEF[cur_pok]) == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "Sp. Atk Stat")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (stoi(pokemon.pokemon_SpATK[cur_pok]) == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "Sp. Def Stat")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (stoi(pokemon.pokemon_SpDEF[cur_pok]) == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "Speed Stat")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (stoi(pokemon.pokemon_SPEED[cur_pok]) == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "Generation")
        {
            while (true)
            {
                cout<<"Answer: ";
                getline(cin, answer);
                try{
                    num = stoi(answer);
                    break;
                }
                catch(const invalid_argument)
                {
                    cout<< "Invalid Input. Please put a number.\n";
                }
            }
            if (stoi(pokemon.pokemon_GEN[cur_pok]) == num)
            {
                is_correct = true;
            }
            else
            {
                is_correct = false;
            }
        }
        else if (topic == "Legendary")
        {
            cout<<"Yes or No?\n";
            while(true)
            {
                getline(cin, answer);
                answer.resize(distance(answer.begin(), remove_if(answer.begin(), answer.end(), [](unsigned char c){ return c == ' ';})));
                transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char c){ return tolower(c);});
                answer.front() = toupper(answer.front());
                bool res;
                if (answer == "Y" || answer =="N" || answer == "No"|| answer == "Yes")
                {
                    if (answer == "No" || answer == "N")
                    {
                        res = false;
                    }
                    if (answer == "Yes" || answer == "Y")
                    {
                        res = true;
                    }
                    if (res == pokemon.pokemon_LEGENDARY[cur_pok])
                    {
                        is_correct = true;
                        break;
                    }
                    else if (res == pokemon.pokemon_LEGENDARY[cur_pok])
                    {
                        is_correct = true;
                        break;
                    }
                    else if (res != pokemon.pokemon_LEGENDARY[cur_pok])
                    {
                        is_correct = false;
                        break;
                    }
                    else if (res != pokemon.pokemon_LEGENDARY[cur_pok])
                    {
                        is_correct = false;
                        break;
                    }
                }
                else
                {
                    cout<< "Invalid Input. Please put a Yes or No.\n";
                }
            }
        }

        // checking if its correct
        if (is_correct)
        {
            cout<<"...";
            cout<< "\nCORRECT!\n";
            score += add;
        }
        else
        {
            cout<<"...";
            cout<< "\nINCORRECT!\n";
            score -= rem;
        }
        // print score
        cout<< "Score: " << score << endl<< "..." <<endl<<endl;
        // updating number
        number++;
    }

    return 0;    
}

void print_all_pokemon(Pokemon pokemon)
{
    for (string poke: pokemon.pokemon_name){
        cout<<poke << "|";
        cout<<pokemon.pokemon_type1[poke]<< "|";
        cout<< pokemon.pokemon_type2[poke]<< "|";
        cout<<pokemon.pokemon_Total[poke]<< "|";
        cout<<pokemon.pokemon_HP[poke]<< "|";
        cout<<pokemon.pokemon_ATK[poke]<< "|";
        cout<<pokemon.pokemon_DEF[poke]<< "|";
        cout<<pokemon.pokemon_SpATK[poke]<< "|";
        cout<<pokemon.pokemon_SpDEF[poke]<< "|";
        cout<<pokemon.pokemon_SPEED[poke]<< "|";
        cout<<pokemon.pokemon_GEN[poke]<< "|";
        cout<<pokemon.pokemon_LEGENDARY[poke]<< "\n"; 
    
    }
}


Pokemon fill_pokemon()
{
    string text;
    // initiazing the pokemon struct

    Pokemon pokemon;
    
    // reading the file
    ifstream MyReadFile("pokemon_names_types.csv");
    
    // get the first line
    getline(MyReadFile, text);
    pokemon.header = split(text, ',');

    // inserting the types

    pokemon.Types_to_num["Normal"] = "1"; 
    pokemon.Types_to_num["Fire"] = "2"; 
    pokemon.Types_to_num["Water"] = "3"; 
    pokemon.Types_to_num["Electric"] = "4"; 
    pokemon.Types_to_num["Grass"] = "5"; 
    pokemon.Types_to_num["Ice"] = "6"; 
    pokemon.Types_to_num["Fighting"] = "7"; 
    pokemon.Types_to_num["Poison"] = "8"; 
    pokemon.Types_to_num["Ground"] = "9"; 
    pokemon.Types_to_num["Flying"] = "10"; 
    pokemon.Types_to_num["Psychic"] = "11"; 
    pokemon.Types_to_num["Bug"] = "12"; 
    pokemon.Types_to_num["Rock"] = "13"; 
    pokemon.Types_to_num["Ghost"] = "14"; 
    pokemon.Types_to_num["Dragon"] = "15"; 
    pokemon.Types_to_num["Dark"] = "16"; 
    pokemon.Types_to_num["Steel"] = "17"; 
    pokemon.Types_to_num["Fairy"] = "18"; 

    while(getline(MyReadFile, text))
    {
        // spliting each line
        vector<string> splitval = split(text, ',');
        
        string poke = splitval[1];

        // pokemon to id
        pokemon.pokemon_to_id[poke] = stoi(splitval[0]);
        
        // id to pokemon
        pokemon.id_to_pokemon[stoi(splitval[0])] = poke;
        
        // storing the name to a list
        pokemon.pokemon_name.push_back(poke);

        // storing the name of the pokemon in a dict
        pokemon.pokemon_type1[poke] = splitval[2];
        pokemon.pokemon_type2[poke] = splitval[3];

        // storing stats
        pokemon.pokemon_Total[poke] = splitval[4];
        pokemon.pokemon_HP[poke] = splitval[5];
        pokemon.pokemon_ATK[poke] = splitval[6];
        pokemon.pokemon_DEF[poke] = splitval[7];
        pokemon.pokemon_SpATK[poke] = splitval[8];
        pokemon.pokemon_SpDEF[poke] = splitval[9];
        pokemon.pokemon_SPEED[poke] = splitval[10];

        // storing gen and legendary
        pokemon.pokemon_GEN[poke] = splitval[11];
        splitval[12].front() = tolower(splitval[12].front());
        istringstream(splitval[12]) >> boolalpha >> pokemon.pokemon_LEGENDARY[poke];
        
    }
    
    MyReadFile.close();

    return pokemon;
}

// func to split string to list using char
vector<string> split(string text, char del)
{
    istringstream iss(text);
        vector<string> splitval;
        string sub;
        while(getline(iss, sub, del))
        {
            splitval.push_back(sub);
        }
    
    return splitval;
}