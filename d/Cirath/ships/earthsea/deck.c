  /* /d/Cirath/ships/earthsea/deck.c
  * On the back of an athasian roc.
  * Decius, February 1998
  */

#pragma save_binary
#pragma strict_types

inherit "/d/Cirath/ships/earthsea/std/deck.c";

#include <stdproperties.h>
#include "ship.h"
#include "defs.h"

void
create_deck()
{
  set_deck_sound("The wind whistles in your ear as "+
    "white clouds float by.\n");
  set_bump_sound("The roc glides to a landing.\n");
  set_short("On the back of an athasian roc");

  set_long("You are sitting in a leather saddle strapped "+
    "to the back of a huge athasian roc. Your seat is "+
    "well behind the bird's head, and out of reach of it's "+
    "dangerous snapping beak.\n");

  add_item("saddle","This is a leather saddle strapped onto "+
    "the back of the roc, allowing passengers to ride the "+
    "giant bird. There are several more saddles, permitting "+
    "more passengers as well.\n");

  add_item(({"bird","roc","athasian roc","giant bird"}),
    "The roc resembles a large eagle with dark brown "+
    "plumage. It is fifty feet long, and has a wingspan of "+
    "well over one hundred feet.\n");


  add_prop(ROOM_I_INSIDE,0);
  add_prop(ROOM_I_LIGHT,1);
  add_prop(ROOM_I_NO_TELEPORT,1);
  add_prop(ROOM_I_HIDE,-1);

}
