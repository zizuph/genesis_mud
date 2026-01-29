/*
 *  /d/Emerald/common/guild/aod/wep/boulder_knife.c
 *
 *  The knife that is created when an Ogre busts a boulder. It sucks,
 *  but maybe Ogres need a knife now and then. This is the RARE instance
 *  of a two-handed knife.
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_weapon;

/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name("knife");
    add_name( ({ "shard", "dagger", "chip-knife" }) );
    set_short("enormous chip-knife");
    add_adj( ({ "enormous", "chip" }) );

    set_long("When two rocks are smashed together, a few of the shards"
      + " that result are often thin enough to serve as a cutting"
      + " device. In this case, the rock must have been a boulder,"
      + " because this thing is about three feet long! Even if you"
      + " were big enough to wield this thing in one hand, it would"
      + " probably be the world's worst (and most cumbersome) knife.\n");

    set_hit(10);
    set_pen(12);
    set_pm(({ 0, 1, 0 }));
    add_prop(OBJ_I_WEIGHT, 4000); 
    add_prop(OBJ_I_VOLUME, 2500);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_BOTH); /* yeah, a two-handed knife! */

    set_keep(1);
} /* create_weapon */
