#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit PLAINS_OUT;

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
    add_item(({"wooden bridge","bridge"}),
      "A bridge made from darkwood and rope, probably around the " +
      "time of the cataclym, hangs between the two sides of " +
      "the chasm.\n");
    add_item(({"great chasm","chasm"}),
      "Beneath you opens a chasm like a giant mouth, wide open " +
      "to receive a tasty morsel, namely you. Time to get off " +
      "the bridge you think!\n");

    add_exit(ROOM + "10i","northwest",0);
    add_exit(ROOM + "12k","southeast",0);

    reset_estwilde_room();
}

string
short_descr()
{
    return "Standing on an ancient wooden bridge over a great chasm";
}

string
long_descr()
{
    return "You stand on an ancient wooden bridge that hangs " +
    "grimly over a great chasm. It has probably been " +
    "hanging here for quite some time, most likely not " +
    "long after the chasm was made, around the time of the " +
    "cataclym. The bridge creaks loudly as a gusty " +
    "wind blows through the chasm, reminding you that it " +
    "is a long way down, and that you don't have wings.\n";
}
