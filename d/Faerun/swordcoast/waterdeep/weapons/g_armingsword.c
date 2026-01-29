/*
 * waterdeep/weapons/g_armingsword.c
 * An arming sword used by soldiers in the City Guard
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_WEP;

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define HIT          33
#define PEN          32

void
create_waterdeep_weapon()
{
    set_name(({ "sword", "arming-sword", "arming sword" }));
    set_adj(({ "knightly", "steel", "straight-bladed", "double-edged" }));

    set_short("steel arming sword");
    set_long(
        CAP(LANG_ADDART(short())) + ". It is a straight-bladed, double-edged "
        + "sword with a cross-shaped hilt. It is made to be wielded one-"
        + "handedly. It looks masterfully crafted.\n"
    );

    set_default_weapon(HIT, PEN, W_SWORD, W_IMPALE | W_SLASH, W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);

    add_prop(
        OBJ_S_WIZINFO,
        "This weapon is used by soldiers of the City Guard of Waterdeep.\n"
    );

    add_item(
        ({ "hilt", "haft", "shaft" }),
        "The hilt consists of a cross-guard, a leather-wrapped grip and a "
        + "pommel.\n"
    );

    add_item(
        ({ "grip", "leather-wrapped grip", "straps", "leather straps" }),
        "The grip is made to accomodate a single hand, and is wrapped tightly "
        + "in leather straps to increase comfort and friction.\n"
    );

    add_item(
        "cross-guard",
        "The cross-guard runs perpendicular to the blade, and curve slightly "
        + "outwards from the hilt at the ends.\n"
    );

    add_item(
        ({ "pommel" }),
        "An almond shaped pommel sits at the end of the grip. It prevents the "
        + "hand from sliding off during vigorous swings, as well as helps to "
        + "balance the sword.\n"
    );

    add_item(
        ({ "blade", "straight blade" }),
        "The blade is straight and double-edged and tapers to a sharp point at "
        + "the end. It is about 30 inches long.\n"
    );

    add_item(
        ({ "edge", "edges", "double-edge", "double-edges", "point" }),
        "The point and the edges of the " + short() + " are razor-sharp.\n"
    );
}
