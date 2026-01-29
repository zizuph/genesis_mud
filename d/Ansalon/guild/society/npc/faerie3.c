/*
 * /d/Ansalon/guild/society/npc/faerie.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Coded by Gwyneth on December 2000
 */
inherit "/std/npc";

#include <const.h>
#include <cmdparse.h>
#include <files.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <../guild.h>

#define DELAY			5.0
#define FAERIE_TREE		(KGROOM + "faerie_tree")
#define LIVE_I_FAERIE_ATTACKER	"_live_i_faerie_attacker_"
#define MESSAGE			(KGOBJ + "scroll")
#define TEMP_ROOM		(KGROOM + "faerie_temp")

/* Global Variables */
string gAdj1   = "tiny";
string gAdj2   = "nude";
string *gAdorn = ({ "a small silver ring" });
string gEyes1  = "wise";
string gEyes2  = "rainbow";
string gHair1  = "shoulder length";
string gHair2  = "snow white";
string gHair3  = "styled with a top-knot";
string gName   = "faerie";
string gOwner  = "unknown";
int gGender    = G_MALE;

static string gComm1, gComm2, gMessage, gSender, gWho;

/* Prototypes */
public string attack_func();
public void faerie_setup();
public void fly_to_owner();
public void fly_away();
public int quit_test();

public string query_message() { return gMessage; }
public string query_sender() { return gSender; }
public string query_recipient() { return gWho; }
public string query_owner() { return gOwner; }

public void
create_npc()
{
	set_race_name("faerie");

	set_living_name("faerie");

	add_prop(OBJ_M_NO_ATTACK, &attack_func());
	add_prop(OBJ_M_NO_MAGIC_ATTACK, &attack_func());
	add_prop(OBJ_I_WEIGHT, 30);
	add_prop(OBJ_I_VOLUME, 32);
	add_prop(CONT_I_WEIGHT, 30);
	add_prop(CONT_I_VOLUME, 32);
	add_prop(CONT_I_HEIGHT, 7);
	add_prop(NPC_I_NO_LOOKS, 1);
	add_prop(NPC_M_NO_ACCEPT_GIVE, " giggles and dances away, " +
		"refusing to take your gift.\n");
	add_prop(OBJ_M_NO_DROP, &quit_test());
	remove_prop(OBJ_M_NO_GET);

	set_skill(SS_AWARENESS, 100);
	set_alarm(0.2, 0.0, &faerie_setup());
}

public int
quit_test()
{
	return (query_verb() == "quit");
}

public void
leave_env(object from, object to)
{
	::leave_env(from, to);

	if (to->id("corpse"))
	{
		set_alarm(1.0, 0.0, &fly_away());
	}
}

public void
faerie_hair(string hair1, string hair2, string hair3)
{
	gHair1 = hair1;
	gHair2 = hair2;
	gHair3 = hair3;
}

public void
faerie_eyes(string eyes1, string eyes2)
{
	gEyes1 = eyes1;
	gEyes2 = eyes2;
}

public void
faerie_name(string name)
{
	if (strlen(gName))
	{
		remove_name(gName);
	}
	gName = name;
	set_name(gName);
	add_name("faerie");
}

public string
short_desc()
{
	string gender = query_gender_string();
	return(gAdj1 + " " + gAdj2 + " " + gender + 
		" faerie");
}

public void
faerie_adjs(string adj1, string adj2)
{
	gAdj1 = adj1;
	gAdj2 = adj2;
	remove_adj("tiny");
	remove_adj("nude");
	set_adj(({ gAdj1, gAdj2 }));
	set_short("@@short_desc");
}

public void
faerie_adorn(string adorn)
{
	if (member_array(adorn, gAdorn) == -1)
	{
		gAdorn += ({ adorn });
	}
	else
	{
		gAdorn -= ({ adorn });
	}
}

public void
faerie_gender(int gender)
{
	gGender = gender;
	set_gender(gGender);
}

