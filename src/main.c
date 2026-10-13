#include "raylib.h"
#include "stdio.h"
#include "string.h"

// Canvas

typedef struct {
    Color color;
    float reacitivity;
    float melting_point;
    float boiling_point;
    float viscosity;
} Compound;

typedef struct {
    bool filled;
    float heat;
    Compound* compound;
} Molecule;

typedef struct {
    Molecule 
    Image buffer;
    Texture display;
    int rows;
    int cols;
} Canvas;

// Particulate
typedef struct {
    int window_width;
    int window_height;
    Canvas canvas;

} Particulate;

void InitializeParticulate(){
    Particulate p;
    p.window_width = 1280;
    p.window_height = 720;

}



int main(void) {

    const int window_width = 1280;
    const int window_height = 720;

    const int rows = window_width / gridSize;
    const int cols = window_height / gridSize;

    int matrix[rows][cols];
    memset(matrix, 0, sizeof(matrix)); // initialize all values to 0

    Color bgColor = BLACK;

    InitWindow(screenWidth, screenHeight, "Basic Sand Sim Demo");
    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            
            Vector2 mpos = GetMousePosition();
            int x = mpos.x / gridSize;
            int y = mpos.y / gridSize;

            if (matrix[y][x] == 0){
                matrix[y][x] = 1;
            }
        }

        BeginDrawing();
        ClearBackground(bgColor);

        // iterate bottom to top through the matrix. Top to bottom would cause everything to happen instantly
        for(int r = rows; r >= 0; r--){
            for(int c = cols; c >=0; c--){
                if(matrix[r][c] == 1){

                    // Move tile if able
                    if (r+1 < rows && matrix[r+1][c] == 0){
                        matrix[r][c] = 0;
                        matrix[r+1][c] = 1;
                    }
                    else if (matrix[r+1][c] == 1){
                        if(matrix[r+1][c+1] == 0){
                            matrix[r][c] = 0;
                            matrix[r+1][c+1] = 1;
                        }else if(matrix[r+1][c-1] == 0){
                            matrix[r][c] = 0;
                            matrix[r+1][c-1] = 1;
                        }
                    }

                    // Draw tile
                    DrawRectanglePro((Rectangle){c * gridSize, r * gridSize, gridSize, gridSize}, (Vector2){0, 0}, 0, WHITE);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
