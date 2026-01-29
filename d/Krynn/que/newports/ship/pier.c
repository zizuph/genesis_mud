#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>

inherit BASE_FILE;
inherit "/d/Genesis/gsl_ships/lib/pier";

void add_stuff();

object ship;

void
create_newport_room()
{
    set_short("On a pier in Newports");
    set_long("This is a pier that stretches out into the Newsea. " +
        "Occasionally, a ship will land here to transport people " +
        "to a far-off land known as Sparkle. This pier ends to " +
        "the northwest, where it enters the village of Newports.\n");

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type " +
         "'Call here restart_ship <reason>'.\n");

    add_exit(NEWPORTS, "northwest");

    add_item("pier", "The pier is built on huge boulders. How they got here " +
         "is a mystery.\n");
    add_item(({"sea","newsea","Newsea","water"}),
        "This is the shore of Newsea, stretching out far to the east. " +
        "You can see no land beyond the waters.\n");
    add_item("boulders","They're hard rock.\n");

    /* Warfare: This is a pier, we do not want guards here! */
    set_num_npc(0);


    add_stuff();
    set_alarm(1.0,0.0,"post_sign");
    add_pier_entry(MASTER_OB(TO), "Newports", "Pier to Sparkle");
    initialize_pier();
}

void
add_stuff()
{
  /*
    seteuid(getuid(this_object()));
    if (!ship)
    {
        ship = clone_object(OBJ + "ship");
        ship->start_ship();
    }
  */
}

void
reset_room()
{
    add_stuff();
}

void
post_sign()
{
  /*
    object sign;

    seteuid(getuid(this_object()));

    
    sign = clone_object(OBJ + "sign");
    sign->move(SIGN_ROOM);
  */
}

void
restart_ship(string reason)
{
  /*
    if (!reason)
      {
      write("Can't restart the ship without a reason.\n");
      return 0;
      }
    (ship->query_captain())->remove_object();
    ship->remove_object();
    add_stuff();
    write_file("/d/Krynn/common/log/shiprestart", extract(ctime(time()), 4, 15)
              + " Sparkle-Newports " + capitalize(this_player()->query_real_name()) + " " + reason + "\n");
    write("Ship restarted.\n");
  */
}

