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
  set_name("voulge");
  add_name("polearm");
  set_short("vicious steel voulge");
  set_long("An elongated axe-like blade adorns the iron haft of this "+
	   "weapon. Though the shaft is distinctly iron, the blade is "+
	   "composed of a blackened steel.\n");
  set_adj("vicious");
  add_adj("steel");
  
  set_hit(27);
  set_pen(36);
 
  likely_dull = 10;
  likely_corr = 10;
  likely_break = 10;
  set_dull(random(4)); // need not be in prime

  set_wt(W_POLEARM);
  set_dt(W_SLASH);
  set_hands(W_BOTH); 
  add_prop(OBJ_I_WEIGHT, 12200);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(27, 36) - 50 + random(100));
  add_prop(OBJ_I_VOLUME, 6100);
}       












