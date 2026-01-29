/*
 * Sea room on the way to Kalad
 */
inherit "/std/room";
#include "../ship.h"

void create_room()
{
    set_short("narrow water-filled tunnel");

    set_long("The currents in this small tunnel are picking up, "
            +"pushing the ship forward at a steep angle down. The "
            +"sides of the tunnel glisten with "
            +"the spray from the water.\n");

    set_noshow_obvious(1);

    add_exit(SEA + "d_sea_n8.c", "north", 0, 10);
    add_exit(SEA + "d_sea_n6.c", "south", 0, 10);

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

string darksea_sound()
{
  return "The ship rolls and keel sickeningly, and you feel a sudden drop "
        +"from below.\nThe ship speeds forward at a steep angle, "
        +"and spray from the currents splashes over onto the deck.\n";
}
