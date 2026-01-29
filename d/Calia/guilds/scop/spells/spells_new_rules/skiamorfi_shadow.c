/*
 *   Skiamorfi Shadow based off of Igneous' Disguise Shadow   
 *
 *   This shadow is used to disguise a players met/nonmet description
 *
 *   Copyright (C) Chad Richardson July 1996
 *
 *   Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Modifications by Bishop, April 2004.
 *
 * Navarre December 2006:
 *   - Changed the evade code to no longer
 *     evade special attacks and spells.
 *     Also changed to take number of enemies into
 *     account, so when you are fighting one enemy and evade
 *     X % of the incoming hits, you should only evade
 *     X/2 % of the incoming hits when you are fighting two 
 *     enemies, otherwise you get double the combat aid.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include <living_desc.h>
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#define SW   shadow_who

//    Prototypes
private mixed query_list(mixed list, int arg);

//   Global Vars
private string *Intro_list = ({});
int Block_prop = 0;
int skiamorfi_level = 1;
string Adj1 = "large", Adj2 = "ghostly";

/*
 * Function name :  remove_disguise_shadow
 * Description   :  remove this shadow from a player.
 */
void remove_disguise_shadow() {remove_shadow();}

/*
 * Function name :  remove_shadow
 * Description   :  Removes all the props we added to the player
 *                  and removes the shadow
 */
void
remove_shadow()
{	
    destruct();
}

/*
 * Function name :  set_disguise
 * Arguments     :  *string vars,  an array of vars we need to have to make
 *                  this disguise.
 * Description   :  Does what is says... sets up the disguise.
 */
void
set_disguise(string *vars)
{
    //  Can't fool ourselves
    Intro_list = ({SW->query_real_name()});

    Adj1 = vars[0];
    Adj2 = vars[1];
}

void
set_skiamorfi_level(int i)
{
    skiamorfi_level = i;
}

/* 
 *  All functions that this shadow masks should be placed 
 *  below this comment header, -Igneous-  
 */


/*
 * Function name :  parse_command_adjectiv_id_list
 * Description   :  Adds the disguised adverbs to the adjective list
 */
string *
parse_command_adjectiv_id_list()
{
    return ({Adj1}) + ({Adj2});
}

string *
parse_command_id_list()
{
    string *ids =  ({SW->query_real_name(), OB_NAME(SW), "presence"});
    
    if (SW->notmet_me(TP))
    {
        ids -= ({ SW->query_real_name() });
    }
 
    return ids;
}

private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
	return 0;
    if (!arg && sizeof(list))
	return list[0];
    else
	return list + ({});
}

varargs public mixed
query_adj(int arg)
{
    return query_list(({Adj1,Adj2}), arg);
}

public string *
query_adjs() 
{ 
    return query_list(({Adj1, Adj2}), 1);
}

public int
adjectiv_id(string str)
{
    return (member_array(str, ({Adj1, Adj2})) >= 0);
}

string
query_race_name()
{
    return "presence";
}

public varargs string
long(mixed for_obj)
{
    string sex, me_desc, other_desc;

    if (shadow_who->query_gender() == G_MALE)
    {
        sex = "male.";
    }
    else if (shadow_who->query_gender() == G_FEMALE)
    {
        sex = "female.";
    }
    else
    {
        sex = "neuter.";
    }

    if (!objectp(for_obj))
    {
        for_obj = TP;
    }

    me_desc = "You are cloaked in shadows. Your identity is concealed to "+
        "all onlookers unless you choose to introduce yourself to "+
        "them again. All of your possessions are concealed from "+
        "sight by the shadowy presence you have become.";
    
    if (skiamorfi_level == 1)
    {
        other_desc = "This strange presence is cloaked in shifting shadows." +
            " The shadows contract and expand eerily as the being moves, but" +
            " in spite of its forbidding exterior, you do not feel threatened"+
            " by it. Its shape is only vaguely humanoid, but you get a sense" +
            " that it is " + sex; 
    }
    else
    if (skiamorfi_level == 2)
    {
        other_desc = "Your breath catches as you take in the haunting beauty" +
            " of this radiant presence. It moves languidly and with purpose," +
            " and though clearly not of this world, it does not strike you as"+
            " ominous or menacing. Instead, you find it comforting to look at"+
            " and be near. Its shape is only vaguely humanoid, but you get a" +
            " sense that it is " + sex;
    }
    else
    {
        other_desc = "This mesmerizing presence has been touched by the" +
            " divine. It appears forged  from light and shadow equally," +
            " casting a glow upon its surroundings that makes them seem" +
            " greater and more alive. From the serene manner of its" +
            " movements, to the sheer majesty of its presence, everything" +
            " about this being suggests that it possesses the wisdom of the" +
            " ages. Its shape is only vaguely humanoid, but you get a sense" +
            " that it is " + sex;
    }      

    return (SW == for_obj ? me_desc : other_desc) + "\n";
} 

