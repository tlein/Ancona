#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Engine/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Engine/Screens/LoadingScreen.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>

#include "../Screens/FlappyScreen.hpp"
#include "FlappyGame.hpp"
#include <iostream>

using namespace ild;

FlappyGame::FlappyGame(
        int windowWidth, 
        int windowHeight, 
        const std::string & title)
    : Game(windowWidth,windowHeight, title)
{
    sf::View view = _window.getView();
    view.zoom(.5f);
    _window.setView(view);
    ResourceLoaderInit::Init();
    CreateInitialScreen();
}


void FlappyGame::CreateInitialScreen()
{
    _requestList = new RequestList();
    _requestList->Add("TexturePNG","flappy");
    _requestList->Add("TexturePNG","flappy-bottom-pipe");
    _requestList->Add("TexturePNG","flappy-top-pipe");
    _requestList->Add("TexturePNG","flappy-ground");
    _requestList->Add("TexturePNG","flappy-bg1");
    _requestList->Add("TexturePNG","flappy-bg2");
    _requestList->Add("TexturePNG","flappy-fg");
    _requestList->Add("TexturePNG","col-point");
    _requestList->Add("FontTTF","small_pixel-7");
    _requestList->Start();
    _screenManager->Push(
            new FlappyScreen(*_screenManager));
    _screenManager->Push(
            new LoadingScreen(*_screenManager, *_requestList));
}
