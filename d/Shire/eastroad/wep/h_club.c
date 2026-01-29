/* Adapted from Orcmaker club, for use by hobbits. */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define WEP_TYPE    W_CLUB
#define HIT            15
#define PEN            7
#define HANDS          W_ANYH
#define DAMAGE         W_BLUDGEON

void
create_weapon()
{
   set_name("club");
   add_name(({"club"}));
   add_adj(({"sturdy","wooden"}));
   set_short("sturdy club");
   set_pshort("sturdy clubs");
   set_long("This sturdy wooden club is really nothing more than " +
      "than a cudgel, normally used for bashing weeds.  However, you " +
      "might be able to use it as a weapon if necessary.\n");
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
