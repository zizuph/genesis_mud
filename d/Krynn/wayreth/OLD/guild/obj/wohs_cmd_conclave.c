/*
 * The conclave soul.
 *
 * It holds all the commands the conclave members are allowed to do.
 */

/*
 * TODO:
 *   Make expel
 */
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <macros.h>
#include "../local.h"
#include "../../local.h"
#include "/d/Krynn/common/defs.h"
#include <language.h>

static gTmp;              /* Used by CHECK_IN_TOWER */

#define CHECK_SO_CONCLAVE if (!IS_CONCLAVE(RNAME(TP))) return 0;
#define CHECK_IN_TOWER    if (!TP->query_wiz_level() && \
			      !(E(TP) && sscanf(file_name(E(TP)), WTOWER + \
		              "%s", gTmp))) return NF("This command may " + \
			      "only be performed while inside a Tower " + \
			      "of High Sorcery.\n");


/*
 * The name of the soul.
 */
public string 
get_soul_id() { return "Conclave of WoHS"; }

/*
 * It is a command soul.
 */
public int 
query_cmd_soul() 
{ 
    return 1; 
}

/*
 * The list of verbs and functions. Please add new in alfabetical order.
 */
public mapping
query_cmdlist()
{
    return (["waccept"  : "waccept",
	     "wbanish"  : "wbanish",
	     "wexpel"   : "wexpel",
             "wpromote" : "wpromote",
	     "wreward"  : "wreward", 
	     "wpunish"  : "wpunish",
	     "wresign"  : "wresign",
	     "wfullwiz" : "wfullwiz",
           ]);
}

public int
wresign(string str)
{
    string type = C(ADMIN->query_member_type(TP));

    CHECK_SO_CONCLAVE;

    CHECK_IN_TOWER;

    if ((str) && (parse_command(str, ({ }), "[from] [the] " +
	 "'conclave' / 'Conclave' / 'Head of the " + type + " Robes'")))
      {
	ADMIN->remove_conclave_member(TP);
        setuid();
        seteuid(getuid());

        log_file("/d/Krynn/log/guild/wohs/record", ctime(time()) + " " + 
		 C(RNAME(TP)) + " resigned as the head of the " +
		 type + " Robes"+
		 ".\n",50000);
	write("You are no longer the Head of the " + type + " Robes.\n");
	return 1;
      }
    write("Are you sure? If you are, <wresign from the conclave> "+
	"or <wresign from the Head of the " + type + " Robes.\n"+
	"This is permanant, and to be reinstated will take the "+
	"actions of another Conclave Member.\n");
    return 1;
}

public int
waccept(string str)
{
    string type = ADMIN->query_member_type(TP);
    object a_ply;

    CHECK_SO_CONCLAVE;

    CHECK_IN_TOWER;

    NF("Whom do you want to accept?\n");
    if (!str || !strlen(str))
        return 0;

    a_ply = find_player(lower_case(str));

    if (!objectp(a_ply) || !present(a_ply, E(TP)))
        return 0;

    if (!TP->query_met(a_ply))
        return NF("You don't know anyone by that name?");

    if (THIS_GUILD(a_ply))
        return NF(a_ply->query_name() + " has already been granted the " +
		  "power of Magic.\n");

    if (ADMIN->query_accept_busy(type))
        return NF("The gods are busy at the moment.\n");

    write("You whisper the words of the spell that will summon " +
	  "the three gods of Magic.\n");
    tell_room(E(TP), QCTNAME(TP) + " starts to whisper words in the " +
	      "spidery language of magic.\n", TP);

    ADMIN->accept_seq(a_ply);
    return 1;
}

public int
wbanish(string str)
{
}

