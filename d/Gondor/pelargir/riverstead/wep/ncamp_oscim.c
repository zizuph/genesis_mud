/*
 *  NCAMP_ARM + "ncamp_oscim.c"
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
    set_name("scimitar");
    add_name("sword");
    set_pname("scimitars");
    add_pname("swords");
    set_adj("crude");
    set_short("crude scimitar");
    set_pshort("crude scimitars");
    set_long("This weapon shows all the signs of mass production. It has no "
        + "ornamentation or engraving, its edges are rough and unpolished, and "
        + "its handle is broad and seems to be untailored to any specific hand. The "
        + "blade is sharp nonetheless. This weapon could do some damage.\n");
    set_default_weapon(18, 12, W_SWORD, W_SLASH | W_IMPALE,  W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(12, W_SWORD) + random(101));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18, 12) + random(37));
}
