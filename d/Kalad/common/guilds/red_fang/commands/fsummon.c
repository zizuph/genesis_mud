/*
 * This code handles the summoning ability for the the Red
 * Fang racial guild in Kalad.
 *
 * Created October 2017 by Zignur
 * 2017-10-23 Zignur add a check if the player attacked a red fang wolf.
 * 2017-10-24 Zignur New messages for the summoning added 
 *
 */

#pragma strict_types
#include "/d/Kalad/defs.h"
inherit "/d/Genesis/specials/timed_ability";
#include "/d/Kalad/common/guilds/red_fang/default.h"
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

public void config_ability()
{
    ::config_ability();
    set_ability_name("fsummon");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(5);
    set_ability_cooldown_time(15);
    set_ability_target(target_actor);
    set_ability_vocal(1);
    set_ability_visual(0);
}

static void 
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You lean your head back and howl to the skies.\n" +
    "In the distance you hear a wolf howl back in response.\n");
    
    tell_room(environment(actor), QCTNAME(actor) + " howls like a wolf.\n" +
    "In the distance you hear a wolf howl back in response.\n", actor, actor);
}

static void 
resolve_ability(object actor, mixed *items, mixed *targets,
                int *resist, mixed *results)
{
    object  mount;
    int mount_fatigue, mount_health;
            
    setuid();
    seteuid(getuid());
    
    object* mounts;
    
    /* Find all cloned wolves in the world */
    if (objectp(mount = find_object(FANG_DIR(obj/wolf))))
    {
        mounts = object_clones(mount);
        
    }
        
    /* See if we own one of the wolves that are cloned */
    if (sizeof(mounts = filter(mounts, &operator(==)
        (, actor->query_real_name()) @ &->query_owner()))) 
    {
        /* Means we already have a active wolf */
         mount = mounts[0];           
    }
    /* Means we dont have a wolf active so we clone a new one */
    else
    {
        mount = clone_object(FANG_DIR(obj/wolf));
        mount->set_base_stat(SS_CON,(actor->query_stat(SS_CON)+50));

        if(actor->query_prop(WOLF_FATIGUE))
        {
            if(actor->query_prop(WOLF_DISMISS_TIME))
            {
                int dismiss_time = actor->query_prop(WOLF_DISMISS_TIME);

                // after 10 minutes of dismissing the wolf is fully rested.
                if((dismiss_time + 600) < time())
                    mount_fatigue = mount->query_max_fatigue();
                else
                    mount_fatigue = actor->query_prop(WOLF_FATIGUE);
            }
            else
                mount_fatigue = actor->query_prop(WOLF_FATIGUE);

        }        
        else
        {
            mount_fatigue = mount->query_max_fatigue(); 
        }

        if(actor->query_prop(WOLF_HEALTH))
        {
            if(actor->query_prop(WOLF_DISMISS_TIME))
            {
                int dismiss_time = actor->query_prop(WOLF_DISMISS_TIME);

                // after 10 minutes of dismissing the wolf is fully healed.
                if((dismiss_time + 600) < time())
                    mount_health = mount->query_max_hp();
                else
                    mount_health = actor->query_prop(WOLF_HEALTH);
            }
            else
                mount_health = actor->query_prop(WOLF_HEALTH);
        }        
        else
        {
            mount_health = mount->query_max_hp(); 
        }

        mount->refresh_steed(mount_fatigue, mount_health);
    
        /* If this function fails it means that we dont own a wolf */
        if(!(mount->configure_wolf(actor)) )
        {
            /* Tell the player to buy a wolf */
            actor->catch_msg("You do not own a wolf, travel to the" +
               " stables to purchase one.\n");    
           return;
        }        
    }
    
    /* Check if something went terrible wrong */
    if (!objectp(mount))
    {
        actor->catch_msg("Something went wrong.\n");
        return;
    }
    
    /* 2017-10-24 Zignur New messages for the summoning added */
    
    actor->catch_msg("Lurking from the shadows" +
        " comes a " + mount->query_short() + ", " + 
        mount->query_possessive() +  " body hunkered low to the ground."+
        " You reach out a hand for " + mount->query_objective() + " to sniff,"+
        " and " + mount->query_pronoun() + " springs up, pushing" +
        " "  + mount->query_possessive() + " weight into you.\n", 0, mount);
        
    tell_room(environment(actor), "Lurking from the shadows" +
        " comes a " + mount->query_short() + ", " + 
        mount->query_possessive() +  " body hunkered low to the ground."+
        " " + QCTNAME(actor)+ " reach out a hand for" + 
        " " + mount->query_objective() + " to sniff, and" +
        " " + mount->query_pronoun() + " springs up, pushing" +
        " " + mount->query_possessive() + " weight into" +
        " " + actor->query_objective() + ".\n", actor);   
 
    /* Move out the wolfie! */
    mount->move_living("M", environment(actor), 1, 1);
    
    /* Have the player mount it */
    actor->command("$mount " +  OB_NAME(mount) + "");  
    
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("You just summoned your wolf, maybe wait a while.\n");
}

public void
hook_special_in_cooldown()
{
    write("You just summoned your wolf, maybe wait a while.\n");
}

/*
   Used to see if its possible to summon the mount

*/
static int 
check_valid_action(object player, mixed *targets, string arg,
                   int execute)
{
    
    object* mounts;
    
    /*
     * See if the wolf is present in the room
     * Returns a array of all objects in the room with
     * query_owner == to this_player. Should never be more
     * than max one, if sizeof is null/0 then we have no
     * mounts present in the room.
     */
    if (sizeof(mounts = filter(all_inventory(environment(player)),
        &operator(==)(, player->query_real_name()) @ &->query_owner())))
    {
        player->catch_msg("Your wolf is already here.\n");
        return 0;    
    }
    
    /* We dont allow the player to summon while in combat */
    if (player->query_attack())
    {
        player->catch_msg("You are unable to summon your wolf while" +
            " you are in combat.\n");
            
        return 0;
    }
    
    /* No summoning in steed free rooms */
    if (environment(player)->query_prop(ROOM_I_NO_ALLOW_STEED))
    {
        player->catch_msg("You are unable to summon your wolf here.\n");
        return 0;
    }
    
    /* We cant summon when we are stunned */
    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot summon your wolf while you" +
            " are stunned.\n");
        return 0;
    }
    /* 2017-10-23 Zignur check if the player attacked a red fang wolf */
    if(player->query_prop("_rf_wolf_attacked"))
    {
        player->catch_msg("Your wolf refuses to answer your call after" +
            " your recent actions!\n");
        return 0;
    }    
    

    return 1; 
}
