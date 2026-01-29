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
#include SWS + "sw.h"
#include SWS + "spellobj.h"

private int *spells;
static string spell_verb;

static int
has_spell(string spell)
{
    return spells[member_array(spell, ALL_SPELLS)];
}


void
create_spells()
{
    set_name("spellbook");
    add_name("_sw_spell_object");
    set_adj("spellweaver");
    set_long("This is the spellweaver's spell book, it shouldn't ever be " +
        "seen, so this description doesn't matter much.\n");
    set_no_show();
    add_prop(OBJ_S_WIZINFO, "This is the spell object for the spellweaver's " +
        "guild.\n");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);

    spells = ({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
}

add_my_spells()
{
    int i;
    for (i = 0; i<sizeof(spells); i++)
    {
        if (!spells[i])
            continue;
        add_spell(ALL_SPELLS[i], ALL_SPELLS[i], SPELL_DESCRIPT[i]);
    }
}

add_a_single_spell(string spell)
{
    int i;
    i = member_array(spell, ALL_SPELLS);
    add_spell(ALL_SPELLS[i], ALL_SPELLS[i], SPELL_DESCRIPT[i]);
}

init()
{
    ::init();   
}

void
enter_env(object to, object from)
{
    if (living(to))
        add_my_spells();
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
    return MASTER + ":" + implode(spells, "");
}

init_arg(string arg)
{
    string *stuff;
    int i;
    stuff = explode(arg, "");
    for (i=0; i<sizeof(stuff); i++)
        sscanf(stuff[i], "%d", spells[i]);
}

int query_spell_time(string str)
{
    spell_verb = str;
    return 0;
}

int
query_spell_mess(string verb)
{   
	tell_about_spell( ({
		"You start to trace the rune of " + verb + " in the air.\n",
		QCTNAME(TP) + " starts to draw the rune of " + verb + ".\n",
		QCTNAME(TP) + " starts to draw an unknown rune.\n",
		QCTNAME(TP) + " starts to make a strange sign.\n" }) );
   	return 1;
}

chuck_demon(object demon, object me)
{
	set_this_player(me);
	if(!demon) /* might have been killed */ return 0;
	if(!me->find_living()) /* the coward quit or is otherwise unpresent! */
		tell_room(ENV(demon), QCTNAME(demon) + " is snatched back to its own dimension.\n");
	tell_about_spell( ({"The demon whines a little as it is called back to its" +
					" own dimension. It gives off a final snarl and looks" +
					" at you in disgust, then disappears.\n",
					"The demon whines a little as it is called back to its" +
					" own dimension. It gives off a final snarl and gives " +
					QTNAME(TP) + " a look of contempt, then disappears.\n",
					"The demon whines a little as it is called back to its" +
					" own dimension. It gives off a final snarl and looks" +
					QTNAME(TP) + " in the eyes, then disappears.\n",
					"The demon snarls a little, then disappears.\n" }), rune);
	demon->remove_object();
}

void
abort_spell(string rune, int task_result)
{
	object demon;
	int navstat, ndesc;
	if(task_result < -20) /* uh oh! */
	{
		demon = clone_object(SWS + "fail_demon");
		tell_about_spell( ({"As you summon forth the demon of the rune " + rune +
			" you loose your concentration! The demon escapes your " +
			" signs of confinment!\n", QCTNAME(TP) + " clumsily lost control" +
			" of the demon of the rune " + rune + "! It travels to destroy him!\n",
			QCTNAME(TP) + " lost control of the demon of the rune " + HE(TP) + 
			" drew.\n", QCTNAME(TP) + " lets out a surprised shriek of terror" +
			" at something.\n"}) , rune);
			
		navstat = (member_array(rune, ALL_SPELLS) + 1) * (task_result / (-10) + 1) + 10;
		demon->set_stats(({navstat + 10,navstat + 10,navstat - 10,
						navstat - 10, navstat - 10, navstat + 10 }));
		demon->set_hp(query_max_hp());
		ndesc = navstat * sizeof(DEMON_DESCRIPT) / 200;
		if(ndesc >= sizeof(DEMON_DESCRIPT)) ndesc = sizeof(DEMON_DESCRIPT) -1;
		demon->set_adj(DEMON_DESCRIPT[ndesc]);
		demon->add_adj("rune");
		demon->set_short(DEMON_DESCRIPT[ndesc] + " rune demon");
		demon->set_skill(SS_UNARM_COMBAT, (navstat> 100)?100:navstat);
		demon->set_skill(SS_DEFENCE, (navstat>100)?100:navstat);
		/* make the guy see in the dark, too */
		demon->add_prop(LIVE_I_SEE_DARK, 20); /* lots */
		demon->add_prop(LIVE_I_SEE_INVIS, 20);

		demon->move_living("M", ENV(TP), 0);

		demon->attack_object(TP);
		demon->add_prop(LIVE_O_ENEMY_CLING, TP);
		set_alarm((float)(-task_result / 2), 0.0, "chuck_demon", demon, TP, rune);
	}
	else	
		tell_about_spell(({
			"You feel that you were about to loose control of the demons so you aborted" +
			" the spell of " + rune + ".\n",
			QCTNAME(TP) + " nearly lost control of the demons of the rune " + rune + ".\n",
			QCTNAME(TP) + " came close to loosing control of the demons " + TPRO +
			" summoned.\n",
			QCTNAME(TP) + " looks slightly uneasy as something seems to have gone wrong.\n" }),
			rune);
}

mixed
cant_cast(object me, int mana)
{
    if (me->query_ghost())
        return "You can't cast that spell unless you are alive.\n";

    if (me->query_nama()<mana)
        return "You are too mentally drained to cast that spell.\n";

    if (environment(me)->query_prop(ROOM_I_NO_MAGIC))
        return "The spirits are unwilling to come here. You cannot work your magic here.\n";

    return 0;
}

void tell_about_spell(string *messages, string spell, mixed target)
{
    int i;
    mixed *inv;
    inv = FILTER_LIVE(all_inventory(ENV(TP)) - ({ TP }))
    TP->catch_msg(messages[0]);
    for (i=0; i< sizeof(inv); i++)
    {
        if(!inv[i]->query_guild_member(GUILD_NAME))
            inv[i]->catch_msg(messages[3]);
        else
            if (inv[i]->has_spell(spell))
                inv[i]->catch_msg(messages[1]);
            else
                inv[i]->catch_msg(messages[2]);
    }
    if (target)
        target->catch_msg(messages[4]);
}

/*********************ACTUAL SPELL CODE STARTS HERE***************************/

physic(string str)
{
    object *people;
    object who;
    string fail;
    int task_result;

    if (!strlen(str))
        who = this_player();
    else
    {
        people = parse_this(str, "%l");
        NF("Draw a physic rune at whom?\n");
        if (!sizeof(people))
            return 0;
        who = people[0];
    }

	if (fail=cant_cast(TP,20))
        return fail;

	task_result = resolve_task(10,({SS_ELEMENT_DEATH,SS_FORM_CONJURATION,
			SS_WIS}));
	if(task_result <= 0);
    {
    	abort_spell("psychic", task_result);
		TP->add_mana(-4);
		return 1;
    }
    
	tell_about_spell(({"You trace the rune of physic"
		+" in the air, calling forth the healing strength of the dark"
		+" spirits.\n",QCTNAME(TP)+" draws a shape in"
		+" midair, which you recognize as the Spellweaver rune"
		+" of physic.\n",QCTNAME(TP)+" draws"
		+" a Spellweaver rune in the air.\n",
		QCTNAME(TP)	+" traces a strange shape in midair with "
		+TPOS+" finger.\n"
		,"You are healed by the dark powers of the Spellweavers.\n" }),
		"physic",who);
 
	who->reduce_hit_point(-(((TP->query_skill(SS_OCCUP))/10)+
		(TP->query_skill(SS_ELEMENT_DEATH))/10)+20));
	TP->add_mana(-(20));
    return 1;
}

