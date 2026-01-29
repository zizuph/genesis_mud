
/* 
 * big_club.c
 * A big club, carried by ogres
 * City of Gulfport, Northern Ergoth
 * Tibbit, 22 May 1998
 */

inherit "/std/weapon";
#include <wa_types.h> /* Some weapon-specific defs */
#include <stdproperties.h>

void
create_weapon()
{
    set_name("club");
    set_adj("large");
    add_adj("simple");
    set_short("large simple club");

    set_long("This club is simply a large, heavy piece of "+
        "wood, as might be wielded by ogres and the like."+
        "\n");

    set_hit(16);
    set_pen(8);

    set_dt(W_BLUDGEON);
    set_wt(W_CLUB);

    set_hands(W_ANYH);

    /* Props for value, volume, weight may be set if you like */
    add_prop(OBJ_I_VALUE,68);
    add_prop(OBJ_I_WEIGHT,15000);
    add_prop(OBJ_I_VOLUME,15000);
}
