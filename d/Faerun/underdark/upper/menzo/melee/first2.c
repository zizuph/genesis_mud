/*
 *  faerun/underdark/upper/menzo/melee/first2.c
 *
 *   
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 4-4-2004
 */

#include "defs.h"
inherit P_MENZO_MELEE + "std/base_room";

/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_melee_room()
{
	set_short("A dark wide corridor crossing");
	set_long("You stand at a corridor crossing in the " +
                 "the Melee-magthere of Menzoberranzan. " +
                 "The floors are swept clean to perfection " +
                 "and a luminous trail of soft crimson red " +
                 "light runs in the middle of the floor, like a " +
                 "trail of blood guiding the way further into " +
                 "the dark corridor. The walls of the corridor " +
                 "are lost in the shadows, but the corridor " +
                 "still feels quite roomy. \n");
		 
	add_item(({"corridor","crossing","corridor crossing"}),
        "This dark wide corridor on the first floor." +
        "The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
      
        add_item(({"trail", "light","blood" }),
        "There's a trail of soft crimson red light, " +
        "in the middle of the floor, it runs like a trail " +
        "of blood in the direction of the corridor.\n"); 

        add_item(({"wall", "walls"}),
        "The walls of the wide corridor are lost in the dark shadows.\n"); 
    
        add_item(({"floor","floors"}), 
        "The floor has been swept clean to perfection, probably by " +
        "one of the hardworking students. The soft crimson red " +
        "light makes the shiny floor glow with a strange red hue " +
        "near the trail of light in the middle of the floor.\n"); 
        
        add_exit("first1", "west");
        add_exit("first3", "north");
        add_exit("first51","east");
        add_exit("first49", "south");
     
}