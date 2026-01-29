/* As always, if you have any questions about what I've done here, feel
 * free to ask
 * Quetzl
 */


inherit "/std/spells";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <comb_mag.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

void
create_spells()
{
    set_name("spellbook");
    set_adj("cult");
    set_long("This is the spell book of the Cult of Melkor, it shouldn't ever be " +
        "seen, so this description doesn't matter much.\n");
    set_no_show();
    add_prop(OBJ_S_WIZINFO, "This is the spell object for the Cult of Melkor guild.\n");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

/* 
 * this function checks what spells a player can have according to his favor
 * points.
 */
public
update_spells(object me) 
{
	int favpoint, i;
	
	for (i= 0; i< sizeof(ALL_SPELLS); i++)
		remove_spell(ALL_SPELLS[i]);
	
	favpoint = me->query_favor_points();
	for(i = 0; i < sizeof(ALL_SPELLS); i++)
		if(favpoint >= FP_SPELLS[i]) /* the favor points required for that spell */
			add_spell(ALL_SPELLS[i], ALL_SPELLS[i], SPELL_DESCRIPT[i]);
}	

void
enter_env(object to, object from)
{
    if (living(to))
    	update_spells(to);
    ::enter_inv(to, from);
}

void leave_env(object from, object to)
{
    int i;

    if (living(from))
        for (i= 0; i< sizeof(ALL_SPELLS); i++)
            remove_spell(ALL_SPELLS[i]);
    ::leave_env(from, to);
}

query_auto_load()
{
    return MASTER;
}

int query_spell_time(string str)
{
    return TIME_SPELLS[member_array(str, ALL_SPELLS)];
}

int
query_spell_mess(string verb)
{
    mixed *inv;
    int i;
    
    inv = FILTER_LIVE(all_inventory(environment(TP)) - ({ TP }));
    TP->catch_msg("You ask Melkor to grant you " + verb + ".\n");
    for( i = 0; i < sizeof(inv); i++)
        if(!inv[i]->query_guild_member(GUILD_NAME))
            inv[i]->catch_msg(QCTNAME(TP) + " starts speaking in tongues.\n");
        else
        	inv[i]->catch_msg(QCTNAME(TP)+" asks Melkor to grant " + HIM(TP) + " " + verb + ".\n");
   	return 1;
}

void
abort_spell(string rune)
{
	tell_about_spell(({
		"You feel that you were about to loose control of the demons so you aborted" +
		" the spell of " + rune + ".\n",
		QCTNAME(TP) + " nearly lost control of the demons of the rune " + rune + ".\n",
		QCTNAME(TP) + " came close to loosing control of the demons " + TPRO +
		" summoned.\n",
		QCTNAME(TP) + " looks slightly uneasy as something seems to have gone wrong.\n" }));
}

mixed
cant_cast(object me, int mana)
{
    if (me->query_ghost())
        return "You can't cast that spell unless you are alive.\n";

    if (me->query_nama()<mana)
        return "You are too mentally drained to cast that spell.\n";

    if (environment(me)->query_prop(ROOM_I_NO_MAGIC))
        return "Something in the room interfers with the magic.\n";

    return 0;
}

void tell_about_spell(string *messages, object target, string target_str)
{
    int i;
    mixed *inv;
    inv = FILTER_LIVE(all_inventory(ENV(TP)) - ({ TP }))
    TP->catch_msg(messages[0]);
    for (i=0; i< sizeof(inv); i++)
    {
        if(!inv[i]->query_guild_member(GUILD_NAME))
            inv[i]->catch_msg(messages[2]);
        else
            inv[i]->catch_msg(messages[1]);
    }
    if (target)
        target->catch_msg(target_str);
}

/*********************ACTUAL SPELL CODE STARTS HERE***************************/

pain(string str)
    object *ob;
    object target;
    string fail;
    if (!strlen(who))
		target = TP->query_attack();
    ob = parse_this(who, "[at] %l");
    if ((!sizeof(ob))  && (!target))
        return 0;
    if (sizeof(ob))
        target = ob[0];
    
	if (fail = cant_cast(TP,MANA_SPELLS[CMS_PAIN]))
		return fail;
	if (resolve_task(10,({SS_ELEMENT_DEATH,SS_FORM_CONJURATION,SS_INT}),
		target,
		({SS_DEX,SS_DEFENCE}))<=0)
        ({ TARGET: SKILLS AND STATS })) <= 0)
    {
    	abort_spell("pain");
		TP->add_mana(-5);
        return 1;
    }

	/* the tell_about_spell strings are made so that damage info can be supplied in the
		attack object */
	tell_about_spell(({
		"Melkor grants you a spell of pain, which you direct at " + QTNAME(target) + ". ",
		"Melkor grants " + QTNAME(TP) + " a spell of pain, which " + HE(TP) + " directs at "+
						QTNAME(target) + ". ",
		QCTNAME(TP) + " points a deadly finger at " + QTNAME(target) + ". " }),
		target,
		QCTNAME(TP) + " points at you sending waves of pain down your spine.\n");
    TP->attack_object(target);
	TP->add_mana(-(20));
    TP->add_prop(LIVE_O_SPELL_ATTACK, TO);
    return 1;

