/* created by Aridor 07/06/93 */

inherit "/std/weapon";

#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("knife");
    set_adj("small");
    set_adj("sparkling");
    set_short("small sparkling knife");
    set_long(BS("This knife sparkles in all different colors."
         +   "You wonder if it is of any real use.",SL));

    set_hit(5);
    set_pen(3);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, 60);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 600);

}

