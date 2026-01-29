/*
 *  /cmd/live/social.c
 *
 *  General commands for 'nonemotive' social behaviour
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "composite.h"
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>

#define BSN(str) (break_string((str), 75) + "\n")

#define MORE_OBJ "/std/board/board_more"

void
create()
{
    seteuid(getuid(this_object())); 
}

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "social";
}

/* **************************************************************************
 * This is a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */
mapping
query_cmdlist()
{
    return ([
	     "aggressive":"aggressive",
	     "ask2":"ask",
	     "assist":"assist",

	     "commune":"commune",

	     "emote":"emote",

	     "forget":"forget_live",

	     "introduce":"intro_live",
	     "introduced":"introduced_list",
	     "invite":"invite",

	     "join":"join",

	     "kill":"kill",

	     "leave":"leave",

             "mwho":"who_known",

	     "present":"intro_live",
	     "players":"who_known",

	     "reply":"reply",
	     "remember":"remember_live",
	     "remembered":"remember_live",

	     "see":"see",
	     "stop":"stop",

	     "team":"team",

	     "who":"who_known"
	     ]);
}

/*
 * Function name: using_soul
 * Description:   Called once by the living object using this soul. Adds
 *		  sublocations responsible for extra descriptions of the
 *		  living object.
 */
public void 
using_soul(object live)
{
    /*
	live->add_subloc(SUBLOC_MISCEXTRADESC, file_name(this_object()));
        live->add_textgiver(file_name(this_object()));
    */
}

/* **************************************************************************
 * Here follows some support functions. 
 * **************************************************************************/

int 
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == this_player())
	return 0;
    else
	return 1;
}

nomask string
capn(string n)
{ 
    if (stringp(n)) 
	return capitalize(n);
    else
	return n;
}

/* **************************************************************************
 * Here follows the actual functions. Please add new functions in the 
 * same order as in the function name list.
 * **************************************************************************/

/*
 * Aggressive - Set how aggressive we are
 *
 * This command is used to state when to fight and when to flee
 *
 * ** not ready yet, needs fixes in the combat system **
 */
int
aggressive(string str)
{
    write("Yes you are, very!\n");
    return 1;
}

/*
 * Ask - Ask someone something
 *
 */
int
ask(string str)
{
    object *oblist, *tmplist;
    string msg, players;
    int i;

    seteuid(getuid());
    
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
	notify_fail("You can't see in here.\n");
	return 0;
    }

    tmplist = ({});
    notify_fail("Ask what?\n");

    if (!str)
	return 0;

    if (parse_command(str, environment(this_player()), "%l %s", oblist, msg))
	oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist))
    {
	notify_fail("Can't find that person.\n");
	return 0;
    } 
    else if (oblist[0] == this_player())
    {
        notify_fail("Don't ask me, I wouldn't know.\n");
	return 0;
    }
    else
    {
	for (i = 0; i < sizeof(oblist); i++)
	{
	    if (objectp(oblist[i]) && living(oblist[i]) &&
			this_player() != oblist[i])
		tmplist += ({ oblist[i] });
	}

	if (!strlen(msg))
	{
	    write("Ask what to " + COMPOSITE_LIVE(oblist) + "?\n");
	    return 1;
	}

	this_player()->reveal_me(1);

	players = COMPOSITE_LIVE(oblist);
	if (this_player()->query_get_echo())
	    write(break_string("You ask " + players + ": " + msg + "\n", 70));
	else
	    write("Ok.\n");

	say(QCTNAME(this_player()) + " asks " + QCOMPLIVE + " something.\n",
			oblist + ({ this_player() }) );

        for (i = 0; i < sizeof(oblist); i++)
        {
            oblist[i]->catch_msg(this_player()->query_The_name(oblist[i]) + 
		" asks you: " + msg + "\n");
            oblist[i]->catch_question(msg);
	    oblist[i]->reveal_me(1);
        }
    }

    return 1;
}

/*
 * assist - Help a friend to kill someone else
 */
