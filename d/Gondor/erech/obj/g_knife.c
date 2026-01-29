/*
 * g_knife.c
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

#define HIT 9
#define PEN 10

/* Prototypes */
void               create_weapon();

/*
 * Function name:    create_weapon()
 * Description  :    Creates the weapon.
 */
void
create_weapon()
{
    set_name("knife");
    set_short("old knife");
    set_pshort("old knives");
    set_long("It's an old knife, used by the Oathbreakers long ago. The " +
	"hilt is made of wood, and the blade is straight and about eight " +
	"inches long.\n");
    set_adj("old");

    set_hit(HIT);
    set_pen(PEN);
    
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    
    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(30) - 15 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE) + 
        random(60) - 30 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
