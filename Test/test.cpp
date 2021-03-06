#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


using namespace sf;




void line(Image & image, float xa, float ya, float xb, float yb, Color c)
{
	float L;
	float DirX;
	float DirY;
	
	DirX = xb - xa;
	DirY = yb - ya;

	L = sqrt((DirX * DirX) + (DirY * DirY));
	
	if( L == 0)
		return;

	DirX = DirX / L;
	DirY /= L;
	
	for( float timp = 0; timp <= L; timp += 1)
	{
		image.setPixel(xa + DirX * timp, ya + DirY * timp, c);
	}

	return;
}

void cerc(Image & image, float mc, int dx, int dy, Color c, bool Umplere_Cerc, int def)
{
	for (float u = 0; u < 2 * 3.14159265359282f; u += 3.141592f/def)
	{
		float x = cos(u) * mc + dx;
		float y = sin(u) * (mc) + dy;

		line(image, x, y, cos(u+3.141592f/def) * mc + dx, sin(u+3.141592f/def) * mc + dy, c);
		if( Umplere_Cerc == true && dx > x)
		line(image, x, y, dx + dx - x, y, c);
	}
	if( mc == 40 )
	for(float u2 = 0; u2 < 2 * 3.14159235659282f;  u2 += 3.141592f/10)
	{
		float x = cos(u2) * mc + dx;
		float y = sin(u2) * mc + dy;

		line(image, x, y, dx, dy, Color::Black);
	}
}

void arrow(Image & image, int capsx, int capdx , int capsusy, int capjosy, int varfx, Color c)
{
	int capsusy2;
	int capjosy2;
	int varfy = capsusy + (capjosy-capsusy)/2;

	capsusy2 = capsusy - (capjosy - capsusy);
	capjosy2 = capjosy + (capjosy - capsusy);


	line(image, capsx, capsusy, capdx, capsusy, c);
	line(image, capsx, capjosy, capdx, capjosy, c);
	line(image, capsx, capjosy, capsx, capsusy, c);
	line(image, capdx, capsusy, capdx, capsusy2, c);
	line(image, capdx, capsusy2, varfx, capsusy + (capjosy-capsusy)/2, c);
	line(image, varfx, varfy, capdx, capsusy2,  c);
	line(image, capdx, capjosy, capdx, capjosy2, c);
	line(image, varfx, varfy, capdx, capjosy2, c);

	return;
}


void dreptunghi(Image & image, int xs, int xd, int ysus, int yjos, Color c)
{
	line(image, xs, ysus, xs, yjos, c);
	line(image, xs, yjos, xd, yjos, c);
	line(image, xs, ysus, xd, ysus, c);
	line(image, xd, ysus, xd, yjos, c);
	
	return;
}





