#include "lakeroom.h"

create_lakeroom() {
  set_short("Slimy brooklet");
  set_long(
	   "You are wading across a green and slimy brooklet.\n"+
	   "The stones are very slippery, so take care not to fall!\n"+
	   "The main path continues east and west. ");
  ADD_EXA("brooklet,stones,path",
       "The stones in the brooklet look very slippery. You might in fact fall.");
  EAST("rom7");
  WEST("rom3");
}
