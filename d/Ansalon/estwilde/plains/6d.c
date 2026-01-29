#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "5e"
#define R2 "6e"
#define R3 "7d"
#define R4 "6c"
#define R5 "5c"

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + R1,"northeast",0);
    add_exit(ROOM + R5,"northwest",0);
    add_exit(ROOM + R2,"east",0);
    add_exit(ROOM + R3,"south",0);
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
