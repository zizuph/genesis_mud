
#include "../guild.h"

inherit "/std/object";
inherit "/lib/skill_raise.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <macros.h>

public void create_object()
{
    set_name("_train_obj");
    add_prop(OBJ_I_NO_GET,1);
    set_no_show();
}


/*
 * Function name: sk_hook_not_allow_train
 * Description:   Message to print if you are not allowed to train
 * Returns:       string -- fail message
 */
public int
sk_hook_not_allow_train()
{
    return 0;
}


public void init()
{
    ::init();
    init_skill_raise();
}

void
sk_hook_write_header(int steps)
{
    if (!steps)
    {
        steps = 1;
    }
    write("With sufficient favor, you may "+ query_verb() + " " +
        LANG_WNUM(steps) + ((steps == 1) ? " step" : " steps") + " here.\n");
    write("  Skill:                Cost:      "+
        "Next level:           Max level:\n"+
        "--------------------------------------"+
        "--------------------------------------\n");
}

/*
 * Function name: sk_hook_skillisting
 * Description  : Display the header when someone is listing the skills
 *                to see which training he can receive.
 */
void
sk_hook_skillisting()
{
    write("With sufficient favor, you may train these skills here:\n");
    write("  Skill:                Cost:      "+
          "Next level:          Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
}

/*
 * Function name: sk_hook_not_allow_train_skill
 * Description:   Message to print if you are not allowed to train
 *                a particular skill
 * Arguments:     skill  -- the skill we can't train (optional)
 * Returns:       string -- fail message
 */
public varargs int
sk_hook_not_allow_train_skill(string skill)
{
    write("You pray for the blessing to learn " + skill +
    " but are met with silence. You feel that if you were more "+
    "in favor with the Eldest you may train further.\n");
    
    return 1;
}

/*
 * Function name: sk_hook_raise_rank
 * Description  : The player trains and pays, write something.
 * Arguments    : int snum  - the number of the skill trained.
 *                int to_lev - the level reached.
 *                int cost - the price paid, in coppers.
 */
void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank;

    rank = sk_rank(to_lev);

    this_player()->catch_msg("You are granted the ability to " +
        sk_tdesc[snum][0] + " at the rank of " + rank + ".\n");
    say(QCTNAME(this_player()) + " are granted " +
        this_player()->query_possessive() + " ability to " +
        sk_tdesc[snum][1] + " and at the level of " + rank +
        ".\n");
}


/*
 * Function name: sk_hook_allow_train_skill
 * Description:   Checks to see if a specific person can learn a
 *                a specific skill ( to a specific level ).
 *                ( Default is:  yes )
 * Arguments:     object - The player trying to improve/learn
 *                skill  - The skill trying to train
 *                level  - The level trying to learn to
 * Returns:       1 - yes (default) / 0 - no
 */
public varargs int
sk_hook_allow_train_skill(object who, string skill, int level)
{
    int free=(who->query_bloodguard() ? 180 : 370 + 100 + 180);
    
    int snum = sk_find_skill(skill);
    
    if (snum < 0)
    {
        return 0;
    }

    if (level<=who->query_base_skill(snum))
    {
        return 1;
    }
    
    int total=0;
    
    foreach (int key : m_indexes(sk_trains))
    {
        if (key==snum)
        {
            continue;
        }
        total+=min(who->query_base_skill(key),sk_trains[key][2]);
    }
    total+=min(level,sk_trains[snum][2]);
    
    total-=free;
    if (total>who->query_skill(VAMP_FAVOR)*5)
    {
        return 0;
    }
        
    return 1;
}
