#include "utils/game_assets.hpp"

#include "core/common.hpp"

GameAssets initializeGameAssets(AssetManager& assetManager)
{
    GameAssets assets;
    assets.shaders["basic"] = assetManager.loadShader("basic", shader_path("basic") + ".vs.glsl", shader_path("basic") + ".fs.glsl");
    assets.shaders["debug"] = assetManager.loadShader("debug", shader_path("debug") + ".vs.glsl", shader_path("debug") + ".fs.glsl");
    assets.shaders["background"] = assetManager.loadShader("background", shader_path("background") + ".vs.glsl", shader_path("background") + ".fs.glsl");
    assets.shaders["sprite"] = assetManager.loadShader("sprite", shader_path("sprite") + ".vs.glsl", shader_path("sprite") + ".fs.glsl");
    assets.shaders["animatedsprite"] = assetManager.loadShader("animatedsprite", shader_path("animatedsprite") + ".vs.glsl", shader_path("animatedsprite") + ".fs.glsl");
    assets.shaders["healthbar"] = assetManager.loadShader("healthbar", shader_path("healthbar") + ".vs.glsl", shader_path("healthbar") + ".fs.glsl");
    assets.shaders["font"] = assetManager.loadShader("font", shader_path("font") + ".vs.glsl", shader_path("font") + ".fs.glsl");

    // fonts
    AssetId deutschFont = assetManager.loadFont("deutsch", font_path("deutsch") + ".ttf", 48.0f);
    assets.fonts["deutsch"] = deutschFont;

    AssetId kingFont = assetManager.loadFont("king", font_path("kingthings") + ".ttf", 148.0f);
    assets.fonts["king"] = kingFont;

    AssetId healthFont = assetManager.loadFont("healthFont", font_path("deutsch") + ".ttf", 20.0f);
    assets.fonts["healthFont"] = healthFont;

    AssetId spellFont = assetManager.loadFont("spellFont", font_path("deutsch") + ".ttf", 32.0f);
    assets.fonts["spellFont"] = spellFont;

    const std::vector<float> vertices = {
        // positions        // colors           // texture coords
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f };

    const std::vector<uint32_t> indices = {
        0, 1, 2,
        2, 3, 0 };

    const std::vector<VertexAttribute> attributes = {
        {3, GL_FLOAT, GL_FALSE, "position"},
        {3, GL_FLOAT, GL_FALSE, "color"},
        {2, GL_FLOAT, GL_FALSE, "texCoord"} };
    AssetId meshId = assetManager.loadMesh("basic", vertices, indices, attributes);

    const std::vector<float> spriteVertices = {
        // positions        // texture coords
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    const std::vector<VertexAttribute> spriteAttributes = {
        {3, GL_FLOAT, GL_FALSE, "position"},
        {2, GL_FLOAT, GL_FALSE, "texCoord"} };

    AssetId spriteMeshId = assetManager.loadMesh("sprite", spriteVertices, indices, spriteAttributes);

    const std::vector<float> mageCollisionVertices = {
        0.f, 1.f, 0.f,
        -.5333333f, 0.2666667f, 0.f,
        .9333333f, .0666667f, 0.f,
        -.4f, -0.333333f, 0.f,
        -0.5333333f, -1.f, 0.f,
        0.4666667f, -1.f, 0.f,
        0.7333333f, -1.f, 0.f,
        0.4f, -0.2f, 0.f,
        0.333333f, 0.8f, 0.f,
        0.9333333f, 0.9333333f, 0.f
    };

    const std::vector<uint32_t> mage_col_indices = {
        0, 1, 8,
        1, 2, 3,
        3, 4, 5,
        3, 5, 7,
        1, 3, 7,
        1, 7, 8,
        7, 8, 9,
        6, 7, 9
    };

    const std::vector<VertexAttribute> mageCollisionAttributes = {
        {3, GL_FLOAT, GL_FALSE, "position"}
    };

    AssetId mageCollisionMeshId = assetManager.loadMesh("mage_collider", mageCollisionVertices, mage_col_indices, mageCollisionAttributes);

    const std::vector<float> debug_vertices = {
        // positions        // colors
        -1.f, -1.f, 0.0f,
         1.f, -1.f, 0.0f,
         1.f,  1.f, 0.0f,
        -1.f,  1.f, 0.0f,
    };

    const std::vector<uint32_t> debug_indices = {
        0, 1, 2,
        2, 3, 0
    };

    const std::vector<VertexAttribute> debug_attributes = {
        {3, GL_FLOAT, GL_FALSE, "position"}
    };
    AssetId debugId = assetManager.loadMesh("debug", debug_vertices, debug_indices, debug_attributes);

    // Player
    AssetId mageTextureId = assetManager.loadTexture("mage-idle", textures_path("mage-idle") + ".png");
    assets.textures["mage-idle"] = mageTextureId;

    AssetId mageWalkTextureId = assetManager.loadTexture("mage-walk", textures_path("mage-walk") + ".png");
    assets.textures["mage-walk"] = mageWalkTextureId;

    AssetId mageAttackTextureId = assetManager.loadTexture("mage-attack", textures_path("mage-attack") + ".png");
    assets.textures["mage-attack"] = mageAttackTextureId;

    // Enemies
    AssetId farmerTextureId = assetManager.loadTexture("farmer", textures_path("farmer") + ".png");
    assets.textures["farmer"] = farmerTextureId;

    AssetId archerTextureId = assetManager.loadTexture("archer", textures_path("archer") + ".png");
    assets.textures["archer"] = archerTextureId;

    AssetId knightTextureId = assetManager.loadTexture("knight", textures_path("knight") + ".png");
    assets.textures["knight"] = knightTextureId;

    // Projectiles / Spells
    AssetId fireballTextureId = assetManager.loadTexture("fireball", textures_path("fireball") + ".png");
    assets.textures["fireball"] = fireballTextureId;

    AssetId barrierTextureId = assetManager.loadTexture("barrier", textures_path("barrier") + ".png");
    assets.textures["barrier"] = barrierTextureId;

    AssetId lightning1TextureId = assetManager.loadTexture("lightning1", textures_path("lightning1") + ".png");
    assets.textures["lightning1"] = lightning1TextureId;

    AssetId lightning2TextureId = assetManager.loadTexture("lightning2", textures_path("lightning2") + ".png");
    assets.textures["lightning2"] = lightning2TextureId;

    AssetId lightning3TextureId = assetManager.loadTexture("lightning3", textures_path("lightning3") + ".png");
    assets.textures["lightning3"] = lightning3TextureId;

    AssetId pitchforkTextureId = assetManager.loadTexture("pitchfork", textures_path("pitchfork") + ".png");
    assets.textures["pitchfork"] = pitchforkTextureId;

    AssetId arrowTextureId = assetManager.loadTexture("arrow", textures_path("arrow") + ".png");
    assets.textures["arrow"] = arrowTextureId;

    // Used for knight's MELEE sword slash
    AssetId fillerTextureId = assetManager.loadTexture("filler", textures_path("filler") + ".png");
    assets.textures["filler"] = fillerTextureId;

    // Background Objects
    AssetId treeTextureId = assetManager.loadTexture("tree", textures_path("tree1") + ".png");
    AssetId campfireTextureId = assetManager.loadTexture("campfire", textures_path("campfire-sheet") + ".png");
    assets.textures["campfire"] = campfireTextureId;
    assets.textures["tree"] = treeTextureId;

    // UI
    AssetId healthBarId = assetManager.loadTexture("healthbar", textures_path("health") + ".png");
    assets.textures["healthbar"] = healthBarId;

    // Add a new mesh for the background (full screen quad)
    const std::vector<float> bgVertices = {
        // positions        // texture coords
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    const std::vector<VertexAttribute> bgAttributes = {
        {3, GL_FLOAT, GL_FALSE, "position"},
        {2, GL_FLOAT, GL_FALSE, "texCoord"} };
    AssetId bgMeshId = assetManager.loadMesh("background", bgVertices, indices, bgAttributes);

    AssetId grassTextureId = assetManager.loadBackgroundTexture("grass1", textures_path("grass1") + ".png");
    assets.textures["grass1"] = grassTextureId;

    AssetId grassTextureId2 = assetManager.loadBackgroundTexture("grass2", textures_path("grass2") + ".png");
    assets.textures["grass2"] = grassTextureId2;

    AssetId grassTextureIdDark = assetManager.loadBackgroundTexture("grass3", textures_path("grass3") + ".png");
    assets.textures["grass3"] = grassTextureIdDark;

    AssetId grassTextureId4 = assetManager.loadBackgroundTexture("grass4", textures_path("grass4") + ".png");
    assets.textures["grass4"] = grassTextureId4;

    AssetId grassTextureId5 = assetManager.loadBackgroundTexture("grass5", textures_path("grass5") + ".png");
    assets.textures["grass5"] = grassTextureId5;

    AssetId grassTextureId6 = assetManager.loadBackgroundTexture("grass6", textures_path("grass6") + ".png");
    assets.textures["grass6"] = grassTextureId6;

    AssetId clayTextureId1 = assetManager.loadBackgroundTexture("clay1", textures_path("clay1") + ".png");
    assets.textures["clay1"] = clayTextureId1;

    AssetId clayTextureId2 = assetManager.loadBackgroundTexture("clay2", textures_path("clay2") + ".png");
    assets.textures["clay2"] = clayTextureId2;

    AssetId clayTextureId3 = assetManager.loadBackgroundTexture("clay3", textures_path("clay3") + ".png");
    assets.textures["clay3"] = clayTextureId3;

    return assets;
}



