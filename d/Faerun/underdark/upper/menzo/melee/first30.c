/*
 *  faerun/underdark/upper/menzo/melee/first30.c
 *
 *   
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 4-4-2004
 */

#include "defs.h"
inherit P_MENZO_MELEE + "std/base_room";
#define STUDENT2 P_MENZO_MELEE + "npc/student2"

private object student2;
public void
reset_room()
{
    if(!objectp(student2))
    {
        student2 = clone_object(STUDENT2);
        student2->move(this_object(), 1);
        student2->command("emote takes a step out of the shadows.");
    }
    
   

}
/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_melee_room()
{
	set_short("In a shadowy small training room");
	set_long("This is a shadowy small training room, where students " +
                 "can practice alone, in pairs or together with " +
                 "a master. The stone walls are cut in a perfect " +
                 "circle, designed to keep a battle going " +
                 "so no one gets cornered. A rounded opening leads " +
                 "out to a dark corridor.\n");
		 
        add_item(({"wall", "walls"}),
        "The walls are cut directly out of stone, in a " +
        "perfect circle.\n"); 
    
        add_item(({"floor","floors"}), 
        "The floor has dark stains of dried blood, the cleanliness " +
        "obviously ended in the corridor just outside.\n"); 
        
        add_exit("first29", "east");
        reset_room();

}