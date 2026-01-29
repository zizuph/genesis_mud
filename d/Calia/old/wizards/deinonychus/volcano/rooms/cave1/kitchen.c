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
  set_short("Kitchen");
  set_long(BS("You end up in the kitchen. The dee-licious smell " +
    "of homecooked lasagne lingers in the air. Close to the " +
    "wall you discover an ancient and sooty cooking stove with " +
    "several pans on top of it. In the middle of the room is a " +
    "wooden table laid with wooden plates. A brief thought " +
    "crosses your mind: 'Watch out for the bears'. You shake " +
    "your goldilocks in disbelief and wish you could sit down " +
    "and feast.\n"));
  add_item(({"pan", "pans"}), "The pans gleam spotlessly. " +
    "Obviously, they're made of stainless steel.\n");
  add_item(({"stove", "cooking stove"}), BS("The cooking stove " +
    "is a rather early model. Judging by the soot on it, " +
    "it has been utterly deprived of any cleaning efforts.\n"));
  add_item(({"plate", "plates", "wooden plate", "wooden plates"}), 
    BS("The wooden plates are a bit smelly but nevertheless " +
    "squeaky clean. Carved in the plates are different species " +
    "of dinosaurs. (Not that you recognize them!) Obviously, " +
    "this room belongs to a dinosaur freak.\n"));
  add_exit(ROOM("ancestor_hall_2"), "southeast", 0);
  add_exit(ROOM("cloak_room"), "southwest", 0);
  add_prop(ROOM_I_LIGHT, 0);
}
