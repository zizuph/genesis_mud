/*
 * /d/Gondor/common/wep/scalpel.c
 *
 * This scalpel is wielded by the surgeon that is capable of removing
 * scars from you.
 *
 * /Mercade 4 May 1994
 *
 * Revision history:
 */

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 15
#define WEAPON_PEN 35 /* very sharp */

void
create_weapon()
{
    set_name("scalpel");
    add_name("knife");

    set_pname("scalpels");
    add_pname("knives");

    set_adj("very");
    add_adj("sharp");
    add_adj("surgeons");
    add_adj("high");
    add_adj("steel");

    set_short("very sharp scalpel");
    set_pshort("sharp scalpels");

    set_long(BSN("This scalpel can do great things in the hands of a " +
	"surgeon. It looks very sharp. Both the blade and the haft are " +
	"made of high steel."));

    add_item( ({ "blade", "steel blade", "high steel blade" }),
        BSN("The blade of the " + short() + " is made of steel. It is " +
        "polished to a fine gloss. With a special process of cooling it, " +
        "the blade is made very strong and dangerously sharp."));
    add_item( ({ "haft", "steel haft", "high steel haft" }),
        BSN("The haft of the " + short() + " is made of steel just as the " +
	"blade is. This is done to make it very strong and to allow a " +
	"surgeon wood. to be very precise with it."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_KNIFE);
    set_dt( (W_SLASH | W_IMPALE) );
    set_hands(W_NONE);

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
        /* for the beauty! */ 200 + random(101) - 50));
    add_prop(OBJ_M_NO_DROP, "@@obj_m_no_drop");
}

/*
 * The surgeon cannot be forced to drop this scalpel.
 */
mixed
obj_m_no_drop()
{
    return (environment()->id("surgeon"));
}
