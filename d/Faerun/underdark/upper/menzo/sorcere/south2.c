/*
 *  faerun/underdark/upper/menzo/sorcere/south2.c
 *
 *   
 *  Stair and corridor on the second floor in the south tower of sorcere.
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
	object door_w,door_e,door_s;
	
	set_short("A shadowy corridor in the Sorcere");
	set_long("Sedimentary rock forms a winding stair up or down into " +
                 "the darkness of the southern tower of Sorcere. " +
                 "This room connects a few studies, from which you " +
                 "vaguely see the flickering light of candles burning." +
                 "A purple orb floats in the air above you, sending " +
                 "small streaks of energized light above your head. " +
                 "Magical stones inserted in the floor, they guide " +
                 "the way towards the dark stairway.\n");
                 
        
        door_w = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_w->configure_ground_door("west", "s2_23", 
		P_MENZO_SORCERE + "second23");
	door_w->move(this_object());

	door_s = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_s->configure_ground_door("south", "s2_25", 
		P_MENZO_SORCERE + "second25");
	door_s->move(this_object());

	door_e = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door_e->configure_ground_door("east", "s2_24", 
		P_MENZO_SORCERE + "second24");
	door_e->move(this_object());
		 
	add_item(({"stair"}),
        "A dark stairway seems to lead up to the third floor " +
        "or down to the first floor " +
        "of the tower. Rough-looking sedimentary rock provides a " +
        "secure footing in the darkness.\n");
      
        add_item(({"stones"}),
        "A trail of smooth stones which has been magically altered " +
        "to glow in a soft dark purple shimmering light. They mark the " +
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
        
        add_exit("second24", "east");
        add_exit("second23", "west");
        add_exit("second25", "south");
        add_exit("second22", "north");
        add_exit("south1", "down");
        add_exit("south3", "up");
       

}