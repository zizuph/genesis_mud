/*
 *  IGARD_ARM + "i_bar.c"
 *  Iron bar wielded by Isengard Prisoners
 *    Modified from: /d/Gondor/common/wep/orcclub.c
 *	   Olorin, Nov 1992
 *    Last modified by Alto, 14 November 2001
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
    set_name("bar");
    set_pname("bars");
    set_short("rusty iron bar");
    set_pshort("rusty iron bars");
    set_adj("rusty");
    add_adj("iron");
    set_long("This rusty bar of iron appears to have once been part "
        + "of a prison cell. It would make a reasonable club, especially "
        + "for a prisoner with no other weapons handy.\n");
    set_default_weapon(22, 22, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(22, 22) + random(200));
    add_prop(OBJ_I_WEIGHT, 
       	(F_WEIGHT_DEFAULT_WEAPON(22, W_CLUB) + 1000 + random(1001)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(IGARD_WEAPON, 1);

}
