/*
 * Sea room on the way to Kalad
 */
inherit "/std/room";
#include "../ship.h"

void create_room()
{
    set_short("dark sea");

    set_long("Dark walls of rough stone surround the ship, brushing "
      +"very close to the sides. Back to the south, a small circle of light "
      +"is all that remains of the great Sybarus cavern behind you. To the "
      +"north there is nothing but darkness.\nThe currents seem to be "
      +"picking up.\n");

    set_noshow_obvious(1);

    add_exit(SEA + "d_sea_n6.c", "north", 0, 10);
    add_exit(SEA + "d_sea_n4.c", "south", 0, 10);

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

string darksea_sound()
{
  return "The ship starts to pick up speed as it moves along the currents in "
        +"the tunnel.\n";
}
