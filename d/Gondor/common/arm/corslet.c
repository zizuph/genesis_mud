inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour()
{
    set_name("corslet");
    add_name("armour");
    set_pname("corslets");
    set_adj("brazen");
    add_adj("banded");
    set_short("brazen banded corslet");
    set_pshort("brazen banded corslets");
    set_long("A corslet of overlapping brazen plates.\n");
    set_default_armour(39, A_TORSO, (({ -2, 1, 1})), 0);	    
    add_prop(OBJ_I_WEIGHT, 9600);
    add_prop(OBJ_I_VOLUME, 5000); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(39)+random(500)-250);
}  
