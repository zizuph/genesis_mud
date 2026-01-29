/*
 * The Shield and Club Warriors soul
 * by Milan
 *
 * Updated by Shiva and Igneous and Novo
 *
 * Revision: 6/20/2008 Novo: Added "AA" version of all commands
 * Revision: 6/21/2008 Novo: updated help file info
 *           6/26/2008 Novo: Fixed runtime when defended object is 0
 *           3/29/2009 Petros: Added aaoptions command to support smash
 *                             targeting choice.
 *           5/27/2010 Petros: Added check for cooldown when defending so that
 *                             people don't inappropriately stack aid.
 *           Nov 1, 2017 Finwe: Commented out check so layman AA can be 
 *                              promoted to Lt.
 * Revision: 2019/06/18 Shanoga: Added aalist command to see other soldiers
 */

#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit "/cmd/std/command_driver";
inherit ABILITIES_LIB;

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <filter_funs.h>

#define AA_ACTIVITY_MAPPINGS  (AA_DIR+"obj/captain_activity_mappings")


static mapping alarm = ([ ]);

/*** Prototypes ***/
void stop_defend(object who);
void end_focus_on_defence(object who);


/* The soul identification */
string get_soul_id(){ return GUILD_NAME; }
int query_cmd_soul() { return 1; }

void
create()
{
    FIXEUID;
}

/* *************************************************************
 * The list of verbs and functions.
 */

mapping
query_cmdlist()
{
    return([
        "help":"help",
		"aahelp" : "help",
        "aaoptions":"show_options",
        "focus":"focus",
        "aafocus":"focus",
        "defend":"defend",
        "aadefend":"defend",
        "break":"break_concentration",
        "aabreak":"break_concentration",
        "aascare":"do_ability",
        "scare":"do_ability",
        "aasmash":"do_ability",
        "smash":"do_ability",
        "aasmack":"do_ability",
        "smack":"do_ability",
        "aaretreat":"do_ability",
        "retreat":"do_ability",
        /*** special commands will be in "aa_commands.c" ***/
        "aalist":"do_list",
        "aasignal":"signal",
        "signal":"signal",
        "aaincognito":"incognito",
        "incognito":"incognito",
        "aasay":"aasay",
		"aaretire":"do_retire",
		"aaresign" : "do_resign",
		"aaexpel" : "do_aaexpel",
        "aaactivity" : "do_captain_activity",
		"aaexecute" : "do_aaexecute",
		"aapunish" : "do_beat_on_head",
		"aalieutenantpromote" : "do_promote_to_lieutenant",
		"aalieutenantdemote" : "do_demote_from_lieutenant",
		"aaropromote" : "do_promote_to_ro",
		"aarodemote" : "do_demote_ro",
		"captainpromote" : "do_promote_to_captain",
		"captaindemote" : "do_demote_from_captain",
        ]);
}

/***************************************************************/
//This is the mapping of commands to actual files

public mapping
query_ability_map()
{
    return ([
    "smash"        : AA_DIR+"special/smash",
    "aasmash"      : AA_DIR+"special/smash",
    "smack"        : AA_DIR+"special/smack",
    "saamack"      : AA_DIR+"special/smack",
    "scare"        : AA_DIR+"special/scare",
    "aascare"      : AA_DIR+"special/scare",
    "retreat"      : AA_DIR+"special/retreat",
    "aaretreat"    : AA_DIR+"special/retreat",
     ]);
}


/***************************************************************/
/* the functions. add them in the same order as in the cmdlist */

