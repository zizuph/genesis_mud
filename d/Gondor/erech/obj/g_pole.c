/*
 * g_pole.c
 * By Skippern
 * June 2000
 *
 * To be found on some of the ghosts in the Path of the Dead in
 * Gondor.
 */
inherit "/std/weapon";

#include <wa_types.h>        /* Contains weapon-related definitions */
#include <formulas.h>        /* Conaitns formulas for weight, value etc. */
#include <stdproperties.h>   /* OBJ_I_VALUE and similar properties */

#define HIT 10
#define PEN 30

/* Prototypes */
void               create_weapon();

/*
 * Function name:    create_weapon()
 * Description  :    Creates the weapon.
 */
void
create_weapon()
{
    set_name("spear");
    set_short("simple spear");
    set_pshort("simple spears");
    set_long("It is a simple spear made from a pole of ash with a large " +
	"arrowhead at the end. Despite its simple nature, it looks quite " +
	"dangerous.\n");
    set_adj("simple");

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_POLEARM);
    set_dt(W_IMPALE);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(30) - 15 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM) + 
	random(60) - 30 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
