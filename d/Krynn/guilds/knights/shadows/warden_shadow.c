inherit "/std/shadow";

#include "../guild.h"
#include <macros.h>

void
remove_position()
{
    shadow_who->remove_autoshadow(MASTER + ":");
    remove_shadow();
}

string
query_guild_title_occ()
{
    string name;

    return "Warden of the High Clerist's Tower";

    name = shadow_who->query_guild_title_occ();
    return name + " and Warden of the High Clerist's Tower";
}

string
has_position()
{
    return POSITIONS[0];
}

