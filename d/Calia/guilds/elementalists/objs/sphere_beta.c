/*
 * Guild Sphere
 *
 * Allows a Worshipper or SCoP to touch the sphere
 * and participate in the testing of the Elemental
 * guild alpha, beta, testing.
 *
 * Created by Petros, March 2013
 */
 
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

#include "../defs.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define GUILD_TESTER_SOUL   "/d/Genesis/specials/guilds/guild_tester_soul"
#define LAST_SWITCH_PROP    "_last_worshipper_switch_time"
  
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
         + "to participate in the beta testing of the Elemental Worshippers "
         + "or switch back if you are already testing.\n";
         
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

public string
query_beta_log_file()
{
    return ELEMENTALIST_LOGS + "beta_events";
}

/* Function name:       touch_cmd
 * Description  :       Allows the player to switch guild shadows and
 *                      souls and participate in the testing.
 */
public int
touch_cmd(string arg)
{
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
    
    setuid(); seteuid(getuid());
    // Possibilities
    // 1. Player is old worshipper
    // 2. Player is scop
    // 2. Player is new worshipper (w/o scop)
    // 4. Player is new worshipper (w/ scop)
    object player = this_player();
    if (sizeof(player->query_magic_effects()))
    {
        write("As you touch the sphere, the cloudy mist leaves the sphere and "
            + "envelops you completely. However, they quickly retreat as a "
            + "result of the existing enchantments that you possess. Please "
            + "remove all magical equipment and dispel all spells before "
            + "attempting to touch the sphere.\n");
        send_debug_message("worshipper_beta", capitalize(player->query_real_name())
            + " attempted to use the sphere while still having magic "
            + "effects.", query_beta_log_file());
        return 1;
    }
    
    mapping last_switch_mapping = query_prop(LAST_SWITCH_PROP);
    if (!m_sizeof(last_switch_mapping))
    {
        last_switch_mapping = ([ ]);
    }
    if (time() < (last_switch_mapping[player->query_real_name()] + 7200))
    {
        write("You touch the sphere, but nothing seems to happen. You sense "
            + "that the magical effects of the sphere have too recently "
            + "changed you and you need to wait longer before you can "
            + "touch the sphere again.\n");
        send_debug_message("worshipper_beta", capitalize(player->query_real_name())
            + " attempted to use the sphere again too quickly.", query_beta_log_file());
        return 1;
    }
    
    string guild_name = player->query_guild_name_lay();
    if (guild_name == "Elemental Worshippers of Calia")
    {
        if (player->is_elemental_cleric())
        {
            // 4. player is new worshipper (w/ scop)
            GUILD_TESTER_SOUL->stop_guild_player_version("cleric", this_player());
            GUILD_TESTER_SOUL->start_guild_player_version("scop", this_player());
            write("As you touch the sphere, the cloudy mist leaves the sphere and "
                + "envelops you completely. You sense the Elementals reverting you "
                + "to the natural gifts that you had before the beta testing.\n");
            send_debug_message("worshipper_beta", capitalize(player->query_real_name())
                + " (scop) ended beta testing.", query_beta_log_file());
        }
        else if (player->is_elemental_worshipper())
        {
            // 3. player is new worshipper (w/o scop)
            GUILD_TESTER_SOUL->stop_guild_player_version("worshipper", this_player());
            GUILD_TESTER_SOUL->start_guild_player_version("worshipper_old", this_player());
            write("As you touch the sphere, the cloudy mist leaves the sphere and "
                + "envelops you completely. You sense the Elementals reverting you "
                + "to the natural gifts that you had before the beta testing.\n");
            send_debug_message("worshipper_beta", capitalize(player->query_real_name())
                + " (ew) ended beta testing.", query_beta_log_file());        
        }
        else
        {
            /*
            // 1. old worshipper
            GUILD_TESTER_SOUL->stop_guild_player_version("worshipper_old", this_player());
            GUILD_TESTER_SOUL->start_guild_player_version("worshipper", this_player());
            write("As you touch the sphere, the cloudy mist leaves the sphere and "
                + "envelops you completely. You sense yourself being changed and "
                + "the gifts you possess to be different. Seek your new gifts "
                + "by looking to your <prayers>. Thank you for joining the "
                + "beta testing!\n");
            send_debug_message("worshipper_beta", capitalize(player->query_real_name())
                + " (ew) started beta testing.", query_beta_log_file());
            */
        }
        last_switch_mapping[player->query_real_name()] = time();
    }
/*    
    else if (guild_name == "Spirit Circle of Psuchae")
    {
        // 2. player is scop
        GUILD_TESTER_SOUL->stop_guild_player_version("scop", this_player());
        GUILD_TESTER_SOUL->start_guild_player_version("cleric", this_player());
        write("As you touch the sphere, the cloudy mist leaves the sphere and "
            + "envelops you completely. You sense yourself being changed and "
            + "the gifts you possess to be different. Seek your new gifts "
            + "by looking to your <prayers>. Thank you for joining the "
            + "beta testing!\n");
        last_switch_mapping[player->query_real_name()] = time();
        send_debug_message("worshipper_beta", capitalize(player->query_real_name())
            + " (scop) started beta testing.", query_beta_log_file());
    }
*/
    else
    {
        write("You gently caress the sphere, but nothing interesting seems "
            + "to occur.\n");
        send_debug_message("worshipper_beta", capitalize(player->query_real_name())
            + " (non-ew/scop) touched the sphere.", query_beta_log_file());
        return 1;
    }
    add_prop(LAST_SWITCH_PROP, last_switch_mapping);
    
    return 1;
}

