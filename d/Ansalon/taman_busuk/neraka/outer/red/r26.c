#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Red Army camp");
    set_extra_long("You are walking on a dirt road in the Red Army camp. " +
        "To the north the road leads to the market square. There is a " +
        "tent to the southeast, while the camp spreads out in the other " +
        "directions.");
    set_quarter(RED);
    add_item_dirtroad();
    add_item_camp();

    add_item(({"tent","canvas tent"}),"It is a canvas tent, big enough " +
        "for about five people. There is a flap covering the entrance.\n");
    add_item(({"flap","canvas flap","tent flap"}),"The flap covers the " +
        "entrance to the tent, to keep the heat in on cold nights.\n");

    add_exit(NOUTER+"red/r25","north",0,0,0);
    add_exit(NOUTER+"red/r28","west",0,0,0);
    add_exit(NOUTER+"red/r27","east",0,0,0);
    add_exit(NOUTER+"red/r31","south",0,0,0);
    add_exit(NOUTER+"red/r30","southwest",0,0,0);
    add_exit(NOUTER+"red/t5","southeast","@@msg@@",0,0);
}

int
msg()
{
    write("You pull aside the flap and enter the tent.\n");
    return 0;
}

