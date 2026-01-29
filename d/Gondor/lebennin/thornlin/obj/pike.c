/*
 * This code is copyright (c) 2000 by Scott A. Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott Hardy has seen the 1991 document of Genesis' called 'legal',
 * and he does not forfeit any of his intellectual property rights
 * as that document supposes he would.  He is the sole and
 * complete owner of this code, which as of Jan. 2001 he is 
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of his code, Genesis acknowledges and agrees
 * to all of the above.
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
# include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"pike"}));
    set_short("pike");
    set_pshort("pikes");
    set_long("This polearm resembles the spears used by the Thornlin militia, " +
      "but it is around the same length as an equestrian lance.  The shaft " +
      "is fairly thick, and made of tough and fine-grained hardwood.  " +
      "The head itself is narrow and very pointed, designed only for piercing.  " +
      "The steel of the head covers the shaft for over 2 feet, and " +
      "another foot or more is covered with steel strips to protect the " +
      "shaft from sword strokes.  The Thornlin Armoury's stamp is on the head.\n");

    set_default_weapon(40,40,W_POLEARM,W_IMPALE,W_BOTH, 0);

    set_keep(1);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40,40) + random(100) - 100);
    add_prop(OBJ_I_WEIGHT,
      (F_WEIGHT_DEFAULT_WEAPON(40, W_POLEARM)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 8);
}
