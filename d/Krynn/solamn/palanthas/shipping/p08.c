/* Mortis 03.2015 
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "/d/Krynn/gsl_ships/palanthas-sparkle/ship.h"

inherit SHIP_BASE;
inherit "/d/Genesis/gsl_ships/lib/pier";

string
query_to_jail()
{
    return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "Fresh wood planks creak on this pier where great, "
        + "foreign ships land.\n"
        + "A marble sign.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Landing street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of wood, tar, and coffee borne "
	+ "on a cool, misty breeze from the bay. " + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Landing street and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily business. "
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Landing street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants, sailors, and dockhands make their way about the street. "
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Landing street amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour. " + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("A great pier off the northeast of Landing street");
    LONG("@@get_time_desc@@");

    ITEM(({"pier", "wood", "plank", "planks"}), "This pier has recently been "
        + "rebuilt to accommodate travellers from far off lands. Fresh wood "
        + "planks creak beneath your feet.\n");
    ITEM(({"sign", "marble sign"}), "The marble sign reads: Passage to "
        + "Sparkle\n");
    
    CMD(({"sign", "marble sign"}), "read", "@@read_sign@@");

	EXIT(SHIP + "s25", "southeast", 0, 0);

    add_pier_entry(MASTER_OB(this_object()), "Palanthas", "Passage to Sparkle");
    initialize_pier();
}

int
read_sign()
{
    write("The marble sign reads: Passage to Sparkle\n");
    return 1;
}