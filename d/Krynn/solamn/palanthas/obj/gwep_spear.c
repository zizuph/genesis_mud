/* Mortis 09.2014
 *
 * Common weapons used by city guards in Palanthas.
 *
 */

#include <wa_types.h>
#include "../local.h"

inherit "/std/weapon";
inherit "/lib/keep";

#define VK_NOBUY                    "_vkeep_shop_no_buy"

create_weapon()
{
    set_name("spear");
    set_adj("oak-shafted");
    set_short("oak-shafted spear");
    set_long("Atop an eight foot oak shaft is a sharp steel spearhead.\n");

    set_hit(30);
    set_pen(31);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);

    add_prop(OBJ_I_VOLUME, 3000 + random(500));
    add_prop(OBJ_I_WEIGHT, 4000 + random(550));
    add_prop(VK_NOBUY, 1);
}

