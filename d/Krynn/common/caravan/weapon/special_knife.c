
/*
 *  Filename:       special_knife.c
 *  Description:    A special knife that makes more damage than usual,
 *                  but hits very bad.
 *
 *  Copyright (c) Dec. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("knife");
    set_adj(({"tiny", "sharp"}));
    set_short("tiny sharp knife");
    set_pshort("tiny sharp knives");
    set_long("The tiny knife is very sharp, but the size of it makes " +
        "it look quite redicolous. It is is far too small to hit with " +
        "but a weird black glow is emitting from it.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 35, "enchantment" }) );
    add_prop(OBJ_S_WIZINFO, "The knife was created by an assassin.\n" +
        "Knowing he would only have one strike, he got the knife " +
        "enchanted with a powerful penetration magic, making the " +
        "knife hit extremely hard.\n");
    add_prop(MAGIC_AM_ID_INFO, (
        "The knife was created by one of the dark assassins who was " +
        "send by Takhisis troops, to take out one of the knighthood " +
        "leaders. It was bestowed with a powerful magic to make it " +
        "slay the victim in a single strike, however the knife is " +
        "so short that one needs to be very close to ones victim.\n", 30) );

    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    set_hit(10);
    set_pen(40);
    set_wt(W_KNIFE);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 40));
}
