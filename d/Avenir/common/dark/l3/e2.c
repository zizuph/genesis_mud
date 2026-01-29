// file name: ~Avenir/common/dark/l3/e2.c
// creator(s):
// revision history:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

create_room()
{
    set_short("Dark tunnel");
    set_long(
"A dark and dank tunnel leading into darkness. The rough-hewn walls\n"+
"slope down to the dusty floor. The air is musty and hints of mold.\n"+
"Darkness and fear pervade in this gloomy place. The north tunnel\n"+
"leads to a small cave.\n");


    AE(L1 + "stair4", "up", 0);
    add_exit("/d/Avenir/common/dark/l3/ec3","north",0);
    add_exit("/d/Avenir/common/dark/l3/e3","south",0);
    add_exit("/d/Avenir/common/dark/l3/e1","west",0); 

    BLACK
    IN
}
