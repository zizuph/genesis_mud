// file name: ~Avenir/common/dark/l3/n5.c
// creator(s):
// revision history:
// purpose:
// note:
// bug(s):
// to-do:

#include "l3_defs.h"
inherit L3_ROOM;
#include "/d/Avenir/common/dark/dark.h"

create_room()
{

    set_short("Dark tunnel");
    set_long(
"A dark and dank tunnel leading into darkness. The rough-hewn walls\n"+
"slope down to the dusty floor. The air is musty and hints of mold.\n"+
"Darkness and fear pervade in this gloomy place. To the west is what\n"+
"appears to be a cave-like room.\n");

    add_exit("/d/Avenir/common/dark/l3/n4","south",0);
    add_exit("/d/Avenir/common/dark/l3/nc2","west",0);

    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);

    add_prop(STATUES_IN_ROOM,random(1)+2);
    set_alarm(5.0,0.0,"reset_room");
}
