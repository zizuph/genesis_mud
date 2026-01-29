inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
    set_name("torso");
    set_adj(({"black polished","blackened","polished"}));
    set_short("black polished torso");
    set_pshort("black polished torsos");
    set_long(
    	"This is a blackened torso, quite well crafted for troll armour. It "
    	+"is polished and looks strong, and tough.\n");
    	
    set_ac(38);
    set_at(A_TORSO);
    set_am(({ 0, 0, 0 }));
    set_af(TO);
    set_shield_slot(A_BODY || A_ROBE);
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(38, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) + random(200) + 50);
    
}