public void
faerie_owner(string owner)
{
	gOwner = owner;
}

public string
long_desc()
{
	string extra, He_She = capitalize(query_pronoun());

	extra = "This is a " + gAdj1 + " " + gAdj2 +
		" " + query_gender_string() + " faerie.\n";
	extra += He_She + " might deliver a message for you " +
		"if you wish to 'send' one. You might also convince " +
		query_objective() + " to 'resend' the message or " +
		"'send a reply'. If you want, you may 'return' " +
		query_objective() + ".\n";
	if (this_player()->query_real_name() == gOwner)
	{
		extra += "You might be able to communicate more with " +
			"your faerie with a wish.\n";
		if (gName != "unknown")
		{
			extra += "You recognize " + query_objective() +
				" as " + capitalize(gName) + ".\n";
		}
	}
	extra += He_She + " is the image of perfection.\n";
	extra += He_She + " is surrounded by a shimmering aura.\n";
	extra += capitalize(query_possessive()) + " hair is " + gHair1 + 
		", " + gHair2 + " and " + gHair3 + ".\n";
	extra += He_She + " has " + gEyes1 + " " + gEyes2 + " eyes.\n";
	extra += He_She + " is wearing " + implode(gAdorn, ", ") +
		" and a tiny belt of pouches.\n";
	extra += He_She + " has a pair of delicate wings.\n";

	return extra;
}

public void
faerie_setup()
{
	set_name(gName);
	set_adj(({ gAdj1, gAdj2 }));
	set_gender(gGender);
	set_long(&long_desc());
}

public void
tell_can_see(object who, string text)
{
	int i, size;
	object *oblist;

	oblist = FILTER_PRESENT_LIVE(all_inventory(environment(who)));
	oblist -= ({ who });
	oblist = FILTER_PLAYERS(oblist);
	oblist = FILTER_IS_SEEN(who, oblist);

	for (i = 0, size = sizeof(oblist);i < size;i++)
	{
		oblist[i]->catch_msg(text);
	}
}

public string
attack_func()
{
	write(capitalize(LANG_THESHORT(this_object())) + " flutters " + 
		query_possessive() + " wings and flies away as " +
		query_pronoun() + " detects your aggressive intentions.\n");
	tell_can_see(this_player(), capitalize(LANG_ASHORT(this_object())) + 
		" flutters " + query_possessive() +
		" wings and flies away from " + QTNAME(this_player()) +
		" in fright.\n");
	move(TEMP_ROOM, 1);
	set_alarm(DELAY, 0.0, &fly_to_owner());
	this_player()->add_prop(LIVE_I_FAERIE_ATTACKER, 1);
	return "";
}

public void
normal_receive_message(object who)
{
	who->catch_tell(capitalize(LANG_ASHORT(this_object())) + 
		" flutters down from above and lands on your " +
		"shoulder, handing you a rolled up scroll from " +
		capitalize(gSender) + ".\n");
	tell_can_see(who, capitalize(LANG_ASHORT(this_object())) + 
		" flutters down from above and lands on " + QTPNAME(who) + 
		" shoulder, handing " + who->query_objective() + " a " +
		"rolled up scroll.\n");
}

public void
heavy_receive_message(object who)
{
	who->catch_tell(capitalize(query_pronoun()) + " flies away again " + 
		"when " + query_pronoun() + " realizes how burdened you " +
		"are.\n");
	tell_can_see(who, 
		capitalize(LANG_THESHORT(this_object())) + " flutters " + 
		query_possessive() + " wings and flies away again.\n");
}

public void
failed_message()
{
	object sender = find_player(gSender);

	sender->catch_tell(capitalize(LANG_THESHORT(this_object())) + 
		" returns, unable to find " + capitalize(gWho) + ".\n");
	tell_can_see(sender, QCTNAME(sender) + " holds out " + 
		sender->query_possessive() + " hand for " + 
		LANG_ASHORT(this_object()) + " to land on.\n");
}

