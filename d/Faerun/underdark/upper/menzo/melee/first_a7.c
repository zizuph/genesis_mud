/*
 *  faerun/underdark/upper/menzo/melee/first_a7.c
 *
 *   
 *  Training arena, Melee-magthere.
 *  Created by Midnight, 8-4-2004
 */

#include "defs.h"
#define STUDENT1 P_MENZO_MELEE + "npc/student1"
#define STUDENT4 P_MENZO_MELEE + "npc/student4"
#define STUDENT5 P_MENZO_MELEE + "npc/student5"
inherit P_MENZO_MELEE + "std/base_room";

private object student1, student4, student5;
public void
reset_room()
{
    if(!objectp(student1))
    {
        student1 = clone_object(STUDENT1);
        student1->move(this_object(), 1);
        student1->command("emote takes a step out of the shadows.");
    }
    
    if(!objectp(student4))
    {
        student4 = clone_object(STUDENT4);
        student4->move(this_object(), 1);
        student4->command("emote takes a step out of the shadows.");
    }
    if(!objectp(student5))
    {
        student5 = clone_object(STUDENT5);
        student5->move(this_object(), 1);
        student5->command("emote takes a step out of the shadows.");
    }

}


/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_melee_room()
{
	set_short("Training arena with a basin of Melee-magthere");
	set_long("This is a part of the huge training hall of " +
        "Melee-magthere. The ceiling is high above, " +
        "the spacious room is only cut by a bridge " +
        "which runs across the hall on the second floor. " +
        "The floor of this part of the training hall " +
        "is a basin of knee-deep water, to provide the " +
        "students with the training of fighting on such a surface.\n ");
        
        add_item(({"ceiling" }),
        "The ceiling is raised high above you, and it's difficult to " +
        "determine just how high, because of the darkness which " +
        "envelops the large training arena.\n"); 
        
         add_item(({"floor","water","basin" }),
        "The floor in this part of the training hall " +
        "is constructed as a large basin filled with knee-deep water " +
        "framed by dark wooden planks.\n"); 
        
         add_item(({"bridge" }),
        "A bridge runs across the arena on the second floor, " +
        "it would surely provide a great overview of the arena.\n");
        
       
        add_exit("first_a1","north");
        add_exit("first_a8","south");
        add_exit("first_a9","east");


	set_atmosphere_interval(15);
        add_atmosphere("The dark waters around you slows your movement.\n");
        reset_room();
}

