/*
 * Sea room on the way to Kalad
 */
inherit "/std/room";
#include "../ship.h"

void create_room()
{
    set_short("narrow water-filled tunnel");

    set_long("The rough unhewn wall of the tunnel around almost seem to "
      +"be carved with some sort of incriptions, but you are moving too "
      +"fast along the tunnel to be able to see. The currents below "
      +"are rough, accelerating the ship faster and faster to the north.\n");

    ACI(({"carving","carvings"}),"read","Amon alk fmmd Cthulu arig asou!\n");
    set_noshow_obvious(1);

    add_exit(SEA + "d_sea_n7.c", "north", 0, 10);
    add_exit(SEA + "d_sea_n5.c", "south", 0, 10);

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

string darksea_sound()
{
  return "The ship bumps against the side tunnel wall, and begins "
        +"to move faster and faster northwards.\n";
}
