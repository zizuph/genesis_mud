/* Ashlar, 3 Aug 97 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 12
#define PEN 8

create_weapon()
{
   set_name("spoon");
   set_adj("small"); 
   set_short("small spoon");   set_long("It is a small spoon with a sharpened handle.\n");
   set_hit(HIT);
   set_pen(PEN);
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(10)-5);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 450);
}