public void
normal_send_message()
{
	object sender = find_player(gSender);

	write("You roll up the scroll and hand it to " +
		LANG_THESHORT(this_object()) + ", asking " + 
		query_objective() + " to deliver it to " + 
		capitalize(gWho) + ". " + 
		capitalize(LANG_THESHORT(this_object())) + " flutters " + 
		query_possessive() + " wings and flies away in search of " + 
		capitalize(gWho) + ".\n");
	tell_can_see(sender, QCTNAME(sender) + " rolls up a scroll, " +
		"hands it to " + LANG_ASHORT(this_object()) + " and " +
		"whispers something to " + query_objective() + " before " +
		LANG_THESHORT(this_object()) + " flutters " + 
		query_possessive() + " wings and flies away.\n");
}

public void
deliver_message()
{
	object scroll;
	object sender = find_player(gSender);
	object who = find_player(gWho);

	/* Failed to find the player, or player is linkdead. */
	if (!objectp(who) ||
	  !interactive(who))
	{
		if (!objectp(sender))
		{
			return;
		}

		set_alarm(0.1, 0.0, &failed_message());

		/* Sender can't carry faerie, sent to faerie room */
		if (move(sender))
		{
			set_alarm(0.2, 0.0, &heavy_receive_message(who));
			set_alarm(0.3, 0.0, &remove_object());
		}
	}
	else
	{
		set_alarm(0.1, 0.0, &normal_receive_message(who));
		scroll = clone_object(MESSAGE);
		scroll->set_message(gMessage);
		scroll->set_sender(gSender);
		scroll->move(who, 1);

		if (move(who))
		{
			set_alarm(0.2, 0.0, &heavy_receive_message(who));
			set_alarm(0.3, 0.0, &remove_object());
		}
	}
}

public int
edit_message(string message)
{
	if (!strlen(message))
	{
		write("You set down your quill, deciding " +
			"not to write that message after all.\n");
		return 1;
	}

	gMessage = message;

	gSender = this_player()->query_real_name();
	set_alarm(0.1, 0.0, &normal_send_message());
	move(TEMP_ROOM, 1);
	set_alarm(DELAY, 0.0, &deliver_message());
	return 1;
}

private int
send_message(string str)
{
	if (!strlen(str))
	{
		notify_fail("Send a message to whom?\n");
		return 0;
	}

	if (SECURITY->query_wiz_level(str) &&
	  !this_player()->query_wiz_level())
	{
		notify_fail(capitalize(LANG_THESHORT(this_object())) + 
			" shakes " + query_possessive() + " head, " +
			"refusing to disturb a wizard.\n");
		return 0;
	}
	else if (lower_case(str) == "reply" ||
	  lower_case(str) == "a reply")
	{
		if (stringp(gSender) &&
		  this_player()->query_real_name() != gSender &&
		  this_player()->query_real_name() == gWho)
		{
			str = gSender;
		}
		else
		{
			notify_fail("You have to have received a message " +
				"to send a reply.\n");
			return 0;
		}
	}

	write("You begin to jot down a message for " +
		capitalize(str) + ".\n");
	gWho = lower_case(str);
	clone_object(EDITOR_OBJECT)->edit(&edit_message());
	return 1;
}

