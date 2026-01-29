/*
 *  NCAMP_ARM + "ncamp_hclub.c"
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
    set_name("cudgel");
    set_pname("cudgel");
    add_name("club");
    add_pname("clubs");
    set_adj("lead-tipped");
    set_short("lead-tipped cudgel");
    set_pshort("lead-tipped cudgels");
    set_long("The business end of this wooden club has been dipped in lead, "
        + "which renders it particularly "
        + "lethal in the hands of someone who knows how to swing it.\n");
    set_default_weapon(22, 22, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(22, 22) + random(200));
    add_prop(OBJ_I_WEIGHT, 
        (F_WEIGHT_DEFAULT_WEAPON(22, W_CLUB) + 1000 + random(1001)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
