/* township/obj/plate.c is cloned by township/npc/townguard.c */
/* and by towncastle/npc/guard.c */
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
 
create_armour()
{
    set_name("mail");
    set_short("plate mail");
    add_adj("steel");
    add_adj("plate");
    set_long("You can't even see a dent in it.\n");
 
    set_ac(25);
 
    set_at(A_TORSO);
}