public void
fly_to_owner()
{
	object owner = find_player(gOwner);

        string message = (capitalize(LANG_THESHORT(this_object())) + 
		" flutters " + query_possessive() + " wings and " +
		"flies away in a swirl of faerie dust.\n");

	if (objectp(environment()))
	{
		if (IS_PLAYER_OBJECT(environment()))
		{
			tell_room(environment(environment()), message,
				environment(), this_object());
			environment()->catch_tell(message);
		}
		if (IS_ROOM_OBJECT(environment()))
		{
			tell_room(environment(), message, 0, this_object());
		}
	}
	if (objectp(owner))
	{
		owner->catch_tell("Your friend, " + 
			LANG_THESHORT(this_object()) + " flutters down " +
			"from above, landing on your shoulder.\n");
		tell_can_see(owner,
			capitalize(LANG_ASHORT(this_object())) + 
			" flutters down from above, landing on " +
			QTPNAME(owner) + " shoulder.\n");

		if (move(owner))
		{
			&heavy_receive_message(owner);
			set_alarm(0.1, 0.0, &remove_object());
			return;
		}
	}
	else
	{
		set_alarm(0.1, 0.0, &remove_object());
		return;
	}
}

public void
fly_away()
{
	string message = (capitalize(LANG_THESHORT(this_object())) +
		" flutters " + query_possessive() + " wings and " +
		"flies away in a swirl of faerie dust.\n");
	if (IS_PLAYER_OBJECT(environment()))
	{
		tell_room(environment(environment()), message, 
			environment(), this_object());
		environment()->catch_tell(message);
	}
	if (IS_CORPSE_OBJECT(environment()))
	{
		tell_room(environment(environment()), message);
	}
	if (IS_ROOM_OBJECT(environment()))
	{
		tell_room(environment(), message, 0, this_object());
	}

	set_alarm(0.2, 0.0, &remove_object());
}

private int
return_faerie(string str)
{
	object owner = find_player(gOwner);
	object *faeries;

	faeries = FIND_STR_IN_OBJECT(str, this_player());

	if (member_array(this_object(), faeries) != -1)
	{
		write("You send " + LANG_THESHORT(this_object()) + 
			" away. " + capitalize(LANG_THESHORT(this_object())) + 
			" flutters " + query_possessive() + " wings and " +
			"flies away.\n");
		tell_can_see(this_player(), QCTNAME(this_player()) + 
			" sends " + LANG_ASHORT(this_object()) + " away. " + 
			capitalize(LANG_THESHORT(this_object())) + 
			" flutters " + query_possessive() + " wings " +
			"and flies away.\n");
	}
	else
	{
		return 0;
	}

	if (!objectp(owner))
	{
		set_alarm(0.1, 0.0, &remove_object());
	}
	else if (this_player()->query_real_name() == gOwner)
	{
		set_alarm(0.1, 0.0, &remove_object());
	}
	else
	{
		move(TEMP_ROOM, 1);
		set_alarm(DELAY, 0.0, &fly_to_owner());
	}

	return 1;
}

private int
resend_message(string str)
{
	if (this_player()->query_real_name() == gOwner)
	{
		set_alarm(0.1, 0.0, &normal_send_message());
		move(TEMP_ROOM, 1);
		set_alarm(DELAY, 0.0, &deliver_message());
		return 1;
	}
	else
	{
		notify_fail("You can't resend a message that you " +
			"haven't written yet.\n");
		return 0;
	}
}

public void
do_faerie_emote(string emote, object target)
{
	if (!present(target, environment(this_object())))
	{
		if (objectp(target))
		{
			move(environment(target), 1);
			tell_room(environment(target),
				capitalize(LANG_ASHORT(this_object())) +
				" arrives in a swirl of faerie dust.\n");
		}
		else
		{
			fly_to_owner();
		}

	}

	command(emote);
}

public void
settle_down(object who)
{
	if (objectp(who))
	{
		if (move(who))
		{
			set_alarm(0.1, 0.0, &heavy_receive_message(who));
			set_alarm(0.2, 0.0, &remove_object());
			return;
		}
		else
		{
			who->catch_tell(
				capitalize(LANG_THESHORT(this_object())) +
				" settles gently upon your shoulder.\n");
			tell_can_see(who, 
				capitalize(LANG_THESHORT(this_object())) +
				" settles gently upon " + QTPNAME(who) +
				" shoulder.\n");
		}
	}
	else
	{
		fly_to_owner();
	}
}

