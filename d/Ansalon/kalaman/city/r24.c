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

    add_item(({"barracks","entrance"}),
      "To the east is the entrance to one of the cities barracks. Solid stone " +
      "foundations meet thick wooden walls, offering those soldiers stationed " +
      "here decent protection from the elements.\n");
    add_item(({"market place","market"}),
      "To the northwest the road opens into the local market place.\n");

    add_exit(CITY + "r4","south",0);
    add_exit(CITY + "b3","east",0);
    add_exit(CITY + "m6","northwest",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand upon a cobbled street in the center of Kalaman. " +
    tod_descr1() + season_road() + "To your east is the entrance to one of the " +
    "cities barracks, while the road turns to the northwest into the local market place.\n";
}