int 
assist(string str)
{
    object	*obs, friend, victim;
    int index;
    string	str2;
    mixed	tmp;

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
	notify_fail("You can't see anything here.\n");
	return 0;
    }

    if (this_player()->query_ghost())
    {
	notify_fail("Umm yes, killed. That's what you are.\n");
	return 0;
    }

    if (!strlen(str))
    {
        if (!sizeof(obs = this_player()->query_team_others()))
        {
            notify_fail("Assist whom? You are not in a team.\n");
            return 0;
        }

        obs = ({ this_player()->query_leader() }) - ({ 0 }) + obs;

	for (index = 0; index < sizeof(obs); index++)
	{
	    if ((environment(this_player()) == environment(obs[index])) &&
		(objectp(victim = obs[index]->query_attack())))
	    {
		friend = obs[index];
		break;
	    }
	}

	if (!objectp(friend))
	{
	    notify_fail("None of your team members is in combat.\n");
	    return 0;
	}
    }
    else
    {
	obs = parse_this(str, "[the] %l");

	if (sizeof(obs) > 1)
	{
	    notify_fail(break_string("Be specific, you can't assist " +
		COMPOSITE_LIVE(obs) + " at the same time.", 76) + "\n");
	    return 0;
	}
	else if (sizeof(obs) == 0)
	{
	    notify_fail("Assist whom?\n");
	    return 0;
	}

	friend = obs[0];
    }

    if (friend == this_player())
    {
	write("Sure! Assist yourself!\n");
	return 1;
    }

    if (member_array(friend, this_player()->query_enemy(-1)) != -1)
    {
	write(break_string("Help " + friend->query_the_name(this_player()) +
	    " to kill you? There are easier ways to commit seppuku!", 76) +
	    "\n");
	return 1;
    }

    victim = friend->query_attack();

    if (!objectp(victim))
    {
	write(friend->query_The_name(this_player()) +
	    " is not fighting anyone.\n");
	return 1;
    }

    if (member_array(victim, this_player()->query_team_others()) != -1)
    {
        notify_fail("But " + victim->query_the_name(this_player()) +
            " is a team with you.\n");
        return 0;
    }

    if (member_array(victim, this_player()->query_enemy(-1)) != -1)
    {
	write("You are already fighting " +
	    victim->query_the_name(this_player()) + ".\n");
	return 1;
    }

    if (tmp = environment(this_player())->query_prop(ROOM_M_NO_ATTACK))
    {
	if (stringp(tmp))
	    write(tmp);
	else
	    write("You sense a divine force preventing your attack.\n");
	return 1;
    }

    if (tmp = victim->query_prop(OBJ_M_NO_ATTACK))
    {
	if (stringp(tmp))
	    write(tmp);
	else
	    write("You feel a divine force protecting this being, your " +
		"attack fails.\n");
	return 1;
    }

    if ((!this_player()->query_npc()) &&
	(this_player()->query_met(victim)) &&
	(this_player()->query_prop(LIVE_O_LAST_KILL) != victim))
    {
	write("Attack " + victim->query_the_name(this_player()) +
	   "?!? Please confirm by trying again.\n");
	this_player()->add_prop(LIVE_O_LAST_KILL, victim);
	return 1;
    }

    this_player()->reveal_me();
    /*
     * Check if we dare!
     */
    if (!F_DARE_ATTACK(this_player(), victim))
    {
	write("Umm... no! You do not have enough self-discipline to dare!\n");
	return 1;
    }

    say(QCTNAME(this_player()) + " assists " + QTNAME(friend) +
	" and attacks " + QTNAME(victim) + ".\n",
	({ this_player(), friend, victim }) );
    victim->catch_msg(this_player()->query_The_name(victim) +
	" attacks you!\n");
    friend->catch_msg(this_player()->query_The_name(friend) +
	" assists you and attacks " + victim->query_the_name(friend) +
	".\n");

    this_player()->attack_object(victim);
    this_player()->add_prop(LIVE_O_LAST_KILL, victim);

    write("Ok.\n");
    return 1;
}

/*
 * Commune - talk with the wizards
 *
 * This is supposed to be used in extreme emergencies only
 */
