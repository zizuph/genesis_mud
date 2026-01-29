/*
 * /d/Gondor/common/dwarf_guild/wep/s_poker.c
 *
 * This poker is wielded by the weaponsmith in the dwarven race guild.
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

#define WEAPON_HIT 23
#define WEAPON_PEN 29

void
create_weapon()
{
    set_name("poker");

    set_pname("pokers");

    set_adj("iron");
    add_adj("black");
    add_adj( ({ "smith", "smith'" }) );

    set_short("black poker");
    set_pshort("black pokers");

    set_long(BSN("It is a black poker, made of iron. It is used to poke " +
        "fire. The smith uses it in his smithy to poke the forge."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_POLEARM);
    set_dt( (W_IMPALE | W_SLASH) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME,  700);
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