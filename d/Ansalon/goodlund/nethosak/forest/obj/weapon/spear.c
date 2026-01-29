/* 
 * Coded by Elmore
 * Updated October 11th 2005 by Navarre
 * Change: 1) Changed weapon to be wielded in one hand, the left hand.
 *         2) Added a little speed to the wielder, due to the challenge of
 *            the guardian, the ancient black dragon.
 *         3) Added Wiz_Info, for stat command.
 *         4) Added the spear to /d/Krynn/info/MAGIC
 *         
 * 2021-01-02 - Cotillion
 * - Removed random from hit/pen
 * - Added weight so it doesn't float.
 */ 

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>

#define SPEED 37

void
create_weapon()
{

   set_name("spear");
   add_name("polearm");
   set_adj("tempered");
   add_adj("staff");

   set_long("This is a long spear that has been made out of a large bone. "+
            "A thin jagged spearhead made out of tempered steel decorates "+
            "the tip of the handle. The cold bone handle has five imprints "+
            "for the fingers of the left hand, providing with a better "+
            "grip in combat. The improved grip and the light weight of the bone, "+
            "makes this spear quite efficient in battle.\n");

   set_short("tempered spear");

   set_default_weapon(35, 48, W_POLEARM, W_SLASH | W_IMPALE, W_LEFT);

   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_WEIGHT, 4070);        

   add_prop(OBJ_I_VALUE, 1232);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC, ({ 3335, "natural"}));
   add_prop(MAGIC_AM_ID_INFO, ({"The weight of this weapon makes it "+
                                "possible to swing it slightly faster "+
                                "than regular weapons.\n", 85}));
   add_prop(OBJ_S_WIZINFO, "This weapon offers the wielder an "+
        "improvement in speed. It has no alignment "+
        "requirement. The weapon is well guarded by Onyx, the "+
        "ancient black dragon in Mithas.");
   set_likely_dull(1);
   set_likely_corr(3);
   set_likely_break(3);
   set_wf(this_object());
}


mixed
wield(object what)
{
  wielder->change_prop(LIVE_I_QUICKNESS,
                       wielder->query_prop(LIVE_I_QUICKNESS) + SPEED);
  return 0;
}

mixed
unwield(object what)
{
  wielder->change_prop(LIVE_I_QUICKNESS,
                         wielder->query_prop(LIVE_I_QUICKNESS) - SPEED);
  return 0;
}



