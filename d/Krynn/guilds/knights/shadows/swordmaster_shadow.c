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
    string name, test;

    return "Swordmaster of Solamnia";

    name = shadow_who->query_guild_title_occ();
    if (extract(name, -11) == "of Solamnia")
	name = extract(name, 0, -13);

    return name + " and Swordmaster of Solamnia";
}

string
has_position()
{
    return POSITIONS[1];
}
