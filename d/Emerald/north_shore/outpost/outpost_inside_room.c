#include "defs.h"

inherit OUTPOST_ROOM;

void
create_outpost_inside_room()
{
    set_short("Inside Outpost");
    set_em_long("Inside the outpost.\n");
    add_item( ({"wall", "walls"}),
        "The walls are made of wooden logs. They are very thick, and seem to "+
        "provide ample protection against attacks and harsh weather.\n");

    add_item( ({"floor"}),
        "The floor seems to be made of flat sheets of stone. There is dried "+
        "mud coming up from the seams, putting a blanket of dirt on everything.\n");
}

nomask void
create_outpost_room()
{
    set_short("The Outpost");
    set_em_long("Somewhere in the Outpost");
    create_outpost_inside_room();
}