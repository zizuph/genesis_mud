/*
 *  faerun/underdark/upper/menzo/sorcere/first1.c
 *
 *   
 *  Entrance to the tower of sorcere.
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
	object door;
	
	set_short("Just inside the Sorcere Tower");
	set_long("You are standing just inside the dark spacious foyer " +
                 "of the Sorcere tower. The large doorway leads out " +
                 "to the plateau on which the tower is built. " +
                 "The ceiling of the foyer raised high above you " +
                 "and because of the darkness you cannot determine " +
                 "exactly how high. A trail of magically enhanced " +
                 "smooth stones inserted into the floor, shows the " +
                 "way with a shimmering blue light " +
                 "which leads further into the tower.\n");
                 
        // Create and configure door
	door = clone_object(P_MENZO_SORCERE + "obj/ground_gate");
	door->configure_ground_door("east", "entrance", 
		P_MENZO_TIERBRECHE + "plateau6");
	door->move(this_object());
		 
	add_item(({"entrance","doorway"}),
        "The doorway is about two stories high and made partially of a " +
        "black metal and partially of blackened wood. The emblem of the " +
        "Sorcere is burnt into the doorway.\n");
      
        add_item(({"rocks","trail","stones"}),
        "A trail of smooth stones which has been magically altered " +
        "to glow in a soft dark blue shimmering light. They mark the " +
        "the way further into the tower.\n");
        
        add_item(({"ceiling"}),
        "The ceiling is so high above you, so that it's lost in the " +
        "darkness and shadows of the foyer.\n");

        add_item(({"floor"}),
        "The floor is hard beneath you and made by solid black rock. " +
        "Although the floor is hard, the echoes of the steps are " +
        "mysteriously absorbed into silence.\n");
        
        add_exit("first2", "west");
        add_exit(P_MENZO_TIERBRECHE + "plateau6", "east");



}