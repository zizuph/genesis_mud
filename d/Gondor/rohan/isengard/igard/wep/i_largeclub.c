/*
 *  IGARD_ARM + "i_largeclub.c"
 *  Standard Isengard Club
 *    Modified from: /d/Gondor/common/wep/orcclub.c
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
    set_name("club");
    set_pname("clubs");
    set_short("spiked iron club");
    set_pshort("spiked iron clubs");
    set_adj("iron");
    add_adj("spiked");
    add_adj("heavy");
    set_long("This spiked iron club was forged in the smithies of Isengard. "
        + "Unlike the crude weapons of lesser orcs, this club was engineered "
        + "for balance and precision. In skilled hands it will deliver bone-"
        + "crushing blows. Its iron spikes ensure that substantial damage is "
        + "also delivered to skin, muscle and internal organs.\n");
    add_item(({"spike", "spikes", "iron spike", "iron spikes"}), "Long "
        + "spikes of well-oiled iron project from the club. Some of them "
        + "are stained with blood.\n");
    set_default_weapon(27,38,W_CLUB,W_IMPALE|W_BLUDGEON,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(31,37)+random(350)-175);
    add_prop(OBJ_I_WEIGHT,
	       (F_WEIGHT_DEFAULT_WEAPON(31, W_CLUB) + random(1000) + 400));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
