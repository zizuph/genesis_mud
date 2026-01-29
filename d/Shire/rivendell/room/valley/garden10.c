/*
 * The garden in Imladris
 * By Finwe, February 1998
 */

#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit GARDEN_BASE;

void reset_room();


void
create_garden_room()
{

    add_exit(VALLEY_DIR + "garden11",  "north");
    add_exit(VALLEY_DIR + "garden09",  "east");

    reset_room();
}

void
reset_room()
{
    fruit_counter = 0;
    veggie_counter = 0;
    set_searched(0);
}
