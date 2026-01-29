/*
 * esword.c
 * Elven longsword
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
  set_name(({"sword","longsword","elven"}));
  set_pname(({"swords","longswords","elven"}));
  set_short("Elven longsword");
  set_pshort("Elven longswords");
  set_long(BS("It is an elven longsword, you wonder whether it got" +
	      " some magic enhancements. \n"));

  /* Set 'to hit' and 'penetration' values */
  set_hit(27);
  set_pen(27);

  /* Set weapon and damage type */
  set_wt(W_SWORD);
  set_dt(W_SLASH);

  /* Set physical attributes. */
  add_prop(OBJ_I_WEIGHT, 15000);
  add_prop(OBJ_I_VOLUME,  5000);
}

string query_recover()
{
  return "/d/Rhovanion/common/weapons/esword.c" + ":" + query_wep_recover();
}

void init_recover(string arg)
{
  init_wep_recover(arg);
}
