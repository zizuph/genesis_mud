/* Alternate weapon for Morognor, should he not have his savage
   black axe.

   Code (c) 2000 Damian Horton - BKA Casimir.
*/

#pragma strict_types
#pragma save_binary

inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include <formulas.h>

void create_weapon()
{
  set_name("axe");
  set_short("heavy black axe");
  set_long("A large and heavy axe cast entirely out of some kind of "+
	   "blackened steel. The axe head is unusually broad "+
	   "for that of a one-handed war axe. The axe is well balanced "+
	   "and can be surprisingly quickly recovered from a missed "+
	   "blow, provided the wielder is fairly strong.\n"); 

  set_adj("heavy");
  add_adj("black");

  set_hit(30);
  set_pen(34);

  likely_dull = 8;
  likely_corr = 6;
  likely_break = 4;

  set_wt(W_AXE);
  set_dt(W_SLASH | W_BLUDGEON);
  set_hands(W_ANYH); 
  add_prop(OBJ_I_WEIGHT, 9600);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30, 34) + random(200));
  add_prop(OBJ_I_VOLUME, 2800); 
}
       











