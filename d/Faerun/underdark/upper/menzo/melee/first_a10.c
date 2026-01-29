/*
 *  faerun/underdark/upper/menzo/melee/first_a10.c
 *
 *   
 *  Training arena, Melee-magthere.
 *  Created by Midnight, 8-4-2004
 */

#include "defs.h"
#define STUDENT2 P_MENZO_MELEE + "npc/student2"
#define STUDENT5 P_MENZO_MELEE + "npc/student5"
#define STUDENT6 P_MENZO_MELEE + "npc/student6"
inherit P_MENZO_MELEE + "std/base_room";

private object student2, student5, student6;
public void
reset_room()
{
    if(!objectp(student2))
    {
        student2 = clone_object(STUDENT2);
        student2->move(this_object(), 1);
        student2->command("emote takes a step out of the shadows.");
    }
    
    if(!objectp(student5))
    {
        student5 = clone_object(STUDENT5);
        student5->move(this_object(), 1);
        student5->command("emote takes a step out of the shadows.");
    }
    if(!objectp(student6))
    {
        student6 = clone_object(STUDENT6);
        student6->move(this_object(), 1);
        student6->command("emote takes a step out of the shadows.");
    }

}


/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_melee_room()
{
	set_short("Training arena with poles of Melee-magthere");
	set_long("This is a part of the huge training hall of " +
        "Melee-magthere. The ceiling is high above, " +
        "the spacious room is only cut by a bridge " +
        "which runs across the hall on the second floor. " +
        "The floor of this part of the training hall " +
        "is constructed of widely separated balancing poles, " +
        "to provide the students with the training of fighting " +
        "in such an environment.\n ");
        
        add_item(({"ceiling" }),
        "The ceiling is raised high above you, and it's difficult to " +
        "determine just how high, because of the darkness which " +
        "envelops the large training arena.\n"); 
        
         add_item(({"floor","balancing poles","poles" }),
        "The floor in this part of the training hall " +
        "is constructed as a large basin filled with knee-deep water " +
        "framed by dark wooden planks.\n"); 
        
         add_item(({"bridge" }),
        "A bridge runs across the arena on the second floor, " +
        "it would surely provide a great overview of the arena.\n");
        
       
        add_exit("first_a9","north");
        add_exit("first_a8","west");


	set_atmosphere_interval(15);
        add_atmosphere("You struggle to keep your balance on one of the poles.\n");
        reset_room();
}

