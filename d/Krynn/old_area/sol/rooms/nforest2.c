/* Forest coded by Lord Rastlin */
/* Modified by Teth, Feb.13,96 */

#include "local.h"

inherit FOROUTROOM;

#include "/d/Krynn/common/defs.h"
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mixedforest",}));

void
reset_solace_room()
{
    set_searched(random(2));
}

void
create_solace_room()
{
    set_place(FOREST);

    set_long_desc("The terrain here is somewhat hilly, but it still " +
             "has thick forest. What might be an animal trail leads " +
             "northeast into some of the foothills of the Sentinel Peaks " +
             "mountain range. This trail also goes southwest, back towards " +
             "civilization. Small bushes line the side of the trail, and " +
             "a boulder rests comfortably on the trail's edge.");
    add_item(({"foothills","hills","mountain range","mountains",
               "Sentinel Peaks", "sentinel peaks", "Peaks", "peaks"}),
               "These surround you, giving the area a measure of " +
               "distinction.\n");
    add_item("terrain", "It is somewhat hilly, caused by this area's " +
             "location in the Sentinel Peaks mountain range.\n");
    add_item("trail", "It has a boulder on it, and leads upwards to the " +
             "northeast.\n");
    add_item("bush", "There are many of them, you'd be better off to look " +
             "at all of them.\n");  
    add_item("bushes", "Nothing too out of the ordinary. A little bit of " +
	     "holly and sumac, perhaps.\n");
    add_item(({"forest","trees","thick forest"}),
	     "It's a thick forest with typical north temperate trees, like " +
	     "pine and poplar.\n");
    add_item(({"pine trees", "poplar trees"}), "They are the dominating " +
             "vegetation, cooling the local temperature slightly.\n");
    add_item("boulder", "It is a large boulder that sits on the trail, " +
	     "disturbing no one.\n");
    add_cmd_item("boulder", ({ "move", "push" }), ({ "@@push", "@@push"}));
    
    add_exit(TDIR + "nforest3", "southwest");
    add_exit(TDIR + "nforest4", "northeast");
    
    reset_room();
    seteuid(getuid(TO));
    set_up_herbs(({ONE_OF(herbs),ONE_OF(herbs),ONE_OF(herbs),
        ONE_OF(herbs)}),({"bushes","trail",}), 3);
}

string
push() 
{ 
    return "It's way too heavy for you, and you imagine everyone else!\n"; 
}


