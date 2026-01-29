/*
 * /d/Gondor/guilds/rangers/soul/mentor.c
 *
 * Included in the soul. Allows for mentoring at any spot.
 *
 * Coded by Gwyneth, 8/24/03
 *
 * Modification log:
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>

public int
mentor(string str)
{
    object *oblist;
    string apprentice, mentor;

    if (!strlen(str))
    {
        notify_fail("Mentor whom?\n");
        return 0;
    }

    str = lower_case(str);
    oblist = parse_this(str, "[the] %l");

    if (!oblist || !sizeof(oblist))
    {
        notify_fail("Mentor whom? You don't see " + CAP(str) + ".\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("You can have " + APPRENTICE_MAX + " apprentices, " +
            "at a time, but mentor them one at a time.\n");
        return 0;
    }

    apprentice = capitalize(oblist[0]->query_real_name());
    mentor = capitalize(this_player()->query_real_name());
    if (!MANAGER->add_apprentice_mentor(apprentice, mentor))
    {
        notify_fail("You are unable to form a mentor-apprentice " +
            "relationship with " + apprentice + ".\n");
        return 0;
    }

    write("You vow to guide and teach " + apprentice +
        " in all the duties and knowledge that a Ranger must know.\n");
    oblist[0]->catch_tell(mentor + " vows to guide and teach you " +
        "in all the duties and knowledge that a Ranger must know.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) +
        " vows to guide and teach " + QCTNAME(oblist[0]) + " in all " +
        "the duties and knowledge that a Ranger must know.\n");
    return 1;
}

