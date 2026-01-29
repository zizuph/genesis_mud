
/* 
 * mace.c
 * A mace, carried by Goblins
 * City of Gulfport, Northern Ergoth
 * Tibbit, 22 May 1998
 */

inherit "/std/weapon";
#include <wa_types.h> /* Some weapon-specific defs */
#include <stdproperties.h>

void
create_weapon()
{
    set_name("mace");
    set_adj("steel");
    add_adj("studded");
    set_short("studded steel mace");

    set_long("A steel-crafted mace, it is a rather nice weapon.  "+
        "The shaft and the head are both covered with studs, likely "+
        "to seriously injure anyone who gets in their way."+
        "\n");

    set_hit(29);
    set_pen(22);

    set_dt(W_BLUDGEON);
    set_wt(W_CLUB);

    set_hands(W_ANYH);

    /* Props for value, volume, weight may be set if you like */
    add_prop(OBJ_I_VALUE,290);
    add_prop(OBJ_I_WEIGHT,1200);
    add_prop(OBJ_I_VOLUME,1200);
}
