/*  The travel-boots of the rangers of the north */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_armour()
{
  set_name("boots");
  add_name("armour");
  set_pname("pairs");
  set_adj("ranger");
  add_adj("leather");
  add_adj("high");
  set_short("pair of supple leather boots");
  set_pshort("pairs of supple leather boots");
  set_long("These high boots are nicely made of supple leather, but have seen\n"+
    "much wear, and are now caked with mud.\n");
  set_default_armour(8, A_LEGS | A_ANKLES | A_FEET, (({ -1, 1, 0})), 0);
  add_prop(OBJ_I_WEIGHT, 360);   /* 260 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(20));
  add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}




