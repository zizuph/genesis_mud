/*
Last update Lilith, Nov 2021: removed odd zigg exit.
                    Might be something that was never finished.
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{
  set_short("Rocky tunnel");
  set_long("You stand in a dark section of a rough rocky"
+" tunnel.  The footing here is uncertain, and heavy cobwebs make it"
+" difficult to see.\n");

  AE(L4+"n29","northeast","@@do_web",DIRT);
  AE(L4+"n31","southwest","@@do_web",DIRT);
// This doesn't seem to do anything right now, so I'm removing it.
// --Lilith Nov 2021
//  AE(CITY+"zigg/level2/cahor2","south","@@do_web",DIRT, 1);

  add_prop(ROOM_I_LIGHT,0);
  IN;

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");    

  AI(({"dirt","stone","stones","rock","rocks","rubble","debris"}),
   "It clutters the floor, making passage difficult.\n");

  AI(({"cobweb","cobwebs"}),"The cobwebs hang down in your " +
   "face, tickling your skin. The cobwebs to the south are particularly "+
   "thick and as you look closer, you notice they are obscuring an "+
   "archway to another chamber.\n");
}
// Added by Tep for creepiness factor
int
do_web()
{
    if (!random(3))
    {
	write("You break through the cobwebs.\n" +
	  "A shiver runs up your spine as they brush against " +
	  "your face. This place makes your skin crawl.\n\n");
	this_player()->add_panic(100);
    } 
  return 0;
}  



