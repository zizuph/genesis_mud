/*
 *  faerun/underdark/upper/menzo/sorcere/north1.c
 *
 *   
 *  Stair and corridor on the first floor in the north tower of sorcere.
 *  Created by Midnight, 13-2-2004
 */

#include "defs.h"

inherit P_MENZO_SORCERE + "std/base_room";

/*
 * Function name: create_sorcere_room
 * Description  : Construct a room for the Sorcere part of Menzoberranzan
 */
void create_sorcere_room()
{
	object door_e,door_n,door_w;
	
	set_short("A shadowy corridor in the Sorcere");
	set_long("Sedimentary rock forms a winding stair up into " +
                 "the darkness of the northern tower of Sorcere. " +
                 "This room connects a few studies, from which you " +
                 "vaguely see the flickering light of candles burning. " +
                 "Magical stones inserted in the floor, they guide " +
                 "the way towards the dark stairway.\n");
        
                
        // Create and configure all doors
	door_w = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_w->configure_ground_door("west", "n1_17", 
		P_MENZO_SORCERE + "first17");
	door_w->move(this_object());

	door_n = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_n->configure_ground_door("north", "n1_16", 
		P_MENZO_SORCERE + "first16");
	door_n->move(this_object());

	door_e = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_e->configure_ground_door("east", "n1_15", 
		P_MENZO_SORCERE + "first15");
	door_e->move(this_object());
        	 
	add_item(({"stair"}),
        "A dark stairway seems to lead up to the second floor " +
        "of the tower. Rough-looking sedimentary rock provides a " +
        "secure footing in the darkness.\n");
      
        add_item(({"stones"}),
        "A trail of smooth stones which has been magically altered " +
        "to glow in a soft dark blue shimmering light. They mark the " +
        "the way along the corridor.\n");
        
        add_item(({"walls","wall","ceiling"}),
        " The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
    
        add_item(({"floor"}),
        "The floor is hard beneath you and made by solid black rock. " +
        "Although the floor is hard, the echoes of the steps are " +
        "mysteriously absorbed into silence.\n");
        
        add_exit("first15", "east");
        add_exit("first17", "west");
        add_exit("first14", "south");
        add_exit("first16", "north");
        add_exit("north2", "up");

}