/* township/obj/boots.c is cloned by township/npc/townguard.c  */
/* and by towncastle/npc/guard.c */
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
 
void
create_armour()
{
    set_name("boots");
    add_adj("sturdy");
    set_short("pair of boots");
    set_long("It looks like they might suit you.\n");
 
    set_ac(8+random(10));
 
    set_at(A_FEET);
}
