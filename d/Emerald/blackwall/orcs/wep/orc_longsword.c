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
  set_name("longsword");
  add_name("sword");
  set_short("dark steel longsword");
  set_long("A longsword forged out of a blackened steel. It balances "+
	   "well and seems to be a quality weapon all-round.\n");
  set_adj("dark");
  add_adj("steel");
 
  set_hit(31);
  set_pen(27);

  likely_dull = 12;
  likely_corr = 12;
  likely_break = 12;
  set_dull(random(4)); // need not be in prime

  set_wt(W_SWORD);
  set_dt(W_SLASH | W_IMPALE);
  set_hands(W_ANYH); 
  add_prop(OBJ_I_WEIGHT, 5800);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(31, 27) - random(50));
  add_prop(OBJ_I_VOLUME, 2500);
}       












