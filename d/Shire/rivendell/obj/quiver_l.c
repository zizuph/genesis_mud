/* Quiver arrows from Rivendell
 * Finwe, June 2004
 */

inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"  
#include <stdproperties.h>
#include <wa_types.h>

create_container()
{
    FIXEUID;
    set_name("quiver");
    set_short("leather quiver");
    set_pshort("leather quivers");
    set_adj("leather quiver");
    set_long("This long quiver is designed to hold arrows. It is round " +
        "and will fit snugly on your back.\n");
    add_prop(CONT_I_WEIGHT,     1000);  
    add_prop(CONT_I_MAX_WEIGHT, 6000);  
    add_prop(CONT_I_VOLUME,     3000);  
    add_prop(CONT_I_MAX_VOLUME, 5000);  
    add_prop(CONT_I_RIGID, 0);          
    add_prop(CONT_I_IS_QUIVER, 1);      
    add_prop(OBJ_I_VALUE,40);           
    set_slots(A_BACK);
    set_layers(4);
    set_looseness(20);
}


void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
