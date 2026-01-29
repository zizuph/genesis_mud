 /*
 * Knife for charity box
 * Finwe, April 2004
 */

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit "/std/weapon";
inherit "/lib/keep";

#define HIT 8 + random(4)
#define PEN 8 + random(4)

create_weapon()
{
    set_name("knife");
    add_name("_ch_oknife_");
    set_pname("knives");
    set_short("notched orc knife");
    set_pshort("notched orc knives");
    set_adj(({"notched","orc"}));
    set_long("This is a " +short() + ". The blade is jagged and appears " +
        "to hve been made by orcs. The knife has a couple of notches in " +
        "the blade, probably from hitting skulls or armours.\n");

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

