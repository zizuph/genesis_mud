/* 	this is a room of the town Gelan
 
    coder(s):   standard
 
    history:    DD.MM.YY    what done                       who did
 
    purpose:	none
    exits:      none
 
    objects:    none
    npcs:       none
 
    quests:     none
    special:    none
 
    to do:      none
    bug:        none known
*/
 
 
#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
 
reset_room()
{
 
 
 
} /* reset_room */
 
create_room()
{
    /* descriptions */
 
    set_short("%");
    set_long(BS("%\n"));
 
	/* properties */
 
    add_prop(ROOM_I_INSIDE, %);					/* this room is % */
    add_prop(ROOM_I_LIGHT,  %);					/* this room is % */
    add_prop(ROOM_I_TYPE,   %);					/* this room is % */
 
    /* exits */
 
    add_exit(GELAN_ROOMS + "%","north",0);
    add_exit(GELAN_ROOMS + "%","south",0);
    add_exit(GELAN_ROOMS + "%","west",0);
    add_exit(GELAN_ROOMS + "%","east",0);
    add_exit(GELAN_ROOMS + "%","nortwest",0);
    add_exit(GELAN_ROOMS + "%","northeast",0);
    add_exit(GELAN_ROOMS + "%","southwest",0);
    add_exit(GELAN_ROOMS + "%","southeast",0);
    add_exit(GELAN_ROOMS + "%","up",0);
    add_exit(GELAN_ROOMS + "%","down",0);
    add_exit(GELAN_ROOMS + "%","%",0);
 
    /* items in the room */
 
    add_item(({"%", "%"}), BS("%\n"));
 
    call_out("reset_room", 1);
 
} /* create_room */
 
/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
