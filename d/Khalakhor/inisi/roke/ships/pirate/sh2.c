#pragma save_binary

inherit "/std/room";
#include "/d/Roke/common/defs.h"

object capt;

create_room()
{
  set_short("inside the captains cabin");
  set_long("You have entered the captain's cabin. Various items\n"+
	   "are stored here, binoculars, charts, empty bottles, and\n"+
	   "full ones. In one of the corners is a huge cage with a\n"+
	   "very sturdy chain around it.\n");

  add_exit(SHIPS+"pirate/sh1","west");

  add_item("cage","The captain usually use the cage to keep prisoners from escaping.\n"+
	   "It is currently empty, but you have a strange feeling that\n"+
	   "it won't be long until some unfortunate being is captured\n"+
	   "and locked up in it.\n");

  add_item("charts","The charts are well-used, and seems to cover most parts of the world.\n");
  add_item("binoculars","They look like they are at least fifty years old.\n");
  add_item("bottles","Some of the bottles are filled with rum, but they look so disgusting\n"+
	   "that you immediately decide against drinking anything in them.\n");

  reset_room();
}
reset_room()
{
  seteuid(getuid(TO));

  if(capt)
    return;

  capt = clone_object(SHIPS+"pirate/monster/captain");
  capt->move(TO);
}
  