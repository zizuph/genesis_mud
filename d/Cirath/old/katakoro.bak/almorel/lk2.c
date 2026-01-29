/*
	Asmodean, March 18, 1995
	LK2	- Property of the Cirath Domain
*/

#include "almorel.h"
#include "Lakes.h"

inherit LAKE_MASTER;

void
create_lakeside()
{
    set_short("Lakeside Street");
    set_long("The street, known by the locals as the Mist Street, "+
	"runs a parallel course with the coastline of the "+
	"Lake of Mists. The street is covered in packed snow and "+
	"glare ice hidden by new snowfall. People dressed in thick "+
	"furs and hide boots stride purposefully by without paying "+
	"you any heed. The walls of the houses facing the lake "+
	"have been battered and packed with snow.\n\n");

    add_exit(ALMOREL+"lk1","southwest");
    add_exit(ALMOREL+"lk3","northeast");
}

