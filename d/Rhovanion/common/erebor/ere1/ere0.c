inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_room()
{

    set_short("South of the Front Gate to the Lonely Mountains.\n");
    set_long(BS(
    "You are standing just south of the towering Front Gate of the " +
    "famous Lonely Mountain. The River Running emerges from underneath " +
    "the gate and flows through a canal to the west of you and continues " + 
    "south. When you look around you can see down into the valley of Dale " +
    "to the south. As you follow the River Running's twists and turns you " +
    "see a small bridge which the River Running flows under, further south " +
    "you can vaguely spot the Long Lake.\n"));

    add_item(({"river", "running"}),BS(
    "The river runs rapid in a deep canal to the west of you. Diving " +
    "into it probably would get you killed in no-time!\n"));

    add_item("canal",BS(
    "The canal is too wide to jump across and it looks to deep to " +
    "wade, besides the walls of the canal are all smooth so where " +
    "would you get the grip to descend anyway?\n"));
 
    add_item("bridge",BS(
    "You can't really make out any contures from this distance but nevertheless, " +
    "it seems as if someone is standing there, watching you.\n")); 
    
    add_exit(CAVE_DIR + "ere1", "north");
    add_exit("/d/Rhovanion/common/erebor/ere0/out1", "southeast");
    
}

