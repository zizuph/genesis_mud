/*
 *  faerun/underdark/upper/menzo/sorcere/ne1.c
 *
 *   
 *  Stair on the first floor in the northeast tower of sorcere.
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
	set_short("A dark stairway in the Sorcere");
	set_long("Sedimentary rock forms a winding stair up into " +
                 "the darkness of the northeastern tower of Sorcere. " +
                 "Magical stones inserted in the floor, they guide " +
                 "the way up along the dark stairway.\n");
		 
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
        
        add_exit("first4", "southwest");
        add_exit("ne2", "up");
       

}