/*
 *  faerun/underdark/upper/menzo/sorcere/west2.c
 *
 *   
 *  Stair and corridor on the second floor in the west tower of sorcere.
 *  Created by Midnight, 29-2-2004
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
	set_long("Sedimentary rock forms a winding stair up or down into " +
                 "the darkness of the western tower of Sorcere. " +
                 "This room connects a few studies, from which you " +
                 "vaguely see the flickering light of candles burning. " +
                 "A purple orb floats in the air above you, sending " +
                 "small streaks of energized light above your head. " +
                 "Magical stones inserted in the floor, they guide " +
                 "the way towards the dark stairway.\n");
         
	// Create and configure all doors
	door_w = clone_object(P_MENZO_SORCERE + "obj/second_door");
	door_w->configure_ground_door("west", "w2_20", 
		P_MENZO_SORCERE + "second20");
	door_w->move(this_object());

	door_n = clone_object(P_MENZO_SORCERE + "obj/second_door");
	door_n->configure_ground_door("north", "w2_19", 
		P_MENZO_SORCERE + "second19");
	door_n->move(this_object());

	door_s = clone_object(P_MENZO_SORCERE + "obj/second_door");
	door_s->configure_ground_door("south", "w2_21", 
		P_MENZO_SORCERE + "second21");
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
        "The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
        
        add_item(({"orb","purble orb"}),
        "The orb floats in the air above you. It lights up the room " +
        "in a hazy glow, since small streaks of energized purple light " +
        "shoots out from the vibrant floating orb.\n");
    
        add_item(({"floor"}),
        "The floor is hard beneath you and made by solid black rock. " +
        "Although the floor is hard, the echoes of the steps are " +
        "mysteriously absorbed into silence.\n");
        
        add_exit("second18", "east");
        add_exit("second20", "west");
        add_exit("second21", "south");
        add_exit("second19", "north");
        add_exit("west3", "up");
        add_exit("west1", "down");
       

}