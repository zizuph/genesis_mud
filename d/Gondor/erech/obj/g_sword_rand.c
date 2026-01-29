/*
 * g_sword_rand.c
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
#include <macros.h>          /* For macros */

#define HIT 15
#define PEN 17

/* Prototypes */
void               create_weapon();
void               query_recover();
void               init_recover(string arg);

/*
 * Function name:    create_weapon()
 * Description  :    Creates the weapon.
 */
void
create_weapon()
{
    set_name("sword");
    set_short("single-bladed sword");
    set_pshort("single-bladed swords");
    set_long("It's a single-bladed sword, used by the Oathbreakers long " +
        "ago. The hilt feels good, and the guards looks strong. The blade " +
	"is blackened and the edge have some marks on it. " +
	"\n");
    set_adj("single-bladed");

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(one_of_list(({W_ANYH, W_LEFT, W_RIGHT})));

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(40) - 20 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD) + 
	random(70) - 45 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}

/*
 * Function name:    query_recover()
 * Description  :    Tests the weapon for wich hand(s) it is wielded in
 *                   and `saves' it for armageddon, so that it can be
 *                   recovered wieldable in the same hand as it was before,
 *                   and not magically changed.
 */
void
query_recover()
{
    return MASTER + ":" + query_hands();
}

/*
 * Function name:    init_recover(string arg)
 * Description  :    Initializes the recovery of the weapon and ensures it
 *                   is the same as before armageddon.
 * Arguments    :    What set_hand value is valid.
 *                   atoi = String To Integer. We want to use the integer, not
 *                   the string.
 */
void
init_recover(string arg)
{
    set_hands(atoi(arg));
}
