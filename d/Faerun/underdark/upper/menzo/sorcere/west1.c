/*
 *  faerun/underdark/upper/menzo/sorcere/west1.c
 *
 *   
 *  Stair and corridor on the first floor in the west tower of sorcere.
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
	object door_w,door_n,door_s;
	
	set_short("A shadowy corridor in the Sorcere");
	set_long("Sedimentary rock forms a winding stair up into " +
                 "the darkness of the western tower of Sorcere. " +
                 "This room connects a few studies, from which you " +
                 "vaguely see the flickering light of candles burning. " +
                 "Magical stones inserted in the floor, they guide " +
                 "the way towards the dark stairway.\n");
         
	// Create and configure all doors
	door_w = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_w->configure_ground_door("west", "w1_20", 
		P_MENZO_SORCERE + "first20");
	door_w->move(this_object());

	door_n = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_n->configure_ground_door("north", "w1_19", 
		P_MENZO_SORCERE + "first19");
	door_n->move(this_object());

	door_s = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_s->configure_ground_door("south", "w1_21", 
		P_MENZO_SORCERE + "first21");
	door_s->move(this_object());
		 

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
        
        add_exit("first18", "east");
        add_exit("first20", "west");
        add_exit("first21", "south");
        add_exit("first19", "north");
        add_exit("west2", "up");

}