/*
	*Slender mithril-tipped pike
	*
	*A pike with an intelligence of its own. It can
	*only be wielded by someone with the proper skill,
	*alignment, and stat requirements. It has special
	*qualities that can be chosen by the wielder: defence,
	*offence and normal. Depending on the chosen stance,
	*the wielder recieves some added effect(s). There is
	*a stiff penalty for successful wielding: 1/4 of
	*current mana is drained. As well, when choosing
	*offence or defence stances, there is an ongoing
	*penalty of fatigue drain.
	*
	*Altrus, July 2005
*/ 

inherit "/std/weapon";
inherit "/lib/keep.c";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define SPD 25
#define PIKE_OFF "_pike_offence"
#define PIKE_DEF "_pike_defence"
#define PIKE_NRM "_pike_normal"
#define PIKE_LOW "_pike_lowered_skill"

int def_add; //number of defence skill points to be added in defence mode
int par_add; //number of parry skill points to be added in defence mode
int pol_add; //number of polearm skill points to be added in offence mode
int def_drp; //number of defence skill points lost due to special hit, temp
int par_drp; //number of parry skill points lost due to special hit, temp

#define FATIGUE 5
#define DELAY 75.0

int fatigue_alarm = 0;

void
create_weapon()
{
    set_name("pike");
    set_short("slender mithril-tipped pike");
	set_pshort("slender mithril-tipped pikes");
    set_adj(({"slender", "mithril-tipped"}));
    set_long("This simple, yet elegantly made pike appears to be roughly half-again longer than a man is tall, which actually seems a bit short for a normal pike. Its haft is made of polished oak, strong and a bit heavy. The tip is a work of wonder, being mithril worked into a simple spike with rather fierce-looking barbs at the base pointing back down the haft. At first glance its surface appears smooth, but as you gaze intently, shapes and patterns seemingly form and reform along the metal. The longer you gaze, the more pronounced the shapes become, and an intense pressure starts to form in your head.\n");
	
	add_item(({"shapes", "patterns", "shapes and patterns"}), "You have no hope of fully comprehending the shapes and patterns forming on the mithril tip; they form and reform too fast for you to keep them in your mind long enough to recognize anything.\n");
	add_item("haft", "The haft seems to be made of oak. Roughly half again as long as a man is tall, and little more than two fingers in width. It is flexible, but amazingly strong.\n");
	add_item(({"tip", "mithril tip"}), "The mithril tip is beautiful in its modesty. All of a foot long, the spike comes to a sharp point, with equally sharp barbs pointing back down the haft.\n");
	add_item("spike", "The spike is roughly two handspans long from where the tip is fastened to the haft of the pike. It tapers to a point so sharp, it seems only the strongest armour of the self-same metal could possibly turn the spike aside.\n");
	add_item("barbs", "Roughly a handspan in length, the barbs point in the opposite direction of the spike. It appears that if the pike were driven far enough into the victim, pulling it back out would result in massive damage.\n");
	
    add_prop(OBJ_I_WEIGHT, 5000 + random(500));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,({"This pike appears to have some sort of magical intelligence.\n",1,
    "Its effectiveness seems to be dependant on the skill and intelligence of the user, and seems to be a rather speedy weapon.\n",25,
    "It seems this pike has a rudimentary intelligence, deciding in battle whether it might lunge suddenly and hurt its opponent greatly, or perhaps trip the opponent up, thus making him less effective in a fight.\n",65 }));
    set_default_weapon((40 + random(5)), (45 + random(5)), W_POLEARM, W_IMPALE, W_BOTH, 0);
    query_keepable();
    set_wf(TO);
    set_likely_dull(1);
    set_likely_break(1);
}

void init()
{
	::init();
	add_action("focus_tactics", "focus");
	add_action("return_normal", "ease");
}

