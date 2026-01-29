inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Shire/common/armour/recover"

create_armour()
{
    set_name( "plate" );
    set_pname("plates");
    set_short("spiked leather plate");
    set_pshort("spiked leather plates");
    set_adj(({"spiked","studded"}));
    set_long("This is a rough troll-made leather plate. It has spikes inserted "
    	    +"in it, and studs inserted in it. It is full of stained blood. It "
    	    +"has the sign of a red skull on the front of it.\n");
    	    
    set_ac(15);
    set_at(A_BODY);
    set_am(({ 0, 1, -1 }));
    set_af(TO);
    set_shield_slot(A_BODY);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_BODY));
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
    
}

