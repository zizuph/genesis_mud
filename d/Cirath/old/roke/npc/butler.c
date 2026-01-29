/*
 * butler.c
 *
 * Used in nyreese/cas_c6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>

void
create_monster()
{
    default_config_npc(25);
    set_skill(SS_DEFENCE, 25);
    set_skill(SS_UNARM_COMBAT, 25);
    set_alignment(20);

    set_name("butler");
    set_short("spooky butler");
    set_adj("spooky");
    add_name("human");

    set_long("The spooky butler is the servant of the wizard Refnas.\n" +
             "He is taking care of his master's leech farm.\n");

    add_act("close door");
    add_act("say Please do not disturb my master.\n");
    add_act("close door");
    add_act("say He is very busy, minding his own matters.\n");
    add_act("close door");
    add_act("say I advise you to do the same, heretic!!\n");
    add_act("close door");
    add_act("say Watch your steps!!! Don't step on the leeches!!\n");
}

int
query_knight_prestige()
{
    return -1;
}
