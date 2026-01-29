/*
ROOM: City Council debate chamber
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
  ::create_room();
  hear_bell = 2;
  
  add_prop(ROOM_I_INSIDE, 1);

  set_short("The Council Debate Chamber");
  set_long(
    "This is the Council Debate Chamber. Here all the debates about "+
    "important Council business take place. However, nobody is "+
    "going to say a word with you around here. You'll have to find "+
    "another way to eavesdrop, just barging in is not the solution.\n"
  );

  add_prop(ROOM_NO_TIME_DESC, 1);
  
   add_exit(CENTRAL(plaza/cc_hall2), "southeast", 0, 0, 0);
}
