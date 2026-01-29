inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
set_name("greaves");
set_short("steel greaves");
set_long("This is a pair of steel greaves. They seem rather "
	+"nice for a goblin to have, he must have stolen it from "
	+"someone.\n");
set_ac(20);
set_at(A_LEGS);
add_prop(OBJ_I_WEIGHT,1500);
add_prop(OBJ_I_VOLUME,2000);
}