smother(string arg)
{
}

sting(string who)
{
}

/***** called from luminate ********/
get_rid_of_lighter(object lighter, object me)
{
	string eff;
    set_this_player(me); /*This is necessary because of set_alarm*/
    lighter->remove_object();
    eff = (query_prop(ROOM_I_LIGHT))?"but there is still enough light to see by " +
    		"here":"leaving the area in total darkness";
	TP->catch_msg("Your illusion of light is broken " + eff + ".\n");
	tell_room(environment(), "The light dims " + eff + ".\n", TP);
}
/*******************************/

luminate(string arg)
{
	string fail;
	int success;
	int level;
	object lighter;
	
	NF("Luminate what?\n");
	if (strlen(arg))
	    return 0;
	    
	if (fail = cant_cast(TP, MANA_SPELLS[CMS_LUMINATE]))
	    return fail;
	
	success = resolve_task(DIFFICULT, ({ SKILLS AND STATS }));
	if (success <= 0)
	{   
		abort_spell("luminate", success);
		DO_SPELL_FAILED_STUFF_HERE
	    return 1;
	}
	level = 1;
	if (success > 30)
	    level = 2;
	if (success > 50)
	    level = 3;
	if (success > 80)
	    level = 4; 
	
	tell_about_spell("You trace the rune of lumin in midair,"
		+" calling forth an unholy luminescence.\n",
		QCTNAME(TP)+" draws the Spellweaver rune of lumin"
		+" in the air.\n",
		QCTNAME(TP)+" draws a spellweaver rune in midair"
		+".\n",
		QCTNAME(TP)+" traces a strange shape in the"
		+" air before "+TPRO+".\n"  }),
		"lumin")
	
	seteuid(getuid(TO));	
	
	 lighter=clone_object(SWS+"sprite");
	lighter->add_prop(OBJ_I_LIGHT, level);
	TP->add_mana(- MANA_COST);
	lighter->move(TP);
	set_alarm(TIME.0, 0.0, "get_rid_of_lighter", lighter, TP);
	return 1;
}

