inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

create_weapon() {
   int ran;

   set_name("sword");
   set_pname("swords");
   set_short("curved orc sword");
   set_pshort("blunt orc swords");
   set_adj(({"blunt","orc"}));
   set_long("The blunt sword has been forged by orc smiths.\n"
          + "It seems very capable of smashing poor peoples heads.\n");

   ran = random(4);
   set_hit(12 + ran);
   set_pen(9 + ran);
   set_wt(W_SWORD);
   set_dt(W_IMPALE);
   set_hands(W_LEFT);

/*
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(12 + ran));
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(11+ran,9 + ran));
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

