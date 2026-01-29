#pragma save_binary

inherit "/std/room";

#include "/d/Roke/common/defs.h"

object parrot,p1,p2;

create_room()
{
  set_short("pirate ship");
  set_long("You are on the deck of a small pirate ship. Above you its\n"+
	   "huge masts tower towards the sky, and from its side hangs\n"+
	   "a small rope ladder down into the water. The captain's\n"+
	   "cabin is east from here.\n");

  add_item("ladder","It is made of very old ropes, and is as dirty as everything else here.\n"+
	   "You could most likely climb down into the water on it.\n");
  add_item("masts","The huge masts are used when sailing the ship.\n");

  add_exit(SHIPS+"pirate/sh2","east");
  add_exit(SHIPS+"pirate/w1","down");
  
  reset_room();

}
reset_room()
{
  seteuid(getuid(TO));
  if(!parrot)
    {
      parrot = clone_object(SHIPS+"pirate/monster/parrot");
      parrot->move(TO);
    }
  if(!p1)
    {
      p1 = clone_object(SHIPS+"pirate/monster/pirate");
      p1->move(TO);
    }
  if(!p2)
    {
      p2 = clone_object(SHIPS+"pirate/monster/pirate");
      p2->move(TO);
    }
}
      