#include <stdio.h>
#include "../lib/raylib.h"

#define PLAYER_HDR_SPD 200.0f
#define PLAYER_JUMP_SPD 350.0f

typedef struct {
    Vector2 position;
    float speed;
    bool canJump;
} Player;

void updatePlayer(Player *player, float delta) {
    if (IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HDR_SPD * delta;
    if (IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HDR_SPD * delta;

    if (IsKeyDown(KEY_SPACE) && player->canJump) {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    /* player->position.y += PLAYER_HDR_SPD * delta; */
}

int main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Raylib Window");

    /* Rectangle player = {50, 50, 100, 100}; */
    Player player = {{50, 50}, 1, true};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // Update
        // --------------------------
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Draw Rectangle first
        Rectangle playerRect = {player.position.x - 20, player.position.y - 40, 40.0f, 40.0f};
        Rectangle floor = {200, screenHeight - 100, screenWidth - 400, 100};

        updatePlayer(&player, deltaTime);
        DrawRectangleRec(playerRect, DARKBROWN);
        DrawRectangleRec(floor, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
