// file name: ~Avenir/common/dark/l3/e1.c
// creator(s):
// revision history:
//   - changed inherited object to l3_room and added l3_defs.h to support imps
//       -=Denis /Nov, 94
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
"slope down to the dusty floor. The air is musty with hints of mold.\n"+  
"Darkness and fear pervade in this gloomy place.\n");

    add_exit("/d/Avenir/common/dark/l3/e2","east",0);
    add_exit("/d/Avenir/common/dark/l3/center","southwest",0);

    BLACK
    IN

    add_prop(STATUES_IN_ROOM,3);
    set_alarm(5.0,0.0,"reset_room");
}
