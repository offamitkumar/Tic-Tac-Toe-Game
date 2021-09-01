#include <iostream>
#include <utility>
#include <set>
#include <iomanip>
/* macros */
#define MAX_WRONG_CHOICE 5
#define GRID_SIZE 3
#define HORIZONTAL_DISPLAY_CONSTANT 8  // used in printing the grid 
#define VERTICAL_DISPLAY_CONSTANT 5 
#define VERTICAL_GAP 5
#define HORIZONTAL_GAP 5

/* Variables */
enum state{ EMPTY , OCCUPIED_PLAYER_ONE , OCCUPIED_PLAYER_TWO };
enum turn{ playerOne , playerTwo };
enum gameResult{ PLAYER_ONE , PLAYER_TWO  , TIE };
std::string USER_ONE , USER_TWO;
state grid[3][3];
gameResult result;
char defaultFillingChar = 'X' , userOneFillingChar='O', userTwoFillingChar='T'; 
bool gameOver = false;
bool nonFreeGridError = false; // prevent players to occupy each other's selected location 
bool nonValidGridLocation = false; // check validity of location 

/* functions Used */
inline void                  clearSystem         ( void ) ;
inline void                  startGame           ( void ) ;
inline void                  developerInfo       ( void ) ;
inline void                  printWarning        ( int  ) ;
inline void                  welcomeUtility      ( void ) ;
inline void                  goodByeMessage      ( void ) ;
inline void                  play                ( void ) ;
inline void                  setGridValues       ( void ) ;
inline void                  printTheGrid        ( void ) ;
inline bool                  isValid             ( int  ) ;
inline void                  setGrid             ( void ) ;
inline std::pair<int,int>    getGridLocation     ( int  ) ;
inline bool                  isGameOver          ( void ) ;
inline void                  printResult         ( void ) ;
inline bool                  perfectName         ( void ) ;


/* function to be added in future */
void setGridSize     ( int  ) ;
void printGrid       ( void ) ;
void printResult     ( void ) ;

int main(int argc , char *argv[]){

    clearSystem(); // clear the screen 

    startGame(); 

    goodByeMessage();

    return 0;
} 

void setGridValues( void ) {

    for( int row = 0; row < GRID_SIZE; ++row ) {
        for( int col = 0; col < GRID_SIZE; ++col ) {
            grid[ row ] [ col ] = state::EMPTY;  // at present none player play a move 
        }
    }
}

std::pair<int,int> getGridLocation( int Input ) {
    switch( Input ) {
        case 1:
            return std::make_pair(0,0);
            break;
        case 2:
            return std::make_pair(0,1);
            break;
        case 3:
            return std::make_pair(0,2);
            break;
        case 4:
            return std::make_pair(1,0);
            break;
        case 5:
            return std::make_pair(1,1);
            break;
        case 6:
            return std::make_pair(1,2);
            break;
        case 7:
            return std::make_pair(2,0);
            break;
        case 8:
            return std::make_pair(2,1);
            break;
        case 9:
            return std::make_pair(2,2);
            break;
    }
    static_assert("Error !!\n");
    exit(0);
}

void setGrid( int Location , turn Turn) {
    std::pair<int , int > gridLocation = getGridLocation(Location);
    if(grid[ gridLocation.first ][ gridLocation.second ] == state::EMPTY){
        if(Turn == turn::playerOne ){
            grid[ gridLocation.first ] [ gridLocation.second ] = OCCUPIED_PLAYER_ONE;
        }else{
            grid[ gridLocation.first ] [ gridLocation.second ] = OCCUPIED_PLAYER_TWO;
        }
    }else{ 
        nonFreeGridError = true;
    }
    return ;
}

bool isValid( int location ) {
    if(location <= 0 || location > 9){
        nonValidGridLocation = true;
        return false;
    }
    return true;
}

