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
    set_short("Cobbled street in the southern district of Kalaman");

    add_item(({"residential buildings","buildings"}),
      "On both the eastern and western side of the road stand tall two-story " +
      "buildings, homes for the richer members of Kalaman's society. " +
      "To the east you notice a gap between two of these buildings making " +
      "what could only be a thin, dark alley.\n");
    add_item(({"dark alley","alley"}),
      "A dark alley is to your east.\n");

    add_exit(CITY + "r30","north",0);
    add_exit(CITY + "r32","southeast",0);
    add_invis_exit(CITY + "alley","east",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled street in the southern district of " +
    "Kalaman. " +tod_descr1() + season_road() +
    "Residential buildings rise up on either side of the road.\n";
}
