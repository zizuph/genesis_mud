/*
 * /d/Gondor/morgul/obj/normalplate.c
 * Stern, 21-apr-2000, this platemail is a non magic platemail
 *        for some morgul npcs that used to have a magical plate.
 */
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour() 
{
  set_name("platemail");
  add_name("mail");
  add_name("_ithil_armour");
  set_adj(({"plate","dark","steel","mat", "morgul","plain"}));
  set_short("mat dark platemail");
  set_pshort("mat dark platemails");
  set_long(BSN(
        "A plain mat dark platemail with on the breast piece a picture " +
        "of the Moon disfigured with a ghastly face of death."));

  set_default_armour(40,A_BODY,({0, 0, 0}),0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(40)+random(800)-300);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR( 40, A_BODY)+random(600)-250);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
