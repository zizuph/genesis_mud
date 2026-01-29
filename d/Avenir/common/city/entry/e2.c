// file name:        /d/Avenir/common/city/entry/e2.c
// creator(s):       Lilith, June 2003
// revisions:	Lucius Oct 2008
//              Lilith Oct 2021: added dej5 the unarmed fighter after AoB team 
//                      ok'd the crozier and the bruising boots.           
// purpose:
// note:
// bug(s):
// to-do:   
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("just outside the entrance to the dungeon");
    set_long("This place is oddly deserted, considering that "+
        "the cobbles here have been worn smooth by the passage "+
        "of many feet over the ages. "+
        "The wall of the Inquisitor's enclave abuts the "+
        "outcropping of stone into which a dark stone structure "+
        "rises directly west.  The building looks like a dungeon "+
        "of sorts, what with its thick walls and high, barred "+
        "windows. Just east you can see a small practice arena, "+
        "and beyond it, the First Gate dominates the skyline.\n");
        
    add_item(({"large building", "west building", "building",
        "stone building", "dark building", "dungeon"}),
        "A stark and imposing building, made of the dark island stone excavated "+
        "during the building of the City walls. Its only embellishment is "+
        "the bars that have been installed over its few windows. The "+
        "door is made of banded wood. There is no handle on the outside.\n");
    add_item(({"door", "wood door", "dungeon door"}),
        "This door is made of kesoit wood. It is so dark it is almost black, "+
        "with a blood-red grain. There doesn't appear to be a handle on this "+
        "side, so the only way into the dungeon is if someone inside opens "+
        "this door.\n");
    add_cmd_item(({"door", "wood door", "dungeon door"}), 
        ({"knock", "knock on", "bang", "bang on"}),
        "A gruff voice shouts through the door: Wrong knock! Go away or "+
        "I'll send a phrynos out to eat you!\n"); 
    add_item(({"window", "windows", "barred windows"}),
        "The windows are very high in the walls of the dungeon, so high that "+
        "they are impossible to reach from here. They allow the passage of "+
        "light, air, and sound, but not much else.\n");

    add_outside();
    add_walls();

    add_exit(ENTRY + "e1", "east", 0);    
	
	add_npc(MON + "dej-minha5", 1, &->equip_me());
}
