/* just a standard sword */
/* This object is put in bree/shop_store every reset */

inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

create_weapon()
{
    set_name(({"shopsword", "sword"}));    /* extra unique name */
    set_pname("swords");
    set_short("old rusty sword");
    set_pshort("old rusty swords");
    set_adj(({"old", "rusty"}));
    set_long("The sword has been used very often... Perhaps too often.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       6,                      /* 'to hit' value    */
       8,                      /* penetration value */
       W_SWORD,                /* weapon type       */
       W_IMPALE,               /* damage type       */
       W_NONE,                 /* nr of hands       */
       0);           /* object that defines wield and unwield functions */

   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME,4500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(6, 8));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
