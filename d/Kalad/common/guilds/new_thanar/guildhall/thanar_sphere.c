/*
 * Guild Sphere
 *
 * This is the object that converts an old Thanar guild member
 * into the new location.
 *
 * Created by Petros, April 2014
 * Modified by Jaacar, July 2017 - changed it to work for SCoP->EC
 * Modified by Mirandus, January 2018 - Changed to move old Thanar to new.
 */
 
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>

#include "guild.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public int      touch_cmd(string arg);

/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    set_name("_thanar_sphere");
    add_name( ({"thanar_sphere", "sphere" }) );
    add_adj( ({ "dark", "cloudy" }) );

    set_short("dark cloudy sphere");    
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
    
    desc = "Before you is a cloudy sphere that pulses with darkness. Within "
         + "its center, you glimpse milky wisps of divine power that "
         + "swim lazily before your eyes. You may <touch sphere> if you wish "
         + "to move to the new location of the Thanarian Order. "
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
    
    object *guild_objs;
    
       
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
    guild_objs = filter(deep_inventory(player),&->id("_thanar_emblem"));

    if (!player->query_guild_member(GUILD_NAME))
    {
        write("You sense a latent power within the sphere, but nothing "
              + "interesting happens.\n");
        return 1;
    }
    // Besides changing the soul and the shadow, we need to do the following:
    // 1. Remove the old guild object
    if (!player->remove_guild_race()) 
    {
        write("something went horribly wrong.\n"); 
        return 1;
    }
      
    player->remove_cmdsoul("/d/Raumdor/guilds/thanar/soul");
    player->update_hooks();
    guild_objs->remove_object();
    //Add new stuff back to them
    clone_object(OBJECT)->move(player, 1);
    object guild_race_shadow = clone_object(SHADOW);
    int race_return_code = guild_race_shadow->shadow_me(player,
    GUILD_TYPE, GUILD_STYLE, GUILD_NAME, "");
    if (race_return_code != 1)
    {
        player->catch_tell("For some unknown reason you cannot join"
        +race_return_code+". Please contact the Guildmaster.\n");
        guild_race_shadow->remove_shadow();
        return 0;
    }
    if (this_player()->query_default_start_location() == 
    "/d/Raumdor/guilds/thanar/start")
    {
        this_player()->set_default_start_location(STARTLOC);
        
    }
    player->setup_skill_decay();
    player->set_guild_pref(SS_RACE, GUILD_TAX);
    player->update_hooks();
    player->update_thanar_shadow();
    write("You sense a the divine will of Thanar has been done and you "
              + "have successfully been transitioned.\n");
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
    
    if (for_obj->query_guild_member(GUILD_NAME))
    {
        return 1;
    }
    
    return 0;
}
