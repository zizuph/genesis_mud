/*
 * The standard inheritable NPC for the Union.
 *
 * The Union member will remember each living it has seen
 * (with the exception of wizards and JR's) who pass by,
 * and any other Union member can ask it to list those it
 * has seen and to describe them.
 *
 * Cirion, Ferbruary 22, 1998
 *
 * Updated: Lilith Aug 2002: npcs clear prohibit bits on 'friends'
 *          Lilith Apr 2003: and 'accepted', and greets them as well.
 *          Lucius Apr 2005: Changed how the information is relayed.
 *          Lucius May 2007: Changed spy info and removed corpse bits
 *                           as they are now done by the shadow and
 *                           a new corpse object.
 *          Zielia Jun 2009: if the krynn plague object enters the npc, 
 *                           it will be cured. Union npcs have immunity,
 *                           especially as the anti-magic in the halls 
 *                           makes them difficult to cleanse.
 *          Lucius Jul 2017: Re-coded.
 *          Lilith Oct 2021: Updated specials code to look for the prop 
 *                           "_npc_flinging_knife"instead of just "knife" 
 *                           since the npcs and can't fling wielded knives, 
 *                           so they weren't switching to slash when they 
 *                           ran out of knives to fling.
 *                           Also updated time_met_desc to reflect longer up times.
 *
 */
#pragma strict_types

inherit "/d/Avenir/inherit/monster";

#include <math.h>
#include <files.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>

#include "../defs.h"
#include "/d/Avenir/include/relation.h"

#undef CLEANUP

private static object union_npc_home, ceremony_room;
private static object *respected = ({ });

/* Mapping of all the passer-by's for this NPC  */
/* During this reboot. It will be of the form:  */
/* ([ "name" : ({ (int)known, (int)when, "short", "long", "name" }) ]); */
private static mapping passer_by = ([]);

#ifdef CLEANUP
private static int cleanup_alarm;

public void
perform_cleanup(void)
{
    /* Two weeks good? */
    int limit = (60 * 60 * 24 * 14),
	now = time();

    cleanup_alarm = 0;
    foreach(string who, mixed data: passer_by)
    {
	if ((data[1] + limit) < now)
	    m_delkey(passer_by, who);
    }
}
#endif

public int
query_met(mixed who)
{
    string name; 
    int known = 0;

    if (objectp(who))
	name = who->query_real_name();
    else if (stringp(who))
	name = lower_case(who);

    if (passer_by[name])
	known = passer_by[name][0];

    return known;
}

/* 
 *  Make things happen when I meet the right people.
 */
public void
meet_living(object who, int known)
{
    /* Don't notice npcs */
    if (!query_interactive(who))
	return;

    /* If we can't see them, we can't remember them */
    if (!CAN_SEE(this_object(), who) ||
	!CAN_SEE_IN_ROOM(this_object()))
	return;

    /* Don't do this for wizards or JR's */
#ifndef DEBUG
    if ((who->query_wiz_level()) || wildmatch("*jr", who->query_name()))
	return;
#endif

    /* I always know members of the Union. */
    if (IS_MEMBER(who))
	known = 1;

    string name = who->query_real_name();

    /* Don't magically forget names upon next encounter. */
    if (passer_by[name] && passer_by[name][0])
	known = 1;

    passer_by[name] = ({ known, time(), who->query_nonmet_name(),
	who->long(this_object()), name });

#ifdef CLEANUP
    if (!cleanup_alarm && !random(5))
	cleanup_alarm = set_alarm(itof(5), 0.0, perform_cleanup);
#endif

#ifdef DEBUG
    command("say meet_living() called for "+ name +"; known=="+ known);
#endif
}

/*
 * Convert a string to an array of past
 * tense descriptions.
 */
private string *
convert_string_past(mixed *data)
{
    int i;
    string *ret;

    if (!sizeof(data))
	return ({ });

    ret = explode(data[3], " ");
    foreach(string word: ret)
    {
	switch(word)
	{   // "He is a..." to "He was a..."
	case "is":	ret[i] = "was";		break;
	    // "He has scars..." to "He had scars..."
	case "has":	ret[i] = "had";		break;
	    // "He looks happy..." to "He looked happy..."
	case "looks":	ret[i] = "looked";	break;
	    // "He seems to be..." to "He seemed to be..."
	case "seems":	ret[i] = "seemed";	break;
	    // "His eyes are..." to "His eyes were..."
	case "are":	ret[i] = "were";	break;
	    // "He wears ..." to "He wore..."
	case "wears":	ret[i] = "wore";	break;
	    // "He holds ..." to "He held..."
	case "holds":	ret[i] = "held";	break;
	    // "presenting himself as..." to "who presented himself as..."
	case "presenting":  ret[i] = "who presented";	break;
	    // Check if we need to sub the name.
	default:
	    word = lower_case(word);
	    if (!data[0] && wildmatch("*"+ data[4] +"*", word))
		ret[i] = data[3];
	    break;
	}

	i++;
    }

    return explode(implode(ret, " "), "\n");
}

