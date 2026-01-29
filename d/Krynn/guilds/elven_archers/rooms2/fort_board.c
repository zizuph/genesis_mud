/*
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 *
 * Updated by Vitwitch, Nov 2020
 */
    
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/d/Krynn/guilds/elven_archers/rooms2/baseroom_fort";

#define GUILDROOMS "/d/Krynn/guilds/elven_archers/rooms2/"
#define VIEWDEST "/d/Krynn/qualinesti/elf_camp/ambush1"

void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_short("A message trunk in a treetop fortress");

    set_long(gBlurbPfx + 
             " There is a curious tree trunk amidst the boughs and "+
             "foliage penetrating this room of the fortress. "+
             "Leaves, large and small, are pinned to its bark in order of age. "+ 
             gBlurbSfx +
             " An opening to the east leads to the nexus of the fortress.\n");

    add_item(({"leaf", "tree trunk", "leaves", "trunk", "messages", "message trunk"}),
             "The large tree trunk in this room is strewn with leaves bearing "+
             "messages to be shared among the Elven Archers of Ansalon.\n");

    gViewFallDest = VIEWDEST;

    add_item(({"fort","fortress","treetop fortress"}),"@@fort_purpose");
    add_item(({"treetops","whispering treetops","branches"}),"@@fort_description");
    add_item(({"walls","wall"}),"@@fort_walls");
    add_item(({"stakes","stakes","strands","strand"}),"@@fort_stakes");
    add_item(({"loopholes","loophole","window","windows","ground","ground below"}),"@@fort_vantage");
    add_item(({"foliage"}),"@@fort_foliage");
 
    INSIDE

    add_exit(GUILDROOMS + "fort_nexus", "east", 0);

    // Clone the guild board
    room_add_object(GUILD_OBJ + "archer_board", 1, 0);
    
    add_cmd_item(({"down", "ground", "loophole", "window"}), "view", "@@view_down");
    set_tell_time(250);
    add_tell("Leaves flutter on the message tree in the gently shifting breeze.\n");

    reset_room();
}