int
commune(string str)
{
    object *us, spec;
    int il, flag = 0, size;
    string *arg, wiz, mess;

    if (!strlen(query_ip_number(this_player())))
    {
	notify_fail("Only true players may commune with the deities.\n");
	return 0;
    }

    if (this_player() != this_interactive())
    {
	tell_object(this_interactive(),
	    "Communing is a decision the player must make alone.\n");
	return 0;
    }

    if (this_player()->query_wiz_level())
    {
	notify_fail("Communing is something relevant only to mortals, " +
	    "seek an audience.\n");
	return 0;
    }

    if (!strlen(str))
    {
	write("Please do 'help commune' to see how this rite is performed.\n");
	write("But Beware! Mortals will be stricken by the ultimate wrath of\n");
	write("the deities supreme if communing for insufficient reasons.\n");
	return 1;
    }

    arg = explode(str, " ");

    if (sizeof(arg) < 2)
    {
	notify_fail("Please do 'help commune' to see how this rite " +
	    "is performed.\n");
	return 0;
    }
    
    wiz = lower_case(arg[0]);
    str = capitalize(this_interactive()->query_real_name());
    mess = implode(arg[1..], " ") + "\n";

    switch(wiz)
    {
    case "all":
	us = filter(users(), "is_wiz", WIZ_CMD_APPRENTICE);
	il = -1;
	size = sizeof(us);

	while(++il < size)
	{
	    if (query_ip_number(us[il]) &&
		!(us[il]->query_prop(WIZARD_I_BUSY_LEVEL) & 32))
	    {
		tell_object(us[il],
		    "COMMUNE anyone from " + str + ": " + mess);
		flag = 1;
	    }
	}
	break;

    case "here":
        if (!environment(this_player()))
	{
	    notify_fail("Here? There is no here?\n");
	    return 0;
	}

	wiz = explode(file_name(environment(this_player())), "/")[2];
	if (!sizeof(arg = (string *)SECURITY->query_domain_members(wiz)))
	{
	    notify_fail("Sorry. You cannot commune 'here' from this room.\n");
	    return 0;
	}

	il = -1;
	size = sizeof(arg);

	while(++il < size)
	{
	    spec = find_player(arg[il]);

	    if (spec &&
		query_ip_number(spec) &&
		!(spec->query_prop(WIZARD_I_BUSY_LEVEL) & 32))
	    {
		tell_object(spec,
		    "COMMUNE " + wiz + " from " + str + ": " + mess);
		flag = 1;
	    }
	}
	break;

    default:
	if (this_player()->query_mana() >=
	    this_player()->query_max_mana() / 10)
	    this_player()->add_mana(-(this_player()->query_max_mana() / 10));
	else
	{
	    write("You feel far to exhausted to do that.\n");
	    return 1;
	}

	spec = find_player(wiz);
	wiz = capitalize(wiz);

	if (!spec || 
	    !spec->query_wiz_level() ||
	    !query_ip_number(spec) ||
	    (spec->query_prop(WIZARD_I_BUSY_LEVEL) & 32) ||
	    spec->query_prop(OBJ_I_INVIS) > 0)
	{
	    break;
	}

	tell_object(spec, "COMMUNE to you from " + str + ": " + mess);
	flag = 1;
	break;
    }

    /* Log the commune message in a public log. */
    SECURITY->commune_log(wiz + ": " + mess);

    if (flag)
	write("You feel you have communed with the deities.\n");
    else
	write("Your prayers remain unheard.\n");
    
    return 1;
}

/*
 * emote - Put here so NPC:s can emote (  No error messages if they do wrong,
 *	   why waste cpu on NPC:s ? ;-)   )
 */
int
emote(string str)
{
    if (!strlen(str) || !this_player()->query_npc())
	return 0;

    say( ({ METNAME + " " + str + "\n", TART_NONMETNAME + " " + str + "\n",
	    UNSEEN_NAME + " " + str + "\n" }) );

/*
 * Nonsense. Why shouldn't you be able to emote and stay hidden? /Mercade
    this_player()->reveal_me(1);
 */
    return 1;
}

/*
 * forget - Forget someone we have remembered
 */
int
forget_live(string name)
{
    object ob;

    if (!name)
    {
	notify_fail("Forget whom?\n");
	return 0;
    }
    ob =  find_living(name);
    if (ob && ob->query_prop(LIVE_I_NON_FORGET))
    {
	notify_fail("It seems impossible to forget " +
		    ob->query_objective()+"!\n");
	return 0;
    }
    if (this_player()->remove_remembered(name))
    {
	this_player()->add_introduced(name);
	write("Ok.\n");
	return 1;
    }
    else
    {
	notify_fail("You do not know any " + capitalize(name) + ".\n");
	return 0;
    }
}

/*
 * introduce - Present yourself or someone else.
 */
