/*
 *  temple3.c
 *
 *  This is a room for the druid temple in Mithas.
 *
 *  Created by Carnak, January 2016
 */
 
#pragma save_binary

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

inherit MITHAS_IN;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#include "./local.h"


public int     pass_tapestry(string str);

create_mithas_room()
{
    set_short("Southeast corner");
    set_long("@@long_desc");
	
    add_exit(TDIR +"temple2", "west", 0);
    add_exit(TDIR +"temple5", "northwest", &pass_tapestry("northwest"));
    add_exit(TDIR +"temple6", "north", 0);

    add_item(({"floor","ground","weeds","grass","rocks","dirt",
	"granite rocks"}),
    "The floor is tiled with smooth rocks and covered in dirt, some "+
    "grass and weeds have emerged from beneath the granite rocks.\n");

    add_item(({"ancient ruin","ruin","temple","building"}),
    "This must be the temple of an ancient druid order that once "+
    "populated Mithas.\n");

    add_item(({"stones","blocks","granite blocks","granite stones"}),
    "The stones are square gray granite blocks which have "+
    "been worn down by time and harsh weather.\n");

    add_item(({"walls","roots","wall","cracks"}),
    "The roots have found their way into the cracks between the "+
    "stones that make up the walls, seemingly reinforcing the "+
    "structural stability.\n");

    add_item(({"wooden roof","roof","hatch","ceiling"}),
    "The wooden roof appears to be in good condition. A hatch "+
    "in the roof has been propped open, allowing light to "+
    "spread throughout the temple during the day.\n");

    add_item(({"hallway"}),
    "You are in the midst of the hallway, it stretches westwards. "+
    "The hallway is nearly void of decorations.\n");

    add_item(({"decorations","decor"}),
    "In the corners of the hallway, large floor mounted candelabras "+
    "have been placed to evenly spread the light throughout the "+
    "temple.\n");

    add_item(({"candelabras","candelabra","corner"}),
    "A floor mounted black iron candelabra stands in each corner of "+
    "the hallway, a skillfully crafted ornament resembling a tree "+
    "growing out from the floor. Within the crown of the tree, a "+
    "massive tallow candle has been set, to shed light upon the "+
    "temple in the dead of night.\n");
	
	add_item(({"candle","crown"}),"Within the crown of the tree "+
	"candelabra, a massive tallow candle has been set, to shed light "+
	"upon the temple in the dead of night.\n");
	
    add_item(({"doorway","arched doorway","arch"}),
    "This is a stone doorway in the form of an arch, it leads "+
    "northwest.\n");
	
    add_item(({"atrium"}),
    "Through an arched doorway to the northwest lies the temple "+
	"atrium.\n");
	 
    add_cmd_item(({"candelabra","candle"}),"light","@@light_candle");
    add_cmd_item(({"candelabra","candle"}),"extinguish","@@extinguish_candle");
}

string
long_desc()
{ 
    return tod_desc()+ "" +season_desc()+
    "You are in the southeast corner of the hallway, which stretches "+
    "north and westwards. In the corner of the hallway, a large floor "+
    "mounted candelabra has been placed to evenly spread the light "+
    "throughout the temple. The north passage exhibits greater decay "+
    "than the rest of the temple and through an arched doorway to the "+
    "northwest lie an atrium.\n";
}

int
light_candle()
{
    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
            break;
            
        case NIGHT:
        case EVENING:
        write("The candle is already lit, sharing its warm glow "+
        "with the dark recesses of the temple.\n");
            break;
            
        case EARLY_MORNING:
        case MORNING:
        case NOON:
        case AFTERNOON:
        write("There would be no point lighting a candle at this "+
        "time of day.\n");
            break;
    }
    return 1;
}

int
extinguish_candle()
{
    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
            break;
            
        case NIGHT:
        case EVENING:
        write("You consider extinguishing the flames that "+
        "spread a warm glow throughout the temple but your "+
        "instincts prevent you, a divine presence linger "+
        "in this temple.\n");
            break;
            
        case EARLY_MORNING:
        case MORNING:
        case NOON:
        case AFTERNOON:
        write("The candle is not lit.\n");
            break;
    }
    return 1;
}

int
pass_tapestry(string str)
{
    write("You step through the arched doorway, into the atrium.\n");
    say(QCTNAME(TP) + " steps through the arched doorway, towards the atrium.\n");
    return 0;
}