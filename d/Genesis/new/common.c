/*
 * File         : /d/Genesis/new/common.c
 * Creator      : Teth@Genesis
 * Copyright    : Daniel Mosquin
 * Date         : October 1, 1998          
 * Modifications: 
 * Purpose      : This room is to be used for discussions about start
 *                locations.      
 * Related Files: /d/Genesis/new/board.c (cloned here)
 * Comments     : This file is to be removed when the new start locations
 *                are moved to /d/Genesis/start.
 * TODO         :
 */

/* Inherit the basic room functionality and default configuration. */
inherit "/std/room";

/* Include the following files as headers to this file. Use the format
 * of <filename.h> in this case, since the location of filename is already
 * predefined. Including "/sys/filename.h" would also work, but it is
 * extremely poor form, as it will not work if ever /sys/filename.h is moved.
 * We want to include this header because of some definitions below.
 */
#include <stdproperties.h>

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    /* Give the room a short description. No need to capitalize. */
    set_short("the start location discussion room");

    /* Give the room a long description. Nothing fancy. */
    set_long("This is the discussion room for the start location " +
      "project.\n");

    /* Add a prop so that wizards can have extra information. This property
       is defined in /sys/stdproperties.h, which was included above. */
    add_prop(OBJ_S_WIZINFO,
      "This room is to be removed when the transfer of the start " +
      "locations to /d/Genesis/start/ takes place. For now, this " +
      "room contains the board for discussion on start locations.\n");

    /* Clone the start location discussion board, then move it to this room. */
    clone_object("/d/Genesis/new/board")->move(this_object(), 1);
}