void
fatiguedrain()
{
    object p;
    p = ENV(TO);
    if (p->query_fatigue() < FATIGUE)
    {
        p->catch_msg("Feeling faint with exhaustion, you shift your grip on the " +
            short() + ", feeling a small amount of relief.\n");
        say("About to faint from exhaustion, " + QCTNAME(p) + " shifts " + HIS_HER(p) + " grip on " + HIS_HER(p) + " " + short() + ", feeling a little relief.\n",p);
    
		//Shuts off offence if currently in offence mode
		if(TP->query_prop(PIKE_OFF))
		{
			TP->set_skill_extra(SS_WEP_POLEARM, TP->query_skill_extra(SS_WEP_POLEARM) - pol_add);
			TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - SPD);
			TP->remove_prop(PIKE_OFF);
		}
		
		//Shuts off defence if currently in defence mode
		if(TP->query_prop(PIKE_DEF))
		{
			TP->set_skill_extra(SS_DEFENCE, TP->query_skill_extra(SS_DEFENCE) - def_add);
			TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) - par_add);
			TP->remove_prop(PIKE_DEF);
		}
		
        if (fatigue_alarm)
        remove_alarm(fatigue_alarm);
        fatigue_alarm = 0;
        return;
	}

    p->add_fatigue(-FATIGUE);
    p->catch_msg("The effort from your chosen stance drains you physically.\n");
    return;
}

//Calculates the skill addition, returns a value less than or equal to 100
int def_skill_calc(int skill)
{
	int add;
	
	if(skill + (skill/5) < 100)
	{
		add = (skill/5);
		return add;
	}
	
	else
	{
		add = ((skill + (skill/5)) - 100);
		return add;
	}
}

//Calculates the skill addition, returns a value less than or equal to 100
int par_skill_calc(int skill)
{
	int add;
	
	if(skill + (skill/5) < 100)
	{
		add = (skill/5);
		return add;
	}
	
	else
	{
		add = ((skill + (skill/5)) - 100);
		return add;
	}
}

//Calculates the skill addition, returns a value less than or equal to 100
int pol_skill_calc(int skill)
{
	int add;
	
	if(skill + 10 <= 100)
	{
		add = 10;
		return add;
	}
	
	else
	{
		add = ((skill + 10) - 100);
		return add;
	}
}

/*
	*Name: focus_tactics
	*
	*Descript: depending on the mode selected, changes certain
	*aspects of the wielder. 'defence' raises the wielder's
	*defence and parry 20%, or to superior guru if +20% exceeds
	*100 skill levels. 'offence' raises the wielder's pole skill
	*10 levels, or to superior guru if +10 exceeds 100 skill
	*levels; as well it adds 25 to speed. Both options incur a 
	*fatigue drain as a penalty for added combat advantage.
	*
	*Arguments: str - the string defining which mode to focus
*/
int focus_tactics(string str)
{
	//Start by getting the current value of the wielder's def/par/pol skills
	int def_skill = TP->query_skill(SS_DEFENCE);
	int par_skill = TP->query_skill(SS_PARRY);
	int pol_skill = TP->query_skill(SS_WEP_POLEARM);
	
	//Is it not even wielded?
	if(query_wielded() != TP)
	{
		write("A faint voice sounds in your mind: 'But you are not even wielding me!'\n");
		return 1;
	}
	
	//If the wielder wants to focus on defence
	else if(str == "on defence" || str == "defence")
	{
		if (TP->query_fatigue() < FATIGUE)
		{
			write("You are too tired to choose a stance.\n");
			return 1;
		}
		
		//Already focusing on defence?
		if(TP->query_prop(PIKE_DEF))
		{
			write("A faint voice sounds in your mind: 'But you are already focusing on defence. Perhaps you wish to focus on offence, or ease off this defensive stance.'\n");
			return 1;
		}
		
		//Shuts off offence if currently in offence mode
		if(TP->query_prop(PIKE_OFF))
		{
			TP->set_skill_extra(SS_WEP_POLEARM, TP->query_skill_extra(SS_WEP_POLEARM) - pol_add);
			TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - SPD);
			TP->remove_prop(PIKE_OFF);
		}
		
		//Remove the normal 'resting' position prop if that is current mode
		if(TP->query_prop(PIKE_NRM))
			TP->remove_prop(PIKE_NRM);
		
		def_add = def_skill_calc(def_skill);
		par_add = par_skill_calc(par_skill);
		
		TP->set_skill_extra(SS_DEFENCE, TP->query_skill_extra(SS_DEFENCE) + def_add);
		TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) + par_add);
		
		TP->add_prop(PIKE_DEF, 1);
		
		TP->add_fatigue(-FATIGUE);
		if (fatigue_alarm)
			remove_alarm(fatigue_alarm);
		if (!TP->query_npc())
			fatigue_alarm = set_alarm(DELAY,DELAY,&fatiguedrain());
				
		write("A faint voice sounds in your mind: 'Have no fear, I shall protect you against your foes!'\nYou shift your grip on the pike slightly, preparing to take defensive measures. You can 'ease off' this stance if you need to rest.\n");
		say(QCTNAME(TP) + " shifts " + HIS_HER(TP) + " grip on " + HIS_HER(TP) + " " + short() + ".\n");
		return 1;
	}
	
	else if(str == "on offence" || str == "offence")
	{
		if (TP->query_fatigue() < FATIGUE)
		{
			write("You are too tired to choose a stance.\n");
			return 1;
		}
		
		//Already focusing on offence?
		if(TP->query_prop(PIKE_OFF))
		{
			write("A faint voice sounds in your mind: 'But you are already focusing on offence. Perhaps you wish to focus on defence, or ease off this offensive stance.'\n");
			return 1;
		}
		
		//Shuts off defence if currently in defence mode
		if(TP->query_prop(PIKE_DEF))
		{
			TP->set_skill_extra(SS_DEFENCE, TP->query_skill_extra(SS_DEFENCE) - def_add);
			TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) - par_add);
			TP->remove_prop(PIKE_DEF);
		}
		
		//Remove the normal 'resting' position prop if that is current mode
		if(TP->query_prop(PIKE_NRM))
			TP->remove_prop(PIKE_NRM);
		
		pol_add = pol_skill_calc(pol_skill);
		
		TP->set_skill_extra(SS_WEP_POLEARM, TP->query_skill_extra(SS_WEP_POLEARM) + pol_add);
		TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) + SPD);
		TP->add_prop(PIKE_OFF, 1);
		
		TP->add_fatigue(-FATIGUE);
		if (fatigue_alarm)
			remove_alarm(fatigue_alarm);
		if (!TP->query_npc())
			fatigue_alarm = set_alarm(DELAY,DELAY,&fatiguedrain());
		
		write("A faint voice sounds in your mind: 'Yes! YES!! ATTACK!! I shall guide you, and you shall not fail!'\nYou shift your grip on the pike slightly, preparing for an all out offensive. You can 'ease off' this stance if you need to rest.\n");
		say(QCTNAME(TP) + " shifts " + HIS_HER(TP) + " grip on " + HIS_HER(TP) + " " + short() + ".\n");
		return 1;
	}
	
	//In case the wielder has not chosen a valid option
	else
	{
		write("A faint voice sounds in your mind: 'How is it you want me to help you? Focus on either offence or defence.'\n");
		return 1;
	}
}

