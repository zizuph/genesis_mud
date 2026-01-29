/*
 *  NCAMP + "newbie_sword.c"
 *    Last modified by Alto, 01 October 2001
 *
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
    set_name("shortsword");
    add_name("sword");
    add_name("_ncamp_weapon_");
    set_pname("shortswords");
    add_pname("swords");
    set_adj("rusting");
    add_adj("iron");
    set_short("rusting iron shortsword");
    set_pshort("rusting iron shortswords");
    set_long("This shortsword seems sturdy enough, although you notice several rusting spots along "
        + "its iron blade. There is no ornamentation on blade or hilt, suggesting this sword once "
        + "belonged to a common soldier.\n");
    set_default_weapon(18, 12, W_SWORD, W_SLASH | W_IMPALE,  W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(12, W_SWORD) + random(101));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18, 12) + random(37));
}
