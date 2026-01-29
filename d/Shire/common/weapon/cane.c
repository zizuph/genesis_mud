inherit "/std/weapon";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

create_weapon() {
   int ran;

   set_name("cane");
   set_pname("canes");
   set_short("wooden cane");
   set_pshort("wooden canes");
   set_adj("wooden");
   set_long("This is a wooden cane.\n");

   ran = random(3);
   set_hit(5 + ran);
   set_pen(5 + ran);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);


}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
