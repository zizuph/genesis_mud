
#pragma save_binary

inherit "/d/Rhovanion/lib/cabin";
#include "/d/Rhovanion/farlong.h"

void
create_cabin()
{
    set_short("A sparsely-furnished cabin");
    set_long(break_string("This cabin on the wooden river-boat is"
	+" sparsely furnished, with nothing of real value present."
	+"  In fact, this room is quite boring.  The only thing to do"
	+" is to head back up onto the deck.\n",75));
  
    add_exit(RHUN+"ships/deck1", "up", 0);

}