#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
#include <iomanip>
//
//HANDE ALTUNBAS CS204_HW_6 SPRING'24
//
using namespace std;

vector<int> player_scores;
mutex game_mtx;
mutex cout_mtx;

int random_range(const int &min, const int &max)
{
    thread_local mt19937 generator(random_device{}());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void print_current_time()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t itt = chrono::system_clock::to_time_t(now);
    tm tm = *localtime(&itt);
    cout << put_time(&tm, "%H:%M:%S");
}

void host_thread(int roundNum, int lowerRange, int upperRange, bool &roundActive, bool &roundStarted, int &correctGuesser, int &target, bool &gameOver, int playerNum, int &totalCorrectCount, int &localCorrectCount)
{

    cout_mtx.lock();
    cout << endl;
    cout << "\n---------------------------------------------------\n";
    cout << "Game started at: ";
    print_current_time();
    cout << "\nRound 1 will start 3 seconds later\n";
    cout_mtx.unlock();

    this_thread::sleep_for(chrono::seconds(3));


    for (int round = 1; round < roundNum + 1; round++)
    {
        game_mtx.lock();
        localCorrectCount = -1;
        target = random_range(lowerRange, upperRange);
        roundActive = true;
        correctGuesser = -1;
        game_mtx.unlock();

        cout_mtx.lock();
        if (round != 1)
        {
            cout << endl;
            cout << "\n---------------------------------------------------\n";
            cout << "Round " << round << " started at: ";
            print_current_time();
        }
        cout << "\nTarget is " << target ;
        cout << endl;
        cout_mtx.unlock();

        // Signal players that the round has started
        roundStarted = true;

        // Wait for a player to guess the correct number
        while (roundActive)
        {
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        // Announce the winner of the round
        if (correctGuesser != -1)
        {

            cout_mtx.lock();
            player_scores[correctGuesser]++;
            totalCorrectCount += 1;
            cout_mtx.unlock();
        }

        //Wait a moment before starting the next round
        roundStarted = false;
    }

    // Signal game over to all players
    gameOver = true;
    cout << endl;
    cout << "\nGame is over!" << endl;
    cout << "Leaderboard:" << endl;
    for (int i = 0; i < playerNum; ++i)
    {
        cout << "Player " << i << " has won " << player_scores[i] << " times" << endl;
    }
    this_thread::sleep_for(chrono::seconds(1));
}

void player_thread(int player_id, int lowerRange, int upperRange, bool &roundActive, bool &roundStarted, int &correctGuesser, int &target, bool &gameOver, int& totalCorrectCount, int roundNum, int& localCorrectCount)
{
    this_thread::sleep_for(chrono::seconds(3)); // Initial sleep to start all players at the same time

    bool shouldExit = false; // Flag to indicate whether the player thread should exit the loop

    while (totalCorrectCount != roundNum && !shouldExit)
    {
        // Check if the game is over
        game_mtx.lock();
        bool localGameOver = gameOver;
        game_mtx.unlock();

        if (localGameOver)
            shouldExit = true; // Set the flag to exit the loop if the game is over
        else
        {
            // Wait for the round to start
            while (!roundStarted && totalCorrectCount < roundNum)
            {
                this_thread::sleep_for(chrono::milliseconds(100));
            }

            game_mtx.lock();
            int localTarget = target;
            bool localRoundActive = roundActive;
            game_mtx.unlock();

            // Check if the round is still active
            if (localRoundActive && localCorrectCount == -1)
            {
                int guess = random_range(lowerRange, upperRange);

                cout_mtx.lock();
                cout << "\nPlayer with id " << player_id << " guessed " << guess;
                if (guess == localTarget)
                {
                    cout << " correctly at: ";
                    localCorrectCount += 1;
                }
                else
                {
                    cout << " incorrectly at: ";
                }
                print_current_time();
                cout_mtx.unlock();

                if (guess == localTarget)
                {
                    game_mtx.lock();
                    if (localRoundActive)
                    {
                        roundActive = false;
                        correctGuesser = player_id;
                        roundStarted = false; // Stop other players from guessing in this round
                    }
                    game_mtx.unlock();
                }

                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }
}




int main()
{
    int lowerRange, upperRange, playerNum, roundNum;

    cout << "Please enter number of players ";
    cin >> playerNum;
    while (playerNum < 1)
    {
        cout << "Number of players cannot be lower than 1!" << endl;
        cout << "Please enter number of players ";
        cin >> playerNum;
    }

    cout << "Please enter number of rounds ";
    cin >> roundNum;
    while (roundNum < 1)
    {
        cout << "Number of rounds cannot be lower than 1!" << endl;
        cout << "Please enter number of rounds ";
        cin >> roundNum;
    }

    cout << "Please enter the randomization range ";
    cin >> lowerRange >> upperRange;
    while (lowerRange > upperRange)
    {
        cout << "Lower bound has to be smaller than or equal to higher bound" << endl;
        cout << "Please enter the randomization range ";
        cin >> lowerRange >> upperRange;
    }

    player_scores.resize(playerNum, 0);
    bool roundActive = false;
    bool roundStarted = false;
    bool gameOver = false;
    int correctGuesser = -1;
    int totalCorrectCount = 0;
    int localCorrectCount = -1;
    int target = 0;
    thread host(host_thread, roundNum, lowerRange, upperRange, ref(roundActive), ref(roundStarted), ref(correctGuesser), ref(target), ref(gameOver), playerNum, ref(totalCorrectCount), ref(localCorrectCount));

    vector<thread> players;
    for (int i = 0; i < playerNum; ++i)
    {
        players.emplace_back(player_thread, i, lowerRange, upperRange, ref(roundActive), ref(roundStarted), ref(correctGuesser), ref(target), ref(gameOver),ref(totalCorrectCount), roundNum, ref(localCorrectCount));
    }

    host.join();
    for(int i = 0; i < players.size(); ++i)
    {
        players[i].join();
    }

    return 0;
}