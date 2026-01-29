/*
 * Joining Room for the Wizards of High Sorcery
 *
 * The settings that are automatically triggered in this room are 
 * determined in /d/Krynn/guilds/wohs/test/room/void1.c
 *
 */

#pragma strict_types

#include "/d/Krynn/wayreth/local.h"
#include <macros.h>
#include <ss_types.h>
#include <time.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"

inherit WAYINROOM;

#define SOHM_MANAGER     (WOHS_LIBS + "sohm_manager")
#define SOHM_JOIN        ("/d/Krynn/guilds/sohm/room/joinroom")

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "/d/Krynn/guilds/sohm/remove_all_spells.h"

#define LEADER_LOG        ("/d/Krynn/guilds/wohs/logs/wohs_conclave")
#define COMPLETED_TEST    "_wohs_test_completed_test"
#define LEFT_TEST         "_wohs_test_left_test"
#define FINISHED_TEST     "_wohs_test_finished_test"
#define WOHS_TEST_SCORE   "_wohs_test_final_score"

// Global Variables
public string * beta_testers = ({ "armanjr", "carnakjr", "cherekjrjr", 
                "hollandjr", "gened", "genee", "rockjr"});

string chosen_order;

public void
reset_wayreth_room()
{

}

public void
create_wayreth_room()
{
    set_short("a small empty chamber off to the side of the Hall of " +
        "Mages");
    set_long("@@long_descr");

    add_item(({"hall","hall of mages","exit","out"}),
        "By leaving out through the exit here you will return to the " +
        "Hall of Mages.\n");
    add_item(({"chamber","empty chamber"}), "This small chamber off to " +
        "the side of the Hall of Mages is where you ended up after " +
        "completing the Test of High Sorcery.\n");

    add_exit("/d/Krynn/wayreth/tower/hall_of_mages", "out",
        "@@leave_room");

    reset_wayreth_room();

}

int
leave_room()
{
    TP->add_prop(FINISHED_TEST, 1);
    return 0;
}

public void
init()
{
    ::init(); 
    add_action("pass","pass");
    add_action("choose", "choose"); 
}

/*
 * Function:    leave_guild
 * Description: Function to remove someone from the guild.
 */
public int 
leave_guild(object player) 
{ 
    if (!WOHS_IS_MEMBER(player))
    {        
	return 0;
    }

    // Remove the person's occupational guild
    if (!player->remove_guild_occ()) 
    { 
	return 0; 
    } 

    // Clear guild stat, remove guild learn, and begin skill decay
    player->clear_guild_stat(SS_OCCUP); 
    player->setup_skill_decay(); 
    player->set_guild_pref(SS_OCCUP, 0);

    // Reset the guild stat and skill
    player->remove_skill(WOHS_GUILD_STAT);
    player->remove_skill(WOHS_GUILD_SKILL);

    // Remove all spells from memory and spellbook, 
    // defined in remove_all_spells.h
    remove_all_spells(player);

    // Reset the start location of the person leaving the guild
    if (player->query_default_start_location() == (WOHS_STARTROOM))
    {
	player->set_default_start_location(player->query_def_start());
    }

    // Remove the command soul
    player->remove_cmdsoul(WOHS_SOUL);
    player->remove_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    player->update_hooks();

    // Remove the guild objects
    object guild_object = present("wohs_guild_object", player);
    if (objectp(guild_object))
    {
	guild_object->remove_object();
    }
    object guild_robe = present("wohs_robe_object", player);
    if (objectp(guild_robe))
    {
        player->command("$remove hood");
        player->command("$remove robe");
	guild_robe->remove_object();
    }

    // Update the Guild Manager
    string name = player->query_real_name();

    WOHS_MANAGER->remove_member(player);
    WOHS_MANAGER->remove_wohs_members_list(name);

    send_debug_message("wohs", capitalize(name)
        + " is no longer a Wizard of High Sorcery.", LEADER_LOG);

    return 1; 
}

/*
 * Function:    join_guild
 * Description: Function to add someone to the guild
 */
public int
join_guild(object player)
{
    // Add Guild Shadow
    object guild_shadow = clone_object(WOHS_SHADOW);
    int shadow_result = guild_shadow->shadow_me(player, WOHS_GUILD_TYPE, 
      WOHS_GUILD_STYLE, WOHS_GUILD_NAME);
    string wohs_name = player->query_real_name();

    switch (shadow_result)
    {
/*
    case -4:
	player->catch_tell("You can't join the Wizards of High Sorcery " 
          + "while you currently have an occupation. Come back when you "
          + "are ready to commit to the life of a Magi, then return " 
          + "and try again.\n");
	return 0;
*/

    case 1:
	// Everything is fine. Autoshadow should have been added as well.
	break;

    default:
/*   
	player->catch_tell("An error occurred in the fabric of space "
	  + "and you are not able to join the Wizards of High Sorcery. "
	  + "Please contact the guildmaster for help.\n");
*/
	return 0;
    }

    // Clear the guild stat, in case it wasn't cleared, and add necessary
    // skill decay and guild tax.
    player->setup_skill_decay(); 

    // Guild stat isn't cleared. Players keep their guild stats from SoHM
    // player->clear_guild_stat(SS_OCCUP); 
    player->set_guild_pref(SS_OCCUP, GUILD_TAX_WOHS); 

    // Add the member to the Guild Manager
    WOHS_MANAGER->add_member(player);

    int test_score = WOHS_MANAGER->query_wohs_test_prop(player, 
        WOHS_TEST_SCORE);
    WOHS_MANAGER->add_wohs_test_time_stamp(wohs_name, time(), test_score);

    return 1;    
}

