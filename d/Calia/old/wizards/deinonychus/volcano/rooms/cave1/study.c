/*  part of the cave on Indy
 
    coder(s):   Deinonychus
 
    history:    DD.MM.YY        what done                       who did
		28.02.93        created                         Deinonychus
 
    purpose:    none
    exits:      none
 
    objects:    none
    npcs:       none
 
    quests:     none
    special:    none
 
    to do:      none
    bug:        none known
*/
 
 
inherit "/std/room";
#include "cave1.h"
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
create_room()
{
  set_short("Study");
  set_long(BS("You're in the study. Buried under heaps and heaps " +
    "of books you can make out a desk. Maybe there's even more " +
    "to discover, who knows.\n"));
  add_exit(ROOM("armour_room"), "west", 0);
  add_prop(ROOM_I_LIGHT, 0);                                          
  add_prop(ROOM_I_INSIDE, 1);    
}
