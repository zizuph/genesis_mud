/* 
 *      /d/Gondor/morgul/obj/orcmace.c
 *      A morning star for Minas Morgul
 *
 *      Copyright (c) 1993, 1994, 1997 by Christian Markus
 *
 *      Olorin, July 1993
 *      Modification log: 
 *      Olorin, July 1994
 *      March 1997, Olorin: General revision.
 */
#pragma strict_types

inherit "/std/weapon.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_weapon() 
{
    set_name(({"morning star","star","mace","weapon"}));
    set_short("morning star");
    set_pshort("morning stars");
    set_long(BSN("A heavy spiked iron ball connected to a metal handle " +
        "by an iron chain. The spikes of the ball are of varying lengths, " +
        "between two and five inches long, and exceedingly sharp. Swinging " +
        "the ball at the end of the chain, an experienced fighter can wreak " +
        "havoc with this club-like weapon. The handle of the morning star " +
        "shows the picture of a Moon disfigured with a ghastly face of death."));
    set_adj(({"orc", "spiked", "heavy"}));
    set_default_weapon(27,38,W_CLUB,W_IMPALE|W_BLUDGEON,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(31,37)+random(350)-175);
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(31, W_CLUB) + random(1000) + 400));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

