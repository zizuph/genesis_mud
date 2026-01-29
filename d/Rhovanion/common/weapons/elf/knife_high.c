/*
 * edagger.c
 * Elven dagger
 * coded by Daneel november 1993
 *
 */

#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Rhovanion/defs.h"

void
create_weapon()
{
  /* Set name, short and long description */
  set_name("dagger");
  set_pname("daggers");
  set_short("Elven dagger");
  set_pshort("Elven daggers");
  set_long(BS("It is a fine elven dagger. \n"));

  /* Set 'to hit' and 'penetration' values */
  set_hit(13);
  set_pen(15);

  /* Set weapon and damage type */
  set_wt(W_KNIFE);
  set_dt(W_IMPALE);

  /* Set physical attributes. */
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 2000);
}

string query_recover()
{
  return "/d/Rhovanion/common/weapons/edagger.c" + ":" + query_wep_recover();
}

void init_recover(string arg)
{
  init_wep_recover(arg);
}
