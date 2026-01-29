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
    set_short("Cobbled street in the city of Kalaman");

    add_exit(CITY + "r26","northeast",0);
    add_exit(CITY + "r29","west",0);
    add_exit(CITY + "r30","south",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You find yourself heading down a street in the city of Kalaman. " + 
    tod_descr1() + season_road() + "The cobbled street continues " +
    "to your northeast and south, while also branching away to the west.\n";
}
