/*
ROOM: City Council Administration office
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
  
  set_short("The Council Administration office");
  set_long(
    "This is the Council Administration office. There stands a giant "+
    "ivory desk in the center of the room, where the Head Administrator "+
    "sits and administrates important Council Business, most of which "+
    "is probably illegal. On the smoke-stained walls hang several "+
    "important looking proclamations. \n"
  );

  add_prop(ROOM_NO_TIME_DESC, 1);

   add_exit(CENTRAL(plaza/cc_hall1), "east", 0, 0, 0);

  add_item("desk",
    "The ivory desk is worth a lot of money. Maybe you could steal it "+
    "and sell it at the local desk shop.\n"
  );
  add_item(({"proclamation","proclamations"}),
      "They all announce increased taxes, wanted ruffians, "+
      "recently hired and fired personnel.\n");
}

void
init()
{
  ::init();
  add_action("do_steal", "steal");
}

int
do_steal(string str)
{
  if (str != "desk")
  {
    notify_fail("You can't steal that!\n");
    return 0;
  }
  say(QCTNAME(TP) + " tries to steal the desk!\n");
  write(
    "It's much too big to fit through the door. Only a sorceror could "+
    "get that desk out of here!\n"
  );
  return 1;
}
