/* -*- Mode: C -*-
 *
 * w_tail.c
 *
 * By Skippern 20(c)04
 *
 */
inherit "/std/weapon";

#include <wa_types.h>        /* Contains weapon-related definitions */
#include <formulas.h>        /* Conaitns formulas for weight, value etc. */
#include <stdproperties.h>   /* OBJ_I_VALUE and similar properties */

#define HIT 10
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
    set_name("mace");
    set_short("black spiked mace");
    set_pshort("black spiked maces");
    set_long("This black mace looks like it have been torn out of a statue. " +
	     "The spikes on the mace's head seems to be able to do some " +
	     "damage.\n");
    set_adj("black");
    add_adj("spiked");

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON | W_IMPALE);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(40) - 20 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD) + 
	random(70) - 45 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
