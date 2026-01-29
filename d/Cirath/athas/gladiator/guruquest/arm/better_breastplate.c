 /* Armour for Myrdoth.
 code (c) 1997 to Damian Horton
 Updated, March 2001, for Raumdor
*/

inherit "/std/armour";

#include <wa_types.h>
#include "/d/Cirath/defs.h"
#include <formulas.h>

void create_armour()
{
  set_name("breastplate");
  set_short("kank banded breastplate");
  set_long("This piece of banded mail armour consist of horizontal "+
	   "strips of kank carapace, bound together and reinforced "+
	   "in critical areas by inix leather. Well ventilated and "+
	   "light by comparaison with its metal equivalent, it still "+
	   "provides decent protection. This particular breastplate "+
	   "appears to have been especially well fashioned.\n");

  set_adj("banded");
  set_adj("kank");

  set_ac(22);
  set_am(({-1,-1,2}));
  set_at(A_BODY);

  add_prop(OBJ_I_WEIGHT, 7320);
  add_prop(OBJ_I_VOLUME, 4200);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(22) + 25 + random(50));
}


