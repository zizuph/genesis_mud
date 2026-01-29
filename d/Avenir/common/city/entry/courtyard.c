// file name:        /d/Avenir/common/city/entry/courtyard.c
// creator(s):       Lilith, June 2003
// revisions:	Lucius Oct 2008
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

#include <stdproperties.h>

static void
create_entry_room(void)
{
    set_short("courtyard before the First Gate in the Forbidden City");
    set_long("This triangular courtyard marks the entrance into "+
        "the Forbidden City. "+
        "The First Gate towers above, its monolithic slabs "+
        "gleaming in the light of the Source. "+
        "The boundaries of the courtyard are determined by the "+
        "arcs of stone walls sweeping from east and west toward "+
        "the south, where the Ziggurat stands. "+
        "Three broad, stepped hills rise toward the cavern ceiling, "+
        "each one enclosed within the walls that form the enclaves "+
        "of the High Lords of Sybarus. "+
        "A blue slate path leads east toward Melchior's bath, a low, "+
        "domed building that has been built into a craggy outcropping. "+
        "Another path, banded like a rainbow in red, green, yellow, "+
        "and purple stones, curves south, into the City proper. "+
        "West, you can see a small arena, and behind it, an imposing "+
        "building with barred windows. "+
        "The artful placement of large urns spilling forth plants and "+
        "flowers of every imaginable colour helps to soften the formal "+
        "lines of building and stone.\n");

    add_item(({"arena", "small arena"}),
        "It appears to be a practice arena for guards who are waiting to "+
        "go on shift.\n");
    add_item(({"imposing building", "west building"}),
        "A stark and imposing building, made of the dark island stone excavated "+
        "during the building of the City walls. Its only embellishment is "+
        "the bars that have been installed over its few windows. It is "+
        "situated just beyond the arena, against a natural outcropping.\n");

    add_outside();
    add_bath();
    add_zig();
    add_urns();
    add_walls();

    add_prop(ROOM_M_NO_ATTACK, "You feel as though the weight "+
        "of a giant hand presses upon you, stifling your attempt.\n");
     add_prop(ROOM_M_NO_MAGIC, "As if the Gods of Sybarus "+
        "would permit your puny magic!\n");

    add_exit(ENTRY +"e3",  "blue",   0);    
    add_exit(ENTRY +"e1",  "west",   0);    
    add_exit(ENTRY +"ez0", "south",  0);    

    /* Place the first Gate */
    add_object(CITY + "obj/door/first_gate2");
    set_dircmd("north");  

    add_npc(MON + "anieste", 1, &->equip_me());
    add_npc(MON + "dej-minha2", 1, &->equip_me());
    add_npc(MON + "time_crier", 1, &->equip_me());
    add_npc(COM + "mon/phrynos", 1, &->equip_me());
    add_npc(BAZAAR + "NPCS/defender", 2, &->equip_me());
    add_npc(BAZAAR + "NPCS/defender_l", 1, &->equip_me());
}
