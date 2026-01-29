#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit "/d/Earthsea/std/monster";

public void
create_traveller_monster()
{
}

public nomask void
create_earthsea_monster()
{
    object to = this_object();
    create_traveller_monster();
    clone_object(TRAVELLERS_SHADOW)->add_race_shadow(to);
    clone_object(TRAVELLERS_GUILD_EMBLEM)->move(to, 1);
}
