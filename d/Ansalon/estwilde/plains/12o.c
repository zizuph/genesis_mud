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

    add_exit(ROOM + "12n","west",0);
    add_exit(ROOM + "11n","northwest",0);

    add_item(({"hill","rocky hill","wall"}),
      "The wall of a steep, rocky hill rises to your east. " +
      "It looks too steep to climb.\n");

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
    "The wall of a steep, rocky hill rises to your east.\n";
}
