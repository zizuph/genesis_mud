#include "defs.h";

inherit TELBERIN_ROYAL_MERC;

void
create_telberin_royal_merc()
{
    set_em_long("The grand palace of Telberin dominates the northern view, "+
        "its massive size making the surrounding structures seem little by "+
        "comparison. A brilliant display of colors draws your eye toward the "+
        "exquisitely kept rose garden, bordering the outside of the circle, "+
        "and over the city's southwest mercantile quarter. You may reach the "+
        "rose garden through the small bronze gate.\n");

    add_item(({"garden", "rose garden"}),
        "You can enter the rose garden by going west through the small bronze "+
        "gate.\n");

    add_exit("tel08_08", "southeast");
    add_exit("tel07_10", "north");
    add_door_exit(TELBERIN_ROSE_GARDEN_DIR + "garden_gate",
        TELBERIN_ROSE_GARDEN_DIR + "rose1", "west");
}
