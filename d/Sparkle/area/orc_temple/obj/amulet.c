/*
 *  /d/Sparkle/area/orc_temple/obj/amulet.c
 *
 *  This is the amulet that Karkadelt will sell in his shop to players
 *  who wish to take on the imbuement quests but are deemed a threat
 *  by Yog-Sothoth. Wearing it will reduce your combat skills and all
 *  stats to 20.
 *
 *  Created December 14, 2010 by Lavellan
 *      Slight revision and update by Gorboth, January 2011
 *      Revised by Mirandus to add a wear confirmation and to remove
 *      the delay between stat loss/gain, August 2015
 *  Updated August 2, 2016 by Gronkas - fixed a typo
 *  
 *  2021-06-01 - Cotillion
 *  - Require players to be almost fully healed before wearing
 */

#pragma strict_types
#include "../defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <wa_types.h>
#include <composite.h>
#include <files.h>
#include <ss_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";

/* Definitions */
#define    LOSE_WARNING              "_amulet_lose_warning"
#define    WEAR_WARNING              "_amulet_wear_warning"
#define    WEAR_CUTOFF               0.85

/* Global Variables */
public int     pending_alarm = 0;
public mapping stat_reductions = ([ ]);

/* Prototypes */
public void descale_player(object player);
public void scale_player(object player);


/*
 * Function name:        create_object
 * Description  :        The constructor
 */
public void
create_object()
{
    set_name("amulet");
    add_name(AMULET);
    add_adj("shiny");
    add_adj("steel");
    set_long("This amulet consists of a brightly polished steel"
      + " circle that has been inscribed with many arcane symbols.\n");

    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_SELL, "That would not be a good idea.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better keep your amulet! You could"
      + " <discard> it if you really wanted to.\n");
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_I_WEIGHT, 15);

    set_looseness(50);
    set_layers(1);
    set_slots(A_NECK);
    set_wf(this_object());
    
    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name: leave_env
 * Description  : When you inherit /lib/wearable_item.c into any object other
 *                than /std/armour.c you MUST also define the function
 *                leave_env() as copy of this function. It MUST make the
 *                call to wearable_item_leave_env(from, to) as well. If
 *                you omit this, then the item will not be automatically
 *                removed when the player drops it, for instance.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    wearable_item_leave_env(from, to);
} /* leave_env */


/*
 * Function name: appraise_object
 * Description  : When you inherit /lib/wearable_item.c into any object
 *                other than /std/armour.c you MUST also define the function
 *                appraise_object() as copy of this function. It MUST make
 *                the call to appraise_wearable_item() as well. If you omit
 *                this, then the player will not be able to appraise this
 *                item properly.
 * Arguments    : int num - the semi-randomised appraise skill.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    
    appraise_wearable_item();
} /* appraise_object */


/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    object player = environment(this_object());
    if (!objectp(player))
    {
        // Something is wrong because we can't get the person trying to wear this amulet
        return -1;
    }
    
    if (!interactive(player))
    {
        // NPCs can wear this normally.
        return 0;
    }
    
    if (sizeof(get_alarm(pending_alarm)))
    {
        return "The effects of the amulet cause you to swoon. You'll"
          + " have to wait a few more seconds until your head clears.\n";
    }

    mixed * weaps = player->query_weapon(-1);
    if (sizeof(weaps))
    {
        return "You can't manage to get the chain untangled whilst wielding " +
            COMPOSITE_DEAD(weaps) + "!\n";
    }

    if (itof(player->query_hp()) / itof(player->query_max_hp()) < WEAR_CUTOFF) {
        return "The amulet refuses to be worn due to your lack of health.\n";
    }

    
    if (!player->query_prop(WEAR_WARNING))
    {
        player->add_prop(WEAR_WARNING, 1);

        return "Wear the " + short() + "? If you are in Sparkle then "
        +"you will be much weaker than before. Otherwise this amulet will "
        +"do nothing. Retype to confirm.\n";
        
    }

    pending_alarm = set_alarm(0.0, 0.0, &descale_player(player));
    
    // The Amulet Shadow reduces the person's skills
    if (!player->has_sparkle_amulet_shadow())
    {
        setuid();
        seteuid(getuid());
        object amulet_shadow = clone_object(OBJ_DIR + "amulet_shadow");
        amulet_shadow->shadow_me(player);
    }
    
    return 0;
} /* wear */