public int
wdemote(string str)
{
    string name, reason;
    int level, pl_level, acc_level;
    object pl, book;

    CHECK_SO_CONCLAVE;

    CHECK_IN_TOWER;

    if (sscanf(str, "%s %d because %s", name, level, reason) != 3)
        return NF(C(query_verb()) + " whom how many levels because what?\n");

    if ((level < 1) || (level > 3))
        return NF("You may only demote 1-3 levels at the time.\n");

    if (!(pl = find_player(name)))
        return NF("No player with that name in the game at the moment.\n");

    if (pl == TP)
        return NF("You can't demote yourself.\n");

    if (!IS_MEMBER(pl))
        return NF(C(name) + " is not a member of the High Sorcery.\n");

    if (ADMIN->query_member_type(pl) == TYPE_APPRENTICE)
        return NF("You can't demote an apprentice wizard.\n");

    if (!(pl_level = pl->query_wohs_level()))
        return NF(C(name) + " can't be demoted any further.\n");

    if (IS_CONCLAVE(RNAME(pl)))
    {
        /* Demote master */
    }

    pl->change_level_mod(-level);

    pl->catch_msg("You feel a sudden pain all over your body, as you " +
		  "feel the anger of " + QTNAME(TP) + ".\n");

    write("You demote " + C(name) + " "+ LANG_WNUM(level) + " " + 
	  (level == 1 ? "level" : "levels") + ".\n");

    tell_room(E(pl), QCTNAME(pl) + " crings from a sudden jolt of " +
	      "invisible pain.\n", ({ pl, TP }));

    log_file("/d/Krynn/log/guild/wohs/record", ctime(time()) + " " + 
	     C(RNAME(TP)) + " demoted " +
	     C(name) + " " + LANG_WNUM(level) + " " +
	     (level == 1 ? "level" : "levels") + " because " + reason + 
	     ".\n",50000);

    if(book = present(SPELL_BOOK, E(pl)))
	book->setup_spells(pl->query_wohs_level());
    return 1;
}

public int
wexpel(string str)
{
    object whom;

    CHECK_SO_CONCLAVE;

    if (!str || !strlen(str))
        return NF("Expel whom?\n");

    str = lower_case(str);
    whom = find_player(str);

    if (!objectp(whom) || !THIS_GUILD(whom))
        return NF("There is no wizard with that name within this world.\n");

    if (E(whom) != E(TP))
        return NF("The one that you want to expel must be present.\n");

    if (whom == TP)
        return NF("If you want to leave, do so at the proper place.\n");

    if ((ADMIN->query_member_type(whom) != TYPE_APPRENTICE) &&
	(ADMIN->query_wohs_head() != RNAME(TP)) &&
	(ADMIN->query_member_type(TP) != ADMIN->query_member_type(whom)))
        return NF("You don't have the powers to do that.\n");

    if (!ADMIN->remove_wohs_member(whom, 1))
    {
        write("Can't expel " + C(str) + " due to a bug. You know what to " +
	      "do.\n");
	return 1;
    }
    
    write("You have now expelled " + C(str) + " from the guild.\n");
    return 1;
}