/***********************  HELP  ***************************/
int help(string s)
{
    if ((s == "shield and club") || (s == "angmar"))
    {
        write("Available commands are:\n"+
            "focus on defence     : Focus on your defence with a shield.\n"+
            "defend [target]      : Focus on defending a fellow soldier \n"+
            "                       with your shield.\n"+
            "break concentration  : You can stop focusing on defence (both above).\n"+
            "scare [target]       : Initiate a combat. Better if you are hidden.\n"+
            "smash [target]       : Try to smash your target/victim to a pulp.\n"+
            "smack [target]       : Try to shield-bash your target/victim.\n"+
            "                       commands got stuck for some reason.\n"+
            "aalist [lay/occ]  : List the soldiers who are currently awake.\n"+
            "signal <sign>        : Send smoke signal. <sign> can be any letter,\n"+
            "                       'HELP', 'HELLO', 'BYE', 'S.O.S.' or 'O.K.'.\n"+
            "signal off/on        : You can turn off/on receiving smoke signals.\n"+
            "incognito on/off     : When incognito you try to hide that you are\n"+
            "                       a member of the army.\n"+
            "aasay                : Say something in the language of Angmar.\n"+
            "plant rumour         : Please do 'help plant rumour' for more info.\n"+
            "aaoptions            : Show available Angmar options.\n"+
            "\n"+
			"claim captaincy      : If the guild has no Captain, a Lieutenant can \n" 
			+"                      claim the position. If the army has no Captain \n"
			+"                      or Lieutenants, the first regular soldier that \n"
			+"                      use this command becomes the new Captain. A \n"
			+"                      candidate must be in the 'old court room' to \n"
			+"                      do use this command.\n"
			+"\n" +
            "Command 'angmar emotes' will give you list of emotes. Have fun!\n"+
            "You can also use aa in front of your commands it they "+
            "conflict with other guilds.\n"+
            ""  );


		    // For lieutenants only.
		    if (AA_COUNCIL_OBJ->is_lieutenant(this_player()->query_name()) || this_player()->query_wiz_level())
		    {
			    write("\n");
			    write("  Commands for the Lieutenants \n");
			    write("  ------------------------\n");
				write("  aaresign  : You retire from the Lieutenant position,\n");
				write("              and enter the ranks of the regular soldiers.\n");
				write("\n");
			    write("  aaexpel <target> : You expel a member of the Army\n");
			    write("                     of Angmar.\n");
			    write("\n");
			    write("  aapunish <target> : You punish a member of the Army\n");
			    write("                      of Angmar(beat on head, skill loss).\n");
			    write("\n");
		    }


		    // For captains only.
            if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) || this_player()->query_wiz_level())
	        {
	            write("\n");
	            write("  Commands for the Captain \n");
	            write("  ------------------------\n");
				write("  aaretire <target>  : You retire and give the position\n");
                write("                     of Captain to someone else.\n");
	            write("\n");
				write("  aaresign  : You retire from the positon of the Captain\n");
				write("            of Angmar and become a Lieutenant.\n");
				write("\n");
				write("  aaexpel <target> : You expel a member of the Army\n");
				write("                     of Angmar.\n");
				write("\n");
				write("  aaexecute <target> : You execute a member of the Army\n");
				write("                       of Angmar.\n");
	            write("\n");
				write("  aapunish <target> : You punish a member of the Army\n");
				write("                      of Angmar(beat on head, skill loss).\n");
				write("\n");
				write("  aalieutenantpromote <target> : Promote an Angmarim to the position\n");
				write("                          of Lieutenant (council).\n");
				write("\n");
				write("  aalieutenantdemote <target> : Demote an Angmarim from the position\n");
				write("                          of Lieutenant (council).\n");
				write("\n");
				write("  aaropromote <target> : Promote an Angmarim to the position\n");
				write("                          of Recruitment Officer.\n");
				write("\n");
				write("  aarodemote <target> : Demote an Angmarim from the position\n");
				write("                          of Recruitment Officer.\n");
                write("\n");
                write("  aaactivity       : Your level of activity as the Captain.\n");
                write("  ----------------------------------------------------------\n");
                write("  Activity level 6 : You are favored by the Emissary of the Dark Lord.\n");
                write("  Activity level 5 : Your position with the Emissary of the Dark Lord is solidified.\n");
                write("  Activity level 4 : You are in good standing with the Emissary of the Dark Lord.\n");
                write("  Activity level 3 : You are accepted by the Emissary of the Dark Lord.\n");
                write("  Activity level 2 : You are losing your standing with the Emissary of the Dark Lord.\n");
                write("  Activity level 1 : The Emissary of the Dark Lord is displeased with your \n");
                write("                     effort and you are about to be replaced.\n");
				write("\n");
	        }

			// For WIZARDS only.
			if (this_player()->query_wiz_level())
			{
				write("\n");
				write("  Commands for the supporting wizard \n");
				write("  ----------------------------------\n");
				write("  captainpromote <target> : You promote "
				+"someone to the new Captain of the Army of Angmar.\n");
				write("\n");
				write("  captaindemote <target> : You demote "
				+ "someone from the position of Captain of the Army of Angmar.\n");
				write("\n");
			}

			


        return 1;
    }

    return 0;
}

