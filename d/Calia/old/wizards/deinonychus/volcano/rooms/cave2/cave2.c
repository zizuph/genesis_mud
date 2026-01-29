/*	this is a room of the volcano
 
	coder(s):	standard
 
	history:	DD.MM.YY	what done		who did
 
	purpose:	none
	exits:		none
 
	objects:	none
	npcs:		none
 
	quests:		none
	special:	none
 
	to do:		none
	bug:		none known
*/
 
 
inherit "/std/room";
#include "cave2.h"
#include <stdproperties.h>
#include <macros.h>
 
create_room()
{
    /* descriptions */
 
    set_short("In a cave");
    set_long(BS("You're in a cave.\n"));
 
	/* properties */
 
    add_prop(ROOM_I_INSIDE, 1);					/* this room is % */
    add_prop(ROOM_I_LIGHT,  1);					/* this room is % */
 
    /* exits */
 
    add_exit(CAVE2 + "cube","up",0);
 
}/* create_room */
 
/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
