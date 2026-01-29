/*
 *  IGARD_ARM + "i_axe.c"
 *  Standard Isengard Axe
 *    Modified from: /d/Gondor/morgul/obj/battleaxe.c
 *	   Olorin, Nov 1992
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
    set_name("axe");
    set_pname("axes");
    set_short("crude rusty axe");
    set_pshort("crude rusty axes");
    set_adj("crude");
    add_adj("rusty");
    set_long("This crude rusty axe was forged in the smithies of Isengard. "
        + "Lashed to a long oaken handle, the blade is a single piece of "
        + "iron cut square. The outer edge is rather sharp, although notched "
        + "in several places. The blade is extremely rusty, but looks like "
        + "it could still do some damage.\n");
  set_default_weapon(24,30,W_AXE,W_SLASH|W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(24,30)+random(300)-150);
  add_prop(OBJ_I_WEIGHT,
     	(F_WEIGHT_DEFAULT_WEAPON(24, W_AXE) + random(400) + 400));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
