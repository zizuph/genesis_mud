inherit "/std/receptacle";
#include "/d/Kalad/defs.h"

create_container()
{
    set_name("basket");
    set_pname("wicker baskets");
    set_short("wicker basket");
    set_adj("wicker");
    set_long(BS("The wicker basket has seen better days.\n"));    

    add_prop(CONT_I_WEIGHT, 250);  /* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 2250);     /* It can hold 2000 grams*/
     add_prop(CONT_I_VOLUME, 60);
    add_prop(CONT_I_MAX_VOLUME, 2030);     /* 2 litres of volume */ 
	add_prop(OBJ_I_VALUE,440);
}