smother(string arg)
{
/*    this one is kind of tricky because all objects define light almost exactly
    the same way, whether they are torches, lamps, gems, or what have you, it
    is possible to code, but wouldn't always work correctly depending on how
    the offending torches etc. were coded. */
}

sting(string who)
{
    object *ob;
    object target;
    string fail;
    int task_result;
    
    if (!strlen(who))
		target=TP->query_attack();
    ob = parse_this(who, "%l");
    if ((!sizeof(ob))  && (!TP->query_attack()))
        return 0;

	/* Check that we are allowed to attack magically here. */
	if (sizeof(ob) && !TP->query_attack() && NPMATTACK(ob)) /* something resists you. */
		TP->catch_msg("As you are drawing the rune of sting at " + QTNAME(ob) +
				" something resists you.");
				
    if (sizeof(ob))
        target = ob[0];
    else
        target = TP->query_attack();
    
	if (fail = cant_cast(TP,20)) return fail;
	
	task_result = resolve_task(10,({SS_ELEMENT_DEATH,SS_FORM_CONJURATION,
		SS_INT}), target, ({SS_DEX,SS_DEFENCE}));
	if(task_result <= 0)
    {
    	abort_spell("sting", task_result);
		TP->add_mana(-5);
        return 1;
    }

	tell_about_spell(({"You trace the rune of sting in"
		+" the air, calling forth the dark spirits to strike at " + QTNAME(target) + ".\n",
		QCTNAME(TP)+" draws the Spellweaver rune of sting"
		+" in midair at.\n",QCTNAME(TP)
		+" draws a Spellweaver rune in the air.\n",
		QCTNAME(TP)+" draws a strange shape in midair.\n",
		"You feel your life zapped away as you are"
		+" stung by a dark power.\n"}),
		"sting",target);
    TP->attack_object(target);
	TP->add_mana(-(20));
    TP->add_prop(LIVE_O_SPELL_ATTACK, TO);
    return 1;
}

