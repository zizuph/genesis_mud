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
  set_short("Living-room");
  set_long(BS("You are in the living room. It is especially " +
    "cozy and oldfashioned. The walls are adorned by precious " +
    "tapestries and ancient papyri, strewn with long forgotten " +
    "runes of ancient empires turned to dust. In one corner you " +
    "find a very comfortable sofa made of soft black leather. " +
    "The ideal place to settle down with a good book.\n"));
  add_item(({"tapestry", "tapestries"}), BS("The tapestries show " +
    "the wars and feats of the ancie)nt. These tapestries " +
    "are of immense historical value and you can only guess " +
    "their material value.\n"));
  add_item(({"sofa"}), BS("The sofa is made of soft black leather " +
    "and adorned with gold buttons.\n"));
  add_exit(ROOM("ancestor_hall_1"), "southeast", 0);
  add_exit(ROOM("fireplace_room"), "south", 0);
  reset_room();
  add_prop(ROOM_I_LIGHT, 0);
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
  if(!present("indy", TO))
  {
    clone_object(MONSTER("indy"))->move(TO);
    tell_room(TO, "Indy arrives.\n");
  }
}

