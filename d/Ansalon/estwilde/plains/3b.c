#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "2b"
#define R2 "3c"
#define R3 "4b"
#define R4 "3a"
object snake;

void
reset_estwilde_room()
{
    if(!objectp(snake))
    {
	snake = clone_object(LIVING + "snake");
	snake->move(TO);
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

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->query_race() == "ogre")
    {
	ob->stop_walking();
    }

}