public void
display_join_sequence()
{
    object player = this_player();

    write("You are now a Wizard of High Sorcery!\n\n");
    tell_room(environment(player), QCTNAME(player) + " is now a wizard " +
        "of High Sorcery!\n", ({ player }));

}

public int
choose(string str)
{
    object player = this_player();
    string race_name = player->query_race_name();

    if (!WOHS_MANAGER->query_passed_wohs_test(player))
    {
	notify_fail("You can only join an Order of High Sorcery if you " +
	  "have first passed the Test!\n");
	return 0;
    }

    if (player->query_guild_name_occ() == WOHS_GUILD_NAME)
    {
	notify_fail("You are already a Wizard of High Sorcery!\n");
	return 0;
    }

    if (player->query_guild_name_occ() != "School of High Magic")
    {
	notify_fail("Only Aspirants of High Sorcery may join an Order " +
	  "after completing the Test!\n");
	return 0;
    }

    if(IN_ARRAY(race_name, WOHS_INELIGIBLE_RACES))
    {
	notify_fail("The Orders do not accept a " +race_name+ " to "+
	  "become a Wizard of High Sorcery.\n");
	return 0;
    }

    // For now, only beta testers (and wizards) can use this command.

/*
    if (!player->query_wiz_level() 
      && !IN_ARRAY(player->query_real_name(), beta_testers))
    {
	notify_fail("Sorry, the Wizards of High Sorcery is currently " +
            "only open to select applicants. Please try again later.\n");
	return 0;
    }
*/

    // WoHS who are banned from casting, or were kicked out cannot
    // join for the duration of their restrictions
    if (WOHS_MANAGER->is_join_restricted(player)
      || WOHS_MANAGER->is_casting_banned(player))
    {
	notify_fail("Your past behaviors prevent you from being able "
	  + "to join an Order. You will need to wait for some "
	  + "time before you will be allowed back into the guild.\n");
	return 0;
    }

    if (!strlen(str))
    {
	return 0;
    }

    if((str != "white") && (str != "red") && (str != "black"))
    {
	notify_fail("Something has gone wrong in assigning your Order. " +
            "Please notify a wizard.\n");
	return 0;
    }

    // remove aspirant from SoHM guild.

    setuid();
    seteuid(getuid());
    if (SOHM_JOIN->leave_guild(player))
    {
	DEBUG("leaving the SOHM.\n");
    }
    else
    {
	notify_fail("For some reason you can't leave the School of High " +
	  "Magic and join the Wizards of High Sorcery.\n");
	return 0;
    }

    string name = player->query_real_name();

    send_debug_message("wohs", capitalize(player->query_real_name())
        + " has joined the Wizards of High Sorcery as a member of the " +
        C(str)+ " Robes.", LEADER_LOG);

    WOHS_MANAGER->remove_started_wohs_test();
    WOHS_MANAGER->remove_player_started_wohs_test(name);
    WOHS_MANAGER->remove_invited_wohs_test(name);
    WOHS_MANAGER->remove_invited_wohs_test_list(name);
    WOHS_MANAGER->add_wohs_test_props(player, LEFT_TEST, 0);

    switch (str)
    {
        case "white":
	{
	    if (join_guild(player))
	    {
		WOHS_MANAGER->set_wohs_order_colour(player, "white");
                WOHS_MANAGER->add_wohs_members_list(name, "white");
		display_join_sequence();
	    }
	    return 1; 
	}
        case "red":
	{
	    if (join_guild(player))
	    {
		WOHS_MANAGER->set_wohs_order_colour(player, "red");
                WOHS_MANAGER->add_wohs_members_list(name, "red");
		display_join_sequence();
	    }
	    return 1; 
	}
        case "black":
	{
	    if (join_guild(player))
	    {
		WOHS_MANAGER->set_wohs_order_colour(player, "black");
                WOHS_MANAGER->add_wohs_members_list(name, "black");
		display_join_sequence();
	    }
	    return 1; 
	}
    default: 
	write("That is not an Order of High Sorcery that you can join.\n");
	return 1;  
    }

    return 0;    
}


// Room descriptions for joinroom

string
long_descr()
{
    return "You stand in a small empty chamber off to the side of the " +
        "Hall of Mages within the Tower of High Sorcery in Wayreth. The " +
        "only exit here returns to the hall.\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && ob->query_prop(COMPLETED_TEST) && 
        !(ob->query_wiz_level()))
    {
       string order = WOHS_MANAGER->query_wohs_order_colour(ob);

       set_alarm(0.1,0.0, &choose(order));
       set_alarm(0.3,0.0, &join_guild(ob));

    }
}
