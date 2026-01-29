#include "lakeroom.h"

create_lakeroom() {
  set_short("EAST of brooklet");
  set_long("This is the east side of a green brooklet.\n"+
	   "The path continues east between some gentle slopes. ");
  ADD_EXA("brooklet","It looks to run closer to the west.");
  EAST("n_of_plain");
  WEST("rom6");
}
