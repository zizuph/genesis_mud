/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/warea_handler/ah_entry.c
* Comments: 
*/


inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    	set_short("The endless wastes");
    	set_long("The wastes seem to go on forever. The plains are "+
             	"basically lifeless. Hills rise and fall gently and "+
             	"majestically off into the distance. Not many could "+
             	"love this land, but apparently some do.\n");


    	if (LOAD_ERR("/d/Cirath/katakoro/wastes/area_handler/area_handler"))
    	{
        	write("Can't load map handler, please report immediately...\n");
        	return;
    	}

    	add_exit("", "west", "@@enter_map:/d/Cirath/katakoro/wastes/area_handler/area_handler|E@@");
    	add_exit("", "east", "@@enter_map:/d/Cirath/katakoro/wastes/area_handler/area_handler|E@@");
    	add_exit("", "north", "@@enter_map:/d/Cirath/katakoro/wastes/area_handler/area_handler|E@@");
}

