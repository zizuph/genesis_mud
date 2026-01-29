/*
 * Upgrade Code for Knights
 *
 * This file contains the code that will upgrade an existing Knight
 * running the old Knight code (2008 and before) and the new code.
 *
 * Created by Petros, December 2008
 */
 
#pragma strict_types

#include "../guild.h"

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define UPGRADE_LOG             (KLOG + "upgrade_conversion")
#define OLD_KNIGHT_SHADOW       "/d/Krynn/solamn/vin/knight/obj/occ_shadow"
#define OLD_KNIGHT_CMDSOUL      "/d/Krynn/solamn/vin/knight/obj/solamnian_soul"
#define OLD_KNIGHT_START_ROOM   "/d/Krynn/solamn/vin/room/startroom"
#define OLD_KNIGHT_MEDAL        "/d/Krynn/solamn/vin/knight/obj/medal"
#define OLD_ADMIN               "/d/Krynn/solamn/vin/knight/admin/admin"
#define KNIGHT_SHADOW           O_SHADOW
#define KNIGHT_CMDSOUL          KNIGHT_SOUL
#define KNIGHT_START_ROOM       (VROOM + "startroom")
#define KNIGHT_MEDAL            MEDALPATH

/* 
 * Function name:       has_old_knight_shadow
 * Description  :       Goes through the shadows and sees if the player
 *                      has the old knight shadow.
 * Arguments    :       player - player to check if they have the knight
 *                               shadow
 * Returns      :       0/1 - does not have old shadow/has old shadow
 */
public int
has_old_knight_shadow(object player)
{
    object current_shadow;
    
    current_shadow = player;
    while (current_shadow = shadow(current_shadow, 0))
    {
        if (MASTER_OB(current_shadow) == OLD_KNIGHT_SHADOW)
        {
            return 1;
        }
    }
    
    return 0;
}

public int
replace_knight_shadow(object player)
{
    object knight_shadow;
    
    setuid();
    seteuid(getuid());
    
    if (!has_old_knight_shadow(player)
        || !player->remove_guild_occ())
    {
        // No need to do a conversion, since the player does not have
        // the old Knight shadow.
        player->catch_tell("An error occurred while trying to convert "
                         + "to the new Knight code. Please report the "
                         + "bug to the Knight GM.\n"
                         + "Error: Old Knight shadow not found.\n");
        send_debug_message("knight_upgrade", 
                           "Knight does not have the old "
                         + "Knight shadow: "
                         + capitalize(player->query_real_name()) + ".\n",
                           UPGRADE_LOG);
        return 0;
    }
                
    send_debug_message("knight_upgrade", 
                       "Converting knight shadow for "
                     + capitalize(player->query_real_name()) + ".",
                     UPGRADE_LOG);
    knight_shadow = clone_object(KNIGHT_SHADOW);
    if (knight_shadow->shadow_me(player, "occupational", 
                                 "fighter", GUILD_NAME) != 1)
    {
        send_debug_message("knight_upgrade", 
                           "Failed converting the "
                         + "knight shadow with the new one.",
                           UPGRADE_LOG);
        player->catch_tell("An error occurred while trying to convert "
                         + "to the new Knight code. Please report the "
                         + "bug to the Knight GM.\n"
                         + "Error: Could not add new Knight shadow.\n");
        knight_shadow->remove_shadow();
        return 0;
    }

    send_debug_message("knight_upgrade", 
                       "Successfully replaced "
                     + "the old knight shadow with the new one.",
                       UPGRADE_LOG);
    return 1;
}

public int
remove_cavalry_shadow(object player)
{   
    int guildstat;
    
    setuid();
    seteuid(getuid());
     
    if (OLD_ADMIN->query_cavalry(player->query_name()))
    {
        OLD_ADMIN->remove_cavalry(player->query_name());
        send_debug_message("knight_upgrade", 
                           "Successfully removed " + player->query_name()
                         + " from the ADMIN list for Cavalry.",
                           UPGRADE_LOG);    
    }
    
    if (player->query_guild_name_lay() != "Solamnian Cavalry")
    {
        // Nothing to remove. Just return.
        return 0;
    }
    
    if (player->remove_guild_lay())
    {
        guildstat = player->query_guild_stat(SS_LAYMAN);
        player->clear_guild_stat(SS_LAYMAN);
        
        send_debug_message("knight_upgrade", 
                           "Successfully removed the Cavalry Shadow and reset "
                         + "the guild stat from " + guildstat + " to zero.",
                           UPGRADE_LOG);    
        return 1;
    }
    
    send_debug_message("knight_upgrade", 
                       "Failed to remove the Cavalry Shadow.",
                       UPGRADE_LOG);    
    
    return 0;
}

public int
replace_knight_cmdsoul(object player)
{
    player->remove_cmdsoul(OLD_KNIGHT_CMDSOUL);
    if (player->add_cmdsoul(KNIGHT_CMDSOUL))
    {
        player->update_hooks();
        player->setup_skill_decay();        
        send_debug_message("knight_upgrade", 
                           "Successfully replaced "
                         + "the old knight soul with the new one.",
                           UPGRADE_LOG);
        return 1;
    }
    
    send_debug_message("knight_upgrade", 
                       "Failed to replace the old knight soul with "
                     + "the new one.",
                       UPGRADE_LOG);
    return 0;
}

public int
replace_knight_start_location(object player)
{
    string start_location;
    
    start_location = player->query_default_start_location();
    if (start_location == OLD_KNIGHT_START_ROOM)
    {
        player->set_default_start_location(KNIGHT_START_ROOM);
        player->move_living("M", KNIGHT_START_ROOM, 1, 1);
        send_debug_message("knight_upgrade", 
                           "Successfully replaced "
                         + "the old knight start room with the new one.",
                           UPGRADE_LOG);
        return 1;
    }
    
    return 0; // didn't replace start location
}

public int
replace_knight_medal(object player)
{
    object oldmedal, newmedal;
    if ((oldmedal = present("pal_med", player))
        && MASTER_OB(oldmedal) == OLD_KNIGHT_MEDAL)
    {
        setuid();
        seteuid(getuid());
        
        // Create the new medal and copy over the options
        newmedal = clone_object(KNIGHT_MEDAL);
        newmedal->set_generous(oldmedal->query_generous());
        newmedal->set_primary(oldmedal->query_primary());
        newmedal->move(player, 1);
        oldmedal->remove_object();
        send_debug_message("knight_upgrade", 
                           "Successfully replaced "
                         + "the old knight tunic with the new one.",
                           UPGRADE_LOG);        
        return 1;
    }

    return 0;
}

/* 
 * Function name:       upgrade_knight
 * Description  :       Upgrades the Knight to the new Knight Code
 * Arguments    :       player - player to do the conversion on
 * Returns      :       0/1 - failure - success
 */
public int
upgrade_knight(object player)
{
    // First replace the Knight Shadow
    if (!replace_knight_shadow(player))
    {
        return 0;
    }
    
    // Remove the Cavalry if they have it.
    remove_cavalry_shadow(player);
    
    // Successfully removed the shadow. Now remove the old cmdsoul
    // and add the new one.
    if (!replace_knight_cmdsoul(player))
    {
        return 0;
    }
    
    // Now we need to move the player to the new start location
    // and set their default start location
    replace_knight_start_location(player);
    
    // Finally, replace the knight medal/tunic
    replace_knight_medal(player);
    
    return 1;
}
