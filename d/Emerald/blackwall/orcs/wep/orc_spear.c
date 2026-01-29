/* A weapon favored by orcs. (~Emerald/blackwall/orcs)
   Code (c) 2000 Damian Horton - BKA Casimir.
*/

#pragma strict_types
#pragma save_binary

inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include <formulas.h>
#include <ss_types.h>

void create_weapon()
{
  set_name("spear");
  add_name("polearm");
  set_short("broad-headed spear");
  set_long("A broad thrusting blade mounted atop a 2 metre long wooden "+
	   "shaft.\n");
  set_adj("broad-headed");
  add_adj("broad");

  set_hit(22);
  set_pen(20);

  likely_dull = 12;
  likely_corr = 12;
  likely_break = 26;
  set_dull(random(5)); // need not be in prime

  set_wt(W_POLEARM);
  set_dt(W_IMPALE);
  set_hands(W_BOTH); 
  add_prop(OBJ_I_WEIGHT, 2800);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(22, 20) - random(60));
  add_prop(OBJ_I_VOLUME, 2800);
}       












