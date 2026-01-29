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
    set_long("@@long_descr");
    set_short("Cobbled street in the southern parts of Kalaman");

    add_item(({"great stone walls","stone walls","walls","wall"}),
      "Surrounding the city are high walls made of solid grey stone.\n");
    add_item_city();
    add_exit(CITY + "r14","east",0);
    add_exit(CITY + "r33","west",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled street in the southern parts of Kalaman. " +
    "To your south rise the great stone walls that protect the city. " +
    tod_descr1() + season_road() + "\n";
}
