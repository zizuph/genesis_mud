/* Ashlar, 3 Aug 97 */

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 25
#define PEN 30

create_weapon()
{
    set_name("club");
    set_adj("huge");
    add_adj("wooden");
    set_short("huge wooden club");
    set_long("This huge wooden club is much preferred by the trolls. By " +
        "its weight alone, it is a powerful weapon.\n");
   set_hit(HIT);
   set_pen(PEN);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(30)-15);
   add_prop(OBJ_I_VOLUME, 6000);
   add_prop(OBJ_I_WEIGHT, 8000);
}