/*
	*Name: return_normal
	*
	*Descript: Returns the wielder to a normal state... removes
	*added special cases, removes the fatigue draining.
	*
	*Arguments: str - the string 'off' for easing
*/
int return_normal(string str)
{
	if(query_wielded() != TP)
	{
		write("A faint voice sounds in your mind: 'But you are not even wielding me!'\n");
		return 1;
	}
	
	if(str != "off")
	{
		write("A faint voice sounds in your mind: 'What? Do you wish to 'ease off' your current stance?'\n");
		return 1;
	}
	
	//Shuts off offence if currently in offence mode
	if(TP->query_prop(PIKE_OFF))
	{
		TP->set_skill_extra(SS_WEP_POLEARM, TP->query_skill_extra(SS_WEP_POLEARM) - pol_add);
		TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - SPD);
		TP->remove_prop(PIKE_OFF);
	}
	
	//Shuts off defence if currently in defence mode
	if(TP->query_prop(PIKE_DEF))
	{
		TP->set_skill_extra(SS_DEFENCE, TP->query_skill_extra(SS_DEFENCE) - def_add);
		TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) - par_add);
		TP->remove_prop(PIKE_DEF);
	}
	
	TP->add_prop(PIKE_NRM, 1);
	write("A faint voice sounds in your mind: 'Yes, of course. One can not push to the limit at all times... Rest now... Rest.'\nYou ease off your grip on the pike, taking a moment to rest.\n");
	say(QCTNAME(TP) + " eases " + HIS_HER(TP) + " grip on " + HIS_HER(TP) + " " + short() + ", looking a little less strained.\n");
	
	if (fatigue_alarm)
	{
		remove_alarm(fatigue_alarm);
		fatigue_alarm = 0;
	}
	
	return 1;
}

