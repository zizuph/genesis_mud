/*
 * breeches.c
 *
 * Common leather breeches, made out of deerskin.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";
inherit "/lib/keep";

public void
create_armour()
{
    set_name("pair of breeches");
    add_name("pair of pants");
    add_name("pair of trews");
    add_name("breeches");
    add_name("trews");
    add_name("pants");
    set_pname("pairs of breeches");
    add_pname("pairs of pants");
    add_pname("pairs of trews");
    add_pname("breeches");
    add_pname("trews");
    add_pname("pants");
    set_short("pair of breeches");
    set_pshort("pairs of breeches");
    set_long("These breeches are made simply enough from " +
        "deerskin, and ruggedly stitched together. They " +
        "don't offer a lot in the way of protection, but " +
        "they are quite light and comfortable.\n");
    set_at(A_LEGS);
    set_ac(10);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(OBJ_I_VOLUME, 2000);
}

