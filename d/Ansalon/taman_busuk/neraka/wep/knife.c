/* Ashlar, 1 Jul 98 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 8
#define PEN 10

create_weapon()
{
   set_name("knife");
   set_adj("ceremonial"); 
   set_short("ceremonial knife");   set_long("It is a small ceremonial knife. It is sharp, but not " +
   "really fit for combat.\n");
   set_hit(HIT);
   set_pen(PEN);
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(10)-5);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 450);
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg); 
}

