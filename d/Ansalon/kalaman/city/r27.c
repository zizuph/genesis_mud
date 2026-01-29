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
    set_short("Cobbled street before a gatehouse in Kalaman");

    add_item(({"double gate","gate"}),
      "To your northwest stands a double gate, allowing passage out " +
      "of Kalaman and into the northeastern plains of Solamnia.\n");
    add_item(({"plains","plains of solamnia"}),
      "If you pass through the gates to your northwest you " +
      "will be able to see the northeastern part " +
      "of the plains of Solamnia.\n");
    add_item(({"great walls","walls","wall"}),
      "Surrounding the city is a high wall of grey stone.\n");

    add_exit(CITY + "gate1","northwest",0);
    add_exit(CITY + "r26","southeast",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You find yourself standing on a road in the city of Kalaman. " +
    tod_descr1() + season_road() + "Looking to the northwest you see a " +
    "double gate that passes through the great walls that surround the " +
    "city and out into the northeastern plains of Solamnia.\n";
}
