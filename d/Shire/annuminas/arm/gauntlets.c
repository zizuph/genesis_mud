inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
set_name("gauntlets");
set_short("steel gauntlets");
set_long("This is a pair of steel gauntlets. They seem rather "
	+"nice for a goblin to have, he must have stolen it from "
	+"someone.\n");
set_ac(20);
set_at(A_ARMS);
add_prop(OBJ_I_WEIGHT,1500);
add_prop(OBJ_I_VOLUME,2000);
}
