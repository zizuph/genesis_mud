#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "4e"
#define R2 "5f"
#define R3 "6e"
#define R4 "6d"
#define R5 "4d"

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
    add_exit(ROOM + R3,"south",0);
    add_exit(ROOM + R4,"southwest",0);
    add_exit(ROOM + R5,"northwest",0);

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
