/* Ashlar, 3 Aug 97 */

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 40
#define PEN 40

create_weapon()
{
    set_name("club");
    add_name("branch");
    set_adj("large");
    add_adj("black");
    set_short("large black branch");
    set_long("This is a large wooden branch with an unusual color. " +
             "The weight from this branch alone makes it a powerful weapon.\n");
   set_hit(HIT);
   set_pen(PEN);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_BOTH);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(40));
   add_prop(OBJ_I_VOLUME, 6000);
   add_prop(OBJ_I_WEIGHT, 28000);
}
