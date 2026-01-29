#include "../master_defs.h"

void return_introduce(string who)
{
    object obj;

    if (obj = present(who, environment()) && !obj->query_npc())
        command("introduce me to "+who);
}

void add_introduced(string who)
{
    if (find_living(who)->query_met(TO))
        return;

    set_alarm(2.0, -2.0, "return_introduce", who);
}
