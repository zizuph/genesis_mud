#include "defs.h"

public int
_cmd_revolt()
{
    object tp = this_player();

    if(!IS_MEMBER(tp))
    {
        return notify_fail("Only Gladiators may stage a revolt!\n");
    }

    if(!MANAGER->query_overseer_by_position(POS_HIGH))
    {
        return notify_fail("But there is no High Overseer to revolt against!\n");
    }

    string name = tp->query_real_name();

    if(MANAGER->query_revolter(name))
    {
        return notify_fail("You are already revolting as it is!\n");
    }

    MANAGER->add_revolter(name);
    write("POWER TO THE GLADIATORS!\n\n"+
        "You are now revolting.\n"+
        "You may 'regret' this action later.\n");
    say(QCTNAME(TP) + " joins the revolution against the Overseers!\n");

    if(sizeof(MANAGER->query_revolters()) >= REVOLT_LIMIT)
    {
        tell_room(TO, "THE OVERSEERS HAVE BEEN OVERTHROWN!\n");
        MANAGER->overthrow_overseers();
    }

    return 1;
}