int
intro_live(string str)
{
    string  intro_who;
    string  intro_to = "";
    object  tp = this_player();
    object  introducee;
    object *livings;
    object *targets;
    int     intro_self = 0;
    int     index;
    int     size;

    notify_fail(capitalize(query_verb()) + " who [to whom]?\n");
    if (!strlen(str))
    {
	return 0;
    }

    if (sscanf(str, "%s to %s", intro_who, intro_to) != 2)
    {
	intro_who = str;
    }

    if ((intro_who == "me") || (intro_who == "myself"))
    {
	intro_self = 1;
	introducee = tp;
    }
    else
    {
	livings = parse_this(intro_who, "[the] %l");
	switch(sizeof(livings))
	{
	case 0:
	    return 0;

	case 1:
	    break;

	default:
	    notify_fail("You can only " + query_verb() +
		" one living at a time.\n");
	    return 0;
        }
	introducee = livings[0];

	/* As if Mercade would type 'introduce Mercade' *duh* */
	if (introducee == tp)
	{
	    intro_self = 1;
	}
    }

    if (!this_player()->query_met(introducee->query_real_name()))
    {
	notify_fail(BSN("You have not been properly introduced to " +
	    introducee->query_the_name(tp) + " yourself."));
	return 0;
    }

    if (strlen(intro_to))
    {
	targets = parse_this(intro_to, "[the] %l");
    }
    else
    {
	targets = FILTER_LIVE(all_inventory(environment(tp)));
    }
    targets -= ({ tp, introducee });

    if (!sizeof(targets))
    {
	notify_fail("Noone to introduce " + (intro_self ? "yourself" :
	    introducee->query_the_name(tp)) + " to.\n");
	return 0;
    }

    tp->reveal_me(1);
    if (!intro_self)
    {
	introducee->reveal_me(1);
    }

    size = sizeof(targets);
    index = -1;
    while(++index < size)
    {
	tell_object(targets[index], tp->query_The_name(targets[index]) +
	    " introduces " + (intro_self ? (tp->query_objective() + "self") :
	    introducee->query_the_name(targets[index])) + " as:\n" +
	    introducee->query_presentation() + ".\n");
    }
    targets->add_introduced(introducee->query_real_name());

    if (strlen(intro_to))
    {
	livings = FILTER_LIVE(all_inventory(environment(tp)));
	livings -= targets;
	livings -= ({ tp, introducee });

	size = sizeof(livings);
	index = -1;
	while(++index < size)
	{
	    livings[index]->catch_msg(BSN(tp->query_The_name(livings[index]) +
		" introduces " + (intro_self ? (tp->query_objective() +
		    "self") : introducee->query_the_name(livings[index])) +
		" to " + FO_COMPOSITE_LIVE(targets, livings[index]) + "."));
	}
    }

    if (!intro_self)
    {
	introducee->catch_msg(break_string(tp->query_The_name(introducee) +
	    " introduces you to " + FO_COMPOSITE_LIVE(targets, introducee) +
	    ".", 75) + "\n");
    }

    if (tp->query_get_echo())
    {
	write(BSN("You " + query_verb() + " " +
	    (intro_self ? "yourself" : introducee->query_the_name(tp)) +
	    " to " + COMPOSITE_LIVE(targets) + "."));
    }
    else
    {
	write("Ok.\n");
    }
    return 1;
}

/*
 * introduced - Give a list of livings we have been introduced to.
 */
int
introduced_list(string str)
{
    object ob;
    mapping tmp;
    
    tmp = this_player()->query_introduced();
    if (mappingp(tmp))
    {
	write("You remember having been introduced to:\n");
	write(break_string(implode(map(sort_array(m_indexes(tmp)),
	    "capn", this_object()), ", "), 70) + "\n");

	return 1;
    }
    else
    {
	write("You don't remember having been introduced to anyone.\n");
	return 1;
    }
}

/*
 * invite - Invite someone to join my team
 */
int
invite(string name)
{
    object *member_list, member;

    if (!name)
    {
	member_list = (object *) this_player()->query_invited();
	if (!member_list || !sizeof(member_list))
	    write("You have not invited anyone to join you.\n");
	else
	{
	    if (sizeof(member_list) == 1)
		write("You have invited " + member_list[0]->short() +
			".\n");
	    else {
		name = (string) COMPOSITE_FILE->desc_live(member_list);
		write("You have invited " +
		      (string) LANG_FILE->word_num(sizeof(member_list)) +
		      " people:\n");
		write(break_string(name, 76, 3));
	    }
	}
	return 1;
    }

    member = find_player(name);

    if (!member || (member && !present(member, environment(this_player()))))
    {
	notify_fail(capitalize(name) +
		    " is not a good potential team member!\n");
	return 0;
    }

    if (!CAN_SEE(this_player(), member))
    {
        notify_fail("Invite whom?");
        return 0;
    }

    if (this_player()->query_leader())
    {
	notify_fail("You can't be a leader when you have a leader!\n");
	return 0;
    }

    if ((!member->query_met(this_player())) ||
	    (!this_player()->query_met(member)))
	return (notify_fail("You have not been introduced!\n"),0);

    if (member == this_player())
    {
	notify_fail("You do not need an invitation to your own team!\n");
	return 0;
    }

    this_player()->team_invite(member);
    member->catch_msg(this_player()->query_The_name(member) +
	" invites you to join " + this_player()->query_possessive() +
	" team.\n");
    this_player()->reveal_me(1);
    member->reveal_me(1);
		
    write("Ok.\n");
    return 1;
}

