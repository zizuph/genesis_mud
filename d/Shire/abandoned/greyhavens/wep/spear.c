/*

/d/Shire/greyhavens/wep/spear.c

Standard issue spear for Sindar citizens, seaman and fisherman

by Palmer, Dec 04, 2003

 */
 
inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("spear");
   set_pname("spears");
   set_short("long spear");
   set_pshort("long spears");
   set_adj("long");
   set_long("A six foot long black spear. The tip is a polished silver.\n");

   set_default_weapon(40, 40, W_POLEARM, W_IMPALE, W_BOTH, 0);

   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,2058);
   add_prop(OBJ_I_VALUE,50 + ((7*11*7)/4));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
