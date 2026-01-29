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
  set_name("sword");
  add_name("broadsword");
  set_short("heavy black broadsword");
  set_long("A large and heavy broadsword cast out of some kind of "+
	   "blackened steel. It is large enough (and heavy enough) to be "+
	   "a two handed weapon yet the handle does not "+
	   "support the use of a second hand. Substantial strength would "+
	   "be required to use this heavy sword.\n"); 

  set_adj("heavy");
  add_adj("broad");
  add_adj("black");

  set_hit(25);
  set_pen(34);

  likely_dull = 8;
  likely_corr = 8;
  likely_break = 12;
  set_dull(random(3)); // need not be in prime

  set_wt(W_SWORD);
  set_dt(W_SLASH);
  set_hands(W_ANYH); 
  add_prop(OBJ_I_WEIGHT, 8800);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25, 34) - 50 + random(100));
  add_prop(OBJ_I_VOLUME, 2800);

  set_wf(this_object()); // this sword has a special wield function
}
       
mixed
wield(object to)
{
    if (this_player()->query_stat(SS_STR) < 60)
    {
	// player isn't strong enough to wield the sword
	return "You are not strong enough to effectively use the "
	    + short();
    }

    return 0; //wield as normal
}











