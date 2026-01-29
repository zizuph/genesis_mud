#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCINROOM;


void
create_sanction_room()
{
    set_short("inside a tent of the Blue Dragonarmy");
    set_long("@@long_descr");

    add_item(({"white canvas tent","canvas tent","tent"}),
      "@@long_descr");

    add_exit(SBLUE + "r1","south",0);
}


string
long_descr()
{
    return "You stand within a white canvas tent used by the " +
    "Blue Dragonarmy soldiers. The heat in here is rather " +
    "oppressive, not surprising considering the tent's location, "+
    "on the edge of the city of fire and lava, Sanction." +
    "\n";
}
