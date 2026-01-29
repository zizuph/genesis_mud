inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

create_weapon() {
   int ran;

   set_name("axe");
   set_pname("axes");
   set_short("dull orc axe");
   set_pshort("dull orc axes");
   set_adj(({"dull","orc"}));
   set_long("This is an orc axe, complete with orcish markings.\n"
          + "The axe is dulled, probably by trying to cut down wood.\n");

   ran = random(3);
   set_hit(8 + ran);
   set_pen(7 + ran);
   set_wt(W_AXE);
   set_dt(W_BLUDGEON | W_SLASH);
   set_hands(W_ANYH);

/* This is just default values and they are set anyway
 * Nick
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(8+ran));
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(8+ran,7+ran));
 */
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