/*
 * Give a nice listing of those people who I have
 * encountered, based on whether I know them or not.
 *
 * E.g., "a long-armed elf, Cirion, and a sultry dark-skinned human"
 */
private string
list_met(void)
{
    string *descs, *indices = m_indices(passer_by);

    if (!sizeof(indices))
	return "Nobody";
    else
	descs = ({ });

    foreach(string who: indices)
    {
	mixed elem = passer_by[who];

	if (elem[0] == 0)
	    descs += ({ elem[2] });
	else
	    descs += ({ capitalize(who) });
    }

    if (sizeof(descs) == 1)
	return "Only " + descs[0];
    else
	return COMPOSITE_WORDS(descs);
}

// for debugging...
public void
dump_met(void)
{
    dump_mapping(passer_by);
}

/*
 * Describe how long ago I met someone.
 */
public string
time_met_desc(int tm)
{
    /* How long ago I met the person, in minutes. */
    int how_long_ago = (time() - tm) / 60;

    switch(how_long_ago)
    {
    case 0..2:
	return "just now";
    case 3..7:
	return "very recently";
    case 8..20:
	return "fairly recently";
    case 21..60:
	return "in the past hour";
    case 61..120:
	return "two hours ago, maybe less";
    case 121..250:
	return "no more than four hours ago";
	case 251..480:
	return "eight hours ago, more or less";
	case 481..720:
	return "within the past sybarun day";
	case 721..1500:
	return "a sybarun day or two ago";
	case 1501..4500:
	return "a handful of days ago, perhaps";
	case 4501..8600: 
	return "within the last wei";
    default:
	return "more than a wei ago, perhaps closer to two.";
    }
}

private mixed *
find_met_desc(string desc)
{
    if (!strlen(desc))
	return ({ });

    desc = lower_case(desc);

    foreach(string who, mixed data: passer_by)
    {   // if they asked about the name, describe the
	// person ONLY IF WE HAVE MET THEM (so people
	// cannot obtain a name they should not be able to).
	if ((desc == who) && (data[0] > 0))
	    return data;
	// else did we ask about the short description?
	else if (desc == data[2])
	    return data;
	// Can't find it? Let's try once again, this time doing
	// a partial string comparison so we can catch
	// "gnome" in "blue-eyed male gnome".
	else if (wildmatch("*"+ desc +"*", data[2]))
	    return data;
    }

    return ({ });
}

/*  
 * This makes the npc describe who it has met.
 */
private void
describe_met(string person)
{
    mixed *elems;
    string *descs;

    if (!IS_MEMBER(TP) || LEVEL(TP) < NORMAL)
    {
	command("say Why should I tell you that?");
	return;
    }

    // can't find the decription...
    if (!sizeof(elems = find_met_desc(person)))
    {
	command("usto "+ OB_NAME(TP) +
	  " I have met no \"" + person + "\" recently.");
	return;
    }

    descs = convert_string_past(elems);

    // describe how long ago we met...
    command("usto "+ OB_NAME(TP) +
      " The encounter occured " + time_met_desc(elems[1]) + "...\n");

    // Give the long description of the person...
    foreach(string str: descs)
	write(str + "\n");

    write("\n");
}

/*
 * VBFC to ask the NPC about the list of people I have met.
 */
public string
ask_about_encountered(void)
{
    if (!IS_MEMBER(TP) || (LEVEL(TP) < NORMAL))
	return "say That is none of your business.";

    command("usto "+ OB_NAME(this_player()) +
	" Today I have encountered: ");

    write(list_met() + ".\n");
    return "";
}

public string
help_union(void)
{
    if (!IS_MEMBER(TP))
    {
	command("say Surely you jest?");
	return "";
    }

    command("us Of course.");
    command("assist "+ OB_NAME(TP));
    return "";
}

