/*
 * Sea room on the way to Kalad
 */
inherit "/std/room";
#include "../ship.h"

void create_room()
{
    set_short("dark sea");

    set_long("The ship is entering a wide, open cave that descends into "
       +"a deep gloom. The caven wall above rises to a massive height, "
       +"making you feel tiny just looking upwards. Far to the south, "
       +"the islands are receding to miniscule specks.\n");

    set_noshow_obvious(1);

    add_exit(SEA + "d_sea_n5.c", "north", 0, 10);
    add_exit(SEA + "d_sea_n3.c", "south", 0, 10);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

string darksea_sound()
{
  return "The ship passes into a massive hole in the cavern wall, and "
        +"suddenly everything becomes dark.\n";
}
