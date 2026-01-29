/*
 *  faerun/underdark/upper/menzo/melee/first_a9.c
 *
 *   
 *  Training arena, Melee-magthere.
 *  Created by Midnight, 8-4-2004
 */

#include "defs.h"
#define STUDENT2 P_MENZO_MELEE + "npc/student2"
#define STUDENT4 P_MENZO_MELEE + "npc/student4"
#define STUDENT7 P_MENZO_MELEE + "npc/student7"
#define MASTER2  P_MENZO_MELEE + "npc/master2"
inherit P_MENZO_MELEE + "std/base_room";

private object student2, student4, student7, master2;
public void
reset_room()
{
    if(!objectp(student2))
    {
        student2 = clone_object(STUDENT2);
        student2->move(this_object(), 1);
        student2->command("emote takes a step out of the shadows.");
    }
    
    if(!objectp(student4))
    {
        student4 = clone_object(STUDENT4);
        student4->move(this_object(), 1);
        student4->command("emote takes a step out of the shadows.");
    }
    if(!objectp(student7))
    {
        student7 = clone_object(STUDENT7);
        student7->move(this_object(), 1);
        student7->command("emote takes a step out of the shadows.");
    }
    if(!objectp(master2))
    {
        master2 = clone_object(MASTER2);
        master2->move(this_object(), 1);
        master2->command("emote takes a step out of the shadows.");
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
        
       
        add_exit("first_a2","north");
        add_exit("first_a10","south");
        add_exit("first_a7","west");


	set_atmosphere_interval(15);
        add_atmosphere("The dark waters around you slows your movement.\n");
        reset_room();
}

