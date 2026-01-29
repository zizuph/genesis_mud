/* The Paladine medal for the Solamnian Knight guild.
 *
 * A change has been made to remove the chance for
 * runtime error, too many alarms //Carnak
 */

#pragma save_binary

inherit "/std/object";

#define ARMYMASTER  "/d/Krynn/common/warfare/armymaster"

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <composite.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <state_desc.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Prototype */
void set_up_knight(object player);

static mapping positions = ([ ]);

int knight_level; /* The level of the knight */
int knight_sublevel; /* The sublevel of the knight */
int generous; /* Will the knight be generous and not kill his enemies? */
int primary; /* Which is the primary hand of the knight: 0-right, 1-left */


void
create_object()
{
    if (!IS_CLONE)
	return;

    knight_level = 0;
    knight_sublevel = 0;
    set_name("tunic");
    add_name("pal_med");
    set_short("tunic of the Knighthood");
    set_long("This elegant tunic is embroidered with the symbols of "+
      "the Knighthood. Having been given it when you became a member "+
      "of the Knights, you have worn it since. To get help on the guild "+
      "use 'help guild help'.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    set_no_show_composite(1);
}

string
query_auto_load()
{
    return MASTER_OB(this_object()) + ":" + knight_level + " " +
    knight_sublevel + " " + generous + " " + primary + " ";
}

/* Special Knight 'assist' command */
int
kaid(string str)
{
    object *obs;
    object friend;
    object victim;
    int    index;
    string *assist;
    string fr;
    string str2;
    mixed  tmp;

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

    if (!stringp(str))
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
	obs = PARSE_THIS(str, "[the] %l");

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

    if (environment(victim) != environment(this_player()))
    {
	notify_fail("The main target of " +
	  victim->query_the_name(this_player()) + " is not in this room.\n");
	return 0;
    }

    if (member_array(victim, this_player()->query_team_others()) != -1)
    {
	notify_fail("But " + victim->query_the_name(this_player()) +
	  " is a team with you.\n");
	return 0;
    }

    if (this_player()->query_attack() == victim)
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

    this_player()->reveal_me(1);
    /*
    * Check if we dare!
    */
    if (!F_DARE_ATTACK(this_player(), victim))
    {
      write("Umm... no! You do not have enough self-discipline to dare!\n");
	return 1;
    }

    str = "";

    if (MEMBER(friend))
	str = "fellow Knight";
    else if (TP->query_leader() == friend)
	str = "leader";
    else if (member_array(friend, TP->query_team()) >= 0)
	str = "comrade";
    else
	assist = ({ "Ok.",
	  TP->query_The_name(victim)+" attacks you!",
	  TP->query_The_name(friend)+" assists you and attacks "+
	  victim->query_the_name(friend)+".",
	  QCTNAME(TP)+" assists "+QTNAME(friend)+" and attacks "+
	  QTNAME(victim)+"." });

    if (str != "")
	switch(random(6))
    {

    case 5:
	assist = ({ "Without hesitation, you charge forward to aid "+
	  str+", "+friend->query_the_name(TP)+", against "+
	  POSSESSIVE(friend)+" enemy "+victim->query_the_name(TP)+
	  ".",
	  "Without hesitation, "+TP->query_the_name(victim)+
	  " charges forward to aid "+friend->query_the_name(victim)+
	  " against you!",
	  "Out of the corner of your eye you see "+
	  TP->query_the_name(friend)+"charge forward without "+
	  "hesitation to aid you against your enemy, "+
	  victim->query_the_name(friend)+".",
	  "Without hesitation, "+QTNAME(TP)+" charges forward to "+
	  "aid "+QTNAME(friend)+" against "+QTNAME(victim)+"." });
    case 4:
	assist = ({ "You gallantly rush to the aid of your "+str+", "+
	  friend->query_the_name(TP)+", attacking "+
	  victim->query_the_name(TP)+".",
	  TP->query_The_name(victim)+" gallantly rushes to the aid "+
	  "of "+friend->query_the_name(victim)+" and attacks you!",
	  TP->query_The_name(friend)+" gallantly rushes to your aid, "+
	  "assisting you against "+victim->query_the_name(friend)+".",
	  QCTNAME(TP)+" gallantly rushes to the aid of "+
	  QTNAME(friend)+" and attacks "+QTNAME(victim)+"." });
	break;
    case 3:
	assist = ({ "Shouting out a Solamnian battlecry, you move to "+
	  "assist "+friend->query_the_name(TP)+" in attacking "+
	  victim->query_the_name(TP)+".",
	  "Shouting out a Solamnian battlecry, "+
	  TP->query_the_name(victim)+" moves to assist "+
	  POSSESSIVE(TP)+" "+str+", "+friend->query_the_name(victim)+
	  " and attacks you!",
	  "Shouting out a Solamnian battlecry, "+
	  TP->query_the_name(friend)+" moves to assist you in "+
	  "attacking "+victim->query_the_name(friend)+".",
	  "Shouting out a Solamnian battlecry, "+QTNAME(TP)+
	  " moves to assist "+QTNAME(friend)+" in attacking "+
	  QTNAME(victim)+"." });
	break;
    case 2:
	assist = ({ "Seeing your "+str+" in battle with "+
	  victim->query_the_name(TP)+", you charge into battle "+
	  "alongside "+OBJECTIVE(friend)+".",
	  TP->query_The_name(victim)+" charges into battle "+
	  "alongside "+friend->query_the_name(victim)+" and "+
	  "attacks you!",
	  TP->query_The_name(friend)+" charges into battle "+
	  "alongside you, "+POSSESSIVE(TP)+" "+str+", and attacks "+
	  victim->query_the_name(friend)+".",
	  QCTNAME(TP)+" charges into battle alongside "+QTNAME(friend)+
	  ", and attacks "+QTNAME(victim)+"." });
	break;
    case 1:
	assist = ({ "You rush forward to stand beside your "+str+" and "+
	  "engage "+victim->query_the_name(TP)+" in combat.",
	  TP->query_The_name(victim)+" rushes forward to stand "+
	  "beside "+friend->query_the_name(victim)+", attacking you!",
	  TP->query_The_name(friend)+" rushes forward to stand "+
	  "beside you, attacking "+victim->query_the_name(friend)+".",
	  QCTNAME(TP)+" rushes forward to stand beside "+QTNAME(friend)+
	  ", attacking "+QTNAME(victim)+"." });
	break;
    default:
	assist = ({ "You cry out: 'In loyalty!' as you assist your "+str+
	  ", "+friend->query_the_name(TP)+", against "+
	  victim->query_the_name(TP)+".",
	  TP->query_The_name(victim)+" cries out: 'In loyalty!' as "+
	  PRONOUN(TP)+" "+friend->query_the_name(victim)+" against "+
	  "you!",
	  TP->query_The_name(friend)+" cries out: 'In loyalty!' as "+
	  PRONOUN(TP)+" assists you against "+
	  victim->query_the_name(friend)+".",
	  QCTNAME(TP)+" cries out: 'In loyalty!' as "+PRONOUN(TP)+
	  " assists "+QTNAME(friend)+" against "+QTNAME(victim)+"." });
    }

    say(assist[3] + "\n", ({ this_player(), friend, victim }) );
    tell_object(victim, assist[1]+"\n");
    tell_object(friend, assist[2]+"\n");

    this_player()->attack_object(victim);
    this_player()->add_prop(LIVE_O_LAST_KILL, victim);

    write(assist[0]+"\n");
    return 1;
}

#ifdef MASK_JOIN_CMD
/*
* join - Join someones team
* modified to make Rose Knights able to lead _all_ other Knights
* regardless of dis comparison by Morrigan.
*/
varargs int
join(string name)
{
    object leader;

    if (!strlen(name))
    {
	notify_fail("You must give the name of the player you want as " +
	  "your leader.\n");
	return 0;
    }

    if (this_player()->query_leader())
    {
	write("You already have a leader!\n");
	return 1;
    }

    name = lower_case(name);
    if (!this_player()->query_met(name))
    {
	write("You don't know anyone called '" + capitalize(name) + "'.\n");
	return 1;
    }

    leader = present(name, environment(this_player()));

    if (member_array(this_player(), leader->query_invited()) < 0)
    {
	write(leader->short() + " has not invited you as a team member.\n");
	return 1;
    }

    if (!leader ||
      !leader->check_seen(this_player()))
    {
	write("You don't see " + capitalize(name) + " here.\n");
	return 1;
    }

    /* Knight of the Rose joining function */
    if (MEMBER(leader) && (leader->query_knight_level() == 5 ||
	(ADMIN)->is_grandmaster(leader->query_name()) ||
	leader->has_position() == "General"))
    {
	leader->team_join(this_player());
	write("Your leader is now: " + leader->short() + ".\n");
	say(QCTNAME(this_player()) + " joined the team of " +
	  QTNAME(leader) + ".\n", ({ leader, this_player() }));
	tell_object(leader, this_player()->query_The_name(leader) +
	  " joined your team.\n");
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
	tell_object(leader, this_player()->query_The_name(leader) +
	  " joined your team.\n");
	return 1;
    }
    else
    {
	write(leader->short() + " has not invited you as a team member.\n");
	return 1;
    }
}
#endif MASK_JOIN_CMD

/******************************************************************************
*           KNIGHTS have a special invite command!
* Black Knights may not lead a team (invite) at all! Knights who have recently
* Pkilled have a skill set with the age. They may not lead a team for 2 days
* (AGE!) or until a conclave or assistant has pardoned them.
* This function was moved to the medal from it's original location
* in the soul because it was not called before the other invite
* command from the soul. Additionally, it was modified to allow
* Knights of the Rose to lead anyone, regardless of dis comparisons.
* Nov 95 by Morrigan
*****************************************************************************/
int
invite(string name)
{
    object         *member_list, member;

    /* this is the knight specific part */

    /* if (TP->query_knight_level() == L_BROSE)  */
    //Line above doesn 't seem to cut it, using int instead of macro
    if (TP->query_knight_level() == 1)
    {
	write("Knights of the Black Rose have disgraced the Knights of Solamnia " +
	  "and may not lead any teams.\n");
	return 1;
    }
    if (REALAGE(TP) < TP->query_skill(SS_DISGRACED))
    {/* 2 days playing time! */
	write("You have disgraced the Knights of Solamnia and may not lead a team currently.\n");
	return 1;
    }
    else
	TP->remove_skill(SS_DISGRACED);

    /* end knight specific part */

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
	    else
	    {
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
	return (notify_fail("You have not been introduced!\n"), 0);

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

/* Modified Nov 95 by Morrigan and Aridor to enable the primary command */
void
init_arg(string str)
{
    int i = sscanf(str, "%d %d %d %d", knight_level, knight_sublevel,
      generous, primary);

    if (i < 2)
    {
    	knight_level = 0;
    	knight_sublevel = 0;
    	generous = 0;
    	primary = 0;
    }
    else if (i == 2)
    {
    	generous = 0;
    	primary = 0;
    }
    else if (i == 3)
    	primary = 0;

    if (TP->test_bit("Krynn", 1, 3) == 1)
    {
    	knight_level = 1;
    }
}

void
init()
{
    object * medals;

    seteuid(getuid(TO));

    add_action("kaid", "kaid");

#ifdef MASK_JOIN_CMD
    add_action("join", "join");
#endif

    add_action("invite", "invite");
    
    // If the person has more than one tunic/medal, we want to
    // make sure we remove it if it is not the first one.
    medals = filter(all_inventory(TP), &->id("pal_med"));
    if (sizeof(medals) > 1 && medals[-1..][0] != this_object())
    {
        send_debug_message("pal_med", "Removing extra Knight tunic.");
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
    
    /* Replaced the alarms, the functions is at the bottom
     * of the file
     */
    set_alarm(1.0, 0.0, &set_up_knight(TP));
    
    /* Removed due to runtime error: *too many alarms
    set_alarm(0.0,0.0,"setup_positions", TP);
    set_alarm(1.0,0.0,"set_tax", 0);
    set_alarm(3.0,0.0,"soul", TP);
    set_alarm(5.0,0.0,"adjust_wimpy", TP);
    set_alarm(6.0,0.0,"update_membership",TP);
    set_alarm(7.0,0.0,"check_actions", TP);
    */
}

void
update_membership(object me)
{
    (ADMIN)->add_knight(me->query_real_name(),knight_level);
}

public int
ensure_spur_key(object me)
{
    object key;
    object * allkeys;
    
    if (!objectp(me))
    {
        return 0;
    }
    
    allkeys = filter(all_inventory(me), 
                &wildmatch("/d/Krynn/solamn/hctower/spur/obj/main_key#*") 
                    @ file_name);
    if (sizeof(allkeys))
    {
        // Return 0 if we didn't create a key
        return 0;
    }
    
    key = clone_object("/d/Krynn/solamn/hctower/spur/obj/main_key");
    key->add_prop(OBJ_M_NO_DROP, "You would never drop the "+
      "precious keys to the Spur.\n");
    key->move(me);
    key->set_keep(1);
    
    return 1;
}

void
setup_positions(object me)
{
    int i;
    object key;

    positions = restore_map(APPOINT_FILE);
    if (member_array(me->query_name(), m_values(positions)) < 0)
	return;

    if (positions[POSITIONS[0]] == me->query_name())
    {
        clone_object(SHADOWS + "warden_shadow")->shadow_me(me);
        if (ensure_spur_key(me))
        {
            me->catch_msg("As Warden of the High Clerist's Tower, you "+
              "of course have your personal set of keys to the structure.\n");
        }
    }

    if (positions[POSITIONS[1]] == me->query_name())
    {
	clone_object(SHADOWS + "swordmaster_shadow")->shadow_me(me);
    }

    if (positions[POSITIONS[2]] == me->query_name())
	clone_object(SHADOWS + "general_shadow")->shadow_me(me);

    if (positions[POSITIONS[3]] == me->query_name())
	clone_object(SHADOWS + "east_lt_shadow")->shadow_me(me);

    if (positions[POSITIONS[4]] == me->query_name())
	clone_object(SHADOWS + "south_lt_shadow")->shadow_me(me);

    return;
}

/* Function name: check_actions
* Description:   If the player is in the action list of the admin room,
*                take the appropriate actions.
*/
void
check_actions(object who)
{
    object key;

    /* Give keys to the high clerist for the High Clerist's Tower */
    if (ADMIN->query_conclave("sword") == who->query_name())
    {
        if (ensure_spur_key(who))
        {
        	who->catch_msg("As the High Clerist, you "+
        	  "of course have your personal set of keys to the High Clerist's Tower.\n");
        }
    }

    /* Remove an activated extended leave if a Knight logs during it */
    if (ADMIN->query_activated_extended_leave(L(who->query_name())))
    {
	ADMIN->remove_extended_leave(L(who->query_name()), "ADMIN");
	ADMIN->notify_conclave("ADMIN: "+who->query_name()+" returned from extended leave.");
	ADMIN->log_action("leave", who->query_name()+" returned from extended leave");
    }

    (ADMIN)->check_action_pending(who);
}

/*
* Function name: soul
* Description:   Add the toolsoul and spell object to the member
*/
void
soul(object ob)
{
    int i;
    string *souls;

    seteuid(getuid(TO));
    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
	ob->remove_cmdsoul(souls[i]);
    ob->add_cmdsoul(KNIGHT_SOUL);
    for (i = 0; i < sizeof(souls); i++)
	if (souls[i] != KNIGHT_SOUL)
	    ob->add_cmdsoul(souls[i]);
    ob->update_hooks();

}

/* adjust the wimpy level for those knights that have it too high
*/
void
adjust_wimpy(object ob)
{
    string how;
    int i = ob->query_whimpy();
    int j = WIMPY_LIMIT[knight_level] + WIMPY_LIMIT2[knight_sublevel];
    if (i > j)
    {
	i = 0;
	ob->catch_msg("Your current wimpy level is not allowed for a " +
	  "Knight of Solamnia!\n");
	how = SD_HEALTH[sizeof(SD_HEALTH) * i / 100];
	ob->catch_msg("You are now wimpy at: '" + how + "'. Please " +
	  "adjust your wimpy level to something fitting your station " +
	  "as a Knight of Solamnia.\n");
	ob->set_whimpy(i);
    }
}

/*
* Function name: set_knight_level
* Description:   Set which level the knight has
*/
void
set_knight_level(int level)
{
    object ob = E(TO);

    seteuid(getuid(TO));

    /* Nothing to do if level hasn't changed or is illegal. */
    if (level == knight_level || level < 1 || level > 5)
	return;

    if (knight_level == 1 && level > 3)
	level = 3;

    /*
    if (ob->test_bit("Krynn",1,2) && level > 2)
       level = 2;

    if (level == 5 && !ob->test_bit("Krynn",1,10))
       level = 4;

    if (level == 4 && !ob->test_bit("Krynn",1,9))
       level = 3;
    */

    knight_level = level;

    if (knight_level == 1)
	ob->set_bit(1,3);
    else
    {
	ob->clear_bit(1,3);

	if (knight_level == 2 || knight_level == 3)
	    ob->clear_bit(1,4);
	else
	    ob->set_bit(1,4);

	if (knight_level == 2 || knight_level == 4)
	    ob->clear_bit(1,5);
	else
	    ob->set_bit(1,5);
    }

    (ADMIN)->add_knight(ob->query_real_name(), knight_level, LAYMAN(ob));
    TO->set_tax(0);
}

/*
* Function name: set_knight_sublevel
* Description:   Set which sublevel the knight has
*/
void
set_knight_sublevel(int sublevel)
{
    knight_sublevel = sublevel;
}

/*
* Function name: query_knight_level
* Description:   Ask about the knights level
*/
int
query_knight_level()
{

    return knight_level;
}

/*
* Function name: query_knight_sublevel
* Description:   Ask about the knights sublevel
*/
int
query_knight_sublevel()
{
    if (knight_sublevel == 11 && !(ADMIN->is_conclave(E(TO)->query_name())) &&
	!(ADMIN->is_grandmaster(E(TO)->query_name())))
	knight_sublevel = 10;

    return knight_sublevel;
}

/*
* Function name: set_tax
* Description:   Update the tax of the member
*/
void
set_tax(int i)
{
    int stat, old_tax, new_tax;
    int tax, pen, areas, total;
    object ob;

    ob = E(TO);
    if (!knight_sublevel)
    {
	ob->set_skill(SS_PRESTIGE_ST,
	  ob->exp_to_stat(ob->query_skill(SS_PRESTIGE_ACC)));
	stat = ob->query_skill(SS_PRESTIGE_ST);
	if (stat < 20 && !ob->query_skill(SS_PRESTIGE_ACC))
	{
	    ob->set_skill(SS_PRESTIGE_ST, 20);
	    ob->set_skill(SS_PRESTIGE_ACC, 20 * 20 * 20 + 100);
	    stat = 20;
	}

	if (ob->test_bit("Krynn", 1, 4) == 0)
	{
	    if (ob->test_bit("Krynn", 1, 5) == 0)
		knight_level = 2;
	    if (ob->test_bit("Krynn", 1, 5) == 1)
		knight_level = 3;
	}

	if (ob->test_bit("Krynn", 1, 4) == 1)
	{
	    if (ob->test_bit("Krynn", 1, 5) == 0)
		knight_level = 4;
	    if (ob->test_bit("Krynn", 1, 5) == 1)
		knight_level = 5;
	}


	if (ob->test_bit("Krynn",1 ,3) == 1)
	    knight_level = 1;

	if (knight_sublevel && !ob->query_skill(SS_PRESTIGE_ACC))
	{
	    ob->set_skill(SS_PRESTIGE_ACC, ob->query_acc_exp(SS_OCCUP));
	    ob->set_skill(SS_PRESTIGE_ST,
	      ob->exp_to_stats(ob->query_skill(SS_PRESTIGE_ACC)));
	}

	knight_sublevel = L_1;
	if (stat >= SS_LEVEL1)
	    knight_sublevel = L_2;
	if (stat >= SS_LEVEL2)
	    knight_sublevel = L_3;
	if (stat >= SS_LEVEL3)
	    knight_sublevel = L_4;
	if (stat >= SS_LEVEL4)
	    knight_sublevel = L_5;
	if (stat >= SS_LEVEL5)
	    knight_sublevel = L_6;
	if (stat >= SS_LEVEL6)
	    knight_sublevel = L_7;
	if (stat >= SS_LEVEL7)
	    knight_sublevel = L_8;
	if (stat >= SS_LEVEL8)
	    knight_sublevel = L_9;
	if (stat >= SS_LEVEL9)
	    knight_sublevel = L_10;
    }

    if ((ADMIN)->query_grandmaster() == ob->query_real_name() ||
      (ADMIN)->query_conclave("crown") == ob->query_name() ||
      (ADMIN)->query_conclave("sword") == ob->query_name() ||
      (ADMIN)->query_conclave("rose") == ob->query_name())
	knight_sublevel = 11;

    new_tax = TAX[knight_level];
/*
  Petros, May 2011 - Removing the armoury tax because the saving racks
                     reduce the usefulness of the high armoury.
                     
    if (knight_level > 3)
	new_tax += ARMOURY_TAX;
    if (knight_level == 3 && knight_sublevel > 8)
	new_tax += ARMOURY_TAX;
*/
    if (ARMYMASTER->query_peace() == 0)
    {
    total = sizeof(ARMYMASTER->query_areas());
    areas = sizeof(ARMYMASTER->query_areas_of_army("Knights"));
    pen = (total / 2) - areas;
    new_tax += pen;
    }


    old_tax = ob->query_learn_pref(SS_OCCUP);

    if (new_tax != old_tax)
	ob->set_guild_pref(SS_OCCUP, new_tax);

    if (!ob->query_guild_member_lay() && ob->query_learn_pref(SS_LAYMAN))
	ob->set_guild_pref(SS_LAYMAN, 0);

    if (!ob->query_guild_member_race() && ob->query_learn_pref(SS_RACE))
	ob->set_guild_pref(SS_RACE, 0);
}

/* if the player isn't devoted to Paladine remove some prestige
 * once in a while
 */
/*
void
decay_prestige()
{
   object who = E(TO);
   int when = who->query_prop(KNIGHT_I_DEVOTION);

   if (!who || !interactive(who))
      return;

   if (when < who->query_age())
      {
      if (who->query_skill(SS_PRESTIGE_ACC) > 2000)
	 who->change_prestige((MEMBER(who) ? -200 : -40),1);
   }
   else
      who->change_prestige(3);
}
*/

int
query_generous()
{
    return generous;
}

void
set_generous(int what)
{
    generous = what;
}

int
query_primary()
{
    return primary;
}

void
set_primary(int what)
{
    primary = what;
}

/*
 * Function:        set_up_knights
 * Descriptions:    This was added to handle the old init alarms
 */
void
set_up_knight(object player)
{
    setup_positions(player);
    set_tax(0);
    soul(player);
    adjust_wimpy(player);
    update_membership(player);
    check_actions(player);
}