public mixed
remove(object obj)
{
    object player = query_worn();
    if (!objectp(player))
    {
        // Something is wrong because we can't get the wearer.
        return -1;
    }

    if (!interactive(player))
    {
        return 0;
    }

    if (sizeof(get_alarm(pending_alarm)))
    {
        return "The effects of the amulet cause you to swoon. You'll"
          + " have to wait a few more seconds until your head clears.\n";
    }

    if (environment(player)->id(DUNGEON_ROOM))
    {
        return "As you begin to lift the amulet off of your"
          + " neck, you sense a palpable awareness in the air around"
          + " you stir with malice, and fleeting hints of an"
          + " unfathomable horror lick at your mind. You do not dare"
          + " to take the amulet off while in these dungeons lest"
          + " that horror awaken to your presence!\n";
    }

    pending_alarm = set_alarm(0.0, 0.0, &scale_player(player));
    
    player->remove_prop(WEAR_WARNING);
    if (player->has_sparkle_amulet_shadow())
    {
        player->remove_sparkle_amulet_shadow();
    }
    return 0;
} /* remove */

/*
 * Function name:        query_auto_load
 * Description  :        players may keep this item over multiple
 *                       logins
 * Returns      :        string - the filename of this module.
 */
public string
query_auto_load()
{
    return MASTER + ":";
} /* query_auto_load */


/*
 * Function name:        lose_it
 * Description  :        Allow players to get rid of this item, if they
 *                       really want to.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
lose_it(string arg)
{
    string  word;
    object *obj;

    notify_fail("Discard what, the amulet?\n");

    if (!strlen(arg))
    {
        return 0;
    }

    object player = environment(this_object());
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        notify_fail("You have to be holding the item to discard it!\n");
        return 0;
    }

    object target = PARSE_COMMAND_ONE(arg, player, "[the] %i");
    if (!objectp(target) || target != this_object())
    {
        return 0;
    }
    
    if (query_worn())
    {
        notify_fail("You need to remove it before discarding it.\n");
        return 0;
    }

    if (!this_object()->query_prop(LOSE_WARNING))
    {
        this_object()->add_prop(LOSE_WARNING, 1);

        write("Permanently discard your " + short() + "? Retype to"
          + " confirm.\n");
        return 1;
    }

    write("You discard your " + short() + ".\n");
    this_object()->remove_object();
    return 1;
} /* lose_it */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(lose_it, "discard");
} /* init */

/*
 * Function name:        scale_health
 * Description  :        We scale the player's % of existing health down
 *                       to their new size following removal of the
 *                       amulet.
 * Arguments    :        object player - the player
 *                       float health_percentage - the scaling factor
 */
public void
scale_health(object player, float health_percentage)
{
    float  health_max = itof(player->query_max_hp());
    int    current_health = player->query_hp();
    int    new_health = ftoi(health_max * health_percentage);

    player->heal_hp(new_health - current_health);
} /* scale_health */

/*
 * Function:    scale_stuffed
 * Description: Scale the stuffed to the correct percentage given the
 *              player's current stats.
 * Argument:    object player - the player
 *              float stuffed_percentage - the final percentage given current stats
 */
public void
scale_stuffed(object player, float stuffed_percentage)
{
    float  stuffed_max = itof(player->eat_max());
    int    current_stuffed = player->query_stuffed();
    int    new_stuffed = ftoi(stuffed_max * stuffed_percentage);

    if (new_stuffed == current_stuffed)
    {
        return;
    }
    else if (new_stuffed > current_stuffed)
    {
        int max_increment = ftoi(stuffed_max / 5.0);
        // eat_food won't let you do it all at once. no more than 1/5th at a time.
        for (int interim = current_stuffed; interim < new_stuffed; interim += max_increment)
        {
            if (interim + max_increment <= new_stuffed)
            {
                player->eat_food(max_increment);
            }
            else
            {
                player->eat_food(new_stuffed - interim);
            }
        }
    }
    else
    {
        // No limit on negative eating.
        player->eat_food(new_stuffed - current_stuffed);
    }
}

/*
 * Function:    scale_soaked
 * Description: Scale the soaked to the correct percentage given the
 *              player's current stats.
 * Argument:    object player - the player
 *              float soaked_percentage - the final percentage given current stats
 */
public void
scale_soaked(object player, float soaked_percentage)
{
    float  soaked_max = itof(player->drink_max());
    int    current_soaked = player->query_soaked();
    int    new_soaked = ftoi(soaked_max * soaked_percentage);

    if (new_soaked == current_soaked)
    {
        return;
    }
    else if (new_soaked > current_soaked)
    {
        int max_increment = ftoi(soaked_max / 15.0);
        // eat_food won't let you do it all at once. no more than 1/15th at a time.
        for (int interim = current_soaked; interim < new_soaked; interim += max_increment)
        {
            if (interim + max_increment <= new_soaked)
            {
                player->drink_soft(max_increment);
            }
            else
            {
                player->drink_soft(new_soaked - interim);
            }
        }
    }
    else
    {
        // No limit on negative drinking
        player->drink_soft(new_soaked - current_soaked);
    }
}