/*
 * join - Join someones team
 */
varargs int 
join(string name)
{
    object          leader;

    notify_fail("You must give the name of the player you want as " +
	"your leader.\n");

    if (!name)
	return 0;

    if (this_player()->query_leader())
    {
	write("You already have a leader!\n");
	return 1;
    }

    if (!this_player()->query_met(name))
    {
	write("You don't know anyone called '" + capitalize(name) + "'.\n");
	return 1;
    }

    leader = present(name, environment(this_player()));

    if (!leader || !leader->check_seen(this_player()))
    {
	write("You don't see " + capitalize(name) + " here.\n");
	return 1;
    }

    /*
     * Can not have a leader with too low DIS
     */
    if (leader->query_stat(SS_DIS) + 10 < this_player()->query_stat(SS_DIS) &&
		!this_player()->query_wiz_level())
    {
	write("You do not have enough faith in " + 
	      LANG_POSS(leader->short()) + " discipline.\n");
	return 1;
    }

    if (leader->team_join(this_player()))
    {
	write("Your leader is now: " + leader->short() + ".\n");
	say(QCTNAME(this_player()) + " joined the team of " +
		QTNAME(leader) + ".\n", ({ leader, this_player() }));
	leader->catch_msg(this_player()->query_The_name(leader) +
	    " joined your team.\n");
	return 1;
    }
    else
    {
	write(leader->short() +
	      " has not invited you as a team member.\n");
	return 1;
    }
}

/*
 * kill - Start attacking someone with the purpose to kill
 */
varargs int 
kill(string str)
{
    object      ob, *a;
    string 	str2;
    mixed	tmp;

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
	notify_fail("You can't see anything here.\n");
	return 0;
    }

    if (this_player()->query_ghost())
    {
	notify_fail("Umm yes, killed. That's what you are.\n");
	return 0;
    }
    if (!str)
    {
	notify_fail("Kill what ?\n");
	return 0;
    }

    a = CMDPARSE_ONE_ITEM(str, "kill_access", "kill_access");
    if (sizeof(a) > 1)
    {
	str2 = COMPOSITE_LIVE(a);
	notify_fail(break_string("Be specific, you can't kill " + str2 +
		    " at the same time.\n",76));
	return 0;
    }
    else if (!sizeof(a))
    {
	notify_fail("You find no such living creature.\n");
	return 0;
    }
    ob = a[0];

    if (!ob)
    {
	notify_fail("No " + str + " here !\n");
	return 0;
    }
    if (!living(ob))
    {
	write(str + " is not a living thing !\n");
	say( ({ METNAME + " tries foolishly to kill " + str + ".\n",
		TART_NONMETNAME + " tries foolishly to kill " +
		str + ".\n", "" }) );
	return 1;
    }
    if (ob == this_player())
    {
	write("What ? Attack yourself ?\n");
	return 1;
    }
    if ((object) this_player()->query_enemy() == ob)
    {
	write("Yes, yes.\n");
	return 1;
    }

    if (tmp = environment(this_player())->query_prop(ROOM_M_NO_ATTACK))
    {
	if (stringp(tmp))
	    write(tmp);
	else
	    write("You sense a divine force preventing your attack.\n");
	return 1;
    }

    if (tmp = ob->query_prop(OBJ_M_NO_ATTACK))
    {
	if (stringp(tmp))
	    write(tmp);
	else
	    write("You feel a divine force protecting this being, your " +
		"attack fails.\n");
	return 1;
    }

    if (!this_player()->query_npc() && this_player()->query_met(ob) &&
	this_player()->query_prop(LIVE_O_LAST_KILL) != ob)
    {
	write("Attack " + ob->query_the_name(this_player()) +
	    "?!? Please confirm by trying again.\n");
	this_player()->add_prop(LIVE_O_LAST_KILL, ob);
	return 1;
    }

    this_player()->reveal_me();
    /*
     * Check if we dare!
     */
    if (!F_DARE_ATTACK(this_player(), ob))
    {
	write("Umm... no, You do not have enough self-discipline to dare!\n");
	return 1;
    }

    say(QCTNAME(this_player()) + " attacks " + QTNAME(ob) + ".\n",
        ({this_player(), ob}));
    ob->catch_msg(this_player()->query_The_name(ob) + " attacks you!\n");

    this_player()->attack_object(ob);
    this_player()->add_prop(LIVE_O_LAST_KILL, ob);

    write("Ok.\n");
    return 1;
}

