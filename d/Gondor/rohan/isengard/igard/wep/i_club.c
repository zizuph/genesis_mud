/*
 *  IGARD_ARM + "i_club.c"
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
    set_short("spiked wooden club");
    set_pshort("spiked wooden clubs");
    set_adj("wooden");
    add_adj("spiked");
    add_adj("crude");
    set_long("The spiked wooden club is made from a large limb torn "
        + "from a tree in Fangorn forest. It is a crude weapon, but the "
        + "iron spikes driven through the wood ensure that it will still "
        + "do some damage.\n");
    add_item(({"spike", "spikes", "iron spike", "iron spikes"}), "Long "
        + "spikes of rusted iron are driven through the club. Some of them "
        + "have been chipped and broken on unfortunate skulls.\n");
    set_default_weapon(22, 22, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(22, 22) + random(200));
    add_prop(OBJ_I_WEIGHT, 
       	(F_WEIGHT_DEFAULT_WEAPON(22, W_CLUB) + 1000 + random(1001)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(IGARD_WEAPON, 1);

}
