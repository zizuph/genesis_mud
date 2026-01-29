
/* 
 * cutlass.c
 * Cutlass, used by the typical sailor
 * City of Gulfport, Northern Ergoth
 * Tibbit, 22 May 1998
 */

inherit "/std/weapon";
#include <wa_types.h> /* Some weapon-specific defs */
#include <stdproperties.h>

void
create_weapon()
{
    set_name("cutlass");
    set_adj("sailor's");
    set_short("sailor's cutlass");

    set_long("The narrow slashing sword known as the cutlass is a favorite "+
        "among sailors. This one appears to be well-made."+
        "\n");

    set_hit(29);
    set_pen(22);

    set_dt(W_SLASH);
    set_wt(W_SWORD);

    set_hands(W_ANYH);

    /* Props for value, volume, weight may be set if you like */
    add_prop(OBJ_I_VALUE,300);
    add_prop(OBJ_I_WEIGHT,800);
    add_prop(OBJ_I_VOLUME,800);
}
