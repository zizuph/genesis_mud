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
    set_short("End of street before the western city barracks");

    add_item(({"walls","wooden walls","barracks","entrance"}),
      "To your north is the entrance to one of the city barracks. Solid stone foundations " +
      "meet thick wooden walls, offering those soldiers housed here decent " +
      "protection from the elements.\n");

    add_exit(CITY + "b5","north",0);
    add_exit(CITY + "r28","east",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand at the end of a cobbled street before the wooden walls " +
    "of the western barracks of Kalaman. " +tod_descr1() + 
    "The entrance to the barracks is to your north.\n";
}
