#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include "raylib.h"

using namespace std;
using namespace chrono;

int accuracy1 = 0, wpm1 = 0;
int accuracy2 = 0, wpm2 = 0;
int accuracy3 = 0, wpm3 = 0;
int accuracy4 = 0, wpm4 = 0;

bool close = false;

void TitleScreen(Music &titleMusic);
void Menu(Music &titleMusic);
void level1(Music &titleMusic);
void level2(Music &titleMusic);
void level3(Music &titleMusic);
void level4(Music &titleMusic);
void ending(Music &titleMusic);

static float height = 800;
static float width = 1370;

class Game;

class button_textures
{
protected:
    Texture2D restartbuttonTexture;
    Texture2D returnbuttonTexture;

public:
    inline void loadbutton()
    {
        restartbuttonTexture = LoadTexture("img/restart.png");
        returnbuttonTexture = LoadTexture("img/return.png");
    }
};

class Game : public button_textures
{
private:
    Texture2D buttonTexture;

public:
    void settexture1()
    {
        buttonTexture = LoadTexture("img/button.png");
    }
    void TitleScreen(Music &titleMusic);
    void Menu(Music &titleMusic);
    void level1(Music &titleMusic);
    void level2(Music &titleMusic);
    void level3(Music &titleMusic);
    void level4(Music &titleMusic);
    void ending(Music &titleMusic);
};

