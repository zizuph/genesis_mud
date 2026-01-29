   
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>
#define MY_RANDOM_FORMULA (random(30) + 10)

void create_armour()

	{

	set_name("crystal body armour");
	set_short("crystal body armour");
	set_pshort("crystal body armours");
	set_long("This armour appears to be crafted "+
		"from a heavy metal coated with blue "+
		"shining crystal.  On the breast of the "+
		"armour is carved the figure of a white horse.\n");
	set_adj("shining");
	likely_break = random(30);
	likely_cond = random(30);
	set_ac(25);
	set_at(A_BODY);
	add_prop(OBJ_I_WEIGHT, random(10000) + 10000);
	add_prop(OBJ_I_VOLUME, random(10000) + 10000);
	add_prop(OBJ_I_VALUE,
		F_VALUE_ARMOUR
		(random(30) + 10)
		+ random(20) - 10);
	}
