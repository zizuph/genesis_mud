/*
 *	/d/Gondor/lebennin/rroad/rroad.c
 *
 *	The master for the road in south Lebennin 
 * running west of Pelargir outside of the city walls.
 *
 *	Olorin, October 1995
 *
 *      Revised November 1995 by Theory
 *
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

#define CROPS	({ "wheat", "barley", "oats", })

void
create_road()
{
}

void
create_area_room()
{
    set_area("southern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(8);
    set_areadesc("field");
    set_grass("long green");

    remove_item("road");
    remove_item("ground");
    remove_item("field");

    create_road();
}





void
add_road(string extra = "")
{
   string desc =
	"This old road running around the west side of Pelargir outside "
   +	"the city walls. It is used by peasants and traders who do not "
   +	"wish to enter the city. It is also used by travellers who cannot "
   +	"enter the city when the gates are locked.";

   if 	(strlen(extra))
	desc += (" " + extra);

   add_item(({"road" , "old road" , "ground", }), BSN(desc));
}

void
add_field(string extra= "")
{
    string  desc =
        "The fields west of the road look as if they are used "
      + "for farming, but one cannot see any cattle.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"field","fields"}), BSN(desc));
}


string
add_sirith(string where, string *what = ({}), string extra = "")
{
    string desc = "";
	
    switch (where)
    {
    case "north":
	desc +="The northern arm of the river Sirith flows under "
	     + "the wall of the city south of here. It is not very "
	     + "wide and therefore runs quickly. There is a small "
	     + "bridge crossing the river southeast of here";
	break;
    case "northcent":
	desc +="Just north of here a small bridge crosses the northern "
	     + "arm of the river Sirith. The river is not wide and runs "
	     + "very quickly, and the bridge is there so travellers do "
	     + "not need to risk their lives crossing it. It enters the "
	     + "city under the wall a short distance to the east";
	break;
    case "southcent":
	desc +="The southern arm of the river Sirith can be seen from "
	     + "here flowing lazily into the Anduin off to the east. A "
	     + "wooden bridge crosses the larger arm of the river south "
	     + "of here, placed there so wagons could cross the river.";
	break;
    case "south":
	desc +="Between you and the city walls the wide southern arm "
	     + "flows eastward into the Anduin. A wooden bridge can be "
	     + "seen northwest of here on the ring road, and the great "
	     + "stone bridge can be seen off to the east.";
	break;
    default:
	break;
    }
	
    if (strlen(extra))
	desc += (" " + extra);
    add_item(({"sirith", "river", "river sirith"}) + what, BSN(desc)); 
}

void
add_city(string extra = "")
{
    string desc = "Pelargir upon Anduin is the second largest city of "
        	+ "Gondor and the largest harbour of the realm.";
    if (strlen(extra))
	desc += (" " + extra);
    add_item(({"city", "pelargir"}), BSN(desc));
}

void
add_walls(string where, string extra ="")
{
    string desc = "";

    switch (where)
    {
	case "north":
	    desc +="The city walls of Pelargir rise high above the road "  
		 + "to the south and southeast. The north gate of the city "
                 + "is along the road to the east.";
	    break;
	case "central":
	    desc +="The great walls surrounding the harbour city of "
		 + "Pelargir seem to tower above the fields of Lebennin. "
		 + "The walls are "
		 + "to the east of here, and it is possible to see "
		 + "guards walking their patrol on the battlements.";
	    break;
	case "south":
	    desc +="The river cuts between the road and the walls here, "
		 + "but the towers standing aside the south gate of the "
		 + "city of Pelargir are visible off to the east.";
	    break;
	default:
	    break;
    }

    if (strlen(extra))
	desc += (" " + extra);

    add_item(({"wall", "walls", "city walls"}), BSN(desc));
}

void
add_birds()
{
    string desc = "The gulls flying overhead are a sign that the "
	 + "great river is near, flowing into the sea just south of "
	 + "Pelargir.";
    add_item(({"birds", "gulls"}), BSN(desc));
}


void
add_bridge(string where, string *what = ({}))
{
    string desc = "This wooden bridge passes over the river Sirith on the "
         + "ring road around Pelargir.";

    switch (where)
    {
	case "south":
	    desc  +=" It is quite wide, as it needs to get over the "
	    	  + "wide southern arm of the Sirith.";
	    break;
	case "north":
	    desc  +=" It appears to be rather run down, but still "
		  + "obviously usable for carts and other travellers.";
	    break;
	default:
	    break;
    }
    add_item(({"wooden bridge"}) + what,BSN(desc));
}
