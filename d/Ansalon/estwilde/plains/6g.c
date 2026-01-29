#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "5g"
#define R2 "7h"
#define R3 "7g"
#define R4 "6f"
object lizard;

void
reset_estwilde_room()
{
    if(!objectp(lizard))
    {
	lizard = clone_object(LIVING + "hill_lizard");
	lizard->move(TO);
    }
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + R1,"north",0);
    add_exit(ROOM + R2,"southeast",0);
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
