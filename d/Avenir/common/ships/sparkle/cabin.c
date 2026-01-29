// -*-C++-*-
// name: cabin   /d/Avenir/common/ships/sparkle/cabin.c
// creator(s):    Tepisch   Oct 1994
// last update:   Boriska, Mar 23 1995
// purpose:       To house the crew   
// note:
// bug(s):
// to-do:         

#pragma save_binary

inherit "/d/Genesis/ship/cabin";

#include "/d/Avenir/common/ships/ship.h"

void
create_cabin()
{
  SHORT("An odd-smelling cabin inside the G.S. Melancholy");
  LONG("This cabin has the odd, musty smell of an old crypt.  "  +
       "It is a long, dark room, with a guttering oil-lamp to "  +
       "light it.  There doesn't appear to be much here, though "+
       "in the corners you can see piles of white sticks or "    +
       "perhaps bones. You feel very uneasy in this place.\n");
  add_item(({"lamp", "oil-lamp"}), "The lamp sways on its "+
	   "ceiling-hook.\n");
  add_item(({"corner", "sticks", "bones"}), 
	   "ACK! There in the corner you see a humanoid skeleton!  "+
	   "This place is getting creepier by the second!\n");
  
  add_exit(SPAR_DIR + "deck", "fore");
  clone_object(SPAR_DIR + "chest")->move(this_object(), 1);
}


