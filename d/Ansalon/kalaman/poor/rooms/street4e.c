#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

create_kalaman_room()
{
    set_short("Poor district");
    set_long("You stand in a soon to be poor district of Kalaman.\n");

    add_exit("e5","north",0);
    add_exit("e3","south",0);
}
