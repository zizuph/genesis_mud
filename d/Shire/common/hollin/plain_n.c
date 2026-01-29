#include "lakeroom.h"

create_lakeroom() {
  set_short("Northern part of plain");
  set_long(
	   "You are standing on the northern part of the plain. "+
	   "To the west is the lake, and to the east stands a tall white "+
	   "tree which stretches its boughs up towards the rocky wall. "+
	   "The plain closes to the north, but extends further to the south. ");
  ADD_EXA("tree","Perhaps you should go closer, that is: east?");
  ADD_EXA("plain","You see nothing special.");
  NORTH("n_of_plain");
  EAST("tree_n");
  SOUTH("in_front");
}
