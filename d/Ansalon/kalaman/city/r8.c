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
    set_short("End of street before the eastern city barracks");

    add_item(({"cobbled street","street","streets","cobbled streets"}),
      "You are at the end of a cobbled street near one of the city barracks.\n");
    add_item(({"walls","wooden walls","barracks","entrance"}),
      "To your east is the entrance to one of the city barracks. Solid stone foundations " +
      "meet thick wooden walls, offering those soldiers housed here decent protection " +
      "from the elements.\n");
    add_item(({"foundations","stone foundations"}),
      "You see at the base of the stone foundation some tiny writing, reading 'Arman made this!'\n");

    add_exit(CITY + "b1","east",0);
    add_exit(CITY + "r3","west",0);


    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand at the end of a cobbled street before the wooden walls " +
    "of the eastern barracks of Kalaman. " +tod_descr1()+ season_road() +
    "The entrance to the barracks is to " +
    "your east.\n";
}
