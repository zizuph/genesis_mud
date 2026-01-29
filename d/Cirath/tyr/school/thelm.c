/* l_vhelm.c: The helm of Lyden. Revised by Serpine, 11/24/95. */
 
#pragma strict_types
 
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"
 
void
create_armour()
{
    set_name(({"helm", "helmet"}));
    set_adj("red");
    add_adj("deep");
    set_short("red deep helm");
    set_long("Steel is rare in Athas, so even a rusty piece can set a "
            +"warrior apart as one of the greats.\n");
    set_ac(35);
    set_at(A_HEAD);
 
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 900);
}
