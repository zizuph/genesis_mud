/*
 * poor_axe.c
 *
 * A fairly crude little handaxe, not much of a weapon, meant for smaller
 * humanoid npc's, like goblins up to statave 30.
 *
 * Khail - April 20/97
 */
#pragma strict_types

#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define HIT  15
#define PEN  15

inherit "/d/Khalakhor/std/weapon";

/*
 * Function name: create_khalakhor_weapon
 * Description  : Turns this object into a weapon.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_weapon()
{
    set_name("handaxe");
    add_name("axe");
    set_adj("crude");
    add_adj("little");
    set_short("crude little handaxe");
    set_long("The handaxe is fairly crude, little more than a " +
        "stick of wood for a handle with a wedge of steel " +
        "hammered onto the top. However, it has a good " +
        "edge, and is still capable of killing.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_AXE);
    set_hands(W_ANYH);
    set_dt(W_SLASH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);

}
