/* Quiver for the Uruk-hai in Moria
 * Based on the haradrim arrows from Gondor.
 * Thanks Rohim and Gondor!!
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
    set_short("long quiver");
    set_pshort("long quivers");
    set_adj("long");
    set_long("This long quiver is designed to hold arrows. It is " +
        "rectangular in shape and black and looks like it was once " +
        "used by an uruk-hai.\n");
    add_prop(CONT_I_WEIGHT,     1000);   /* It weighs 1 Kg            */
    add_prop(CONT_I_MAX_WEIGHT, 6000);   /* It can contain up to 5 Kg  */
    add_prop(CONT_I_VOLUME,     3000);   /* It measures 3 Ltr         */
    add_prop(CONT_I_MAX_VOLUME, 13000);  /* It can contain 10 Ltr       */
    add_prop(CONT_I_RIGID, 0);           /* It is not a rigid object       */
    add_prop(CONT_I_IS_QUIVER, 1);       /* It is a quiver */
    add_prop(OBJ_I_VALUE,40);            /* Value 40 cc*/
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
