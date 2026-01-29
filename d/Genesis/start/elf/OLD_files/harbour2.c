/*
 * Generic Elvish start.
 * Northern part of the harbour.
 */

#include "defs.h"

inherit ROOM;

create_room()  
{
  set_short("A harbour");
  set_long(""+
   "You are in the northern part of the harbour at the innersea  of  Habros.\n"+
   "It seems to be a rather small harbour and you see nothing special  about\n"+
   "it.  The harbour extends to the south.  To the west,  you  see  a  pier.\n"+
   "You see a forest to the west and although you can't go  there,  you  see\n"+
   "some mountain range far north.  But you could visit the  little  cottage\n"+
   "just north from here.\n");
  add_item("sea",
   "Never have you seen something like this.  This sea is so blue, that you\n"+
   "can't imagine any other like this.\n");
  add_item("pier",
   "The pier is the place to look for a ship to leave this nice place.\n");
  add_item("forest",
   "The forest is much to dense to pass here.\n");
  add_item("cottage",
   "It is a little cottage.  On the front wall, you see a plaque with a gold\n"+
   "horn on it.  There isn't anything else worth looking at.\n");
  add_exit(STANDARD_DIR + "post", "north");
  add_exit(STANDARD_DIR + "pier2", "west");
  add_exit(STANDARD_DIR + "harbour1", "south");
  set_noshow_obvious(1);
}
