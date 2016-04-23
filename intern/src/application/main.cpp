#include "application/app_main.h"

#include <exception>
#include <iostream>

int main()
{
    Game::CApplication TheApp;

	try
	{
        TheApp.OnStart();
		TheApp.OnRun();
	}
	catch (std::exception& _rException)
	{
		std::cout << _rException.what() << std::endl;
	}
	catch (const char* _pMessage)
	{
		std::cout << _pMessage << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception" << std::endl;
	}


    try
    {
        TheApp.OnExit();
    }
    catch (std::exception& _rException)
    {
        std::cout << _rException.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
    }
}