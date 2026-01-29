/* Conan Apr -95
 * Ported to the new ship system
 * Tapakah, 10/2008
*/
 
#include "defs.h"
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

#pragma save_binary

inherit STDSHIPROOM;

void
create_room()
{
	::create_shiproom();
  set_short("Golden ship deck");
  set_long(break_string(
    "You are standing on the deck of a large, impressive, golden ship. "+
    "Everything here is made of gold, even the ropes are covered with it! "+
    "You gasp as you see all this wealth at one place. You also wonder "+
    "who could afford it. That person must be one of the wealthiest in "+
    "the world.\n",60));

  OUTSIDE;

  add_exit("gcabin","aft");
}

