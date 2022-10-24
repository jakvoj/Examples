#include<iostream>
#include<SDL.h>
int SDL_main(int, char**)
{
	bool quit = false;
	bool vpravo = true;
	int vyskok_vyska = 0;
	bool vyskok = false;
	bool dolu = false;
	int poloha = 0;
	bool vyhra = false;
	bool prohra = false;
	int zbytek = 0;
	bool pad = false;
	SDL_Init(SDL_INIT_VIDEO);//inicializace SDL - prace s grafikou
	int souradnice_mapa[2][20];//souradnice objektù - respektive prostøedí
	souradnice_mapa[0][0] = 0;
	souradnice_mapa[1][0] = 570;
	souradnice_mapa[0][1] = 0;
	souradnice_mapa[1][1] = 100;
	souradnice_mapa[0][2] = 680;
	souradnice_mapa[1][2] = 570;
	souradnice_mapa[0][3] = 1900;
	souradnice_mapa[1][3] = 570;
	souradnice_mapa[0][4] = 2570;
	souradnice_mapa[1][4] = 100;
	souradnice_mapa[0][5] = 1470;
	souradnice_mapa[1][5] = 470;
	int velikost_mapa[2][20];//pixelová velikost jednotlivıch objektù
	velikost_mapa[0][0] = 500;
	velikost_mapa[1][0] = 30;
	velikost_mapa[0][1] = 30;
	velikost_mapa[1][1] = 470;
	velikost_mapa[0][2] = 680;
	velikost_mapa[1][2] = 30;
	velikost_mapa[0][3] = 700;
	velikost_mapa[1][3] = 30;
	velikost_mapa[0][4] = 30;
	velikost_mapa[1][4] = 470;
	velikost_mapa[0][5] = 320;
	velikost_mapa[1][5] = 30;
	int souradnice_prekazka[2][20];//souøadnice pøekáek
	souradnice_prekazka[0][0] = 500;
	souradnice_prekazka[1][0] = 570;
	souradnice_prekazka[0][1] = 1360;
	souradnice_prekazka[1][1] = 570;
	int velikost_prekazka[2][20];//velikost pøekáek
	velikost_prekazka[0][0] = 180;
	velikost_prekazka[1][0] = 30;
	velikost_prekazka[0][1] = 540;
	velikost_prekazka[1][1] = 30;
	int souradnice_cil[2][20];//souøadnice cíle - je to pole, protoe by se to dalo tøeba rozšíøit o checkpointy
	souradnice_cil[0][0] = 2350;
	souradnice_cil[1][0] = 319;
	int velikost_cil[2][20];
	velikost_cil[0][0] = 176;
	velikost_cil[1][0] = 251;
	int souradnice_text[2][20];//pouito pro texty, respektive pro vıhru a prohru
	souradnice_text[0][0] = 400;
	souradnice_text[1][0] = 0;
	souradnice_text[0][1] = 400;
	souradnice_text[1][1] = 0;
	int velikost_text[2][20];
	velikost_text[0][0] = 323;
	velikost_text[1][0] = 88;
	velikost_text[0][1] = 323;
	velikost_text[1][1] = 88;
	SDL_Window * window = SDL_CreateWindow("Panackovo cernobile dobrodruzstvi",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 600, 0);//vytvoøení hlavního okna
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);//vytvoøení rendereru pro okno, do kterého bude vykreslovat, stará se o samotné vykreslování							
	SDL_Surface* panacek = SDL_LoadBMP("panacek_vpravo.bmp");//vytvoøení surface panacek a naètení jeho textury
	SDL_Surface* zeme[20];//surface pro prostøedí
	SDL_Surface* prekazky[20];//surface pro pøekáky
	SDL_Surface* cil[20];//surface pro cíle
	SDL_Surface* text[20];//surface pro text
	for (int i = 0; i < 6; i++)
	{
		zeme[i] = SDL_LoadBMP("zeme.bmp");//na vytvoøení prostøedí jsem pouil pouze jednu texturu, proto for cyklus
	}
	prekazky[0] = SDL_LoadBMP("bodce1.bmp");//naètení pøekáek
	prekazky[1] = SDL_LoadBMP("bodce2.bmp");
	cil[0] = SDL_LoadBMP("cil.bmp");//naètení cíle
	text[0] = SDL_LoadBMP("vyhra_text.bmp");//naètení textù
	text[1] = SDL_LoadBMP("prohra_text.bmp");
	Uint32 WhiteColor = SDL_MapRGB(panacek->format, 255, 255, 255);//nastavení barvy, která se nebude vykreslovat, v našem pøípadì 255 255 255, tedy bílá
	SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//samotné aplikování na texturu
	for (int i = 0; i < 6; i++)
	{
		SDL_SetColorKey(zeme[i], SDL_ENABLE, WhiteColor);//zprùhlednìní bílé prostøedí
	}
	for (int i = 0; i < 2; i++)
	{
		SDL_SetColorKey(prekazky[i], SDL_ENABLE, WhiteColor);//zprùhlednìní bílé u pøekáek
	}
	SDL_SetColorKey(cil[0], SDL_ENABLE, WhiteColor);//zprùhlednìní bílé u cíle
	SDL_SetColorKey(text[0], SDL_ENABLE, WhiteColor);//zprùhlednìní bílé u textu
	SDL_SetColorKey(text[1], SDL_ENABLE, WhiteColor);
	SDL_Texture * textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvoøení struktury SDL_Texture pro panáèka a tedy uloení do gpu ram
	SDL_Texture * textura_zeme[20];//vytvoøení pole struktur SDL_Texture pro prostøedí
	SDL_Texture * textura_prekazky[20];//vytvoøení pole struktur SDL_Texture pro pøekáky
	SDL_Texture * textura_cile[20];//vytvoøení pole struktur SDL_Texture pro cíle
	SDL_Texture * textura_text[20];//vytvoøení pole struktur SDL_Texture pro text
	for (int i = 0; i < 6; i++)
	{
		textura_zeme[i] = SDL_CreateTextureFromSurface(renderer, zeme[i]);//samotné vytvoøení SDL_Texture pro prostøedí
	}
	for (int i = 0; i < 2; i++)
	{
		textura_prekazky[i] = SDL_CreateTextureFromSurface(renderer, prekazky[i]);//samotné vytvoøení SDL_Texture pro pøekáky
	}
	textura_cile[0] = SDL_CreateTextureFromSurface(renderer, cil[0]);//samotné vytvoøení SDL_Texture pro cíle
	textura_text[0] = SDL_CreateTextureFromSurface(renderer, text[0]);//samotné vytvoøení SDL_Texture pro text
	textura_text[1] = SDL_CreateTextureFromSurface(renderer, text[1]);
	SDL_Event* event = new SDL_Event; //struktura, která uchovává události, tedy napøíklad stisk klávesy
	int x = 50;
	int y = 382;
	while (!quit)//hlavní smyèka samotné hry - zde se stále opakuje kolobìh - naètení vstupu, zmìna scény, vykreselní scény
	{
		while (SDL_PollEvent(event))//pokud skonèí fronta pøíchozích událostí, tak dojde k ukonèení této smyèky 
		{
			if (event->type == SDL_QUIT)
				quit = true;
			if (event->key.keysym.sym == SDLK_RIGHT)//pokud dojde ke stisku klávesy doprava
			{
				if (vyhra == false && prohra == false)//pokud je prohra nebo vyhra, tak se panacek zastaví
				{
					if (poloha + 162 <= souradnice_mapa[0][4] + 1350 && poloha + 162 <= souradnice_cil[0][0] + 1350)//zajištìní kolize s prostøedím
					{
						if (poloha >= 200 && poloha <= 1595)//zde se pohybuje prostøedí
						{
							souradnice_mapa[0][0] -= 5;
							souradnice_mapa[0][1] -= 5;
							souradnice_mapa[0][2] -= 5;
							souradnice_mapa[0][3] -= 5;
							souradnice_mapa[0][4] -= 5;
							souradnice_mapa[0][5] -= 5;
							souradnice_prekazka[0][0] -= 5;
							souradnice_prekazka[0][1] -= 5;
							souradnice_cil[0][0] -= 5;
							poloha += 5;
							vpravo = true;
						}
						else//zde se pohybuje panáèek
						{
							x += 5;
							poloha += 5;
							vpravo = true;
						}
					}
				}
			}
			if (event->key.keysym.sym == SDLK_LEFT)//pokud dojde ke stisku klávesy doleva
			{
				if (vyhra == false && prohra == false)//pokud je prohra nebo vyhra, tak se panacek zastaví
				{
					if (poloha >= souradnice_mapa[0][1] + 30 - 45)//zajištìní kolize s prostøedím
					{
						if (poloha >= 200 && poloha <= 1595)//zde se pohybuje prostøedí
						{
							souradnice_mapa[0][0] += 5;
							souradnice_mapa[0][1] += 5;
							souradnice_mapa[0][2] += 5;
							souradnice_mapa[0][3] += 5;
							souradnice_mapa[0][4] += 5;
							souradnice_mapa[0][5] += 5;
							souradnice_prekazka[0][0] += 5;
							souradnice_prekazka[0][1] += 5;
							souradnice_cil[0][0] += 5;
							poloha -= 5;
							vpravo = false;
						}
						else //zde se pohybuje panáèek
						{
							x -= 5;
							poloha -= 5;
							vpravo = false;
						}
					}
				}
			}
			if (event->key.keysym.sym == SDLK_UP)//pokud dojde ke stisku klávesy nahoru
			{
				if (vyhra == false && prohra == false)//pokud je prohra nebo vyhra, tak se panacek zastaví
				{
					vyskok = true;//aktivování vıskoku
				}
			}
		}
		if (vpravo == true)//pokud se pohybujeme doprava, tak dojde ke kolizi jinak ne ->
		{
			for (int i = 0; i < 2; i++)
			{
				if (y + 188 == souradnice_prekazka[1][i] && x + 100 > souradnice_prekazka[0][i] && x < souradnice_prekazka[0][i] + velikost_prekazka[0][i])
				{
					prohra = true;//aktivování prohry
				}
			}
		}
		if (vpravo == false)// -> kdy se pohybujeme doåeva; mùe zato to, e nohy panáèka nejsou úplnì v okrajích textury, take chce kolize nastavit pro kadı smìr zvláš
		{
			for (int i = 0; i < 2; i++)
			{
				if (y + 188 == souradnice_prekazka[1][i] && x + 162 > souradnice_prekazka[0][i] && x + 62 < souradnice_prekazka[0][i] + velikost_prekazka[0][i])
				{
					prohra = true;//aktivování prohry
				}
			}
		}
		if (vyskok == true)//pokud stiskeneme klávesu nahoru
		{
			if (vyskok_vyska <= 120 && dolu == false)//první èást skoku
			{
				SDL_Delay(10);//prodleva 10 ms, regulujeme tím rychlost skoku
				y--;
				vyskok_vyska++;
			}
			if (vyskok_vyska >= 120)
			{
				dolu = true;
				vyskok_vyska = vyskok_vyska + zbytek;//zbytek zde slouí pro dokonèení skoku, pokud jsme na plošinì nad zemí
				zbytek = 0;
			}
			if (vyskok_vyska > 0 && dolu == true)//druhá èást skoku
			{
				SDL_Delay(10);//prodleva 10 ms, regulujeme tím rychlost skoku
				y++;
				vyskok_vyska--;
				if (vyskok_vyska == 0)//dokonèení skoku
				{
					dolu = false;
					vyskok = false;
				}
				if (y + 188 == souradnice_mapa[1][5] && x + 100 > souradnice_mapa[0][5] && x < souradnice_mapa[0][5] + velikost_mapa[0][5] && vpravo == true && zbytek == 0)//nastavení podmínek pro skok z plošiny nad zemí; skáèeme smìrem doprava
				{
					vyskok = false;
					dolu = false;
					zbytek = vyskok_vyska;
					vyskok_vyska = 0;
				}
				if (y + 188 == souradnice_mapa[1][5] && x + 162 > souradnice_mapa[0][5] && x + 62 < souradnice_mapa[0][5] + velikost_mapa[0][5] && vpravo == false && zbytek == 0)//nastavení podmínek pro skok z plošiny nad zemí; skáèeme smìrem doleva
				{
					vyskok = false;
					dolu = false;
					zbytek = vyskok_vyska;
					vyskok_vyska = 0;
				}
			}
		}
		if (y + 188 == souradnice_mapa[1][5] &&  x > souradnice_mapa[0][5] + velikost_mapa[0][5] && vpravo == true && vyskok == false)//pokud pøejdeme plošinu, tak spadneme; jdeme smìrem doprava
		{
			pad = true;
		}
		if (y + 188 == souradnice_mapa[1][5] && x + 162 < souradnice_mapa[0][5] && vpravo == false && vyskok == false)//pokud pøejdeme plošinu, tak spadneme; jdeme smìrem doleva
		{
			pad = true;
		}
		if (pad == true)//provedení pádu
		{
			if (zbytek != 0)
			{
				SDL_Delay(10);//prodleva 10 ms, regulujeme tím rychlost pádu
				y++;
				zbytek--;
				if (zbytek == 0)
				{
					pad = false;
				}
			}
		}
		if (vyskok == true || pad == true)//pokud skáèeme nebo padáme
		{
			if (vpravo == true)//pokud skáèeme doprava
			{
				SDL_FreeSurface(panacek);//smazání obsahu SDL_Surface panáèka
				SDL_DestroyTexture(textura_panacek);//smazání obsahu SDL_Texture panáèka
				panacek = SDL_LoadBMP("panacek_vpravo_nahoru.bmp");//naètení skákajícího panáèka
				SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//nastavení bílé jako prùhledné
				textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvoøení SDL_Texture z panáèka - pøesunutí do ram gpu
			}
			if (vpravo == false)//pokud skáèeme doleva
			{
				SDL_FreeSurface(panacek);//smazání obsahu SDL_Surface panáèka
				SDL_DestroyTexture(textura_panacek);//smazání obsahu SDL_Texture panáèka
				panacek = SDL_LoadBMP("panacek_vlevo_nahoru.bmp");//naètení skákajícího panáèka
				SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//nastavení bílé jako prùhledné
				textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvoøení SDL_Texture z panáèka - pøesunutí do ram gpu
			}
		}
		if (vyskok == false)//pokud jdeme
		{
			if (vpravo == true && pad == false)//pokud jdeme doprava
			{
				SDL_FreeSurface(panacek);//smazání obsahu SDL_Surface panáèka
				SDL_DestroyTexture(textura_panacek);//smazání obsahu SDL_Texture panáèka
				panacek = SDL_LoadBMP("panacek_vpravo.bmp");//naètení panáèka jdoucí doprava
				SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//nastavení bílé jako prùhledné
				textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvoøení SDL_Texture z panáèka - pøesunutí do ram gpu
			}
			if (vpravo == false && pad == false)//pokud jdeme doprava
			{
				SDL_FreeSurface(panacek);//smazání obsahu SDL_Surface panáèka
				SDL_DestroyTexture(textura_panacek);//smazání obsahu SDL_Texture panáèka
				panacek = SDL_LoadBMP("panacek_vlevo.bmp");//naètení panáèka jdoucí doleva
				SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//nastavení bílé jako prùhledné
				textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvoøení SDL_Texture z panáèka - pøesunutí do ram gpu
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//pøekreslení okna bílou barvou - jinak by stará scéna zùstala a vytvoøila by se "mazanice"
		SDL_RenderClear(renderer);//samotné pøekreslení bílou barvou
		SDL_Rect umisteni_panacek = { x, y, 162, 188 };//nastavení rozmìrù a polohy panáèka; textura panáèka se bude vykreslovat na obdélník
		SDL_Rect umisteni_zeme[20];//vytvoøení obdelníkù pro prostøedí
		SDL_Rect umisteni_prekazka[20];//vytvoøení obdelníkù pro pøekáky
		SDL_Rect umisteni_cil[20];//vytvoøení obdelníkù pro cíl
		SDL_Rect umisteni_text[20];//vytvoøení obdelníkù pro texty
		for (int i = 0; i < 6; i++)
		{
			umisteni_zeme[i] = { souradnice_mapa[0][i], souradnice_mapa[1][i], velikost_mapa[0][i], velikost_mapa[1][i] };//nastavení rozmìrù obdelníkù pro prostøedí
		}
		for (int i = 0; i < 2; i++)
		{
			umisteni_prekazka[i] = { souradnice_prekazka[0][i], souradnice_prekazka[1][i], velikost_prekazka[0][i], velikost_prekazka[1][i] };//nastavení rozmìrù obdelníkù pro pøekáky
		}
		umisteni_cil[0] = { souradnice_cil[0][0], souradnice_cil[1][0], velikost_cil[0][0], velikost_cil[1][0] };//nastavení rozmìrù obdelníku pro cíl
		umisteni_text[0] = { souradnice_text[0][0], souradnice_text[1][0], velikost_text[0][0], velikost_text[1][0] };//nastavení rozmìrù obdelníkù pro texty
		umisteni_text[1] = { souradnice_text[0][1], souradnice_text[1][1], velikost_text[0][1], velikost_text[1][1] };
		SDL_RenderCopy(renderer, textura_panacek, NULL, &umisteni_panacek);//pøesunutí textury panáèka na obdelník
		for (int i = 0; i < 6; i++)
		{
			SDL_RenderCopy(renderer, textura_zeme[i], NULL, &umisteni_zeme[i]);//pøesunutí textury prostøedí na obdelník 
		}
		for (int i = 0; i < 2; i++)
		{
			SDL_RenderCopy(renderer, textura_prekazky[i], NULL, &umisteni_prekazka[i]);//pøesunutí textury pøekáky na obdelník
		}
		SDL_RenderCopy(renderer, textura_cile[0], NULL, &umisteni_cil[0]);//pøesunutí textury cíle na obdelník
		if (poloha + 162 >= souradnice_cil[0][0] + 1350)
		{
			SDL_RenderCopy(renderer, textura_text[0], NULL, &umisteni_text[0]);//pokud vyhrajeme, tak se vypíše text vıhry
			vyhra = true;
		}
		if (prohra == true)
		{
			SDL_RenderCopy(renderer, textura_text[1], NULL, &umisteni_text[1]);//pokud vyhrajeme, tak se vypíše text prohry
		}
		SDL_RenderPresent(renderer);//samotné vykreslení scény
	}//konec hlavní smyèky
	SDL_DestroyTexture(textura_panacek);//smazání textury panáèka na konci programu
	for (int i = 0; i < 6; i++)
	{
		SDL_DestroyTexture(textura_zeme[i]);//smazání textury prostøedí
	}
	for (int i = 0; i < 2; i++)
	{
		SDL_DestroyTexture(textura_prekazky[i]);//smazání textury pøekáky
	}
	SDL_DestroyTexture(textura_cile[0]);//smazání textury cíle
	SDL_DestroyTexture(textura_text[0]);//smazání textury textu
	SDL_DestroyTexture(textura_text[1]);
	SDL_FreeSurface(panacek);//smazání surface panáèka
	for (int i = 0; i < 6; i++)
	{
		SDL_FreeSurface(zeme[i]);//smazání surface prostøedí
	}
	for (int i = 0; i < 2; i++)
	{
		SDL_FreeSurface(prekazky[i]);//smazání surface pøekáky
	}
	SDL_FreeSurface(cil[0]);//smazání surface cíle
	SDL_FreeSurface(text[0]);//smazání surface textu
	SDL_FreeSurface(text[1]);
	SDL_DestroyRenderer(renderer);//smazání struktury Renderer
	SDL_DestroyWindow(window);//smazání struktury okna
	SDL_Quit();
	return 0;
}