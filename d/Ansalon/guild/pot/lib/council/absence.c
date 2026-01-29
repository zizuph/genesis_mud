/* Stralle @ Genesis 010409
 *
 * Absence
 *
 * Prolongs the time a council member can be absent. Should contain
 * weeks and a reason which is logged and readable by the other
 * members of the council.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include "/d/Ansalon/guild/pot/guild.h"
#include <language.h>

mapping
query_absence_commands()
{
    return ([ "absent" : "do_absent" ]);
}

int
do_absent(string arg)
{
    int weeks, cur_weeks;
    string reason;
    
    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        "[for] %d [weeks] [due] [to] %s", weeks, reason))
    {
        notify_fail("Absent for how many weeks due to what reason?\n");
        return 0;
    }

    if (weeks < 0 || weeks >= 8)
    {
        notify_fail("Weeks should be a maximum of eight.\n");
        return 0;
    }
    
    if (strlen(reason) > 60)
    {
        notify_fail("Please keep the reason to a maximum of sixty " +
            "characters.\n");
        return 0;
    }

    if ((cur_weeks =
        GUILD_ADMIN->query_council_absent(this_player()->query_real_name()) /
        (86400 * 7)))
    {
        if (cur_weeks + weeks <= 8)
        {
            write("You have already let it known that you are going to " +
                "be absent for " + LANG_WNUM(cur_weeks) + " weeks and now " +
                "make it known that period will be extended for another " +
                LANG_WNUM(weeks) + " weeks.\n");
            weeks += cur_weeks;
        }
        else
        {
            write("You have already let it known that you are going to " +
                "be absent for " + LANG_WNUM(cur_weeks) + ". Extending " +
                "that period by another " + LANG_WNUM(weeks) + " would " +
                "make more than eight weeks.\n");
            return 1;
        }
    }
    else
    {
        write("You let it be known that you are going to be absent " +
            "for " + LANG_WNUM(weeks) + " weeks.\n");
    }

    GUILD_ADMIN->set_council_absent(this_player()->query_real_name(),
        time() + weeks * 86400 * 7);
    GUILD_ADMIN->log(this_player(), "council", "Will be absent for " +
        LANG_WNUM(weeks) + " weeks");

    return 1;
}
