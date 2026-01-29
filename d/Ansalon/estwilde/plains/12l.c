#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit PLAINS_OUT;

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "12m","east",0);
    add_exit(ROOM + "11l","north",0);
    add_exit(ROOM + "12k","west",0);

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
    "\n";
}
