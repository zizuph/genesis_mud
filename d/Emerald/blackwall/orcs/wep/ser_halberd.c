/* A weapon used by one of the orc lieutenants. (~Emerald/blackwall/orcs)
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
  set_name("halberd");
  add_name("polearm");
  set_short("cruel serrated halberd");
  set_long("A vicious looking polearm consisting of a large axe blade "+
	   "and a spear point placed atop a pole. Both blade and point "+
	   "are viciously serrated so as to tear the flesh from anyone "+
	   "foolish enough to try to get near its wielder.\n");

  set_adj("cruel");
  add_adj("serrated");
 
  set_hit(31);
  set_pen(40);
  set_pm(({-5, 5, 0})); //impale, slash, bludgeon

  likely_dull = 12;
  likely_corr = 12;
  likely_break = 12;
  set_dull(random(3)); // need not be in prime

  set_wt(W_POLEARM);
  set_dt(W_SLASH | W_IMPALE);
  set_hands(W_BOTH); 
  add_prop(OBJ_I_WEIGHT, 11777);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(31, 40) + random(200));
  add_prop(OBJ_I_VOLUME, 6200);

  add_prop(OBJ_S_WIZINFO, "The serrated edges of this weapon increase "+
	   "the damage it does by 20%. This is not a magical property.\n");
}       

/* The serrated edges on this weapon increase damage dealt by 20%. */
int
did_hit(int aid, string hdesc, int phurt,
        object victim, int dt, int phit, int dam)
{ 
    victim->heal_hp(- (dam / 5)); // victim takes an extra 20% damage
   
    /* Done only every so often to prevent the weapon from spamming
       with an overabundance of messages. */
    if (random(5)) 
    {
	set_alarm(0.1, 0.0, &victim->catch_tell("The wounds left by "+
	    "the serrated halberd are especially painful.\n"));
    }
    
    return ::did_hit();
}










