inherit "/std/weapon";
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
 void
create_weapon()
{
   int ran;
    set_name("knife");
   set_pname("knives");
   set_short("dented orc knife");
   set_pshort("dented orc knives");
   set_adj(({"dented","orc"}));
   set_long("This is an orc knife, complete with bloody stains.\n"
          + "The knife is dented, probably by cleaving someones skull.\n");
    ran = random(3);
   set_hit(8 + ran);
   set_pen(7 + ran);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_ANYH);
 /*
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(8+ran));
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(8+ran,7+ran));
*/
}

