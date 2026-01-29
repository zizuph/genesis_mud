/* township/obj/gauntlets.c is cloned by township/npc/townguard.c */
/* and by towncastle/npc/guard.c */
inherit "/std/armour";
 
#include <wa_types.h>
#include "/d/Emerald/defs.h"
 
void
create_armour()
{
    set_name("gauntlets");
    add_adj("banded");
    set_short("pair of gauntlets");
    set_long("It looks like they might suit you.\n");
 
    set_ac(8+random(10));
 
    set_at(A_HANDS);
}
