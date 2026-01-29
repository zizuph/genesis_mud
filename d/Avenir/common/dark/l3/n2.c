// file name: ~Avenir/common/dark/l3/n2.c
// creator(s):
// revision history:
//   - changed inherited object to l3_room and added l3_defs.h to support imps
//       -=Denis /Oct 94
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
"Darkness and fear pervade in this gloomy place.\n");

    add_exit("/d/Avenir/common/dark/l3/n3","north",0);
    add_exit("/d/Avenir/common/dark/l3/n1","east",0);

    BLACK
    IN
    
    add_prop(STATUES_IN_ROOM,random(1)+2);

    set_alarm(5.0,0.0,"reset_room");
}
