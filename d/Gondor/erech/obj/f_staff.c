/*
 * f_staff.c
 * By Skippern December 2000
 *
 * To be found on some of the farmers in Erech.
 */
inherit "/std/weapon";

#include <wa_types.h>        /* Contains weapon-related definitions */
#include <formulas.h>        /* Conaitns formulas for weight, value etc. */
#include <stdproperties.h>   /* OBJ_I_VALUE and similar properties */

#define HIT 20
#define PEN 15

/* Prototypes */
void               create_weapon();

/*
 * Function name:    create_weapon()
 * Description  :    Creates the weapon.
 */
void
create_weapon()
{
    set_name("staff");
    set_short("shepards staff");
    set_pshort("shepards staves");
    set_long("It is a shepards staff, usefull for herding sheeps and " +
	     "cattle.\n");
    set_adj("shepard");

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_POLEARM);
    set_dt(W_IMPALE|W_SLASH);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(30) - 18 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM) + 
	random(60) - 30 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