/***********************  COMMANDS  *************************/

#include "aa_commands.c"

/*
 * Function name: sort_by_rank
 * Description  : Sorter to sort the soldiers by highest rank.
 *                We want to sort descendingly.
 * Arguments    : string name1 - the first name to compare.
 *                string name2 - the second name to compare.
 * Returns      : int -1/0/1 - larger/equal/smaller.
 */
int
sort_by_rank(string name1, string name2)
{
    name1 = lower_case(explode(name1, " ")[0]);
    name2 = lower_case(explode(name2, " ")[0]);
    if (find_player(name1)->query_aa_stat() == find_player(name2)->query_aa_stat())
    {
        if (name1 == name2)
        {
            return 0;
        }
        return ((name1 > name2) ? -1 : 1);
    }
    return ((find_player(name1)->query_aa_stat() > find_player(name2)->query_aa_stat()) ? -1 : 1);
}

public int
do_captain_activity()
{
    string activity;
    
    int level_captain;
    

    if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()))
    {
        level_captain = AA_ACTIVITY_MAPPINGS->query_captain_activity_gauge(this_player()->query_name());
        
        if (level_captain > 900)
        {
            write("You are favored by the Emissary of the Dark Lord.\n");
            
            return 1;
        }
        
        if (level_captain > 700)
        {
            write("Your position with the Emissary of the Dark Lord is solidified.\n");
            
            return 1;
        }
        
        if (level_captain > 500)
        {
            write("You are in good standing with the Emissary of the Dark Lord.\n");
            
            return 1;
        }
        
        if (level_captain > 150)
        {
            write("You are accepted by the Emissary of the Dark Lord.\n");
            
            return 1;
        }
        
        if (level_captain > 100)
        {
            write("You are losing your standing with the Emissary of the Dark Lord.\n");
            
            return 1;
        }
        
        if (level_captain > 5)
        {
            write("The Emissary of the Dark Lord is displeased with your "
            +"effort and you are about to be replaced.\n");
            
            return 1;
        }
        
        return 1;
    }
    
    return 0;
}

/*
 * Function name: aawho
 * Description  : Helper function for "aalist" to filter by occ/lay
 *                and build the name and title string.
 * Arguments    : object ob - the player
 *                string branch - "occ" or "lay" to select branch
 * Returns      : string - player name, title, gender + race
 */
string
aawho(object ob, string branch)
{
    string title;
    if (!ob->query_guild_member("Angmar Army"))
        return 0;
    if (branch == "occ")
    {
        if (member_array("/d/Shire/guild/AA/shadow/aa_sh_occ:",
                         ob->query_autoshadow_list()) > -1)
        {
            if (ob->query_aa_incognito())
                title = ob->query_rank();
            else
                title = implode(explode(ob->query_guild_title_occ(),
                                        " ")[0..-6], " ");
            return implode(explode(break_string(
                ob->query_name() + " the " + title + ", " +
                ob->query_gender_string() + " " + ob->query_race_name(),
                74), "\n"), "\n      ");
        }
    }
    if (branch == "lay")
    {
        if (member_array("/d/Shire/guild/AA/shadow/aa_sh_lay:",
                         ob->query_autoshadow_list()) > -1)
        {
            if (ob->query_aa_incognito())
                title = ob->query_rank();
            else
                title = implode(explode(ob->query_guild_title_lay(),
                                        " ")[0..-6], " ");
            return implode(explode(break_string(
                ob->query_name() + " the " + title + ", " +
                ob->query_gender_string() + " " + ob->query_race_name(),
                74), "\n"), "\n      ");
        }
    }
}

/*
 * Function name: do_list
 * Description  : Emote to display a member list to Army members.
 * Arguments    : string str - none
 * Returns      : 0/1 for fail/success
 */
