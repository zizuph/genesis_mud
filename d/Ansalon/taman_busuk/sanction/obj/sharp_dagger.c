#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

inherit "/std/weapon";
inherit "/lib/keep";

#define WEAPON_HIT 32
#define WEAPON_PEN 28

void
create_weapon()
{
   set_name("dagger");
   set_pname("daggers");
   add_pname("weapons");
   set_adj("sharp");
   add_adj("long");
   set_short("long steel dagger");
   set_long("Over a foot long, this " +
            "sharp dagger looks very intimidating. The pommel of the dagger is " +
            "wrapped in leather, and its blade is extremely sharp.\n");

   set_hit(WEAPON_HIT);
   set_pen(WEAPON_PEN);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_ANYH);
   
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));
}
