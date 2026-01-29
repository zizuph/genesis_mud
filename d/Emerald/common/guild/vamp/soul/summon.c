#include "abilities.h"
#include "../bat_manager.h"

static void summon2();

static mixed
summon(string arg)
{
    if (strlen(arg) &&
        member_array(arg, ({ "bat", "messenger", "messenger bat" })) < 0)
    {
        return CMD_SYNTAX_FAILURE;
    }

#if 0
    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("You cannot summon a creature while inside.\n");
        return CMD_FAIL_WITHOUT_COST;
    }
#endif

    if (!levels_test())
    {        
        return CMD_FAIL_WITHOUT_COST;
    }

    write("You concentrate, extending your power over the surrounding " +
        "area, attempting to gain control of a creature of darkness.\n");

    return summon2;
}

static int
summon2()
{
    if (!success_test(1, this_player(), "vsummon"))
    {
        write("No creature answers your summons.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());
    BAT_MANAGER->get_messenger(this_player());
    return 1;
}

int
stop_summon(object who)
{
    if (query_cmd_in_progress(who, "vsummon"))
    {
        who->catch_tell("Ok.\n");
        stop_vamp_cmd_execution(who);
        return 1;
    }

    notify_fail("You aren't currently trying to summon a creature, though.\n");
    return 0;
}

int
break_summon(object who)
{
    who->catch_tell("Your concentration is broken; you fail to summon " +
        "a creature.\n");
    return 1;
}
