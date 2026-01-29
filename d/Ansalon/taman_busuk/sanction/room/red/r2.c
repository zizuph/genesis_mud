#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("center of an encampment of the Red Dragonarmy");
    set_long("@@long_descr");

    add_item(({"encampment","orderly encampment"}),
      "This is an encampment of the Red Dragonarmy, one of the most " +
      "formidable forces on Ansalon.\n");
    add_item(({"large hall","hall"}),
      "To your north is the large training hall of the Red Dragonarmy. " +
      "Consisting of a solid stone base and high timber walls, " +
      "this hall is well-used by the legions of soldiers in the training of " +
      "the arts of warfare.\n");
    add_item(({"walls","timber","timber walls","high timber walls"}),
      "The large hall to your north consists of high timber walls " +
      "stained a dark rusty-brown colour.\n");
    add_item(({"black stone","stone base","base"}),
      "Black stone, most likely basalt, makes up the base of the " +
      "large training hall to your north.\n");
    add_item("tent","To your northeast, a tent used by dragonarmy " +
      "soldiers stands open.\n");
    add_item("trail","A trail continues through the " +
      "encampment to your northwest.\n");

    add_exit(SRED + "tent1","northeast",0);
    add_exit("/d/Ansalon/guild/dragonarmy/room/train_red","north",0);
    add_exit(SRED + "r1","south",0);
    add_exit(SRED + "r3","northwest",0);
}


string
long_descr()
{
    return tod_short_descr() + "You stand at the center of " +
    "an orderly encampment of the red dragonarmy. To your north " +
    "rises a large hall constructed of black stone and timber " +
    "that has been dyed a dark rusty-brown colour. " +
    "A tent stands open to your northeast, while a trail through the " +
    "encampment leads off to your northwest.\n";
}
