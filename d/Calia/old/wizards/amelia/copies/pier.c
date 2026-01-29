inherit "/std/room";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>

void add_stuff();

object ship;

void
create_room()
{
    set_short("A pier in Crystalmir Lake");
    set_long(break_string(
	"You are on a pier in Crystalmir Lake. Sometimes a sea wizard " +
	"brings a ship here to transport people between a far away city " +
	"named Sparkle and Solace. East is a road to Solace. " +
	"\n", 70));

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type 'Call here restart_ship <reason>'.\n");    

    add_exit(C_SOLACE, "east", 0);

    add_item("pier", "The pier is built by huge boulders. How they got here " +
	"is a mystery.\n");

    add_stuff();
    call_out("post_sign", 1);
}

void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!ship)
    {
    	ship = clone_object(OBJ + "ship");
    	ship->start_ship();
    }
}

void
reset_room()
{
    add_stuff();
}

void
post_sign()
{
    object sign;

    seteuid(getuid(this_object()));

    sign = clone_object(OBJ + "sign");
    sign->move(SIGN_ROOM);
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
               + " Sparkle-Solace " + capitalize(this_player()->query_real_name()) + " " + reason + "\n");
  write("Ship restarted.\n");
}
