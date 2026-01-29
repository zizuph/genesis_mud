/*
 * Sea room on the way to Kalad
 */
inherit "/std/room";
#include "../ship.h"

void create_room()
{
    set_short("dark sea");

    set_long("The great cavern wall gets larges as you approach it, rising "
      +"to a massive height. It is lit by the pale, watery light from "
      +"the Source, indistinct from here. There seems to be a small "
      +"opening in the wall the ship is making for.\n");

    set_noshow_obvious(1);

    add_exit(SEA + "d_sea_n4.c", "north", 0, 10);
    add_exit(SEA + "d_sea_n2.c", "south", 0, 10);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

string darksea_sound()
{
  return "As the ships glides northwards, the great cavern wall ahead dwarfs "
        +"all before it.\n";
}
