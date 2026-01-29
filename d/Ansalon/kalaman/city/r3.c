#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_short("A cobbled street in Kalaman");
    set_long("@@long_descr");

    add_item_city();

    add_exit(CITY + "r2","northwest",0);
    add_exit(CITY + "r8","east",0);
    add_exit(CITY + "r7","south",0);
    add_exit(CITY + "r6","southeast",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled street in Kalaman. " +
    tod_descr1() + season_road() + "The road branches off " +
    "to the east and south, while continuing to the southeast.\n";
}
