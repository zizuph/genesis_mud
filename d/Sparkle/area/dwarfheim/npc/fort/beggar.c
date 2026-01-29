#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"

void
create_monster()
{
    set_name("beggar");
    set_adj("old");
    set_short("old beggar");
    set_long("He looks very hungry.\n");

    default_config_npc(20);
}

void
enter_inv(object a,object b)
{
    ::enter_inv(a,b);

    set_alarm(2.0, 0.0, &command("say thank you!"));
    set_alarm(6.0, 0.0, &command("eat all"));
}

