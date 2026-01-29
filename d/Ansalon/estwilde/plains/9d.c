#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "8d"
#define R2 "9e"
#define R4 "9c"

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
    add_item_hill();

    reset_estwilde_room();
}

string
short_descr()
{
    return tod_descr1() + " before a steep hill";
}

string
long_descr()
{
    return plain_desc()+
    "To your south rises a steep hill that blocks your " +
    "view of the plains any further in that " +
    "direction.\n";
}
