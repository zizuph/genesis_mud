	inherit "/std/armour.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Avenir/common/common.h"

create_armour()
{
	set_name("tribal necklace");
	add_name("necklace");
	set_short("tribal necklace");
	set_long("This is a home-made necklace of sea shells and other things the tribeswomen gather to make jewellery.\n");

	set_ac(8);
	set_am( ({0, 1, -1}) );
	set_at(A_NECK);

	add_prop(OBJ_I_VALUE, 70);
	add_prop(OBJ_I_VOLUME, 112);
	add_prop(OBJ_I_WEIGHT, 119);
}
