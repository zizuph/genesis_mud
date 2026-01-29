#include "/d/Shire/common/defs.h"
inherit "/std/armour";
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
    set_name(({"armour","chainmail","mail"}));
    set_short("rigid chainmail");
    set_adj(({"black","triple"}));
    set_long("This is a black chainmail made of triple links. It looks "
    	    +"like it can take a lot of damage. The chains are thick and "
    	    +"are about 1 inch in diameter. It has the sign of the red skull "
    	    +"in it, which is the sign of the Angmarim trolls, coming from the "
    	    +"north.\n");
    
    set_ac(30);
    set_at(A_BODY);
    set_am(({ 0, 0, 0 }));
    set_af(TO);
    set_shield_slot(A_BODY);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(40,A_BODY));
    add_prop(OBJ_I_VOLUME, F_VOLUME_ARMOUR);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) +(random(600)-300));
    
}


