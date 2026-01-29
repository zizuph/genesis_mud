/* Stralle @ Genesis 010409
 *
 * Honourifics
 *
 * Assigns some title to a DA (or other) who has especially 
 * aided the priesthood. Number of days it should prolong.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include "../../guild.h"

mapping
query_honourifics_commands()
{
    return ([ "honour" : "do_honour" ]);
}

int
do_honour(string arg)
{
    int days;
    string who, title;
    object pl, ob;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        "%w [with] [bestowing] [the] [title] %s 'for' %d [days]", who, title,
        days))
    {
        notify_fail("Honour whom with what title for how many days?\n");
        return 0;
    }

    who = lower_case(who);
    
    if (!(pl = find_player(who)))
    {
        notify_fail("There is no one known by " + capitalize(who) +
            " in the realms.\n");
        return 0;
    }
    
    if (present("_pot_honour_ob", pl))
    {
        notify_fail("But " + capitalize(who) + " already has been " +
            "bestowed that honour.\n");
        return 0;
    }

    if (pl->query_guild_name_occ() == GUILD_NAME)
    {
        notify_fail("Priests bears titles not for honour.\n");
        return 0;
    }

    if (days < 1 || days > 14)
    {
        notify_fail("A more saner number of days would be a maximum of " +
            "two weeks.\n");
        return 0;
    }
    
    if (strlen(title) > 50 || sizeof(explode(title, " ")) > 5)
    {
        notify_fail("Being called that would have " + capitalize(who) +
            " fall on " + pl->query_possessive() + " tongue when " +
            "called for an introduction.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    ob = clone_object(GUILDDIR + "obj/honour_ob");
    ob->set_time(days);
    ob->set_title(title);
    if (ob->move(pl))
        ob->move(pl, 1);
    
    GUILD_ADMIN->log(this_player(), "council", "Honours " +
        pl->query_name() + " with the title: \"" + title + "\" for " +
        days + " days");

    write("You let it be known that " + capitalize(who) + " will also " +
        "be known as " + title + ".\n");
    return 1;
}
