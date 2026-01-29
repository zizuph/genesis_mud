/*  this is a room of the town Gelan

    coder(s):   Merlin 
 
    History:    date        who  what      
                14. 9. 94   pb   created 

    purpose:    hospital of the town, here you can get healing, removing
                of poisons, scars, plastic surgery and more
                this is the lobby of the hospital

    exits:      north to the road, south to the corridor with the doors

    objects:    none
    npcs:       a receptionisc

    quests:     none
    special:   

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

/*
 * Function name: reset_room
 * Description:   resets the room, installs the npcs
 * Arguments:     none
 * Returns:       none
 */

reset_room()
/* resets the room */
{
    seteuid(getuid());

} /* reset_room */

/*
 * Function name: create_room
 * Description:   creates the room
 * Arguments:     none
 * Returns:       none
 */

create_room()
/* creates the room */
{
    /* descriptions */

    set_short("Lobby of the Calia Hospital");
    set_long("This is the lobby of the famous Berti Cheese Hospital, "
           + "Gelan's one and only hospital. "
           + "This room is very clean and very white, but has this "          
           + "typical hospital odor. It's very quiet, and you don't "         
           + "dare to disturb this silence. You feel somewhat uneasy, "       
           + "but well, you only come here if you or some friend has "     
           + "a problem."          
           + "Maybe the sour looking lady behind this enormous desk "          
        + "can help you with your problems.\n");

    /* properties */

    add_prop(ROOM_I_INSIDE, 1);		/* this room is inside */

    /* exits */

    // add_exit("", "west", "@@pass_guards", 3);

    /* items in the room */

    add_item(({"note", "notice"}), 
            "                    Berti Chees Hospital (BCH)\n\n"
          + "The BCH welcomes you. Don't heistate to ask anything at "
          + "the lobby.\n\n");
    add_item("desk", "This is a huge, white desk, very clean.\n");

    reset_room();
} /* create_room */


