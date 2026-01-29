/*
 *  faerun/underdark/upper/menzo/melee/first38.c
 *
 *   
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 4-4-2004
 */

#include "defs.h"
inherit P_MENZO_MELEE + "std/base_room";
#define STUDENT7 P_MENZO_MELEE + "npc/student7"
#define MASTER1 P_MENZO_MELEE + "npc/master1"

private object student7, master1;
public void
reset_room()
{
    
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
        
        add_exit("first37", "south");
        reset_room();
     

}