/*
* Created by: Asmodean
* Date: March 18, 1995
*
* File: /d/Cirath/katakoro/almorel/lk2.c
* Comments: BG - Property of Cirath Domain, edited by Luther Oct. 2001
*/

#pragma strict_types
#pragma save_binary

#include "defs.h"

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

    	add_exit(KAT_ALMO + "lk1", "southwest", 0, 1);
    	add_exit(KAT_ALMO + "lk3", "northeast", 0, 1);
    	reset_room();
}

