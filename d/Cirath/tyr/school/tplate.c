/*This is the standard armour for the guards in the jail of Tyr. */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_armour()
{
	set_name("breastplate");
   set_adj("hide");
   add_adj("thick");
   set_short("thick hide breastplate");
   set_long("This breastplate looks to be made from a huge piece "
	+"of animal skin of some sort.  Upon closer inspection, you "
	+"see that the hide is used solely as a cover for the thick piece "
   	+"of metal that is beneath it.  The metal could probably "
	+"offer quite a bit of protection in a fight.\n");


   set_ac(40);
	set_at(A_BODY);

	add_prop(OBJ_I_WEIGHT, 10800);
	add_prop(OBJ_I_VOLUME, 12000);
}