int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "Nivel 1");
	Image image;
	image.create(800,600, Color::Red);
	Texture tex;
	tex.loadFromImage(image);
	Sprite sprite;
	sprite.setTexture(tex);

	float dt = 3.14159235659282/40;
	int dx = 50;
	int dy = 340;
	bool v = true;
	int verificare = 1;
	int jump = 0;
	int crestere = 0;

	int bx = 0;
	int by;
	bool b = false;
	bool b2 = true;
	bool b3 = true;

	int px = 0;
	int py = 0;
	bool p = true;
	int chestia = 0;

	bool sageata = true;
	int timpsageata = 0;

	bool nivel2 = true; 

    while (window.isOpen())
    {
		// see what new events happened
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				//std::cout << event.key.code << std::endl ;

				/*if( event.key.code == 57)
				{
					dx += 60;
					dy -= 80;
				}*/
				if( event.key.code == 72 && dx < 800 )
					dx += 10;
				if( event.key.code == 71 && dx > 55 )
					dx -= 10;
				if( event.key.code == 36 )
					window.close();
				if( event.key.code == 58 )
				{
					if( verificare == true)
						verificare = false;
					else
						verificare = true;
				}
				if( event.key.code == 57 && jump ==0 && dx < 800 )
				{
					jump = 35;
				}
				
			}
        }

		if (jump != 0)
		{
			dy -= jump;
			dx += 10;
			jump -= 5;
		}		
		if (dy < 350 && dx < 360)
		{
			dy += 10;
			dx += 10;
		}
		//obstacole
		if (dy > 300 && dx > 360)
			dx -=20;
		//gravitatie
		if (dy < 300 && dx > 360)
		{
			dy += 10;
			dx += 10;
		}		
		if (dy < 250 && dx > 600)
		{
			dy += 10;
			dx += 10;
		}
		//sageata
		if (dy > 250 && dx > 525)
			dx -=6;
		
		//miscare rata
		if (px < 50 && p == true)
			px += 1;
		else
		{
			p = false;
			px -= 10;
		}
		if (px < 0)
		{
			p = true;
		}
		//coliziune cu rata
		if (dx+90 > px + 435 && dx-90 < px + 430 && b2 == true)
		{
			std::cout << " Game over!!";
			nivel2 = true;
			window.close();
			system("pause");
			break;
		}
		if (dx > 740)
		{
			std::cout << "AI CASTIGAT Nivelul 1!!!" << std::endl << "Urmatorul nu este gata..." << std::endl;
			nivel2 = false;
			window.close();
		}


		// draw the new frame in memory
		image.create(801, 801, Color::Black);
		//image.loadFromFile("");


		//fundal


			
		for (int i = 20; i <= 720; i += 200)
			for (int j = 20; j<= 600; j += 190)
				image.setPixel(i, j, Color::White);
		
		cerc(image, 14, 300, 340, Color::Yellow, true, 70);
		cerc(image, 30, 750, 550, Color::White, true, 120);
		cerc(image, 25, 50, 50, Color::White, true, 100);
		cerc(image, 14, 730, 70, Color::Red, true, 350);	
		for (float dt = 0; dt < 2 * 3.141592f; dt += 3.141592f / 10)
		{
			float x = cos(dt) * 20 + 730;
			float y = sin(dt) * 7 + 70;		
			line(image, x, y, cos(dt + 3.141592f / 10) * 25 + 730, sin(dt + 3.141592f / 10) * 9 + 70, Color::Red);
		}
		cerc(image, 8, 70, 540, Color::Blue, true, 40);
		cerc(image, 50, 250, 330, Color::Black, true, 400);
		
		cerc(image, 100, 400, 100, Color::White, true, 350);
		cerc(image, 40, 355+dx/9, 85 + dy/6, Color::Green, true, 160);
		cerc(image, 25, 355+dx/9, 90 + dy/6, Color::Black, true, 100);

		/*cerc(image, 100, 400, 400, Color::White, true, 350);
		cerc(image, 40, 355+dx/9, 340 + dy/6, Color::Green, true, 175);
		cerc(image, 25, 355+dx/9, 345 + dy/6, Color::Black, true, 175);*/

		//line(image, 0, 400, 800, 400, Color::Yellow);
		//line(image, 0, 385, 400, 385, Color::Yellow);
		for( int i = 0; i <= 390; i += 8)
		{
			line(image, i, 400, i + 15, 385, Color::Yellow);
		}

		line(image, 400, 350, 400, 400, Color::Blue);
		line(image, 400, 350, 800, 350, Color::Blue);
		for( int i = 400; i <= 800; i += 1)
		{
			line(image, i, 400, i, 350, Color::Blue);
		}

		line(image, 415, 330, 800, 330, Color::Blue);
		line(image, 400, 400, 800, 400, Color::Blue);
		for( int i = 400; i <= 785; i += 5)
		{
			line(image, i, 350, i+15, 331, Color::Blue);
		}

		if(sageata == true && b2 == false)
		{
			timpsageata ++;
			dreptunghi(image, 415, 520, 260, 220, Color::Cyan);
			arrow(image, 416, 490, 235, 245, 520, Color::Green);
		}
		
		if(timpsageata > 20)
		{
			sageata = false;
		}
		if(sageata == false)
		{
			timpsageata --;
		}
		if(timpsageata < 0)
		{
			sageata = true;
		}

		//Sageata
		for ( float j = 0; j <= 150; j+= 2) 
			if( j < 75 )
				line(image, 650 - j, 200+j, 650, 200+j, Color::Magenta);
			else
				line(image, 500 + j, 200+j, 650, 200+j, Color::Magenta);
		for ( float i = 0; i <= 50; i+= 2)
			line(image, 650, 250+i, 800, 250 + i, Color::Magenta); 

			
		if (verificare == true)
		{
			for (int i = 0; i <= 300; i += 10)
				line(image, i, 0, 0, 300 - i, Color::Blue);

			/*for (int i = 0; i <= 300; i += 10)
				line(image, 0, 300 + i, i, 600, Color::Blue);

			for (int i = 0; i <= 300; i += 10)
				line(image, 800, i, 500 + i, 0, Color::Blue);*/

			for (int i = 0; i <= 400; i += 10)
				line(image, 800, 600 - i, 400 + i, 600, Color::Blue);
		}

		//Rata vampir
		if(b2 == true)
		{
			b3 = true;

			//line(image, px + 390, py + 330, px + 450, py + 330, Color::Black);
			cerc(image, 15, px + 435, py + 280, Color::Yellow, true, 60);
			cerc(image, 15, px + 405, py + 280, Color::Yellow, true, 60);
			cerc(image, 5, px + 435 - dx/40, py + 280, Color::Black, true, 40);
			cerc(image, 5, px + 405 - dx/40, py + 280, Color::Black, true, 40);

			cerc(image, 30, px + 420, py + 330, Color::White, true, 80);
			cerc(image, 16, px + 420, py + 330, Color::Black, true, 60);			

			for (float i = -0.7; i <= 0.7; i += 0.01f)
			{
				float zx = i*40 + px + 420;
				float zy = -i*i*40 + py + 275;

				line(image, zx, zy, (i + 0.02f)*40 + px + 420, -(i + 0.02f)*(i + 0.02f)*40 + py + 270, Color::Red);
			}

			for (float dt = 0; dt < 2 * 3.141592f; dt += 3.141592f / 90)
			{
				float x = cos(dt) * 20 + px + 420;
				float y = sin(dt) * px / 2 + py + 330;
			
				line(image, x, y, cos(dt + 3.141592f / 90) * 40 + px + 420, sin(dt + 3.141592f / 90) * 15 + py + 330, Color::Red);
			}
		}
					
		

		//arma
		if(event.key.code == 37)
		{
			bx = dx;
			by = dy;
			b = true;
		}	

		if(bx > px + 390)
		{
			b2 = false;
		}
			
		if(b == true)
		{
			bx += 30;
			arrow(image, bx, bx + 30, by, by - 8, bx + 60, Color::Green);
			arrow(image, bx - 1, bx + 31, by, by - 8, bx + 60, Color::Green);
		}

		if(bx > 710)
		{
			b = false;	
			bx = dx;
			chestia = 40;
		}
		
		if (chestia >= 1 && chestia <= 50 && b3 == true)
		{
			b3 = false;
			chestia += 20;
			cerc(image, chestia, px + 420, py + 330, Color::Red, true, chestia * 4);
			cerc(image, chestia / 2, px + 420, py + 330, Color::Yellow, true, chestia / 2 * 4);
		}





		//cercuri
		for (float u = 0; u < 2 * 3.14159235659282f; u += dt)
		{
			// Cerc in cadere
			if ( dx < 750 && dx > 50 && dy < 350 && dy > 50 )
			{
				float x = cos(u)*50 + dx;
				float y = sin(u)*50 + dy;	

				line(image, x, y, cos(u+dt)*50 + dx, sin(u+dt)*50 + dy, Color::Red);
				//line(image, x, y, dx, dy, Color::Red);
				
				if(y>20)
				{
					line(image, x + 10, y-20, cos(u + dt)*50 + dx + 10, sin(u + dt)*50 + dy - 20, Color::Red);
					line(image, x , y, cos(u)*50 + dx + 10, sin(u)*50 + dy - 20, Color::Red); 

				}

				//cerc(image, 50, dx, dy, Color::Green, true, 10);
			}

				//Cerc cazut
			if ( dx < 750 && dx > 50 && dy >= 350 && dy > 50 )
			{
				float x = cos(u)*50 + dx;
				float y = sin(u)*50 + 350;		

				line(image, x, y, cos(u+dt)*50 + dx, sin(u+dt)*50 + 350, Color::Blue);
				line(image, x + 15, y-15, cos(u+dt)*50 + dx + 15, sin(u+dt)*50 + dy - 15, Color::Blue);

				line(image, x, y, cos(u)*50 + dx + 15, sin(u)*50 + dy - 15, Color::Blue);
			}						
			} 			

		//ochi si gura
		if (b3 == false)
		{
			cerc(image, 15, dx + 20, dy -20, Color::White, true, 50);
			cerc(image, 15, dx - 20, dy -20, Color::White, true, 50);
			cerc(image, 10, dx + 20, dy -20, Color::Black, true, 32);
			cerc(image, 10, dx - 20, dy -20, Color::Black, true, 32);

			for (float i = -0.5; i <= 0.5; i += 0.01f)
			{
				float zx = i*40 + dx;
				float zy = -i*i*40 + dy + 30;

				line(image, zx, zy, (i + 0.02f)*40 + dx, -(i + 0.02f)*(i + 0.02f)*40 + dy + 25, Color::Red);
			}
		}
			
		if (b3 == true)
		{
			cerc(image, 19, dx + 20, dy -20, Color::White, true, 65);
			cerc(image, 19, dx - 20, dy -20, Color::White, true, 65);
			cerc(image, 11, dx - 20, dy -20, Color::Black, true, 40);
			cerc(image, 11, dx + 20, dy -20, Color::Black, true, 40);

			for (float i = -0.5; i <= 0.5; i += 0.01f)
			{
				float zx = i*40 + dx;
				float zy = i*i*40 + dy + 16;

				line(image, zx, zy, (i + 0.02f)*40 + dx, (i + 0.02f)*(i + 0.02f)*40 + dy + 13, Color::Red);
			}
		}

		// clear the window for a new frame of animation
        window.clear();

		// draw the new frame on screen
		tex.loadFromImage(image);
		//sprite.setPosition(
		window.draw(sprite);

        window.display();

    }

	dx = 50;
	dy = 500;

	int oux = 10;
	int ouy = 15;
	int curcan = 6;

	nivel2 = false;

	bool saritura = false; // verificare sol
	int ts = 0; // timp saritura1

	int matrice[81][61];
	bool directie = true; 
	b2 = false;

	//Matrice harta
	for( int i = 0; i <= 80; i++)
		for(int j = 0; j <= 53; j++)
			matrice[i][j] = 0;

	for( int i = 0; i <= 80; i++)
		for(int j = 53; j <= 56; j++)
			matrice[i][j] = 1;

	for( int i = 35; i <= 80; i++)
		for(int j = 45; j <= 47; j++)
			matrice[i][j] = 1;

	for( int i = 0; i <= 30; i++)
		for(int j = 41; j <= 42; j++)
			matrice[i][j] = 1;

	/*for( int i = 30; i <= 60; i++)
		for(int j = 35; j <= 37; j++)
			matrice[i][j] = 1;*/

	for ( int i = 30; i <= 41; i++)
		for(int j = 18; j <= 20; j++)
			matrice[j][i] = 2;

	for( int i = 0; i <= 30; i++)
		for(int j = 29; j <= 30; j++)
			matrice[i][j] = 1;


	
	if(nivel2 == false)
	{
	RenderWindow window2(VideoMode(800, 600), "Nivel 2 (Buna!)");
	while(window2.isOpen())
	{
		Event event;
		while(window2.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window2.close();
			if(event.type == Event::KeyPressed)
			{

				std::cout << event.key.code << std::endl;

				if (event.key.code == 36 )
					window2.close();
				if (event.key.code == 71 && matrice[(dx-10)/10][dy/10] != 1)
					dx -= 10;
				if (event.key.code == 72)
					directie = true;
				if (event.key.code == 71)
					directie = false;
				if (event.key.code == 72 && matrice[(dx+10)/10][dy/10] != 1)
					dx += 10;
				if (event.key.code == 57 && matrice[dx / 10][(dy + 10) / 10] != 0)
				{	
					ts = 50;
				}
				if (event.key.code == 58 && verificare == false)
					verificare = true;
				if (event.key.code == 58 && verificare == true)
					verificare = false;		
				if (event.key.code == 73 && matrice[dx / 10][(dy - 10)/10] == 2)
					dy -= 5;
			}
		}

		//limitare stanga
		if (dx > 770)
			dx -= 10;
		//limitare dreapta
		if (dx < 30)
			dx +=10;
		//Saritura Dreapta
		if (ts != 0 && directie == true)
		{	
			ts -= 10;
			dy -= ts;
			dx += 8;
		}
		//Saritura Stanga
		if (ts != 0 && directie == false)
		{	
			ts -= 10;
			//sleep(1000);
			dy -= ts;
			dx -= 8;
		}
		//Gravitatie in Dreapta
		if (matrice[dx / 10][(dy + 10) / 10] == 0 && directie == true)
		{
			dy += 10;
			dx += 10;
		}
		
		//Gravitatie in Stanga
		if (matrice[dx / 10][(dy + 10) / 10] == 0 && directie == false)
		{
			dy += 10;
			dx -= 10;
		}
		//Stergere pamant
		matrice[oux][ouy] = 0;
		matrice[oux+1][ouy] = 0;
		matrice[oux][ouy+1] = 0;
		matrice[oux+1][ouy+1] = 0;


		//cadere oua
		ouy += 1;

		if (ouy >= 52)
		{
			ouy = 2;
			oux =  rand() % 80;
		}
		matrice[oux][ouy] = 3;
		if (dx / 10 + 4 > oux && dx / 10 - 4 < oux && dy / 10 + 4 > ouy && dy / 10 - 4 < ouy)
		{
			curcan -= 1;
			std::cout << curcan << std::endl;
		}		
		if (curcan == 0)
		{
			break;
			std::cout << "Game over";
		}
		
		image.create(801, 601, Color::Black);
		
		//fundal

		if (curcan/3 == 2)
		{
			cerc(image, 20, 50, 570, Color::Red, true, 80);
			cerc(image, 20, 100, 570, Color::Red, true, 80);
		}
		if (curcan/3 == 1)
		{
			cerc(image, 20, 50, 570, Color::Red, true, 80);
		}

		for (int i = 20; i <= 720; i += 200)
			for (int j = 20; j<= 600; j += 190)
				image.setPixel(i, j, Color::White);
		
		cerc(image, 14, 300, 340, Color::Yellow, true, 70);
		cerc(image, 30, 750, 550, Color::White, true, 120);
		cerc(image, 25, 50, 50, Color::White, true, 100);
		cerc(image, 30, 730, 70, Color::Red, true, 350);	
		for (float dt = 0; dt < 2 * 3.141592f; dt += 3.141592f / 20)
		{
			float x = cos(dt) * 50 + 730;
			float y = sin(dt) * 13 + 70;		
			line(image, x, y, cos(dt + 3.141592f / 10) * 36 + 730, sin(dt + 3.141592f / 10) * 9 + 70, Color::Red);
		}
		cerc(image, 8, 70, 520, Color::Blue, true, 40);
		cerc(image, 50, 250, 330, Color::Black, true, 400);
		
		
		//pamant
		for (int i = 1; i < 80; i += 2)
			for (int j = 1; j < 59; j += 2)
				if (matrice[i + 1][j + 1] == 1)
					cerc(image, 10, (i + 1) * 10, (j + 1) * 10, Color::Blue, true, 100);
		//scari
		for (int i = 1; i < 80; i += 1)
			for (int j = 1; j < 59; j += 1)
				if (matrice[i][j] == 2)
					cerc(image, 10, (i + 1) * 10, (j + 1) * 10, Color::Red, false, 4);

		//oua
		for (int i = 1; i < 80; i += 1)
			for (int j = 1; j < 59; j += 1)
				if (matrice[i][j] == 3)
					for (float u = 0; u <2 * 3.141592; u += 3.141592/50)
					{
						float x = cos(u)* 10 + (i + 1) * 10;
						float y = sin(u)* 15 + (j + 1) * 10;
						line(image, x, y, cos(u + 3.141592/50)* 10 + (i + 1) * 10, sin(u + 3.141592/50)* 15 + (j + 1) * 10, Color::White);
						line(image, x, y, (i + 1) * 10 + (i + 1) * 10 - x, y, Color::White);
					}
					//cerc(image, 15, (i + 1) * 10, (j + 1) * 10, Color::White, true, 60);

		//ochiul de pe fundal
		cerc(image, 100, 400, 100, Color::White, true, 350);
		cerc(image, 40, 355+dx/9, 85 + dy/8, Color::Green, true, 160);
		cerc(image, 25, 355+dx/9, 90 + dy/8, Color::Black, true, 100);

		//personaj

		cerc(image, 30, dx, dy, Color::Green, true, 120);
		//ochi si gura
		if (b3 == false)
		{
			cerc(image, 15, dx + 20, dy - 20, Color::White, true, 50);
			cerc(image, 15, dx - 20, dy - 20, Color::White, true, 50);
			cerc(image, 11, dx + 20, dy - 20, Color::Blue, true, 50);
			cerc(image, 11, dx - 20, dy - 20, Color::Blue, true, 50);
			cerc(image, 8, dx + 20, dy - 20, Color::Black, true, 32);
			cerc(image, 8, dx - 20, dy - 20, Color::Black, true, 32);

			for (float i = -0.5; i <= 0.5; i += 0.01f)
			{
				float zx = i*40 + dx;
				float zy = -i*i*40 + dy + 20;

				line(image, zx, zy, (i + 0.02f)*40 + dx, -(i + 0.02f)*(i + 0.02f)*40 + dy + 15, Color::Red);
			}
		}
			
		if (b3 == true)
		{
			cerc(image, 19, dx + 20, dy -20, Color::White, true, 65);
			cerc(image, 19, dx - 20, dy -20, Color::White, true, 65);
			cerc(image, 11, dx - 20, dy -20, Color::Black, true, 40);
			cerc(image, 11, dx + 20, dy -20, Color::Black, true, 40);

			for (float i = -0.5; i <= 0.5; i += 0.01f)
			{
				float zx = i*40 + dx;
				float zy = i*i*40 + dy + 16;

				line(image, zx, zy, (i + 0.02f)*40 + dx, (i + 0.02f)*(i + 0.02f)*40 + dy + 13, Color::Red);
			}
		}
		//Gata personaj
		
		//Adancime
		if (verificare == true)
		{
			for (int i = 0; i <= 300; i += 10)
				line(image, i, 0, 0, 300 - i, Color::Red);

			/*for (int i = 0; i <= 300; i += 10)
				line(image, 0, 300 + i, i, 600, Color::Blue);

			for (int i = 0; i <= 300; i += 10)
				line(image, 800, i, 500 + i, 0, Color::Blue);*/

			for (int i = 0; i <= 400; i += 10)
				line(image, 800, 600 - i, 400 + i, 600, Color::Red);
		}






		//Matrice
		/*for (int i = 1; i <= 800; i += 15)
		{
			line(image, i, 0, i, 600, Color::Green);
		}
		for (int i = 1; i <= 600; i += 15)
		{
			line(image, 0, i, 800, i, Color::Green);
		}*/




		//std::cout << dx << "-X	" << dy << "-Y" << std::endl;
			
		std::cout << rand() % 80 << std::endl;
		

		window2.clear();

		

		tex.loadFromImage(image);

		window2.draw(sprite);

		window2.display();

	}
	}
	


    return 0;