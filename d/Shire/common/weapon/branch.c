inherit "/std/weapon";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

create_weapon() {
   int ran;

   set_name("branch");
   set_pname("branches");
   set_short("pine branch");
   set_pshort("pine branches");
   set_adj("pine");
   set_long("This is a branch from a pine tree.\n"
	    + "It could brobably serve as a club\n");

   ran = random(3);
   set_hit(8 + ran);
   set_pen(8 + ran);
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