/*
	*Name: wield
	*
	*Descript: Redefined wielding function. Imposes hefty restrictions
	*for prospective wielders. Must have 90 pole skill(superior master),
	*must have 370 alignment(nice) or above, must have 125 intelligence
	*(somewhere around bright). If successfully wielded, drains a quarter
	*of the users current mana.
	*
	*Arguments: obj - the polearm to be wielded
*/
public mixed
wield(object obj)
{
    int mana = TP->query_max_mana();
	
	//Check for requirements - high pole skill, good alig, moderate intelligence
	if((TP->query_skill(SS_WEP_POLEARM) >= 90) && (TP->query_alignment() >= 460) && (TP->query_stat(3) >= 125))
    {
		write("As you take a firm grip on the pike, a faint voice sounds in your mind: 'At last, one who is worthy of the power I hold!'\nA faint voice sounds in your mind: 'I can grant you great success in battle. Should you wish to fight more effectively, you might try to 'focus' on defence or offence.'\n");
		say(QCTNAME(TP) + " looks as if " + HE_SHE(TP) + " is listening intently to something... To what you can not be certain.\n" + capitalize(HE_SHE(TP)) + " takes a firm grip on " + HIS_HER(TP) + " " + short() + ".\n");
		if(TP->query_mana() - (mana/4) < 0)
			TP->set_mana(0);
		else
			TP->set_mana(mana-(mana/4));
		TP->add_prop(PIKE_NRM, 1);
		return 1;
    }
    
	else
	{
		return "A faint voice sounds in your mind: 'You are not worthy of me, begone!'\n";
	}
}

/*
	*Name: unwield
	*
	*Descript: Redefined unwielding function. Removes any conditions
	*and props set by the current mode of the pike.
	*
	*Arguments: obj - the polearm to be unwielded
*/
public mixed
unwield(object obj)
{
    //Shuts off offence if currently in offence mode
	if(TP->query_prop(PIKE_OFF))
	{
		TP->set_skill_extra(SS_WEP_POLEARM, TP->query_skill_extra(SS_WEP_POLEARM) - pol_add);
		TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - SPD);
		TP->remove_prop(PIKE_OFF);
	}
	
	//Shuts off defence if currently in defence mode
	if(TP->query_prop(PIKE_DEF))
	{
		TP->set_skill_extra(SS_DEFENCE, TP->query_skill_extra(SS_DEFENCE) - def_add);
		TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) - par_add);
		TP->remove_prop(PIKE_DEF);
	}
	
	//Remove the normal 'resting' prop, if that is the current mode
	if(TP->query_prop(PIKE_NRM))
		TP->remove_prop(PIKE_NRM);
    
	write("A faint voice sounds in your mind: 'Our work may be done for now, but there is much evil left in the world, remember me when the time comes to take up the fight again!'\nYou regretfully release your hold on the pike.\n");
	say(QCTNAME(TP) + " gets a distant, almost regretful, look in " + HIS_HER(TP) + " eyes as " + HE_SHE(TP) + " releases " + HIS_HER(TP) + " pike.\n");
	
	if (fatigue_alarm)
	{
		remove_alarm(fatigue_alarm);
		fatigue_alarm = 0;
	}
	
    return 1;
}

//Removes the lowered-skill prop, called from 'reset_skills'
//the target's skills have reset... like a temporary reprieve
void reset_trip(object target)
{
	target->remove_prop(PIKE_LOW);
}

//Resets the skill levels in the target, calls the timer
//to remove the lowered-skill prop
void reset_skills(object target, object attacker)
{
	if (objectp(target))
    {
		target->set_skill_extra(SS_DEFENCE, target->query_skill_extra(SS_DEFENCE) + def_drp);
		target->set_skill_extra(SS_PARRY, target->query_skill_extra(SS_PARRY) + par_drp);
		target->catch_msg("You seem to have recovered from being tripped up.\n");
	        tell_room(ENV(target), QCTNAME(target) + " seems to have recovered from being tripped up.\n", target, target);
		set_alarm(30.0, 0.0, &reset_trip(target));
	}
}

