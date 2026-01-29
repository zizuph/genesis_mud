// file name:   /d/Avenir/common/city/entry/ez0.c
// creator(s):  Lucius
// revisions:   Lucius Oct 2008
//              Vyasa  Oct 2016
// purpose:
// note: based on e3.c by Lilith
// bug(s):
// to-do:
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;
#include <stdproperties.h>
static void
create_entry_room(void)
{
    set_short("rainbow path, near the First Gate");
    set_long("This rainbow coloured stone path runs between the "+
        "First Gate and the interior of the Forbidden City. "+
        "Just to the north is the courtyard at the foot of the Gate, "+
        "and west of it, a dark structure. Far to the south, the "+
        "Ziggurat stands, pleasure palace of the High Lords of Sybarus. "+
        "Southeast can be seen the wall enclosing the Executioner's "+
        "enclave, and to the soutwest, the Inquisitors Enclave. "+
        "Some distance to the east can be seen the domed building known as "+
        "Melchior's Bath. Banded like a rainbow in red, "+
        "green, yellow, and purple stones, this path curves further south, "+
        "into the City proper. Large urns spilling forth plants and flowers "+
        "of every imaginable colour have been placed here and there alongside "+
        "the stone path.\n");

    add_outside();
    add_bath();
    add_zig();
    add_urns();
    add_walls();

    add_prop(ROOM_M_NO_MAGIC, "The light suddenly pulsates fiercely, absorbing "+
        "the power emanating from you.\n");


    add_exit(ENTRY +"courtyard", "north", 0);

    add_npc(MON + "city_overseer", 1, &->equip_me());
}

