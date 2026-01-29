inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_room()
{
    object door;

    set_short("Outside the Front Gate.\n");
    set_long(BS(
    "You are standing in front of the towering Front Gate of the " +
    "famous Lonely Mountain. The River Running emerges from within " +
    "the mountain and flows through a canal under the gate and " + 
    "continues south. When you turn around you look south, down " +
    "in the valley of Dale. As you follow the Running's twists and " +
    "turns south you can vaguely spot the Long Lake.\n"));

    add_item(({"river", "running"}),BS(
    "The river runs rapid in a deep canal to the west of you. Diving " +
    "into it probably would get you killed in no-time!\n"));

    add_item("canal",BS(
    "The canal is too wide to jump across and it looks to deep to " +
    "wade, besides the walls of the canal are all smooth so where " +
    "would you get the grip to descend anyway?\n"));
 
    door = clone_object(ERE_DIR + "door_ere1");
    door->move(TO);

    add_exit(ERE_DIR + "ere1", "south");
}

