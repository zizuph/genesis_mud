/*      Field room one off the ring road around pelargir
 *  
 *      Copyright (C) Jim Fraser  1995 (Theory)
 *
 *      Revisions  (by) (date)
 */

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h";

void
create_field()
{
}

void
create_area_room()
{
    object *herbs_here = HERB_MASTER->query_herbs("subtropical");

    set_area("southern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(4);
    set_areadesc("field");
    set_grass("long green");

/*
    remove_item("ground");
    remove_item("furrows");
    remove_item("field");
 */

    create_field();

    set_up_herbs( ({ ONE_OF_LIST( HERB_MASTER->query_herbs("middle earth") ),
                     ONE_OF_LIST( herbs_here ), 
                     ONE_OF_LIST( herbs_here ) }), ({ "field", "ground", }), 3);
}

void
add_road(string extra = "")
{
   string desc =
	"The old road used to get around Pelargir is a little to the east "
   +	"of here. ";

   if 	(strlen(extra))
	desc += (" " + extra);

   add_item(({"road" , "old road" ,}), BSN(desc));
}

void
add_sirith(string where, string *what = ({}), string extra = "")
{
    string desc = "";
	
    switch (where)
    {
    case "north":
	desc +="Just to the northeast of here a small bridge crosses the "
	     + "northern arm of the river Sirith. The river is not wide and "
	     + "runs very quickly, and the bridge is there so travellers do "
	     + "not need to risk their lives crossing it. It enters the "
	     + "city under the wall a short distance to the east";
	break;
    case "south":
	desc +="The southern arm of the river Sirith can be seen from "
	     + "here flowing lazily into the Anduin off to the east. A "
	     + "wooden bridge crosses the larger arm of the river southeast "
	     + "of here, placed there so wagons could cross the river.";
	break;
    default:
	break;
    }
	
    if (strlen(extra))
	desc += (" " + extra);
    add_item(({"sirith","river","river sirith","arm",})+ what,BSN(desc)); 

}

void
add_walls()
{
    string desc = "The Pelargir city walls are to the east of here, and it "
                + "is possible to see the tops, and occasionally, a guard "
                + "patrolling the battlements.";
    add_item(({"walls" , "city walls" , "wall",}),BSN(desc));
}

void
add_city()
{
    string desc = "Pelargir is the main port city of Gondor, and its size "
	 	+ "reflects that. The city walls stretch for as far as the " 
		+ "can see in the east, blocking out all views of the "
		+ "Anduin.";
    add_item(({"pelargir","city",}),BSN(desc));
}

void
add_fence(string extra = "")
{
    string desc = "The fence blocks off all passage to the west.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"fence",}),BSN(desc));
}

void
add_house()
{
    string desc = "The house you can see on the other side of the fence "
		+ "looks very lived it. It does not appear to be very "
		+ "strong, but it looks well used, and there is smoke "
		+ "coming from the chimney";
    add_item(({"house", "shack", "farmhouse",}),BSN(desc));
}

void
add_field()
{
    string desc = "The fields to the west look as though they are used "
		+ "for cattle farming, as the fields are not furrowed.";
    add_item(({"fields" , "field",}), BSN(desc));
    add_item(({"furrow", "furrows", }), "The fields are not furrowed.\n");
}

void 
add_bridge(string where)
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
    add_item(({"wooden bridge", "bridge", "old wooden bridge",}),BSN(desc));
}

