/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2001 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above, accepting this as an exception to any
 * policies to the contrary.
 */
/* Originally RoN NPC boots, author uncertain, modified for
 * use in Thornlin by Auberon, Feb. 2001
 */
#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("boots");
    add_name("armour");
    set_adj("brown");
    set_adj("leather");
    set_adj("supple");
    set_short("pair of supple leather boots");
    set_long("These brown boots are well made of soft leather, and seem like " +
      "they would be comfortable even on very long journeys.\n");
    set_default_armour(7, A_ANKLES| A_FEET, (({ -1, 1, 0})), 0);
    add_prop(OBJ_I_WEIGHT, 360);   /* 260 */
    add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(20));
}