bool isGameOver( void ){
    bool gridIsEmpty = true;
    for(int row = 0; row < GRID_SIZE; ++row){
        for( int col = 0; col < GRID_SIZE; ++col ) {
            if( grid[row][col] != state::EMPTY ){
                goto skip;
            }
        }
    }
    return false;
skip:
    if(grid[0][0] != state::EMPTY && grid[0][0] == grid[0][1]  && grid[0][0] == grid[0][2]){
        result = ( grid[0][0] == state::OCCUPIED_PLAYER_ONE )? gameResult::PLAYER_ONE : gameResult::PLAYER_TWO;
        return true;
    }
    if(grid[1][0] != state::EMPTY && grid[1][0] == grid[1][1]  && grid[1][0] == grid[1][2]){
        result = ( grid[1][0] == state::OCCUPIED_PLAYER_ONE )? gameResult::PLAYER_ONE : gameResult::PLAYER_TWO;
        return true;
    }
    if(grid[2][0] != state::EMPTY && grid[2][0] == grid[2][1]  && grid[2][0] == grid[2][2]){
        result = ( grid[2][0] == state::OCCUPIED_PLAYER_ONE )? gameResult::PLAYER_ONE : gameResult::PLAYER_TWO;
        return true;
    }
    if(grid[0][0] != state::EMPTY && grid[0][0] == grid[1][0]  && grid[0][0] == grid[2][0]){
        result = ( grid[0][0] == state::OCCUPIED_PLAYER_ONE )? gameResult::PLAYER_ONE : gameResult::PLAYER_TWO;
        return true;
    }
    if(grid[1][1] != state::EMPTY && grid[0][1] == grid[1][1]  && grid[0][1] == grid[2][1]){
        result = ( grid[0][1] == state::OCCUPIED_PLAYER_ONE )? gameResult::PLAYER_ONE : gameResult::PLAYER_TWO;
        return true;
    }
    if(grid[0][2] != state::EMPTY && grid[0][2] == grid[1][2]  && grid[0][2] == grid[2][2]){
        result = ( grid[0][2] == state::OCCUPIED_PLAYER_ONE )? gameResult::PLAYER_ONE : gameResult::PLAYER_TWO;
        return true;
    }
    if(grid[0][0] != state::EMPTY && grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) {
        result = ( grid[0][0] == state::OCCUPIED_PLAYER_ONE )? gameResult::PLAYER_ONE : gameResult::PLAYER_TWO;
        return true;
    }
    if(grid[0][2] != state::EMPTY && grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]) {
        result = ( grid[0][2] == state::OCCUPIED_PLAYER_ONE )? gameResult::PLAYER_ONE : gameResult::PLAYER_TWO;
        return true;
    }
    // what if all grid are occupied but none of the player is winner 
    for(int row = 0; row < GRID_SIZE; ++row){
        for( int col = 0; col < GRID_SIZE; ++col ) {
            if( grid[row][col] == state::EMPTY ){
                return false;
            }
        }
    }
    result = gameResult::TIE;
    return true;
}

void printResult( void ) {
    if( result == gameResult::PLAYER_ONE ) {
        std::cout << USER_ONE << " is Winner !!" << '\n';
    }else if(result == gameResult::PLAYER_TWO){
        std::cout << USER_TWO << " is Winner !!" << '\n'; } 
    else{
        std::cout << " TIE !! " << '\n' ; 
    }
}

void play( void ) {
    gameOver = false;
    setGridValues( );
    turn Turn = turn::playerOne;
    int occupyGrid;
    std::cout << "Enter Player 1 Name: ";
    std::cin.ignore();
    std::getline(std::cin , USER_ONE);
    std::cout << "Enter Player 2 Name: ";
    std::getline(std::cin , USER_TWO );
    if (perfectName()) {
        userOneFillingChar = USER_ONE[0]; 
        userTwoFillingChar = USER_TWO[0];
    } 
    while(gameOver == false){
        printTheGrid( ); 
        if(nonValidGridLocation == true){
            std::cout<<"\nError: Please Enter a Valid Location between 1 to 9 ( inclusive ) !"<<'\n';
            nonValidGridLocation = false;
        }
        if(nonFreeGridError == true){
            std::cout<<"\nError: Please Enter a Valid Location , Current location is already Occupied!"<<'\n';
            nonFreeGridError = false;
        }
        if( isGameOver() ){ // if game is over , return; 
            gameOver = true;
            printResult();
            return; 
        }
        if(Turn == turn::playerOne){
            std::cout<<"Player 1 Turn: ";
            std::cin>>occupyGrid;
            if(occupyGrid == 0){
                exit(0);
            }
            if(isValid(occupyGrid) == false){
                continue;
            }
            setGrid(occupyGrid , Turn);
            if(nonFreeGridError == true){
                continue;
            }
            Turn = turn::playerTwo;
        }else{
            std::cout<<"Player 2 Turn: ";
            std::cin>>occupyGrid;
            if(occupyGrid == 0){
                exit(0);
            }
            if(isValid(occupyGrid) == false){
                continue;
            }
            setGrid(occupyGrid , Turn);
            if(nonFreeGridError == true){
                continue;
            }
            Turn = turn::playerOne;
        }
    }
}

