#pragma save_binary

#include "local.h"

inherit STREET_BASE

#include <stdproperties.h>
#include <macros.h>
#include RND_MEET

object ship;
object merchant;
object cleric;

void
add_stuff()
{
    string str;

    seteuid(getuid(this_object()));
    if (!ship)
    {
	ship = clone_object(SHIP_D + "ship");
	ship->start_ship();
    }

    if (!merchant)
	merchant = clone_object("/d/Krynn/solamn/thief/guild/obj/recruiter");
    str = GET_RANDOM_ROOM("/d/Krynn/");
    find_living("aridor")->catch_msg("MERCHANT moved to " + str + ".\n");
    find_living("teth")->catch_msg("MERCHANT moved to " + str + ".\n");
    merchant->move_living("", str);

    if (!cleric)
	cleric = clone_object("/d/Krynn/common/npcs/wand_cl_morgion");
    str = GET_RANDOM_ROOM("/d/Krynn/");
    find_living("aridor")->catch_msg("MCLERIC moved to " + str + ".\n");
    find_living("teth")->catch_msg("MCLERIC moved to " + str + ".\n");
    cleric->move_living("", str);
}

void
create_palan_room()
{
    set_short("A pier in the harbour of Palanthas");
    set_long(BS("You are on a pier in the harbour of Palanthas. The merchant vessel " +
	"anchoring here every now and then " +
	"also transports people between a far away village " +
	"named Cove and Palanthas.", SL));

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type 'Call here restart_ship <reason>'.\n");

    add_exit(PIER1, "south");
    add_exit(PIER4, "northwest");
    add_exit("/d/Krynn/solamn/palan/shipX/flotsam_pier", "north", 0, 0);

    add_item("pier", "The pier is built from wood.\n");

    add_stuff();

    (PIER4)->load_me();
}

void
reset_palan_room()
{
    add_stuff();
}

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
      + " Cove-Palanthas " + capitalize(TP->query_real_name()) + " " + reason + "\n");
    write("Ship restarted.\n");
}

