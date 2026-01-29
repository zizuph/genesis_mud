/*
 * g_axe.c
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
    set_name("axe");
    set_short("timbermans axe");
    set_pshort("timbermans axes");
    set_long("It's an old Gondorian timbermans axe. The grip is plain, " +
	"about one foot and a half long, with a plain head on it. The " +
	"axe head is rough and heavy, but stil quite light and plain, " +
	" and along the edge there are some marks. It is usefull for " +
	"chopping wood.\n");
    set_adj("timbermans");

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(30) - 15 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE) + 
        random(60) - 30 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
