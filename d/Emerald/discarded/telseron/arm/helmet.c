/* township/obj/helmet.c is cloned by townsgip/npc/townguard.c */
/* and by towncastle/npc/guard.c */
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
 
void
create_armour()
{
    set_name("helmet");
    add_adj("steel");
    set_long("It looks like it might suit you.\n");
 
    set_ac(14);
 
    set_at(A_HEAD);
}
