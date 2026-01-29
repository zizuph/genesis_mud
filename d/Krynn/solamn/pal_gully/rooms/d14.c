/* 
 * Mess Hall of the Dewar Caverns
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_DEWAR_BASE; 

object dwarf1;
object dwarf2;
object dwarf3;
object dwarf4;
object dwarf5;

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
	if (!objectp(dwarf4))
    {
        dwarf4 = clone_object(LIV + "dewar");
        dwarf4->move(TO);
    }
	if (!objectp(dwarf5))
    {
        dwarf5 = clone_object(LIV + "dewar");
        dwarf5->move(TO);
    }
}

/*
 * Function name: create_pal_dewar_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_dewar_room()
{
    set_short("Mess Hall");
    set_long("Large, broad, and filled with "
    +"long tables, this mess hall stinks. Here "
    +"the Dewar come to eat their food and "
    +"commiserate over their poor lot in life. "
    +"Scraps of food and spilled drink lay "
    +"unclean on the floor. The stench from the "
    +"mouldy food fills the air like a putrid gas.\n");
    
    add_item(({"tables", "large tables", "broad tables", "table"}), 
    "Long tables that seat up to 30 Dewar line the room.\n");
    add_item(({"food", "scraps", "mouldy food", "flesh", "bread"}), 
	"Bits and pieces of flesh and bread lie on the ground uneaten "
	+"and unclean.\n");
    
    add_item(({"drink", "spilled drink", "patches"}), "Sticky patches from where "
    +"drinks have been spilt lay like land mines all over the "
    +"floor. The Dewar apparently do not like to clean.\n");
    
    add_item(({"floor", "floors"}), "The floors of the cavern are smooth "
    +"and covered in a fine lair of rock dust. Blood stains are "
    +"visible as are footprints from the inhabitants of this system. "
    +"These floors have bits of food and spilled drinks all over "
    +"the place.\n");
    
    add_exit(RDIR + "d13","west",0);
    add_exit(RDIR + "d15","east",0);
    reset_pal_dewar_room();
    
}