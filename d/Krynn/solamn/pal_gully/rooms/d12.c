/* 
 * Prison Room of the Dewar Caverns
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
    set_short("Prison");
    set_long("This room is small, stinky, and hot compared "
    +"to the rest of the cavern system. Small cages no "
    +"larger than that for a dog, are sturdily attached to "
    +"the walls. Implements of torture are hung along "
    +"the west wall while there is a chair with straps and "
    +"restraints in the centre of the room. Blood pools "
    +"on the floor indicate that this room has been used "
    +"recently. The room is lit with oil lanterns attached "
    +"to the walls.\n");
    
    add_item(({"implements", "torture", "implements of torture", 
    "west wall", "instruments"}), "Knives, whips, needles and other instruments "
    +"are hung along the wall. They have stains from the blood that has "
    +"been left to dry upon them. The Dewar are known for "
    +"their insanity, but these tools are too much.\n");
    add_item(({"chair", "centre of room", "chairs", "restraints",
	"straps",}), "This chair has "
    +"straps on it to hold a victim in place while they are "
    +"'questioned'. Dried blood is visible in the fabric.\n");
	add_item(({"cages", "small cage", "cage", "small cages"}), "Small "
	+"cages that are no bigger than that of a standard dog, appear to have "
	+"been used to hold prisoners within them.\n");
	add_item(({"blood pools", "pools", "pools of blood","crimson fluid"}),
	"Pools of fresh "
	+"blood have settled on the floor near the chair. The crimson fluid "
	+"looks sticky in the light of the lanterns.\n");
    
    add_exit(RDIR + "d10","north",0);
    
       
    reset_room();
    
}