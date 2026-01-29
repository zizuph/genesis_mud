/* /d/Raumdor/common/temple/lair5.c 
*
*Lair of the Khiraa 
*
*
* Refurbishing the original khiraa lair
*
* Nerull 2020
*
*/
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

string
query_k_rune()
{
    //if(IS_LP(TP) || IS_DK(TP))
      //  return "They are praises to the Nameless one. All hail "+
        //"unto Him. Khiraa.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}


void
create_room()
{
    ::create_room();
	
	add_prop(ROOM_I_LIGHT,0);
	
    set_short("In a dark hall");
    
    set_long("\n   You find yourself in a large, dark hall. The walls "+
    "around you here are in better condition that outside. The "+
    "stone is darker, and the stench of decay is stronger. The air "+
    "is also starting to get colder.\n"+
    "   Along the walls, you notice strange runes carved in. You "+
    "also notice what look like two, tall candle holders. However, "+
    "instead of candles in them, a dark purple-black flame burns. It "+
    "casts a little light in the room. Dark shadows are everywhere.\n\n");
	
    add_item(({"holders","candle holders"}),"They are made of black "+
    "steel and are about five feet high. Dark purple-black flames burn "+
    "in them from an unknown source.\n");
	
    add_item("flames","They are dark eerie flames which cast little light "+
    "in the room.\n");
	
    add_item("walls","The walls are made of dark, almost black, stone. "+
    "They are in better shape than outside, and no moss grows on them. "+
    "Strange runes and symbols cover them, however.\n");
	
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
		
	add_exit(TEMPLE_DIR + "lair_main", "north", 0);
	add_exit(TEMPLE_DIR + "lair4", "south", 0);	
    
    add_npc(REGULAR_DKNIGHT, 3);
}

