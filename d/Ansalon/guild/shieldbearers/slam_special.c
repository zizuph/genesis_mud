
/* This file is included in the guild shadow.  It contains the code
 * for the guild's special attack.  We keep it in a separate file to
 * keep from cluttering the shadow and for easier debugging.
 */

/* Navarre August 13th 2008.
 * Made the special hit another target if one is gone
 * but there are more present in the room.
 * That's how most special attacks work.
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include <ss_types.h>

static private int slam_alarm = 0;
static private int preparing_slam = 0;

void   slam(object target);
void   slam_message(object target);

/* Function name: can_attack_with_slam
 * Decription   : Determines if we are allowed to slam someone
 * Arguments    : object target  - our target
 *                string attack  - special name
 * Returns      : string         - Why aren't we allowed
 *                0              - We are allowed to attack
 */
public mixed
can_attack_with_slam(object target, string attack)
{
    mixed  why;
    object who = query_shadow_who();
    
    if (!target || !living(target) || !present(target, environment(who)))
    {
        return "You can't " + capitalize(attack) + " that!\n";
    }

    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
      who->query_prop(LIVE_I_STUNNED))
    {
        return "You are too stunned to "+attack+".\n";
    }

    if (stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
        stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
    {
        return why;
    }
    else if ( why )
    {
        return "You try, but something stops you from charging at " +
             target->query_the_name(who) + ".\n";
    }

  /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(who, -1))
    {
        /* A message should be given by query_not_attack_me(), so
         * no need to specify one here.
         */
        return "";
    }
  
  /* Check only if we are not already fighting this target */
    if ( member_array(target, who->query_enemy(-1)) == -1 )
    {
      /* Not enough DIS */
        if ( !F_DARE_ATTACK(who, target) )
        {
            return "You don't dare to slam " + target->query_the_name(who) + 
                ".\n";
        }
      
      /* Confirm attack on introduced person */
        if ( !who->query_npc() && who->query_met(target) &&
            ( who->query_prop(LIVE_O_LAST_KILL) != target) )
        {
            who->add_prop(LIVE_O_LAST_KILL, target);

            return "Slam " + target->query_the_name(who) + "?!? " +
                "Please confirm by trying again.\n";
        }
    }
        
    return 0;
}

/* Function name: reset_slam
 * Description  : Informs about readiness to use the special and
 *                clears the alarm.
 */
void
reset_slam()
{
    object who = query_shadow_who();
    who->catch_msg("You feel like you could slam someone again!\n");
    slam_alarm = 0;
}

void
prepare_slam(object target)
{
    float delay;

    object who = query_shadow_who();
    
    delay = who->query_speed(5 + random(8));
    
    if ( present(target, E(who)) )
	set_alarm(who->query_speed(3), 0.0, &slam_message(target));

    set_alarm(delay, 0.0, &slam(target));
    preparing_slam = 1;
    slam_alarm = 1;
}

void
slam_message(object target)
{
    object who = query_shadow_who();

    if ( !who->query_attack() && present(target, E(who)) )
    {
	if ((who->query_race() == "hobbit") ||
            (who->query_race_name() == "gnome") )
        {
  	    who->catch_msg("Your tiny feet pump swiftly as you run " +
	        "bravely towards " + QTNAME(target) + "...\n");
            target->catch_msg(QCTNAME(who) + " puts " + HIS(who) +
                " head down and runs bravely towards you, " + HIS(who) +
                " tiny feet pumping swiftly as " + HE(who) +
                " approaches...\n");
            who->tell_watcher(QCTNAME(who)+ " puts " + HIS(who) +
	        " head down and runs bravely towards " + QTNAME(target) +
                ", " +HIS(who)+ " tiny feet pumping swiftly as " +
	        HE(who) + " approaches...\n", target);
        }
        else
        {
	    who->catch_msg("Your stout legs pump hard as you charge " +
	        "furiously towards " + QTNAME(target) + "...\n");
            target->catch_msg(QCTNAME(who) + " puts " + HIS(who) +
	        " head down and charges towards you, " + HIS(who) +
	        " stout legs pumping harder and harder as " + HE(who) +
	        " approaches...\n");
            who->tell_watcher(QCTNAME(who)+ " puts " + HIS(who) +
	        " head down and charges furiously at " + QTNAME(target) +
	        ", " +HIS(who)+ " legs pumping harder and harder as " +
                HE(who) + " approaches...\n", target);
	}
    }
}

