#include <iostream>
#include <iomanip>
/* macros */
#define MAX_WRONG_CHOICE 5
#define GRID_SIZE 3
#define HORIZONTAL_DISPLAY_CONSTANT 8  // used in printing the grid 
#define VERTICAL_DISPLAY_CONSTANT 5 
#define VERTICAL_GAP 5
#define HORIZONTAL_GAP 5


/* Variables */

enum state{ EMPTY , OCCUPIED };

state grid[3][3];


/* functions Used */

inline void clearSystem     ( void ) ;
inline void startGame       ( void ) ;
inline void developerInfo   ( void ) ;
inline void printWarning    ( int  ) ;
inline void welcomeUtility  ( void ) ;
inline void goodByeMessage  ( void ) ;
inline void play            ( void ) ;
inline void setGridValues   ( void ) ;
inline void printTheGrid    ( void ) ;


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


void play( void ) {

    setGridValues( );

    printTheGrid( ); 


}


void printTheGrid( void ) {

    clearSystem();

    std:: cout << '\n'; 
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


                if( i == 2 and  grid[ i ][ k ] == state::OCCUPIED ) {

                    std::cout << std::setfill(' ') << std::setw(4) << 'O' << std::setfill(' ') << std::setw(4);

                }else if(i == 2 and grid[ i ][ k ] == state::EMPTY ) {

                    std::cout << std::setfill(' ') << std::setw(4) << 'X' << std::setfill(' ') << std::setw(4);

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
    
    while ( wrongChoice < MAX_WRONG_CHOICE ) {

        std::cout << "Enter Your Choice: ";

        std::cin >> userInput;
        isWrongChoice = false;

        // for any correct choice we will set the total wrong choice made till now to 0 :)

        switch( userInput ) {

            case 1: 
                play( );
                wrongChoice = 0;

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
    }

    return;
}
