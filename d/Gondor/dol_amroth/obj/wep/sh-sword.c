/* -*- Mode: C -*-
 *
 * sh-sword.c
 * By Skippern 20(c)02
 *
 */
inherit "/std/weapon";

#include <wa_types.h>        /* Contains weapon-related definitions */
#include <formulas.h>        /* Conaitns formulas for weight, value etc. */
#include <stdproperties.h>   /* OBJ_I_VALUE and similar properties */

#define HIT 15
#define PEN 17

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
    set_short("sharp short sword");
    set_pshort("sharp short swords");
    set_long("This short sword looks very sharp.\n");
    set_adj("sharp");
    add_adj("short");

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(40) - 20 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD) + 
	random(70) - 45 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
