/*
 * sandknight.c
 *
 * Used in nyreese/sandcastle.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>
#include <ss_types.h>

void
create_monster()
{
    set_short("sand knight");
    set_name("knight");
    set_adj("sand");
    set_long("The knight looks as if he has hidden something in the sand.\n");
  
    default_config_npc(30);
    set_skill(SS_DEFENCE, 5);
    set_skill(SS_UNARM_COMBAT, 5);
    set_alignment(-100);
    NEVERKNOWN;
}

int query_knight_prestige(){return 20;}
