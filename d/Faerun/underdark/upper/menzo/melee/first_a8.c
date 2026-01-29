/*
 *  faerun/underdark/upper/menzo/melee/first_a8.c
 *
 *   
 *  Training arena, Melee-magthere.
 *  Created by Midnight, 8-4-2004
 */

#include "defs.h"
#define STUDENT3 P_MENZO_MELEE + "npc/student3"
#define STUDENT4 P_MENZO_MELEE + "npc/student4"
#define STUDENT6 P_MENZO_MELEE + "npc/student6"
inherit P_MENZO_MELEE + "std/base_room";

private object student3, student4, student6;
public void
reset_room()
{
    if(!objectp(student3))
    {
        student3 = clone_object(STUDENT3);
        student3->move(this_object(), 1);
        student3->command("emote takes a step out of the shadows.");
    }
    
    if(!objectp(student4))
    {
        student4 = clone_object(STUDENT4);
        student4->move(this_object(), 1);
        student4->command("emote takes a step out of the shadows.");
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
        
       
        add_exit("first_a7","north");
        add_exit("first_a10","east");


	set_atmosphere_interval(15);
        add_atmosphere("You struggle to keep your balance on one of the poles.\n");
        reset_room();
}

