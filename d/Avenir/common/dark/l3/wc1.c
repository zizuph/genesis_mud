// file name: ~Avenir/common/dark/l3/wc1.c
// creator(s):
// revision history:
// purpose:
// note: Imps live here.
// bug(s):
// to-do:

#include "l3_defs.h"
inherit L3_ROOM;
#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{

    set_short("dark cave");
    set_long(
"This wretched little cave is littered with scraps of foul meat "+
"and gnawed bones. The smell here is terrible, making you want "+
"to leave as soon as possible.\n");

    add_item("bones",
"Bones from various poor beasts cover the floor. They are of "+
"varying ages, some are bleached white with age, and others "+
"still have bits of fresh meat stuck to them. They are all "+
"marked with what appears to be the teeth of some enormous "+
"beast.\n");

    add_item (({"meat","scrap","scraps"}),
"Scraps of foul, rancid meat lie amongst the bones, creating "+
"an unbearable stench.\n");

    add_exit("/d/Avenir/common/dark/l3/center","northeast",0);

    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);

    add_prop(STATUES_IN_ROOM,3);
    set_alarm(0.5,0.0,"reset_room");
}
