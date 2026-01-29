/*
 * g_hammer.c
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

#define HIT 25
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
    set_name("hammer");
    set_short("blacksmiths hammer");
    set_pshort("blacksmiths hammers");
    set_long("It's a blacksmiths hammer. It has forged many weapons in " +
	"ages long ago. The shaft is 3 feet long and you need both hands " +
	"get a good grip on it. The head is very crude and quite heavy. You " +
	"beleave it would do a lot of damage to be hit by it.\n");
    set_adj("blacksmiths");

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(30) - 15 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB) + 
        random(60) - 30 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
