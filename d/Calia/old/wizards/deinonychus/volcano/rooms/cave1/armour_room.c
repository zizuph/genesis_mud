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
  set_short("Armour-room");
  set_long(BS("A quick glance around assures you: 'This is the " + 
    "armour-room. Numerous old weapons decorate the walls. " +
    "The resident of this cave appears to be an eager collector " + 
    "of old weapons. Apart from the old and useless stuff you " +
    "detect a display-case with, Deo volente, awesome weapons.\n"));
  add_item("weapons", "You spot an old war-hammer, two antique " +
    "halberds, a cudgel, a cross-bow and a huge axe. " +
    "Undoubtedly, some years ago these weapons have been " +
    "taking their bloody toll, but nowadays even a delicate touch " +
    "could turn'em to dust.\n");
  add_item(({"war-hammer", "hammer"}),
    "Examining the war-hammer gives you a sudden headache. ;-)\n");
  add_item(({"halberds", "halberd"}),
    "Examining the halberds brings a picture of brainless, eyeless " +
    "- in fact decapitated - chicken to your mind.\n");
  add_item("cudgel", 
    "The cudgel is a particularly nasty weapon: A spikey " +
    "steel-ball chained to a solid wooden stick.\n");
  add_item("cross-bow",
    "This looks exactly like the one you know from William Tell " +
    "(in case you know who this is ;-).\n");
  add_item("axe", 
    "Gimme a break dude, you know exactly what an axe looks like.\n");
  add_exit(ROOM("study"), "east", 0);
  add_exit(ROOM("cloak_room"), "southeast", 0);
  add_exit(ROOM("sleeping_room"), "south", 0);
  add_prop(ROOM_I_LIGHT, 0);
  add_prop(ROOM_I_INSIDE, 1);
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
  object cupboard;
    
  if(!(cupboard = present("cupboard", TO)))
  {  
    cupboard = clone_object(OBJECT("armour-cupboard"));
    cupboard->move(TO);
  }
  else
    cupboard->reset_container();
}  

