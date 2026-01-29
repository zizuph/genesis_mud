#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "9i"
#define R2 "9j"
#define R3 "11h"
#define R4 "10h"

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
    add_exit(ROOM + "bridge1","southeast",0);
    add_exit(ROOM + R3,"southwest",0);
    add_exit(ROOM + R4,"west",0);
    add_item_chasm();
    add_item(({"ancient-looking bridge","wooden bridge","bridge"}),
      "To the southeast an ancient-looking wooden bridge " +
      "hangs down between the two sides of the chasm. It " +
      "creaks ominously as it sways with the wind that blows " +
      "through the chasm. You wonder how safe it would be to " +
      "cross?\n");

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
    "To your southeast a great chasm opens up before you. " +
    "An ancient-looking wooden bridge starts here, crossing " +
    "over the chasm to the southeast.\n";
}
