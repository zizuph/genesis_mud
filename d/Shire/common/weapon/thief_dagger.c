inherit "/std/weapon";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

create_weapon() {
   int ran;

   set_name(({ "dagger" }));
   set_short("long sharp dagger");
   set_adj(({"long","sharp"}));
   set_long("From the looks of the handle, this dagger has been well-used,\n"
          + "but the blade looks to be at least as sharp as anything you'd find at\n"
          + "the smithy.  The well-worn fabric covering the handle is tinged\n"
          + "reddish-brown.\n");

   ran = random(10);
   set_hit(15 + ran);
   ran = random(5);
   set_pen(7 + ran);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE);
   set_hands(W_ANYH);

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
