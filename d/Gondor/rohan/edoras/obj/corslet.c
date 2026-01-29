inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"

create_armour()
{
    set_name("corslet");
    add_name("armour");
    set_pname("corslets");
    set_adj("bright");
    add_adj("long");
    set_short("bright long corslet");
    set_pshort("bright long corslets");
    set_long("A long corslet of overlapping plates that have been brandished bright.\n");
    set_default_armour(34, A_TORSO, (({ -2, 1, 1})), 0);	    
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 5000); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(34)+random(500)-100);
}  
