#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    near_walls();
    add_exit(KALAMAN + "o3","north",0);
    add_exit(ROOM + "1c","west",0);
    add_exit(ROOM + "1e","east",0);
    add_exit(ROOM + "2d","south",0);

    reset_estwilde_room();
}

string
short_descr()
{
    return tod_descr1();
}

string
long_descr()
{
    return plain_desc()+
    "To your north rises the great stone walls of the port " +
    "city of Kalaman.\n";
}