public void
perform_wish()
{
	float num, num2, num3;
	object target = find_player(gWho);

	if (!objectp(target) ||
	  !interactive(target))
	{
		set_alarm(DELAY, 0.0, &failed_message());
		
		if (objectp(find_living(gOwner)))
		{
			if (move(find_living(gOwner)))
			{
				&heavy_receive_message(find_living(gOwner));
				set_alarm(0.1, 0.0, &remove_object());
				return;
			}
		}
		else
		{
			set_alarm(0.1, 0.0, &remove_object());
		}

		return;
	}
	else
	{
		move(environment(target), 1);
		tell_room(environment(target), 
			capitalize(LANG_ASHORT(this_object())) +
			" arrives in a swirl of faerie dust.\n");
		num  = rnd() + 1.0;
		num2 = rnd() + 1.0;
		num3 = rnd() + 1.0;
		set_alarm(num, 0.0, &do_faerie_emote(gComm1, target));
		set_alarm(num + num2, 0.0, &do_faerie_emote(gComm2, target));
		set_alarm(num + num2 + num3, 0.0, &settle_down(target));
		return;
	}
}

private int
faerie_wish(string str)
{
	string *command, *command1, *command2, *command3;

	if (gOwner != this_player()->query_real_name())
	{
		return 0;
	}

	if (!strlen(str))
	{
		notify_fail("Syntax is: 'wish find <player>, " +
			"[emote], [emote]'.\n");
		return 0;
	}
	
	command = explode(str, ",");

	gComm1 = "";
	gComm2 = "";
	gSender = this_player()->query_real_name();

	/* Note, there is only one break in this switch */
	switch(sizeof(command))
	{
	case 3:
		command3 = explode(command[2], " ");
		command3 -= ({""});

		if (!SOUL_CMD->exist_command(command3[0]) &&
		  (command3[0] != "whisper" && 
		  command3[0] != "say" &&
		  command3[0] != "shout" &&
		  command3[0] != "asay"))
		{
			notify_fail(capitalize(command3[0]) + 
				" is not something your faerie knows " +
				"how to do.\n");
			return 0;
		}

		gComm2 = command[2];
	case 2:
		command2= explode(command[1], " ");
		command2 -= ({""});

		if (!SOUL_CMD->exist_command(command2[0]) &&
		  (command2[0] != "whisper" && 
		  command2[0] != "say" &&
		  command2[0] != "shout" &&
		  command2[0] != "asay"))
		{
			notify_fail(capitalize(command2[0]) + 
				" is not something your faerie knows " +
				"how to do.\n");
			return 0;
		}

		gComm1 = command[1];
	case 1:
		command1 = explode(command[0], " ");
		if (sizeof(command1) < 2)
		{
			notify_fail("Find which player?\n");
			return 0;
		}
		if (command1[0] != "find")
		{
			notify_fail("Syntax is: 'wish find <player>, " +
				"[emote], [emote]'.\n");
			return 0;
		}
		if (SECURITY->query_wiz_level(lower_case(command1[1])) &&
		  !this_player()->query_wiz_level())
		{
			notify_fail(capitalize(LANG_THESHORT(this_object())) +
				" shakes " + query_possessive() + " head, " +
				"refusing to disturb a wizard.\n");
			return 0;
		}

		gWho = lower_case(command1[1]);
		break;
	default:
		notify_fail("Syntax is: 'wish find <player>, " +
			"[emote], [emote]'.\n");
		return 0;
	}
	

	write("You send your faerie off to find " + capitalize(gWho) + 
		".\n");
	move(TEMP_ROOM, 1);
	set_alarm(DELAY, 0.0, &perform_wish());
	return 1;
}

public void
init_living()
{
	add_action(send_message,   "send");
	add_action(return_faerie,  "return");
	add_action(resend_message, "resend");
	add_action(faerie_wish, "wish");
}
