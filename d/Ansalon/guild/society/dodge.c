/*
 * /d/Ansalon/guild/kender_occ/dodge.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Dodge special - A kender can dodge hits in combat. Special
 *                 based on the dexterity and dodge skill of
 *                 the kender.
 *
 * Created: Gwyneth, July 1999
 * Modified in January 2001 by Gwyneth to be more efficient and
 * based more on how burdened one is. Added brief option.
 */

#include <stdproperties.h>
#include "guild.h"

public void stop_dodge(object who);

/* Function name : dodge_special
 * Description   : Checks to see if the kender can dodge, adds the
 *                 dodging prop, sets the dodge variable, and sets
 *                 the alarm to reset the special.
 * Returns       : 0 on failure, 1 on success
 */
public int
dodge_special(string str)
{
    object who = this_player(), tank;
    int num, duration, skill, wimpy_scale = who->query_whimpy();

    if (strlen(str))
    {
        if (lower_case(str) == "brief on")
        {
            this_player()->set_dodge_brief(1);
            write("Dodge brief:   On\n");
            return 1;
        }
        else if (lower_case(str) == "brief off")
        {
            this_player()->set_dodge_brief(0);
            write("Dodge brief:   Off\n");
            return 1;
        }
    }

    skill = who->query_skill(SS_CTACT_SPECIAL);

    if (who->query_kender_dodge())
    {
        notify_fail("You are already dodging!\n");
        return 0;
    }
    else if (who->query_prop(DODGE_RESET))
    {
        notify_fail("You aren't ready to dodge again.\n");
        return 0;
    }
    else if (!who->query_attack())
    {
        notify_fail("You aren't in combat!\n");
        return 0;
    }
    else if (skill < 1)
    {
        notify_fail("You attempt to dodge, but stumble over your own " +
            "feet in the process.\n");
        return 0;
    }
    else if (who->query_prop(SLING_PREPARE)) 
    {
        notify_fail("You are too busy preparing to sling, and " +
            "must stay still.\n");
        return 0;
    }
    else if (who->query_prop(SLING_RESET))
    {
        notify_fail("You are too tired from your last sling to " +
            "dodge properly.\n");
        return 0;
    }
    else if (wimp_check(who) < wimpy_scale)
    {
        notify_fail("You can't dodge if you're that ready to run away! " +
            "What are you, a kender, or a goblin??\n");
        return 0;
    }
    else if (who->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You can barely manage to stay alive as stunned as you are, " +
            "much less dodge!\n");
        return 0;
    }

    who->set_kender_dodge(1);

    /* Dodge lasts 30 secs max, 10 minimum - skill based, then starts reset */
    duration = min(30, max(10, skill / 3));
    set_alarm(itof(duration), 0.0, &stop_dodge(who));
    write("You stand on the balls of your feet, ready for any blows " +
        "that come your way.\n");
    return 1;
}

/* Function name : reset_dodge
 * Description   : Removes the props 
 * Arguments     : who = this_player()
 * Returns       : Null
 */
public void
reset_dodge(object who)
{
    who->remove_prop(DODGE_RESET);
    who->catch_tell("\nYou feel ready to dodge again.\n\n");
}

/* Function name : stop_dodge
 * Description   : Sets the kender's dodge variable off, and
 *                 sets an alarm for the special to reset, adds
 *                 dodge reset prop.
 * Arguments     : who = the dodger 
 */
public void
stop_dodge(object who)
{
    int mod;

    /* Remove the shadow */
    who->set_kender_dodge(0);

    /* Start the reset alarm, and add reset prop. */
    who->add_prop(DODGE_RESET, 1);
    set_alarm(8.0,0.0, &reset_dodge(who));
    who->catch_tell("You get tired from your dodging efforts, and have " + 
        "to rest a bit before you can dodge again.\n");

    return;
}
