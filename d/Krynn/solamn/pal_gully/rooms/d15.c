/* 
 * Meeting Room of the Dewar Caverns
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
    set_short("Meeting Hall");
    set_long("This broad chamber has seats set in "
    +"rows around the room. A small podium is setup "
    +"at the front of the room, right in the centre. "
    +"This room has diagrams about plans of attack "
    +"as well as schematics of an old abandoned mine. "
    +"Blood, food, and spilled drink lie on the "
    +"floor of this room. The room is lit by oil lanterns on the walls.\n");
   
    add_item(({"diagrams", "diagram", "plans", "plan", "plan of attack", 
    "attack plans"}), "Diagrams of infiltration techniques, entry points and "
    +"tactical plans are attached to the walls near the front of the room. "
    +"It appears the Dewar are planning an attack on someone.\n");
	add_item(({"podium", "small podium"}), "A small podium, about the right "
	+"size for a dwarf, has been setup at the front of the room. Schematics "
	+"and diagrams are strewn about, on the walls and on this podium.\n");
	add_item(({"seats", "rows", "seat", "row"}), "Small seats have been "
	+"setup in rows to accomodate the Dewar during their strategic "
	+"planning.\n");
    add_item(({"schematics", "schematic", "schematics of a mine", "mine"}),
    "Floor plans and a layout of an old abandoned mine are up on "
    +"the wall near the attack plans. They show where the refuse and "
    +"garbage has and should be dumped, and where they must eliminate "
    +"the Aghar Dwarves in order to reclaim their dumping site.\n");
    
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
        
    add_exit(RDIR + "d14","west",0);
    add_exit(RDIR + "d16","southeast",0);
    reset_pal_dewar_room();
    
}