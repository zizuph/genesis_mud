#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_short("On a cobbled road beside the palace walls");
    set_long("@@long_descr");

    add_item(({"palace walls","walls","wall"}),
      "Of similar grey stone to that wall surrounding the city, " +
      "this wall stands more to seperate the palace from the " +
      "main roads of Kalaman than for protection.\n");
    add_item(({"palace","spires"}),
      "Looking over the wall you see the spires of the palace of Kalaman, " +
      "the home of the Lord of the city, as well as the place where " +
      "his council sits.\n");
    add_item_city();

    add_exit(CITY + "r12","east",0);
    add_exit(CITY + "r16","west",0);
    add_exit(CITY + "r14","south",0);
    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a road that runs around the wall of the " +
    "palace of the local lord of Kalaman. " + tod_descr1() + season_road() +
    "The road continues to the west and east, and branches off to the " +
    "south.\n";
}
