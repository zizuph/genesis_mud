inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

create_weapon() {
   int ran;

   set_name("scimitar");
   set_pname("scimitars");
   set_short("curved orc scimitar");
   set_pshort("curved orc scimitars");
   set_adj(({"curved","orc"}));
   set_long("This is a curved scimitar, like the ones orcs tend to wear.\n"
          + "Judging from the stains on the blade, this one has seen some action.\n");

   ran = random(3);
   set_hit(11 + ran);
   set_pen(13 + ran);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_ANYH);

/* Default values are always set /Nick
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(11+ran));
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(11+ran,13+ran));
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

