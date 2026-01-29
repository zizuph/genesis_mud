/*
 *  faerun/underdark/upper/menzo/sorcere/third3.c
 *
 *   
 *  Corridor on the third floor in the main tower of sorcere.
 *  Created by Midnight, 8-3-2004
 */

#include "defs.h"

inherit P_MENZO_SORCERE + "std/base_room";

/*
 * Function name: create_sorcere_room
 * Description  : Construct a room for the Sorcere part of Menzoberranzan
 */
void create_sorcere_room()
{
    object door_w;
    object door_e;

	set_short("A shadowy corridor of the main tower");
	set_long("The shadows are static along the edges of this " +
                 "wide corridor crossing of the main tower of Sorcere. " +
                 "The only lightsource is the trail of glimmering " +
                 "magical stones inserted in the floor, their " +
                 "soft hue of crimson radiance guide the way inside " +
                 "the shadowy corridor. " +
                 "A crimson orb floats in the air above you, sending " +
                 "small streaks of energized light above your head. " +
                 "The floor is hard beneath you and made by solid black rock. " +
                 "Although the floor is hard, the echoes of the steps are " +
                 "mysteriously absorbed into silence.\n");

   	// Create and configure all doors
	door_w = clone_object(P_MENZO_SORCERE + "obj/third_master_door");
	door_w->configure_ground_door("west", "s6_3", 
		P_MENZO_SORCERE + "study6");
	door_w->move(this_object());
	
	door_w = clone_object(P_MENZO_SORCERE + "obj/third_master_door");
	door_w->configure_ground_door("east", "s7_3", 
		P_MENZO_SORCERE + "study7");
	door_w->move(this_object());
         
	add_item(({"corridor"}),
        "A dark corridor on the second floor of the main tower " +
        "of Sorcere. The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
      
        add_item(({"stones"}),
        "A trail of smooth stones which has been magically altered " +
        "to glow in a soft dark crimson shimmering light. They mark the " +
        "the way along the corridor.\n");
        
        add_item(({"walls","wall","ceiling"}),
        "The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
        
        add_item(({"orb","purble orb"}),
        "The orb floats in the air above you. It lights up the room " +
        "in a hazy glow, since small streaks of energized crimson light " +
        "shoots out from the vibrant floating orb.\n");
    
        add_item(({"floor"}),
        "The floor is hard beneath you and made by solid black rock. " +
        "Although the floor is hard, the echoes of the steps are " +
        "mysteriously absorbed into silence. It seems to be constructed " +
        "of some black volcanic rock.\n");
        
        add_exit("study6", "west");
        add_exit("third4", "north");
        add_exit("study7", "east");
        add_exit("third12", "south");

}