int main()
{
    Game game;
    InitWindow(width, height, "Alphabet");
    InitAudioDevice();
    SetTargetFPS(60);
    Image icon = LoadImage("img/icon.ico");
    Music titleMusic = LoadMusicStream("audio/menu.mp3");
    SetWindowIcon(icon);
    while (!WindowShouldClose() && !close)
    {
        game.TitleScreen(titleMusic);
        game.Menu(titleMusic);
    }

    UnloadMusicStream(titleMusic);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void Game ::Menu(Music &titleMusic)
{
    Texture2D overlay1 = LoadTexture("img/background7.png");
    Texture2D buttonTexture = LoadTexture("img/button.png");
    Texture2D exitbuttonTexture = LoadTexture("img/exit.png");

    int adjustment = 90;
    Rectangle button1 = {280, 290, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};
    Rectangle button2 = {575, 580, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};
    Rectangle button3 = {930, 300, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};
    Rectangle button4 = {627, 200, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};
    Rectangle button5 = {1200, 650, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};

    bool button1Hovered = false;
    bool button1Clicked = false;
    bool button2Hovered = false;
    bool button2Clicked = false;
    bool button3Hovered = false;
    bool button3Clicked = false;
    bool button4Hovered = false;
    bool button4Clicked = false;
    bool button5Hovered = false;
    bool button5Clicked = false;

    PlayMusicStream(titleMusic);

    while (!WindowShouldClose() && !button1Clicked && !button2Clicked && !button3Clicked && !button4Clicked && !button5Clicked)
    {
        Vector2 mousePoint = GetMousePosition();
        button1Hovered = CheckCollisionPointRec(mousePoint, button1);
        button2Hovered = CheckCollisionPointRec(mousePoint, button2);
        button3Hovered = CheckCollisionPointRec(mousePoint, button3);
        button4Hovered = CheckCollisionPointRec(mousePoint, button4);
        button5Hovered = CheckCollisionPointRec(mousePoint, button5);

        if (button1Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            button1Clicked = true;
        }
        if (button2Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && wpm1 >= 15 && accuracy1 >= 50)
        {
            button2Clicked = true;
        }
        if (button3Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && wpm2 >= 20 && accuracy2 >= 50)
        {
            button3Clicked = true;
        }
        if (button4Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && wpm3 >= 25 && accuracy3 >= 50)
        {
            button4Clicked = true;
        }
        if (button5Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            button5Clicked = true;
        }

        UpdateMusicStream(titleMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 position = {0.0f, 0.0f};
        float scale = 0.5f;
        DrawTextureEx(overlay1, position, 0.0f, scale, WHITE);

        float button1Scale = button1Hovered ? 0.35f : 0.3f;
        Vector2 button1Position = {260, 365};
        DrawTextureEx(buttonTexture, button1Position, 0.0f, button1Scale, WHITE);

        if (wpm1 >= 15 && accuracy1 >= 50)
        {
            float button2Scale = button2Hovered ? 0.35f : 0.3f;
            Vector2 button2Position = {580, 590};
            DrawTextureEx(buttonTexture, button2Position, 0.0f, button2Scale, WHITE);
        }

        if (wpm2 >= 20 && accuracy2 >= 50)
        {
            float button3Scale = button3Hovered ? 0.35f : 0.3f;
            Vector2 button3Position = {980, 365};
            DrawTextureEx(buttonTexture, button3Position, 0.0f, button3Scale, WHITE);
        }
        if (wpm3 >= 25 && accuracy3 >= 50)
        {
            float button4Scale = button4Hovered ? 0.35f : 0.3f;
            Vector2 button4Position = {677, 240};
            DrawTextureEx(buttonTexture, button4Position, 0.0f, button4Scale, WHITE);
        }

        float button5Scale = button5Hovered ? 0.35f : 0.3f;
        Vector2 button5Position = {1200, 650};
        DrawTextureEx(exitbuttonTexture, button5Position, 0.0f, button5Scale, WHITE);

        EndDrawing();
    }

    UnloadTexture(exitbuttonTexture);
    UnloadTexture(buttonTexture);
    UnloadTexture(overlay1);

    if (button1Clicked)
    {
        level1(titleMusic);
    }
    else if (button2Clicked)
    {
        level2(titleMusic);
    }
    else if (button3Clicked)
    {
        level3(titleMusic);
    }
    else if (button4Clicked)
    {
        level4(titleMusic);
    }
    else if (button5Clicked)
    {
        close = true;
    }
}

void Game ::TitleScreen(Music &titleMusic)
{
    Font font = GetFontDefault();
    Texture2D overlay1 = LoadTexture("img/background.png");
    settexture1();
    Rectangle button = {585, 450, (float)buttonTexture.width, (float)buttonTexture.height};

    bool buttonHovered = false;
    bool buttonClicked = false;

    PlayMusicStream(titleMusic);

    while (!WindowShouldClose() && !buttonClicked)
    {
        Vector2 mousePoint = GetMousePosition();
        buttonHovered = CheckCollisionPointRec(mousePoint, button);

        if (buttonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            buttonClicked = true;
        }

        UpdateMusicStream(titleMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 position = {0.0f, 0.0f};
        float scale = 0.5f;
        DrawTextureEx(overlay1, position, 0.0f, scale, WHITE);

        float buttonScale = buttonHovered ? 0.55f : 0.5f;
        Vector2 buttonPosition = {button.x - (buttonScale - 1.0f) * button.width / 2,
                                  button.y - (buttonScale - 1.0f) * button.height / 2};
        DrawTextureEx(buttonTexture, buttonPosition, 0.0f, buttonScale, WHITE);

        EndDrawing();
    }

    UnloadFont(font);
    UnloadTexture(overlay1);
    UnloadTexture(buttonTexture);
}

void Game ::level1(Music &titleMusic)
{
    loadbutton();

    const string sentence = "A Quick Brown Fox Jumps Over the lazy Dog ONce Again";
    Font font = LoadFont("resources/arial.ttf");
    Texture2D overlay3 = LoadTexture("img/background11.png");
    Texture2D buttonTexture = LoadTexture("img/button.png");
    Music music = LoadMusicStream("audio/first.mp3");

    PlayMusicStream(music);

    string userInput;
    bool typingFinished = false;
    bool returnClicked = false;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();

    auto countWords = [](const string &str)
    {
        int count = 0;
        bool inSpaces = true;
        for (char ch : str)
        {
            if (isspace(ch))
            {
                inSpaces = true;
            }
            else
            {
                if (inSpaces)
                {
                    count++;
                    inSpaces = false;
                }
            }
        }
        return count;
    };

    auto calculateAccuracy = [](const string &userInput, const string &sentence)
    {
        int correctChars = 0;
        int maxChars = min(static_cast<int>(userInput.length()), static_cast<int>(sentence.length()));

        for (int i = 0; i < maxChars; ++i)
        {
            if (userInput[i] == sentence[i])
            {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
                correctChars++;
            }
        }

        return (correctChars / static_cast<double>(sentence.length())) * 100.0;
    };

    while (!WindowShouldClose() && !returnClicked)
    {
        UpdateMusicStream(music);

        if (!typingFinished)
        {
            int key = GetCharPressed();
            if (key >= 32 && key <= 126)
            {
                userInput += static_cast<char>(key);
            }
            else if (IsKeyPressed(KEY_BACKSPACE) && !userInput.empty())
            {
                userInput.pop_back();
            }
            else if (IsKeyPressed(KEY_ENTER))
            {
                typingFinished = true;
                stop = high_resolution_clock::now();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 position = {0.0f, 0.0f};
        float scale = 0.5f;
        DrawTextureEx(overlay3, position, 0.0f, scale, WHITE);

        DrawText(sentence.c_str(), 300, 150, 28, BROWN);
        DrawText(userInput.c_str(), 300, 250, 28, BLACK);

        int adjustment = 150;
        Rectangle restartButton = {1200, 650, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};
        Rectangle menuButton = {100, 100, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};

        bool restartButtonHovered = CheckCollisionPointRec(GetMousePosition(), restartButton);
        bool menuButtonHovered = CheckCollisionPointRec(GetMousePosition(), menuButton);

        float restartButtonScale = restartButtonHovered ? 0.35f : 0.3f;
        float menuButtonScale = menuButtonHovered ? 0.35f : 0.3f;

        DrawTextureEx(restartbuttonTexture, {restartButton.x, restartButton.y}, 0.0f, restartButtonScale, WHITE);
        DrawTextureEx(returnbuttonTexture, {menuButton.x, menuButton.y}, 0.0f, menuButtonScale, WHITE);

        if (restartButtonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            userInput.clear();
            typingFinished = false;
            start = high_resolution_clock::now();
        }
        else if (menuButtonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            returnClicked = true;
        }
        if (typingFinished)
        {
            auto duration = duration_cast<seconds>(stop - start).count();
            double accuracy = calculateAccuracy(userInput, sentence);
            int wordCount = countWords(sentence);
            double wordsPerMinute = (wordCount / (double)duration) * 60;

            if (duration < 5)
            {
                wordsPerMinute = 0;
            }

            DrawText("Typing Test Complete!", 500, 440, 30, RED);
            DrawText(TextFormat("Time taken: %lld seconds", duration), 350, 550, 30, BLACK);
            DrawText(TextFormat("Accuracy: %.2f%%", accuracy), 350, 600, 30, BLACK);
            DrawText(TextFormat("Typing Speed: %.2f words per minute", wordsPerMinute), 350, 650, 30, BLACK);

            accuracy1 = accuracy;
            wpm1 = wordsPerMinute;
        }

        EndDrawing();
    }

    StopMusicStream(music);
    UnloadMusicStream(music);
    UnloadFont(font);
    UnloadTexture(overlay3);
    UnloadTexture(buttonTexture);
    UnloadTexture(restartbuttonTexture);
    UnloadTexture(returnbuttonTexture);

    if (returnClicked)
    {
        Menu(titleMusic);
    }
}

void Game ::level2(Music &titleMusic)
{
    loadbutton();

    const string sentence = "Typing is @n EssenTi@l Skill in the Digital Age We Live I^";
    Font font = LoadFont("resources/arial.ttf");
    Texture2D overlay3 = LoadTexture("img/background10.png");
    Texture2D buttonTexture = LoadTexture("img/button.png");
    Music music = LoadMusicStream("audio/second.mp3");

    PlayMusicStream(music);

    string userInput;
    bool typingFinished = false;
    bool returnClicked = false;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();

    auto countWords = [](const string &str)
    {
        int count = 0;
        bool inSpaces = true;
        for (char ch : str)
        {
            if (isspace(ch))
            {
                inSpaces = true;
            }
            else
            {
                if (inSpaces)
                {
                    count++;
                    inSpaces = false;
                }
            }
        }
        return count;
    };

    auto calculateAccuracy = [](const string &userInput, const string &sentence)
    {
        int correctChars = 0;
        int maxChars = min(static_cast<int>(userInput.length()), static_cast<int>(sentence.length()));

        for (int i = 0; i < maxChars; ++i)
        {
            if (userInput[i] == sentence[i])
            {
                correctChars++;
            }
        }

        return (correctChars / static_cast<double>(sentence.length())) * 100.0;
    };

    while (!WindowShouldClose() && !returnClicked)
    {
        UpdateMusicStream(music);

        if (!typingFinished)
        {
            int key = GetCharPressed();
            if (key >= 32 && key <= 126)
            {
                userInput += static_cast<char>(key);
            }
            else if (IsKeyPressed(KEY_BACKSPACE) && !userInput.empty())
            {
                userInput.pop_back();
            }
            else if (IsKeyPressed(KEY_ENTER))
            {
                typingFinished = true;
                stop = high_resolution_clock::now();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 position = {0.0f, 0.0f};
        float scale = 0.5f;
        DrawTextureEx(overlay3, position, 0.0f, scale, WHITE);

        DrawText(sentence.c_str(), 300, 150, 28, BROWN);
        DrawText(userInput.c_str(), 300, 250, 28, BLACK);

        int adjustment = 150;
        Rectangle restartButton = {1200, 650, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};
        Rectangle menuButton = {100, 100, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};

        bool restartButtonHovered = CheckCollisionPointRec(GetMousePosition(), restartButton);
        bool menuButtonHovered = CheckCollisionPointRec(GetMousePosition(), menuButton);

        float restartButtonScale = restartButtonHovered ? 0.35f : 0.3f;
        float menuButtonScale = menuButtonHovered ? 0.35f : 0.3f;

        DrawTextureEx(restartbuttonTexture, {restartButton.x, restartButton.y}, 0.0f, restartButtonScale, WHITE);
        DrawTextureEx(returnbuttonTexture, {menuButton.x, menuButton.y}, 0.0f, menuButtonScale, WHITE);

        if (restartButtonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            userInput.clear();
            typingFinished = false;
            start = high_resolution_clock::now();
        }
        else if (menuButtonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            returnClicked = true;
        }

        if (typingFinished)
        {
            auto duration = duration_cast<seconds>(stop - start).count();
            double accuracy = calculateAccuracy(userInput, sentence);
            int wordCount = countWords(sentence);
            double wordsPerMinute = (wordCount / (double)duration) * 60;

            if (duration < 5)
            {
                wordsPerMinute = 0;
            }

            DrawText("Typing Test Complete!", 500, 440, 30, RED);
            DrawText(TextFormat("Time taken: %lld seconds", duration), 350, 550, 30, BLACK);
            DrawText(TextFormat("Accuracy: %.2f%%", accuracy), 350, 600, 30, BLACK);
            DrawText(TextFormat("Typing Speed: %.2f words per minute", wordsPerMinute), 350, 650, 30, BLACK);

            accuracy2 = accuracy;
            wpm2 = wordsPerMinute;
        }

        EndDrawing();
    }

    StopMusicStream(music);
    UnloadMusicStream(music);
    UnloadFont(font);
    UnloadTexture(overlay3);
    UnloadTexture(buttonTexture);
    UnloadTexture(restartbuttonTexture);
    UnloadTexture(returnbuttonTexture);

    if (returnClicked)
    {
        Menu(titleMusic);
    }
}

void Game ::level3(Music &titleMusic)
{
    loadbutton();

    const string sentence = "$He s3lls sea$hells bY! the sEaShOr3 of s0mE !sl@nD*s";
    Font font = LoadFont("resources/arial.ttf");
    Texture2D overlay3 = LoadTexture("img/background9.png");
    Texture2D buttonTexture = LoadTexture("img/button.png");
    Music music = LoadMusicStream("audio/third.mp3");

    PlayMusicStream(music);

    string userInput;
    bool typingFinished = false;
    bool returnClicked = false;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();

    auto countWords = [](const string &str)
    {
        int count = 0;
        bool inSpaces = true;
        for (char ch : str)
        {
            if (isspace(ch))
            {
                inSpaces = true;
            }
            else
            {
                if (inSpaces)
                {
                    count++;
                    inSpaces = false;
                }
            }
        }
        return count;
    };

    auto calculateAccuracy = [](const string &userInput, const string &sentence)
    {
        int correctChars = 0;
        int maxChars = min(static_cast<int>(userInput.length()), static_cast<int>(sentence.length()));

        for (int i = 0; i < maxChars; ++i)
        {
            if (userInput[i] == sentence[i])
            {
                correctChars++;
            }
        }

        return (correctChars / static_cast<double>(sentence.length())) * 100.0;
    };

    while (!WindowShouldClose() && !returnClicked)
    {
        UpdateMusicStream(music);

        if (!typingFinished)
        {
            int key = GetCharPressed();
            if (key >= 32 && key <= 126)
            {
                userInput += static_cast<char>(key);
            }
            else if (IsKeyPressed(KEY_BACKSPACE) && !userInput.empty())
            {
                userInput.pop_back();
            }
            else if (IsKeyPressed(KEY_ENTER))
            {
                typingFinished = true;
                stop = high_resolution_clock::now();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 position = {0.0f, 0.0f};
        float scale = 0.5f;
        DrawTextureEx(overlay3, position, 0.0f, scale, WHITE);

        DrawText(sentence.c_str(), 300, 150, 28, BROWN);
        DrawText(userInput.c_str(), 300, 250, 28, BLACK);

        int adjustment = 150;
        Rectangle restartButton = {1200, 650, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};
        Rectangle menuButton = {100, 100, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};

        bool restartButtonHovered = CheckCollisionPointRec(GetMousePosition(), restartButton);
        bool menuButtonHovered = CheckCollisionPointRec(GetMousePosition(), menuButton);

        float restartButtonScale = restartButtonHovered ? 0.35f : 0.3f;
        float menuButtonScale = menuButtonHovered ? 0.35f : 0.3f;

        DrawTextureEx(restartbuttonTexture, {restartButton.x, restartButton.y}, 0.0f, restartButtonScale, WHITE);
        DrawTextureEx(returnbuttonTexture, {menuButton.x, menuButton.y}, 0.0f, menuButtonScale, WHITE);

        if (restartButtonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            userInput.clear();
            typingFinished = false;
            start = high_resolution_clock::now();
        }
        else if (menuButtonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            returnClicked = true;
        }

        if (typingFinished)
        {
            auto duration = duration_cast<seconds>(stop - start).count();
            double accuracy = calculateAccuracy(userInput, sentence);
            int wordCount = countWords(sentence);
            double wordsPerMinute = (wordCount / (double)duration) * 60;

            if (duration < 5)
            {
                wordsPerMinute = 0;
            }

            DrawText("Typing Test Complete!", 500, 440, 30, RED);
            DrawText(TextFormat("Time taken: %lld seconds", duration), 350, 550, 30, BLACK);
            DrawText(TextFormat("Accuracy: %.2f%%", accuracy), 350, 600, 30, BLACK);
            DrawText(TextFormat("Typing Speed: %.2f words per minute", wordsPerMinute), 350, 650, 30, BLACK);

            accuracy3 = accuracy;
            wpm3 = wordsPerMinute;
        }

        EndDrawing();
    }

    StopMusicStream(music);
    UnloadMusicStream(music);
    UnloadFont(font);
    UnloadTexture(overlay3);
    UnloadTexture(buttonTexture);
    UnloadTexture(restartbuttonTexture);
    UnloadTexture(returnbuttonTexture);

    if (returnClicked)
    {
        Menu(titleMusic);
    }
}

void Game ::level4(Music &titleMusic)
{
    loadbutton();

    const string sentence = "! @m r3aLly N0t g0nNa l!e,-->TH!s Ls q*ite% (a h@rd )0ne";
    Font font = LoadFont("resources/arial.ttf");
    Texture2D overlay3 = LoadTexture("img/background13.png");
    Texture2D buttonTexture = LoadTexture("img/button.png");
    Music music = LoadMusicStream("audio/fourth.mp3");

    PlayMusicStream(music);

    string userInput;
    bool typingFinished = false;
    bool returnClicked = false;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();

    auto countWords = [](const string &str)
    {
        int count = 0;
        bool inSpaces = true;
        for (char ch : str)
        {
            if (isspace(ch))
            {
                inSpaces = true;
            }
            else
            {
                if (inSpaces)
                {
                    count++;
                    inSpaces = false;
                }
            }
        }
        return count;
    };

    auto calculateAccuracy = [](const string &userInput, const string &sentence)
    {
        int correctChars = 0;
        int maxChars = min(static_cast<int>(userInput.length()), static_cast<int>(sentence.length()));

        for (int i = 0; i < maxChars; ++i)
        {
            if (userInput[i] == sentence[i])
            {
                correctChars++;
            }
        }

        return (correctChars / static_cast<double>(sentence.length())) * 100.0;
    };

    while (!WindowShouldClose() && !returnClicked)
    {
        UpdateMusicStream(music);

        if (!typingFinished)
        {
            int key = GetCharPressed();
            if (key >= 32 && key <= 126)
            {
                userInput += static_cast<char>(key);
            }
            else if (IsKeyPressed(KEY_BACKSPACE) && !userInput.empty())
            {
                userInput.pop_back();
            }
            else if (IsKeyPressed(KEY_ENTER))
            {
                typingFinished = true;
                stop = high_resolution_clock::now();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 position = {0.0f, 0.0f};
        float scale = 0.5f;
        DrawTextureEx(overlay3, position, 0.0f, scale, WHITE);

        DrawText(sentence.c_str(), 300, 150, 28, BROWN);
        DrawText(userInput.c_str(), 300, 250, 28, BLACK);

        int adjustment = 150;
        Rectangle restartButton = {1200, 650, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};
        Rectangle menuButton = {100, 100, (float)buttonTexture.width - adjustment, (float)buttonTexture.height - adjustment};

        bool restartButtonHovered = CheckCollisionPointRec(GetMousePosition(), restartButton);
        bool menuButtonHovered = CheckCollisionPointRec(GetMousePosition(), menuButton);

        float restartButtonScale = restartButtonHovered ? 0.35f : 0.3f;
        float menuButtonScale = menuButtonHovered ? 0.35f : 0.3f;

        DrawTextureEx(restartbuttonTexture, {restartButton.x, restartButton.y}, 0.0f, restartButtonScale, WHITE);
        DrawTextureEx(returnbuttonTexture, {menuButton.x, menuButton.y}, 0.0f, menuButtonScale, WHITE);

        if (restartButtonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            userInput.clear();
            typingFinished = false;
            start = high_resolution_clock::now();
        }
        else if (menuButtonHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            returnClicked = true;
        }
        if (typingFinished)
        {
            auto duration = duration_cast<seconds>(stop - start).count();
            double accuracy = calculateAccuracy(userInput, sentence);
            int wordCount = countWords(sentence);
            double wordsPerMinute = (wordCount / (double)duration) * 60;

            if (duration < 5)
            {
                wordsPerMinute = 0;
            }

            DrawText("Typing Test Complete!", 500, 440, 30, RED);
            DrawText(TextFormat("Time taken: %lld seconds", duration), 350, 550, 30, BLACK);
            DrawText(TextFormat("Accuracy: %.2f%%", accuracy), 350, 600, 30, BLACK);
            DrawText(TextFormat("Typing Speed: %.2f words per minute", wordsPerMinute), 350, 650, 30, BLACK);

            accuracy4 = accuracy;
            wpm4 = wordsPerMinute;
        }

        EndDrawing();
    }

    StopMusicStream(music);
    UnloadMusicStream(music);
    UnloadFont(font);
    UnloadTexture(overlay3);
    UnloadTexture(buttonTexture);
    UnloadTexture(restartbuttonTexture);
    UnloadTexture(returnbuttonTexture);

    if (returnClicked)
    {
        if (wpm4 >= 30 && accuracy4 >= 50)
        {
            ending(titleMusic);
        }
        else
        {
            Menu(titleMusic);
        }
    }
}

void Game ::ending(Music &titleMusic)
{
    Texture2D endOverlay = LoadTexture("img/final.png");
    Vector2 position = {0.0f, 0.0f};
    float scale = 0.5f;

    PlayMusicStream(titleMusic);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(titleMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextureEx(endOverlay, position, 0.0f, scale, WHITE);

        EndDrawing();
    }

    UnloadTexture(endOverlay);
}
