#pragma strict_types

#include "defs.h"

inherit "/std/object";

string *quests = ({LIVE_I_HORN_QUEST,
                   LIVE_I_SEER_QUEST,
                   LIVE_I_SWORD_QUEST,
                   LIVE_I_BEAST_QUEST});
int *vals;

public void
create_object()
{
    set_name(QUEST_TRACKER_NAME);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
    vals = allocate(sizeof(quests));
}

public string
query_auto_load()
{
    int i,
        val;
    string arg;
    object ob;

    if (!living(ob = environment(TO)))
        return MASTER;

    arg = ":";

    for (i = 0; i < sizeof(quests); i++)
    {
        vals[i] = ob->query_prop(quests[i]);
        arg += vals[i] + "&";        
    }

    if (strlen(arg) < 2)
        return MASTER;
    else
        return MASTER + arg;
}

public void
setup_quests(string arg)
{
    object ob;
    int i;

    if (!strlen(arg) || strlen(arg) < 2)
    {
        return;
    }
    if (!environment() || !living(ob = environment()))
    {
        return;
    }

    else
    {
        sscanf(arg,"%d&%d&%d&%d&", vals[0], vals[1], vals[2], vals[3]);
    }

    for (i = 0; i < 4; i++)
    {
        if (vals[i])
            ob->add_prop(quests[i], vals[i]);
    }
    remove_object();
}        

public void
init_arg(string arg)
{
    set_alarm(1.0, 0.0, &setup_quests(arg));
}
