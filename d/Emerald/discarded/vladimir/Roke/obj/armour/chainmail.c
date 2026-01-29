inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

create_armour()
{
set_name("chainmail");
set_short("steel-link chainmail");
set_long("It is a shiny steel chainmail that is made from links of\n"
 + "chain attached to one another. It is very light and versitile.\n");
set_adj("shiny");

set_default_armour(20);
add_prop(OBJ_I_WEIGHT,3500);
add_prop(OBJ_I_VOLUME,2000);
add_prop(OBJ_I_VALUE,320);
}

