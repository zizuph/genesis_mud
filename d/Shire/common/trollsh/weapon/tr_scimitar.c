inherit "/std/weapon";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Shire/common/weapon/recover"

create_weapon()
{
    set_name("scimitar");
    add_name("sword");
    set_short("large scimitar");
    set_pshort("scimitars");
    set_adj(({"troll","large","alloyed","guards"}));
    set_long("This is a large scimitar used by the guarding trolls which "
    	    +"patrol under the shaws. It is a cruel, blood-stained scimitar "
    	    +"which obviously have been used a lot in combat. It is rough "
    	    +"and quite heavy.\n");
    set_hit(39);
    set_pen(40);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_BLUDGEON);
    
    add_prop(F_VALUE_WEAPON(34,37) + random(300));
    add_prop(OBJ_I_WEIGHT, 15000);
}
    

