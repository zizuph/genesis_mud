/*
 * Guild Sphere
 *
 * This is the object that converts an old Spirit Circle guild member
 * into the new Elemental Clerics guild.
 *
 * Created by Petros, April 2014
 * Modified by Jaacar, July 2017 - changed it to work for SCoP->EC
 */
 
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>

#include "../defs.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define COUNCIL_CODE "/d/Calia/guilds/scop/specials/council_code"
// Prototypes
public int      touch_cmd(string arg);

/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    set_name("_elementalist_sphere");
    add_name( ({"elementalist_sphere", "sphere" }) );
    add_adj( ({ "swirling", "cloudy" }) );

    set_short("swirling cloudy sphere");    
    set_long("@@sphere_description@@");

    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_SELL, "This is much too valuable to sell!\n"); 
    add_prop(OBJ_M_NO_GET, "As hard as you try, you just cannot get the "
                         + "sphere.\n");    


    // These lines are necessary for loading the quest control room
    // since we access it implicitly
    setuid(); 
    seteuid(getuid());
    
}

/* Function name:       sphere_description
 * Description  :       Returns the long description for the guild sphere
 */
public string
sphere_description()
{
    string desc;
    
    desc = "Before you is a cloudy sphere that pulses with light. Within "
         + "its center, you glimpse milky wisps of elemental power that "
         + "swim lazily before your eyes. You may <touch sphere> if you wish "
         + "to convert into the new Elemental Clerics of Calia guild. "
         + "Note that this is not a reversible action.\n";
          
    return desc;
}

/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();    
    
    add_action(touch_cmd, "touch");
}

/* Function name:       touch_cmd
 * Description  :       Allows the player to switch guild shadows and
 *                      souls and participate in the testing.
 */
