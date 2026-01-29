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
#include "/d/Rhovanion/farlong/work/sw/s_s/sw.h"

#define ALL_SPELLS                                                \
                 ({ "physic", "smother", "sting", "vigilant", "herald",\
			"lumin",\
                    "darken", "cicerone", "specie", "veil", "cosmos",   \
                    "epee", "aegis", "temblor", "refuge", "phobia",     \
                    "thrall", "revenant", "espy", "dispel" })

#define SPELL_DESCRIPT({"heal yourself or others with dark power",\
	"extinguish flaming light sources","sting an enemy",\
	"cast a spell of protection","send a messenger to those you know",\
	"light up the area","make the room dark","darkhearing",\
	"conjure coins","make yourself invisible","send a mental message to anyone",\
	"conjure a weapon for yourself","conjure armour for yourself",\
	"cause an earthquake","call a spirit to take you home",\
	"cause an enemy to flee","summon a spirit to fight for you",\
	"steal the life of an enemy","locate someone",\
	"dispel existing magic"})

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

mixed
cant_cast(object me, int mana)
{
    if (me->query_ghost())
        return "You can't cast that spell unless you are alive.\n";

    if (me->query_nama()<mana)
        return "You are too mentally drained to cast that spell.\n";

    if (environment(me)->query_prop(ROOM_I_NO_MAGIC))
        return "Something in the area prevents you from casting that spell.\n";

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

	if(resolve_task(10,({SS_ELEMENT_DEATH,SS_FORM_CONJURATION,
			SS_WIS}))<=0)
    {
		write("You failed to cast the spell correctly.\n");
		TP->add_mana(-4);
		return 1;
    }
    
	tell_about_spell(({break_string("You trace the rune of physic"
		+" in the air, calling forth the healing strength of the dark"
		+" spirits.\n",75),break_string(QCTNAME(TP)+" draws a shape in"
		+" midair, which you recognize as the Spellweaver rune"
		+" of physic.\n",75),break_string(QCTNAME(TP)+" draws"
		+" a Spellweaver rune in the air.\n",75),
		break_string(QCTNAME(TP)
		+" traces a strange shape in midair with "
		+TPOS+" finger.\n",75)
		,"You are healed by the dark powers of the Spellweavers.\n" }),
		"physic",who);
 
	who->reduce_hit_point(-(((TP->query_skill(SS_OCCUP))/10)+
		(TP->query_skill(SS_ELEMENT_DEATH))/10)+20));
	TP->add_mana(-(20));
    return 1;
}

smother(string arg)
{
    this one is kind of tricky because all objects define light almost exactly
    the same way, whether they are torches, lamps, gems, or what have you, it
    is possible to code, but wouldn't always work correctly depending on how
    the offending torches etc. were coded.
}

sting(string who)
{
    object *ob;
    object target;
    string fail;
    if (!strlen(who))
		target=TP->query_attack();
    ob = parse_this(who, "%l");
    if ((!sizeof(ob))  && (!TP->query_attack()))
        return 0;
    if (sizeof(ob))
        target = ob[0];
    else
        target = TP->query_attack();
    
	if (fail=cant_cast(TP,20)
		return fail;
	if (resolve_task(10,({SS_ELEMENT_DEATH,SS_FORM_CONJURATION,SS_INT}),
		target,
		({SS_DEX,SS_DEFENCE}))<=0)
        ({ TARGET: SKILLS AND STATS })) <= 0)
    {
		write("You fail to cast the sting spell correctly.\n");
		TP->add_mana(-5);
        return 1;
    }

	tell_about_spell(({break_string("You trace the rune of sting in"
		+" the air, calling forth the dark spirits.\n",75),
		break_string(QCTNAME(TP)+" draws the Spellweaver rune of sting"
		+" in midair.\n",75),break_string(QCTNAME(TP)
		+" draws a Spellweaver rune in the air.\n",75),
		QCTNAME(TP)+" draws a strange shape in midair.\n",
		break_string("You feel your life zapped away as you are"
		+" stung by a dark power.\n",75)}),
		"sting",target);
    TP->attack_object(target);
	TP->add_mana(-(20));
    TP->add_prop(LIVE_O_SPELL_ATTACK, TO);
    return 1;
}

/***** called from lumin ********/
get_rid_of_lighter(object lighter, object me)
{
    set_this_player(me); /*This is necessary because of set_alarm*/
    do some writes and says if you want.
    lighter->remove_object();
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

	tell_about_spell(break_string("You trace the rune of lumin in midair,"
		+" calling forth an unholy luminescence.\n",75),
		break_string(QCTNAME(TP)+" draws the Spellweaver rune of lumin"
		+" in the air.\n",75),
		break_string(QCTNAME(TP)+" draws a spellweaver rune in midair"
		+".\n",75),
		break_string(QCTNAME(TP)+" traces a strange shape in the"
		+" air before "+TPRO+".\n",75)  }),
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
		write("You failed to cast the spell of vigilant correctly.\n",75));

        return 1;
    }

    do all the normal stuff here, I'm getting tired of this, so I'd be happy
    to help you in person, or finish up here later, but I think you probably
    get the general idea.  What you need to do to give a player a new spell 
    is call player->add_a_single_spell("name of spell"), and it should all
    work correctly, and autoload correctly.  I just realized I didn't put
    spell attack in, so here it is:
}

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