public int
wpromote(string str)
{
    string name, what;
    int level, pl_level, acc_level;
    object whom, book;

    CHECK_SO_CONCLAVE;

    CHECK_IN_TOWER;

    if (!str || !strlen(str))
        return NF("Promote whom?\n");

    NF("Promote whom to the head of what?\n");
    if (!parse_command(str, ({}), "%s 'to' [the] 'head' 'of' [the] " +
		       "%s", name, what))
        return 0;

    what = lower_case(what);
    if (what != "orders")
        if (sscanf(what, "%s robes", what) != 1)
	    return 0;

    if ((what != "orders") && (what != "white") && (what != "red") && 
	(what != "black"))
        return NF("You can't promote someone to that.\n");

    whom = find_player(name);
    
    if (!objectp(whom) || !THIS_GUILD(whom))
        return NF("There is no wizard with that name within this world.\n");

    if (E(whom) != E(TP))
        return NF("The one to receive the promotion must be present.\n");

    if (whom == TP)
        return NF("You may not promote yourself.\n");

    if (ADMIN->query_member_type(whom) == TYPE_APPRENTICE)
        return NF("You can't promote an apprentice.\n");

    if (what == "orders")
    {
        if (strlen(ADMIN->query_wohs_head()))
	    return NF(C(ADMIN->query_wohs_head()) + " is already " +
		      "the Head of the Orders.\n");

        if (!IS_CONCLAVE(name))
	    return NF(C(name) + " must be a member of the Conclave.\n");

        if (!ADMIN->query_vote_head(whom))
	    return NF(C(name) + " doesn't have enough votes to be " +
		      "promoted to Head of the Orders.\n");

        ADMIN->set_wohs_head(RNAME(whom));

	write("You have promoted " + C(name) + " to the Head " +
	      "of the Orders.\n");
	whom->catch_msg("You are now Head of the Orders.\n");
	tell_room(E(whom), QCTNAME(whom) + " has been promoted to the " +
		  "Head of the Orders of by " + QCTNAME(TP) + ".\n", 
		  ({ TP, whom }));

	setuid();
	seteuid(getuid());

	log_file("/d/Krynn/log/guild/wohs/record", ctime(time()) + " " + 
		   C(RNAME(TP)) + " promoted " +
		   C(name) + " to the leader of the Orders.\n",50000);
	return 1;
    } 
    else
    {
        if (strlen(ADMIN->query_wohs_head()) && 
	    RNAME(TP) != ADMIN->query_wohs_head())
            return NF("You don't have sufficient power to do that.\n");

        if ((sizeof(ADMIN->query_conclave_member()) == 3) || 
	    ADMIN->query_conclave_head(what))
	    return NF("The position as the Head of the Order of " + 
		      C(what) + " robes, is already take.\n");

        if (ADMIN->query_member_type(whom) != what)
	    return NF(C(name) + " is not a member of that order.\n");

        if (!ADMIN->query_vote_conclave(whom, what))
	    return NF(C(name) + " doesn't have enough votes to be " + 
		      "promoted to the Head of the Order of " + C(what) +
		      " robes.\n");

        ADMIN->add_conclave_member(whom);
	write("You have promoted " + QCTNAME(whom) + " to the Head " +
	      "of the Order of " + C(what) + " robes.\n");
	whom->catch_msg("You are now Head of the Order of " + C(what) + 
			" robes.\n");
	tell_room(E(whom), QCTNAME(whom) + " has been promoted to the " +
		  "Head of the Order of " + C(what) + " robes by " +
		  QCTNAME(TP) + ".\n", ({ TP, whom }));

	setuid();
	seteuid(getuid());

	log_file("/d/Krynn/log/guild/wohs/record", ctime(time()) + " " + 
		 C(RNAME(TP)) + " promoted " +
		 C(name) + " to the leader of the " + C(what) + 
		 " robes.\n",50000);
	if(book = present(SPELL_BOOK, E(whom)))
	    book->setup_spells(whom->query_wohs_level());
	return 1;
    }
}

public int
wreward(string str)
{
    object whom, book;
    string name, reason;
    int rank, w_level;

    CHECK_SO_CONCLAVE;

    if (!str || !strlen(str))
        return NF("Reward whom?\n");

    if (!parse_command(str, ({}), "%s 'with' %d 'rank' / 'ranks' " +
		       "'because' %s", name, rank, reason))
        return NF("Reward whom with how many ranks because of what?\n");

    if ((rank > 3) || (rank < 1))
        return NF("You may only reward someone with one, two or three " +
		  "ranks.\n");

    name = lower_case(name);
    whom = find_player(name);

    NF("Nobody with that name is a member within your order.\n");
    if (!objectp(whom) || !THIS_GUILD(whom))
        return 0;

    if ((ADMIN->query_member_type(whom) != TYPE_APPRENTICE) && 
	(ADMIN->query_member_type(whom) != ADMIN->query_member_type(TP)) &&
	(RNAME(TP) != ADMIN->query_wohs_head()))
        return 0;

    if (TP == whom)
        return NF("Who do you think you are? You can't reward yourself.\n");

//    if (E(whom) != E(TP))
//        return NF(C(name) + " must be present when getting rewarded.\n");

    if ((w_level = whom->query_wohs_level()) >= ADMIN->query_number_levels()-1)
        return NF(C(name) + " can't be rewarded anymore ranks.\n");

    if ((ADMIN->query_size_apprentice_titles() <= (w_level + rank)) &&
	(ADMIN->query_member_type(whom) == TYPE_APPRENTICE))
        return NF(C(name) + " is only an apprentice and can't be " +
		  "rewarded to that kind of rank.\n");

    if ((ADMIN->query_number_levels() - w_level - 1) < rank)
        return NF("You can't reward " + C(name) + " with so many ranks.\n");

    whom->change_level_mod(rank);

    whom->catch_msg("You feel a new and refreshing power, power " +
		  "given to you by " + QTNAME(TP) + ".\n");
    write("With the powers given to you by " + ADMIN->query_wohs_god(TP) +
	  ", you grant " + C(name) + " additional power.\n");
    tell_room(E(whom), QCTNAME(whom) + " shivers slightly.\n", ({ whom, TP }));

    setuid();
    seteuid(getuid());

    log_file("/d/Krynn/log/guild/wohs/record", ctime(time()) + " " + 
	     C(RNAME(TP)) + " rewarded " +
	     C(name) + " with " + LANG_WNUM(rank) + " " +
	     (rank == 1 ? "rank" : "ranks") + " because " + reason + 
	     ".\n",50000);

    if(book = present(SPELL_BOOK, E(whom)))
	book->setup_spells(whom->query_wohs_level());

    return 1;    
}

