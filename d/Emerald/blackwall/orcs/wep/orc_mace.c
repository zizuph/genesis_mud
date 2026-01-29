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
  set_name("mace");
  add_name("club");
  set_short("crude iron mace");
  set_long("A heavy, crudely flanged mass of metal atop an iron handle. "+
	   "Don't let its simple and crude nature deceive you, this "+
	   "is a perfectly good weapon.\n");
  set_adj("crude");
  add_adj("iron");

  set_hit(27);
  set_pen(23);

  likely_dull = 4;
  likely_corr = 12;
  likely_break = 12;
  set_dull(random(3)); // need not be in prime

  set_wt(W_CLUB);
  set_dt(W_IMPALE);
  set_hands(W_ANYH); 
  add_prop(OBJ_I_WEIGHT, 7400);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(27, 23) - 25 - random(100));
  add_prop(OBJ_I_VOLUME, 2250);
}       