/***** called from lumin ********/
get_rid_of_lighter(object lighter, object me)
{
	string eff;
    set_this_player(me); /*This is necessary because of set_alarm*/
    lighter->remove_object();
    eff = (query_prop(ROOM_I_LIGHT))?("but there is still enough light to see by " +
    		"here"):" leaving the area in total darkness";
	TP->catch_msg("Your light nymph disappears, " + eff + ".\n");
	tell_room(environment(), "The light nymph disappears, " + eff + ".\n", TP);
}
/*******************************/

lumin(string arg)
{
	string fail;
	int success;
	int level;
	object lighter;
	NF("Lumin what?\n");
	if (strlen(arg))
	    return 0;
	    
	if (fail = cant_cast(TP, MANA_COST))
	    return fail;
	
	success = resolve_task(DIFFICULT, ({ SKILLS AND STATS }));
	if (success <= 0)
	{
		abort_spell("lumin", success);
		TP->add_mana(- 10);
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
	TP->add_mana(- 20);
	lighter->move(TP);
	set_alarm(TIME.0, 0.0, "get_rid_of_lighter", lighter, TP);
	return 1;
}

/***** called from darken ********/
get_rid_of_darker(object darker, object me)
{
	string eff;
	int li;
    set_this_player(me); /*This is necessary because of set_alarm*/
    darker->remove_object();
    li = ENV(TP)->query_prop(ROOM_I_LIGHT);
    eff = (li)?"and the light returns.\n ":"but it is still dark here.\n";
    TP->catch_msg("Your dark spirit disappears " + eff + ".\n");
    tell_room(environment(), "The dark spirit disappears and the darkness subsides" + (li?"":" a little") + ".\n", TP);
}
/*******************************/

darken(string arg)
{
	string fail;
	int success;
	int level;
	object darker;
	NF("Darken what?\n");
	if (strlen(arg))
	    return 0;
	    
	if (fail = cant_cast(TP, MANA_COST))
	    return fail;
	
	success = resolve_task(DIFFICULT, ({ SKILLS AND STATS }));
	if (success <= 0)
	{
		abort_spell("lumin", success);
		TP->add_mana(- 10);
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
	
	 darker=clone_object(SWS+"sprite");
	darker->add_prop(OBJ_I_LIGHT, 1 - level);
	TP->add_mana(- 20);
	darker->move(TP);
	set_alarm(TIME.0, 0.0, "get_rid_of_darker", darker, TP);
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

/*    do all the normal stuff here, I'm getting tired of this, so I'd be happy
    to help you in person, or finish up here later, but I think you probably
    get the general idea.  What you need to do to give a player a new spell 
    is call player->add_a_single_spell("name of spell"), and it should all
    work correctly, and autoload correctly.  I just realized I didn't put
    spell attack in, so here it is: */
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
		"A knife mysteriously appears in " + TPSOMETHING + " hand.\n" }), "epee");
		
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
		"A leather armour is brought to " + QTNAME(TP) + " by unseen hands.\n" }), "aegis");
		
	seteuid(getuid(TO));
	lthr = clone_object(SWG + "sw_lthr");
	lthr->move(TP);
	TP->add_mana(-80);
}

