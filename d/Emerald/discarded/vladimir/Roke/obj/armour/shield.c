inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Roke/common/defs.h"

void
create_armour()

{
set_name("buckler");
set_short("metal buckler");
set_long("Its a small metal shield.\n");
set_adj("metal");
add_adj("round");
add_prop(OBJ_I_VALUE,200);

set_ac(6);
set_am(({ -1, 1, 0}));
set_at(A_SHIELD);
}