/*
 * leave - Leave a team or force someone to leave a team
 */
int 
leave(string name)
{
    object ob;

    /* This function used to have 'reveal_me' calls in players, though
     * that is nonsense since you do not even have to be in the same room
     * to leave a team or force a member to leave your team. /Mercade
     */

    if (!strlen(name))
    {
	if (objectp(ob = this_player()->query_leader()))
	{
	    ob->team_leave(this_player());
	    write("You leave your leader.\n");
	    ob->catch_msg(this_player()->query_The_name(ob) +
		" left your team.\n");

	    return 1;
	}

	if (sizeof(this_player()->query_team()))
	{
	    notify_fail("You are leading a team. To force a member to " +
		"leave, do <leave name>.\n");
	    return 0;
	}

	notify_fail("You are not a member of a team.\n");
	return 0;
    }

    if (!sizeof(this_player()->query_team()))
    {
	notify_fail("You are not the leader of a team. Do <leave> to " +
	    "leave your leader.\n");
	return 0;
    }

    if (!objectp(ob = find_player(name)))
    {
	notify_fail("No such player, \"" + capitalize(name) + "\".\n");
	return 0;
    }

    if ((ob->query_leader()) != this_player())
    {
	notify_fail("No member named \"" + capitalize(name) +
	    "\" in your team.\n");
	return 0;
    }

    this_player()->team_leave(ob);
    this_player()->remove_invited(ob); /* disallow him/her to rejoin. */
    write("You force " + ob->query_the_name(this_player()) +
	" to leave your team.\n");
    ob->catch_msg(this_player()->query_The_name(ob) + " forces you to leave " +
	this_player()->query_possessive() + " team.\n");

    return 1;
}

/*
 * reply - Allow mortals to reply when something is told to them.
 */
int
reply(string str)
{
    string who;
    object tp, target;

    tp = this_player();

    if (!strlen(who = (string)tp->query_prop("_reply_wizard")))
    {
	notify_fail("You can only reply if someone told you something.\n");
	return 0;
    }

    if (!str)
    {
	notify_fail("Reply what?\n");
	return 0;
    }

    tp->remove_prop("_reply_wizard");

    if (!objectp(target = find_player(who)))
    {
	write("You cannot reply, that person is no longer in the game.\n");
	return 1;
    }

    target->catch_msg(tp->query_The_name(target) + " replies: " + str + "\n");
    tp->catch_msg("You replied to " + target->query_the_name(tp) + ".\n");
    return 1;
}

/*
 * remember - Remember one of the livings introduced to us
 */
int
remember_live(string str)
{
    object ob;
    mapping tmp;
    int num;
    
    if (!str || query_verb() == "remembered")
    {
	tmp = this_player()->query_remembered();
	if (mappingp(tmp))
	{
	    if (num = m_sizeof(tmp))
	    {
		num = F_MAX_REMEMBERED(this_player()->query_stat(SS_INT)) - num;
		if (num < 0)
		    num = 0;

		write("These are the people you remember:\n");
		write(break_string(implode(map(sort_array(m_indexes(tmp)),
		    "capn", this_object()), ", "), 70) + "\n");
		write("Your brain can handle " + LANG_WNUM(num) +
			" more name" + (num == 1 ? ".\n" : "s.\n") );
		return 1;
	    }
	    else
	    {
		write("You do not seem to remember anyone.\n");
		return 1;
	    }
	}
	else
	{
	    write("You don't remember knowing anyone at all.\n");
	    return 1;
	}
    }

    str = lower_case(str);    
    if (objectp(ob = find_living(str)) &&
	(ob->query_prop(LIVE_I_NON_REMEMBER)))
    { 	
	notify_fail("Remember" + ob->query_objective() + "? Never!");
 	return 0;
    }

    switch (this_player()->add_remembered(str))
    {
    case -1:
	write("Your poor brain cannot handle any more people.\n");
	return 1;
    case 1:
	write("Ok.\n");
 	return 1;
    case 2:
	write("You refresh your memory of " + capitalize(str) + ".\n");
        return 1;
    default:
	notify_fail("You can't remember having been introduced to " + 
		    capitalize(str) + ".\n");
	return 0;
    }
}

