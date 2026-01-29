#pragma strict_types
// name: cabin   /d/Avenir/common/ships/sparkle/cabin.c
// creator(s):    Tepisch   Oct 1994
// purpose:       To house the crew   
// last update:   Boriska, Mar 23 1995
//
// Ported by Tapakah to the new ship system, 05/2009

#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

public void
create_room ()
{
  ::create_shiproom();
    set_short("An odd-smelling cabin inside the G.S. Melancholy");
    set_long("This cabin has the odd, musty smell of an old crypt.  " +
      "It is a long, dark room, with a guttering oil-lamp to "  +
      "light it.  There doesn't appear to be much here, though "+
      "in the corners you can see piles of white sticks or "    +
      "perhaps bones. You feel very uneasy in this place.\n");
    add_item(({"lamp", "oil-lamp"}), "The lamp sways on its "+
      "ceiling-hook.\n");
    add_item(({"corner", "sticks", "bones"}), 
      "ACK! There in the corner you see a humanoid skeleton!  "+
      "This place is getting creepier by the second!\n");

    clone_object(CHEST)->move(this_object(), 1);
}

void
reset_room()
{
    object deck;
    deck = find_object("/d/Avenir/common/ships/gsl-sparkle/ship/deck");
    if (!(deck))
        return;
    if ((present("Barney", deck)) || (present("Barney", deck)))
        return;
    deck->call_thief();
    return;
}
