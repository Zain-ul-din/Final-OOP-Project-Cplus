/*
   @open Source
     Tic Tac Toc Game in c++
     -- MIT License
*/

#include <iostream> // std io
#include <string> // std string
#include <vector> // std vector
#include <algorithm> // c build in algo's
#include <cmath> // math stuff
#include <windows.h> // windows apis like, keyboard btn click
#include <conio.h> // get char
#include <thread> // cplus 11 multi threading and thread sleep
#include <chrono> // cplus system time
#include <functional> // cplus 11 functions

#define DEFAULT_BOX '-'
#define PLAYER1_BOX 'X'
#define PLAYER2_BOX 'O'
#define CURSOR '^'
#define _CH_ getch();

void clearScreen();
void set_cursor(bool);
template < class returnType, class...EventHandler > class Event; // @Helper
class InputManager;
class GameRenderer;
class GameManager;

#define CLS clearScreen();
// Player Turn State
enum class PlayerTurn {
    Player1,
    Player2
};

/*
  @ Custom Event Handler
  -- Triggers Action when some thing happens and have multiple Subs
*/
template < class returnType, class...EventHandler >
    class Event {
        public: Event() {}

        void operator += (std:: function < returnType(EventHandler...) > e) {
            eArray.push_back(e);
        }

        template < class...Args >
        inline void Invoke(Args & ...argu) const {
            if (eArray.empty()) return;
            for (auto e: eArray) e(argu...);
        }

        private: std::vector < std:: function < returnType(EventHandler...) >> eArray;
 };

/*
  @ Game Renderer
  -- Renderers Game Map , player UI , etc ...
*/
class GameRenderer {
    public: GameRenderer(const int rowSize,
        const int colSize) {
        this -> rowSize = rowSize <= 2 ? 3 : rowSize;
        this -> colSize = colSize <= 2 ? 3 : colSize;

        this -> mapSize = rowSize * colSize;
        this -> currentBoxIdx = 0; // sets to start

        for (int i = 0; i < this -> mapSize; i += 1)
            arr.push_back(DEFAULT_BOX);

        p1 = "Player1";
        p2 = "Player2";
    }

    void Render(int cursorPos, PlayerTurn playerTurn = PlayerTurn::Player1) {
        std::cout << "\n\t\t -- TIC TAC TOE GAME --- \t\t\n";
        std::cout << (playerTurn == PlayerTurn::Player1 ? " @ " + p1 + " TURN " : " @ " + p2 + " TURN ");
        std::cout << "\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "\t";
        for (int i = 0; i < this -> mapSize; i += 1) {
            if (i % rowSize == 0)
                std::cout << "\n";
            std::cout << "\t" << ((cursorPos == i) ? CURSOR : arr[i]) << "\t";
        }
        std::cout << "\t";
        this -> currentBoxIdx = cursorPos;
        std::cout << "\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "\nMove Up Down Left Right Key's Press Enter to fill the Box \n";
    }

    void Set_Box(PlayerTurn turnState, int idx) {
        idx = abs(idx);
        if (idx >= arr.size() || !IsEmptyBox(idx))
            return;
        arr[idx] = (turnState == PlayerTurn::Player1) ? PLAYER1_BOX : PLAYER2_BOX;
    }

    int GetCurrentBoxIdx() const {
        return this -> currentBoxIdx;
    }

    bool IsEmptyBox(int idx) {
        return arr[idx] != PLAYER1_BOX && arr[idx] != PLAYER2_BOX;
    }

    int GetIdxOfEmptyBox() {
        for (int i = 0; i < arr.size(); i += 1)
            if (IsEmptyBox(i))
                return i;
        return 0; // prevent err		      
    }

    // Finds Closest Idx under cursor
    int GetLowerClosestIdx(const int idx) {
        if (idx + colSize >= mapSize) return idx; // invalid Idx

        if (IsEmptyBox(idx + colSize))
            return idx + colSize;

        for (int auxiliaryIdx = idx + colSize; auxiliaryIdx < mapSize; auxiliaryIdx += colSize)
            if (IsEmptyBox(auxiliaryIdx))
                return auxiliaryIdx;

        return idx; // prevent err     
    }

    // Finds Closest Idx on the top of cursor
    int GetClosestIdxOnTop(const int idx) {
        if (idx - colSize < 0) return idx;

        if (IsEmptyBox(idx - colSize)) return idx - colSize;

        for (int auxiliaryIdx = idx - colSize; auxiliaryIdx >= 0; auxiliaryIdx -= colSize)
            if (IsEmptyBox(auxiliaryIdx))
                return auxiliaryIdx;

        return idx;
    }