void
slam(object target)
{
    object* enemies;
    object enemy;
    object who = query_shadow_who();
    int    attacker_str, attacker_skill, attacker_stat;
    int    shield_ac, attacker_appraise;
    int    penet = 0, time, slam_alarm_id, slam_missed = 0;
    string shield_short, why;
    object slam;
    mixed  hitresult;

    preparing_slam = 0;
    slam_alarm_id = set_alarm(who->query_speed(25), 0.0, &reset_slam());

    if ( !present(target, E(who)) )
    {
        target = 0;

        enemies = who->query_enemy(-1);
        for(int i = 0, num_enemies = sizeof(enemies); i < num_enemies; i++)
        {
            enemy = enemies[i];

            if(enemy && environment(enemy) == environment(who))
            {
                target = enemy;
                break;
            }
        }

        if(!target)
        {
            write("Your target seems to have escaped!\n");
            remove_alarm(slam_alarm_id);
            slam_alarm_id = set_alarm(who->query_speed(5), 0.0, &reset_slam());
            return;
        }
    }

    if ( member_array(A_SHIELD, who->query_armour(-1)->query_at()) < 0 )
    {
	write("You cannot slam without a shield!\n");
	remove_alarm(slam_alarm_id);
	slam_alarm_id = set_alarm(who->query_speed(5), 0.0, &reset_slam());
	return;
    }

 /* Has the target become invalid somehow? */
    if (stringp(why = can_attack_with_slam(target, "slam")))
    {
        who->catch_msg(why);
        return;
    }
    
    if ( who->query_armour(W_RIGHT)->query_at() == A_SHIELD )
    {
	shield_short = who->query_armour(W_RIGHT)->short();
	shield_ac = who->query_armour(W_RIGHT)->query_ac();
    }
    else if ( who->query_armour(W_LEFT)->query_at() == A_SHIELD )
    {
	shield_short = who->query_armour(W_LEFT)->short();
	shield_ac = who->query_armour(W_LEFT)->query_ac();
    }

    attacker_str      = who->query_stat(SS_STR);
    attacker_skill    = who->query_skill(SHIELDSLAM_SPECIAL);
    attacker_stat     = who->query_stat(SS_LAYMAN);
    attacker_appraise = who->query_skill(SS_APPR_MON);
     
    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);

    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
 /* The slam missed */
    if ( (who->query_combat_object())->cb_tohit(-1, 80, target) != 1 )
    {
        if ((who->query_race() == "hobbit") ||
            (who->query_race_name() == "gnome") )
        {
            who->catch_msg("With a shriek, you run past " + QTNAME(target) +
                ", missing " + HIM(target) + " with your " + 
                shield_short + ".\n");
            target->catch_msg("With a shriek, " + QTNAME(who) + " runs " +
                "past you, missing you with " + HIS(who) + " " +
                shield_short + ".\n");
            who->tell_watcher("With a shriek, " + QTNAME(who) + " runs " +
                "past " + QTNAME(target) + ", missing " + HIM(target) +
                " with " + HIS(who) + " " + shield_short + ".\n", target);
        }
        else
        {
 	    who->catch_msg("With a roar, you charge past " + QTNAME(target) +
	        ", missing " + HIM(target) + " with your " + 
	        shield_short + ".\n");
	    target->catch_msg("With a roar, " + QTNAME(who) + " charges " +
   	        "past you, missing you with " + HIS(who) + " " + 
   	        shield_short + ".\n");
	    who->tell_watcher("With a roar, " + QTNAME(who) + " charges " +
	        "past " + QTNAME(target) + ", missing " + HIM(target) + 
	        " with " + HIS(who) + " " + shield_short + ".\n", target);
	}
	
	slam_missed = 1;
	penet = 0;
    }
    else     /* Successfull slam */
    {
        if ((who->query_race() == "hobbit") ||
            (who->query_race_name() == "gnome") )
        {
  	    who->catch_msg("With a shriek, you run into " + QTNAME(target) +
	        ", slamming " + HIM(target) + " with your " +
	        shield_short + ".\n");
	    target->catch_msg("With a shriek, " + QTNAME(who) + " runs " +
	        "into you, slamming you with " + HIS(who) + " " + 
	        shield_short + ".\n");
	    who->tell_watcher("With a shriek, " + QTNAME(who) + 
	        " runs into " + QTNAME(target)+ ", slamming " + 
	        HIM(target) + " with " + HIS(who) + " " + 
	        shield_short + ".\n", target);
        }
        else
        {
  	    who->catch_msg("With a roar, you charge into " + QTNAME(target) +
	        ", slamming " + HIM(target) + " with your " +
	        shield_short + ".\n");
	    target->catch_msg("With a roar, " + QTNAME(who) + " charges " +
	        "into you, slamming you with " + HIS(who) + " " + 
	        shield_short + ".\n");
	    who->tell_watcher("With a roar, " + QTNAME(who) + 
	        " charges into " + QTNAME(target)+ ", slamming " + 
	        HIM(target) + " with " + HIS(who) + " " + 
	        shield_short + ".\n", target);
        }

  
        /* Calculate the damage formula */ 
        penet =   attacker_str + shield_ac;
        penet += (attacker_appraise * 100) / 60;
        penet +=  MIN( MAX_GUILD_STAT_MOD, attacker_stat );
        penet =  (penet * 5) / 3;
        penet =  (penet * attacker_skill) / 100;
        penet =   MIN(800, penet);
        
//        if ( who->query_real_name() == "blizzardjr" )
//            find_player("blizzard")->catch_msg("DEBUG: PENET: " + penet + ".\n");
    }

    hitresult = target->hit_me(penet, W_BLUDGEON, who, -1);
    if (!sizeof(hitresult))
    {
        if ( !slam_missed )
	{
	    target->catch_msg("You are unaffected by " + HIS(who) + " attack.\n");
	    tell_room(E(target), QCTNAME(target) + " looks " +
		"unaffected, shrugging off the attack effortlessly.\n", target, TO);
	}
	return;
    }

    switch ( hitresult[0] )
    {
        case 0:
            if ( !slam_missed )
            {
                target->catch_msg("You are unaffected by " + HIS(who) + " attack.\n");
                tell_room(E(target), QCTNAME(target) + " looks " +
                    "unaffected, shrugging off the attack effortlessly.\n",
                    target, TO);
            }
	    return;
        case 1..6:
       	    target->catch_msg("You stumble, knocked slightly off balance " +
	        "by the attack.\n");
	    tell_room(E(target), QCTNAME(target)+ " stumbles, " +
	        "knocked slightly off balance by the attack.\n", target, TO);
            time = 4;
        break;
        case 7..18:
	    target->catch_msg("You struggle to keep your " +
	        "feet after the mighty attack.\n");
	    tell_room(E(target), QCTNAME(target) + " struggles " +
	        "to keep " + HIS(target) + " footing.\n", target, TO);
	    time = 6;
        break;
        case 19..36:
            if ( target->query_humanoid() )
	    {
	        target->catch_msg("Your knees buckle and you " +
	            "fall backwards, unable to keep your footing.\n");
	        tell_room(E(target), QCTNAME(target)+ "'s knees " +
	            "buckle, forcing " + HIM(target) + " backwards onto " +
	            "the ground.\n", target, TO);
	        time = 8;
	    }
	    else
	    {
	        target->catch_msg("You retreat backwards fearfully " +
	            "after such a hard hit!\n");
	        tell_room(E(target), QCTNAME(target) + " retreats " +
	            "backwards fearfully after such a mighty hit!\n", 
	            target, TO);
	    }
        break;
        default:
	    target->catch_msg("You feel dizzy... Is that the " +
	        "ground coming up to meet you?\n");
	    tell_room(E(target), QCTNAME(target)+ " collapses to the " +
	        "ground, dazed and totally unaware of " + HIS(target) +
	        " surroundings.\n", target, TO);
	    time = 10;
        break;
    }

    if ( target->query_hp() <= 0 )
    {
        target->do_die(who);
	return;
    }
        
    /* The slam will stun only humanoids */
    if ( !target->query_humanoid() )
        return;
  	
    /* Non-Neidars fully stun their opponents after reaching 60 in guild stat 
     * else the time is halved.
     */
    if ( !who->query_guild_member(NEIDAR_CLAN) && (attacker_stat < 60) )
        time = time / 2;

    /* The slam was not strong enough to stun the enemy even for a moment */
    if ( hitresult[0] < 1 )
        return;
  	    
    /* If the slam was strong enough -> we stun the target */
    seteuid(getuid(TO));

    slam = present("dwarven_special_obj", target);
    
    /* If the target is stunned already, remove the old stun object first */
    if ( slam )
        slam->remove_object();
        
    slam = clone_object(GUILD_DIR + "slam_obj");
    slam->set_slam_effect_time(time);
    slam->move(target, 1);

}


int
query_slam()
{
    return !!slam_alarm;
}

int
query_prepare_slam()
{
    return !!preparing_slam;
}
