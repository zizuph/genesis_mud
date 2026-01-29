/*
 * Knight Special Attack (kattack)
 * 
 * Special was ported to the Genesis Specials System.
 *
 * Modifications:
 *   March 2009 - Changed combat aid so that High Knights have the same
 *                aid as Lord Knights. Changed after discussion with the
 *                balance team. - Petros
 *
 *   November 2018 - The combat aid modifier was not added properly, only
 *                   reaching 91 instead of 100, meaning the kattack was at
 *                   an 8 caid disadvantage. The kattack is no longer improved
 *                   by horses. - Carnak
 *
 *   November 2019 - A bug was discovered where 'charge horse' attacked their
 *                   own horse, so I figured Id add the same target code here
 *                   as I did in the charge ability.
 *
 * Created by Petros, October 2008
 */
  
#pragma strict_types

#include "../guild.h"
#include "/d/Genesis/specials/std/defs.h"

inherit DAMAGE_LIB;
inherit KNIGHT_UTILITY;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "/std/combat/combat.h"

/*
 * Function Name:   target_one_other_non_warhorse_present_living
 * Description:     This function makes sure that knights are unable to use this
 *                  ability to attack their horse.
 * Arguments:       (object) actor - The knight using the ability.
 *                  (string) str - The argument used along with the ability.
 * Returns:         (object *) An array of targets
 */
public object *
target_one_other_non_warhorse_present_living_or_enemy(object actor, string str)
{
    object *warhorse, *oblist, enemy;

    
    enemy = actor->query_attack();

    if (!strlen(str))
    {
        if (!enemy || 
            /* This shouldn't happen, but we'll check just in case */
            !present(enemy, environment(actor)))
        {
            actor->catch_tell("You aren't fighting anyone!\n");
            return ({});
        }
        return ({ enemy });
    }
    
    warhorse = ({ actor->query_steed() });
    if (pointerp(actor->query_following_steeds()))
        warhorse += actor->query_following_steeds();
    
    oblist = PARSE_THIS(str, "[at] / [on] [the] %l") - warhorse;
    
    if (!sizeof(oblist))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        actor->catch_tell("You will have to be more specific! You can only " +
            "select one target.\n");
        return ({});
    }

    return oblist;
} /* target_one_other_non_warhorse_present_living */

public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(80);
    set_tohit(95);
    set_skills( ({ SS_KATTACK }) );
    set_stats( ({ SKILL_AVG, TS_STR, TS_STR, TS_INT, TS_DIS, SKILL_END }) );
    set_ability_name("kattack");
    set_ability_vocal(0);
    set_ability_visual(0);
    set_ability_prep_time(7);
    set_ability_cooldown_time(8);
    set_ability_target(target_one_other_non_warhorse_present_living_or_enemy);
        
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

public void hook_special_complete()
{
    write("\nYou feel able to focus yourself towards your opponent " +
      "again.\n\n");
}

static mixed * check_required_items(object actor,mixed * targets,
                  string arg,int pretest)
{
    object weapon;
    
    weapon = query_primary_weapon(actor);

    if (!weapon)
    {
    	write("You cannot attack without a weapon.\n");
    	return 0;
    }
    return  ({ weapon });
}