public string
race_sound()
{
    return "whispers in an eerie voice";
}

public void
shadow_me_transform(object target)
{
    shadow_me(target);
}

int filter_enemies(object ob)
{
  return ob->query_attack() == shadow_who;
}


/*
 * Function   : query_not_attack_me()
 * Arguments  : who: the attacker, aid: the attack ID
 * Description: Determines whether an attack is successful
 * Returns    : true if the attack fails, false if the attack succeeds
 */
int 
query_not_attack_me(object who, int aid)
{
    int percent, success;
    object attack_ob;
    mixed attack;
    string attack_desc;
    int number_of_enemies;
    
    if (SW->query_prop(LIVE_I_STUNNED))
    {
        return SW->query_not_attack_me(who, aid);
    }
    number_of_enemies = sizeof(filter(shadow_who->query_enemy(-1),
                               filter_enemies));

    attack_ob = who->query_combat_object();
    attack = attack_ob->query_attack(aid);

    // magical and special attack shouldn't miss
    if (!attack)
    {
        return SW->query_not_attack_me(who, aid);
    }
    attack_desc = attack_ob->cb_attack_desc(aid);

   // Takes into account that we shouldn't evade 25% of the
   // time for all enemies fighting us, 25% of the time divided
   // by the number of enemies. 

   if((number_of_enemies == 0) || (random(100) > (100 /number_of_enemies)))
   {
       return SW->query_not_attack_me(who, aid);
   }

   /* Evade Percentage Calculation
    * Caster: 35*90/100 +20*90/100 + 35*90/100 + 100 + 100 = 31.5 + 18 + 31.5 + 100 + 100 = 281
    * Enemy : 100 + 100 + 36*72/100 + 36*72/100 = 251.84 ~ 252.
    * Mod_IF = 281 - 252 ~ 29.    * Targeting around 25% evade, executing:
    * exec for (i=0; i<10000; i++) { a += (ME->resolve_task(TASK_DIFFICULT-100,
    *                                ({ SKILL_VALUE, 31 })) > 0);} return a;
    * Shows that TASK_DIFFICULT-100 with Modif = 31, yiels just below 25%
    */
    success = (SW->resolve_task(TASK_DIFFICULT-100,
              ({SKILL_WEIGHT, 35, TS_DEX,
               SKILL_WEIGHT, 20, TS_WIS,
               SKILL_WEIGHT, 35, TS_LAYMAN, SKILL_END,
               SS_SPELLCRAFT, SS_FORM_TRANSMUTATION}),
               who, 
               ({SS_AWARENESS, SS_APPR_MON,
               SKILL_WEIGHT, 36, TS_INT, SKILL_WEIGHT, 36, TS_DEX, SKILL_END})));

    /* for players with small stats the evade does't work very well, so for small
     * players 15 is added to the success value.
      */
    if ((SW->query_average()<101) && (SW->query_base_stat(SS_DEX)<101))
    {
        success += 15;
    }

    // Evade did not succeed
    if (success < 0)
    {
        return SW->query_not_attack_me(who, aid);
    }

    // Evade worked.
    SW->catch_tell(LANG_POSS(who->query_The_name(shadow_who)) + 
                           " attack on you hits nothing but shadows and mist.\n");
    who->catch_tell("Your attack on " + shadow_who->query_the_name(who) +
                    " hits nothing but shadows and mist.\n"); 
    SW->tell_watcher(LANG_POSS(QCTNAME(who)) + " attack on " +
                     QTNAME(shadow_who) + " hits nothing but shadows and mist.\n", 
                     (({who, SW})));      
    return 1;
}
