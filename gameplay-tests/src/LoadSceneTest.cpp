#include "LoadSceneTest.h"
#include "TestsGame.h"

#if defined(ADD_TEST)
    ADD_TEST("Scene", "Load Scene", LoadSceneTest, 2);
#endif

LoadSceneTest::LoadSceneTest()
    : _font(NULL), _scene(NULL), _lightNode(NULL), _wireFrame(false)
{
    
}

void LoadSceneTest::initialize()
{
    // Create the font for drawing the framerate.
    _font = Font::create("res/common/arial18.gpb");

    _scene = Scene::load("res/common/test.scene");

    // Find the light node
    _lightNode = _scene->findNode("directionalLight");

    // Update the aspect ratio for our scene's camera to match the current device resolution
    _scene->getActiveCamera()->setAspectRatio(getAspectRatio());

    _scene->visit(this, &LoadSceneTest::bindLights);
}

void LoadSceneTest::finalize()
{
    SAFE_RELEASE(_font);
    SAFE_RELEASE(_scene);
}

void LoadSceneTest::update(float elapsedTime)
{
    
}

void LoadSceneTest::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);

    // Visit all the nodes in the scene, drawing the models/mesh.
    _scene->visit(this, &LoadSceneTest::drawScene);

    drawFrameRate(_font, Vector4(0, 0.5f, 1, 1), 5, 1, getFrameRate());
}

void LoadSceneTest::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        if (x < 75 && y < 50)
        {
            // Toggle Vsync if the user touches the top left corner
            setVsync(!isVsync());
            return;
        }
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}

void LoadSceneTest::keyEvent(Keyboard::KeyEvent evt, int key)
{
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_W:
        case Keyboard::KEY_CAPITAL_W:
            _wireFrame = !_wireFrame;
            break;
        }
    }
}

bool LoadSceneTest::drawScene(Node* node)
{
    Model* model = node->getModel();
    if (model)
        model->draw(_wireFrame);
    return true;
}

bool LoadSceneTest::bindLights(Node* node)
{
    Model* model = node->getModel();
    if (model)
    {
        Material* material = model->getMaterial();
        if (material)
        {
            MaterialParameter* ambientColorParam = material->getParameter("u_ambientColor");
            if (ambientColorParam)
            {
                ambientColorParam->setValue(_scene->getAmbientColor());
            }
            if (_lightNode && _lightNode->getLight())
            {
                MaterialParameter* lightDirectionParam = material->getParameter("u_lightDirection");
                MaterialParameter* lightColorParam = material->getParameter("u_lightColor");
                if (lightDirectionParam)
                {
                    lightDirectionParam->bindValue(_lightNode, &Node::getForwardVectorView);
                }
                if (lightColorParam)
                {
                    lightColorParam->setValue(_lightNode->getLight()->getColor());
                }
            }
        }
    }
    return true;
}