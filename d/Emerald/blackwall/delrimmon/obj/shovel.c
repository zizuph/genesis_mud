/*
 *  /d/Emerald/blackwall/delrimmon/obj/shovel.c
 *
 *  This shovel was left behind when the troops positioned at
 *  Del Rimmon abandoned their post after the tragedy of the
 *  western plains. It is still servicable as a digging tool.
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/obj/shovel";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_weapon();


/*
 * Function name:        create_weapon
 * Description  :        set up the shovel
 */
public void
create_weapon()
{
  set_name("shovel");
  set_short("shovel");
    add_adj("metal");  /* added by Gorboth, July 2007 */
  set_long("This shovel looks positively ancient. Its dull blade is"
    + " supported by a long wooden handle. One could still dig with"
    + " it, most likely.\n");

  set_default_weapon(15,10,W_POLEARM,W_SLASH|W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_VOLUME,3000);
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15,10)+150-random(50));
} /* create weapon */
