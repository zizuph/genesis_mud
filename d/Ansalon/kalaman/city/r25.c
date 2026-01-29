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
    set_short("A cobbled street in the city of Kalaman");

    add_item(({"market place","market"}),
      "To the northwest the road opens into the local market place.\n");

    add_exit(CITY + "m3","northeast",0);
    add_exit(CITY + "r26","southwest",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled street in the western part of Kalaman. " +
    tod_descr1() + season_road() + "To your northeast the road opens up into " +
    "the local market place.\n";
}
