/*  part of the cave on Indy
 
    coder(s):	Deinonychus
 
    history:	DD.MM.YY	what done			who did
		28.02.93	created				Deinonychus
 
    purpose:	none
    exits:	none
 
    objects:	none
    npcs:	none
 
    quests:	none
    special:	none
 
    to do:	none
    bug:	none known
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
  object skeleton;
  object sign;
  set_short("Triceratops hall");
  set_long(BS("You are in the triceratops hall. The hall is very " +
    "clean. Filling the hall is a gigantic dinosaur skeleton. " +
    "The bones have been arranged in a way to present the " +
    "skeleton as an active, agile and probably dangerous creature. " +
    "On the wall you discover a large metal plate bearing a few " +
    "interesting facts.\n"));
  add_exit(ROOM("antechamber"), "north", 0);
  add_prop(ROOM_I_LIGHT, 0);
  skeleton = clone_object(OBJECT("skeleton"));
  skeleton->write("triceratops");	/* set long for skeleton */
  skeleton->set_no_show_composite(1);
  skeleton->move(TO);
  sign = clone_object(OBJECT("sign"));
  sign->write("triceratops");		/* set writing for sign */
  sign->set_no_show_composite(1);
  sign->move(TO);
}
