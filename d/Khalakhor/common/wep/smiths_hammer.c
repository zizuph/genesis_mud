/*
 * smiths_hammer.c
 *
 * A heavy smiths hammer. Not really designed for combat, but
 * heavy enough to be worth avoiding being hit in the head with ;)
 * 
 * Khail - August 15, 1997
 */
#pragma strict_types

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define HIT 15
#define PEN 28

inherit "/d/Khalakhor/std/weapon";
inherit "/lib/keep";

public void
create_khalakhor_weapon()
{
    set_name("hammer");
    set_adj("heavy");
   set_short("smiths hammer");
   set_pshort("smiths hammers");
    add_adj("smiths");
    set_long("This hammer is one favoured by many smiths, " +
        "not much to look at, but nicely weighted and very " +
        "sturdy.\n");

    set_wt(W_CLUB);
    set_hands(W_ANYH);
    set_dt(W_BLUDGEON);
    set_hit(HIT);
    set_pen(PEN);
    set_keep(1);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
