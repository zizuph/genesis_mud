/* 
 *  Shadow Converter for the Neidar Clan
 *  
 *  This file performs the conversion step to convert an old
 *  neidar into a newly recoded neidar.
 *
 *  Created by Petros, June 2009
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include "../guild.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define OLD_NEIDAR_SHADOW           "/d/Ansalon/guild/dwarf/occ_shadow"
#define OLD_NEIDAR_EMBLEM           "/d/Ansalon/guild/dwarf/emblem"
#define OLD_NEIDAR_CMDSOUL          "/d/Ansalon/guild/dwarf/cmdsoul"
#define OLD_NEIDAR_START_LOCATION   "/d/Ansalon/guild/dwarf/start"
#define LOGFILE                     SAVE_PATH + "recode_conversions"

/* 
 * Function name:       has_old_neidar_shadow
 * Description  :       Goes through the shadows and sees if the player
 *                      has the old neidar shadow.
 * Arguments    :       player - player to check if they have the neidar
 *                               shadow
 * Returns      :       0/1 - does not have old shadow/has old shadow
 */
public int
has_old_neidar_shadow(object player)
{
    object current_shadow;
    
    current_shadow = player;
    while (current_shadow = shadow(current_shadow, 0))
    {
        if (MASTER_OB(current_shadow) == OLD_NEIDAR_SHADOW)
        {
            return 1;
        }
    }
    
    return 0;
}

public void
replace_old_emblem(object player)
{
    object * emblems;
    object emblem;
    
    setuid();
    seteuid(getuid());
    
    emblems = filter(all_inventory(player), &->id(GUILD_EMBLEM_ID));
    emblems->remove_object(); 

    // Now clone a new one.
    emblem = clone_object(GUILD_EMBLEM);
    emblem->move(player, 1);
}

public void
log_existing_info(object player)
{
    string real_name;        
    int avg_stat, guild_stat, battlerage_skill, chop_skill;
    // We want to keep track of certain things in case the conversion
    // goes wrong.
    // 1. Guild Exp/Stat
    // 2. Chop and Battlerage skills
    // 3. Avg Stat
    real_name = IS_PLAYER_OBJECT(player) ? 
        capitalize(player->query_real_name()) : file_name(player);
    avg_stat = player->query_average_stat();
    guild_stat = player->query_stat(SS_OCCUP);
    battlerage_skill = player->query_skill(BATTLERAGING_SKILL);
    chop_skill = player->query_skill(SS_GUILD_SPECIAL_SKILL);
    
    send_debug_message("neidar_shadow_conversion",
        real_name + " (" + avg_stat + ") has guild stat of "
      + guild_stat + ". Battlerage: " + battlerage_skill
      + " Chop: " + chop_skill + ".", 
        LOGFILE);     
}

/* 
 * Function name:       convert_neidar_shadow
 * Description  :       Converts the old Neidar shadow to the new one
 * Arguments    :       player - player to do the conversion on
 * Returns      :       0/1 - failure - success
 */
public int
convert_neidar_shadow(object player)
{
    object neidar_shadow;
    string start_location, real_name;
    int errcode;
    
    setuid();
    seteuid(getuid());
    
    real_name = IS_PLAYER_OBJECT(player) ? 
        capitalize(player->query_real_name()) : file_name(player);
            
    if (!has_old_neidar_shadow(player))
    {
        // No need to do a conversion, since the player does not have
        // the old shadow.
        player->catch_tell("A strange feeling passes over you and you "
            + "realize that something isn't quite right. You should "
            + "probably tell your guildmaster that you have a feeling "
            + "something is wrong.\n");
        send_debug_message("neidar_shadow_conversion", 
            real_name + " does not have the old neidar shadow.",
            LOGFILE);
        return 0;
    }
    
    log_existing_info(player);
            
    // Remove the existing Calian Shadow     
    player->remove_guild_occ();
    
    send_debug_message("neidar_shadow_conversion", 
        "Converting old neidar shadow for " + real_name + ".",
        LOGFILE);

    neidar_shadow = clone_object(NEIDAR_SHADOW);
    if ((errcode = neidar_shadow->shadow_me(player, GUILD_TYPE, 
         GUILD_STYLE, GUILD_NAME)) != 1)
    {
        string errstring = "";
        switch (errcode)
        {
        case 0:
            errstring = "No player or player already shadowed.";
            break;
            
        case -1:
            errstring = "No name of guild.";
            break;
            
        case -2:
            errstring = "Not correct guild type.";
            break;
            
        case -3:
            errstring = "No style of guild.";
            break;
            
        case -4:
            errstring = "The other guilds don't like this guild.";
            break;            
        }
        send_debug_message("neidar_shadow_conversion", 
            "Failed to successfully add the new neidar shadow with error: "
          + errstring, LOGFILE);
        player->catch_tell("A strange feeling passes over you and you "
            + "realize that something isn't quite right. You should "
            + "probably tell your guildmaster that you have a feeling "
            + "something is wrong and that you are now lacking an "
            + "occupational guild.\n");
        neidar_shadow->remove_shadow();
        return 0;
    }
    else
    {
        send_debug_message("neidar_shadow_conversion", 
            "Successfully replaced the old neidar shadow with the new "
          + "one.", LOGFILE);

        // Successfully removed the shadow. Now remove the old cmdsoul
        // and add the new one.
        player->remove_cmdsoul(OLD_NEIDAR_CMDSOUL);
        player->add_cmdsoul(NEIDAR_CMDSOUL);
        player->update_hooks();
        player->setup_skill_decay();
        
        // Now we need to move the player to the new start location
        // and set their default start location if they started in
        // the old place.
        start_location = player->query_default_start_location();
        if (!strlen(start_location) 
            || start_location == OLD_NEIDAR_START_LOCATION)
        {
            player->set_default_start_location(GUILD_STARTLOC);            
            player->move_living("M", GUILD_STARTLOC, 1, 1);
        }
        
        // Now replace the guild emblem object
        replace_old_emblem(player);
        
        player->catch_tell("\nYou feel a rumbling beneath your feet and "
            + "lose your balance for a moment. A warm glow surrounds your "
            + "body as your feel the power of Reorx upon you. As quickly "
            + "as it appeared, it disappears yet again. You feel renewed "
            + "and more vigorous than before!\n\n");
        player->catch_tell("You ought to read your help files to find "
            + "out what you have been blessed with.\n");
        return 1;
    }        
}
