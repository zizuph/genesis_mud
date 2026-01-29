inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
set_name("chainmail");
set_short("light-steel chainmail");
set_long("This is a steel chainmail of better quality than that "
        +"found on the other goblins around here. It was probably "
        +"stolen from someone else. It seems like it would offer "
        +"good protection.\n");
set_adj("rusty");

set_default_armour(25);
add_prop(OBJ_I_WEIGHT,3500);
add_prop(OBJ_I_VOLUME,2000);
add_prop(OBJ_I_VALUE,320);
}
