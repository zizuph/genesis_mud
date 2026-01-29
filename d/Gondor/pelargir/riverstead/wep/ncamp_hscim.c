/*
 *  NCAMP_ARM + "ncamp_hscim.c"
 */

#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

public void
create_weapon() 
{
    set_name("longsword");
    add_name("sword");
    set_pname("longswords");
    add_pname("swords");
    set_adj("old");
    add_adj("blue-steel");
    set_short("old blue-steel longsword");
    set_pshort("old blue-steel longswords");
    set_long("The leather on its hilts is faded and cracked, but the blade has "
        + "been kept free of rust through long years of oiling and care. In days "
        + "of yesteryear, this longsword was used by a soldier of Gondor. Until "
        + "recently, however, it was nothing more than an heirloom of the farmers "
        + "who descended from that long-ago soldier.\n");
    set_default_weapon(18, 12, W_SWORD, W_SLASH | W_IMPALE,  W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(12, W_SWORD) + random(101));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18, 12) + random(37));
}