/*
 * see - Do we want to see all other peoples combat messages
 */
varargs int
see(string str)
{
    notify_fail("See what? Fights?\n");
    if (!str)
	return 0;

    if (str == "fights")
    {
    	if (!this_player()->query_see_blood())
        {
	    this_player()->set_see_blood(1);
	    write("Ok.\n");
	    return 1;
        }

	notify_fail("You already keep your eyes open for fights.\n");
	return 0;
    }
    else if (str == "no fights")
    {
    	if (this_player()->query_see_blood())
        {
	    this_player()->set_see_blood(0);
	    write("Ok.\n");
	    return 1;
        }

        notify_fail("You already hide your eyes from combat if possible.\n");
	return 0;
    }
    return 0;   	
}   

/*
 * stop - Stop hunting or fighting
 */
int
stop(string str)   /* Rewritten by Left of Hyperborea -- 23.4.92 */
{
    string a,b;
    object *e, *pe;
    
    if (!str)
    {
	notify_fail("Stop what? The world?\n");
	return 0;
    }

    pe = this_player()->query_enemy(-1);

    if (!pe || sizeof(pe) == 0)
    {
	notify_fail("You are not hunting anyone.\n");
	return 0;
    }

    /* use the full power of parse_command on the stop spec.  It will
     * now support "stop hunting all", "stop hunting vogons".. etc
     */
    if (parse_command(str, pe,
		" 'hunt' / 'hunting' / 'fight' / 'fighting' %i ", e))
    {
	int i;
        for (i = 1; i < sizeof(e) ; i++)
        {
            this_player()->stop_fight(e[i]);
        }
        write("Ok.\n");
        return 1;
    }

    (sscanf(str, "%s %s", a, b) || sscanf(str, "%s", a)); /*gasp* /JnA */

    if (a == "hunt" || a == "hunting" || a == "fight" || a == "fighting")
    {
        /* stop hunting the last one fought */
        if (!b || b == "")
        {
            this_player()->stop_fight(this_player()->query_enemy());
            write("Ok.\n");
            return 1;
        }
        else
        /* give error messages for ones not being fought, and those that
         * do not exist.
         */
        {
            object not_hunted;

            not_hunted = find_player(b);
            if (!not_hunted)
                not_hunted = find_living(b);

            if (not_hunted)
	    {
                if (a == "hunt" || a == "hunting")
                    notify_fail("You are not hunting: " +
				not_hunted->query_the_name(this_player()) +
				"\n");
                else
		    notify_fail("You are not fighting: " +
				not_hunted->query_the_name(this_player()) +
				"\n");
		return 0;
	    }

            notify_fail("No such enemy found: " + b + "\n");
            return 0;
        }
    }

    notify_fail(capitalize(query_verb()) + " what ?\n");
    return 0;
}

/*
 * team - Tell me what team I am a member 
 */
varargs int
team(string str)
{
    object	leader;
    object	*members;

    if (!str) /* My team */
    {
	if (leader = (object) this_player()->query_leader()) 
	{
	    members = (object *) leader->query_team();
	    write("You are a member of " + leader->short() + 
		  "'s team.");
	    members = FILTER_LIVE(members - ({ this_player() }) );
	    if (!sizeof(members)) 
	    {
		write(" You are the only member.\n");
		return 1;
	    }
	    else
		write(" The other members are:\n");
	}
	else if (sizeof(members = (object *) this_player()->query_team()) > 0)
	    write("You are the leader of your team. The members are:\n");
        if (sizeof(members))
    	{
	    write(break_string(implode(MAP_FUN(members, "short"), " "),
		76, 3) + "\n");
	    return 1;
	}
	notify_fail("You are not member of a team.\n");
	return 0;
    }
    notify_fail("You can find out about your team with this command.\n");
    return 0;
}

/*
 * who - Tell what players are logged in and who we know
 */
nomask int
index(string str, string letter)
{
    return member_array(letter, explode(str, ""));
}

