/*
 * Knight Training Room Base
 *
 * This room handles many of the common functions among the various
 * training rooms that the Knights have. The Knights have a total
 * of 6 training rooms:
 *   east_train2, train1, train2, west_train1, inner_court, library
 *
 * Created by Petros, November 2008
 */

#include "../../../guild.h"
#include <macros.h>
#include <ss_types.h>

inherit "/lib/skill_raise";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public object       gTrainer;
public int          levlim;

public object
query_guild_trainer()
{
    return gTrainer;
}

public void
set_guild_trainer(object trainer)
{
    gTrainer = trainer;
}

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    if (!who->query_knight_level())
    {
        who->catch_msg("You are no member of this guild, you cannot train "
          + "here. Only Knights of Solamnia can improve their skills "
          + "here.\n");
        return 0;
    }

    if (!objectp(query_guild_trainer())
        || !present(query_guild_trainer(), environment(this_player())))
    {
        who->catch_msg("The trainer isn't here to train you.\n");
        return 0;
    }

    if (REALAGE(who) < who->query_skill(SS_DISGRACED))
    {
        who->catch_msg("You are currently banned from training!\n");
        return 0;
    }

    who->remove_skill(SS_DISGRACED);
    return 1;
}

int
sk_query_max(int snum)
{
    int klev, mxtrain, traineable_max;
    mixed skval;
    object pl;

    levlim = 0;
    if (!IN_ARRAY(snum, sk_query_train()))
    {
	    return 0;
	}

    skval = sk_trains[snum];
    traineable_max = skval[2];        
    mxtrain = SKILLS_MANAGER->query_skill_max(this_player(), snum);
        
    if (mxtrain < traineable_max)
    {
        levlim = 1;
    }
    
    return min(mxtrain, traineable_max);
}

int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have to\n" +
                "seek knowledge elsewhere.\n");

    if (levlim)
    {
        notify_fail("Sorry but your order doesn't allow you to train to "
            + "further in this skill.\n");
    }
    return 0;
}
