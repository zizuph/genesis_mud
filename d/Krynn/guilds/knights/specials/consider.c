/*
 * /d/Krynn/guilds/knights/specials/consider.c
 *
 * This is the consider ability for Knights. It allows them to see their
 * progress in their prestige. It also allows them to verify the alignment
 * of others they meet so they will know whether they can kill them or
 * not. This is absolutely necessary for a Knight to roleplay well, as
 * they should not be killing people randomly.
 *
 * Created by Petros, October 2008
 */
 
#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

public void config_ability()
{
    ::config_ability();
    set_ability_name("consider");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_time(0);
    set_ability_target(target_one_present_living);    
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
}

public void
print_consider_for_self(object actor)
{
    int level, sublevel, prestige;
    string nr, st, pr, tr, order;

    level = actor->query_knight_level();
    sublevel = actor->query_knight_sublevel();
    prestige = actor->query_skill(SS_PRESTIGE_ST);
    
    switch(level)
    {
    case L_ROSE:
        order = "Order of the Rose";
        break;
    case L_SWORD:
        order = "Order of the Sword";
        break;
    case L_CROWN:
        order = "Order of the Crown";
        break;
    case L_SQUIRE:
        order = "Knighthood";
        break;
    default:
        order = "not used";
        break;
    }
    
    switch (level)
    {
    case L_ROSE:
    case L_SWORD:
    case L_CROWN:    
        if (sublevel != 1)
        {
            write("Your rank in the "+order+" is "+actor->query_knight_title()+
              ".\n");
        }
        else
        {
            write("Your rank in the "+order+" is "+actor->query_knight_title()+
              ", but you are dangerously close to becoming a Knight of "+
              "the Black Rose.\n");
        }

        if (sublevel < actor->query_level_up(prestige + 1))
            st = "deserving of a promotion";
        else if (sublevel < actor->query_level_up(prestige + 3))
            st = "as one who will soon be worthy of promotion";
        else if (sublevel > actor->query_level_up(prestige - 1))
            st = "very recently promoted, and not deserving of another promotion "+
            "in the near future";
        else if (sublevel > actor->query_level_up(prestige - 3))
            st = "recently promoted, and not yet ready for another promotion";
        else
            st = "as an established member of your current rank";

        write("You feel your deeds and actions of late have left "+
          "you " + st + ".\n");

        break;
    
    case L_SQUIRE:
    
        nr = SQUIRE_TITLES[sublevel + 1];
        pr = SQUIRE_TITLES[sublevel - 1];
        tr = SQUIRE_TITLES[sublevel];

        if (sublevel < actor->query_level_up(prestige + 1))
            st = "and you feel your promotion to " + nr + " is likely to "+
            "come very soon.";
        else if (sublevel < actor->query_level_up(prestige + 3))
            st = "and you feel that soon you will be promoted to " + nr +".";
        else if (sublevel > actor->query_level_up(prestige - 1))
            st = "but you have only recently attained this rank, and "+
            "are not even close to another promotion.";
        else if (sublevel > actor->query_level_up(prestige - 3))
            st = "but you have recently attained this rank, and are not "+
            "close to another promotion.";
        else
            st = "and while you've proven yourself as worthy of this rank, "+
            "you doubt that you will be promoted any time soon.";

        write("Your actions as a Squire have attained you the "+
          "rank of " + tr + ", "+st+"\n");
        break;
    
    case L_BROSE:
    
        if (sublevel < 1)
            write("At the moment, you are about as likely to be reinstated as "+
              "a draconian.\n");
        if (sublevel == 1)
            write("Your actions have been a disgrace to the Knighthood, and "+
              "presently they do not think highly of you at all.\n");
        if (sublevel == 2)
            write("While you are a Knight of the Black Rose, you feel that your "+
              "journey to becoming a true Knight again is nearly over.\n");
        break;
    }    
}

public void
print_consider_for_other(object actor, object target)
{
    int prestige, align;
    
    // Get the Prestige and the Alignment of the target
    prestige = actor->query_ob_prestige(target);
    align = target->query_alignment();

    // If prestige is not set, or if it's a player, we calculate
    // prestige based on their alignment.
    if (!prestige || interactive(target))
    {
        if (align < -750)
            align = -751;
        if (align > 400)
            align = 401;
    
        switch(align)
        {
        case -200..200:
            prestige = 0;
            break;
        case -400..-201:
            prestige = 100;
            break;
        case -750..-401:
            prestige = 500;
            break;
        case -751:
            prestige = 1000;
            break;
        case 201..400:
            prestige = -2;
            break;
        case 401:
            prestige = -4;
            break;
        default:
            prestige = 0;
            break;
        }
    }

    if (prestige == 0)
        actor->catch_msg("You feel that " + QTNAME(target) + " is of no concern to "+
          "the Knighthood.\n");
    else if (prestige > 1000)
        actor->catch_msg("You feel the Knighthood would be very impressed by your "+
          "defeat of " + QTNAME(target) + ".\n");
    else if (prestige > 500)
        actor->catch_msg("You feel the Knighthood would be thankful to you for "+
          "ridding the world of " + QTNAME(target) + ".\n");
    else if (prestige > 100)
        actor->catch_msg("You feel the Knighthood would approve of your actions, "+
          "were you to kill " + QTNAME(target) + ".\n");
    else if (prestige > 0)
        actor->catch_msg("You do not think the Knighthood would object to your "+
          "killing " + QTNAME(target) + ".\n");
    else  if (prestige < -4)
        actor->catch_msg("The Knighthood will not stand for your unknightly " +
          "behavior if you kill "+QTNAME(target) + "!\n");
    else  if (prestige < -2)
        actor->catch_msg("The Knighthood would be gravely disappointed in you if "+
          "you killed " + QTNAME(target) + ".\n");
    else  if (prestige < -0)
        actor->catch_msg("You believe the Knighthood would frown upon you for killing " +
          QTNAME(target) + ".\n");

}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    object target;
    
    // A Knight must consider himself daily, as part of the roleplay.
    if (actor->query_prop(KNIGHT_I_DEVOTION) < actor->query_age() + 200)
    {
        actor->add_prop(KNIGHT_I_DEVOTION, actor->query_age() + 200);
    }

    // Get the target for the ability
    if (pointerp(targets) && sizeof(targets) > 0 && objectp(targets[0]))
    {
        target = targets[0];
    }
    
    if (!objectp(target) || target == actor)
    {
        // We print out information about our own prestige
        print_consider_for_self(actor);
        return;
    }

    print_consider_for_other(actor, target);
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
}

public void
hook_special_in_cooldown()
{
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    if (!targets || !sizeof(targets))
    {
        player->catch_tell("Consider whom?\n");
        return 0;
    }

    if (sizeof(targets) > 1)
    {
        player->catch_tell("You can only consider one being at a time.\n");
        return 0;
    }
    
    if (!IS_KNIGHT(player))
    {
        // Must have the tunic of the Knighthood to perform actions.
        player->catch_tell("You cannot consider as you are not a Knight!\n");
        return 0;
    }
    
    // If it passes everything, return success
    return 1; 
}