    bool GetWinner(PlayerTurn currentState, bool getRes = false) {
        std::cout << "\n\n";
        const std::string PLAYER_NAME = currentState == PlayerTurn::Player1 ? this -> p1 : this -> p2;
        #define WINTEXT CLS std::cout << "\t\t Result :  " << PLAYER_NAME << " WON !! \n";
        const char COMPARE_CHAR = currentState == PlayerTurn::Player1 ? PLAYER1_BOX : PLAYER2_BOX;

        // Horizontal Check 

        std::vector < char > hFlag;
        int _colSize = colSize;

        for (int i = 0; i < arr.size(); i += 1) {
            hFlag.push_back(arr[i]);

            if (i == _colSize - 1) {
                if (std::all_of(hFlag.begin(), hFlag.end(), [ & ](char box) {
                        return box == COMPARE_CHAR;
                    })) {
                    WINTEXT
                    return false;
                }
                hFlag.clear();
                _colSize += colSize;
            }
        }

        // Vertical Check

        for (int i = 0; i < colSize; i += 1) {
            std::vector < char > vFlag;
            int idx = i;
            do {
                vFlag.push_back(arr[idx]);
                idx += colSize;
            } while (idx < arr.size());

            if (std::all_of(vFlag.begin(), vFlag.end(), [ & ](char box) {
                    return box == COMPARE_CHAR;
                })) {
                WINTEXT
                return false;
            }
        }

        // Diaglonal Check

        int dIdx = 0;
        std::vector < char > dFlag;
        _colSize = colSize;
        for (int i = 0; i < arr.size(); i += 1) {
            if (i == dIdx)
                dFlag.push_back(arr[i]);
            if (i == _colSize - 1) {
                dIdx += 1;
                dIdx += colSize;
                _colSize += colSize;
            }
        }

        if (std::all_of(dFlag.begin(), dFlag.end(), [ & ](char box) {
                return box == COMPARE_CHAR;
            }) && dFlag.size() == rowSize) {
            WINTEXT
            return false;
        }

        dIdx = colSize - 1;
        dFlag.clear();
        _colSize = colSize;

        for (int i = 0; i < arr.size(); i += 1) {
            if (i == dIdx)
                dFlag.push_back(arr[i]);
            if (i == _colSize - 1) {
                _colSize += colSize;
                dIdx -= 1;
                dIdx += colSize;
            }
        }

        if (std::all_of(dFlag.begin(), dFlag.end(), [ & ](char box) {
                return box == COMPARE_CHAR;
            }) && dFlag.size() == rowSize) {
            WINTEXT
            return false;
        }

        for (int i = 0; i < arr.size(); i += 1)
            if (IsEmptyBox(i)) return true; // for tick flag

        if (getRes) getch();
        CLS std::cout << "\t Result : Tie :-( \n";
        return false;
        #undef WINTEXT
    }

    void SetPlayers(std::string p1, std::string p2) {
        this -> p1 = p1;
        this -> p2 = p2;
    }

    private: std::string p1,
    p2; // players
    std::vector < char > arr;
    int mapSize,
    rowSize,
    colSize;
    int currentBoxIdx;
};

/*
   SINGLETON CLASS 
   @ handles  game input
   -> UP , DOWN , LEFT , RIGHT , ENTER => KEY Binding
*/
class InputManager {
    public: static InputManager * _Instance() {
        if (instance)
            return instance;

        instance = new InputManager();
        return instance;
    }

    void ListenToKeys() {
        while (true) {
            if (!tick) {
                getch();
                system("cls");
                std::cout << "\n\t\t== GAME OVER ==\n";
                return;
            }
            _CH_
            // @firing Events
            LISTEN_KEY(VK_UP, [ & ]() {
                OnUpBtnPressed.Invoke();
            });
            LISTEN_KEY(VK_DOWN, [ & ]() {
                OnDownBtnPressed.Invoke();
            });
            LISTEN_KEY(VK_LEFT, [ & ]() {
                OnLeftBtnPressed.Invoke();
            });
            LISTEN_KEY(VK_RIGHT, [ & ]() {
                OnRightBtnPressed.Invoke();
            });

            LISTEN_KEY(VK_RETURN, [ & ]() {
                OnEnterBtnPressed.Invoke();
            });

            std::this_thread::sleep_for(std::chrono::milliseconds(150)); // next action trigger delay
        }
    }

