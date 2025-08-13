#include "../lib/raylib.h"
#include <stdio.h>

#define G 1400
#define PLAYER_HDR_SPD 400.0f
#define PLAYER_JUMP_SPD 400.0f

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

void updatePlayer(Player *player, EnvItem envItems[], size_t envItemsLen,
                  float delta) {
    if (IsKeyDown(KEY_LEFT))
        player->position.x -= PLAYER_HDR_SPD * delta;
    if (IsKeyDown(KEY_RIGHT))
        player->position.x += PLAYER_HDR_SPD * delta;

    if (IsKeyDown(KEY_SPACE) && player->canJump) {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    bool hitObstacle = false;
    Rectangle playerRect = {player->position.x - 20, player->position.y - 40,
                            40.0f, 40.0f};
    for (size_t i = 0; i < envItemsLen; i++) {
        EnvItem *ei = envItems + i;
        if (ei->blocking && CheckCollisionRecs(playerRect, ei->rect)) {
            hitObstacle = true;
            player->speed = 0.0f;
            player->position.y = ei->rect.y;
            break;
        }
    }

    if (!hitObstacle) {
        player->position.y += player->speed * delta;
        player->speed += G * delta;
        player->canJump = false;
    } else {
        player->canJump = true;
    }
}

int main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Raylib Window");

    Player player = {0};
    player.position = (Vector2){400, 480};
    player.speed = 0;
    player.canJump = false;

    EnvItem envitems[] = {
        {{200, screenHeight - 100, screenWidth - 400, 100},
         1,
         LIGHTGRAY}, // surface
    };

    size_t EnvItemsLen = sizeof(envitems) / sizeof(envitems[0]);

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

        updatePlayer(&player, envitems, EnvItemsLen, deltaTime);
        DrawRectangleRec(playerRect, YELLOW);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
