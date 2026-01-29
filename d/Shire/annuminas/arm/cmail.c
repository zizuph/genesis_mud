inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
set_name("chainmail");
set_short("steel-link chainmail");
set_long("This is a nice suit of chainmail. It is made of nice "
        +"steel links interlocked with each other. It is "
        +"lightweight and versatile.\n");
set_adj("rusty");

set_default_armour(15);
add_prop(OBJ_I_WEIGHT,3500);
add_prop(OBJ_I_VOLUME,2000);
add_prop(OBJ_I_VALUE,320);
}
