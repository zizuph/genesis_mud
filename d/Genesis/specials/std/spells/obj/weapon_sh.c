/*
 * Shadow Weapon Shadow
 *
 * This is an example shadow for the shadow_weapon spell.
 *
 * Created by Navarre, October 2010.
 */
#pragma strict_types

inherit "/std/shadow.c";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>


public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
        int dt, int phit, int dam, int hid)
{
  int rval = shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
  shadow_who->query_wielded()->catch_tell("You totally hit your enemy!\n");
  return rval;
}

