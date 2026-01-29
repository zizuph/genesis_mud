#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit PLAINS_OUT;
#define R1 "11n"
#define R2 "12o"
#define R4 "12m"

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + R1,"north",0);
    add_exit(ROOM + R2,"east",0);
    add_exit(ROOM + R4,"west",0);

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
