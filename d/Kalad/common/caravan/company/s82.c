#include "../default.h"
inherit CVAN_ROOM;

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define EGUARD	(NPC + "tceguard")

object ob1;
object ob2;

void
create_cvan_room()
{
    set_hear_bell(0);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Inner Sanctum");
    set_long("You enter a magnificently decorated hall.\n"+
      "This massive place is built entirely out of solid marble. Grand pillars "+
      "lie directly to the north and south. More gigantic pillars can be seen "+
      "to the west, all perfectly sculpted and lining the exquisite red "+
      "carpet, which begins here and heads westward. Up above, on the "+
      "ceiling are large crystalline chandeliers, providing a brilliant "+
      "illumination for the entire hall. Behind the pillars to the north "+
      "and south are immense alcoves, so large that they are more like "+
      "rooms, than mere recesses aside this grand hall.\n");

    add_item(({ "pillars" }), "Huge pillars built out of solid marble, they "+
      "must be as large as the great redwoods of the Hespyre mountains.\n");

    add_item(({ "carpet" }), "A magnificent carpet woven from some wonderfully "+
      "soft substance. The carpet stretches out to the west.\n");

    add_item(({ "chandeliers" }), "Great crystalline chandeliers that tinkle "+
      "ever so slightly, creating a soothing melody that flows throughout "+
      "the room.\n");

    add_item(({ "alcoves" }), "All you can see are flickering shadows "+
      "whenever you gaze in their direction. It must be some trick of the "+
      "light, and the fact that most of your view is obscured by the "+
      "gigantic pillars aside the grand carpet.\n");

    add_exit(CVAN + "company/s81", "west");
    add_exit(CVAN + "company/s73", "north");
    add_exit(CVAN + "company/s79", "south");

    clone_object(CVAN + "door/isdoor1")->move(TO);
}

int
query_move()
{
    object *ob;
    int pres, i;

    ob = FILTER_LIVE(all_inventory(this_object()));
    pres = 0;

    for (i = 0; i < sizeof(ob); i++)
    {
	if (ob[i]->query_name() == "Nadar")
	{
	    pres = 1;
	}
    }

    if (pres == 1)
    {
	write("The elite company guard blocks your way west.\n");
	say(QCTNAME(TP) + " tries to go west but is stopped by the elite company guard.\n");
    }
    return pres;
}
