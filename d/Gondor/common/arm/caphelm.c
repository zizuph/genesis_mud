inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour()
{
    set_name(({"helmet","helm"}));
    set_pname("helmets");
    add_pname("helms");
    set_adj("golden");
    set_short("golden helmet");
    set_pshort("golden helmets");
    set_long("The helmet of a captain in the army of Harad.\n");
    set_default_armour(30, A_HEAD, (({ 0, 0, 0})), 0);	    
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 5000); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30)+random(200)-100);
}  
