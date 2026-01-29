/*
 * Originally the Shortsword for the Hin Warrior guard
 * Now a common dagger for the charity boxes
 * Finwe, April 2004
 */

#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
 
inherit "/std/weapon";
inherit "/lib/keep";

#define HIT 8 + random(4)
#define PEN 8 + random(4)

create_weapon()
{
    set_name("dagger");
    add_name("knife");
    set_pname("daggers");
    set_pname("knives");
    set_short("dull dagger");
    set_pshort("dull daggers");
    set_adj("dull");
    set_long("The " + short() + " is made from steel. It looks used but " +
        "dull colored.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
        HIT,                     /* 'to hit' value    */
        PEN,                     /* penetration value */
        W_KNIFE,                /* weapon type       */
        W_IMPALE | W_SLASH,     /* damage type       */
        W_ANYH,                /* nr of hands       */
        0);           /* object that defines wield and unwield functions */

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
    set_keep();
}

