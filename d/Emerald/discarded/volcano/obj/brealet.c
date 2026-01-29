inherit "/std/armour";
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
	set_name("bracelet");
	set_adj("small");
	set_short("bracelet");
	set_long("   A hand-crafted bracelet, made of seashells, and other " +
	"things the tribeswomen gather to make their jewellery. " +
	"This one is made to honour the gods which the tribe worship.\n\n");
                                                            
  set_ac(6);
  set_am(({ 0, 0, 0}));
  set_at (A_L_ARM);
	add_prop(OBJ_I_VALUE, 100);
  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME, 500);
}
