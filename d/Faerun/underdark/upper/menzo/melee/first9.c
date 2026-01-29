/*
 *  faerun/underdark/upper/menzo/melee/first9.c
 *
 *   
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 4-4-2004
 */

#include "defs.h"
inherit P_MENZO_MELEE + "std/base_room";
#define STUDENT7 P_MENZO_MELEE + "npc/student7"

private object student7;
public void
reset_room()
{
   
    
    if(!objectp(student7))
    {
        student7 = clone_object(STUDENT7);
        student7->move(this_object(), 1);
        student7->command("emote takes a step out of the shadows.");
    }
    

}
/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_melee_room()
{
	set_short("A dark wide corridor corner on the first floor.");
	set_long("You stand at a corridor corner in the " +
                 "the Melee-magthere of Menzoberranzan. " +
                 "The floors are swept clean to perfection " +
                 "and a luminous trail of soft crimson red " +
                 "light runs in the middle of the floor, like a " +
                 "trail of blood guiding the way further into " +
                 "the dark corridor. The walls of the corridor " +
                 "are lost in the shadows, but the corridor " +
                 "still feels quite roomy. \n");
		 
	add_item(({"corridor"}),
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
        
        add_exit("first7", "south");
        add_exit("first10", "east");
        reset_room();     

}