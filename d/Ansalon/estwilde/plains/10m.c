#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit PLAINS_OUT;
object rock;

void
reset_estwilde_room()
{
    if(!objectp(rock))
    {
	rock = clone_object(EOBJ + "rock");
	rock->move(TO);
    }
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "11n","southeast",0);
    add_exit(ROOM + "11m","south",0);
    add_exit(ROOM + "11l","southwest",0);

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
