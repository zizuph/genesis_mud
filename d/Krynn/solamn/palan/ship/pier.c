/*
Roke ship removed and long description altered.
Arman 1/6/98
Pier utilized for Pan-Domain Circle line
*/
#pragma save_binary

#include "local.h"

inherit STREET_BASE
inherit "/d/Genesis/gsl_ships/lib/pier";

#include <stdproperties.h>
#include <macros.h>
#include RND_MEET

object ship;
object merchant;
object cleric;

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;

void
add_stuff()
{
    string str;

    seteuid(getuid(this_object()));
    /*
    Ship captain removed for time being due to Roke renovations
    Arman - 1/6/98
	if (!ship)
	{
	    ship = clone_object(SHIP_D + "ship");
	    ship->start_ship();
	}
    */

    if (!merchant)
      merchant = clone_object("/d/Krynn/solamn/thief/guild/obj/recruiter");
    str = GET_RANDOM_ROOM("/d/Krynn/");
    find_living("aridor")->catch_msg("MERCHANT moved to " + str + ".\n");
    merchant->move_living("", str);

    if (!cleric)
      cleric = clone_object("/d/Krynn/common/npcs/wand_cl_morgion");
    str = GET_RANDOM_ROOM("/d/Krynn/");
    find_living("aridor")->catch_msg("MCLERIC moved to " + str + ".\n");
    cleric->move_living("", str);
}

void
create_palan_room()
{
    set_short("A pier in the harbour of Palanthas");
    set_long("You are on a pier in the harbour of Palanthas. The merchant " +
	     "vessel anchoring here used to " +
	     "transport people between a far away village " +
	     "named Cove and Palanthas. However in the changes performed by "+
             "Genesis ShipLines Company, the pier is now used by Pan-Donut "+
             "Circle Route.\n");

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type "  +
	     "'Call here restart_ship <reason>'.\n");

    add_exit(PIER1, "south");
    add_exit(PIER4, "northwest");
    add_exit("/d/Krynn/solamn/palan/shipX/flotsam_pier", "north", 0, 0);

    add_item("pier", "The pier is built from wood.\n");

    add_stuff();

    (PIER4)->load_me();

    add_pier_entry(MASTER_OB(TO), "Palanthas", "Pan-Donut Circle");
    /* Loading the Sign seems to break the pier selfcreated sign.
     * Comes up as unused, but all other piers have the same error 
     * on this particular line.
     * 20100701, Lunatari
     */
    sign = clone_object(SIGN);
    sign->move(TO);
    initialize_pier();
}

void
reset_palan_room()
{
    add_stuff();
}


object
query_sign ()
{
  return sign;
}
/*
restart_ship(string reason)
{
    if (!reason)
    {
	write("Can't restart the ship without a reason.\n");
	return 0;
    }
    (ship->query_captain())->remove_object();
    ship->remove_object();
    add_stuff();
    write_file("/d/Krynn/common/log/shiprestart", extract(ctime(time()), 4, 15)
	       + " Cove-Palanthas " + capitalize(TP->query_real_name()) + " " +
	       reason + "\n");
    write("Ship restarted.\n");
}
*/

