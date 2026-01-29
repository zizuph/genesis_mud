#include "abilities.h"
#include <macros.h>

static int resolve_unseen();

static mixed
unseen(string arg)
{
    if (strlen(arg))
    {
        return CMD_SYNTAX_FAILURE;
    }

    if (this_player()->query_unseen_level())
    {
        write("You are already unseen.\n");
        return CMD_FAIL_WITHOUT_COST;
    }

    if (!levels_test())
    {
        return CMD_FAIL_WITHOUT_COST;
    }

    write("You concentrate, focusing on the shadows about you.\n");
    return resolve_unseen;
}

static int
resolve_unseen()
{
    /* Necessary to avoid multi-casting lockups. */
    if (this_player()->query_unseen_level())
    {
        write("You are already unseen.\n");
        return 0;
    }

    if (!success_test(1, this_player(), "vunseen"))
    {
        write("You can't manage to fade into the shadows.\n");
        return 0;
    }

    write("You attempt to fade into the darkness of the room.\n");

    this_player()->set_unseen(this_player()->query_vamp_stat() / (75 + random(26)));

    return 1;
}

int
end_unseen(object who)
{
    if (!who->query_unseen())
    {
        return 0;
    }

    who->set_unseen(0);
    who->catch_tell("You emerge from your shroud of darkness.\n");
    tell_room(environment(who), QCTNAME(who) + " emerges from the " +
        "shadows.\n", who);
    return 1;
}

int
stop_unseen(object who)
{
    if (query_cmd_in_progress(who, "vunseen"))
    {
        who->catch_tell("Ok.\n");
        stop_vamp_cmd_execution(who);
        return 1;
    }
    else if (!end_unseen(who))
    {
        notify_fail("You aren't unseen, though!\n");
        return 0;
    }

    who->catch_tell("Ok.\n");
    return 1;
}

int
break_unseen(object who)
{
    who->catch_tell("Your concentration is broken; you cannot become " +
        "unseen.\n");
    return 1;
}
