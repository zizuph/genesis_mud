inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_room()
{

    set_short("Outside the East Gate.\n");
    set_long(BS(
    "You are standing in front of the huge East Gate of the Lonely Mountains.\n" +
    "A small iron gate is barring the entrace to the east, but is seems " +
    "to be able to be opened. From inside the cave you can hear the sounds " + 
    "of talking, obviously someone is discussing something important on the " +
    "other side of the gate. You can see a track between the mountain walls " +
    "leading southeast.\n"));

    add_item(({"wall", "walls"}),BS(
    "The walls seem to high and impossible to climb.\n")); 

    add_exit(CAVE_DIR + "lm1c88", "west");
    add_exit("/d/Rhovanion/common/erebor/ere0/lm0c22", "southeast");

}