int
do_list(string str)
{
    string occ_members, lay_members;
    string *occ_soldiers, *lay_soldiers;
    
    if (!this_player()->query_guild_member("Angmar Army"))
        return 0;
    
    // Layman only.
    if (str == "lay")
    {
        occ_soldiers = map(users() - ({ 0 }), "aawho", this_object(), "lay")
            - ({ 0 });
        occ_soldiers = sort_array(occ_soldiers, "sort_by_rank");
        occ_members = "You know that the following part-time soldiers " +
            "of the Army are awake:\n    " +
            implode(occ_soldiers, "\n    ") + "\n";
        if (sizeof(occ_soldiers) > 0)
            write(occ_members);
        else
            write("No part-time soldiers of the Army are currently awake.\n");
        return 1;
    }
    
    // Occupational only.
    if (str == "occ")
    {
        occ_soldiers = map(users() - ({ 0 }), "aawho", this_object(), "occ")
            - ({ 0 });
        occ_soldiers = sort_array(occ_soldiers, "sort_by_rank");
        occ_members = "You know that the following full-time soldiers " +
            "of the Army are awake:\n    " +
            implode(occ_soldiers, "\n    ") + "\n";
        if (sizeof(occ_soldiers) > 0)
            write(occ_members);
        else
            write("No full-time soldiers of the Army are currently awake.\n");
        return 1;
    }
    
    // All members.
    if (!str)
    {
        occ_soldiers = map(users() - ({ 0 }), "aawho", this_object(), "occ")
            - ({ 0 });
        occ_soldiers = sort_array(occ_soldiers, "sort_by_rank");
        
        lay_soldiers = map(users() - ({ 0 }), "aawho", this_object(), "lay")
            - ({ 0 });
        lay_soldiers = sort_array(lay_soldiers, "sort_by_rank");
        
        occ_members = "You know that the following full-time soldiers " +
            "of the Army are awake:\n    " +
            implode(occ_soldiers, "\n    ") + "\n";
        lay_members = "You know that the following part-time soldiers " +
            "of the Army are awake:\n    " +
            implode(lay_soldiers, "\n    ") + "\n";
        if ((sizeof(occ_soldiers) > 0) && (sizeof(lay_soldiers) > 0))
            write(occ_members + lay_members);
        else if (sizeof(occ_soldiers) > 0)
            write(occ_members);
        else
            write(lay_members);
        return 1;
    }
    
    notify_fail("Syntax: aalist [lay or occ or none]\n" + 
                "  occ: full-time soldiers only\n" + 
                "  lay: part-time soldiers only\n" + 
                "  none: all soldiers\n");
    return 0;
}


// The captain resigns and give the position to someone else.
int
do_retire(string str)
{

	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1 || this_player()->query_wiz_level())
	{
		if (!str)
		{
			return 0;
		}

		if (str == this_player()->query_name())
		{
			write("You are already the Captain! Select someone else to "
				+ "succeed you as the new Captain!\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_captain(str) == 1)
		{
			write("That person is already the Captain of the Army of Angmar.\n");
			return 1;
		}
        
        if (TP->query_guild_name_lay() == GUILD_NAME)
        {
            write("Only occupational members of the Army can take the Captain spot.\n");
			return 1;
        }

		AA_COUNCIL_OBJ->demote_captain_self(this_player()->query_name());
		AA_COUNCIL_OBJ->promote_captain(str);

		tell_object(find_player(str), "You have been promoted to the new "
			+ "Captain of the Army of Angmar by " + this_player()->query_name() + "!\n");

		write("You promote " + find_player(str)->query_name() + " to the new "
			+ "Captain of the Army of Angmar!\n\nYou step down and enter the "
			+ "ranks of the regular soldiers.\n");

		return 1;
			
	}

	return 0;
}


// The captain resigns.
int
do_resign()
{

	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1 || this_player()->query_wiz_level())
	{
		AA_COUNCIL_OBJ->demote_captain_self(this_player()->query_name());

		write("You resign from your position as the "
			+ "Captain of the Army of Angmar!\n\nYou step down and enter the "
			+ "ranks of the Lieutenants.\n");

		return 1;
	
	}


	if (AA_COUNCIL_OBJ->is_lieutenant(this_player()->query_name()) == 1 || this_player()->query_wiz_level())
	{
		AA_COUNCIL_OBJ->demote_lieutenant_self(this_player()->query_name());

		write("You resign from your position as a "
			+ "Lieutenant of the Army of Angmar!\n\nYou step down and enter the "
			+ "ranks of the regular soldiers.\n");

		return 1;

	}

	return 0;
}


