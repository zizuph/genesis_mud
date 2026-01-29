inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere0/"

create_room()
{

    set_short("Southeast of the Front Gate to the Lonely Mountains.\n");
    set_long(
    "You are standing on a road just southeast of the Front Gate to Lonely Mountain. " +
    "The River Running flows through a canal to the west of you and continues south " +
    "down into the valler of Dale. As you follow the River Running's twists and " + 
    "turns you see a small bridge which it runs under just to the south. Even " +
    "further to the south, you can see the Long Lake. " +
    " " +
    "\n");

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
    
    add_exit(CAVE_DIR+ "lm0c0","northwest");
    add_exit(CAVE_DIR+ "lm0c4","south");
    add_exit(CAVE_DIR+ "lm0c2","southeast");
}

