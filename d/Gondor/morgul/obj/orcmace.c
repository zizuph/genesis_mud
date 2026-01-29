/* This is file /d/Gondor/morgul/obj/orcmace.c    */
/* A heavy orc mace                               */
/* Olorin, July 1993                              */
/*
 * Last Modification: Olorin, July 1994
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon() 
{
  set_name(({"mace","orc mace","weapon"}));
  set_short("heavy mace");
  set_pshort("maces");
  set_long(BSN("A heavy orc mace with sharp steel spikes. The handle " +
    "shows the picture of a Moon disfigured with a ghastly face of death."));
  set_adj(({"orc", "spiked", "heavy"}));
  set_default_weapon(30,22,W_CLUB,W_IMPALE|W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(23,25)+random(250)-125);
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(30, W_CLUB) + random(800) + 400));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

