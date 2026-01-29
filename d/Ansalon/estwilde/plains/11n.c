#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit PLAINS_OUT;
#define R1 "10m"
#define R2 "12o"
#define R3 "12n"
#define R4 "11m"

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + R1,"northwest",0);
    add_exit(ROOM + R2,"southeast",0);
    add_exit(IRON + "r1","east",0);
    add_exit(ROOM + R3,"south",0);
    add_exit(ROOM + R4,"west",0);

    add_item(({"passage","wind-blown passage"}),
      "To the east is a natural passageway that passes " +
      "through the center of two hills.\n");
    add_item(({"steep hill","hill"}),
      "In actual fact you notice that it is not a single hill, " +
      "but two hills with a very thin passage seperating " +
      "them. The steep walls of these hills look impossible to climb.\n");

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
    "The wall of a steep hill rises to your east, broken " +
    "only by a small, wind-blown passage.\n";
}
