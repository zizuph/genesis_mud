#include "lakeroom.h"

create_lakeroom() {
  set_short("East of the lake");
  set_long(
	   "You are standing east of the Sirannon lake, in front of "+
	   "the highest part of a rocky wall somewhat to the east. "+
	   "The mountain lake stretches westwards, and on the other side you can see "+
	   "the dam where the river of Sirannon used to gush down to the lowlands. "+
	   "The plain opens to the north and the south. "+
	   "It is remarkable that there seems to be a well-walked track going east. ");
  ADD_EXA("wall,mountain","The wall seems polished and featureless, strange.");
  ADD_EXA("dam","On the other side. Go around on the north side of the lake.");
  ADD_EXA("plain","It's to the north and to the south.");
  ADD_EXA("track","Leading to the wall. Interesting!");
  NORTH("plain_n");
  EAST("under_wall");
  SOUTH("plain_s");
}
