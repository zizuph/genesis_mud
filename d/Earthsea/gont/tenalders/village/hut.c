/*  Farmer cottage
 *  Coded by Amelia 11/22/97
 *  contains dish of cream for cat quest
 *  contains chest with a scroll
 */

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "defs.h"

#define DOOR DOORS + "cottage_in.c"
#define CHEST TA_ITEMS+"scroll_chest.c"

object door;
object chest;

int CREAM_FOUND = 0;
int BED_MADE = 0;
string bed_made();
int make_bed(string str);
string find_stuff(object player, string str);

void
reset_room()
{


    CREAM_FOUND = 0;
    // don't reset made bed/chest if players are present in room
    if (!sizeof(FILTER_PRESENT_LIVE(all_inventory(TO))))
    {
	if (objectp(chest))
	    chest->remove_object();
	BED_MADE = 0;
    }
}

void
create_earthsea_room()
{
    set_short("Small cottage");
    set_long(BS("This is a very small but cosy cottage. "+
	"In the center of the room you see a wooden table, which is "+
	"set as if the inhabitant had just finished breakfast and "+
	"left in a hurry before washing up. There is a "+
	"feather bed against the south wall with a patchwork quilt. "+
	"Flower-print curtains cover the window on the east wall "+
	"but allow light to enter. In the corner behind the door "+
	"there is a rack with an old tattered cloak. An oak walking staff "+
	"stands alone in the corner.\n", 70));

    add_item((({"wooden table", "table", "crockery", "dishes"})),
      "The wooden table occupies the center of the room "+
      "and contains some crockery with the remains of breakfast.\n");
    add_item((({"cloak", "rack", "old tattered cloak",
	  "tattered cloak" })),
      "The rack is made of wood and has several hooks for "+
      "hanging cloaks. There is one old cloak on it now, "+
      "which looks like it has seen a lot of use.\n");
    add_item((({"feather bed", "bed", "quilt", "patchwork quilt"})),
      "There is a feather bed with a patchwork quilt lying "+
      "on it. "+ "@@bed_made");

    add_item((({"curtains", "window", "flower-print curtains" })),
      "Some colourful curtains cover the window and permit "+
      "some privacy, however, they are thin enough to let in "+
      "lots of light.\n");
    add_item((({"staff", "oak staff", "oak walking staff",
	  "walking staff"})),
      "Standing in the corner you see a walking staff made "+
      "from oak, which looks like it is awaiting its master's "+
      "return.\n");

    reset_room();
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "find_stuff");
    add_prop(OBJ_I_SEARCH_TIME, 3);

    door = clone_object(DOOR);
    door->move(TO);

}


string
find_stuff(object player, string str)
{
    object cream;
    object tp = this_player();

    if (str == "table" || str == "wooden table" ||
      str == "dishes" || str == "crockery")
    {
	if (!CREAM_FOUND)
	{
	    seteuid(getuid(TO));
	    cream = clone_object(CREAM);
	    cream->move(tp);
	    CREAM_FOUND = 1;
	    tell_room(TO, QCTNAME(tp) + " finds something on the "+
	      "table.\n", ({tp}));
	    return "You find a " + cream->query_short() + ".\n";
	}
    }

    return "You find nothing of interest there.\n";
}

string
bed_made()
{
    if (!BED_MADE)
	return "It looks as though someone needs to make the bed.\n";
    //else
    return "The bed is neatly made.\n";
}
void
init()
{
    ::init();
    add_action(&make_bed(), "make");

}

int
make_bed(string str)
{
    object tp = this_player();

    if (str == "bed" || str == "featherbed")
    {
	tp->catch_msg("You straighten the quilt on the bed and fold "+
	  "the corners under neatly.\n");
	tell_room(TO, QCTNAME(tp) + " straightens the quilt on the "+
	  "bed, folding the corners under neatly.\n", ({tp}));
	BED_MADE = 1;
	if (!objectp(chest))
	    chest = clone_object(CHEST);
	chest->move(TO);
	tp->catch_msg("With the covers nicely straightened, "+
	  "you notice there is a cedar chest at the foot of "+
	  "the bed.\n");

	return 1;
    }
    notify_fail("Make what?\n");
    return 0;
}

