/*
 * g_tsword.c
 * By Skippern
 * February 2001
 *
 * A toy sword for the ghost children to play with.
 */
inherit "/std/weapon";

#include <wa_types.h>        /* Contains weapon-related definitions */
#include <formulas.h>        /* Conaitns formulas for weight, value etc. */
#include <stdproperties.h>   /* OBJ_I_VALUE and similar properties */

#define HIT 5
#define PEN 3

/* Prototypes */
void               create_weapon();

/*
 * Function name:    create_weapon()
 * Description  :    Creates the weapon.
 */
void
create_weapon()
{
    set_name("sword");
    set_short("small toy sword");
    set_pshort("small toy swords");
    set_long("It's a small toy sword, made out of a piece of wood " +
	     "cut into the shape of a sword. It is rather small, but " +
	     "guess it would fit fine into the hand of a child. " +
	"\n");
    set_adj( ({ "small", "toy" }) );

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_SWORD);
    set_dt(W_BLUDGEON);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, 10 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD) -
	random(70) );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
}

