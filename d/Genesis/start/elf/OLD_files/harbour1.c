/*
 * Generic Elvish start.
 * Southern part of the harbour.
 */

#include "defs.h"

inherit ROOM;

create_room()  
{
  set_short("A harbour");
  set_long(""+
   "You are in the southern part of the harbour at the innersea  of  Habros.\n"+
   "It seems to be a rather small harbour and you see nothing special  about\n"+
   "it.  The harbour extends to the north.  To the west,  you  see  a  pier.\n"+
   "A nice beach is to your south.  You see a forest to the west.\n");
  add_item("sea",
   "Never have you seen something like this.  This sea is so blue, that you\n"+
   "can't imagine any other like this.\n");
  add_item("pier",
   "The pier is the place to look for a ship to leave this nice place.\n");
  add_item("forest",
   "The forest is much to dense to pass here.\n");
  add_exit(STANDARD_DIR + "harbour2", "north");
  add_exit(STANDARD_DIR + "pier1", "west");
  add_exit(STANDARD_DIR + "beach", "south");
  set_noshow_obvious(1);
}
