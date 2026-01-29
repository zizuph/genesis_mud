#include <stdproperties.h>

inherit "/std/bow";

public void
create_bow()
{
  set_adj(({"sleek", "elven"}));
  set_short("sleek elven bow");
  set_long("The bow very sleek and very light, still you feel " + 
	   "that it would require considerable strength to draw it. " +
	   "It is made from some kind of white wood that has been " +
	   "decorated with thin elven runes that seem to twine with " +
	   "the fibers of the wood.\n");
  add_prop(OBJ_I_WEIGHT, 900);
  add_prop(OBJ_I_VOLUME, 3250);
  set_hit(40);
  set_pen(58);
}
  
