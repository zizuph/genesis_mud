/*
 *  IGARD_ARM + "i_longbow.c"
 *  Standard Isengard Club
 *    Modified from: /d/Gondor/morgul/obj/halberd.c
 *    Olorin, July 1993
 *    Last modified by Alto, 11 October 2001
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
#include "../igard_defs.h"

public void
create_weapon() 
{
    set_name("longbow");
    add_name(({"polearm", "bow", "_igard_longbow"}));
    set_pname("longbows");
    add_pname("bows");
    set_adj("sturdy");
    add_adj("ash");
    set_short("sturdy ash longbow");
    set_pshort("sturdy ash longbows");
    set_long("This is a long tapering cut of ash wood, bent through its "
        + "middle in a shallow yet graceful curve. Tied to each end of the "
        + "bow is a sturdy length of gut. In the hands of an experienced "
        + "archer, the longbow is an extremely deadly weapon. In the hands "
        + "of common soldiers, however, it still makes a formidable "
        + "polearm.\n");
    set_default_weapon(28, 40,W_POLEARM,W_IMPALE|W_BLUDGEON,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28, 40)+random(400)-200);
    add_prop(OBJ_I_WEIGHT,
	       (F_WEIGHT_DEFAULT_WEAPON(28, W_POLEARM) + random(500) + 1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
