/*
 * Generic Elvish start.
 * First pier of the harbour.
 */

#include "defs.h"

inherit ROOM;

create_room()  
{
  set_short("A pier");
  set_long(""+
   "You are standing on a pier in the harbour.  Here one can board  a  ship.\n"+
   "It is however not safe to stay here too  long.   With  all  those  ships\n"+
   "passing by an accident can easily take place.\n"+
   "If you want to leave, you'll have to go east, because the pier ends west\n"+
   "in the sea and you can't possibly go there.\n");
  add_item("sea",
   "Never have you seen something like this.  This sea is so blue, that you\n"+
   "can't imagine any other like this.\n");
  add_item("pier",
   "The pier is the place to look for a ship to leave this nice place.\n");
  add_exit(STANDARD_DIR + "harbour1", "east");
  set_noshow_obvious(1);
}
