#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

static private int slam_alarm = 0;
static private int preparing_slam = 0;

void slam(object target);
void slam_message(object target);

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
    object who = query_shadow_who();

    if(present(target, E(who)))
	set_alarm(5.0, 0.0, &slam_message(target));
    set_alarm(10.0, 0.0, &slam(target));
    preparing_slam = 1;
    slam_alarm = 1;
}

void
slam_message(object target)
{
    object who = query_shadow_who();
    if(!who->query_attack())
    {
	if(present(target, E(who)))
	{
	    who->catch_msg("Your stout legs pump hard as you charge " +
	      "furiously towards " +QTNAME(target) + "...\n");
	    target->catch_msg(QCTNAME(who) + " puts " +HIS(who)+
	      " head down and charges towards you, " +HIS(who)+
	      " stout legs pumping harder and harder as " +HE(who)+
	      " approaches...\n");
	    who->tell_watcher(QCTNAME(who)+ " puts " +HIS(who)+
	      " head down and charges furiously at " +QTNAME(target)+
	      ", " +HIS(who)+ " legs pumping harder and harder as " +HE(who)+
	      " approaches...\n", target);
	}
    }
}

void
slam(object target)
{
    object who = query_shadow_who();
    int attacker_str, attacker_skill, attacker_dex, victim_dex;
    int hitsuc, shield_ac, shield_bonus;
    string shield_short;
    object slam;

    preparing_slam = 0;
    set_alarm(30.0, 0.0, "reset_slam");

    if(!present(target, E(who)))
    {
	write("Your target seems to have escaped!\n");
	return;
    }


    if(member_array(A_SHIELD, who->query_armour(-1)->query_at()) < 0)
    {
	write("You cannot slam without a shield!\n");
	return;
    }

    if(who->query_armour(W_RIGHT)->query_at() == A_SHIELD)
    {
	shield_short = who->query_armour(W_RIGHT)->short();
	shield_ac = who->query_armour(W_RIGHT)->query_ac();
    }
    else if(who->query_armour(W_LEFT)->query_at() == A_SHIELD)
    {
	shield_short = who->query_armour(W_LEFT)->short();
	shield_ac = who->query_armour(W_LEFT)->query_ac();
    }

    attacker_str = who->query_stat(SS_STR);
    attacker_dex = who->query_stat(SS_DEX);
    victim_dex = target->query_stat(SS_DEX);

    attacker_skill = who->query_skill(SLAM_SPECIAL_SKILL);

/*Formula to hit an opponent with slam */
shield_bonus = attacker_skill /2 + attacker_str /10 - victim_dex /10 + 15;


    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);

    if(shield_bonus > (random(100) + 1))
	/*
	    if((hitsuc = who->query_combat_object()->cb_tohit(-1,shield_bonus,target)) > 0)
	*/
    {
	who->catch_msg("With a roar, you charge into " +QTNAME(target)+
	  ", slamming " +HIM(target)+ " with your " +
	  shield_short + ".\n");
	target->catch_msg("With a roar, " +QTNAME(who)+ " charges " +
	  "into you, slamming you with " +HIS(who)+ " " +shield_short+
	  ".\n");
	who->tell_watcher("With a roar, " +QTNAME(who)+ " charges into " +
	  QTNAME(target)+ ", slamming " +HIM(target)+ " with " +HIS(who)+
	  " " +shield_short+ ".\n",target);
	slam = clone_object(GUILD_DIR + "slam_obj");
	slam->set_attacker_str(attacker_str);
	slam->set_slam(attacker_skill);
	slam->set_shield_ac(shield_ac);
	slam->move(target);
    }
    else
    {
	who->catch_msg("With a roar, you charge past " +QTNAME(target)+
	  ", missing " +HIM(target)+ " with your " +
	  shield_short + ".\n");
	target->catch_msg("With a roar, " +QTNAME(who)+ " charges "+
	  "past you, missing you with " +HIS(who)+ " " +shield_short+ ".\n");
	who->tell_watcher("With a roar, " +QTNAME(who)+ " charges " +
	  "past " +QTNAME(target)+ ", missing " +HIM(target)+ " with " +
	  HIS(who)+ " " +shield_short + ".\n", target);
    }
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
