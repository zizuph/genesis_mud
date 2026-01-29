/*
 *  Dagger for the illithids
 *  -- Finwe, July 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

inherit FAERUN_WEP_BASE;

int hit = 14 + random(5),
    pen = 16 + random(5);

void create_faerun_weapon() 
{
    set_name("dagger");
    set_adj("polished");
    set_adj("steel");
    set_short("polished steel dagger");
    set_long("The " + short() + " is made of steel. The blade is long " +
        "and designed for stabbing. The handle has a large silver skull " +
        "on it. \n");

    set_default_weapon(     /* See /sys/wa_types.h for maxima */
      hit,                  /* 'to hit' value    */
      pen,                  /* penetration value */
      W_KNIFE,              /* weapon type       */
      W_IMPALE | W_SLASH,   /* damage type       */
      W_ANYH,               /* nr of hands       */
      0);               /* object that defines wield and unwield functions */

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));
}
