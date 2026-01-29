/*
 * f_schyte.c
 * By Skippern December 2000
 *
 * To be found on some of the farmers in Erech.
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
    set_name("schyte");
    set_short("sharp schyte");
    set_pshort("sharp schytes");
    set_long("It is a sharp schyte, usefull for cutting the crops.\n");
    set_adj("sharp");

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
