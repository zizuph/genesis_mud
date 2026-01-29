 /* Darryn's scale shirt.
 code (c) 1997 to Damian Horton */

inherit "/std/armour";
#include <wa_types.h>
#include "defs.h"
#include "/sys/formulas.h"

void create_armour()
{
  set_name("shirt");
  set_short("lizardscale shirt");
  set_long("This armored shirt is composed of the greenish-black scales "+
	   "of some indeterminate reptilian creature. The scales are "+
	   "sewn into a quilted backing, to prevent chaffing, and "+
	   "to absorb the impact of blows. It's more comfortable "+
	   "then metal armour, though its still hot under the Athasian "+
	   "sun.\n");
  set_adj("lizardscale");
  add_adj("scale");
  add_adj("lizard");

   set_ac(25);
  set_am(({-1,1,0}));
  set_at(A_BODY);

  add_prop(OBJ_I_WEIGHT, 4900);
  add_prop(OBJ_I_VOLUME, 3900);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15)-random(175));
}
