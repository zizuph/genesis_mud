/*
 * Guild Sphere
 *
 * This is the object that converts an old Worshipper guild member
 * into the new Elemental Worshippers guild.
 *
 * Created by Petros, April 2014
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
#define GUILD_TESTER_SOUL   "/d/Genesis/specials/guilds/guild_tester_soul"
#define SS_PATRON_ELEMENTAL 114052
#define SS_CARVED 114050
  
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
         + "to convert into the new Elemental Worshippers of Calia guild. "
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
        send_debug_message("worshipper_convert", capitalize(player->query_real_name())
            + " attempted to use the sphere while still having magic "
            + "effects.", EVENTS_LOG);
        return 1;
    }

    if (!player->is_worship())
    {
        write("You sense a latent power within the sphere, but nothing "
              + "interesting happens.\n");
        send_debug_message("worshipper_convert", capitalize(player->query_real_name())
                           + " touched the sphere, but is not a valid Worshipper.",
                           EVENTS_LOG);
        return 1;
    }
    // Besides changing the soul and the shadow, we need to do the following:
    // 1. Remove all the old worshipper guild objects
    // 2. Transfer their Patron Elemental (if any) over to the guild manager
    // 3. Transfer their Carvings (if any) over to the guild manager
    // 4. Set the "starting exp" based on their current guild stat
    int old_guild_stat = player->query_stat(SS_LAYMAN);
    int old_patron = player->query_skill(SS_PATRON_ELEMENTAL);
    int old_carved = player->query_skill(SS_CARVED);
    send_debug_message(
        "worshipper_convert", capitalize(player->query_real_name())
        + " conversion: guild stat (" + old_guild_stat + "), patron (" + old_patron
        + "), carved (" + old_carved + ")", EVENTS_LOG);
    GUILD_TESTER_SOUL->stop_guild_player_version("worshipper_old", this_player());
    // 1. Remove all the old worshipper guild objects
    present("worshipper_wand", player)->remove_object();
    present("worshipper_dagger", player)->remove_object();
    present("worshipper_chalice", player)->remove_object();
    present("worshipper_pentacle", player)->remove_object();
    present("worshipper_sceptre", player)->remove_object();
    GUILD_TESTER_SOUL->start_guild_player_version("worshipper", this_player());
    GUILD_MANAGER->add_worshipper(this_player());
    // 2. Transfer their Patron Elemental (if any) over to the guild manager
    GUILD_MANAGER->transfer_old_guild_patron_elemental(player);
    // 3. Transfer their carvings
    GUILD_MANAGER->transfer_old_guild_carving(player);
    // 4. Set starting experience to get the lower of current guild stat 
    //    or guild stat based on experience
    int experience_based_stat = player->exp_to_stat(player->query_max_exp() * 13 / (100 - 13));
    if (old_guild_stat < experience_based_stat)
    {
        int starting_exp = player->query_max_exp() - player->stat_to_exp(old_guild_stat) * (100 - 13) / 13;
        send_debug_message("worshipper_conversion", capitalize(player->query_real_name())
                           + " has a starting exp value of " + starting_exp + " in order "
                           + "to achieve a " + old_guild_stat + " guild stat.", EVENTS_LOG);
        // We need to set up a lower guild to match their old guild stat
        GUILD_MANAGER->set_starting_exp(player, starting_exp);
    }
    else
    {
        send_debug_message("worshipper_conversion", capitalize(player->query_real_name())
                           + " has a starting exp value of 0 in order "
                           + "to achieve a " + experience_based_stat + " guild stat.", EVENTS_LOG);
        GUILD_MANAGER->set_starting_exp(player, 0);
    }
    write("As you touch the sphere, the cloudy mist leaves the sphere and "
          + "envelops you completely. You sense yourself being changed and "
          + "the gifts you possess to be different. Seek your new gifts "
          + "by looking to your <prayers>. Going over <help worshipper> "
          + "wouldn't hurt either.\n");
    send_debug_message("worshipper_conversion", capitalize(player->query_real_name())
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
    
    if (for_obj->is_worship())
    {
        // Old Worshippers have a shadow that will return true for
        // the is_worship call.
        return 1;
    }
    
    return 0;
}
