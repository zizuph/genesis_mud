inherit "/std/armour";
#include "/d/Emerald/defs.h"

#include <wa_types.h>
#include <stdproperties.h>


void
create_armour ()
{
	set_name("wreath");
	add_name("head dress");
	set_adj("decorative");
	set_short("head dress");
	set_long("A decorative head dress, made out of berries and leaves.\n");

	set_ac(2);
	set_am(({0, 0, 0}));
  set_at (A_HEAD);
	add_prop(OBJ_I_WEIGHT, 600);
	add_prop(OBJ_I_VOLUME, 300);
	add_prop(OBJ_I_VALUE, 76);
}


