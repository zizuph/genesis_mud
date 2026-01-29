/* Adapted from Orcmaker dagger, for use by hobbits */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define WEP_TYPE    W_KNIFE
#define HIT            12
#define PEN            13
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH | W_IMPALE

void
create_weapon()
{
   set_name("dagger");
   add_adj(({"long"}));
   set_short("long dagger");
   set_long("This is a long, thin dagger, that has been made " +
      "for use by a hobbit.  The grip is small, for a hobbit's " +
      "hand, but the dagger could probably be used by anyone.\n");
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
