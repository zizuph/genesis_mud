inherit "/std/room";

#include "/d/Emerald/defs.h"

void
reset_room()
{
    set_searched(0);
}

void
create_room()
{
   object door;

   set_short("In a garden");
   set_long("   The garden looks suddenly run-down here.  A tangle of "+
            "unkempt rose bushes valiantly attempts to bloom despite the "+
            "obvious neglect.  There is a tiny cottage trimmed in blue "+
            "to your west. Even with the unkeptness of the roses, they "+
            "still smell delightful.\n\n");

   add_item(({"cottage"}),"A small, neat cottage.\n");
   add_item(({"bushes", "rose bushes"}),"As you peer into the tight mesh "+
           "of thorny thicket, you think you see traces of colour.  Could "+
           "there possibly be roses blooming somewhere within this confusion?\n");

   add_exit(VILLAGE_DIR + "g8", "north", 0);
   door=clone_object(VILLAGE_DIR + "doors/door_c.c");
   door->move(this_object());

//  add_prop(OBJ_S_SEARCH_FUN, "search_fun");
}

string
search_fun(object player, string what)
{
    object rose;
    string str;

    if (what != "bush" && what != "bushes")
	return 0;
    if (query_searched() >= 3)
	return 0;
    seteuid(getuid());
    switch (query_searched()) {
	case 0:
	    rose = clone_object(VILLAGE_DIR + "obj/yellow_rose");
	    str = "You reach through the thorns and pluck a "+
		  rose->short(this_player()) + ".\n";
	    break;
	case 1:
	    rose = clone_object(VILLAGE_DIR + "obj/red_rose");
	    str = "You again search carefully and find, this time, a " +
		  rose->short(this_player()) + ".\n";
	    break;
	case 2:
	    rose = clone_object(VILLAGE_DIR + "obj/white_rose");
	    str = "Once more you brave the brambles and extract a " +
		  rose->short(this_player()) + ".\n";
	    break;
    }
    set_searched(query_searched() + 1);
    rose->move(player);
    return str;
}
