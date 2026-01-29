/* 
 * Storage Room of the Dewar Caverns
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_DEWAR_BASE; 

object dwarf1;
object dwarf2;
object dwarf3;

/*
 * Function name: reset_pal_dewar_room
 * Description  : Resets the room
 */
void
reset_pal_dewar_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "dewar");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIV + "dewar");
        dwarf2->move(TO);
    }
	if (!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIV + "dewar");
        dwarf3->move(TO);
    }
}

/*
 * Function name: create_pal_dewar_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_dewar_room()
{
    set_short("Storage Room");
    set_long("Just off the living quarters to the north. "
    +"This storage room contains barrels, sacks, "
    +"and crates of stores and foodstuffs for the Dewar. "
    +"Piled high along the walls the food looks "
    +"good and fresh. This room is lit by oil lanterns "
    +"attached to the wall.\n");
    
    add_item(({"barrels", "sacks", "crates", "barrel", "sack", "crate"}),
	"Barrels, sacks and crates filled with food and other sundries that "
	+"keep the dewar dwarves full and energized to carry out their "
	+"bloodlust.\n");
	add_item(({"food", "food stuffs", "piles", "pile", "pile of food"}),
	"Piles of fresh food that looks absolutely delicious. It's stored in "
	+"crates, barrels and sacks and up on a shelf out of reach without a "
	+"ladder. It looks delicious.\n");
        
        
    add_exit(RDIR + "d6","north",0);
    reset_pal_dewar_room();
    
}