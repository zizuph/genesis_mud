/*
 * /d/Gondor/common/dwarf_guild/wep/s_hammer.c
 *
 * This hammer is wielded by the weaponsmith in the dwarven race guild.
 *
 * /Mercade 29 july 1993
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 29
#define WEAPON_PEN 23

void
create_weapon()
{
    set_name("hammer");

    set_pname("hammers");

    set_adj("iron");
    add_adj( ({ "smith", "smith'" }) );

    set_short("iron smith hammer");
    set_pshort("iron smith hammers");

    set_long(BSN("This hammer is made for a smith. It is made of iron."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
        random(151) - 75));
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}