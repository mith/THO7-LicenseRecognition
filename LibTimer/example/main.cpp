#include "exectimer.h"

#include <iostream>

int main(int argc, char** argv)
{
	int n = 100000000;
	
	// maak een timer object aan
	BaseTimer* bt = new BaseTimer();

	// start de timer
	bt->start();

	// doe iets wat je wilt meten hoe lang het duurt
	double m = 0;
	for (int i = 0; i < n; i++) m += cos((double)i);
	m /= (double)n;

	// stop de timer
	bt->stop();

	// rapporteer door de elapsed...() functies aan te roepen
	std::cout << "Time for the operation was: " << bt->elapsedSeconds() << " seconds (answer: " << m << ")" << std::endl;
	std::cout << "Time for a single cos()-operation was: " << static_cast<double>(bt->elapsedMicroSeconds()) / static_cast<double>(n) << " mu-seconds" << std::endl;


	// sla de gegevens op in het timer object onder een label
	bt->store("test cos");


	// doe het nog een keer of iets anders, wel eerst de timer resetten
	bt->reset();

	// start de timer
	bt->start();

	// doe iets wat je wilt meten hoe lang het duurt
	m = 0;
	for (int i = 0; i < n; i++) m += sin((double)i);
	m /= (double)n;

	// stop de timer
	bt->stop();

	// sla de gegevens op in het timer object onder een label
	bt->store("test sin");

	// bewaar de gegevens daarna in een bestand
	bt->save("testje.txt");

	std::cout << "Klaar" << std::endl;

	// wacht op input van de gebruiker om te stoppen
	std::cin >> m;

	delete bt;
	bt = nullptr;

	// we kunnen ook kijken hoe lang een programma runt
	ExecTimer* et = new ExecTimer();
	et->run("calc.exe",false);
	std::cout << "Calculator ran for " << et->elapsedSeconds() << " seconds." << std::endl;
	delete et;

	// wacht op input van de gebruiker om te stoppen
	std::cin >> m;

	return 0;
}

