/*
 *  NCAMP_ARM + "ncamp_oaxe.c"
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
    set_name("axe");
    add_name("battleaxe");
    set_pname("axes");
    add_pname("battleaxes");
    set_adj("crude");
    add_adj("heavy");
    set_short("crude heavy axe");
    set_pshort("crude heavy axes");
    set_long("This axe shows all the signs of mass production. It has no "
        + "ornamentation or engraving, its edges are rough and unpolished, and "
        + "its handle is broad and seems to be untailored to any specific hand. The "
        + "blade is sharp nonetheless. This weapon could do some damage.\n");
    set_default_weapon(24,30,W_AXE,W_SLASH|W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(24,30)+random(300)-150);
    add_prop(OBJ_I_WEIGHT,
        (F_WEIGHT_DEFAULT_WEAPON(24, W_AXE) + random(400) + 400));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
