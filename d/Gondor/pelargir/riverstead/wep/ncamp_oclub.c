/*
 *  NCAMP_ARM + "ncamp_oclub.c"
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
    set_name("club");
    set_pname("clubs");
    set_adj("knobbed");
    add_adj("wooden");
    set_short("knobbed wooden club");
    set_pshort("knobbed wooden club");
    set_long("This club is really not much more than a large tree branch, ripped "
        + "down and whittled on one end to form a handle. Despite its crude and "
        + "unskilled production, it is heavy and could deal a fair amount of "
        + "damage to an enemy.\n");
    set_default_weapon(22, 22, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(22, 22) + random(200));
    add_prop(OBJ_I_WEIGHT, 
        (F_WEIGHT_DEFAULT_WEAPON(22, W_CLUB) + 1000 + random(1001)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
