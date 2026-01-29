
/* 
 * knife.c
 * A simple utility knife
 * City of Gulfport, Northern Ergoth
 * Tibbit, 1 May 1998
 */

inherit "/std/weapon";
#include <wa_types.h> /* Some weapon-specific defs */
#include <stdproperties.h>

void
create_weapon()
{
    set_name("knife");
    set_adj("small");
    add_adj("utility");
    set_short("small utility knife");

    set_long("This simple knife is used for small "+
        "cutting jobs, and might be possessed by "+
        "any citizen."+
        "\n");

    set_hit(10);
    set_pen(11);

    set_dt(W_IMPALE | W_SLASH);
    set_wt(W_KNIFE);

    set_hands(W_ANYH);

    /* Props for value, volume, weight may be set if you like */
    add_prop(OBJ_I_VALUE,70);
    add_prop(OBJ_I_WEIGHT,360);
    add_prop(OBJ_I_VOLUME,350);
}
