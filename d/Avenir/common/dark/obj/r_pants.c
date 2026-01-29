// Durty leather pants, equipment of ~Avenir/common/dark/rogue
// made by Boriska, Feb 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("pants");
  set_pname("pants");
  set_short("black leather pants");
  set_pshort("black leather pants");
  set_long("Black pants made of high quality leather with linen\n" +
	   "underside. They are of simple appearance but well made.\n");
  add_adj(({"leather", "black"}));
  set_ac (10);
  set_at (A_LEGS);
  add_prop (OBJ_I_WEIGHT, 3000);
  add_prop (OBJ_I_VOLUME, 2000);
}