refuge(string str)
{
	string fail;
	int task_result;
	
	NF("Refuge where?");
	if(str != "home" && strlen(str)) return 0;
	
	NF("You are already at a place of refuge.\n");
	if(environment(TP) == (SWG + "startroom")) return 0;
	
	if(fail = (cant_cast(TP, -110))) return fail;
	task_result = resolve_task(TASK_DIFFICULT, ({ SS_FORM_CONJURATION, SS_ELEMENT_DEATH, SS_INT }));
	if(task_result <= 0)
	{   
		abort_spell("refuge", task_result);
		return 1;
	}
	tell_about_spell( ({
		"The demons of the rune refuge bring you to a safe place.\n",
		"The demons of the rune refuge bring " + QTNAME(TP) + " to a safe place.\n",
		"Demons teleport " + QTNAME(TP) + " to an unknown place.\n",
		QCTNAME(TP) + " suddenly disappears!\n" }), "refuge" );
	
	TP->add_mana(-110);
	TP->move_living("M", SWG+"startroom", 1);
}

visible_again(object me)
{
	if(!me) /* quit? */
		return;
	set_this_player(me);
	if(! TP->query_prop(OBJ_I_INVIS)) return; /* maybe removed cause we attacked */
	TP->remove_prop(OBJ_I_INVIS);
	tell_about_spell( ({"The veil dissolves and you are visible again.\n",
			QCTNAME(TP) + "'s veil dissolves and " + HE(TP) + " is visible again.\n",
			QCTNAME(TP) + " is visible again.\n",
			QCTNAME(TP) + " appears from nowhere.\n" }), "veil");
}

veil(string str)
{
	string fail;
	int task_result;
	
	NF("You are already invisible.\n");
	if(TP->query_prop(OBJ_I_INVIS)) return 0;
	
	if(fail = cant_cast(TP, 50)) return fail;
	
	task_result = resolve_task(TASK_DIFFICULT, ({ SS_FORM_CONJURATION, SS_ELEMENT_AIR,
										SS_SPELLCRAFT, SS_INT }));
	if(task_result  <= 0)
	{
		abort_spell("veil", task_result);
		return 0;
	}
	
	/* les veil */
	tell_about_spell(({"The demons bring you a veil of invisibility.\n",
		"The demons bring " + QNAME(TP) + " a veil of invisibility.\n",
		QCTNAME(TP) + " calls upon the spirits to make " + HIM(TP) + " invisible.\n",
		QCTNAME(TP) + " suddenly disappears!\n"}), "veil");
	TP->add_prop(OBJ_I_INVIS, 1);
	set_alarm((float)((SS_SPELLCRAFT + SS_ELEMENT_AIR) * 3 + task_result), 0.0, 
											visible_again, TP);
}

temblor(string str)
{
	string fail; int task_result, room_type;
	object *others;
	/* cause an earthquake */
	NF("Temblor what?\n");
	if(strlen(str)) return 0;
	
	if(fail = cant_cast(TP, 150)) return fail;
	
	others = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));
	
	NF("There is noone else here!\n");
	if(!sizeof(others)) return 0;
	room_type = ENV(TP)->query_prop(ROOM_I_TYPE);
	
	NF("You cannot make an earthquake here!\n");
	if(!(room_type == ROOM_NORMAL || room_type == ROOM_BEACH)) return 0;
	
	/* ok, les rock */
	tell_about_spell( ({ "The demons start to shake the ground, violently.\n",
		QCTNAME(TP) + " summons demons of temblor to shake the ground.\n",
		"Demons arrive and start to shake the ground at the command of " + QTNAME(TP) + ".\n",
		"The ground suddenly starts to shake violently.\n"
	
	

public void
spell_attack(object attacker, object target)
{
    int hurt;
    mixed *results;
    string how;

    switch(spell_verb) /* This is to allow different spell attacks, all in TO*/
    {
        case "sting":
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