/*
 * Function:    scale_intox
 * Description: Scale the intox to the correct percentage given the
 *              player's current stats.
 * Argument:    object player - the player
 *              float intox_percentage - the final percentage given current stats
 */
public void
scale_intox(object player, float intox_percentage)
{
    float  intox_max = itof(player->intoxicated_max());
    int    new_intox = ftoi(intox_max * intox_percentage);

    player->set_intoxicated(new_intox);
}

/*
 * Function:    is_descaling_stats
 * Description: Returns whether the amulet currently has recorded
 *              descaling stats for the player. This us used by the
 *              shadow to determine if it should also reduce the skills.
 */
public int
is_descaling_stats()
{
    return (sizeof(m_indices(stat_reductions)) > 0);
}

/*
 * Function name:        descale_player
 * Description  :        Alter the stats of the player and produce a
 *                       message to tell them the effect has taken
 *                       place.
 */
public void
descale_player(object player)
{
    if (!objectp(player))
    {
        return;
    }
    
    mapping effective_paths =
        ([ "/d/Sparkle" : "S",
           "/d/Genesis" : "G",
           "/w" : "W" ]);
    if (!match_path(effective_paths, file_name(environment(player))))
    {
        return;
    }
    
    if (player->query_average() >= 40)
    {
        if (is_descaling_stats())
        {
            // We won't try and descale the player more than once. If we already
            // have some stat reductions, that's it.
            return;
        }
        
        player->catch_tell("A sickening shudder"
          + " goes through your body, and you feel much weaker and"
          + " less skilled than before!\n");

        float health_percentage = itof(player->query_hp()) / itof(player->query_max_hp());
        float stuffed_percentage = itof(player->query_stuffed()) / itof(player->eat_max());
        float soaked_percentage = itof(player->query_soaked()) / itof(player->drink_max());
        float intox_percentage = itof(player->query_intoxicated()) / itof(player->intoxicated_max());
        
        foreach (int player_stat : ({ SS_STR, SS_DEX, SS_CON, SS_INT, SS_WIS, SS_DIS }))
        {
            int current_stat_value = player->query_base_stat(player_stat);
            if (current_stat_value <= 20)
            {
                continue;
            }
            stat_reductions[player_stat] = 20 - current_stat_value; // reduce the base stat down to 20
            player->set_stat_extra(player_stat, player->query_stat_extra(player_stat) + stat_reductions[player_stat]);
        }

        /* We need to scale the players hitpoints down to the correct
         * percentage for their new size.
         */
        scale_health(player, health_percentage);
        /* Large players who are full need to have their stuffed levels
         * reduced. Otherwise, it might be a very long time before they
         * are able to do things like eat herbs, etc.
         */
        scale_stuffed(player, stuffed_percentage);
        /* Lets do the same thing for soaked levels, so that players can
         * consume alcohol.
         */
        scale_soaked(player, soaked_percentage);
        /* We absolutely MUST do the same for intox. Players who have
         * intox values far beyond their intoxication maximum receive
         * an inordinate benefit in regeneration of hitpoints.
         */
        scale_intox(player, intox_percentage);
        
    }
}

/*
 * Function name:        scale_player
 * Description  :        When the player removes the amulet, we 
 *                       return their stats to normal
 */
public void
scale_player(object player)
{
    if (!is_descaling_stats())
    {
        // Nothing to do if there have been no stat reductions.
        return;
    }
    
    float health_percentage = itof(player->query_hp()) / itof(player->query_max_hp());
    float stuffed_percentage = itof(player->query_stuffed()) / itof(player->eat_max());
    float soaked_percentage = itof(player->query_soaked()) / itof(player->drink_max());
    float intox_percentage = itof(player->query_intoxicated()) / itof(player->intoxicated_max());
    
    foreach (int player_stat : m_indices(stat_reductions))
    {
        player->set_stat_extra(player_stat, player->query_stat_extra(player_stat) - stat_reductions[player_stat]);
        m_delkey(stat_reductions, player_stat); // remove the mapping so we don't reduce it again.
    }
    
    /* We need to scale the players hitpoints down to the correct
     * percentage for their new size.
     */
    scale_health(player, health_percentage);
    /* Large players who are full need to have their stuffed levels
     * reduced. Otherwise, it might be a very long time before they
     * are able to do things like eat herbs, etc.
     */
    scale_stuffed(player, stuffed_percentage);
    /* Lets do the same thing for soaked levels, so that players can
     * consume alcohol.
     */
    scale_soaked(player, soaked_percentage);
    /* We absolutely MUST do the same for intox. Players who have
     * intox values far beyond their intoxication maximum receive
     * an inordinate benefit in regeneration of hitpoints.
     */
    scale_intox(player, intox_percentage);
} /* scale_player */


