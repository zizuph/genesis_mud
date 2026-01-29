/*
 * blade.c
 *
 * Custom sword for the Blademasters. Created from the conversion
 * of other swords in the game by a blademaster bladesmith.
 *
 * Khail - Mar 4/97
 */
#pragma strict_types

#include "defs.h"
#include <macros.h>

#define HIT 25
#define PEN 25

inherit "/d/Khalakhor/std/weapon";

public int
is_blademaster_equipment()
{
    return 1;
}

public void
create_khalakhor_weapon()
{
    set_name("sword");
    add_name(BLADEMASTER_SWORD_NAME);
    add_name("katana");
    set_short("sleek curved sword");
    set_pshort("sleek curved swords");
    set_adj("sleek");
    add_adj("curved");
    set_long("The sleek curving blade of the sword is quite " +
        "different from the usually heavy double-edged swords " +
        "used by many people. Its single edge is razor " +
        "sharp, and in the hands of a master it is a formidable " +
        "weapon. It obviously was not forged by a typical " +
        "bladesmith. The only mark on the blade is an etching " +
        "of a thistle near the hilt.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_SWORD);
    set_hands(W_BOTH);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, 7500 / 5);
}

public string
query_recover()
{
    return MASTER + ":" + query_hands() + "$$" + query_pen() +
        "$$" + query_hit() + "$$" + query_wep_recover();
}

public void
init_recover(string arg)
{
    int rec_hands,
        rec_pen,
        rec_hit;
    string extra;

    sscanf(arg,"%d$$%d$$%d$$%s",rec_hands,rec_pen,rec_hit,extra);
    set_hands(rec_hands);
    set_pen(rec_pen);
    set_hit(rec_hit);
    init_wep_recover(extra);
}
