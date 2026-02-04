/* -*- C -*- */
/*
 * Based on the heave steel mace in Gondor
 * Sept. 97, changed the query_see_blood() in tell_watcher() to
 * the use of options instead. Mortricia.
 *
 * Modifications:
 *  Lilith July 2008
 *   -Changed to 45/45 from 42/42 
 *   -Changed to any-handed from two-handed (per Navarre's recommendation)
 * Lilith Sept 2008
 *   -Changed the damage from a call to do negative heal_hp to 
 *    a hit_me call with magic_dt 
 *   -Added magic res_cold check in the did_hit (undeads have partial res)
 * Petros May 2009
 *   -Fixed the way resistance checks are done
 *   -Set the weight properly to match the pen
 *   -Limited cold pen to F_PENMOD max, as that is equivalent to 100% caid.
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/d/Genesis/specials/resist";

#include <wa_types.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>
#include <filter_funs.h>

#define HIS(x)		((x)->query_possessive())
#define DAMAGE_LOG     FROST2_DIR+"log/wep_dam_log"

public string
query_recover() { return MASTER+":"+query_wep_recover(); }

public void
init_recover(string arg) { init_wep_recover(arg); }

public void
create_weapon ()
{
    set_name ("club");
    add_name ("weapon");
    set_adj (({"frost", "heavy"}));
    set_short ("heavy frost club");
    set_long ("This large club is ice-cold to the touch. It just might "+
            "be one of the coveted clubs used by " +
	      "the frost giants from the mountains of Northern Terel.\n");
    
    set_pen(45);
    set_hit(45);
    set_hands(W_ANYH);
    set_dt(W_BLUDGEON);
    set_wt(W_CLUB);
    set_wf(TO);
  
    set_spellpower_elements(({ SS_ELEMENT_AIR, SS_ELEMENT_WATER }));
    set_magic_spellpower(42);

    set_likely_dull(0);
    add_prop (OBJ_I_VALUE, F_VALUE_WEAPON(45, 45));
    add_prop (OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(45, W_CLUB));
    add_prop (OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop (OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop (MAGIC_AM_MAGIC,({ 40, "enchantment" }));
    add_prop (OBJ_S_WIZINFO, 
	      ("This club is magical weapon wielded by frost giants in "+
	       "Terel. The frost giant is in file " +
	       "/d/Terel/common/frost/npc/frost_giant.c "+
             "The clubs started out " +
	       "as normal heavy clubs, but were enchanted " +
	       "by a sorcerer of the area, who relies on the frost " +
	       "giants to keep his neck of the woods quiet.  " +
	       "It's a 45 45 club with an extra damage special.\n"));

    add_prop (MAGIC_AM_ID_INFO,
	      ({("The heavy club seems to be magical.\n",1,
		 "It is a club of the frost giants, one that does " +
		 "extra cold damage!\n"),50 }));
}


private void
tell_watcher (string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded ();
    ob = FILTER_LIVE (all_inventory (ENV (me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof (ob); i++) {
        if (!ob[i]->query_option(OPT_BLOOD) && CAN_SEE_IN_ROOM(ob[i]))
            ob[i]->catch_msg (str);
    }
}

public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int result;
    int res, special, skill;
    
    result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (phurt == -1)
    {
	    query_wielded()->catch_msg(
	        "You swing the heavy frost club with all your power, but " +
	        "miss.\n");
	    enemy->catch_msg("You duck under " + QTNAME(query_wielded()) +
			     "'s wild swing of the frost club.\n");

	    tell_watcher(QCTNAME(wielder)+" swings the frost club with all "+
		         HIS(wielder) + " power, but misses.\n", enemy);
    }
    else if (phurt == 0)
    {
	    query_wielded()->catch_msg("Your frost club just barely misses "+
				                   QTNAME (enemy)+"!\n");
	    enemy->catch_msg("The frost club of "+ QTNAME (query_wielded ())+
			     " just barely misses your head!\n");
	    tell_watcher(QCTNAME (wielder) + " just barely misses " +
		         QTNAME (enemy) + " with " + HIS (wielder) +
		         " heavy frost club.\n", enemy);
    }
    else 
    {
        query_wielded()->catch_msg("Your frost club slams into "+
                                   QTNAME (enemy)+" heavily!\n");
        enemy->catch_msg("The frost club of "+ QTNAME (query_wielded ())+
                        " slams into you!\n");
        tell_watcher(QCTNAME (wielder) + " slams " +
                     QTNAME (enemy) + " heavily with " + HIS (wielder) +
                     " heavy frost club.\n", enemy);

        if (random(4) == 0) /* extra frost damage */
        { 
            /* Check for resistances. */
            res = combine_resistances(enemy, 
                ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_COLD }) );
            if (res >= 100)
            {
                query_wielded()->catch_msg("Your frost club connects solidly "+
                  "with "+ QTNAME (enemy)+", but "+enemy->query_pronoun() +
                  " appears to be immune to the frost!\n");
                enemy->catch_msg("You are immune to the magic of the "+
                  "frost club wielded by "+ QTNAME (query_wielded ())+"\n");
                return result;
            }
               
            /* ok, now we get to the damage */
            query_wielded()->catch_msg("Your club blankets "+
                QTNAME (enemy)+" in frigid frost!\n");
            enemy->catch_msg("The frost club of "+ QTNAME (query_wielded ())+
                " blankets you with chilling frost!\n");
            tell_watcher(QCTNAME (wielder) + " covers " +
                QTNAME (enemy) + " with frost from " + HIS (wielder) +
                " heavy frost club.\n", enemy);
            skill = query_wielded()->query_skill(SS_WEP_CLUB);
            // Should never do more than 100% combat aid
            dam = min(F_PENMOD(query_pen(), skill), dam);
            // Reduce the Cold Pen by the resistance
            special = dam - (dam * res / 100);
            setuid();
            seteuid(getuid());
            write_file(DAMAGE_LOG, wielder->query_name() +" "+ special +" wcpen "+
                " to "+ enemy->query_name() +" with cold res "+ res +
                " (" + ctime(time()) + ")\n");
            enemy->hit_me(special, MAGIC_DT, TP, -1); 
        }
    }
	
    return result;
}

public void
set_spellpower_elements(int* element_skills)
{
    spellpower_elements = element_skills;
}

void appraise_object(int num)
{
   ::appraise_object(num);
   write(item_spellpower_desc());
}
 
string stat_object() 
{
     return ::stat_object() + stat_object_spellpower();
}

 