// White shirt,  equipment of ~Avenir/common/dark/rogue
// made by Boriska, Feb 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("shirt");
  set_short("white linen shirt");
  add_adj(({"white", "linen"}));
  set_long ("White shirt custom made by good taylor. It appears to be\n" +
	    "of rather small size though and not extremely clean.\n");
  set_ac (7);
  set_at (A_BODY);
  add_prop (OBJ_I_WEIGHT, 2000);
  add_prop (OBJ_I_VOLUME, 1000);
}
