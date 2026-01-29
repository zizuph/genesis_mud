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
  set_name("battleaxe");
  add_name("axe");
  set_short("large steel battleaxe");
  set_long("A large and heavy axe designed to be wielded with only one "+
	   "hand. The blackened steel blade is broad leaving no doubt "+
	   "that this is weapon of war.\n");
  set_adj("large");
  add_adj("steel");
 
  set_hit(23);
  set_pen(32);

  likely_dull = 12;
  likely_corr = 12;
  likely_break = 12;
  set_dull(random(4)); // need not be in prime

  set_wt(W_AXE);
  set_dt(W_SLASH);
  set_hands(W_ANYH); 
  add_prop(OBJ_I_WEIGHT, 8800);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(23, 32) - 25 - random(100));
  add_prop(OBJ_I_VOLUME, 2600);
}       












