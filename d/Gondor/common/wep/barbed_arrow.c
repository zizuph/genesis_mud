/*
 *Special stun arrow for haradrim greatbow
 *Altrus, July 2005
*/

inherit "/std/arrow";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

#define IS_STUN "_stunned_from_barbed_arrow"
#define WLD_BOW "_is_wielding_greatbow"

public void
create_arrow()
{
    set_adj("barbed grey-feathered");

    set_projectile_id("gondor_grey_feathered_arrow");
    set_hit(45 + random(10));
    set_pen(50 + random(10));
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + " somewhat heavier than normal. Tipped with " + ((num == 1) ? "a nasty looking, barbed steel head" : "nasty looking, barbed steel heads") + " the " + ((num == 1) ? "arrow looks" : "arrows look") + " like " + ((num == 1) ? "it" : "they") + "might severely hurt if shot properly. " + ((num==1) ? "It" : "They") + " might even knock someone to the ground, if shot hard enough.\n";
}

void reset_stun(object target)
{
	target->remove_prop(IS_STUN);
}

void un_stun(object target, object attacker, object arrow)
{
    if (objectp(target))
    {
	target->remove_stun();
	target->remove_subloc("_arrow_stunned");
	arrow->remove_prop(OBJ_M_NO_DROP);
	arrow->remove_prop(OBJ_M_NO_GIVE);
	target->catch_msg("Gritting your teeth, you rip the arrow out of your shoulder!\n");
	tell_room(ENV(target), QCTNAME(target) + " grits " + HIS_HER(target) + " teeth and rips the arrow out of " + HIS_HER(target) + " shoulder!\n", target, target);
	set_alarm(30.0, 0.0, &reset_stun(target));
	}
}

public void
projectile_hit_target(object archer, int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam, int hid)
{
    int skill, stat, skill_e, stat_e, pen, perf, pdam;
    mixed *hitresult;
    string ptext;
    object arrow = this_object();

    skill = archer->query_skill(SS_WEP_MISSILE);
    stat = archer->query_stat(SS_DEX);
    skill_e = enemy->query_skill(SS_DEFENCE);
    stat_e = enemy->query_stat(SS_DEX);
    
    //Special hit wont work unless you have the skill and wielding the greatbow
    if(!archer->query_prop(WLD_BOW))
        return;
    if(archer->query_skill(SS_WEP_MISSILE) < 80)
	return;
    //Cap the stats at 90....don't want to get too high, damage might get ridiculous, or
    //the reverse, it might never hit
    if (stat > 90)
        stat = 70 + random(20);
    if (stat_e > 90)
        stat_e = 70 + random(20);

    if ((random(80) < (skill/2)) && (random(skill+stat) > random(skill_e+stat_e)))
    {
        if(random(4))
        {
            if(!enemy->query_prop(IS_STUN))
	    {
                enemy->add_stun();
		enemy->add_prop(IS_STUN, 1);
		enemy->add_subloc("_arrow_stunned", this_object());
		arrow->add_prop(OBJ_M_NO_DROP, "It's stuck deep, and you can't bring yourself to tear it out!\n");
		arrow->add_prop(OBJ_M_NO_GIVE, "It's stuck deep, and you can't bring yourself to tear it out!\n");
		arrow->move_object(enemy);
		set_alarm(15.0, 0.0, &un_stun(enemy, archer, arrow));
		archer->catch_msg("Pulling back as far as you can, you release the string on the greatbow.\nThe " + short() + " knocks " + QTNAME(enemy) + " back... The arrow sinks deep and looks stuck!\n");
	        enemy->catch_msg(QCTNAME(archer) + " pulls back far on the greatbow and releases.\nThe " + short() + " knocks you back... The arrow sinks in deep, and feels like it is stuck!\n");
	        archer->tell_watcher(QCTNAME(archer) + " pulls back far on the greatbow and releases.\nThe " + short() + " knocks " + QTNAME(enemy) + " back... The arrow sinks deep and looks stuck!\n");
		return;
	    }
        }
	
    pen = F_PENMOD(40+random(stat/4), skill);
    hitresult = enemy->hit_me(pen, W_IMPALE, archer, -1);
    perf = hitresult[2] * 100 / pen;
   
    ptext = "grazes weakly";
    if (perf > 15)
	ptext = "punctures superficially";
    if (perf > 30)
	ptext = "pierces harshly";
    if (perf > 45)
	ptext = "sinks deeply";
    if (perf > 60)
	ptext = "perforates painfully";
    if (perf > 75)
	ptext = "penetrates devastatingly";
		
		if (enemy->query_hp() <= 0)
		{
			enemy->command("gasp");
			archer->catch_msg("With an amazingly accurate shot, you fell " + QTNAME(enemy) + "!\n" + HE_SHE(enemy) + " stumbles to the ground, blood oozing from the deep wound.\n");
			enemy->catch_msg(QCTNAME(archer) + " hits you with an amazingly accurate shot!\nYou stumble to the ground, blood oozing from the deep wound.\n");
			archer->tell_watcher("With an amazingly accurate shot, " + QCTNAME(archer) + " fells " + QTNAME(enemy) + "!\n" + HE_SHE(enemy) + " stumbles to the ground, blood oozing from the deep wound.\n");
			enemy->do_die(archer);
			return;
		}
		
		archer->catch_msg("With an uncanny precision, you fire an arrow straight at " + QTNAME(enemy) + ".\nIt " + ptext + "!\n");
		enemy->catch_msg("With an uncanny precision, " + QCTNAME(archer) + " fires an arrow straight at you.\nIt " + ptext + "!\n");
		archer->tell_watcher("With an uncanny precision, " + QCTNAME(archer) + " fires an arrow straight at " + QTNAME(enemy) + ".\nIt " + ptext + "!\n");
        return;
    }
}

string
show_subloc(mixed subloc, object on, object who)
{
   if(subloc!="_arrow_stunned")
      return "";
   if(who==on)
      return "You have a barbed grey-feathered arrow stuck in you!\n";
   else
      return CAP(HE_SHE(on))+" has a barbed grey-feathered arrow stuck in " + HIM_HER(on) + "!\n";
}
