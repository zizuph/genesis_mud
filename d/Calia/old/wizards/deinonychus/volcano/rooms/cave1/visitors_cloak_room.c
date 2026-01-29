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

/* prototype(s) */
reset_room();

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
create_room()
{
  object wardrobe;
  object shoe_stand;
  set_short("Visiters cloak-room");
  set_long(BS("You're in the visitors cloak-room. Attached to the " +
    "wall is a wardrobe and on the floor is a shoe-stand.\n"));
  add_exit(ROOM("crossing"), "southeast", 0);
  add_exit(ROOM("entrance"), "west", 0);
  add_exit(ROOM("cloak_room"), "northeast", 0);
  add_prop(ROOM_I_LIGHT, 0);
  add_prop(ROOM_I_INSIDE, 1);
  wardrobe = clone_object(OBJECT("wardrobe"));
  wardrobe->set_no_show_composite(1);
  wardrobe->move(TO);
  shoe_stand = clone_object(OBJECT("shoe-stand"));
  shoe_stand->set_no_show_composite(1);
  shoe_stand->move(TO);
  reset_room();
}

/*****************************************************************************/

/*
 * Function name: reset_room()
 * Description:   Resets the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
reset_room()
{
  if(!present("shoe-horn")) clone_object(OBJECT("shoe-horn"));
}

