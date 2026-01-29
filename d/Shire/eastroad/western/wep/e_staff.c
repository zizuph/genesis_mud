/* Adapted from Orcmaker staff, for use by hobbits 
 * Adapted for use for Elves.
 * Avenger, May 2 1995
 */
 
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#include <formulas.h>
#include "/d/Shire/common/defs.h"
 
#define WEP_TYPE    W_POLEARM
#define HIT            31
#define PEN            12
#define HANDS          W_BOTH
#define DAMAGE         W_BLUDGEON
 
void
create_weapon()
{

 set_name("polearm");
 add_name(({"staff"}));
 add_adj(({"long"}));
 set_short("long staff");
 set_long("This is a long, sturdy staff, crafted from a single " +
  "piece of oak, about as thick as your thumb, and polished "+
  "lovingly.  It has obviously carried its previous owner "+
  "many miles.\n");
 set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
 add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
 add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
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
