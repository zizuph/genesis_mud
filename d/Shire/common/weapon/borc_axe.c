inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

create_weapon() {

   set_name("axe");
   set_pname("axes");
   set_short("shiny sharp axe");
   set_pshort("shiny sharp axes");
   set_adj(({"shiny","sharp"}));
   set_long("This is an orc axe, complete with orcish markings.\n"
       + "This axe looks like it belongs in the hands of a leader.\n");

   set_hit(20);
   set_pen(28);
   set_wt(W_AXE);
   set_dt(W_BLUDGEON | W_SLASH);
   set_hands(W_ANYH);

/* This is just default values and they are set anyway
 * Nick
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(8));
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(8,7));
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
