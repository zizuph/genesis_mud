/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

object woman;

string
query_to_jail()
{
  return "northwest";
}

void
reset_palan_room()
{
    if (woman)
      return;
    woman = clone_object(LIV + "woman");
    woman->move(TO);
}

void
create_palan_room()
{

    set_short("In the southeastern parts of Palanthas");
    set_long(BS("You are on a street bustling with activity. Shops line the "
         +   "sides, with there being a new building bearing the symbols of " 
         +   "an alchemist to your east, as well as a Jeweler's Shop to the northeast. "
         +   "The street continues northwest towards the central plaza and "
         +   "towards the southeast is a another street crossing.",SL));

    add_exit(ROOM + "street2","southeast",0,1);
    add_exit(ROOM + "plaza","northwest",0,1);
    add_exit(ROOM + "jeweler","northeast",0,1);
    add_exit(ROOM + "alchemist","east",0,1);

    reset_room();
}


int
jeweler_closed()
{
  write("You find a sign hanging on the door saying: \n"
      + "Due to vacations, the jeweler's shop is closed.\n");
  if (TP->query_wiz_level())
    return 0;
  else
    return 1;
}
