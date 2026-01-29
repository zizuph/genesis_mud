/* 
 * Room in the Aghar Mines in Krynn Newbie Zone
 * a7.c
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE;

object dwarf1;
object dwarf2;

/*
 * Function name: reset_pal_gully_room
 * Description  : Resets the room
 */
void
reset_pal_gully_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "aghar");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIV + "aghar");
        dwarf2->move(TO);
    }
}

/*
 * Function name: create_pal_gully_room()
 * Description  : Constructor for the room, modify this to change room.
 */
public void 
create_pal_gully_room()
{
    set_short("Storage Room");
    set_long("Just off the living quarters to the north. "
	+"This storage room contains rotted sacks, "
	+"barrels and crates of what must be considered "
	+"food. Most of it is just garbage and scraps "
	+"cast away by the Dewar Dwarves or others into "
	+"this mine. Whoever could be happy living here "
	+"and eating this are truly those who find happiness elsewhere.\n");
	
	add_item(({"barrels", "sacks", "crates", "barrel", "sack", "crate"}),
	"Barrels, sacks and crates filled with what could barely be called "
	+"food. The stench is horrible and everything has certainly rotted.\n");
	add_item(({"food", "food stuffs", "piles", "pile", "pile of food"}),
	"Piles of rotted that looks absolutely disgusting. It's stored in "
	+"crates, barrels and sacks and up on a shelf out of reach without a "
	+"ladder. It looks horrible.\n");
    	
	add_exit(RDIR + "a6","south",0);
	reset_pal_gully_room();
    
}