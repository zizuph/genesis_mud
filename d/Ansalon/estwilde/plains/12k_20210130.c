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

    add_exit(ROOM + "bridge1","northwest",0);
    add_exit(ROOM + "12l","east",0);
    add_exit(ROOM + "11l","northeast",0);
    add_item_chasm();

    add_item(({"bridge","wooden bridge"}),
      "To the northwest an ancient-looking wooden bridge " +
      "hangs down between the two sides of the chasm. It creaks " +
      "ominously as it sways with the wind that blows through " +
      "the chasm.\n");

    reset_estwilde_room();
}

string
short_descr()
{
    return tod_descr1() + " before a bridge over a great chasm";
}

string
long_descr()
{
    return plain_desc()+
    "To your northwest a great chasm opens up before you. " +
    "An ancient-looking wooden bridge starts here, " +
    "crossing over the chasm to the northwest.\n";
}
