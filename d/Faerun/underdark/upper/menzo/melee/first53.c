/*
 *  faerun/underdark/upper/menzo/melee/first53.c
 *
 *   
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 7-4-2004
 */

#include "defs.h"
inherit P_MENZO_MELEE + "std/base_room";
#define MASTER1 P_MENZO_MELEE + "npc/master1"


private object master1;
public void
reset_room()
{
    if(!objectp(master1))
    {
        master1 = clone_object(MASTER1);
        master1->move(this_object(), 1);
        master1->command("emote takes a step out of the shadows.");
    }

}
/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_melee_room()
{
	set_short("In a dark cross-corridor");
	set_long("This is a dark corridor which runs straight through " +
	         "the first floor. To the west you can see that the " +
	         "corridor opens up into a very spacious hall. The contours " +
	         "of a dark stair can be seen just to the east. " +
	         "The floors in the room are swept clean to " +
                 "perfection and a luminous trail of soft crimson red " +
                 "light runs in the middle of the floor, like a trail " +
                 "of blood guiding the way further into the dark " +
                 "corridor. The walls of the corridor is lost in " +
                 "the shadows, but the corridor still feels quite " +
                 "roomy.\n"); 
		 
	add_item(({"corridor","cross-corridor"}),
        "This dark wide corridor on the first floor." +
        "The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
      
        add_item(({"trail", "light","blood" }),
        "There's a trail of soft crimson red light, " +
        "in the middle of the floor, it runs like a trail " +
        "of blood in the direction of the bridgeway.\n"); 

        add_item(({"wall", "walls"}),
        "The walls of the wide corridor are lost in the dark shadows.\n"); 
        
        add_item(({"hall"}),
        "You can see a hall to the west, it looks like it is some " +
        "sort of training arena.\n"); 
        
        add_item(({"stair"}),
        "Through the darkness, you can just barely see the outlines " +
        "of a stair east of here.\n"); 
    
        add_item(({"floor","floors"}), 
        "The floor has been swept clean to perfection, probably by " +
        "one of the hardworking students. The soft crimson red " +
        "light makes the shiny floor glow with a strange red hue " +
        "near the trail of light in the middle of the floor.\n"); 
        
        
        add_exit("first_a2", "west");
        add_exit("first28","east");
        reset_room();
}

