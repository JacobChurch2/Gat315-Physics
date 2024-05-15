#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
ncEditorData_t ncEditorData;

Rectangle editorRect;

Vector2 anchor01 = { 950, 50 };
Texture2D cursorTexture;

bool EditorBoxActive = true;
float MassMinValue = 0.0f;
float MassMaxValue = 0.0f;
float GravitationValue = 0.0f;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/dark/style_dark.rgs");

    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    ncEditorData.anchor01 = (Vector2){ 950, 50 };

    ncEditorData.EditorBoxActive = true;
    ncEditorData.BodyTypeEditMode = false;
    ncEditorData.BodyTypeActive = 0;
    ncEditorData.MassMinValue = 0.5f;
    ncEditorData.MassMaxValue = 10.0f;
    ncEditorData.DampingValue = 0.0f;
    ncEditorData.GravitationValue = 0.0f;
    ncEditorData.GravityScaleValue = 0.0f;

    editorRect = (Rectangle){ ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 304, 616 };

    HideCursor();
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor(Vector2 position)
{
    //
    if (ncEditorData.BodyTypeEditMode) GuiLock();

    if (ncEditorData.EditorBoxActive)
    {
        ncEditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 280, 584 }, "Editor");
        GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 24, ncEditorData.anchor01.y + 40, 232, 152 }, "Body");
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 120, ncEditorData.anchor01.y + 96, 120, 16 }, "MassMin", NULL, & ncEditorData.MassMinValue, 0.1, 10);
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 120, ncEditorData.anchor01.y + 120, 120, 16 }, "MassMax", NULL, & ncEditorData.MassMaxValue, 0.1, 10);
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 120, ncEditorData.anchor01.y + 144, 120, 16 }, "Damping", NULL, & ncEditorData.DampingValue, 0, 10);
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 120, ncEditorData.anchor01.y + 168, 120, 16 }, "Gravitation", NULL, & ncEditorData.GravitationValue, 0, 20);
        GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 24, ncEditorData.anchor01.y + 216, 232, 104 }, "World");
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 120, ncEditorData.anchor01.y + 240, 120, 16 }, "GravityScale", NULL, & ncEditorData.GravityScaleValue, 0, 20);
        if (GuiDropdownBox((Rectangle) { ncEditorData.anchor01.x + 40, ncEditorData.anchor01.y + 56, 200, 24 }, "DYNAMIC;KINEMATIC;STATIC", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
    }

    GuiUnlock();

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, WHITE);
}

ncBody* GetBodyIntersect(ncBody* bodies, Vector2 position)
{
    for (ncBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5f)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(ncBody* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}
