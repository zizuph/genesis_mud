/*
 * undertaker.c
 *
 * Used in nyreese/cas_b5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
    set_name("undertaker");
    set_short("old undertaker");
    set_adj("old");
    set_long("The undertaker looks a little bored.\n");
    set_alignment(-20);
    set_living_name("undertaker");

    default_config_npc(5);
    set_base_stat(0, 80);

    set_skill(SS_WEP_POLEARM, 10);
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_PARRY, 15);

    set_random_move(5);
}

void
equip_me()
{
    clone_object(ROKEDIR + "wep/shovel")->move(this_object());

    command("wield all");
}

void
koll()
{
    object corpse;

    corpse = present("corpse", environment(this_object()));

    if (!corpse)
        return;

    command("dig");
    command("enlarge");
    command("enlarge");

    command("take corpse");
    command("put corpse in hole");
    command("fill");
}

void
enter_env(object a, object b)
{
    ::enter_env(a,b);
  
    set_alarm(1.0, 0.0, koll);
}

