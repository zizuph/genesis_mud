/* meld.c created by Shiva@Genesis.
 * This file contains the code for the "earthmeld" command.
 * This is part of the vampire guild soul.
 */

#include "../guild.h"
#include "abilities.h"
#include <macros.h>
#include <tasks.h>

public int cleanse2();

static mixed
cleanse(mixed arg)
{
    function f;
    if (arg)
    {
        return 0;
    }
  
    if (TP->query_attack())
    {
        NF("You can't manage it while in the middle of combat.\n");
        return 0;
    }

    if (!levels_test())
    {
        return CMD_FAIL_WITHOUT_COST;
    }

    write("You focus your power.\n");
    return cleanse2;
}

public int cleanse2()
{
    write("You cleanse your blood of impurities.\n");
    return 1;
}

int stop_cleanse(object who)
{
    if (query_cmd_in_progress(who, "vcleanse"))
    {
        who->catch_msg("Ok.\n");
        stop_vamp_cmd_execution(who);
        return 1;
    }

    notify_fail("You aren't cleansing, though!\n");
    return 0;
}

int break_cleanse(object who)
{
    who->catch_tell("Your concentration is broken; you cannot cleanse yourself.\n");
    return 1;
}