int
who(string opts, object *list, int size)
{
    int i, j;
    int scrw = (int)this_player()->query_prop(PLAYER_I_SCREEN_WIDTH);
    int see_invis = (int)this_player()->query_prop(LIVE_I_SEE_INVIS);
    string to_write = "", *title, tmp;

    /* We sort automatically to mix in the NPC's. */
    list = sort_array(list, "sort_name", this_object());

    if (scrw == 0)
        scrw = 80;
    scrw -= 3;

    if (!sizeof(list))
    {
        to_write += ("There are no players of the requested type present.\n");
        /* No need to check for mwho here. */
        write(to_write);
        return 1;
    }

    if (size == 1)
        to_write += ("Only one player present.\n");
    else
        to_write += ("There are " + size +
	    " players in the game. Within the requested type you know:\n");

    if (index(opts, "n") > -1)
    {
        to_write += (sprintf("%-*#s\n", scrw,
            implode(map(list, "get_name", this_object(), see_invis) - ({ 0 }),
            "\n")));
        /* No need to check for mwho here. */
        write(to_write);
        return 1;
    }

    for(i = 0; i < sizeof(list); i++)
    {
        tmp = (string)list[i]->query_presentation();

        if (list[i]->query_prop(OBJ_I_INVIS) > see_invis)
        {
            if (this_player()->query_wiz_level())
                to_write += ("(" +
                    capitalize(list[i]->query_real_name()) + ")\n");
        }
        else if (strlen(tmp) < scrw)
        {
            to_write += (tmp + "\n");
        }
        else /* Split a too long title in a nice way. */
        {
            title = explode(break_string(tmp, (scrw - 2)), "\n");
            tmp = sprintf("%-*s\n", scrw, title[0]);

            title = explode(break_string(
                implode(title[1..(sizeof(title) - 1)], " "),
                (scrw - 8)), "\n");

            for(j = 0; j < sizeof(title); j++)
                tmp += (sprintf("      %-*s\n", (scrw - 6), title[j]));

            to_write += (tmp);
        }
    }

    if (query_verb() == "mwho")
    {
        setuid();
        seteuid(getuid());
        clone_object(MORE_OBJ)->more(to_write);
    }
    else
        write(to_write);

    return 1;
}

nomask int
sort_name(object a, object b)
{
    string sa = (string)a->query_real_name();
    string sb = (string)b->query_real_name();

    if (sa < sb)
	return -1;
    if (sa == sb)
	return 0;
    return 1;
}

nomask string
get_name(object player, int see_invis)
{
    if (player->query_prop(OBJ_I_INVIS) > see_invis)
    {
	if (this_player()->query_wiz_level())
	{
	    return ("(" + capitalize(player->query_real_name()) + ")");
	}

	return 0;
    }

    return capitalize(player->query_real_name());
}

/*
 * Function name: real_player
 * Description  : This filter is used to remove login objects from the list.
 * Arguments    : object player - the player to test
 * Returns      : int 1/0       - true if a real living
 */
nomask int
real_player(object player)
{
    return (function_exists("create_container", player) == "/std/living");
}

int
who_known(string opts)
{
    object  *list = users() - ({ 0 });
    object  npc;
    mapping rem;
    string  *names = ({ });
    int     t;
    int     size;

    if (!strlen(opts))
         opts = " ";

    /* This filters for players logging in and such. */
    list = filter(list, "real_player", this_object());

    size = sizeof(list);
    if (index(opts, "w") > -1)
        list = filter(list, "is_wiz", WIZ_CMD_APPRENTICE);
    else if (index(opts, "m") > -1)
	list = filter(list, "not_wiz", WIZ_CMD_APPRENTICE);

    /* Wizards won't see the NPC's */
    if (this_player()->query_wiz_level())
	return who(opts, list, sizeof(list));

    if (mappingp(rem = this_player()->query_remembered()))
        names += m_indices(rem);
    if (mappingp(rem = this_player()->query_introduced()))
        names += m_indices(rem);

#ifdef MET_ACTIVE
    for (t = 0; t < sizeof(list); t++)
    {
	if (!(member_array(list[t]->query_real_name(), names) >= 0 ||
	    list[t]->query_prop(LIVE_I_ALWAYSKNOWN) ||
            list[t] == this_player()))
        {
	    list[t] = 0;
        }
    }

    list = list - ({ 0 });
#endif

    if (index(opts, "w") == -1)
    {
	names -= list->query_real_name();

	for (t = 0; t < sizeof(names); t++)
	{
	    if (objectp(npc = find_living(names[t])))
	    {
		list += ({ npc });
		size++;
	    }
	}
    }

    return who(opts, list, size);
}
