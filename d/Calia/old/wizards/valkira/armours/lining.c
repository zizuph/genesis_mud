//OBJECT: cloak lining
    /* Calia Domain

    HISTORY

    Created by Valkira 8/16/99

    PURPOSE

    The inner lining to a traveller's cloak.  It has a secret pocket.*/

inherit "/d/Genesis/std/pack";
inherit "/lib/keep"; 
inherit "/lib/wearable_item";

#include <stdproperties.h>

void
create_pack()
{
    set_name("lining");
    add_name("secret pocket");

    set_adj("inner");

    set_short("traveller's cloak lining");
    
    set_long("This lining is worn with the traveller's cloak.  There" +
        " is a secret pocket in the lining.\n");

    set_wf(0);
    set_mass_storage(1);

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 4500);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(OBJ_I_NO_DROP,"You need this lining, so you keep it.");
    
} 
