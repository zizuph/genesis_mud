/* rd_sw_03: North end of southern Stadium Way, Serpine-2/16/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
void
create_room()
{
    ::create_room();
    set_short("north end of southern Stadium Way");
    set_long("The favorite means of entry into the arena of Tyr, this "
            +"section of Stadium Way has been packed hard by the "
            +"constant trample of feet. Even now spectators and "
            +"contestants alike file north through its bleak entryway. "
            +"A section of the arena's wall juts out to the west, a "
            +"downwards running staircase carved into it. Above the "
            +"staircase is an odd image of a serrated bone axe on what "
            +"appears to be a sandy plain.\n");
 
    add_item(({"bleak entryway", "entryway"}), "It appears to be a "
            +"barren tunnel with a round depression in the floor.\n");
    add_item(({"depression", "round depression"}),
             "You can't see it clearly from this distance.\n");
    add_item(({"spectators", "spectator"}), "The spectators seem eager "
            +"to witness slaughter in the arena.\n");
    add_item(({"contestants", "contestant"}), "Mostly hardened "
            +"warriors, those planning to fight in Tyr's arena require "
            +"courage and stamina. Also a readiness to die.\n");
    add_item("image", "It may well be the symbol of the Champions of "
            +"Kalak, those Gladiators who are a part of the stable "
            +"owned by the King of Tyr.\n");
    add_item("staircase", "It heads down into darkness.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
/*
    add_exit(STADIUM+"s_stadium.c", "north", "@@tunnel_message", 1);
*/
    add_exit(STADIUM+"s_stadium.c", "north", "@@block_exit@@", 1);
    add_exit(TZ_MARKET+"rd_sw_02.c", "south", 0, 1);
    add_exit(GLAD_DIR+"room/entrance.c", "west", "@@stair_message", 1);
    add_exit(GLAD_DIR+"room/entrance.c","down","@@stair_message",1,1);
}
 
public int
stair_message()
{
    TP->catch_msg("You march down the stony staircase.\n");
    return 0;
}
 
public int
tunnel_message()
{
    TP->catch_msg("It becomes darker as you enter the tunnel.\n");
    return 0;
}
