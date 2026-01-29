/* Adapted from Orcmaker knife, for use by hobbits */
   inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define WEP_TYPE    W_KNIFE
#define HIT            9
#define PEN            10
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH

void
create_weapon()
{
   set_name("knife");
   add_name(({"knife"}));
   add_adj(({"small"}));
   set_short("small knife");
   set_pshort("small knives");
   set_long("This is a small, single-edged knife, commonly " +
      "carried by hobbits.  It looks quite sharp, but is normally " +
      "used for cutting up food, and probably wouldn't do much " +
      "damage as a weapon.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(HIT,PEN));
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
