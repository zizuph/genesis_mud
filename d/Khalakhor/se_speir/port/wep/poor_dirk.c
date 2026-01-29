/*
 * poor_dirk.c
 *
 * A rather plain dirk, not much of a weapon, meant for smaller
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
    set_name("dirk");
    add_name("knife");
    set_adj("long");
    add_adj("sharp");
    set_short("long sharp dirk");
    set_long("The dirk is long and sharp, but fairly cheaply " +
        "made. The blade still has hammer marks on it, and the " +
        "normally carved grip looks like it's nothing more than " +
        "cloth wrapped around the blade tang. Not a great weapon, " +
        "but a weapon none the less.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_KNIFE);
    set_hands(W_ANYH);
    set_dt(W_SLASH | W_IMPALE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