void printTheGrid( void ) {
    clearSystem();
    std:: cout << '\n'; 
    std::set<std::pair<int,int>>occupied;
    for( int j = 0; j <  GRID_SIZE ; ++j ) {
        std::cout<<"\t\t\t\t\t\t";
        for(int i = 0; i < HORIZONTAL_DISPLAY_CONSTANT * GRID_SIZE ; ++i ) {
            std::cout<<'#';
        }
        std::cout << '#';
        std::cout << '\n' ;
        for(int i = 0; i < VERTICAL_GAP ; ++i) {
            std::cout<<"\t\t\t\t\t\t";
            std::cout<<'#';
            for( int k = 0; k < 3; ++k ) {
                bool printed = false;
                if(i==2){
                    for(int x=0;x < 3; ++x){
                        if(occupied.find(std::make_pair(j,k))==occupied.end() && grid[j][k] == state::OCCUPIED_PLAYER_ONE){
                            occupied.insert(std::make_pair(j,k));
                            std::cout << std::setfill(' ') << std::setw(4) << userOneFillingChar << std::setfill(' ') << std::setw(4);
                            printed = true;
                            break;
                        }
                        if(occupied.find(std::make_pair(j,k))==occupied.end() && grid[j][k] == state::OCCUPIED_PLAYER_TWO){
                            occupied.insert(std::make_pair(j,k));
                            std::cout << std::setfill(' ') << std::setw(4) << userTwoFillingChar << std::setfill(' ') << std::setw(4);
                            printed = true;
                            break;
                        }
                    }
                }
                if(printed == true){
                    std::cout << '#';
                    continue;
                }
                if(i == 2 and grid[ j ][ k ] == state::OCCUPIED_PLAYER_ONE ) {
                    std::cout << std::setfill(' ') << std::setw(4) << 'A' << std::setfill(' ') << std::setw(4);
                }else if(i==2 and grid[ j ][ k ] == state::OCCUPIED_PLAYER_TWO){
                    std::cout << std::setfill(' ') << std::setw(4) << 'C' << std::setfill(' ') << std::setw(4);
                }else if(i == 2 and grid[ j ][ k ] == state::EMPTY ) {
                    std::cout << std::setfill(' ') << std::setw(4) << defaultFillingChar << std::setfill(' ') << std::setw(4);
                }else{
                    std::cout << std::setfill(' ') << std::setw(8) ;
                }
                std::cout << '#';
            }
            std::cout << '\n' ;
        }
    }

    std::cout<<"\t\t\t\t\t\t";
    for(int i = 0; i < HORIZONTAL_DISPLAY_CONSTANT * GRID_SIZE ; ++i ) {
        std::cout<<'#';
    }
    std::cout<<'#'<<'\n';
}
void developerInfo( void ) {
    clearSystem();
    std::cout << "\t\t\t\t This information will be added Soon!!\n  " << '\n' ;
    std::cout << "\n\t\t\t\t For any Bug please mail : offamitkumar@gmail.com \n\n";
    return ;
}
void clearSystem( void ) {
    // for Linux & Mac 
    system("clear");
    // for Windows comment the above line and uncomment the line below
    // system("cls");
    return ;
}
void printWarning ( int warningNumber ) {
    static int isFirstMistake = 0; 
    clearSystem();
    welcomeUtility();
    if(++isFirstMistake == 1){
        std::cout << "Oops!! You made a Incorrect Choice !!" ;
    }else{
        std::cout << "Oops!! You made a Incorrect Choice again !!";
    }
    std::cout << '\n' << '\n' ;
    std::cout<<"Warning : You have only " << warningNumber << " choices remaining.\n\n"; 
    return ;
}
void goodByeMessage ( void ) {
    clearSystem();
    std::cout<<R"(


                                                                 Thank you for using this Game !!
                                                              
                                                              
                                                                 Mail Me if you find any Bug : offamitkumar@gmail.com
                                                              
                                                               
                                                               
    )"<< '\n' ;
}
void welcomeUtility ( void ) {
    std::cout<<R"(  
        
                                                                      -: Welcome to Tic-Tac-Toe Game :-
                 
                                                                    
                                                                       Choose Your Options :
                 
                                                                       1 ) Play The Game 
                                                                       2 ) Manual 
                                                                       3 ) Developer Info
                                                                       4 ) Exit 
                 
        )"<<'\n';
    return ;
}
void startGame( void ) {
    welcomeUtility ( ); 
    int userInput , wrongChoice{};
    bool isWrongChoice = false; 
    bool isGamePlayed = false;
    while ( wrongChoice < MAX_WRONG_CHOICE ) {
        std::cout << "Enter Your Choice: ";
        std::cin >> userInput;
        isWrongChoice = false;
        // for any correct choice we will set the total wrong choice made till now to 0 :)
        switch( userInput ) {
            case 1: 
                play( );
                wrongChoice = 0;
                isGamePlayed = true;
                break;
            case 2:
                // Manual ( ) 
                wrongChoice = 0;
                break;
            case 3:
                developerInfo();
                wrongChoice = 0;
                break;
            case 4:
                return ;
            default:
                isWrongChoice = true;
        }
        wrongChoice += isWrongChoice;
        if( wrongChoice == MAX_WRONG_CHOICE ) {
            return ;
        }
        if(isWrongChoice == true){
            printWarning( MAX_WRONG_CHOICE - wrongChoice );
        }
        if(isGamePlayed == true){
            isGamePlayed = false;
            char Continue;
            std::cout<<"\nDo you want continue(y/n/Y/N):  ";
            std::cin>>Continue;
            switch ( Continue ) {
                case 'N':
                case 'n':
                case 'Q':
                case 'e':
                case 'E':
                case 'q':
                    return; 
                case 'y':
                case 'Y':
                    break;
                    // pass
                default:
                    std::cout<<"\nYou pressed illegal key\nStarting the game again \n";
            }
        }
    }
    return;
}
bool perfectName ( void ) {
    return USER_ONE[0] != USER_TWO[0]; 
}
