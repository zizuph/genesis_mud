
/* 
 * big_knife.c
 * A big knife, carried by ogres
 * City of Gulfport, Northern Ergoth
 * Tibbit, 22 May 1998
 */

inherit "/std/weapon";
#include <wa_types.h> /* Some weapon-specific defs */
#include <stdproperties.h>

void
create_weapon()
{
    set_name("knife");
    set_adj("large");
    add_adj("heavy");
    add_adj("bone");
    set_short("large heavy bone knife");

    set_long("Crafted from the bone of some dead animal, "+
        "this knife is typical of the kind carried by wild "+
        "ogres near the lands of Ergoth."+
        "\n");

    set_hit(10);
    set_pen(11);

    set_dt(W_SLASH);
    set_wt(W_KNIFE);

    set_hands(W_ANYH);

    /* Props for value, volume, weight may be set if you like */
    add_prop(OBJ_I_VALUE,120);
    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME,400);
}
