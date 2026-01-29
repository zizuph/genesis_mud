/*
 * Goblin village in Mirkwood.
 * Varian 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";
inherit MIRKWOOD_STD_DIR + "room";


void create_room()
{
    
    set_mirkwood_location(LOCATION_EAST_EDGE);
    
       

    set_short("On a small path in Mirkwood forest.");
    
    set_long("You are currently on a small path which seems to wind in from " +
        "the northwest before climbing the tall hill which rises up out of the "
        + VBFC("location_desc") + " of Mirkwood forest to the southeast. " +
    	"You see the faint light from the " + VBFC("light_type") + 
    	" of the " + VBFC("day_desc") +" " + VBFC("sun_moon") + " as it " +
    	"prys its way through the black trees and displays the rough stone " +
    	"walls of a crude village perched atop the rocky hill. All around you, " +
    	"the thick underbrush seems to be anxiously awaiting the unwary " +
    	"creature who might inadvertently stray from the path. Partially " +
        "hidden in the gloomy shadows, you notice a scarred boulder which " +
        "rests beside the path.\n");

    add_item_light(({"moon","stars","sun","rising sun","setting sun","noon sun",
			"night stars", "night moon", "afternoon sun", "morning sun"}),
    	"Your eyes drink in the " + VBFC("light_type") + " from " +
    	"the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " as it shines " +
    	"upon the village atop the hill.\n", LIGHT_ALL);
	add_item_light(({"boulder", "scarred boulder", "marks", "markings"}),
	    "This boulder is large and rough, and covered with marks which " +
        "actually appear to be crude letters which have been carved into " +
        "the stone itself. Reading carefully, you gather that this serves " +
        "as a sign for the goblin village of Hargnak which stands upon the " +
        "hill before you.\n", LIGHT_ALL);
	add_item_light(({"sign", "stone sign"}),
	    "This is certainly not the most sophisticated sign you have ever " +
        "seen, but it seems to indicate that the name of the village on " +
        "top of the hill is named Hargnak.\n", LIGHT_ALL);
	add_item_light(({"hill", "tall hill", "rocky hill"}),
	    "This craggy hill seems to claw its way free of the black trees of " +
        "Mirkwood and into the freedom of the " + VBFC("day_desc") +
        " " + VBFC("sun_moon") + " above, the stone walls of the village " +
        "crowning it as if it were some long forgotten king.\n", LIGHT_ALL);
	add_item_light(({"village", "hargnak", "Hargnak"}),
	    "This very path you are walking along climbs up the rocky hill " +
        "and past the stone walls of the village of Hargnak. Hargnak " +
        "appears to be a village inhabited by goblins who use the Old " +
        "Road to travel and meet their kin in the Misty Mountains " +
        "to the west.\n", LIGHT_ALL);
	add_item_light(({"walls", "rough walls", "stone walls", "village walls"}),
	    "You can see the rough, stone walls of the village, crowning the " +
        "peak of the hill before you. For all of their rough appearance, " +
        "you suspect that these walls would be very effective in battling " +
        "any threat which might approach this village.\n", LIGHT_ALL);
	add_item_light(({"forest", "mirkwood", "Mirkwood"}),
	    "This is the legendary Mirkwood forest. There have always " +
	    "been stories of how dangerous this forest has been for " +
	    "the unwary traveller, and as you glance around at the " +
	    "surrounding forest, you can understand why.\n", LIGHT_ALL);
	add_item_light(({"road","path","ground", "trail"}),
	    "A well-worn dirt path comes from the village of Hargnak, winding down " +
	    "the hill before reaching back towards the Old Road before it is " +
	    "seemingly swallowed up by the gloom of Mirkwood forest. You could " +
        "follow this path directly into the village of Hargnak if you " +
        "wanted to.\n", LIGHT_ALL);
	add_item_light(({"sky", "light", "up"}),
	    "You are actually able to see some of the the sky here, unlike just about " +
	    "everywhere else in Mirkwood. The " + VBFC("light_type") + " from " +
	    "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " shines " +
	    "its light across the village which crowns the hill before you. \n",
	    LIGHT_ALL);
	add_item_light(({"shadow", "shadows"}),
	    "The forest of Mirkwood is full of sinister looking shadows " +
	    "which almost appear alive, giving you the impression they are " +
        "looking for any unwary victims.\n", LIGHT_ALL);
	

    add_exit("hargnak2", "enter", "@@hargnak@@");
    add_exit("hargnak2", "up", "@@hargnak@@",0,1);
    add_exit("hargnak2", "follow", "@@hargnak@@",0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r01/p43", "northwest");
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r01/f44", "north", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r01/f45", "northeast", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r02/f45", "east", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r03/f45", "southeast", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r03/f44", "south", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r03/f43", "southwest", 0,0,1);
    add_exit(MIRKWOOD_SOUTH_FOREST_DIR + "r02/f43", "west", 0,0,1);
}
int
gairent()
{
    write("You follow the path as it up the hill into the village.\n\n\n");
    return 0;
}

void
init()
{
    ::init();
    add_action("do_read","read");
}
int
do_read(string str)
{
    if(!str)
    {
        write("Read what?\n");
        return 0;
    }
    if((str != "sign")  && (str != "boulder") && (str != "stone sign"))
    { 
        write("Read what?\n");
        return 0;
    }
    write("HARGNAK VILLAGE\n");
    SAYBB(" examines some rough markings on the boulder here.");
    return 1;
}
