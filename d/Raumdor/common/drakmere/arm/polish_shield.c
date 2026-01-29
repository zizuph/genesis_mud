inherit "/std/armour";
#include "/d/Raumdor/defs.h"

/* by Nerull*/

void
create_armour()
{
    ::create_armour();
    
    set_name("shield");
    set_short("polished silvery shield");
    add_name("shield");
    set_adj("polished");
    add_adj("silvery");
    set_long("A standard large shield of silvery steel that covers a"
    +" good portion of your body. Its polished and reflects"
    +" light nicely.\n");
 
    set_ac(40);
    set_at(A_SHIELD);
   
    add_prop(OBJ_I_VALUE, 850);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 5000);
    set_af(TO);
}



