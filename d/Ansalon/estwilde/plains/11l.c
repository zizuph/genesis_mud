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

    add_exit(ROOM + "10m","northeast",0);
    add_exit(ROOM + "11m","east",0);
    add_exit(ROOM + "12k","southwest",0);
    add_exit(ROOM + "12l","south",0);

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
    "A great chasm opens up before you to your northwest.\n";
}
