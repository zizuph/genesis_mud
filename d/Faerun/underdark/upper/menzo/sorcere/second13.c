/*
 *  faerun/underdark/upper/menzo/sorcere/second13.c
 *
 *   
 *  Corridor on the second floor in the main tower of sorcere.
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
	set_short("A shadowy corridor in the Sorcere");
	set_long("You're walking in a narrow corridor which connects " +
                 "the north mayor tower with the wide corridor of the " +
                 "main tower of Sorcere. Eerie shadows creep up along " +
                 "the walls. " +
                 "The only lightsource is the trail of glimmering " +
                 "magical stones inserted in the floor, they guide " +
                 "the way inside the shadowy corridor.\n");
		 
	add_item(({"corridor"}),
        "A dark corridor on the first floor of the main tower " +
        "of Sorcere. The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
      
        add_item(({"stones"}),
        "A trail of smooth stones which has been magically altered " +
        "to glow in a soft dark purple shimmering light. They mark the " +
        "the way along the corridor.\n");
        
        add_item(({"walls","wall","ceiling"}),
        " The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
    
        add_item(({"floor"}),
        "The floor is hard beneath you and made by solid black rock. " +
        "Although the floor is hard, the echoes of the steps are " +
        "mysteriously absorbed into silence.\n");
        
        add_exit("second6", "south");
        add_exit("second14", "north");

}