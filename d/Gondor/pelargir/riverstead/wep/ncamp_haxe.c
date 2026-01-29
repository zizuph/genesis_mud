/*
 *  NCAMP_ARM + "ncamp_haxe.c"
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
    set_name("hatchet");
    add_name("axe");
    set_pname("hatchets");
    add_pname("axes");
    set_adj("sturdy");
    add_adj("oak-handled");
    set_short("sturdy oak-handled hatchet");
    set_pshort("sturdy oak-handled hatchets");
    set_long("This rather large hatchet has seen much use, but its blade has been "
        + "carefully tended and is quite sharp. Although it was obviously designed "
        + "for chopping firewood, it would split a skull just as easily.\n");
    set_default_weapon(24,30,W_AXE,W_SLASH|W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(24,30)+random(300)-150);
    add_prop(OBJ_I_WEIGHT,
        (F_WEIGHT_DEFAULT_WEAPON(24, W_AXE) + random(400) + 400));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
