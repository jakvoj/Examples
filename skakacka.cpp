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
	int souradnice_mapa[2][20];//souradnice objekt� - respektive prost�ed�
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
	int velikost_mapa[2][20];//pixelov� velikost jednotliv�ch objekt�
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
	int souradnice_prekazka[2][20];//sou�adnice p�ek�ek
	souradnice_prekazka[0][0] = 500;
	souradnice_prekazka[1][0] = 570;
	souradnice_prekazka[0][1] = 1360;
	souradnice_prekazka[1][1] = 570;
	int velikost_prekazka[2][20];//velikost p�ek�ek
	velikost_prekazka[0][0] = 180;
	velikost_prekazka[1][0] = 30;
	velikost_prekazka[0][1] = 540;
	velikost_prekazka[1][1] = 30;
	int souradnice_cil[2][20];//sou�adnice c�le - je to pole, proto�e by se to dalo t�eba roz���it o checkpointy
	souradnice_cil[0][0] = 2350;
	souradnice_cil[1][0] = 319;
	int velikost_cil[2][20];
	velikost_cil[0][0] = 176;
	velikost_cil[1][0] = 251;
	int souradnice_text[2][20];//pou�ito pro texty, respektive pro v�hru a prohru
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
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 600, 0);//vytvo�en� hlavn�ho okna
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);//vytvo�en� rendereru pro okno, do kter�ho bude vykreslovat, star� se o samotn� vykreslov�n�							
	SDL_Surface* panacek = SDL_LoadBMP("panacek_vpravo.bmp");//vytvo�en� surface panacek a na�ten� jeho textury
	SDL_Surface* zeme[20];//surface pro prost�ed�
	SDL_Surface* prekazky[20];//surface pro p�ek�ky
	SDL_Surface* cil[20];//surface pro c�le
	SDL_Surface* text[20];//surface pro text
	for (int i = 0; i < 6; i++)
	{
		zeme[i] = SDL_LoadBMP("zeme.bmp");//na vytvo�en� prost�ed� jsem pou�il pouze jednu texturu, proto for cyklus
	}
	prekazky[0] = SDL_LoadBMP("bodce1.bmp");//na�ten� p�ek�ek
	prekazky[1] = SDL_LoadBMP("bodce2.bmp");
	cil[0] = SDL_LoadBMP("cil.bmp");//na�ten� c�le
	text[0] = SDL_LoadBMP("vyhra_text.bmp");//na�ten� text�
	text[1] = SDL_LoadBMP("prohra_text.bmp");
	Uint32 WhiteColor = SDL_MapRGB(panacek->format, 255, 255, 255);//nastaven� barvy, kter� se nebude vykreslovat, v na�em p��pad� 255 255 255, tedy b�l�
	SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//samotn� aplikov�n� na texturu
	for (int i = 0; i < 6; i++)
	{
		SDL_SetColorKey(zeme[i], SDL_ENABLE, WhiteColor);//zpr�hledn�n� b�l� prost�ed�
	}
	for (int i = 0; i < 2; i++)
	{
		SDL_SetColorKey(prekazky[i], SDL_ENABLE, WhiteColor);//zpr�hledn�n� b�l� u p�ek�ek
	}
	SDL_SetColorKey(cil[0], SDL_ENABLE, WhiteColor);//zpr�hledn�n� b�l� u c�le
	SDL_SetColorKey(text[0], SDL_ENABLE, WhiteColor);//zpr�hledn�n� b�l� u textu
	SDL_SetColorKey(text[1], SDL_ENABLE, WhiteColor);
	SDL_Texture * textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvo�en� struktury SDL_Texture pro pan��ka a tedy ulo�en� do gpu ram
	SDL_Texture * textura_zeme[20];//vytvo�en� pole struktur SDL_Texture pro prost�ed�
	SDL_Texture * textura_prekazky[20];//vytvo�en� pole struktur SDL_Texture pro p�ek�ky
	SDL_Texture * textura_cile[20];//vytvo�en� pole struktur SDL_Texture pro c�le
	SDL_Texture * textura_text[20];//vytvo�en� pole struktur SDL_Texture pro text
	for (int i = 0; i < 6; i++)
	{
		textura_zeme[i] = SDL_CreateTextureFromSurface(renderer, zeme[i]);//samotn� vytvo�en� SDL_Texture pro prost�ed�
	}
	for (int i = 0; i < 2; i++)
	{
		textura_prekazky[i] = SDL_CreateTextureFromSurface(renderer, prekazky[i]);//samotn� vytvo�en� SDL_Texture pro p�ek�ky
	}
	textura_cile[0] = SDL_CreateTextureFromSurface(renderer, cil[0]);//samotn� vytvo�en� SDL_Texture pro c�le
	textura_text[0] = SDL_CreateTextureFromSurface(renderer, text[0]);//samotn� vytvo�en� SDL_Texture pro text
	textura_text[1] = SDL_CreateTextureFromSurface(renderer, text[1]);
	SDL_Event* event = new SDL_Event; //struktura, kter� uchov�v� ud�losti, tedy nap��klad stisk kl�vesy
	int x = 50;
	int y = 382;
	while (!quit)//hlavn� smy�ka samotn� hry - zde se st�le opakuje kolob�h - na�ten� vstupu, zm�na sc�ny, vykreseln� sc�ny
	{
		while (SDL_PollEvent(event))//pokud skon�� fronta p��choz�ch ud�lost�, tak dojde k ukon�en� t�to smy�ky 
		{
			if (event->type == SDL_QUIT)
				quit = true;
			if (event->key.keysym.sym == SDLK_RIGHT)//pokud dojde ke stisku kl�vesy doprava
			{
				if (vyhra == false && prohra == false)//pokud je prohra nebo vyhra, tak se panacek zastav�
				{
					if (poloha + 162 <= souradnice_mapa[0][4] + 1350 && poloha + 162 <= souradnice_cil[0][0] + 1350)//zaji�t�n� kolize s prost�ed�m
					{
						if (poloha >= 200 && poloha <= 1595)//zde se pohybuje prost�ed�
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
						else//zde se pohybuje pan��ek
						{
							x += 5;
							poloha += 5;
							vpravo = true;
						}
					}
				}
			}
			if (event->key.keysym.sym == SDLK_LEFT)//pokud dojde ke stisku kl�vesy doleva
			{
				if (vyhra == false && prohra == false)//pokud je prohra nebo vyhra, tak se panacek zastav�
				{
					if (poloha >= souradnice_mapa[0][1] + 30 - 45)//zaji�t�n� kolize s prost�ed�m
					{
						if (poloha >= 200 && poloha <= 1595)//zde se pohybuje prost�ed�
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
						else //zde se pohybuje pan��ek
						{
							x -= 5;
							poloha -= 5;
							vpravo = false;
						}
					}
				}
			}
			if (event->key.keysym.sym == SDLK_UP)//pokud dojde ke stisku kl�vesy nahoru
			{
				if (vyhra == false && prohra == false)//pokud je prohra nebo vyhra, tak se panacek zastav�
				{
					vyskok = true;//aktivov�n� v�skoku
				}
			}
		}
		if (vpravo == true)//pokud se pohybujeme doprava, tak dojde ke kolizi jinak ne� ->
		{
			for (int i = 0; i < 2; i++)
			{
				if (y + 188 == souradnice_prekazka[1][i] && x + 100 > souradnice_prekazka[0][i] && x < souradnice_prekazka[0][i] + velikost_prekazka[0][i])
				{
					prohra = true;//aktivov�n� prohry
				}
			}
		}
		if (vpravo == false)// -> kdy� se pohybujeme do�eva; m��e zato to, �e nohy pan��ka nejsou �pln� v okraj�ch textury, tak�e chce kolize nastavit pro ka�d� sm�r zvl᚝
		{
			for (int i = 0; i < 2; i++)
			{
				if (y + 188 == souradnice_prekazka[1][i] && x + 162 > souradnice_prekazka[0][i] && x + 62 < souradnice_prekazka[0][i] + velikost_prekazka[0][i])
				{
					prohra = true;//aktivov�n� prohry
				}
			}
		}
		if (vyskok == true)//pokud stiskeneme kl�vesu nahoru
		{
			if (vyskok_vyska <= 120 && dolu == false)//prvn� ��st skoku
			{
				SDL_Delay(10);//prodleva 10 ms, regulujeme t�m rychlost skoku
				y--;
				vyskok_vyska++;
			}
			if (vyskok_vyska >= 120)
			{
				dolu = true;
				vyskok_vyska = vyskok_vyska + zbytek;//zbytek zde slou�� pro dokon�en� skoku, pokud jsme na plo�in� nad zem�
				zbytek = 0;
			}
			if (vyskok_vyska > 0 && dolu == true)//druh� ��st skoku
			{
				SDL_Delay(10);//prodleva 10 ms, regulujeme t�m rychlost skoku
				y++;
				vyskok_vyska--;
				if (vyskok_vyska == 0)//dokon�en� skoku
				{
					dolu = false;
					vyskok = false;
				}
				if (y + 188 == souradnice_mapa[1][5] && x + 100 > souradnice_mapa[0][5] && x < souradnice_mapa[0][5] + velikost_mapa[0][5] && vpravo == true && zbytek == 0)//nastaven� podm�nek pro skok z plo�iny nad zem�; sk��eme sm�rem doprava
				{
					vyskok = false;
					dolu = false;
					zbytek = vyskok_vyska;
					vyskok_vyska = 0;
				}
				if (y + 188 == souradnice_mapa[1][5] && x + 162 > souradnice_mapa[0][5] && x + 62 < souradnice_mapa[0][5] + velikost_mapa[0][5] && vpravo == false && zbytek == 0)//nastaven� podm�nek pro skok z plo�iny nad zem�; sk��eme sm�rem doleva
				{
					vyskok = false;
					dolu = false;
					zbytek = vyskok_vyska;
					vyskok_vyska = 0;
				}
			}
		}
		if (y + 188 == souradnice_mapa[1][5] &&  x > souradnice_mapa[0][5] + velikost_mapa[0][5] && vpravo == true && vyskok == false)//pokud p�ejdeme plo�inu, tak spadneme; jdeme sm�rem doprava
		{
			pad = true;
		}
		if (y + 188 == souradnice_mapa[1][5] && x + 162 < souradnice_mapa[0][5] && vpravo == false && vyskok == false)//pokud p�ejdeme plo�inu, tak spadneme; jdeme sm�rem doleva
		{
			pad = true;
		}
		if (pad == true)//proveden� p�du
		{
			if (zbytek != 0)
			{
				SDL_Delay(10);//prodleva 10 ms, regulujeme t�m rychlost p�du
				y++;
				zbytek--;
				if (zbytek == 0)
				{
					pad = false;
				}
			}
		}
		if (vyskok == true || pad == true)//pokud sk��eme nebo pad�me
		{
			if (vpravo == true)//pokud sk��eme doprava
			{
				SDL_FreeSurface(panacek);//smaz�n� obsahu SDL_Surface pan��ka
				SDL_DestroyTexture(textura_panacek);//smaz�n� obsahu SDL_Texture pan��ka
				panacek = SDL_LoadBMP("panacek_vpravo_nahoru.bmp");//na�ten� sk�kaj�c�ho pan��ka
				SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//nastaven� b�l� jako pr�hledn�
				textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvo�en� SDL_Texture z pan��ka - p�esunut� do ram gpu
			}
			if (vpravo == false)//pokud sk��eme doleva
			{
				SDL_FreeSurface(panacek);//smaz�n� obsahu SDL_Surface pan��ka
				SDL_DestroyTexture(textura_panacek);//smaz�n� obsahu SDL_Texture pan��ka
				panacek = SDL_LoadBMP("panacek_vlevo_nahoru.bmp");//na�ten� sk�kaj�c�ho pan��ka
				SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//nastaven� b�l� jako pr�hledn�
				textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvo�en� SDL_Texture z pan��ka - p�esunut� do ram gpu
			}
		}
		if (vyskok == false)//pokud jdeme
		{
			if (vpravo == true && pad == false)//pokud jdeme doprava
			{
				SDL_FreeSurface(panacek);//smaz�n� obsahu SDL_Surface pan��ka
				SDL_DestroyTexture(textura_panacek);//smaz�n� obsahu SDL_Texture pan��ka
				panacek = SDL_LoadBMP("panacek_vpravo.bmp");//na�ten� pan��ka jdouc� doprava
				SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//nastaven� b�l� jako pr�hledn�
				textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvo�en� SDL_Texture z pan��ka - p�esunut� do ram gpu
			}
			if (vpravo == false && pad == false)//pokud jdeme doprava
			{
				SDL_FreeSurface(panacek);//smaz�n� obsahu SDL_Surface pan��ka
				SDL_DestroyTexture(textura_panacek);//smaz�n� obsahu SDL_Texture pan��ka
				panacek = SDL_LoadBMP("panacek_vlevo.bmp");//na�ten� pan��ka jdouc� doleva
				SDL_SetColorKey(panacek, SDL_ENABLE, WhiteColor);//nastaven� b�l� jako pr�hledn�
				textura_panacek = SDL_CreateTextureFromSurface(renderer, panacek);//vytvo�en� SDL_Texture z pan��ka - p�esunut� do ram gpu
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//p�ekreslen� okna b�lou barvou - jinak by star� sc�na z�stala a vytvo�ila by se "mazanice"
		SDL_RenderClear(renderer);//samotn� p�ekreslen� b�lou barvou
		SDL_Rect umisteni_panacek = { x, y, 162, 188 };//nastaven� rozm�r� a polohy pan��ka; textura pan��ka se bude vykreslovat na obd�ln�k
		SDL_Rect umisteni_zeme[20];//vytvo�en� obdeln�k� pro prost�ed�
		SDL_Rect umisteni_prekazka[20];//vytvo�en� obdeln�k� pro p�ek�ky
		SDL_Rect umisteni_cil[20];//vytvo�en� obdeln�k� pro c�l
		SDL_Rect umisteni_text[20];//vytvo�en� obdeln�k� pro texty
		for (int i = 0; i < 6; i++)
		{
			umisteni_zeme[i] = { souradnice_mapa[0][i], souradnice_mapa[1][i], velikost_mapa[0][i], velikost_mapa[1][i] };//nastaven� rozm�r� obdeln�k� pro prost�ed�
		}
		for (int i = 0; i < 2; i++)
		{
			umisteni_prekazka[i] = { souradnice_prekazka[0][i], souradnice_prekazka[1][i], velikost_prekazka[0][i], velikost_prekazka[1][i] };//nastaven� rozm�r� obdeln�k� pro p�ek�ky
		}
		umisteni_cil[0] = { souradnice_cil[0][0], souradnice_cil[1][0], velikost_cil[0][0], velikost_cil[1][0] };//nastaven� rozm�r� obdeln�ku pro c�l
		umisteni_text[0] = { souradnice_text[0][0], souradnice_text[1][0], velikost_text[0][0], velikost_text[1][0] };//nastaven� rozm�r� obdeln�k� pro texty
		umisteni_text[1] = { souradnice_text[0][1], souradnice_text[1][1], velikost_text[0][1], velikost_text[1][1] };
		SDL_RenderCopy(renderer, textura_panacek, NULL, &umisteni_panacek);//p�esunut� textury pan��ka na obdeln�k
		for (int i = 0; i < 6; i++)
		{
			SDL_RenderCopy(renderer, textura_zeme[i], NULL, &umisteni_zeme[i]);//p�esunut� textury prost�ed� na obdeln�k 
		}
		for (int i = 0; i < 2; i++)
		{
			SDL_RenderCopy(renderer, textura_prekazky[i], NULL, &umisteni_prekazka[i]);//p�esunut� textury p�ek�ky na obdeln�k
		}
		SDL_RenderCopy(renderer, textura_cile[0], NULL, &umisteni_cil[0]);//p�esunut� textury c�le na obdeln�k
		if (poloha + 162 >= souradnice_cil[0][0] + 1350)
		{
			SDL_RenderCopy(renderer, textura_text[0], NULL, &umisteni_text[0]);//pokud vyhrajeme, tak se vyp�e text v�hry
			vyhra = true;
		}
		if (prohra == true)
		{
			SDL_RenderCopy(renderer, textura_text[1], NULL, &umisteni_text[1]);//pokud vyhrajeme, tak se vyp�e text prohry
		}
		SDL_RenderPresent(renderer);//samotn� vykreslen� sc�ny
	}//konec hlavn� smy�ky
	SDL_DestroyTexture(textura_panacek);//smaz�n� textury pan��ka na konci programu
	for (int i = 0; i < 6; i++)
	{
		SDL_DestroyTexture(textura_zeme[i]);//smaz�n� textury prost�ed�
	}
	for (int i = 0; i < 2; i++)
	{
		SDL_DestroyTexture(textura_prekazky[i]);//smaz�n� textury p�ek�ky
	}
	SDL_DestroyTexture(textura_cile[0]);//smaz�n� textury c�le
	SDL_DestroyTexture(textura_text[0]);//smaz�n� textury textu
	SDL_DestroyTexture(textura_text[1]);
	SDL_FreeSurface(panacek);//smaz�n� surface pan��ka
	for (int i = 0; i < 6; i++)
	{
		SDL_FreeSurface(zeme[i]);//smaz�n� surface prost�ed�
	}
	for (int i = 0; i < 2; i++)
	{
		SDL_FreeSurface(prekazky[i]);//smaz�n� surface p�ek�ky
	}
	SDL_FreeSurface(cil[0]);//smaz�n� surface c�le
	SDL_FreeSurface(text[0]);//smaz�n� surface textu
	SDL_FreeSurface(text[1]);
	SDL_DestroyRenderer(renderer);//smaz�n� struktury Renderer
	SDL_DestroyWindow(window);//smaz�n� struktury okna
	SDL_Quit();
	return 0;
}