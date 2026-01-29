#include "defs.h";

inherit TELBERIN_ROYAL_MERC;

void
create_telberin_royal_merc()
{

    set_em_long("You are on the Royal Circle of Telberin. The sweet smell of "+
        "fresh fruits, are coming from the exquisitely kept fruit garden, "+
        "bordering the outside of the circle, and over the city's southwest "+
        "mercantile quarter. You may reach the fruit garden through the small "+
        "black iron gate.\n");

    add_item(({"garden", "fruit garden"}),
        "You can enter the fruit garden by going west through the small black "+
        "iron gate.\n");

    add_item(({"fruit", "fruits",}),
        "You can see the tops of tall trees bursting above the tall hedges "+
        "that surround the lovely fruit garden. You can also see many "+
        "different size, shapes and colors of fruit hanging from their "+
        "limbs.\n");

    add_exit("tel10_07", "east");
    add_exit("tel08_08", "northwest");
    add_door_exit(TELBERIN_FRUIT_GARDEN_DIR + "garden_gate",
        TELBERIN_FRUIT_GARDEN_DIR + "fruit01", "west");
}
