/* City is closed room */

#include "../local.h"

inherit STREET_BASE

object ken;

void
reset_palan_room()
{

}

void
create_palan_room()
{
    object door;

    set_short("You are in the open room");
    set_long("You are in the only open part of Palanthas, as the "
        + "wrath and joy of the mighty wizards are raining down "
        + "upon the city.\n");

    add_exit(ROOM + "street5","southeast");
    add_exit(PIER1,"north");

    reset_room();
}



