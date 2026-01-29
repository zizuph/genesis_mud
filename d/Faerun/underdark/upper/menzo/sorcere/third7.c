/*
 *  faerun/underdark/upper/menzo/sorcere/third7.c
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
	set_short("A shadowy corridor of the main tower");
	set_long("The shadows are static along the edges of this " +
                 "wide corridor in the north wing of the main tower of " +
                 "Sorcere. The only lightsource is the trail of glimmering " +
                 "magical stones inserted in the floor, their " +
                 "soft hue of crimson radiance guide the way inside the " +
                 "shadowy corridor. " +
                 "The floor is hard beneath you and made by solid black rock. " +
                 "Although the floor is hard, the echoes of the steps are " +
                 "mysteriously absorbed into silence.\n");
		 
	add_item(({"corridor"}),
        "A dark corridor on the third floor of the main tower " +
        "of Sorcere. The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
      
        add_item(({"stones"}),
        "A trail of smooth stones which has been magically altered " +
        "to glow in a soft dark crimson shimmering light. They mark the " +
        "the way along the corridor.\n");
        
        add_item(({"walls","wall","ceiling"}),
        "The walls and ceiling of the corridor are " +
        "swallowed up by the shadows and lost in the darkness.\n");
    
          add_item(({"floor"}),
        "The floor is hard beneath you and made by solid black rock. " +
        "Although the floor is hard, the echoes of the steps are " +
        "mysteriously absorbed into silence. It seems to be constructed " +
        "of some black volcanic rock.\n");
        
        add_exit("third8", "south");
        add_exit("third6", "east");

}