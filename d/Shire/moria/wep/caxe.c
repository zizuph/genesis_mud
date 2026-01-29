inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_AXE
#define HIT            20
#define PEN            28
#define HANDS          W_BOTH
#define DAMAGE         W_SLASH

void
create_weapon()
{
   set_name("axe");
   add_name(({"axe"}));
   add_adj(({"curved","ancient"}));
   set_short("ancient curved axe");
   set_pshort("ancient curved axes");
   set_long("This ancient axe looks untouched and untarnished since "+
   "what must have been an age. It is of dwarven make and the axe-blade "+
   "curves menacingly at the front to provide an excellent chopping "+
   "surface.\n");
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
