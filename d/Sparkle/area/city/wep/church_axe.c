/*
 *  /d/Sparkle/area/city/wep/church_axe.c
 *
 *  The default axe given to new players who pray at the church in
 *  Sparkle.
 *
 *  given at: /d/Genesis/start/human/town/church.c
 *
 *  Created May 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/wep/church_weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>


/* prototypes */
public void        create_church_weapon();


/*
 * Function name:        create_church_weapon
 * Description  :        dummy constructor function for inheriting
 *                       objects to redefine
 */
public void
create_church_weapon()
{
    set_name("axe");

    set_short("mistform axe");
    set_long("This axe is light as a feather, yet looks as if it could"
      + " still do quite a bit of damage if anyone wanted to"
      + " <wield> it and try to <kill> something.\n");

    set_default_weapon(10, 10, W_AXE, W_SLASH, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(10, W_AXE) / 4);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
} /* create_church_weapon */

