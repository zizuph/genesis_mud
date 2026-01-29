/*
 *  IGARD_ARM + "i_largehalberd.c"
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
    set_name("halberd");
    add_name("polearm");
    set_pname("halberds");
    add_pname("polearms");
    set_adj("slender");
    add_adj("steel");
    set_short("slender steel halberd");
    set_pshort("slender steel halberds");
    set_long("From the marks on its shaft, this halberd was forged in the "
        + "smithies of Isengard. A single piece of fine steel has been lashed "
        + "through the long oaken shaft, such that on one side is a long curving "
        + "blade for cutting and on the other a long spike for gouging. On "
        + "its proximal end is another long spike for lancing an opponent "
        + "caught off guard.\n");
    add_item(({"shaft", "mark", "marks"}), "The shaft on the slender steel "
        + "halberd bears the mark of the White Hand of Isengard.\n");
    set_default_weapon(28, 40,W_POLEARM,W_IMPALE|W_SLASH,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28, 40)+random(400)-200);
    add_prop(OBJ_I_WEIGHT,
	       (F_WEIGHT_DEFAULT_WEAPON(28, W_POLEARM) + random(500) + 1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