vigilant(string arg)
{
    string fail;
    /* If you want this castable on others, change this line */
    NF("Vigilant what?\");
    if (strlen(arg))
        return 0;

    if (fail = (cant_cast(TP, MANA_COST)))
        return fail;

    if (resolve_task(DIFFICULTY, ({ SKILLS AND STATS })) <= 0)
    {
		abort_spell("vigilant");
        return 1;
    }

    do all the normal stuff here, I'm getting tired of this, so I'd be happy
    to help you in person, or finish up here later, but I think you probably
    get the general idea.  What you need to do to give a player a new spell 
    is call player->add_a_single_spell("name of spell"), and it should all
    work correctly, and autoload correctly.  I just realized I didn't put
    spell attack in, so here it is:
}

epee(string str)
{
	string fail;
	object knife;
	
	NF("Epee what?");
	if(strlen(str)) return 0;
	
	if(fail = (cant_cast(TP, -70))) return fail;
	if(resolve_task(TASK_ROUTINE, ({ SS_FORM_CONJURATION, SS_ELEMENT_DEATH, SS_INT })) <= 0)
	{   
		abort_spell("epee");
		return 1;
	}
	/* ok, make the thing */
	tell_about_spell( ({
		"The demons create a Spellweaver knife in your hand.\n",
		QCTNAME(TP) + " calls upon the rune epee to create a Spellweaver " +
		"knife in " + TPOS + " hand.\n",
		QCTNAME(TP) + " calls upon the demons to create a knife in " + TPOS + " hand.\n",
		"A knife mysteriously appears in " + TPSOMETHING + " hand.\n");
		
	seteuid(getuid(TO));
	knife = clone_object(SWG + "sw_knife");
	knife->move(TP);
	TP->add_mana(-70);
}

aegis(string str)
{
	string fail;
	object lthr;
	
	NF("Aegis what?");
	if(strlen(str)) return 0;
	
	if(fail = (cant_cast(TP, -80))) return fail;
	if(resolve_task(TASK_ROUTINE, ({ SS_FORM_CONJURATION, SS_ELEMENT_DEATH, SS_INT })) <= 0)
	{   
		abort_spell("aegis");
		return 1;
	}
	/* ok, make the thing */
	tell_about_spell( ({
		"The demons fashion a leather armour of the Spellweavers to your fit.\n",
		QCTNAME(TP) + " uses the rune aegis to create a leather armour.\n",
		QCTNAME(TP) + " calls upon the demons to create a leather armour.\n",
		"A leather armour is brought to " + QTNAME(TP) + " by unseen hands.\n" }));
		
	seteuid(getuid(TO));
	lthr = clone_object(SWG + "sw_lthr");
	lthr->move(TP);
	TP->add_mana(-80);
}

refuge(string str)
{
	string fail;
	
	NF("Refuge where?");
	if(str != "home" && strlen(str)) return 0;
	
	NF("You are already at a place of refuge.\n");
	if(environment(TP) == (SWG + "startroom")) return 0;
	
	if(fail = (cant_cast(TP, -110))) return fail;
	if(resolve_task(TASK_DIFFICULT, ({ SS_FORM_CONJURATION, SS_ELEMENT_DEATH, SS_INT })) <= 0)
	{   
		abort_spell("refuge");
		return 1;
	}
	tell_about_spell( ({
		"The demons of the rune refuge bring you to a safe place.\n",
		"The demons of the rune refuge bring " + QTNAME(TP) + " to a safe place.\n",
		"Demons teleport " + QTNAME(TP) + " to an unknown place.\n",
		QCTNAME(TP) + " is suddenly taken away by unseen forces!\n" }) );
	
	TP->add_mana(-110);
	TP->move_living("M", SWG+"startroom", 1);
}	



public void
spell_attack(object attacker, object target)
{
    int hurt, favor;
    mixed *results;
    string how;

	favor = attacker->query_favour_points(); /* if the caster isn't a cult member .. well */
    switch(spell_verb) /* This is to allow different spell attacks, all in TO*/
    {
        case "pain":
            hurt = F_PENMOD(putyourpenhere, put average skills/stats here);
            hurt -= hurt * target->query_magic_res(whatkind)/100;
            /* Use the above line if the magic can be resisted, whatkind 
             * should be one of the MAGIC_I_RESIST?? properties
             */
            results = target->hit_me(hurt, 0, attacker, 0);
            /* results[0] contains a percentage of success, you can use this
             * to generate different messages based on how badly the caster
             * hurt the target.
             */
            break;
        case "other spells go here etc":
    }
    if (target->query_hp() <= 0)
        target->do_die(attacker);
    /* If you want, this can be put in the switch statement, and generate
     * special victory messages to the player when they kill someone
     * In that case, you would use if (target->query_hp() <= 0) {do stuff,
     * then call do_die in target. then return; }
     */
    return;
}
