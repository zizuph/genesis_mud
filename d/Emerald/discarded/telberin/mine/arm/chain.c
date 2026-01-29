 
/* mine/arm/chain.c is cloned by mine/npc/dwarf3.c */
 
inherit "/std/armour";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_armour()
{
    set_name("chainmail");
    set_short("dwarven chainmail");
    set_long( "This chainmail is strong and made entirely "+
              "of stainless steel.\n" );
    set_adj("dwarven"); 
    set_ac(22);
    set_at(A_TORSO);
    set_am(({     1,      1,      -2 }));
}
