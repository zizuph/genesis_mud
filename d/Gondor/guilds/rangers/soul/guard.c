/*
 * /d/Gondor/guilds/rangers/soul/guard.c
 *
 * This allows a Ranger to guard a campfire from being
 * extinguished or kicked out.
 *
 * Coded by Gwyneth (suggested by Xar), 26 May 2004
 *
 * Modification log:
 */

#include "/d/Gondor/defs.h"
#include <cmdparse.h>
#include <macros.h>

public int
fire_filter(object x)
{
    return (x->query_is_campfire());
}

public int
rguard(string str)
{
    mixed *fire;

    if (!strlen(str))
    {
        notify_fail("Guard what? A campfire?\n");
        return 0;
    }

    if (!parse_command(str, ENV(TP), "[the] %i", fire) ||
      !sizeof(fire = NORMAL_ACCESS(fire, 0, 0)))
    {
        notify_fail("Guard what?\n");
        return 0;
    }

    fire = filter(fire, fire_filter);
    if (!sizeof(fire))
    {
        notify_fail("Guard what?\n");
        return 0;
    }

    if (fire[0]->query_guarding(TP->query_real_name()))
    {
        write("You're already guarding that particular campfire.\n");
        return 1;
    }

    fire[0]->set_guarded_by(TP->query_real_name());
    write("You stand guard over the " + fire[0]->query_name() +
        " so nobody can extinguish it.\n");
    say(QCTNAME(TP) + " stands guard over the " +
        fire[0]->query_name() + ".\n");
    return 1;
}

public int
runguard(string str)
{
    mixed *fire;

    if (!strlen(str))
    {
        notify_fail("Guard what? A campfire?\n");
        return 0;
    }

    if (!parse_command(str, ENV(TP), "[the] %i", fire) ||
      !sizeof(fire = NORMAL_ACCESS(fire, 0, 0)))
    {
        notify_fail("Guard what?\n");
        return 0;
    }

    fire = filter(fire, fire_filter);
    if (!sizeof(fire))
    {
        notify_fail("Guard what?\n");
        return 0;
    }

    if (fire[0]->query_guarding(TP->query_real_name()))
    {
        fire[0]->remove_guarded_by(TP->query_real_name());
        write("You stop guarding the " + fire[0]->query_name() + ".\n");
        say(QCTNAME(TP) + " stops guarding the " +
            fire[0]->query_name() + ".\n");
        return 1;
    }

    write("You're not guarding this particular campfire.\n");
    return 1;
}
