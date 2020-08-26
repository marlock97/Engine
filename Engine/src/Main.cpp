/************************************************************************/
/*!
\file	Main.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	26/08/2020
\brief  Main script

\log  26/08/2020 -> Initial version
*/
/************************************************************************/

int main(void)
{
	WindowManager::Instance()->Initialize();
	WindowManager::Instance()->CreateWindow();
	WindowManager::Instance()->GetMainWindow()->SetFullScreen();

	return 0;
}