/* Make the NPC a member of the Union. Give them    */
/* the shadow, soul, all that jazz.                 */
static void
make_member(void)
{
    object arm = clone_object(TOKEN_OBJ);
    arm->move(TO, 1);

    arm = clone_object(OCC_SHADOW);
    if (arm->shadow_me(TO, OCC_TYPE, OCC_STYLE, OCC_NAME) != 1)
    {
	write("Unable to be a Shadow Warrior.\n");
	SECURITY->do_debug("destroy", arm);
    }
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    // default home is where they are first cloned to
    if (!union_npc_home)
	union_npc_home = to;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    // Union NPCs are immune to krynn's plague
    if (ob->id("nasty_sickness")) 
    {
	ob->cure_poison( ({"all"}), 999 );   
	ob->timeout();
    }
}

public void
set_union_npc(void)
{
    reset_euid();

    add_prop(CONT_I_HEIGHT, 200);
    set_appearance(60 + random(40));

    set_skill(SS_FLING, 100);
    set_skill(SS_SWAY, 100);
    set_skill(SS_SLASH, 100);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_KNIFE, 100);

    // give some virtues. An NPC with a name will always have
    // the same virtues... ;)
    set_skill(US_DIGNITY, 500 + NAME_TO_RANDOM(query_name(), 143242, 600));
    set_skill(US_PRIDE, 500 + NAME_TO_RANDOM(query_name(), 1424, 600));
    set_skill(US_GRACE, 500 + NAME_TO_RANDOM(query_name(), 54324, 600));
    set_skill(US_PURITY, 500 + NAME_TO_RANDOM(query_name(), 78655, 600));

    set_dont_answer_unseen(1);

    make_member();
    /*
     * We can now ask the NPC for a list of people we have met.
     * We can also ask the NPC to describe the person, but since
     * the question is handled dynamically (e.g., we can only
     * respond to "ask cyrus to describe the dark-haired elf"
     * if we have met a dark-haired elf...), this will be handled
     * in the catch_question() function.
     */
    add_ask(({ "list people", "who have you met", "report",
	"list met", "report who you saw", "report who you met",
	"list those you met", "who have you encountered",
	"who have you seen"}), VBFC_ME("ask_about_encountered"), 1);

    add_ask(({ "assist", "assist me" }), VBFC_ME("help_union"), 1);
}

public void
unseen_hook(void)
{
    command("gaze suspic");
}

public void
respect(object who)
{
    // Only do respect if we are at our home.
    if (environment() != union_npc_home)
	return;

    if (!objectp(who) || !query_interactive(who))
	return;

    if (query_attack() &&
	present(who, environment()) && CAN_SEE(TO, who))
    {
	command("say Aide me, " + who->query_name() + "!");
	return;
    }

    if (member_array(who, respected) != -1)
	return;

    if (command("respect " + OB_NAME(who)))
	respected += ({ who });
}

public void
add_introduced(string str)
{
    object who = present(str, environment());

    if (!objectp(who))
	return;
    /*
     * Update our list of people to reflect that we know the
     * person's name
     */
    meet_living(who, 1);

    if (!query_interactive(who) || who->query_met(query_real_name()) ||
	!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, who) || ENEMY(who))
	return;

    set_alarm(itof(1 + random(3)), 0.0, &command("introduce myself"));
}

private string *sounds = ({
    "murmurs", "whispers", "says", "speaks"
});

public string
race_sound(void)
{
    return one_of_list(sounds);
}

public int
death_hearers(object ob)
{
    if (!present(TOKEN_ID, ob) || ob->query_wiz_level())
	return 0;

    if (present(ob, environment()))
	return 0;

    return 1;
}

public void
do_die(object killer)
{
    object thing;

#ifdef MAKE_KILLERS_ENEMIES
    // Make killers enemies of the Union
    LIST->add_enemy(killer->query_real_name());
#endif

#ifdef MAKE_KILLERS_INFIDELS
    // Make killers enemies of Sybarus
    if (killer->query_skill(SS_INFIDEL))
	killer->set_skill(SS_INFIDEL, IS_INFIDEL(killer) + 1);    
    else 
	killer->MAKE_INFIDEL;      

    WRATHOBJ->load_me();         
    WRATHOBJ->test_wrath(killer);
#endif

    if (thing = present(TOKEN_ID))
    {
	command("emote grasps hard onto "+ LANG_ASHORT(thing) +".\n");
	filter(users(), death_hearers)->catch_tell(
	  "The sphere in your hand suddenly turns freezing cold.\n"+
	  "You feel a wave of misery and grief wash over you.\n");
    }

    ::do_die(killer);
}

