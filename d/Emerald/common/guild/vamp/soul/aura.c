#include "../guild.h";
#include "abilities.h"

static int aura2();

static mixed
aura(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    if (this_player()->query_obscured())
    {
        write("You are already obscured by a dark aura.\n");
        return CMD_FAIL_WITHOUT_COST;
    }

    if (!levels_test())
    {
        return CMD_FAIL_WITHOUT_COST;
    }

    write("You concentrate, attempting to channel your power into a dark " +
        "aura.\n");

    return aura2;
}

static int
aura2()
{
    int suc;

    if (!(suc = success_test(1,  this_player(), "vaura")))
    {
        write("You are unable to create a visible aura.\n");
        return 0;
    }

    write("From the depths of your soul, you summon a dark aura "+
        "around yourself.\n");
    allbb(" summons a dark aura around " + OBJ(this_player()) + "self.");

    this_player()->set_obscured(suc * 3);
    this_player()->modify_thirst_rate(-300);
    return 1;
}

void
remove_aura(object who)
{
    who->set_obscured(0);
    who->modify_thirst_rate(300);
    set_this_player(who);
    write("Your aura flickers and fades away.\n");
    allbb("'s dark aura flickers and fades away.");
}

int
stop_aura(object who)
{
    if (query_cmd_in_progress(who, "vaura"))
    {
        who->catch_msg("Ok.\n");
        stop_vamp_cmd_execution(who);
        return 1;
    }

    if (who->query_obscured())
    {
        remove_aura(who);
        return 1;
    }
        
    notify_fail("You aren't trying to create an aura, though!\n");
    return 0;
}

int
break_aura(object who)
{
    who->catch_tell("Your concentration is broken; you cannot create " +
       "an aura.\n");
    return 1;
}
