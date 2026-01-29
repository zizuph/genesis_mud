#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "10h"
#define R2 "10i"
#define R4 "11g"

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
    add_exit(ROOM + R2,"northeast",0);
    add_exit(ROOM + R4,"west",0);
    add_item_chasm();

    reset_estwilde_room();
}

string
short_descr()
{
    return tod_descr1() + " before a great chasm";
}

string
long_descr()
{
    return plain_desc()+
    "A great chasm opens up to your southeast.\n";
}