// Expelling a member from the Army.
int
do_aaexpel(string str)
{
	if (!str)
	{
		return 0;
	}

	
	// OLD  if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 0 && !this_player()->query_wiz_level())

	// NEW
	//if (AA_COUNCIL_OBJ->lieut_cap(this_player()->query_name()) == 1)
	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1 || 
		AA_COUNCIL_OBJ->is_lieutenant(this_player()->query_name()) == 1)
	{
		if (str == this_player()->query_name())
		{
			write("You can't expel yourself from the Army of Angmar!\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_captain(str) == 1)
		{
			write("You can't just expel the Captain of the Army of Angmar!\n");
			return 1;
		}

		object aamember = find_player(str);

		if (!IS_MEMBER(aamember))
		{
			NF("That person is not a member of the Army of Angmar!\n");
			return 0;
		}

		write("You expel " + aamember->query_name() + " from the "
			+ "Army of Angmar!\n");

		(AA_DIR + "rooms/chapel")->do_leave(aamember);

		return 1;
	}

	

	return 0;
}


// Execution. Captain Only.
int
do_aaexecute(string str)
{
	if (!str)
	{
		return 0;
	}
	
	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1)
	{
		if (str == this_player()->query_name())
		{
			write("You can't execute yourself!\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_captain(str) == 1)
		{
			write("You can't execute the Captain of the Army of Angmar!\n");
			return 1;
		}

		object aamember = find_player(str);

		if (!IS_MEMBER(aamember))
		{
			NF("That person is not a member of the Army of Angmar!\n");
			return 0;
		}

		write("You summon the Lidless Eye to execute " + aamember->query_name() + "!\n");

		tell_room(ENV(aamember),
			"Suddenly, the terrible visage of a burning Lidless Red Eye fills"
			+ " the entire area, and a deep and penetrating voice speaks: DIE!\n");

		aamember->heal_hp(-10 - aamember->query_hp());
		aamember->do_die(TO);
	}

	

	return 0;
}



// Beat on head.
int
do_beat_on_head(string str)
{
	if (!str)
	{
		return 0;
	}

	
	//OLD  if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 0 && !this_player()->query_wiz_level())

	// NEW
	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1 ||
		AA_COUNCIL_OBJ->is_lieutenant(this_player()->query_name()) == 1)
	{
		if (str == this_player()->query_name())
		{
			write("You can't punish yourself!\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_captain(str) == 1)
		{
			write("You can't punish the Captain of the Army of Angmar!\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_lieutenant(str) == 1)
		{
			write("You can't punish an Lieutenant of the Army of Angmar in that way!\n");
			return 1;
		}

		object aamember = find_player(str);

		if (!IS_MEMBER(aamember))
		{
			NF("That person is not a member of the Army of Angmar!\n");
			return 0;
		}

		write("You summon the Lidless Eye to punish " + aamember->query_name() + "!\n");

		int *skills, i;

		aamember->catch_msg("\n"
			+ "Suddenly, the terrible visage of a burning Lidless Red Eye fills"
			+ " the entire area, and a deep and penetrating voice speaks: WRETCH,"
			+ " RECEIVE YOUR DUE REWARD!\n"
			+ "\nMany angry warriors jump at you " +
			"and beat you with their nasty clubs...\n" +
			"Fortunatelly you lose consciousness so you don't feel every hit.\n\n" +
			"When you wake up you notice that you have terrible headache " +
			"and that you feel less skillful.\n\n");

		tell_room(ENV(aamember), "\n"
			+ "Suddenly, the terrible visage of a burning Lidless Red Eye fills"
			+ " the entire area, and a deep and penetrating voice speaks: WRETCH,"
			+ " RECEIVE YOUR DUE REWARD!\n"
			+ "\nMany angry warriors jump at " +
			QTNAME(aamember) + " and beat " + HIM(aamember) + " with their nasty clubs...\n" +
			QCTNAME(aamember) + " is soon knocked down but the cruel warriors continue " +
			"beating " + HIM(aamember) + ", aiming mainly for " + HIS(aamember) + " head.\n" +
			"After they are satisfied they leave, leaving " +
			QTNAME(aamember) + " laying on the floor...\n\n" +
			"After a long time " + QTNAME(aamember) + " regains his sense and touches" + HIS(aamember) +
			" sore head. " + CAP(HE(aamember)) + " sure regrets what " + HE(aamember) +
			" has done!\n\n", aamember);

		aamember->set_max_headache(MAX(1000, aamember->query_max_headache()));

		aamember->set_headache(aamember->query_max_headache());

		skills = aamember->query_all_skill_types();
		for (i = 0; i < sizeof(skills); i++)
		{
			if ((skills[i] < 1000) || (skills[i] == 138000) || (skills[i] == 138001))
			{
				aamember->set_skill(skills[i], aamember->query_skill(skills[i]) - random(20));
				if (aamember->query_skill(skills[i]) < 1) aamember->remove_skill(skills[i]);
			}
		}

		return 1;
	}

	

	return 0;
}



// NEW
int
do_promote_to_lieutenant(string str)
{
	if (!str)
	{
		return 0;
	}


	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1 ||
		this_player()->query_wiz_level())
	{
		if (str == this_player()->query_name())
		{
			write("You are the Captain, therefore you can't promote yourself "
				+ "to Lieutenant.\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_lieutenant(str) == 1)
		{
			write("That person is already an Lieutenant of the Army of Angmar.\n");
			return 1;
		}
        
        if (TP->query_guild_name_lay() == GUILD_NAME)
        {
            write("Only occupational members of the Army can be Lieutenants.\n");
			return 1;
        }

		object lay_aamember = find_player(str);
// commented out so Lay AA can become Lt.
// Finwe, November 2017
/*
		if (lay_aamember->query_guild_name_lay() == "Angmar Army")
		{
			write("Layman members can't be Lieutenants for the Army of Angmar.\n");
			return 1;
		}
*/
		AA_COUNCIL_OBJ->promote_lieutenant(str);

		return 1;
	}

	return 0;
}


// NEW
int
do_demote_from_lieutenant(string str)
{
	if (!str)
	{
		return 0;
	}

	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1 ||
		this_player()->query_wiz_level())
	{
		if (str == this_player()->query_name())
		{
			write("This option does not work on yourself, Captain.\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_lieutenant(str) == 1)
		{
			AA_COUNCIL_OBJ->demote_lieutenant(str);

			return 1;
		}

		write("That person is not a Lieutenant of the Army of Angmar.\n");

		return 1;
	}

	return 0;
}


// NEW
int
do_promote_to_ro(string str)
{
	if (!str)
	{
		return 0;
	}

	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1 ||
		this_player()->query_wiz_level())
	{
		if (str == this_player()->query_name())
		{
			write("You are the Captain, therefore you can't demote yourself "
				+ "to a Recruitment Officer.\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_lieutenant(str) == 1)
		{
			write("That person is a Lieutenant of the Army of Angmar already.\n");
			return 1;
		}

		object lay_aamember = find_player(str);

		AA_COUNCIL_OBJ->promote_ro(str);

		return 1;
	}

	return 0;
}


// NEW
int
do_demote_ro(string str)
{
	if (!str)
	{
		return 0;
	}

	if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1 ||
		this_player()->query_wiz_level())
	{
		if (str == this_player()->query_name())
		{
			write("This option do not work on yourself, Captain.\n");
			return 1;
		}

		if (AA_COUNCIL_OBJ->is_lieutenant(str) == 1)
		{
			write("That person is a Lieutenant of the Army of Angmar.\n");
			return 1;
		}

		AA_COUNCIL_OBJ->demote_ro(str);

		return 1;
	}

	return 0;
}



// This function is for wizards to promote members directly to
// AA captain. Make sure noone else occupy the position.
int
do_promote_to_captain(string str)
{
	if (!str)
	{
		return 0;
	}

	if (!this_player()->query_wiz_level())
	{
		return 0;
	}


	if (str == this_player()->query_name())
	{
		write("You can't promote yourself.\n");
		return 1;
	}

	if (AA_COUNCIL_OBJ->is_captain(str) == 1)
	{
		write("That person is already the Captain of the Army of Angmar.\n");
		return 1;
	}

	object lay_aamember = find_player(str);

	if (lay_aamember->query_guild_name_lay() == "Angmar Army")
	{
		write("Layman members can't be Captains for the Army of Angmar.\n");
		return 1;
	}

	//AA_COUNCIL_OBJ->demote_ro(str);
	AA_COUNCIL_OBJ->promote_captain(str);

	

	return 1;
}



// This function is for wizards to demote members directly from
// AA captain.
int
do_demote_from_captain(string str)
{
	if (!str)
	{
		return 0;
	}

	if (!this_player()->query_wiz_level())
	{
		write("What?\n");
		return 1;
	}


	if (str == this_player()->query_name())
	{
		write("You can't demote yourself.\n");
		return 1;
	}

	if (AA_COUNCIL_OBJ->is_captain(str) == 1)
	{
		AA_COUNCIL_OBJ->demote_captain(str);
		return 1;
	}

	write("That person is not the Captain of the Army of Angmar.\n");
	return 1;
}



int check_valid_defend()
{
    /*if (TP->query_aa_member_killer() > 1)
    {
        NF("You are banned from using "+query_verb()+" for killing army members!\n");
        return 0;
    }*/

    object *
    shields = filter(TP->query_armour(-1),
                     &operator(==)(A_SHIELD) @ &->query_at());
    if (!sizeof(shields))
    {
        NF("You need to wear some shield first!\n");
        return 0;
    }

    if (SMASH_ABILITY->query_ability_preparing(TP))
    {
        NF("You are preparing to smash your enemy now!\n");
        return 0;
    }
    if (SMACK_ABILITY->query_ability_preparing(TP))
    {
        NF("You are preparing to smack your enemy now!\n");
        return 0;
    }
    if (SCARE_ABILITY->query_ability_preparing(TP))
    {
        NF("You are preparing to scare your enemy now!\n");
        return 0;
    }
    // We should not be able to defend when in cooldown. Otherwise, it leads
    // to inappropriately stacking damage.
    if (SMASH_ABILITY->query_ability_in_cooldown(TP)
        || SMACK_ABILITY->query_ability_in_cooldown(TP)
        || SCARE_ABILITY->query_ability_in_cooldown(TP))
    {
        NF("You are not ready to do that!\n");
        return 0;
    }

    object defended=TP->query_aa_evade_obj()->query_defend();
    if (defended==TP)
    {
        NF("You are already concentrating on your defence.\n");
        return 0;
    }
    if (defended)
    {
        NF("You are defending "+defended->query_The_name(TP)+" now!\n");
        return 0;
    }
    return 1;
}

/***********************  DEFEND  ***************************/
int defend(string str)
{
    int a;
    object *target;

    target = parse_this(str, "[the] %l");

    if (sizeof(target) > 1)
    {
        NF("Be specific, you can't "+query_verb()+" "+COMPOSITE_LIVE(target)+
            " at the same time.\n");
        return 0;
    }
    if (!sizeof(target))
    {
        NF("You find no such living creature.\n");
        return 0;
    }
    if (member_array(target[0], TP->query_team_others()) == -1)
    {
        NF(target[0]->query_The_name(TP)+" is not member of your team!\n");
        return 0;
    }
    if (!IS_MEMBER(target[0]))
    {
        NF(target[0]->query_The_name(TP)+" is not member of Angmar's army!\n");
        return 0;
    }

    if (sizeof(filter(target[0]->query_evade_effects(),
        &->query_aa_evade_effect()))>3)
    {
        NF(target[0]->query_The_name(TP)+" already has two defenders.\n");
        return 0;
    }
    if (!check_valid_defend())
    {
        return 0;
    }

    a = 1 + random(TP->query_skill(SS_SHIELD));
    TP->catch_msg("You start to defend "+QTNAME(target[0])+".\n");
    TP->tell_watcher(QCTNAME(TP)+" starts to defend "+
        QTNAME(target[0])+".\n", target[0]);
    target[0]->catch_msg(QCTNAME(TP)+" starts to defend you.\n");
    TP->query_aa_evade_obj()->set_defend(target[0]);
    alarm[TP->query_name()] = set_alarm(itof(a), 0.0, &stop_defend(TP));
    return 1;
}

void stop_defend(object who)
{
    object defended=who->query_aa_evade_obj()->query_defend();

    remove_alarm(alarm[who->query_name()]);
    m_delkey(alarm,who->query_name());
    who->query_aa_evade_obj()->clear_defend(who);

    if (defended)
    {
        who->catch_msg("You stop defending "+QTNAME(defended)+".\n");
        who->tell_watcher(QCTNAME(who)+" stops defending "+
            QTNAME(defended)+".\n", defended);
        defended->catch_msg(QCTNAME(who)+
            " stops defending you.\n");
    }
}

/***********************  FOCUS  ***************************/
int
focus(string str)
{
    int a;

    if (str != "on defence")
    {
        NF("Focus on what? Defence???\n");
        return 0;
    }
    if (!check_valid_defend())
    {
        return 0;
    }
    if (!TP->query_attack())
    {
        NF("But you are not fighting anyone.\n");
        return 0;
    }

    a = 1 + random(TP->query_skill(SS_SHIELD));
    TP->catch_msg("You start to concentrate on your defence.\n");
    TP->tell_watcher(QCTNAME(TP)+" starts to concentrate on "+HIS(TP)+
    " defence.\n");
    TP->query_aa_evade_obj()->set_defend(TP);
    alarm[TP->query_name()] = set_alarm(itof(a), 0.0,
    &end_focus_on_defence(TP));
    return 1;
}

void
end_focus_on_defence(object who)
{
    remove_alarm(alarm[who->query_name()]);
    m_delkey(alarm,who->query_name());
    who->catch_msg("You lost your concentration.\n");
    who->tell_watcher(QCTNAME(who)+" lost "+HIS(who)+" concentration.\n");
    who->query_aa_evade_obj()->clear_defend();
    return;
}

/***********************  BREAK CONCENTRATION  *************/
int
break_concentration(string str)
{
    if (str != "concentration")
    {
        NF("Break what? Concentration?\n");
        return 0;
    }
    if (TP->query_aa_evade_obj()->query_defend()==TP)
    {
        end_focus_on_defence(TP);
        return 1;
    }
    if (TP->query_aa_evade_obj()->query_defend())
    {
        stop_defend(TP);
        return 1;
    }
    NF("But you are not focusing on defence now!\n");
    return 0;
}

public int
show_options(string str)
{
    object player;
    string * arguments;

    setuid();
    seteuid(getuid());

    player = this_player();
    if (!str)
    {
        write("Army of Angmar Options\n");
        write("======================\n");
        write("Smash Anything [smash]: ");
        switch (AA_OPTIONS_OBJ->query_option("smash", player->query_real_name()))
        {
        case 1:
            write("On (You currently don't care where you smash, as "
                + "long as it hits!)\n");
            break;
        case 0:
        default:
            write("Off (You currently want to smash heads only!)\n");
            break;
        }
        write("\n");
        write("To set your options, use \"aaoptions <option> <value>\".\n");
        write("\n");
        return 1;
    }
    else if (lower_case(str) == "smash")
    {
        write("Smash Anything [smash]:   ");
        switch (AA_OPTIONS_OBJ->query_option("smash", player->query_real_name()))
        {
        case 1:
            write("On (You currently don't care where you smash, as "
                + "long as it hits!)\n\n");
            write("To change this, try <aaoptions smash off>.\n");
            break;
        case 0:
        default:
            write("Off (You currently want to smash heads only!)\n\n");
            write("To change this, try <aaoptions smash on>.\n");
            break;
        }
        write("\n");
        return 1;
    }

    arguments = explode(str, " ");
    if (sizeof(arguments) == 2
        && lower_case(arguments[0]) == "smash")
    {
        switch (lower_case(arguments[1]))
        {
        case "on":
            AA_OPTIONS_OBJ->set_option("smash", player->query_real_name(), 1);
            write("You will now smash wildly, not caring where you hit!\n");
            break;

        case "off":
            AA_OPTIONS_OBJ->set_option("smash", player->query_real_name(), 0);
            write("You will now try to smash only the head!\n");
            break;
        }
        return 1;
    }

    notify_fail(str + " is not a recognized option.\n");
    return 0;
}