public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam, mixed * items)
{
    object weapon, shield, horse;
    object *weapons;
    int hitres, weaponmod, statmod, pen, skill, weaponstat, to_hit;
    int wt, ht, rcry, rcry2, horsemod;
    string tar, att, aud, cry, *dam;
    int i = random(2);

    object actor=this_player();

    if (!objectp(actor))
        return;

    tar = "";
    att = "";
    aud = "";

    weapon = query_primary_weapon(actor);
    wt = weapon->query_wt();
    shield = query_shield(actor, 0);
    
    if (phurt < 0)
    {
        // We missed!
        switch (wt)
        {
        case W_SWORD:
        	att = "You swing your "+weapon->short()+" towards "+
				    QTNAME(enemy)+"'s "+hdesc+", but "+PRONOUN(enemy)+
				    " evades the attack.";
            tar = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+ 
                    weapon->short()+ " towards your "+
		            hdesc+", but you evade the attack.";
            aud = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+ 
                    weapon->short()+" towards "+QTNAME(enemy)+"'s "+
		            hdesc+", but "+QTNAME(enemy)+" evades "+
		            "the attack.";
		    break;
        case W_POLEARM:
            att = "You swing your "+weapon->short()+" towards "+
            QTNAME(enemy)+"'s "+hdesc+", but "+PRONOUN(enemy)+" evades "+
            "the attack.";
            tar = QTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+ weapon->short()+
            " towards your "+hdesc+", but you evade the attack.";
            aud = QTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+ weapon->short()+
            " towards "+QTNAME(enemy)+"'s "+hdesc+", but "+QTNAME(enemy)+" evades "+
            "the attack.";
            break;
        
        case W_CLUB:
            att = "You swing your "+weapon->short()+" harmlessly at "+
            QTNAME(enemy)+"'s "+hdesc+".";
            tar = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+weapon->short()+
            " harmlessly at your "+hdesc+".";
            aud = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+weapon->short()+
            " harmlessly at "+QTNAME(enemy)+"'s "+hdesc+".";
            break;

        case W_AXE:
            att = "You swing your "+weapon->short()+" towards "+
            QTNAME(enemy)+"'s "+hdesc+", but "+PRONOUN(enemy)+" evades "+
            "the attack.";
            tar = QTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+ weapon->short()+
            " towards your "+hdesc+", but you evade the attack.";
            aud = QTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+ weapon->short()+
            " towards "+QTNAME(enemy)+"'s "+hdesc+", but "+QTNAME(enemy)+" evades "+
            "the attack.";
            break;

        case W_KNIFE:
        default:
            att = "You swing your "+weapon->short()+" harmlessly at "+
            QTNAME(enemy)+"'s "+hdesc+".";
            tar = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+weapon->short()+
            " harmlessly at your "+hdesc+".";
            aud = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+weapon->short()+
            " harmlessly at "+QTNAME(enemy)+"'s "+hdesc+".";
            break;
        }

        actor->catch_msg(att+"\n");
        enemy->catch_msg(tar+"\n");
        actor->tell_watcher(aud+"\n", ({ actor, enemy }) );

        return;              
    }    

    if (wt == W_SWORD)
    {
    	switch(phurt)
    	{
	    case 0..5:
    	    att = "You lash out quickly with your "+weapon->short()+" and " +
        		  "lightly cut "+QTNAME(enemy)+"'s "+hdesc+".";
        	tar = QCTNAME(actor)+" lashes out quickly with "+POSSESSIVE(actor)+" "+
        		  weapon->short()+", lightly cutting your "+hdesc+".";
        	aud = QCTNAME(actor)+" lashes out quickly with "+POSSESSIVE(actor)+" "+
        		  weapon->short()+", lightly cutting the "+hdesc+" of "+
        		  QTNAME(enemy)+".";
        	break;
    	case 6..10:
	        att = QCTNAME(enemy)+" grabs your wrist as you attempt to bring your "+
		          weapon->short()+" down upon "+POSSESSIVE(enemy)+" "+hdesc+", but "+
	              "you bring your leg up and kick "+OBJECTIVE(enemy)+" hard in the "+
		          "chest.";
        	tar = "You grab "+QTNAME(actor)+"'s wrist as "+PRONOUN(actor)+" attempts "+
		          "to bring "+POSSESSIVE(actor)+" down upon your "+hdesc+", but "+
		          PRONOUN(actor)+" brings up his leg, kicking you hard in the chest.";
	        aud = QCTNAME(actor)+" swings downward with "+POSSESSIVE(actor)+" "+
    		      weapon->short()+", but "+QTNAME(enemy)+" grabs "+POSSESSIVE(actor)+
		          " wrist. "+QCTNAME(actor)+" steps back and brings "+POSSESSIVE(actor)+
		          " foot up, kicking "+QTNAME(enemy)+" hard in the chest.";
	        break;
	    case 11..15:
    	    att = "You bash "+QTNAME(enemy)+" with the hilt of your "+
        		  weapon->short()+", sending "+OBJECTIVE(enemy)+" staggering "+
		          "backwards.";
	        tar = QCTNAME(actor)+" bashes you with the hilt of "+POSSESSIVE(actor)+
    		      " "+weapon->short()+", sending you staggering from the blow.";
        	aud = QCTNAME(enemy)+" is sent staggering backwards as "+QTNAME(actor)+
        		  " bashes "+OBJECTIVE(enemy)+" with the hilt of "+POSSESSIVE(actor)+" "+
        		  weapon->short()+".";
        	break;
	    case 16..22:
	        att = "You slash deeply into "+QTNAME(enemy)+"'s "+hdesc+" with your "+
    		      weapon->short()+".";
        	tar = QCTNAME(actor)+" slashes deeply into your "+hdesc+" with "+
        		  POSSESSIVE(actor)+" "+weapon->short()+".";
        	aud = QCTNAME(actor)+" slashes deeply into "+QTNAME(enemy)+"'s "+hdesc+
        		  " with "+POSSESSIVE(actor)+" "+weapon->short()+".";
        	break;
    	case 23..29:
	        att = "Spotting an opening in "+QTNAME(enemy)+"'s defence, you stab " +
    		      "forward and pierce "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
        		  weapon->short()+".";
        	tar = QCTNAME(actor)+" stabs forward, spotting an opening in your " +
        		  "defence, and pierces your "+hdesc+" with "+POSSESSIVE(actor)+" "+
        		  weapon->short()+".";
        	aud = QCTNAME(actor)+" stabs forward, spotting an opening in "+
        		  QTNAME(enemy)+"'s defence, and pierces "+POSSESSIVE(enemy)+" "+hdesc+
        		  " with "+POSSESSIVE(actor)+" "+weapon->short()+".";
	    case 30..36:
    	    att = "You slash into "+QTNAME(enemy)+"'s "+hdesc+" with your "+
        		  weapon->short()+", then bring it around again in a fierce "+
		          "backhand swing, cutting deeply into "+POSSESSIVE(enemy)+" body.";
	        tar = QCTNAME(actor)+" slashes into your "+hdesc+" with "+POSSESSIVE(actor)+
    		      " "+weapon->short()+", then brings it around again in a "+
        		  "fierce backhand swing, cutting deeply into your body.";
        	aud = QCTNAME(actor)+" slashes into "+QTNAME(enemy)+"'s "+hdesc+" with "+
        		  POSSESSIVE(enemy)+" "+weapon->short()+", then brings it around "+
        		  "again in a fierce backhand swing, cutting deeply into "+
        		  POSSESSIVE(enemy)+" head.";
        	break;
	    case 37..43:
	        att = "Side-stepping a wayward blow from "+QTNAME(enemy)+", you "+
    		      "twirl and bring your "+weapon->short()+" around in a wide "+
        		  "arc, tearing a deep wound into "+POSSESSIVE(enemy)+" "+hdesc+".";
        	tar = QCTNAME(actor)+" side-steps your wayward blow and twirls, "+
        		  "bringing "+POSSESSIVE(actor)+" "+weapon->short()+" around in "+
        		  "a wide arc and tearing a deep wound into your "+hdesc+".";
        	aud = QCTNAME(actor)+" side-steps "+QTNAME(enemy)+"'s wayward blow and "+
        		  "twirls, bringing "+POSSESSIVE(actor)+" "+weapon->short()+
        		  " around in a wide arc and tearing a deep wound into "+QTNAME(enemy)+
        		  "'s "+hdesc+".";
        	break;
	    case 44..50:
    	    att = "With a skillful swing, you open a large gash on "+QTNAME(enemy)+
        		  "'s "+hdesc+" with the blade of your "+weapon->short()+".";
        	tar = QCTNAME(actor)+" opens a large gash on your "+hdesc+" with a " +
        		  "skillful swing of "+POSSESSIVE(actor)+" "+weapon->short()+".";
        	aud = QCTNAME(actor)+" opens a large gash on "+QTNAME(enemy)+"'s "+hdesc+
        		  " with a skillful swing of "+POSSESSIVE(actor)+" "+
        		  weapon->short()+".";
        	break;
	    default:
    	    att = "You confidently lunge forward, driving the blade of your "+
        		  weapon->short()+" deep into "+QTNAME(enemy)+"'s "+hdesc+".";
        	tar = QCTNAME(actor)+" confidently lunges forward, driving the blade " +
        		  "of "+POSSESSIVE(actor)+" "+weapon->short()+" deep into "+
        		  "your "+hdesc+".";
        	aud = QCTNAME(actor)+" confidently lunges forward, driving the blade " +
        		  "of "+POSSESSIVE(actor)+" "+weapon->short()+" deep into "+
        		  "the "+hdesc+" of "+QTNAME(enemy)+".";
        	break;
    	}
    }
    else if (wt == W_POLEARM)
    {
        switch(phurt)
        {
        case 0..5:
            {
            att = "You thrust with your "+weapon->short()+", and stab the "+
            "point into "+QTNAME(enemy)+"'s "+hdesc+".";
            tar = QCTNAME(actor)+" thrusts with "+POSSESSIVE(actor)+" "+
            weapon->short()+", and stabs the point into your "+hdesc+".";
            aud = QCTNAME(actor)+" thrusts with "+POSSESSIVE(actor)+" "+
            weapon->short()+", and stabs the point into "+QTNAME(enemy)+
            "'s "+hdesc+".";
            break;
            }
        case 6..10:
            {
            att = "You swing your "+weapon->short()+" at "+QTNAME(enemy)+
            ", striking "+POSSESSIVE(enemy)+" "+hdesc+".";
            tar = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+weapon->short()+
            " at you, striking your "+hdesc+".";
            aud = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+weapon->short()+
            " at "+QTNAME(enemy)+", striking "+POSSESSIVE(enemy)+" "+hdesc+".";
            break;
            }
        case 11..20:
            {
            att = QCTNAME(enemy)+" grabs your wrist as you attempt to bring your "+
            weapon->short()+" down upon "+POSSESSIVE(enemy)+" "+hdesc+", but "+
            "you bring your leg up and kick "+OBJECTIVE(enemy)+" hard in the "+
            "chest.";
            tar = "You grab "+QTNAME(actor)+"'s wrist as "+PRONOUN(actor)+" attempts "+
            "to bring "+POSSESSIVE(actor)+" down upon your "+hdesc+", but "+
            PRONOUN(actor)+" brings up his leg, kicking you hard in the chest.";
            aud = QCTNAME(actor)+" swings downward with "+POSSESSIVE(actor)+" "+
            weapon->short()+", but "+QTNAME(enemy)+" grabs "+POSSESSIVE(actor)+
            " wrist. "+QCTNAME(actor)+" steps back and brings "+POSSESSIVE(actor)+
            " foot up, kicking "+QTNAME(enemy)+" hard in the chest.";
            break;
            }
        case 21..30:
            {
            att = "You drive your "+weapon->short()+" into "+QTNAME(enemy)+
            "'s "+hdesc+" with a forceful blow.";
            tar = QCTNAME(actor)+" drives "+POSSESSIVE(actor)+" "+weapon->short()+
            " into your "+hdesc+" with a forceful blow.";
            aud = QCTNAME(actor)+" drives "+POSSESSIVE(actor)+" "+weapon->short()+
            " into "+QTNAME(enemy)+"'s "+hdesc+" with a forceful blow.";
            break;
            }
        case 31..40:
            {
            att = "You drive your "+weapon->short()+" deep into "+QTNAME(enemy)+
            "'s "+hdesc+", causing a severe injury.";
            tar = QCTNAME(actor)+" drives "+POSSESSIVE(actor)+" "+weapon->short()+
            " deep into your "+hdesc+", causing a severe injury.";
            aud = QCTNAME(actor)+" drives "+POSSESSIVE(actor)+" "+weapon->short()+
            " deep into "+QTNAME(enemy)+"'s "+hdesc+", causing a severe injury.";
            break;
            }
        case 41..50:
            {
            att = "You raise your "+weapon->short()+" aloft, letting it fall "+
            "with a crushing blow upon "+QTNAME(enemy)+"'s "+hdesc+".";
            tar = QCTNAME(actor)+" raises "+POSSESSIVE(actor)+" "+weapon->short()+
            " aloft, letting it fall with a crushing blow upon your "+hdesc+
            ".";
            aud = QCTNAME(actor)+" raises "+POSSESSIVE(actor)+" "+weapon->short()+
            " aloft, letting it fall with a crushing blow upon "+QTNAME(enemy)+
            "'s "+hdesc+".";
            break;
            }
        default:
            {
            att = "You deliver a mortal wound to "+QTNAME(enemy)+", impaling "+
            POSSESSIVE(enemy)+" "+hdesc+" with your "+
            weapon->short()+".";
            tar = QCTNAME(actor)+" mortally wounds you, impaling your "+
            hdesc+" with "+POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" mortally wounds "+QTNAME(enemy)+", "+
            "impaling "+POSSESSIVE(enemy)+" "+hdesc+" with "+POSSESSIVE(actor)+
            " "+weapon->short()+".";
            break;
            }
        }
    }
    else if (wt == W_CLUB)
    {
        switch(phurt)
        {
        case 0..5:
            {
            att = "Swinging hard with your "+weapon->short()+", you hit "+
            QTNAME(enemy)+" lightly on the "+hdesc+".";
            tar = "Swinging hard with "+POSSESSIVE(actor)+" "+weapon->short()+
            ", "+QTNAME(actor)+" hits you lightly on the "+hdesc+".";
            aud = "Swinging hard with "+POSSESSIVE(actor)+" "+weapon->short()+
            ", "+QTNAME(actor)+" hits "+QTNAME(enemy)+" lightly on the "+
            hdesc+".";
            break;
            }
        case 6..10:
            {
            att = "You thrust forward, bashing "+QTNAME(enemy)+" with the hilt "+
            "of your "+weapon->short()+".";
            tar = QCTNAME(actor)+" thrusts forward, bashing you with the hilt "+
            "of "+POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" thrusts forward, bashing "+QTNAME(enemy)+" with "+
            "the hilt of "+POSSESSIVE(actor)+" "+weapon->short()+".";
            break;
            }
        case 11..20:
            {
            att = "With a fierce swing, you hurt "+QTNAME(enemy)+"'s "+hdesc+
            " with your "+weapon->short()+".";
            tar = "With a fierce swing, "+QTNAME(actor)+" hurts your "+hdesc+
            " with "+POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = "With a fierce swing, "+QTNAME(actor)+" hurts "+QTNAME(enemy)+
            "'s "+hdesc+" with "+POSSESSIVE(actor)+" "+
            weapon->short()+".";
            break;
            }
        case 21..30:
            {
            att = "You raise your "+weapon->short()+" above your head "+
            "and bring it crashing down on "+QTNAME(enemy)+"'s "+hdesc+".";
            tar = QCTNAME(actor)+" raises "+POSSESSIVE(actor)+" "+
            weapon->short()+" above "+POSSESSIVE(actor)+" head and "+
            "brings it crashing down on your "+hdesc+".";
            aud = QCTNAME(actor)+" raises "+POSSESSIVE(actor)+" "+
            weapon->short()+" above "+POSSESSIVE(actor)+" head and "+
            "brings it crashing down upon "+QTNAME(enemy)+"'s "+hdesc+".";
            break;
            }
        case 31..40:
            {
            att = "You strike "+QTNAME(enemy)+"'s "+hdesc+" with your "+
            weapon->short()+", then bring it around again in a powerful "+
            "backhand stroke, smashing it into "+QTNAME(enemy)+"'s head.";
            tar = QCTNAME(actor)+" strikes your "+hdesc+" with " +
            POSSESSIVE(actor) +
            " "+weapon->short()+", then brings it around again in a "+
            "powerful backhand stroke, smashing it into your head.";
            aud = QCTNAME(actor)+" strikes "+QTNAME(enemy)+"'s "+hdesc+" with "+
            POSSESSIVE(actor)+" "+weapon->short()+", then brings it around "+
            "again in a powerful backhand stroke, smashing it into "+
            QTNAME(enemy)+"'s head.";
            break;
            }
        case 41..50:
            {
            att = "You nearly shatter "+QTNAME(enemy)+"'s "+hdesc+" with a "+
            "devastating swing of your "+weapon->short()+".";
            tar = QCTNAME(actor)+" nearly shatters your "+
            hdesc+" with a devastating swing of "+POSSESSIVE(actor)+
            " "+weapon->short()+".";
            aud = QCTNAME(actor)+" nearly shatters "+QTNAME(enemy)+"'s "+hdesc+
            " with a devastating swing of "+POSSESSIVE(actor)+" "+
            weapon->short()+".";
            break;
            }
        default:
            {
            att = "You swing your "+weapon->short()+" at "+QTNAME(enemy)+
            " with all of your might, crushing "+POSSESSIVE(enemy)+" "+
            hdesc+".";
            tar = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+
            weapon->short()+" at you with all of "+POSSESSIVE(actor)+
            " might, crushing your "+hdesc+".";
            aud = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+
            weapon->short()+" at "+QTNAME(enemy)+" with all of "+
            POSSESSIVE(actor)+" might, crushing "+QTNAME(enemy)+"'s "+
            hdesc+".";
            break;
            }
        }
    }
    else if (wt == W_AXE)
    {
        switch(phurt)
        {
        case 0..5:
            {
            att = "You lash out with your "+weapon->short()+" and lightly "+
            "slash "+QTNAME(enemy)+"'s "+hdesc+".";
            tar = QCTNAME(actor)+" lashes out with "+POSSESSIVE(actor)+" "+
            weapon->short()+", lightly slashing your "+hdesc+".";
            aud = QCTNAME(actor)+" lashes out with "+POSSESSIVE(actor)+" "+
            weapon->short()+", lightly slashing the "+hdesc+" of "+
            QTNAME(enemy)+".";
            break;
            }
        case 6..10:
            {
            att = "You bash "+QTNAME(enemy)+"'s "+hdesc+" with the flat side of " +
            "your "+weapon->short()+".";
            tar = QCTNAME(actor)+" bashes your "+hdesc+" with the flat side of "+
            POSSESSIVE(enemy)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" bashes "+QTNAME(enemy)+"'s "+hdesc+" with the " +
            "flat side of "+POSSESSIVE(actor)+" "+weapon->short()+".";
            break;
            }
        case 11..20:
            {
            att = QCTNAME(enemy)+" grabs your wrist as you attempt to bring your "+
            weapon->short()+" down upon "+POSSESSIVE(enemy)+" "+hdesc+", but "+
            "you bring your leg up and kick "+OBJECTIVE(enemy)+" hard in the "+
            "chest.";
            tar = "You grab "+QTNAME(actor)+"'s wrist as "+PRONOUN(actor)+" attempts "+
            "to bring "+POSSESSIVE(actor)+" down upon your "+hdesc+", but "+
            PRONOUN(actor)+" brings up his leg, kicking you hard in the chest.";
            aud = QCTNAME(actor)+" swings downward with "+POSSESSIVE(actor)+" "+
            weapon->short()+", but "+QTNAME(enemy)+" grabs "+POSSESSIVE(actor)+
            " wrist. "+QCTNAME(actor)+" steps back and brings "+POSSESSIVE(actor)+
            " foot up, kicking "+QTNAME(enemy)+" hard in the chest.";
            break;
            }
        case 21..30:
            {
            att = "You rip deeply into "+QTNAME(enemy)+"'s "+hdesc+" with your "+
            weapon->short()+".";
            tar = QCTNAME(actor)+" rips deeply into your "+hdesc+" with "+
            POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" rips deeply into "+QTNAME(enemy)+"'s "+hdesc+
            " with "+POSSESSIVE(actor)+" "+weapon->short()+".";
            break;
            }
        case 31..40:
            {
            att = "Swinging hard with your "+weapon->short()+", you slice a "+
            "nasty gash into "+QTNAME(enemy)+"'s "+hdesc+".";
            tar = "Swinging hard with "+POSSESSIVE(actor)+" "+weapon->short()+
            ", "+QTNAME(actor)+" slices a nasty gash into your "+hdesc+".";
            aud = "Swinging hard with "+POSSESSIVE(actor)+" "+weapon->short()+
            ", "+QTNAME(actor)+" slices a nasty gash into "+QTNAME(enemy)+"'s "+
            hdesc+".";
            break;
            }
        case 41..50:
            {
            att = "With a mighty swing, you cut to the bone of "+QTNAME(enemy)+
            "'s "+hdesc+" with the blade of your "+weapon->short()+".";
            tar = QCTNAME(actor)+" cuts to the bone of your "+hdesc+" with a " +
            "mighty blow of "+POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" swings "+POSSESSIVE(actor)+" "+weapon->short()+
            " mightily, cutting to the bone of "+QTNAME(enemy)+"'s "+hdesc+".";
            break;
            }
        default:
            {
            att = "You almost tear "+QTNAME(enemy)+"'s "+hdesc+" off with a "+
            "tremendous blow of your "+weapon->short()+".";
            tar = QCTNAME(actor)+" almost tears your "+hdesc+" off with a "+
            "tremendous blow of your "+weapon->short()+".";
            aud = QCTNAME(actor)+" almost tears "+QTNAME(enemy)+"'s "+hdesc+
            " off with a tremendous blow of "+POSSESSIVE(actor)+" "+
            weapon->short()+".";
            break;
            }
        }
    }
    else if (wt == W_KNIFE)
    {
        switch(phurt)
        {
        case 0..5:
            {
            att = "You nick "+QTNAME(enemy)+"'s "+hdesc+" with the tip of your "+
            weapon->short()+".";
            tar = QCTNAME(actor)+" nicks your "+hdesc+" with the tip of "+
            POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" nicks "+QTNAME(enemy)+" "+hdesc+" with the tip of "+
            POSSESSIVE(actor)+" "+weapon->short()+".";
            break;
            }
        case 6..10:
            {
            att = "You cut a shallow wound into "+QTNAME(enemy)+" "+hdesc+
            " with your "+weapon->short()+".";
            tar = QCTNAME(actor)+" cuts a shallow wound into your "+hdesc+
            " with "+POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" cuts a shallow wound into "+QTNAME(enemy)+"'s "+
            hdesc+" with "+POSSESSIVE(actor)+" "+weapon->short()+".";
            break;
            }
        case 11..20:
            {
            att = "You slice into "+QTNAME(enemy)+"'s "+hdesc+" with your "+
            weapon->short()+".";
            tar = QCTNAME(actor)+" slices into your "+hdesc+" with "+
            POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" slices into "+QTNAME(enemy)+"'s "+hdesc+
            " with "+POSSESSIVE(actor)+" "+weapon->short()+".";
            break;
            }
        case 21..35:
            {
            att = "Your "+weapon->short()+" bites deeply into "+
            QTNAME(enemy)+"'s "+hdesc+".";
            tar = QCTNAME(actor)+"'s "+weapon->short()+" bites "+
            "deeply into your "+hdesc+".";
            aud = QCTNAME(actor)+"'s "+weapon->short()+" bites "+
            "deeply into your "+hdesc+".";
            break;
            }
        case 36..50:
            {
            att = "You carve a deep wound into the "+hdesc+" of "+
            QTNAME(enemy)+" with your "+weapon->short()+".";
            tar = QCTNAME(actor)+" carves a deep wound into your "+hdesc+
            " with "+POSSESSIVE(actor)+" "+weapon->short()+".";
            aud = QCTNAME(actor)+" carves a deep wound into the "+hdesc+
            " of "+QTNAME(enemy)+" with "+POSSESSIVE(actor)+" "+
            weapon->short()+".";
            break;
            }
        default:
            {
            att = "You pierce "+QTNAME(enemy)+"'s defences with your "+
            weapon->short()+", driving it deep into "+
            POSSESSIVE(enemy)+" "+hdesc+".";
            tar = QCTNAME(actor)+" pierces your defences with "+
            POSSESSIVE(actor)+" "+weapon->short()+", driving "+
            "it deep into your "+hdesc+".";
            aud = QCTNAME(actor)+" pierces "+QTNAME(enemy)+"'s defences with "+
            POSSESSIVE(actor)+" "+weapon->short()+", driving "+
            "it deep into "+POSSESSIVE(enemy)+" "+hdesc+".";
            break;
            }
        }
    }

    if (shield && !random(3))
    {
        switch(phurt)
        {
            case 0..5:
            {
                switch(wt)
                {
                case W_SWORD:
                    dam = ({ "quickly lash out with your "+weapon->short()+", "+
                      "lightly cutting "+QTNAME(enemy)+"'s "+hdesc+".\n",
                      "quickly lashes out with "+POSSESSIVE(actor)+" "+weapon->short()+
                      ", lightly cutting your "+hdesc+".",
                      "quickly lashes out with "+POSSESSIVE(actor)+" "+weapon->short()+
                      ", lightly cutting "+QTNAME(enemy)+"'s "+hdesc+"." });
                    break;
                case W_CLUB:
                    dam = ({ "swing hard with your "+weapon->short()+", "+
                      "hitting "+QTNAME(enemy)+"'s "+hdesc+" lightly.",
                      "swings hard with "+POSSESSIVE(actor)+" "+weapon->short()+
                      ", hitting your "+hdesc+" lightly.",
                      "swings hard with "+POSSESSIVE(actor)+" "+weapon->short()+
                      ", hitting "+QTNAME(enemy)+"'s "+hdesc+" lightly." });
                    break;
                case W_AXE:
                    dam = ({ "lash out with your "+weapon->short()+", lightly "+
                      "slashing "+QTNAME(enemy)+"'s "+hdesc+".",
                      "lashes out with "+POSSESSIVE(actor)+" "+weapon->short()+
                      ", lightly slashing your "+hdesc+".",
                      "lashes out with "+POSSESSIVE(actor)+" "+weapon->short()+
                      ", lightly slashing "+QTNAME(enemy)+"'s "+hdesc+"." });
                    break;
                case W_KNIFE:
                    dam = ({ "nick "+QTNAME(enemy)+"'s "+hdesc+" with the tip of "+
                      "your "+weapon->short()+".",
                      "nicks your "+hdesc+" with the tip of "+POSSESSIVE(actor)+
                      " "+weapon->short()+".",
                      "nicks "+QTNAME(enemy)+"'s "+hdesc+" with the tip of "+
                      POSSESSIVE(actor)+" "+weapon->short()+"." });
                    break;
                default:
                    dam = ({ "scratch "+QTNAME(enemy)+"'s "+hdesc+" with "+
                      "your "+weapon->short()+".",
                      "scratches your "+hdesc+" with "+POSSESSIVE(actor)+
                      " "+weapon->short()+".",
                      "scratches "+QTNAME(enemy)+"'s "+hdesc+" with "+
                      POSSESSIVE(actor)+" "+weapon->short()+"." });
                }
    
                att = "You bring up your "+shield->short()+" to block "+
                    "a blow from "+QTNAME(enemy)+" and "+dam[0];
                tar = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
                    shield->short()+" to block a blow and "+dam[1];
                aud = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
                     shield->short()+" to block a blow from "+QTNAME(enemy)+
                    " and "+dam[2];
                break;
            }
    
        case 6..12:
            {
            att = "You bash "+QTNAME(enemy)+" with your "+shield->short()+", "+
            "sending "+OBJECTIVE(enemy)+" staggering backwards.";
            tar = QCTNAME(actor)+" bashes you with "+POSSESSIVE(actor)+
            " "+shield->short()+", sending you staggering backwards.";
            aud = QCTNAME(enemy)+" is sent staggering backwards as "+QTNAME(actor)+
            " bashes "+OBJECTIVE(enemy)+" with "+POSSESSIVE(actor)+" "+
            shield->short()+".";
            break;
            }
        case 13..20:
            {
                switch(wt)
                {
                case W_SWORD:
                    dam = ({ "slice into "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
                      weapon->short()+".",
                      "slices into your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                      weapon->short()+".",
                      "slices into "+POSSESSIVE(enemy)+" "+hdesc+" with "+
                      POSSESSIVE(actor)+" "+weapon->short()+"." });
                    break;
                case W_CLUB:
                    dam = ({ "strike "+POSSESSIVE(enemy)+" "+hdesc+" hard with your "+
                      weapon->short()+".",
                      "strikes your "+hdesc+" hard with "+POSSESSIVE(actor)+" "+
                      weapon->short()+".",
                      "strikes "+QTNAME(enemy)+"'s "+hdesc+" with "+POSSESSIVE(actor)+
                      " "+weapon->short()+"." });
                    break;
                case W_AXE:
                    dam = ({ "tear a wound into "+POSSESSIVE(enemy)+" "+hdesc+
                      " with your "+weapon->short()+".",
                      "tears a wound into your "+hdesc+" with "+POSSESSIVE(actor)+
                      " "+weapon->short()+".",
                      "tears a wound into "+QTNAME(enemy)+"'s "+hdesc+" with "+
                      POSSESSIVE(actor)+" "+weapon->short()+"." });
                    break;
                case W_KNIFE:
                    dam = ({ "stab "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
                      weapon->short()+".",
                      "stabs into your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                      weapon->short()+".",
                      "stabs into "+QTNAME(enemy)+"'s "+hdesc+" with "+
                      POSSESSIVE(actor)+" "+weapon->short()+"." });
                    break;
                default:
                    dam = ({ "hit "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
                         weapon->short()+".",
                         "hits your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                         weapon->short()+".",
                         "hits "+QTNAME(enemy)+"'s "+hdesc+" with "+
                         POSSESSIVE(actor)+" "+weapon->short()+"." });
                }
    
                att = "You bring up your "+shield->short()+" to block "+
                "a blow from "+QTNAME(enemy)+" and "+dam[0];
                tar = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
                 shield->short()+" to block a blow and "+dam[1];
                aud = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
                 shield->short()+" to block a blow from "+QTNAME(enemy)+
                " and "+dam[2];
                break;
            }

        case 21..30:
            {
            att = "You send "+QTNAME(enemy)+" sprawling as you fiercely slam "+
            "your "+shield->short()+" into "+POSSESSIVE(enemy)+" chest.";
            tar = QCTNAME(actor)+" sends you sprawling as "+PRONOUN(actor)+
            " fiercely slams "+POSSESSIVE(actor)+" "+shield->short()+
            "into your chest.";
            aud = QCTNAME(actor)+" sends "+QTNAME(enemy)+" sprawling as "+
            PRONOUN(actor)+" fiercely slams "+POSSESSIVE(actor)+" "+
            shield->short()+" into "+POSSESSIVE(enemy)+" chest.";
            break;
            }
        case 40..50:
            {
                if (!random(2))
                {
            att = QCTNAME(enemy)+"'s knees buckle and "+PRONOUN(enemy)+" swoons "+
            "under the tremendous impact of your "+shield->short()+" as "+
            "you smash it into his body with a bone crushing sound.";
            tar = "You feel your knees buckle and you swoon under the trem"+
            "endous impact of "+QTNAME(actor)+"' "+shield->short()+" as "+
            PRONOUN(actor)+" smashes it into your body, with a bone "+
            "crushing sound.";
            aud = QCTNAME(enemy)+"'s knees buckle and "+PRONOUN(enemy)+" swoons "+
            "under the tremendous impact of "+QTNAME(actor)+"'s "+
            shield->short()+" as "+PRONOUN(actor)+" smashes it into "+
            POSSESSIVE(actor)+" body with a bone crushing sound.";
            break;
                }
                switch(wt)
            {
            case W_SWORD:
                dam = ({ "tear a gaping wound in "+POSSESSIVE(enemy)+" "+hdesc+" with "+
                  "your "+weapon->short()+".",
                  "tears a gaping wound in your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                  weapon->short()+".",
                  "tears a gaping wound in "+QTNAME(enemy)+"'s "+hdesc+" with "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_CLUB:
                dam = ({ "smash "+POSSESSIVE(enemy)+" "+hdesc+" with a mighty "+
                  "blow of your "+weapon->short()+".",
                  "smashes your "+hdesc+" with a mighty blow of "+
                  POSSESSIVE(actor)+" "+weapon->short()+".",
                  "smashes "+QTNAME(enemy)+"'s "+hdesc+" with a mighty blow of "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_AXE:
                dam = ({ "cut to the bone of "+POSSESSIVE(enemy)+" "+hdesc+" in a "+
                  "tremendous strike of your "+weapon->short()+".",
                  "cuts to the bone of your "+hdesc+" in a tremendous strike "+
                  "of "+POSSESSIVE(actor)+" "+weapon->short()+".",
                  "cuts to the bone of "+QTNAME(enemy)+"'s "+hdesc+" with a "+
                  "tremendous strike of "+POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_KNIFE:
                dam = ({ "bury your "+weapon->short()+" to the hilt in "+
                  POSSESSIVE(enemy)+" "+hdesc+".",
                  "buries "+POSSESSIVE(actor)+" "+weapon->short()+" to the "+
                  "hilt in your "+hdesc+".",
                  "buries "+POSSESSIVE(actor)+" "+weapon->short()+" to the "+
                  "hilt in "+QTNAME(enemy)+"'s "+hdesc+"." });
                break;
            default:
                dam = ({ "smash "+POSSESSIVE(enemy)+" "+hdesc+" with a mighty "+
                  "blow of your "+weapon->short()+".",
                  "smashes your "+hdesc+" with a mighty blow of "+
                  POSSESSIVE(actor)+" "+weapon->short()+".",
                  "smashes "+QTNAME(enemy)+"'s "+hdesc+" with a mighty blow of "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                  }
    
               if (!random(2))
               {
               att = "You bring up your "+shield->short()+" to block "+
                 "a blow from "+QTNAME(enemy)+" and "+dam[0];
             tar = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
                 shield->short()+" to block a blow and "+dam[1];
             aud = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
                 shield->short()+" to block a blow from "+QTNAME(enemy)+
             " and "+dam[2];
               }
              else
               {
               att = "You daze "+QTNAME(enemy)+" with a fierce shield "+
                  "bash and "+dam[0];
             tar = QCTNAME(actor)+" dazes you with a fierce shield "+
                  "bash and "+dam[1];
             aud = QCTNAME(actor)+" dazes "+QTNAME(enemy)+" with a fierce "+
                  "shield bash and "+dam[2];
              }
                 break;
              }
        }
    }

    weapons = actor->query_weapon(-1);
    if (sizeof(weapons) == 2 && actor->query_weapon(W_RIGHT)->query_wt() != W_POLEARM &&
      actor->query_weapon(W_LEFT)->query_wt() != W_POLEARM && random(3) == 0)
    {
        switch(phurt)
        {
        case 0..5:
            {
            switch(wt)
            {
            case W_SWORD:
                dam = ({ "quickly lash out with your "+weapon->short()+", "+
                  "lightly cutting "+QTNAME(enemy)+"'s "+hdesc+".\n",
                  "quickly lashes out with "+POSSESSIVE(actor)+" "+weapon->short()+
                  ", lightly cutting your "+hdesc+".",
                  "quickly lashes out with "+POSSESSIVE(actor)+" "+weapon->short()+
                  ", lightly cutting "+QTNAME(enemy)+"'s "+hdesc+"." });
                break;
            case W_CLUB:
                dam = ({ "swing hard with your "+weapon->short()+", "+
                  "hitting "+QTNAME(enemy)+"'s "+hdesc+" lightly.",
                  "swings hard with "+POSSESSIVE(actor)+" "+weapon->short()+
                  ", hitting your "+hdesc+" lightly.",
                  "swings hard with "+POSSESSIVE(actor)+" "+weapon->short()+
                  ", hitting "+QTNAME(enemy)+"'s "+hdesc+" lightly." });
                break;
            case W_AXE:
                dam = ({ "lash out with your "+weapon->short()+", lightly "+
                  "slashing "+QTNAME(enemy)+"'s "+hdesc+".",
                  "lashes out with "+POSSESSIVE(actor)+" "+weapon->short()+
                  ", lightly slashing your "+hdesc+".",
                  "lashes out with "+POSSESSIVE(actor)+" "+weapon->short()+
                  ", lightly slashing "+QTNAME(enemy)+"'s "+hdesc+"." });
                break;
            case W_KNIFE:
                dam = ({ "nick "+QTNAME(enemy)+"'s "+hdesc+" with the tip of "+
                  "your "+weapon->short()+".",
                  "nicks your "+hdesc+" with the tip of "+POSSESSIVE(actor)+
                  " "+weapon->short()+".",
                  "nicks "+QTNAME(enemy)+"'s "+hdesc+" with the tip of "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            default:
                dam = ({ "swing hard with your "+weapon->short()+", "+
                  "hitting "+QTNAME(enemy)+"'s "+hdesc+" lightly.",
                  "swings hard with "+POSSESSIVE(actor)+" "+weapon->short()+
                  ", hitting your "+hdesc+" lightly.",
                  "swings hard with "+POSSESSIVE(actor)+" "+weapon->short()+
                  ", hitting "+QTNAME(enemy)+"'s "+hdesc+" lightly." });
            }
    
                    if (!random(2))
                    {
            att = "You bring up your "+weapons[1]->short()+" to parry "+
            "a blow from "+QTNAME(enemy)+" and "+dam[0];
            tar = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
            weapons[1]->short()+" to parry a blow and "+dam[1];
            aud = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
            weapons[1]->short()+" to parry a blow from "+QTNAME(enemy)+
            " and "+dam[2];
                    }
                   else
                    {
            att = "You swing at and miss "+QTNAME(enemy)+" with your "+weapons[1]->short()+", but "+
            dam[0];
            tar = QCTNAME(actor)+" swings at you and misses with "+POSSESSIVE(actor)+
            " "+weapons[1]->short()+", but "+dam[1];
            aud = QCTNAME(actor)+" misses "+QTNAME(enemy)+" with "+POSSESSIVE(actor)+
            " "+weapons[1]->short()+", but "+dam[2];
                    }
            break;
            }
        case 11..15:
            {
            switch(wt)
            {
            case W_SWORD:
                dam = ({ "slice into "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
                  weapon->short()+".",
                  "slices into your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                  weapon->short()+".",
                  "slices into "+POSSESSIVE(enemy)+" "+hdesc+" with "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_CLUB:
                dam = ({ "strike "+POSSESSIVE(enemy)+" "+hdesc+" hard with your "+
                  weapon->short()+".",
                  "strikes your "+hdesc+" hard with "+POSSESSIVE(actor)+" "+
                  weapon->short()+".",
                  "strikes "+QTNAME(enemy)+"'s "+hdesc+" with "+POSSESSIVE(actor)+
                  " "+weapon->short()+"." });
                break;
            case W_AXE:
                dam = ({ "tear a wound into "+POSSESSIVE(enemy)+" "+hdesc+
                  " with your "+weapon->short()+".",
                  "tears a wound into your "+hdesc+" with "+POSSESSIVE(actor)+
                  " "+weapon->short()+".",
                  "tears a wound into "+QTNAME(enemy)+"'s "+hdesc+" with "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_KNIFE:
                dam = ({ "stab "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
                  weapon->short()+".",
                  "stabs into your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                  weapon->short()+".",
                  "stabs into "+QTNAME(enemy)+"'s "+hdesc+" with "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            default:
                dam = ({ "strike "+POSSESSIVE(enemy)+" "+hdesc+" hard with your "+
                     weapon->short()+".",
                     "strikes your "+hdesc+" hard with "+POSSESSIVE(actor)+" "+
                     weapon->short()+".",
                     "strikes "+QTNAME(enemy)+"'s "+hdesc+" with "+POSSESSIVE(actor)+
                     " "+weapon->short()+"." });
            }
    
                    if (!random(2))
                    {
            att = "You bring up your "+weapons[1]->short()+" to parry "+
            "a blow from "+QTNAME(enemy)+" and "+dam[0];
            tar = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
            weapons[1]->short()+" to parry a blow and "+dam[1];
            aud = QCTNAME(actor)+" brings up "+POSSESSIVE(actor)+" "+
            weapons[1]->short()+" to parry a blow from "+QTNAME(enemy)+
            " and "+dam[2];
                    }
                   else
                    {
            att = "You swing at and miss "+QTNAME(enemy)+" with your "+weapons[1]->short()+", but "+
            dam[0];
            tar = QCTNAME(actor)+" swings at you and misses with "+POSSESSIVE(actor)+
            " "+weapons[1]->short()+", but "+dam[1];
            aud = QCTNAME(actor)+" misses "+QTNAME(enemy)+" with "+POSSESSIVE(actor)+
            " "+weapons[1]->short()+", but "+dam[2];
                    }
            break;
            }
        case 25..33:
            {
            switch(wt)
            {
            case W_SWORD:
                dam = ({ "slash deeply into "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
                  weapon->short()+".",
                  "slashes deeply into your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                  weapon->short()+".",
                  "slashes deeply into "+QTNAME(enemy)+"'s "+hdesc+" with "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_CLUB:
                dam = ({ "hurt "+POSSESSIVE(enemy)+" "+hdesc+" badly with a fierce "+
                  "swing of your "+weapon->short()+".",
                  "hurt your "+hdesc+" badly with a fierce swing of "+
                  POSSESSIVE(actor)+" "+weapon->short()+".",
                  "hurts "+QTNAME(enemy)+"'s "+hdesc+" badly with a fierce swing of "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_AXE:
                dam = ({ "rips into "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
                  weapon->short()+".",
                  "rips into your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                  weapon->short()+".",
                  "rips into "+QTNAME(enemy)+"'s "+hdesc+" with "+POSSESSIVE(actor)+
                  " "+weapon->short()+"." });
                break;
            case W_KNIFE:
                dam = ({ "stab deeply into "+POSSESSIVE(enemy)+" "+hdesc+" with your "+
                  weapon->short()+".",
                  "stabs deeply into your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                  weapon->short()+".",
                  "stabs deeply into "+QTNAME(enemy)+"'s "+hdesc+" with "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            default:
                dam = ({ "hurt "+POSSESSIVE(enemy)+" "+hdesc+" badly with a fierce "+
                  "swing of your "+weapon->short()+".",
                  "hurt your "+hdesc+" badly with a fierce swing of "+
                  POSSESSIVE(actor)+" "+weapon->short()+".",
                  "hurts "+QTNAME(enemy)+"'s "+hdesc+" badly with a fierce swing of "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
            }
            switch(weapons[1]->query_wt())
            {
            case W_SWORD:
                att = "You slice a shallow wound in "+QTNAME(enemy)+"'s body with "+
                "your "+weapons[1]->short()+", and "+dam[0];
                tar = QCTNAME(actor)+" slices a shallow wound into your body with "+
                POSSESSIVE(actor)+" "+weapons[1]->short()+", and "+dam[1];
                aud = QCTNAME(actor)+" slices a shallow wound into "+QTNAME(enemy)+
                "'s body with "+POSSESSIVE(actor)+" "+weapons[1]->short()+", "+
                "and "+dam[2];
                break;
            case W_CLUB:
                att = "You strike "+QTNAME(enemy)+"'s body with your "+
                weapons[1]->short()+", and "+dam[0];
                tar = QCTNAME(actor)+" strikes your body with "+POSSESSIVE(actor)+
                weapons[1]->short()+", and "+dam[1];
                aud = QCTNAME(actor)+" strikes "+QTNAME(enemy)+"'s body with "+
                POSSESSIVE(actor)+" "+weapons[1]->short()+", and "+dam[2];
                break;
            case W_AXE:
                att = "You slash into "+QTNAME(enemy)+"'s body with your "+
                weapons[1]->short()+", and "+dam[0];
                tar = QCTNAME(actor)+" slashes into your body with "+
                POSSESSIVE(actor)+" "+weapons[1]->short()+", and "+dam[1];
                aud = QCTNAME(actor)+" slashes into "+QTNAME(enemy)+"'s body "+
                "with "+POSSESSIVE(actor)+" "+weapons[1]->short()+", and "+
                dam[2];
                break;
            case W_KNIFE:
                att = "You stab "+QTNAME(enemy)+"'s body with your "+
                weapons[1]->short()+", and "+dam[0];
                tar = QCTNAME(actor)+" stabs your body with "+POSSESSIVE(actor)+
                " "+weapons[1]->short()+", and "+dam[1];
                aud = QCTNAME(actor)+" stabs "+QTNAME(enemy)+"'s body with "+
                POSSESSIVE(actor)+" "+weapons[1]->short()+", and "+dam[2];
                break;
            default:
                att = "You strike "+QTNAME(enemy)+"'s body with your "+
                weapons[1]->short()+", and "+dam[0];
                tar = QCTNAME(actor)+" strikes your body with "+POSSESSIVE(actor)+
                weapons[1]->short()+", and "+dam[1];
                aud = QCTNAME(actor)+" strikes "+QTNAME(enemy)+"'s body with "+
                POSSESSIVE(actor)+" "+weapons[1]->short()+", and "+dam[2];
            }
            }
        case 43..50:
            {
            switch(wt)
            {
            case W_SWORD:
                dam = ({ "tear a gaping wound in "+POSSESSIVE(enemy)+" "+hdesc+" with "+
                  "your "+weapon->short()+".",
                  "tears a gaping wound in your "+hdesc+" with "+POSSESSIVE(actor)+" "+
                  weapon->short()+".",
                  "tears a gaping wound in "+QTNAME(enemy)+"'s "+hdesc+" with "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_CLUB:
                dam = ({ "smash "+POSSESSIVE(enemy)+" "+hdesc+" with a mighty "+
                  "blow of your "+weapon->short()+".",
                  "smashes your "+hdesc+" with a mighty blow of "+
                  POSSESSIVE(actor)+" "+weapon->short()+".",
                  "smashes "+QTNAME(enemy)+"'s "+hdesc+" with a mighty blow of "+
                  POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_AXE:
                dam = ({ "cut to the bone of "+POSSESSIVE(enemy)+" "+hdesc+" in a "+
                  "tremendous strike of your "+weapon->short()+".",
                  "cuts to the bone of your "+hdesc+" in a tremendous strike "+
                  "of "+POSSESSIVE(actor)+" "+weapon->short()+".",
                  "cuts to the bone of "+QTNAME(enemy)+"'s "+hdesc+" with a "+
                  "tremendous strike of "+POSSESSIVE(actor)+" "+weapon->short()+"." });
                break;
            case W_KNIFE:
                dam = ({ "bury your "+weapon->short()+" to the hilt in "+
                  POSSESSIVE(enemy)+" "+hdesc+".",
                  "buries "+POSSESSIVE(actor)+" "+weapon->short()+" to the "+
                  "hilt in your "+hdesc+".",
                  "buries "+POSSESSIVE(actor)+" "+weapon->short()+" to the "+
                  "hilt in "+QTNAME(enemy)+"'s "+hdesc+"." });
                break;
            default:
                dam = ({ "smash "+POSSESSIVE(enemy)+" "+hdesc+" with a mighty "+
                     "blow of your "+weapon->short()+".",
                     "smashes your "+hdesc+" with a mighty blow of "+
                     POSSESSIVE(actor)+" "+weapon->short()+".",
                     "smashes "+QTNAME(enemy)+"'s "+hdesc+" with a mighty blow of "+
                     POSSESSIVE(actor)+" "+weapon->short()+"." });
            }
            switch(weapons[1]->query_wt())
            {
            case W_SWORD:
                att = "Driving the blade of your "+weapons[1]->short()+" deeply "+
                "into "+ QTNAME(enemy)+"'s body, you also "+dam[0];
                tar = "As "+PRONOUN(actor)+" drives the blade of " +
                POSSESSIVE(actor) + " " + weapons[1]->short() +
                " into your body, " + QTNAME(actor) + " " + dam[1];
                aud = "As " + QTNAME(actor) + " drives the blade of " +
                POSSESSIVE(actor) + " " + weapons[1]->short() +
                " into " + QTNAME(enemy) + "'s body, " + PRONOUN(actor) +
                " also "+dam[2];
                break;
            case W_CLUB:
                att = "Bringing your "+weapons[1]->short()+" crashing down upon "+
                QTNAME(enemy)+"'s shoulder, you also "+dam[0];
                tar = "As "+PRONOUN(actor)+" brings "+POSSESSIVE(actor)+" "+
                weapons[1]->short()+" crashing down upon your shoulder, "+
                QTNAME(actor)+" also "+dam[1];
                aud = "As "+PRONOUN(actor)+" brings "+POSSESSIVE(actor)+" "+
                weapons[1]->short()+" crashing down upon "+QTNAME(enemy)+"'s "+
                "shoulder, "+PRONOUN(actor)+" also "+dam[2];
                break;
            case W_AXE:
                att = "Nearly slashing through "+QTNAME(enemy)+"'s body with your "+
                weapons[1]->short()+", you also "+dam[0];
                tar = "As "+PRONOUN(actor)+" nearly slashes through your body with "+
                POSSESSIVE(actor)+" "+weapons[1]->short()+", "+QTNAME(actor)+
                " also "+dam[1];
                aud = "As "+PRONOUN(actor)+" nearly slashes through "+QTNAME(enemy)+
                "'s body with "+POSSESSIVE(actor)+" "+weapons[1]->short()+", "+
                QTNAME(actor)+" also "+dam[2];
                break;
            case W_KNIFE:
                att = "Plunging the length of your "+weapons[1]->short()+" into "+
                QTNAME(enemy)+"'s shoulder, you also "+dam[0];
                tar = "As "+PRONOUN(actor)+" plunges the length of "+POSSESSIVE(actor)+
                " "+weapons[1]->short()+" into your shoulder, "+QTNAME(actor)+
                " also "+dam[1];
                aud = "As "+PRONOUN(actor)+" plunges the length of "+POSSESSIVE(actor)+
                " "+weapons[1]->short()+" into "+QTNAME(enemy)+"'s shoulder, "+
                QTNAME(enemy)+" also "+dam[2];
                break;
            default:
                att = "Bringing your "+weapons[1]->short()+" crashing down upon "+
                QTNAME(enemy)+"'s shoulder, you also "+dam[0];
                tar = "As "+PRONOUN(actor)+" brings "+POSSESSIVE(actor)+" "+
                weapons[1]->short()+" crashing down upon your shoulder, "+
                QTNAME(actor)+" also "+dam[1];
                aud = "As "+PRONOUN(actor)+" brings "+POSSESSIVE(actor)+" "+
                weapons[1]->short()+" crashing down upon "+QTNAME(enemy)+"'s "+
                "shoulder, "+PRONOUN(actor)+" also "+dam[2];
            }
            }
        }
    }
    
    horse = query_mounted_solamnian_steed(actor);
    if (objectp(horse) && !random(5))
    {
        switch(phurt)
        {
        case 5..10:
            {
            att = "You whirl your "+horse->steed_short()+" around and "+
            POSSESSIVE(horse)+" flank slams into "+QTNAME(enemy)+".";
            tar = QCTNAME(actor)+" whirls "+POSSESSIVE(actor)+" "+horse->steed_short()+
            " around and slams its flank into you.";
            aud = QCTNAME(actor)+" whirls "+POSSESSIVE(actor)+" "+horse->steed_short()+
            " around and slams its flank into "+QTNAME(enemy)+".";
            break;
            }
        case 11..18:
            {
            att = "You spur your "+horse->steed_short()+" forward and "+
            PRONOUN(horse)+" jerks "+POSSESSIVE(horse)+" head "+
            "upwards, nearly knocking "+QTNAME(enemy)+" to the ground.";
            tar = QCTNAME(actor)+" spurs "+POSSESSIVE(actor)+" "+horse->steed_short()+
            " forward and it jerks its head upwards, nearly knocking you "+
            "to the ground.";
            aud = QCTNAME(actor)+" spurs "+POSSESSIVE(actor)+" "+horse->steed_short()+
            " forward and it jerks its head upwards, nearly knocking "+
            QTNAME(enemy)+" to the ground.";
            break;
            }
        case 30..40:
            {
            att = "Your "+horse->steed_short()+" rears back on "+POSSESSIVE(horse)+
            " hindlegs, smacking "+QTNAME(enemy)+" heavily with its front "+
            "hooves, and knocking "+OBJECTIVE(enemy)+" back a few steps.";
            tar = QCTNAME(actor)+"'s "+horse->steed_short()+" rears back on its "+
            "hindlegs, smacking its front hooves into you heavily, and "+
            "knocking you backwards.";
            aud = QCTNAME(actor)+"'s "+horse->steed_short()+" rears back on its "+
            "hindlegs, smacking "+QTNAME(enemy)+" heavily with its front "+
            "hooves, and knocking "+OBJECTIVE(enemy)+" backwards.";
            break;
            }
        case 41..50:
            {
            att = "Your bring your "+horse->steed_short()+" around, and the well-"+
            "trained mount kicks "+QTNAME(enemy)+" tremendously hard with its "+
            "hindlegs. "+QCTNAME(enemy)+" looks dazed.";
            tar = QCTNAME(actor)+" brings "+POSSESSIVE(actor)+" "+horse->steed_short()+
            " around, and the steed kicks you tremendously hard with its "+
            "hindlegs. You see stars.";
            aud = QCTNAME(actor)+" brings "+POSSESSIVE(actor)+" "+horse->steed_short()+
            " around, and the steed kicks "+QTNAME(enemy)+" tremendously hard "+
            "with its hindlegs. "+QCTNAME(enemy)+" looks dazed.";
            }
        }
    }

    rcry = random(3);
    if (!rcry && phurt >= 20)
    {
        switch(random(10))
        {
        case 0:
            cry = "For Vingaard and the Orders!";
            break;
        case 1:
            switch(actor->query_knight_level())
            {
            case 5:
            cry = "For the Order of the Rose!";
            break;
            case 4:
            cry = "For the Order of the Sword!";
            break;
            case 3:
            cry = "For the Order of the Crown!";
            break;
            default:
            cry = "For the Knighthood!";
            break;
            }
            break;
        case 2:
            switch(actor->query_knight_level())
            {
            case 4:
            cry = "Kiri-Jolith!";
            break;
            case 3:
            cry = "Habbakuk!";
            break;
            default:
            cry = "Paladine!";
            break;
            }
            break;
        case 3:
            cry = "By the Measure!";
            break;
        case 4:
            cry = "For Vingaard!";
            break;
        case 5:
            cry = "By the Oath and the Measure!";
            break;
        case 6:
            cry = "Victory to the Knighthood!";
            break;
        case 7:
            cry = "For Solamnia!";
            break;
        case 8:
            cry = "For the Knighthood!";
            break;
        case 9:
            switch(actor->query_knight_level())
            {
            case 5:
            cry = "In the name of justice!";
            break;
            case 4:
            cry = "In the name of courage!";
            break;
            case 3:
            cry = "In the name of honour!";
            break;
            default:
            cry = "In the name of Solamnia!";
            break;
            }
            break;
        }
        if (!actor->query_prop("_i_quiet_knight"))
        {
            actor->command("$shout "+cry);
        }
    }

    actor->catch_msg(att+"\n");
    enemy->catch_msg(tar+"\n");
    actor->tell_watcher(aud+"\n", ({ actor, enemy }) );

    if (enemy->query_hp() <= 0)
    {
        switch(random(3))
        {
        case 0:
            actor->catch_msg("You wipe the blood from your "+weapon->short()+
              " as you regard "+QTNAME(enemy)+" solemnly, knowing "+
              POSSESSIVE(enemy)+" end is near.\n");
            enemy->catch_msg(QCTNAME(actor)+" wipes the blood "+
                "from "+POSSESSIVE(actor)+
                " "+weapon->short()+" as "+PRONOUN(actor)+" regards " +
                "you solemnly.");
            actor->tell_watcher(QCTNAME(actor)+" wipes the blood from "+
              POSSESSIVE(actor)+" "+weapon->short()+" as "+
              PRONOUN(actor)+" regards "+QTNAME(enemy)+
              " solemnly.\n", enemy);
            break;
        case 1:
            if (enemy->query_race_name() == "draconian")
            {
            actor->catch_msg("You feel no remorse as you strike the killing blow, "+
              "but rather you look with disgust at "+QTNAME(enemy)+".\n");
            actor->tell_watcher(QCTNAME(actor)+" looks with disgust at "+QTNAME(enemy)+
              " as "+PRONOUN(actor)+" strikes the killing blow.\n", enemy);
            }
            else
            {
            actor->catch_msg("You feel a brief twinge of remorse as you strike "+
              "the killing blow, but quickly regain your composure.\n");
            actor->tell_watcher(QCTNAME(actor)+"'s face softens briefly as "+
              PRONOUN(actor)+" looks at "+QTNAME(enemy)+", but "+PRONOUN(actor)+
              " quickly regains "+POSSESSIVE(actor)+" cool composure.\n", 
              enemy);
            enemy->catch_msg(QCTNAME(actor)+"'s face softens briefly as "+
             PRONOUN(actor)+" he looks at you, but "+PRONOUN(actor)+
             " quickly regains "+POSSESSIVE(actor)+" cool composure.\n");
            }
            break;
        case 2:
            if (actor->query_steed() && !random(3))
            {
                horse = actor->query_steed();
    
                switch(random(2))
                {
                case 1:
                    actor->catch_msg("Your "+horse->steed_short()+" rears back on "+POSSESSIVE(horse)+
                      " hindlegs, sending "+QTNAME(enemy)+" crashing to the ground "+
                      "with a crushing blow of its front hooves.\n");
                    enemy->catch_msg(QCTNAME(actor)+"'s "+horse->steed_short()+" rears back "+
                      "on its hindlegs, sending you crashing to the ground with a crushing "+
                      "blow of its front hooves.\n");
                    actor->tell_watcher(QCTNAME(actor)+"'s "+horse->steed_short()+" rears back on its "+
                      "hindlegs, sending "+QTNAME(enemy)+" crashing to the ground with a "+
                      "crushing blow of its front hooves.\n", enemy);
                    break;
                    
                case 0:
                    actor->catch_msg("As "+QTNAME(enemy)+" falls to the ground, "+
                          "your "+horse->steed_short()+" charges forward like a well-trained "+
                          "beast of battle, trampling your foe underfoot.\n");
                    enemy->catch_msg("As you fall to the ground, "+QTNAME(actor)+
                          "'s "+horse->steed_short()+" charges forward like a well-trained "+
                          "beast of battle, trampling you underfoot.\n");
                    actor->tell_watcher("As "+QTNAME(enemy)+" falls to the ground, "+QTNAME(actor)+
                          "'s "+horse->steed_short()+" charges forward like a well-trained "+
                          "beast of battle, trampling the fallen foe underfoot.\n", 
                          enemy);
                    break;
                }
            }
            else
            {
                actor->catch_msg("Your blood surges with adrenaline as you realize "+
                  "you've survived yet another battle!\n");
                actor->tell_watcher(QCTNAME(actor)+" begins to calm down from the "+
                  "excitement of battle, having survived yet again.\n", enemy);
            }
            break;
        }
        enemy->do_die(actor);
    }
}

public void hook_attack_object(object enemy)
{
    object actor = this_player();

    object weapon;
    
    weapon = query_primary_weapon(actor);
    
    if (!objectp(weapon))
    {
        return;
    }
    
    say(QCTNAME(actor)+" raises "+POSSESSIVE(actor)+" "+weapon->short()+
        " aloft, giving "+QTNAME(enemy)+" a traditional salute as "+
          PRONOUN(actor)+" rushes forward to do battle with "+OBJECTIVE(enemy)+
          "!\n", ({ enemy, actor }));
    enemy->catch_msg(QCTNAME(actor)+" raises "+POSSESSIVE(actor)+" "+
          weapon->short()+" aloft, giving you a traditional " +
          "salute as "+PRONOUN(actor)+" rushes forward to do " +
          "battle with you!\n");
    actor->catch_msg("You raise your "+weapon->short()+" aloft, saluting "+
          QTNAME(enemy)+" traditionally as you rush forward to " +
          "do battle with "+OBJECTIVE(enemy)+"!\n");
}


static void 
ability_msg(object actor, mixed * targets, string arg)
{
    object weapon, enemy;
    
    enemy = targets[0];
    weapon = query_primary_weapon(actor);
    
    switch (random(5))
    {
        case 4:
            if (objectp(weapon))
            {
                actor->catch_msg("You feign an attack with your "+weapon->short()+
                  ", distracting "+QTNAME(enemy)+", and follow through with the "+
                  "true attack...\n");     
                break;   
            }
            // intentionally fall through if no weapon.
        case 3:
            actor->catch_msg(QCTNAME(enemy)+" swings clumsily, leaving an opening "+
              "in "+POSSESSIVE(enemy)+" defence which you move to exploit...\n");
            break;
        case 2:
            actor->catch_msg("You skillfully parry "+QTNAME(enemy)+"'s attack, "+
              "leaving "+OBJECTIVE(enemy)+" open for a strike...\n");
            break;
        case 1:
            actor->catch_msg("Dodging "+QTNAME(enemy)+"'s blow, you move in to "+
              "counterattack...\n");
            break;
            
        default:
            actor->catch_msg("You duck a fierce swing from "+QTNAME(enemy)+
              ", leaving "+OBJECTIVE(enemy)+" off balance...\n");
            break;
    }
}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object enemy;

    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (CHARGE_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are still charging towards your foes "
            + "and are unable to engage using kattack at this time.\n");       
        return 0;
    }
    else if (CHARGE_ABILITY->query_ability_in_cooldown(player))
    {
        player->catch_msg("Having just recently charged past your foes "
            + "you are still unable to engage and kattack.\n");
        return 0;
    }
    
    // If it passes everything, return success
    return 1; 
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier()
{
    // Knights are modified by a few factors
    // 1. Knight Level
    // 2. Mounted on Horse
    //
    // Knights will start at 35% power. Every Knight Level gives them an extra
    // 5% in power. Being mounted gives them an extra 15%. A Knight of the Black
    // Rose will have half of the total normal combat aid
    // 2018-11-11: Horses no longer improve kattack, it starts at 45%
    int modifier = 45;
    int horse_modifier = 0;
    int level, sublevel;
    object player;
    
    player = this_player();
    
/*
    // Bonus for riding on Solamnian Warhorse
    if (objectp(query_mounted_solamnian_steed(player)))
    {
        horse_modifier = min(75, player->query_skill(SS_MOUNTED_COMBAT));
    }

    horse_modifier = horse_modifier * 15 / 75;
    modifier += horse_modifier;
*/
    // Now add the Knight Levels
    level = player->query_knight_level();
    sublevel = player->query_knight_sublevel();
    
    switch(player->query_knight_level())
    {
    case L_ROSE:    
    case L_SWORD:
        // Sword and Rose Knights get their maximum
        // damage regardless of sublevel because they
        // have already been through the entire Crown
        // Order.
        modifier += 55;
        break;
        
    case L_CROWN:    
    case L_SQUIRE:
        // Crown Knights and Squire power depends on which sub level
        // they are on.
        modifier += (sublevel * 5);
        break;
        
    case L_BROSE:
        modifier += (sublevel * 5);
        modifier /= 2; // black knights get their modifiers reduces by half
        break;
    }
    
    return modifier;
}
