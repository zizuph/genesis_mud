// Sackmaker's Emporium (/d/Avenir/common/bazaar/intr/sackshop.c)
// creator(s):   Lilith Oct 1996
// purpose:      Provides containers and wearable recepticles
// note:         Entrance is from str14.c
// bug(s):
// to-do:
// last update:  
// 	* Lucius Mar 2009: Havec updated to be a custom sackmaker
// 		using the craftsman routines. Ripped trade code from
// 		the room and updated sign.
//
#pragma strict_types

inherit "/std/room";

#include "../bazaar.h"
#include "/d/Avenir/include/relation.h"
#include <macros.h>
#include <money.h>

public void
create_room(void)
{
    set_short("sack-maker's tent");
    set_long("This place is busier than a typical Sybarite shop.\n"+
        "Here, Havec Sackmaker conducts a thriving business selling "+
        "sacks of all shapes, sizes, and purposes. "+
        "Brass lamps dangle from above, reflecting a cool yellow"+
        "ish light upon rows of pouches, packs, and bags hanging "+
        "from the tent-poles. The scent of leather is heavy in the "+  
        "air, as is the smell of bread from the bakery nearby. "+
        "There is a discreet sign hanging on the wall.\n");

    AI(({"sign", "list", "handwritten list"}), "@@read_list");
    add_cmd_item(({"sign", "list"}), "read", "@@read_list");
    add_item(({"tent", "walls", "structure", "canvas", "wall"}),
        "The pale blue canvas walls of the tent have vertical white "+
        "and green stripes.\n");
    add_item(({"lamp", "lamps", "brass lamps", "brass lamp"}),
        "The lamps are really just highly-polished brass containers "+
        "with strange, rapidly flickering crystals glowing inside. "+
        "They radiate light, but no heat.\n");
    add_item(({"crystal", "crystals", "source"}), 
        "Perhaps these crystals are part of what the Sybarites refer "+
        "to as the Source? They emit a cool yellow light.\n"); 
    add_item(({"row", "rows", "tent-pole", "pole", "poles"}),
        "The merchandise hangs from the tent-poles in neat rows.\n");
	
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
 
    add_exit(EXTR+"str14", "out", 0);

    add_npc(NPC + "havec");
}

public string
read_list(void)
{
    write(
	"              Havec Sackmaker's Emporium\n"+
        "              ^^^^^^^^^^^^^^^^^^^^^^^^^^\n"+
        "    Havec Sackmaker has expanded his business to serve\n"+
        "    all of Sybarus. Here, you may order custom-made sacks\n"+
        "    and wearable containers.\n\n"+  
        "       1.  Pouch (worn around the neck) ----------------\n"+
        "       2.  Belt of pouches (belted at the waist) -------\n"+
        "       3.  Scrip (worn over the shoulder) --------------\n"+
        "       4.  Knapsack (worn on the back) -----------------\n"+
        "       5.  Sack (around the torso) ---------------------\n"+
        "     ---------------------------------------------------\n");
    return "";
}
