/* Npc guard for the Union */
/*
 * Revisions:
 * 	Lilith, Jun 2004: moved friend check up top
 * 	Lucius, Apr 2005: added ranger incognito check.
 * 	Zielia, Jun 2009: added krynn plague check
 * 	Lucius, Jul 2011: added blocking check
 * 	Lucius, Jul 2017: Re-Code.
 *      Arman, Feb 2020: Upgraded stats, weapons, and quickness.
 *  Lilith, Oct 2021: moved order of weapon cloning so npc wields sword.
 *                    added assist Cyrus command in cact.
 *
 */
#pragma strict_types

#include "../defs.h"
inherit (NPC + "npc");

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include <stdproperties.h>

#define REMEMBERED	(NPC + "entrance")


public static int close_alarm;
public static mapping entered = ([ ]);

private void cleanup_remembered();


public string
my_long(void)
{
    string str = "Long black hair falls around her shoulders, "+
	"matching her deep black eyes perfectly. She "+
	"watches your every move intently.\n";

    if (IS_MEMBER(TP))
    {
	str += "She looks as though she is ready to assist "+
	"you in combat, should you ask.\n";
    }

    return str;
}

public void
create_monster(void)
{
    if (!IS_CLONE)
	return;

    set_name("nadia");
    set_living_name("nadia");
    set_race_name("human");
    set_adj("dark-skinned");
    add_adj("sultry");
    add_name("human");
    set_long(my_long);
    set_title("the Union Gatekeeper, Daughter of Shadow");

    set_alignment(0);
    set_appearance(95);
    set_gender(G_FEMALE);
    set_base_stat(SS_OCCUP, 110);
    set_stats(({ 194, 365, 255, 195, 191, 194 }));

    set_union_npc();
    TO->set_union_sphere(SPH_PROTECTION);

    set_skill(SS_LANGUAGE,      20);
    set_skill(SS_AWARENESS,     85);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HERBALISM,     91);
    set_skill(SS_PARRY,         100);
    set_skill(SS_DEFENCE,       100);
    set_skill(SS_ACROBAT,       150);
    set_skill(SS_WEP_KNIFE,     125);
    set_skill(SS_WEP_SWORD,     125);
    set_skill(SS_2H_COMBAT,     125);
    set_skill(SS_SWAY,          125);
    set_skill(SS_FLING,         125);
    set_skill(SS_SLASH,         125);
    set_skill(SS_UNARM_COMBAT,  10);

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(LIVE_I_QUICKNESS, 200);
    set_all_hitloc_unarmed(75);

    set_act_time(35);
    add_act("us The ogres have been seen on the move recently.");
    add_act("us Listen, hear the silence that emanates from these "+
	"dark places.");
    add_act("dbored");
    add_act("dchew");
    add_act("dhair");
    add_act("rub sphere");
    add_act("emote sighs gently.");
    add_act("nudge cyrus");
    add_act(({"close gate", "lock gate with sphere"}));
    add_act("flex fingers");
    add_act("tighten");
    add_act("mark all");
    add_act("dget");

    set_cact_time(3);
    add_cact("angry");
    add_cact("clash");
    add_cact("cross");
    add_cact("dget");
    add_cact("wrath");
    add_cact("assist cyrus");
	add_cact("ask cyrus assist");

    add_ask(({"enter","gate","open gate", "to open gate", "let me in",
	    "unlock", "unlock gate"}),
	VBFC_ME("open_gate"));
    add_ask(({"union","shadow union", "warrior","warriors",
	    "warriors of shadow"}),
	"say Beyond lie the Union of the Warriors of Shadow.", 1);
    add_ask(({ "doors" }),
	"say These gates serve to hold the dismal and ugly world "+
	"at bay from these halls of beauty.", 1);
    add_ask(({ "voice", "elders" }),
	"say The Voice speaks for the Elders.", 1);
    add_ask(({ "help", "task" }), "say I can offer you none.", 1);
    add_ask(({ "join", "apply", "application" }),
	"say I cannot help you with that. Ask Cyrus.", 1);
    add_ask(({ "joining", "hopeful", "membership" }),
	"say You will need to speak to Cyrus or the Voice about that.", 1);
    add_ask(({ "key" }),
	"say I hold the key to this beautiful place.", 1);
    add_ask(({ "name" }), "introduce myself", 1);
    add_ask(({ "ogres" }),
	"say Terrible and ugly creatures are they, dwelling deep "+
	"in the Utterdark amongst filth and hatred.", 1);
    add_ask(({ "quest" }), "say That is yours to discover...", 1);
    add_ask(({ "sphere" }), "say Only those of the Union may carry it.", 1);
    add_ask(({ "stone" }),
	"say These ancient tunnels of stone hold a stronger power of "+
	"darkness than can be imagined.", 1);

    add_ask(({"[list] [who] [are] / [is] [union] "+
	    "'friend' / 'friends' [of] [union]"}),
	VBFC_ME("answer_about_friends"));
    add_ask(({"[list] [who] [are] / [is] [union] "+
	    "'enemy' / 'enemies' [of] [union]"}),
	VBFC_ME("answer_about_enemies"));
    add_ask(({"[list] [who] [are] / [is] [union] "+
	"'friend' / 'friendly' / 'allied' / 'ally' 'guild' / "+
	"'allies' / 'ally' / 'guilds' [of] [the] [union]"}),
	VBFC_ME("answer_about_friend_guilds"));
    add_ask(({"[list] [who] [are] / [is] [union] "+
	    "'enemy' 'guild' / 'guilds' [of] [the] [union]"}),
	VBFC_ME("answer_about_enemy_guilds"));

    add_prop(CONT_I_HEIGHT, 200);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_cmdsoul(COM+"clubs/dance/dancer_soul");
    update_hooks();

    equip(({OBJ+"slash", OBJ+"knife_alt", OBJ+"knife_alt",
	    OBJ+"knife_alt", OBJ+"knife_alt", OBJ+"knife_alt",
	    OBJ+"shirt", OBJ+"pants", OBJ+"boots",
	    OBJ+"cape", OBJ+"gloves", OBJ+"knife_alt",
	    OBJ+"combat_veil"}));

    set_alarm(10.0, 0.0, &command("mark all"));
    set_alarm(10.0, 0.0, &command("veil me"));

    entered = restore_map(REMEMBERED);
    set_alarm(1.0, 0.0, cleanup_remembered);
}

