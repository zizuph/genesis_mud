/*
 *  faerun/underdark/upper/menzo/melee/first1.c
 *
 *   
 *  Entrance, Melee-magthere.
 *  Created by Midnight, 8-4-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_MENZO_IN;

/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_menzo_in_room()
{
//	object door;

    set_faerun_area("melee");
	set_short("Entrance hall of Melee-magthere");
    set_long("This is the impressive entrance hall of the Melee-magthere " +
        "of Menzoberranzan. It is as plain as it is grand, the walls and " +
        "ceiling are constructed as one and raised high above to meet " +
        "somewhere in the shadowy height of the hall. Swirling columns of " +
        "sculptured stone with traces of a silvery metal, gives support to " +
        "the angled ceiling. The floors are swept clean to perfection and " +
        "a luminous trail of soft crimson red light runs in the middle " +
        "of the floor, like a trail of blood guiding the way further " +
        "into the dark corridor.\n");
	
	// Create and configure door
/*
	door = clone_object(P_MENZO_SORCERE + "obj/ground_gate");
	door->configure_ground_door("west", "entrance", 
		P_MENZO_TIERBRECHE + "plateau9");
	door->move(this_object());	 
*/      
        add_item(({"trail", "light","blood" }),
        "There's a trail of soft crimson red light, " +
        "in the middle of the floor, it runs like a trail " +
        "of blood in the direction of the corridor.\n"); 

        add_item(({"wall", "walls"}),
        "These are plain stone walls which runs in a soft angle " +
        "to shape the ceiling of the hall, before being lost in " +
        "shadows.\n"); 
        
        add_item(({"column", "columns"}),
        "A few swirling columns runs from floor to ceiling and they " +
        "have been sculptured directly out of the natural stone. " +
        "Traces of silvery metal in the stone, adds to the beautiful " +
        "swirling pattern.\n"); 
        
        add_item(({"ceiling"}),
        "The ceiling is lined in a soft angle, with it's highest " +
        "point enshrouded in darkness. The ceiling runs downwards " +
        "and is completely aligned with the stone walls, so they " +
        "appear as one single shape.\n"); 
    
        add_item(({"floor","floors"}), 
        "The floor has been swept clean to perfection, probably by " +
        "one of the hardworking students. The soft crimson red " +
        "light makes the shiny floor glow with a strange red hue " +
        "near the trail of light in the middle of the floor.\n"); 
        
        add_exit("plateau9", "west");
        add_exit("first2","east");


}