public int
touch_cmd(string arg)
{
	string old_rank;
	
    if (!check_seen(this_player()))
    {
        notify_fail("What?\n");
        return 0;
    }

    notify_fail("What do you wish to touch? The sphere?\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    object guild_sphere = PARSE_COMMAND_ONE(arg, 0, "[the] %i");
    if (!objectp(guild_sphere) || guild_sphere != this_object())
    {
        return 0;
    }
    
    setuid(); 
    seteuid(getuid());

    object player = this_player();
    if (sizeof(player->query_magic_effects()))
    {
        write("As you touch the sphere, the cloudy mist leaves the sphere and "
            + "envelops you completely. However, they quickly retreat as a "
            + "result of the existing enchantments that you possess. Please "
            + "remove all magical equipment and dispel all spells before "
            + "attempting to touch the sphere.\n");
        send_debug_message("cleric_convert", capitalize(player->query_real_name())
            + " attempted to use the sphere while still having magic "
            + "effects.", EVENTS_LOG);
        return 1;
    }

    if (!player->is_spirit_member())
    {
        write("You sense a latent power within the sphere, but nothing "
              + "interesting happens.\n");
        send_debug_message("cleric_convert", capitalize(player->query_real_name())
                           + " touched the sphere, but is not a valid Spirit Circle member.",
                           EVENTS_LOG);
        return 1;
    }
    // Besides changing the soul and the shadow, we need to do the following:
    // 1. Remove all the old cleric guild objects (they may not have them
    //    all but lets make sure they don't stick around in case they kept
    //    them or were in various stages of entrance to the guild.
    int old_guild_lay_stat = player->query_stat(SS_LAYMAN);
    int old_guild_occ_stat = player->query_stat(SS_OCCUP);
    send_debug_message(
        "cleric_convert", capitalize(player->query_real_name()) +
        " conversion: guild lay stat (" + old_guild_lay_stat + ")," +
        " guild occ stat (" + old_guild_occ_stat + ")", EVENTS_LOG);
    // 1. Remove all the old cleric guild objects and give them the
    //    new mandala
    present("worshipper_wand", player)->remove_object();
    present("worshipper_dagger", player)->remove_object();
    present("worshipper_chalice", player)->remove_object();
    present("worshipper_pentacle", player)->remove_object();
    present("worshipper_sceptre", player)->remove_object();
    present("_aeria_staff_", player)->remove_object();
    present("_psuchae_staff_", player)->remove_object();
    present("_spirit_apprentice_spells_", player)->remove_object();
    present("_schosen_", player)->remove_object();
    present("_diabrecho_staff_", player)->remove_object();
    present("_spirit_elder_spells_", player)->remove_object();
    present("_gu_staff_", player)->remove_object();
    present("spirit_holy_symbol", player)->remove_object();
    present("_spirit_info_book_", player)->remove_object();
    present("_spirit_action_limiter_", player)->remove_object();
    present("_action_limiter_", player)->remove_object();
    present("_spirit_master_spells_", player)->remove_object();
    present("_psuchae_holy_scroll_", player)->remove_object();
    present("_pyros_staff_", player)->remove_object();
    present("spirit_circle_test_book", player)->remove_object();
    player->remove_prop(LIVE_M_MOUTH_BLOCKED);
    clone_object(ELEMENTALIST_OBJS + "child_mandala")->move(player, 1);
    if (!present("_elemental_guild_wand", player))
    	clone_object(ELEMENTALIST_OBJS + "power_tool_wand")->move(player, 1);
    if (!present("_elemental_guild_dagger", player))
    	clone_object(ELEMENTALIST_OBJS + "power_tool_dagger")->move(player, 1);
    if (!present("_elemental_guild_chalice", player))
    	clone_object(ELEMENTALIST_OBJS + "power_tool_chalice")->move(player, 1);
    if (!present("_elemental_guild_pentacle", player))
    	clone_object(ELEMENTALIST_OBJS + "power_tool_pentacle")->move(player, 1);
    	
    GUILD_MANAGER->add_cleric(this_player());
    // 2. Get their old spirit circle rank
    if (COUNCIL_CODE->is_spirit_apprentice(player->query_real_name()))
    {
    	old_rank = "apprentice";
    	COUNCIL_CODE->remove_apprentice(player->query_real_name());
    }
    if (COUNCIL_CODE->is_spirit_master(player->query_real_name()))
    {
    	old_rank = "master";
    	COUNCIL_CODE->remove_master(player->query_real_name());
    }
    if (COUNCIL_CODE->is_spirit_elder(player->query_real_name()))
    {
    	old_rank = "elder";
    }
    	
    // 3. Transfer to their new rank
    switch (old_rank)
    {
    	case "master":
    		// To Full Master
    		if (player->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    		{
    			GUILD_MANAGER->set_full_master(player, 1);
    			GUILD_MANAGER->set_master_cleric(player, 1);
    			GUILD_MANAGER->set_player_conduit_earned(player, 12501);
    			GUILD_MANAGER->set_practice_level(player, 10001); 
    		}
    		// Or just Master
    		else
    		{
    			GUILD_MANAGER->set_master_cleric(player, 1);
    			GUILD_MANAGER->set_player_conduit_earned(player, 5000);
    			GUILD_MANAGER->set_practice_level(player, 8001); 
    		}
    		break;
    	case "elder":
    		GUILD_MANAGER->set_elder_cleric(player, 1);
    		GUILD_MANAGER->set_full_master(player, 1);
    		GUILD_MANAGER->set_master_cleric(player, 1);
    		GUILD_MANAGER->set_player_conduit_earned(player, 12501);
    		GUILD_MANAGER->set_practice_level(player, 10001);
    		break;
    	default:
    		GUILD_MANAGER->set_child_cleric(player, 1);
    		GUILD_MANAGER->set_player_conduit_earned(player, 1000);
    		GUILD_MANAGER->set_practice_level(player, 1000);
    		break;
    }
    // 4. Add the new guild shadows
    GUILD_MANAGER->convert_occ_guild(player);
    write("As you touch the sphere, the cloudy mist leaves the sphere and "
          + "envelops you completely. You sense yourself being changed and "
          + "the gifts you possess to be different. Seek your new gifts "
          + "by looking to your <prayers>. Going over <help cleric> "
          + "wouldn't hurt either.\n");
    write("Once you have done all of that, head to the Conduit chamber to "+
        "<divine> your vision quests. There are five in total for you to see.\n"+
        "After those have been completed, you should head to the statue of the "+
        "Diety you wish to follow and worship them there. Finally once that "+
        "selection has been made, head to the library to find your Word of Power "+
        "appropraite for your branch that you need to carve into your mandala.\n");
    send_debug_message("cleric_conversion", capitalize(player->query_real_name())
                       + " has been converted.", EVENTS_LOG);

    return 1;
}

/*
 * Function:    check_seen
 * Description: This ensures that only those who have their rune stones
 *              tuned to this object can actually see it.
 */
public int
check_seen(object for_obj)
{
    if (for_obj->query_wiz_level())
    {
        // Wizards can see all objects
        return 1;
    }
    
    if (for_obj->is_spirit_member())
    {
        // Old Spirit Circle Members have a shadow that will return true for
        // the is_spirit_member call.
        return 1;
    }
    
    return 0;
}
