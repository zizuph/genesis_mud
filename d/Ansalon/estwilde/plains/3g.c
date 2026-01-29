#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "2g"
#define R2 "3f"
#define R4 "4f"

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
    add_exit(ROOM + R2,"west",0);
    add_exit(ROOM + R4,"southwest",0);

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