private string *snds = ({ "murmurs", "whispers", "says", "speaks" });

public string
race_sound(void)
{
    return one_of_list(snds);
}

private void
close_up(void)
{
    close_alarm = 0;
    command("close gate");
    command("lock gate with sphere");
}

private void
do_unlock(void)
{
    object item = clone_object(OBJ +"guest_rules");

    item->move(TO);
    command("give "+ OB_NAME(item) +" to "+ OB_NAME(TP));

    if (!present(TOKEN_ID, TO))
	clone_object(TOKEN_OBJ)->move(TO);

    set_alarm(1.0, 0.0, &command("unlock gate with sphere"));
    set_alarm(1.5, 0.0, &command("open gate"));

    if (close_alarm) remove_alarm(close_alarm);
    close_alarm = set_alarm(8.0, 0.0, close_up);
}

public void
check_present(object who, function cmd)
{
    if (environment(who) != environment())
	return;

    cmd();
}

public string
open_gate(void)
{
    if (query_attack())
	return "";

    if (!CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
    {
	command("peer");
	command("say Who said that?");
	return "";
    }

    if (GUILD_CLOSED)
    {
	command("say Sorry, I have orders to let absolutely "+
	    "no one through.");
	command("say That includes you.");
	return "";
    }

    if (IS_MEMBER(TP))
    {
	if (U_IS_PUNISHED(TP, U_PUNISHED_NOENTER))
	{
	    command("us You are not allowed within the halls, "+
		TP->query_name() + ".");
	    command("us I suggest you beg for forgiveness before the "+
		"Elders if you ever want to pass by.");
	    return "";
	}

	if (present(TOKEN_ID, TP))
	    command("us Why don't you use your own key?");
	else
	    command("us Of course, "+ TP->query_name() +".");

	do_unlock();
	return "";
    }

    if (TP->query_hooded() || TP->query_ranger_incognito())
    {
	command("say Those that desire entrance should reveal themselves.");
	command("peer expectantly "+ OB_NAME(TP));
	return "";
    }

    if (ENEMY(TP))
    {
	command("say Not a chance, "+ TP->query_race_name());

	set_alarm(2.5, 0.0, &check_present(TP,
	    &command("say Get lost before I decide to kill you.")));
	set_alarm(4.0, 0.0, &check_present(TP,
	    &command("emote starts counting to ten under her breath.")));
	set_alarm(16.0, 0.0, &check_present(TP,
	    &command("kill "+ OB_NAME(TP))));

	return "";
    }

    if (LIST->query_blocked(TP))
    {
	command("ugaze "+ OB_NAME(TP));
	set_alarm(1.0, 0.0, &check_present(TP,
	    &command("say The Elders have declared you "+
	      "Persona Non Grata, "+ TP->query_name() +".")));
	set_alarm(3.0, 0.0, &check_present(TP,
	    &command("say I will not let you pass.")));
	set_alarm(3.5, 0.0, &check_present(TP,
	    &command("ustare "+ OB_NAME(TP))));

	return "";
    }

    if (FRIEND(TP))
    {
	command("say Of course, "+ TP->query_name() +".");
	do_unlock();

	if (TP->test_bit(GUILD_GROUP, PROHIBIT))
	    TP->clear_bit(GUILD_GROUP, PROHIBIT);

	set_alarm(2.5, 0.0, &check_present(TP,
	    &command("smile warm "+ OB_NAME(TP))));

	return "";
    }

    /* This denies entrance to hobbits, kenders, and othe halflings */
    if (member_array(TP->query_race_name(),
	    ({ "hobbit", "kender", "minotaur" })) != -1)
    {
	command("say Your race is foreign to Sybarus.");
	command("say I regret that I cannot open the gate to you.");
	return "";
    }

    if (present("nasty_sickness", TP))
    {
	TP->catch_msg(QCTPNAME(TO)+" black eyes seem alight with "+
	    "unnatural black fire as she stares at you assessingly.\n", TO);
	tell_room(ENV(TO), QCTPNAME(TO)+" black eyes seem alight with "+
	  "unnatural black fire as she stares at "+ QTNAME(TP) +
	  " assessingly.\n", TP, TO);    

	set_alarm(2.5, 0.0, &check_present(TP,
	    &command("say No Outland illness may enter these Halls.")));
	set_alarm(4.5, 0.0, &check_present(TP,
	    &command("say to "+ OB_NAME(TP) +" Purity is the first "+
	      "step towards Grace. You should seek it.")));

	set_alarm(5.0, 0.0, &command("ubrush"));
	return "";
    }

    if (LIST->query_hopeful(TP))
    {
	command("say Emait, Hopeful of the Shadow Union.");
	do_unlock();

	if (TP->test_bit(GUILD_GROUP, PROHIBIT))
	    TP->clear_bit(GUILD_GROUP, PROHIBIT);

	set_alarm(2.5, 0.0, &check_present(TP,
	    &command("smile curious "+ OB_NAME(TP))));

	return "";
    }

    if (TP->test_bit(GUILD_GROUP, PROHIBIT))
    {
	command("emote smiles, an expression of infinate "+
	    "sadness on her face.");
	command("say The Halls are still home to you, "+ TP->query_name() + "?");

	if (LIST->query_accepted(TP->query_real_name()))
	{
	    TP->clear_bit(GUILD_GROUP, PROHIBIT);
	    do_unlock();
	    return "";
	}

	command("say Until the Elders will it so, "+
	  "I cannot permit you to pass.");

	return "";
    }

    if (LIST->guild_query_prop("lock_doors"))
    {
	command("say Sorry, I have orders to let no Outlanders "+
	  "in at this time.");
	return "";
    }

    /* She will remember who has passed, and when */
    if (!TP->query_wiz_level() && !wildmatch("*jr", TP->query_name()))
    {
	if (!query_met(TP))
	{
	    command("say I will need to know your name before I can "+
	      "let you in, " + TP->query_race_name() + ".");
	    return ""; 
	}

	entered[TP->query_real_name()] = time();
	save_map(entered, REMEMBERED);
    }

    command("say Ok, I'll let you in this time. But behave yourself.");
    present("cyrus", environment())->unpc_hook_passing_player(TP);

    do_unlock();
    return "";
}

public int
stop(string str)
{
    if (!CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
	return 0;

    if (query_attack() == TP)
    {
	if (TP->query_stat(SS_DEX) < random(300))
	{
	    TP->catch_msg(QCTNAME(TO)+" moves to block your "+
		"retreat.\n");
	    say(QCTNAME(TO)+" stands in "+QTNAME(TP)+"'s path, "+
		"blocking "+ HIS(TP) +" retreat.\n", ({ TP , TO }));

	    return 1;
	}
    }
    return 0;
}

public void
init_living(void)
{
    ::init_living();

#ifdef BLOCK_ESCAPE
    add_action(stop,   "west");
#endif
    add_action(stop,   "east");

    if (IS_MEMBER(TP))
    {
	if (present("dirty", TP))
	{
	    set_alarm(2.0, 0.0, &check_present(TP,
		&command("us You better get cleaned up a bit, "+
		  TP->query_name() + ".")));
	}

	if (present("nasty_sickness", TP))
	{
	    set_alarm(2.0, 0.0, &check_present(TP,
		&command("us You ought seek Purity at the Flame, "+
		  TP->query_name() + ".")));
	}
    }

    if (!close_alarm)
	close_alarm = set_alarm(10.0, 0.0, close_up);
}

public void
attacked_by(object enemy)
{
    object friend = present("cyrus", environment());

    if (!friend || !friend->query_npc() || friend->query_attack())
	return;

    friend->command("kill "+ OB_NAME(enemy));
}

/* Returns the most recent x people to have passed the gates */
public varargs string *
last_passed(int how_many = 3)
{
    string *who = ({});
    int *times = sort_array(m_values(entered)), *which, i;

    if (sizeof(times) < how_many)
	return m_indices(entered);

    which = times[((sizeof(times) - 1) - how_many)..sizeof(times)];

    for (i = 0; i < sizeof(times); i++)
    {
	if (member_array(entered[m_indices(entered)[i]], which) != -1)
	    who += ({ m_indices(entered)[i] });
    }

    return map(who, capitalize);
}

private void
answer_entered(object who, int how_many)
{
    int size;
    string *people;

    if (!IS_MEMBER(who) || LEVEL(who) < NORMAL)
    {
	command("us Why should I tell you that?");
	return;
    }

    people = map(last_passed(how_many), capitalize);
    size = sizeof(people);

    switch(size)
    {
    case 0:
	command("us Nobody has passed through.");
	break;
    case 1:
	command("us The last person to have passed was "+
	    people[0] + ".");
	break;
    default:
	command("us The last "+ LANG_WNUM(size) +
	    " people to have passed by were " +
	    COMPOSITE_WORDS(sort_array(people)) + ".");
	break;
    }
}

private void
answer_enemy_friend_info(object who, string what_kind)
{
    string *people;

    if (!IS_MEMBER(who) || LEVEL(who) < NORMAL)
    {
	command("say Why should I tell you that?");
	return;
    }

    switch(what_kind)
    {
    case "enemy":
	people = LIST->enemy_list();
	break;
    case "friend":
	people = LIST->friend_list();
	break;
    case "enemy guild":
	people = LIST->enemy_guild_list();
	break;
    case "friend guild":
	people = LIST->friend_guild_list();
	break;

	// Sanity...
    default:
	what_kind = "friend";
	people = LIST->friend_list();
	break;
    }

    // Capitalize all names in the array
    people = map(people, capitalize);

    if (!sizeof(people))
    {
	command("us The Union has no "+ LANG_PWORD(what_kind) +
	    " declared at this time.");
    }
    else if (sizeof(people) > 1)
    {
	command("us The "+ LANG_PWORD(what_kind) +" of the Union are "+
	    COMPOSITE_WORDS(people) + ".");
    }
    else
    {
	command("us The only " + what_kind + " of the Union is "+
	    people[0] + ".");
    }
}

public string
answer_about_friends(void)
{
    answer_enemy_friend_info(TP, "friend");
    return "";
}

public string
answer_about_enemies(void)
{
    answer_enemy_friend_info(TP, "enemy");
    return "";
}

public string
answer_about_friend_guilds(void)
{
    answer_enemy_friend_info(TP, "friend guild");
    return "";
}

public string
answer_about_enemy_guilds(void)
{
    answer_enemy_friend_info(TP, "enemy guild");
    return "";
}

public void
catch_question(string str)
{
    int many = 3;
    string ask, how_many = "";

    if (ask_id(str))
	return ::catch_question(str);

    ask = lower_case(str);

    if (parse_command(ask, ({}), "[who] [has] 'entered' / 'passed' "+
	    "[the] / [these] [gates] / [gate] [recently]") ||
	parse_command(ask, ({}), "'last' %s 'people' [to] [have] "+
	    "[entered] / [passed] [the] [gate] / [gates]", how_many))
    {
	if (LANG_NUMW(how_many))
	    many = LANG_NUMW(how_many);

	set_alarm(2.0, 0.0, &answer_entered(TP, many));
	return;
    }

    ::catch_question(str);
}

/*
 * Cleanup our remembered list - cut it down to only people
 * who have passed within the three days
 */
private void
cleanup_remembered(void)
{
    int limit = time() + (60 * 60 * 24 * 3);
    foreach(string who, int when: entered)
    {
	if (when < limit)
	    m_delkey(entered, who);
    }
    save_map(entered, REMEMBERED);
}

private void 
return_unwanted(object what, object who)
{
    if (!objectp(what))
	return;

    if (present(who, environment()))
	command("usto "+ who->query_real_name() +" That is not for me.");

    if (!command("give "+ OB_NAME(what) +" to "+ OB_NAME(who)))
	what->remove_object();  
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
	return;

    if (obj->query_wt() == W_KNIFE)
	return;

    set_alarm(2.0, 0.0, &return_unwanted(obj, from));
}
