/*
 *  Entrance, Melee-magthere.
 *  Created by Midnight, 8-4-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
inherit ROOM_IN_BASE;

/*
 * Function name: create_menzo_in_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_menzo_in_room()
{
	object door;
	set_short("Entrance hall of Melee-magthere");
	set_long("This is the impressive entrance hall of " +
                 "the Melee-magthere of Menzoberranzan. " +
                 "It is as plain as it is grand, the walls " +
                 "and ceiling are constructed as one and raised " +
                 "high above to meet somewhere in the shadowy height " +
                 "of the hall. Swirling columns of sculptured " +
                 "stone with traces of a silvery metal, gives " +
                 "support to the angled ceiling. " +
                 "The floors are swept clean to perfection " +
                 "and a luminous trail of soft crimson red " +
                 "light runs in the middle of the floor, like a " +
                 "trail of blood guiding the way further into " +
                 "the dark corridor.\n");
	
	// Create and configure door
	door = clone_object(SOR_OBJ_DIR + "ground_gate");
	door->configure_ground_door("west", "entrance", 
		TIER_DIR + "plateau9");
	door->move(this_object());	 
      
        
        add_exit("plateau9", "west");
        add_exit("first2","east");


}

void
init()
{
    ::init();
    if (interactive(this_player()))
        catch(call_other("/d/Faerun/underdark/drow/menzo/melee/npc/clone_handler", "??"));}