public int
wpunish(string str)
{
    object whom, book;
    string name, reason;
    int rank, w_level;

    CHECK_SO_CONCLAVE;

    if (!str || !strlen(str))
        return NF("Punish whom?\n");

    if (!parse_command(str, ({}), "%s 'with' %d 'rank' / 'ranks' " +
		       "'because' %s", name, rank, reason))
        return NF("Punish whom with how many ranks because of what?\n");

    if ((rank > 3) || (rank < 1))
        return NF("You may only punish someone with one, two or three " +
		  "ranks.\n");

    name = lower_case(name);
    whom = find_player(name);

    NF("Nobody with that name is a member within your order.\n");
    if (!objectp(whom) || !THIS_GUILD(whom))
        return 0;

    if ((ADMIN->query_member_type(whom) != TYPE_APPRENTICE) &&
	(ADMIN->query_member_type(whom) != ADMIN->query_member_type(TP)) &&
	(RNAME(TP) != ADMIN->query_wohs_head()))
        return 0;

    if (TP == whom)
        return NF("We don't do such things here. You can't punish " +
		  "yourself.\n");

    if (E(whom) != E(TP))
        return NF(C(name) + " must be present when getting punished.\n");

    if ((w_level = whom->query_wohs_level()) == 0)
        return NF(C(name) + " can't be punished any lower.\n");
    
    if (w_level < rank)
        return NF("You can't punish " + C(name) + " with so many ranks.\n");

    whom->change_level_mod(-rank);

    whom->catch_msg("All of a sudden you grow tired and you feel your " +
		    "powers weaken.\n");
    write("With the powers given to you by " + ADMIN->query_wohs_god(TP) +
	  ", you withdraw some of " + C(LANG_POSS(name)) + " power.\n");
    tell_room(E(whom), QCTNAME(whom) + " stumbles and almost collapses.\n",
	      ({ whom, TP }));

    whom->add_mana(-random(whom->query_mana()) * rank);

    setuid();
    seteuid(getuid());

    log_file("/d/Krynn/log/guild/wohs/record", ctime(time()) + " " + 
	     C(RNAME(TP)) + " punished " +
	     C(name) + " with " + LANG_WNUM(rank) + " " +
	     (rank == 1 ? "rank" : "ranks") + " because " + reason + 
	     ".\n",50000);

    if(book = present(SPELL_BOOK, E(whom)))
	book->setup_spells(whom->query_wohs_level());

    return 1;    
}


public int
wfullwiz(string str)
{
    object whom, book;
    string name, reason;
    int rank, w_level;

//    CHECK_SO_CONCLAVE; // temporarily disabled

    CHECK_IN_TOWER;

    if (!str || !strlen(str))
        return NF("Make whom a full wizard?\n");

    name = lower_case(str);
    whom = find_player(name);

    NF("Nobody with that name is a member within your order.\n");
    if (!objectp(whom) || !THIS_GUILD(whom))
        return 0;

    if (ADMIN->query_member_type(whom) != TYPE_APPRENTICE)
	return NF("But this person is already a full wizard!\n");

    if (ADMIN->query_member_type(whom) != ADMIN->query_member_type(TP) &&
	(RNAME(TP) != ADMIN->query_wohs_head()))
        return NF("You cannot make an apprentice who is not in your " +
	    "order a full wizard unless you are Master/Mistress of "+
	    "the Tower!\n");

    if (E(whom) != E(TP))
        return NF(C(name) + " must be present to become a full wizard.\n");

    ADMIN->start_full_wiz_sequence( whom, TP);

    setuid();
    seteuid(getuid());

    log_file("/d/Krynn/log/guild/wohs/record", ctime(time()) + " " + 
	     C(RNAME(TP)) + " made " +
	     C(name) + " a full wizard " + 
	     ".\n",50000);

    if(book = present(SPELL_BOOK, E(whom)))
	book->setup_spells(whom->query_wohs_level());

    return 1;    
}
