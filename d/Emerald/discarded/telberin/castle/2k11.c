/*
 * 2k11.c
 * This is one of the two second-floor balconies which overlook
 * the central courtyard. This may be the possible site for a quest
 * to recover some sort of item which is hidden atop the fountain
 * below... not sure - see Jasmine.
 * by Alaron August 30, 1996
 */

#define COURTYARD "/d/Emerald/telberin/castle/1k9"

#include "default.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Courtyard balcony");
    set_long("   A cool, gentle breeze brushes against your face as you "+
	     "look out at the central courtyard below. Several finely "+
	     "carved pieces of wooden furniture sit arranged neatly "+
	     "awaiting people to sit. A thick, gray stone railing rises "+
	     "up out of the balcony floor, allowing a slotted view "+
	     "of this balcony's twin across the other side of the "+
	     "courtyard. Down below, the central courtyard is "+
	     "dominated by the beautiful, softly bubbling fountain. A "+
	     "small archway leads back inside to the north.\n\n");

    add_item( ({"furniture", "carved furniture", "wooden furniture"}),
	     "The finely carved pieces of wooden furniture include "+
	     "three tables and six comfortable looking chairs.\n");
    add_item(({"tables", "three tables", "table"}),
	     "There are three beautiful tables out on the balcony. Each "+
	     "is made of finely carved, stained and lacquered wood with "+
	     "thick, black iron legs for sturdy support. Each table "+
	     "is host two chairs of the same style.\n");
    add_item(({"chairs","chair","two chairs","wooden chairs","wood chairs"}),
	     "Each of the chairs is made of finely carved, stained "+
	     "and lacquered wood, with thick black iron legs for "+
	     "additional support and sturdy comfort.\n");

    add_item(({"railing", "stone railing", "thick gray railing",
	       "gray stone railing"}),
	     "The gray stone railing rises out of the single piece of "+
	     "stone which serves as the balcony floor. It comes to waist "+
	     "height with thick slots in the middle for ventilation and "+
	     "view. At the top it thickens and widens into a very large "+
	     "railing which allows people to view the surroundings down "+
	     "below without endangering themselves.\n");

    add_item(({"down", "below", "down below", "courtyard"}),
	     "The courtyard is very beautiful and fills you with a "+
	     "relaxed, calm feeling as you look it over. It is dominated "+
	     "in the center by an enormous bubbling fountain.\n"+
	     "@@people_desc@@");

    /* The CASTLE_ROOM defaults us to an indoor setting, yet this is
     * outdoors, so remove the previous definition of the property.
     */
    remove_prop(ROOM_I_INSIDE);
    add_prop(ROOM_I_INSIDE,0);
    
    add_exit(CASTLE_DIR + "2k2","north");
}

string
people_desc()
{
    object other_room;
    mixed opeople;

    if (!LOAD_ERR(COURTYARD))
	other_room = find_object(COURTYARD);
    else
	return "The courtyard seems hazy and fuzzy. Perhaps there is "+
	    "something wrong with it? Perhaps a wizard could help?\n";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
	return "It looks like there is no one in the courtyard.\n";
    else
	return "From this vantage point, you can see "+COMPOSITE_LIVE(opeople)+
	    " in the courtyard.\n";
}
	
