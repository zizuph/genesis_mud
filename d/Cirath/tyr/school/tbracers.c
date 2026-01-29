
inherit "/std/armour";
#include <wa_types.h>
#include "/d/Cirath/common/defs.h"

void 
create_armour()
{
  set_name("bracers");
  set_short("pair of bracers");
  set_pshort("pairs of bracers");
   set_long("This is a sturdy pair of leather bracers that "
	+"are layered with some form of chitin to make them "
	+"stronger.\n");

  set_adj("leather");

  set_ac(18);
  set_am(({0,0,0}));
  set_at(A_ARMS);

  add_prop(OBJ_I_WEIGHT,  800);
  add_prop(OBJ_I_VOLUME,  400);
}
