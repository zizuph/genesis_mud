/*
 *  faerun/underdark/upper/menzo/melee/first25.c
 *
 *   
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 4-4-2004
 */

#include "defs.h"
inherit P_MENZO_MELEE + "std/base_room";
#define STUDENT4 P_MENZO_MELEE + "npc/student4"

private object student4;
public void
reset_room()
{
   
    
    if(!objectp(student4))
    {
        student4 = clone_object(STUDENT4);
        student4->move(this_object(), 1);
        student4->command("emote takes a step out of the shadows.");
    }
    

}
/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_melee_room()
{
	set_short("A dark eastern corridor on the first floor");
	set_long("You stand in a corridor in the " +
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
        
        add_exit("first26", "west");
        add_exit("first27", "south");
        add_exit("first23", "north");
     
        reset_room();
}