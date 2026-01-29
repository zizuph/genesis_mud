#include "../guild.h"

public varargs void
ktconvey(string colour, object *kot)
{
    if (!kot)
    {
        kot = filter(users(), &->query_kot_member());
    }

    if (!sizeof(kot))
    {
        return;
    }

    map(kot, &call_other(GUILD_SOUL_CLERIC, 
        "convey_message", "red", , this_object()));
}
