/* Ported by Tapakah to the new ship system */

#include "../default.h"
#include "defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit PORT_ROOM;
inherit LIBPIER;
void add_stuff();

object ship;
object sign;

public void
create_port_room()
{

    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("The pier");
    set_long("This is a small, sheltered pier halfway inside a cliffside. "+
      "The rickety wooden planks look barely strong enough to hold your "+
      "weight. A large sign has been planted here. To the north the wooden "+
      "planks of the pier gives way to the bare stone of a cave. To the east, "+
      "the rest of the pier stretches. There is a sign posted here.\n");

    add_item(({"pier"}),"An old wooden pier, the planks don't look too "+
      "stable.\n");
    add_item(({"planks"}),"They are rotten and have little maggots crawling "+
      "within them.\n");
    add_item(({"maggots"}),"Nasty little bugs!\n");
    add_exit(PORT + "shipline/cave", "north");
    add_exit(PORT + "shipline/pier1", "east");

    add_prop(ROOM_I_NO_CLEANUP,1);    
    add_stuff();
}

public void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!sign)
    {
        sign = clone_object("/d/Kalad/common/port/shipline/sign");
        sign->move(this_object());
    }
}