int try_hit(object enemy)
{
    int skill, stat, skill_e, stat_e, pen, perf, pdam;
    mixed *hitresult;
    object me, enmy;
    string text, ptext;

    me = query_wielded();
    enmy = me->query_enemy();
	stat = me->query_stat(SS_STR);
    skill = me->query_skill(SS_WEP_POLEARM);
    skill_e = enemy->query_skill(SS_DEFENCE);
    stat_e = enemy->query_stat(SS_DEX);
    
	// We want to cap the stat at around 100 if the stats get too
    // high (above 110)
    if (stat > 110)
        stat = 90 + random(20);
    if (stat_e > 110)
        stat_e = 90 + random(20);
    
    if(me->query_prop(PIKE_OFF))
	stat = (stat +100);
    
	if ((random(100) < (skill/2)) && (random(skill+stat) > random(skill_e+stat_e)))
    {
		if(random(2))
		{
			if(!enemy->query_prop(PIKE_LOW))
			{
				def_drp = (enemy->query_skill(SS_DEFENCE)/5);
				par_drp = (enemy->query_skill(SS_PARRY)/5);
				enemy->set_skill_extra(SS_DEFENCE, enemy->query_skill_extra(SS_DEFENCE) - def_drp);
				enemy->set_skill_extra(SS_PARRY, enemy->query_skill_extra(SS_PARRY) - par_drp);
				enemy->add_prop(PIKE_LOW, 1);
				set_alarm(30.0, 0.0, &reset_skills(enemy, me));
				me->catch_msg("With all the speed you can muster, you whip the butt-end of the pike around, tripping up " + QTNAME(enemy) + "!\n");
				enemy->catch_msg(QCTNAME(me) + " suddenly whips " + HIS_HER(me) + " pike around with blinding speed, tripping you up!\n");
				me->tell_watcher(QCTNAME(me) + " suddenly whips " + HIS_HER(me) + " pike around with blinding speed, tripping up " + QTNAME(enemy) + "!\n");
				return 1;
			}
		}
		
		/* Tell wizard the enemy's hp before the special. */
    if(me->query_wiz_level())
    {
        me->catch_tell("WIZINFO: Enemy's current hp is: " + enemy->query_hp()
+ "!\n");
    }
	
		pen = F_PENMOD(40+random(stat/4), skill);
		hitresult = enemy->hit_me(pen, W_IMPALE, me, -1);
		perf = hitresult[2] * 100 / pen;
		
		ptext = "weakly";
		if (perf > 15)
			ptext = "harshly";
		if (perf > 30)
			ptext = "brutally";
		if (perf > 45)
			ptext = "savagely";
		if (perf > 60)
			ptext = "viciously";
		if (perf > 75)
			ptext = "grievously";
		
		if (enemy->query_hp() <= 0)
		{
			enemy->command("scream");
			me->catch_msg("With lightning fast speed, you plunge your " + short() + " deep into " + QTNAME(enemy) + "!\n" + QCTNAME(enemy) + " dies in an overflowing pool of blood!\n");
			enemy->catch_msg("With unbelievable speed, " + QCTNAME(me) + " plunges " + HIS_HER(me) + " " + short() + " deep into your body!\nAs blood flows freely from the open wound, you feel your life passing.\n");
			me->tell_watcher("With unbelievable speed, " + QCTNAME(me) + " plunges " + HIS_HER(me) + " " + short() + " deep into " + QTNAME(enemy) + "!\n" + QTNAME(enemy) + " dies in an overflowing pool of blood!\n");
			enemy->do_die(me);
			return 0;
		}
		
		me->catch_msg("With suprising speed and accuracy, you pierce " + QTNAME(enemy) + " with your " + short() + "!!\nRipping it back out, the barbs wound " + HIM_HER(enemy) + " " + ptext + "!\n");
		enemy->catch_msg("With suprising speed and accuracy, " + QCTNAME(me) + " pierces you with " + HIS_HER(me) + " " + short() + "!\nAs " + HE_SHE(me) + " rips it back out, the barbs wound you " + ptext + "!\n");
		me->tell_watcher("With suprising speed and accuracy, " + QCTNAME(me) + " pierces " + QTNAME(enemy) +" with " + HIS_HER(me) + " " + short() + "!\nAs " + QCTNAME(me) + " rips it back out, the barbs wound " + QTNAME(enemy) + " " + ptext + "!\n");
	
	/*Tell wizard new hp.*/
    if(me->query_wiz_level())
    {
        me->catch_tell("WIZINFO: Enemy's new hp is: " + enemy->query_hp() +
"!\n");
	}
	
	}
	
	return 1; /* Try hit */
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}