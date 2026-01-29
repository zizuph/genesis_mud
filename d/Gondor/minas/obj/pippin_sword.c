/*
 * /d/Gondor/common/wep/pippin_sword.c
 *
 * Shortsword for Peregrin Took
 *
 * Alto 20 April 2001
 *
 */

#pragma strict_types

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

public void
create_weapon()
{
    set_name(({"shortsword", "sword", "weapon"}));
    set_pname("shortswords");
    add_pname("swords");
    set_short("long leaf-shaped shortsword");
    set_pshort("long leaf-shaped shortswords");
    set_long("This is actually a dagger made by Men of the north "
        + "Kingdom long ago, but it makes for an excellent shortsword "
        + "in the hands of a hobbit. It is long, leaf-shaped and keen, "
        + "of marvellous workmanship, damasked with serpent-forms in "
        + "red and gold.\n");
    set_adj("long");
    add_adj("leaf-shaped");
    add_adj("short");
    set_default_weapon(20,22,W_SWORD,W_SLASH,W_RIGHT,0);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,1200);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(20,22)+random(400)-100);
}

