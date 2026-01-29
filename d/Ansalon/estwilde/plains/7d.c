#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "6d"
#define R2 "7e"
#define R3 "8d"
#define R4 "7c"
object ogre;

void
reset_estwilde_room()
{
    if(!objectp(ogre))
    {
	ogre = clone_object(LIVING + "ogre");
	ogre->arm_me();
	ogre->move(TO);
    }
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + R1,"north",0);
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
