/* Stralle @ Genesis 010409
 *
 * Cleric promotion
 *
 * Promotes a Cleric to the next sublevel save the step to become a
 * full priest.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include <language.h>
#include <files.h>
#include <const.h>
#include "../../guild.h"

mapping
query_cleric_promotion_commands()
{
    return ([ "promote" : "promote_cleric",
              "demote" : "demote_cleric" ]);
}

int
promote_cleric(string arg)
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
    if (lev >= 40)
    {
        notify_fail(capitalize(arg) + " cannot be promoted to Priest.\n");
        return 0;
    }

    titles = GUILD_TITLES;

    new_lvl = lev / 10;
    GUILD_ADMIN->set_promoted(arg, (new_lvl + 1) * 10);
    write("You promote " + capitalize(arg) + " to that of " +
        LANG_ADDART(titles[0][2 * (new_lvl + 1) +
        (pl->query_gender() == G_FEMALE ? 1 : 0)]) + ".\n");

    GUILD_ADMIN->log(this_player(), "council", capitalize(arg) +
        " promoted to " + titles[0][2 * (new_lvl + 1) +
        (pl->query_gender() == G_FEMALE ? 1 : 0)]);

    return 1;
}

int
demote_cleric(string arg)
{
    object pl;
    int lev, new_lvl;
    mixed titles;

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
    if (lev >= 50)
    {
        notify_fail(capitalize(arg) + " cannot be demoted from Priest.\n");
        return 0;
    }

    titles = GUILD_TITLES;

    new_lvl = lev / 10;
    if ((new_lvl - 1) < 0)
    {
        notify_fail("You cannot demote " + capitalize(arg) + " more than " +
            "to that of " + LANG_ADDART(titles[0][0 +
            (pl->query_gender() == G_FEMALE ? 1 : 0)]) + ".\n");

        return 0;
    }

    GUILD_ADMIN->set_promoted(arg, (new_lvl - 1) * 10 + 9);
    write("You demote " + capitalize(arg) + " to that of " +
        LANG_ADDART(titles[0][2 * (new_lvl - 1) +
        (pl->query_gender() == G_FEMALE ? 1 : 0)]) + ".\n");

    GUILD_ADMIN->log(this_player(), "council", capitalize(arg) +
        " demoted to " + titles[0][2 * (new_lvl - 1) +
        (pl->query_gender() == G_FEMALE ? 1 : 0)]);

    return 1;
}    
