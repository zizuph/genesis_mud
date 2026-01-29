inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_AXE
#define HIT            22
#define PEN            30
#define HANDS          W_BOTH
#define DAMAGE         W_IMPALE

void
create_weapon()
{
   set_name("axe");
   add_name(({"axe"}));
   add_adj(({"great","mighty"}));
   set_short("great mighty axe");
   set_pshort("great mighty axes");
   set_long("This mighty axe looks untouched and untarnished since "+
   "what must have been an age. It is of dwarven make and the axe-blade "+
   "is much bigger than any other of that era "+
   ".\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,1800);

}
   
string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
