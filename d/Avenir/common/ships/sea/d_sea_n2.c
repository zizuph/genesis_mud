/*
 * Sea room on the way to Kalad
 */
inherit "/std/room";
#include "../ship.h"

void create_room()
{
    set_short("dark sea");

    set_long("The water around is silent and flat, a murkey black "
      +"mirror. Back to the south is a large, mist-covered island. "
      +"Far ahead to the north, the massive cavern wall can be made out through "
      +"the gloom.\n");

    set_noshow_obvious(1);

    add_exit(SEA + "d_sea_n3.c", "north", 0, 10);
    add_exit(SEA + "d_sea_n1.c", "south", 0, 10);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

string darksea_sound()
{
  return "The ship keels slightly to starboard, leaving the dark island behind.\n";
}
