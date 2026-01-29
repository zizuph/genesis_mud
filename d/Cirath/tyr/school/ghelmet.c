/* Standard helmet for the guards in the jail of Tyr */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_armour()
{
	set_name("helmet");
	set_short("light glossy helmet");
   set_long("This is a lightweight helmet made from the chitin "
	+"of some large insect that has been coated in a glossy "
	+"finish to make it stronger.\n");
	set_adj("light");
	add_adj("glossy");

	set_ac(20);
	set_at(A_HEAD);

	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VOLUME, 800);
}
