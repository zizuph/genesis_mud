inherit "/d/Gondor/anorien/druedain/amon-din/fallroom1.c";

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("you spin and tumble further down the slope of Amon Din");
    set_long("You spin and tumble further down the slope of Amon"
      + " Din.\n");
}

int
down_slope(object ob)
{
    ob->catch_msg("Down, down you tumble, onward towards the base of the"
      + " hilltop.\n");
    ob->move_living("down the slope", AMON_DIR + "fallroom3");

    return 1;
}
