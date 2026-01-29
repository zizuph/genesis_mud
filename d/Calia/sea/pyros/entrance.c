
 /* Digit 15 MAY 95 */

inherit "/d/Calia/std/water_room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define OUTSIDE "/d/Calia/sea/sector_1_1_4/wr_15_8_4"

void
create_water_room()
{
    set_short("A cave entrance");
    set_long("You have entered a small opening in Mt. Pyros.  It "+
        "appears to have been carved out in a hurry by unnatural means.  "+
        "The walls are rough and jagged, and have bits of stone protruding "+
        "from many places.  There is a small opening in the north wall that "+
        "appears to lead upwards out of the water.  To the south you see "+
        "the murky waters outside the cave.\n");

    add_swim_exit(CAVE+"room1","up","@@go_up",1);
    add_swim_exit(OUTSIDE,"south",0,1);
}

int
go_up()
{
    write("You swim up into the opening and find yourself able to breathe again!\n");
    return 0;
}
