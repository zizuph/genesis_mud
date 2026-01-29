/* Stralle @ Genesis 010409
 *
 * Priest promotion
 *
 * Lets a cleric feel the sensation that she can become a priest.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/lib/council/std_council";

#include <language.h>
#include <files.h>
#include <const.h>
#include "../../guild.h"

mapping
query_priest_promotion_commands()
{
    return ([ "promote" : "promote_priest",
              "demote" : "demote_priest" ]);
}

int
promote_priest(string arg)
{
    object pl;
    int lev, new_lvl;
    mixed *titles;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg)
    {
        notify_fail("Promote whom");
        return 0;
    }

    arg = lower_case(arg);

    if (member_array(arg, GUILD_ADMIN->query_guild_list()) < 0)
    {
        notify_fail("There is no member named " + capitalize(arg) + ".\n");
        return 0;
    }
    
    if (!objectp(pl = find_player(arg)))
    {
        lev = GUILD_ADMIN->query_guild_level(arg);
    }
    else
    {
        lev = pl->query_skill(PS_GUILD_LEVEL);
    }

    /* We cannot promote a member with a certain skill. Try other
     * promote commands if any.
     */
    titles = GUILD_TITLES;
    if (lev >= 50 && lev < 100)
    {
        if (lev >= 90)
        {
            notify_fail(capitalize(arg) + " would need High Priest promotion.\n");
            return 0;
        }
        
        GUILD_ADMIN->set_promoted(arg, lev + 10);
        write("You promote " + capitalize(arg) + " to that of " +
            LANG_ADDART(titles[1][(pl->query_gender() == G_FEMALE ?
                1 : 0) + (((lev - 40) / 10) * 2)]) + ".\n");
                
        GUILD_ADMIN->log(this_player(), "council", capitalize(arg) +
            " promoted to " + titles[1][(pl->query_gender() == G_FEMALE ?
             1 : 0) + (((lev - 40) / 10) * 2)]);

        return 1;
    }

    if (lev >= 100)
    {
        notify_fail(capitalize(arg) + " cannot be promoted to Priest.\n");
        return 0;
    }


    GUILD_ADMIN->set_promoted(arg, 50);
    write("You promote " + capitalize(arg) + " to that of " +
        LANG_ADDART(titles[1][(pl->query_gender() == G_FEMALE ?
            1 : 0)]) + ".\n");

    GUILD_ADMIN->log(this_player(), "council", capitalize(arg) +
        " promoted to " + titles[1][(pl->query_gender() == G_FEMALE ?
            1 : 0)]);

    return 1;
}

int
demote_priest(string arg)
{
    object pl;
    int lev, new_lvl;
    mixed *titles;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg)
    {
        notify_fail("Demote whom");
        return 0;
    }

    arg = lower_case(arg);

    if (member_array(arg, GUILD_ADMIN->query_guild_list()) < 0)
    {
        notify_fail("There is no member named " + capitalize(arg) + ".\n");
        return 0;
    }
    
    if (!objectp(pl = find_player(arg)))
    {
        lev = GUILD_ADMIN->query_guild_level(arg);
    }
    else
    {
        lev = pl->query_skill(PS_GUILD_LEVEL);
    }

    /* We cannot demote a member with a certain skill. Try other
     * demote commands if any.
     */
    if (lev < 50 || lev >= 100)
    {
        notify_fail(capitalize(arg) + " is not a Priest.\n");
        return 0;
    }

    titles = GUILD_TITLES;

    if (lev >= 60)
    {
        GUILD_ADMIN->set_promoted(arg, lev - 10);
        write("You demote " + capitalize(arg) + " to that of " +
            LANG_ADDART(titles[1][(pl->query_gender() == G_FEMALE ?
                1 : 0) + (((lev - 60) / 10) * 2)]) + ".\n");
                
        GUILD_ADMIN->log(this_player(), "council", capitalize(arg) +
            " demoted to " + titles[1][(pl->query_gender() == G_FEMALE ?
             1 : 0) + (((lev - 60) / 10) * 2)]);
        return 1;
    }

    GUILD_ADMIN->set_promoted(arg, 49);
    write("You demote " + capitalize(arg) + " to that of " +
        LANG_ADDART(titles[0][4 * 2 +
        (pl->query_gender() == G_FEMALE ? 1 : 0)]) + ".\n");

    GUILD_ADMIN->log(this_player(), "council", capitalize(arg) +
        " demoted to " + titles[0][4 * 2 +
        (pl->query_gender() == G_FEMALE ? 1 : 0)]);

    return 1;
}    
