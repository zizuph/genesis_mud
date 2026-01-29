/*
 * hunting_knife.c
 * This is Thanduin's hunting knife
 * long, double-edged impaling knife
 * - Alaron Feb 1998
 */

#include "../dirheader.h"
#include "../coramar.h"
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>

inherit "/std/weapon";

void
create_weapon()
{
    set_name("knife");
    set_adj("hunting");
    add_adj("sharp");
    set_short("sharp hunting knife");

    set_long("This long, sharp hunting knife has been extremely well "+
             "maintained. The sharpness and clean shine of the blade "+
             "indicates that its previous owner cleaned and sharpened "+
             "it daily. This looks to be an extremely good weapon "+
             "for hunting small game.\n");

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE );

    set_hit(16); set_pen(14);

    add_prop(OBJ_I_WEIGHT,3600);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,11));

    set_hands(W_ANYH);
}
