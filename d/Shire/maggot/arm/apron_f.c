inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
	set_name("apron");
	add_adj(({"faded","cloth"}));
	set_short("faded cloth apron");
	set_pshort("faded cloth aprons");
	set_long("This "+short()+" is the type worn by hobbit women and girls when working about the house and garden.\n");
	set_ac(5 + random(2));
	set_am( ({ 0, 0, 0}) );
	set_at(A_ROBE);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 300 + random(100));
	add_prop(OBJ_I_VOLUME, 100 + random(50));
}
