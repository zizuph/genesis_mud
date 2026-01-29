/* created by Aridor 07/03/94 */

#include "local.h"

inherit STREET_BASE

#include <stdproperties.h>
#include <macros.h>
#define SIGN_MESS   "A shipline from Newports unloads goods here sometimes" + \
	            ", also taking passengers along.\n"


object ship;

void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!ship)
    {
    	ship = clone_object(SHIP_D + "ship");
    	ship->start_ship();
    }
}

void
create_palan_room()
{

    set_short("New wooden pier in the Harbour");
    set_long("You are on a small wooden pier that has been built into " +
	     "the harbour basin. There is a sign hanging at the end of " +
	     "the pier. To the southeast, the main pier can be seen, with " +
	     "a tower on it.\n");

    add_exit(PIER1,"southeast");

    add_item("sign",SIGN_MESS);
    add_cmd_item("sign","read",SIGN_MESS);
    add_item("tower","It's a small tower but you have to go closer to see more.\n");

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type 'Call here restart_ship <reason>'.\n");

    add_item("pier", "The pier is built from wood.\n");

    add_stuff();

}

void
reset_palan_room()
{
    add_stuff();
}
/*
post_sign()
{
    object sign;

    seteuid(getuid(this_object()));

    sign = clone_object(OBJ + "sign");
    sign->move(SIGN_ROOM);
}

*/


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
               + " Palanthas-Newports " + capitalize(TP->query_real_name()) + " " + reason + "\n");
  write("Ship restarted.\n");
}