public void recheck_meet(object player)
{
    if (!player)
    {
        return;
    }
    if (environment(player) != environment(TO))
    {
        return;
    }
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, player))
    {
        set_alarm(3.0, 0.0, &recheck_meet(player));
	    return;
    }
    meet_living(player, 0);
}

public void
init_living(void)
{
    int resp;

    ::init_living();

    if (TP->query_race() == "ogre")
    {
		if (interactive(TP))
        {
			return;  // no reporting Emerald Ogres.
            set_alarm(3.0, 0.0, &recheck_meet(TP));
        }
	filter(users(), death_hearers)->catch_tell(
	  "\n\nThe sphere in your hand suddenly turns freezing cold.\n"+
	  "You have a vision of Ogres at the Gate.\n\n");
    }


    /* All Union players automatically know their guild NPC's */
    if (IS_MEMBER(TP))
	TP->add_introduced(query_real_name());

    /* Check for seen - don't do any further actions if you cannot see */
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        set_alarm(3.0, 0.0, &recheck_meet(TP));
	    return;
    }

    /* Prune expired entries. */
    respected = filter(respected, objectp);

    if (LIST->query_friend(TP->query_real_name()) ||
	LIST->query_accepted(TP->query_real_name()))
    {
	if (TP->test_bit(GUILD_GROUP, PROHIBIT))
	    TP->clear_bit(GUILD_GROUP, PROHIBIT);

	if (query_interactive(TP) && member_array(TP, respected) == -1)
	    resp = 1;
    }
    /* If the player is declared to be an enemy, or if the     */
    /* player is punished to the level of "autokill", then     */
    /* attack the player on sight.                             */
    else if ((ENEMY(TP) || U_IS_PUNISHED(TP, U_PUNISHED_AUTOKILL)) ||
	     IS_INFIDEL(TP) && !query_attack())
    {
	set_alarm(itof(1 + random(4)), 0.0, &command("kill "+ OB_NAME(TP)));
    }
    /* Otherwise grant the player a certain amount of respect  */
    /* based on their status in the guild.                     */
    else if (IS_MEMBER(TP))
    {
	if (query_interactive(TP) && member_array(TP, respected) == -1)
	    resp = 1;
    }

    // Register them as someone I have met
    meet_living(TP, 0);

    // Show respect
    if (resp)
	set_alarm(itof(1 + random(4)), 0.0, &respect(TP));
}

public int
special_attack(object enemy)
{
    if (!random(5))
	command("sway");
    command("dget");
   // They wield a knife, so their slash never happened 
   // when they ran out of knives. Changing check to  
   // "_npc_flinging_knife" from "knife".
    if (present("_npc_flinging_knife"))
	command("fling");
    else
	command("slash"); 

    return 0;
}

public void
notify_you_killed_me(object what)
{
    set_alarm(1.0, 0.0, &command("dget"));
}

public void
catch_question(string str)
{
    string person;

    if (ask_id(str))
	return ::catch_question(str);

    // Describe livings that we have encountered...
    if (parse_command(str, ({}), "[to] 'describe' [the] %s", person))
    {
	describe_met(person);
	return;
    }

    ::catch_question(str);
}

public void
return_ectios(object who)
{
    if (!query_attack() && objectp(who))
	command("ectios " + OB_NAME(who));
}

public void
union_hook_got_ectios(object who)
{
    set_alarm(itof(1 + random(3)), 0.0, &return_ectios(who));
}

// allow the summoning of this NPC to a ceremony
public void
ceremony_time_out(object from)
{
    if (sizeof(FILTER_PLAYERS(all_inventory(environment()))))
	set_alarm(itof(200 + random(150)), 0.0, &ceremony_time_out(from));
    else
	move_living("away", from, 1, 1);
}

public void
summon_for_union_ceremony(object where)
{
    if (query_attack())
	return;

    ceremony_room = where;
    set_alarm(itof(random(5)), 0.0,
	&move_living("away", where, 1, 1));
    set_alarm(itof(200 + random(150)), 0.0,
	&ceremony_time_out(environment()));
}

// only perform actions when not summoned to a ceremony
public void
monster_do_act()
{
    if (environment() != ceremony_room)
	::monster_do_act();
}