    /*
    
       Btn Click Events
    */
    Event < void > OnUpBtnPressed;
    Event < void > OnDownBtnPressed;
    Event < void > OnLeftBtnPressed;
    Event < void > OnRightBtnPressed;
    Event < void > OnEnterBtnPressed;

    void SetTick(bool state) {
        this -> tick = state;
    } // if false this will not listen for inputs anymore

    private: InputManager() {
        tick = true;
    }
    static InputManager * instance;
    ~InputManager() {
        delete instance;
    }
    bool tick;
    template < class CallBack >
    void LISTEN_KEY(int key, CallBack callBack) {
        if (GetAsyncKeyState(key) < 0) callBack();
    }

};

InputManager * InputManager::instance = nullptr;

/*
  SINGLETON CLASS
  @ handles Game State 
  -> score , playersState etc..
*/
class GameManager {
    public: static GameManager * _Instance() {
        if (instance)
            return instance;

        instance = new GameManager();
        return instance;
    }

    void InitGame() {
        player1 = GetString(">> Enter Player 1 Name : ");
        player2 = GetString(">> Enter Player 2 Name : ");
        system("cls");
    }

    void StartGame() {
        #define ROW_SIZE 3
        #define COL_SIZE 3
        set_cursor(false);
        GameRenderer gameRenderer(ROW_SIZE, COL_SIZE);
        PlayerTurn playerTurnState = PlayerTurn::Player1;
        gameRenderer.SetPlayers(this -> player1, this -> player2);
        #define RE_RENDER CLS gameRenderer.Render(idx, playerTurnState);
        int idx = gameRenderer.GetCurrentBoxIdx(); // game cursor idx
        RE_RENDER
        const int MAPSIZE = ROW_SIZE * COL_SIZE;
        #define IM InputManager::_Instance()
        // Input Manager Event Sub

        //@ Up Key
        IM -> OnUpBtnPressed += [ & ]() {
            if (idx - ROW_SIZE < 0)
                return;
            FindEmptyBox(gameRenderer, idx, [ & ]() {
                idx = gameRenderer.GetClosestIdxOnTop(idx);
            });

            RE_RENDER
        };

        //@ Down Key
        IM -> OnDownBtnPressed += [ & ]() {
            if (idx + COL_SIZE >= MAPSIZE)
                return;
            FindEmptyBox(gameRenderer, idx, [ & ]() {
                idx = gameRenderer.GetLowerClosestIdx(idx);
            });

            RE_RENDER
        };

        //@ Left Key
        IM -> OnLeftBtnPressed += [ & ]() {
            FindEmptyBox(gameRenderer, idx, [ & ]() {
                idx -= 1;
                idx = idx < 0 ? MAPSIZE - 1 : idx;
            });

            RE_RENDER
        };

        //@ Right Key
        IM -> OnRightBtnPressed += [ & ]() {
            FindEmptyBox(gameRenderer, idx, [ & ]() {
                idx += 1;
                idx %= MAPSIZE;
            });

            RE_RENDER
        };

        //@ Enter Key
        IM -> OnEnterBtnPressed += [ & ]() {
            gameRenderer.Set_Box(playerTurnState, idx);
            idx = gameRenderer.GetIdxOfEmptyBox();
            auto prevState = playerTurnState;
            if (!gameRenderer.GetWinner(prevState))
                idx = MAPSIZE;
            playerTurnState = (playerTurnState == PlayerTurn::Player1) ?
                PlayerTurn::Player2 : PlayerTurn::Player1; // Turn State toggler
            RE_RENDER
            IM -> SetTick(gameRenderer.GetWinner(prevState, true));
        };

        // !! Do Sub before Listen
        IM -> ListenToKeys();
        #undef IM
        #undef ROW_SIZE
        #undef COL_SIZE
        #undef RE_RENDER
    }
    private: GameManager() {
        this -> player1 = "X";
        this -> player2 = "Y";
    }

    static GameManager * instance;
    std::string player1,
    player2;

    static std::string GetString(const char msg[]) {
        std::string ss;
        std::cout << msg;
        std::cin.sync();
        std::getline(std::cin, ss);
        return ss;
    }

    template < class CallBack >
    void FindEmptyBox(GameRenderer & gameRenderer, int & idx, CallBack callBack) {
        do callBack();
        while (!gameRenderer.IsEmptyBox(idx));
    }
    ~GameManager() {
        delete instance;
    }
};

GameManager * GameManager::instance = nullptr;
#define GAME GameManager::_Instance()

// Driver Code
int main() {
    GAME -> InitGame();
    GAME -> StartGame();
}
#undef GAME
#undef CLS

void clearScreen() {
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void set_cursor(bool visible) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & info);
}
