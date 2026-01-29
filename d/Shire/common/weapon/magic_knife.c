/* A knife that is enchanted */

inherit "/std/weapon";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

create_weapon() {
   int ran;

   set_name("knife");
   set_pname("knives");
   set_short("glowing knife");
   set_pshort("glowing knives");
   set_adj("glowing");
   set_long("This is a very old knife. It seems very well kept though.\n"); 
   ran = random(3);
   set_hit(8 + ran);
   set_pen(7 + ran);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_ANYH);

   add_prop(MAGIC_AM_MAGIC, ({ 22, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO , ({ "This knife is enchanted. Its not very "
				    + "well done though." , 10 }));
/*
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
