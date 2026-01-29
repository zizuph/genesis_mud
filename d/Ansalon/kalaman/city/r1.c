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
    set_short("Cobbled street before a gatehouse in Kalaman");
    set_long("@@long_descr");

    add_item(({"open double gate","double gate","gate","gatehouse"}),
      "To your northeast stands the gatehouse that allows passage " +
      "through the cities walls to the harbour.\n");
    add_item("harbour","You can see the harbour through the " +
      "gate to the northeast.\n");

    add_item_city();

    add_exit(KROOM + "gate","northeast",0);
    add_exit(CITY + "r2","southwest",0);

    reset_kalaman_room();
}

long_descr()
{
    return "You find yourself standing on a road in the city of " +
    "Kalaman. Looking to your northeast you see an open double " +
    "gate that passes through the great walls that surround the " +
    "city and into the harbour district of Kalaman. " +
    season_road() + tod_descr1() + "The road continues to the " +
    "southwest.\n";
}
