/*
 *  faerun/underdark/upper/menzo/melee/first_a3.c
 *
 *   
 *  Training arena, Melee-magthere.
 *  Created by Midnight, 8-4-2004
 */

#include "defs.h"
#define STUDENT3 P_MENZO_MELEE + "npc/student3"
#define STUDENT6 P_MENZO_MELEE + "npc/student6"
#define STUDENT7 P_MENZO_MELEE + "npc/student7"
#define MASTER1 P_MENZO_MELEE + "npc/master1"
inherit P_MENZO_MELEE + "std/base_room";

private object student3, student6, student7, master1;
public void
reset_room()
{
    if(!objectp(student3))
    {
        student3 = clone_object(STUDENT3);
        student3->move(this_object(), 1);
        student3->command("emote takes a step out of the shadows.");
    }
    
    if(!objectp(student6))
    {
        student6 = clone_object(STUDENT6);
        student6->move(this_object(), 1);
        student6->command("emote takes a step out of the shadows.");
    }
    if(!objectp(student7))
    {
        student7 = clone_object(STUDENT7);
        student7->move(this_object(), 1);
        student7->command("emote takes a step out of the shadows.");
    }
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
	set_short("Muddy training arena of Melee-magthere");
	set_long("This is a part of the huge training hall of " +
        "Melee-magthere. The ceiling is high above, " +
        "the spacious room is only cut by a bridge " +
        "which runs across the hall on the second floor. " +
        "The floor of this part of the training hall " +
        "is covered with a brownish sticky mud, to provide the " +
        "students with the training of fighting on such a surface.\n ");
        
        add_item(({"ceiling" }),
        "The ceiling is raised high above you, and it's difficult to " +
        "determine just how high, because of the darkness which " +
        "envelops the large training arena.\n"); 
        
         add_item(({"floor","mud" }),
        "The floor is covered with a brownish sticky mud, " +
        "framed by dark wooden planks.\n"); 
        
         add_item(({"bridge" }),
        "A bridge runs across the arena on the second floor, " +
        "it would surely provide a great overview of the arena.\n");
        
       
        add_exit("first_a5","north");
        add_exit("first_a1","south");
        add_exit("first_a4","east");


	set_atmosphere_interval(15);
        add_atmosphere("It feels like the mud is taking a steady grip around your feet.\n");
        reset_room();
}

