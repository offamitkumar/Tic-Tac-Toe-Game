#include <iostream>
/* macros */
#define MAX_WRONG_CHOICE 5


/* functions Used */

void clearSystem     ( void ) ;
void welcomeMessage  ( void ) ;
void printWarning    ( int  ) ;
void welcomeUtility  ( void ) ;
void goodByeMessage  ( void ) ;


int main(int argc , char *argv[]){

    clearSystem(); // clear the screen 

    welcomeMessage(); 

    return 0;
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

void welcomeMessage( void ) {

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
                // play ( )
                wrongChoice = 0;

                break;

            case 2:

                // Manual ( ) 
                wrongChoice = 0;

                break;

            case 3:

                // Developer Info
                wrongChoice = 0;

                break;

            case 4:

                return ;

            default:
                isWrongChoice = true;
    //            std::cout<<" Incorrect Type/Choice !! ";
        }

        wrongChoice += isWrongChoice;

        if( wrongChoice == MAX_WRONG_CHOICE ) {
            goodByeMessage();
            exit(0);
        }

        if(isWrongChoice == true){

            printWarning( MAX_WRONG_CHOICE - wrongChoice );

        }
    }

    return;
}
