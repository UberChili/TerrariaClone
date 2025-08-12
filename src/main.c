#include "../lib/raylib.h"
#include <stdio.h>

#define PLAYER_HDR_SPD 200.0f
#define PLAYER_JUMP_SPD 350.0f

typedef struct {
    Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

/* void updatePlayer(Player *player, float delta) { */
void updatePlayer(Player *player, EnvItem envItems[], size_t envItemsLen,
                  float delta) {
    if (IsKeyDown(KEY_LEFT))
        player->position.x -= PLAYER_HDR_SPD * delta;
    if (IsKeyDown(KEY_RIGHT))
        player->position.x += PLAYER_HDR_SPD * delta;

    if (IsKeyDown(KEY_SPACE) && player->canJump) {
        printf("Jump key pressed!\n");
        player->speed = -PLAYER_JUMP_SPD * delta;
        player->canJump = false;
    }

    for (size_t i = 0; i < envItemsLen; i++) {
        if (CheckCollisionRecs(
                envItems[i].rect,
                (Rectangle){player->position.x, player->position.y})) {
            printf("Some rectangles are touching!\n");
            player->position.y = player->position.y - 3;
            player->canJump = true;
        }
    }

    player->position.y += PLAYER_HDR_SPD * delta;
}

int main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Raylib Window");

    EnvItem envitems[] = {
        {{200, screenHeight - 100, screenWidth - 400, 100},
         0,
         LIGHTGRAY}, // surface
    };

    size_t EnvItemsLen = sizeof(envitems) / sizeof(envitems[0]);

    Player player = {{500, screenHeight - 100}, 2, false};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // Update
        // --------------------------
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Draw environment items
        for (size_t i = 0; i < EnvItemsLen; i++) {
            DrawRectangleRec(envitems[i].rect, envitems[i].color);
        }

        // Draw Rectangle first
        Rectangle playerRect = {player.position.x - 20, player.position.y - 40,
                                40.0f, 40.0f};
        /* Rectangle playerRect = {player.position.x, player.position.y, 40.0f,
         */
        /*                         40.0f}; */

        updatePlayer(&player, envitems, EnvItemsLen, deltaTime);
        DrawRectangleRec(playerRect, YELLOW);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
