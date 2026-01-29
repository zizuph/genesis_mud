/*
 * campguard.c
 *
 * Used in wild/fb.c wild/fc.c wild/fd.c wild/ff.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
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
    set_race_name("guard");
    set_name("guard");
    set_adj("dirty");
    set_alignment(0);
    default_config_npc(35);

    set_short("dirty guard");
    set_long("This is a dirty guard guarding the camp of the warriors from " +
             "the evil island Nor-at-Hur.\n");

    NEVERKNOWN;

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_POLEARM, 60);
}

int
query_knight_prestige()
{
    return 400;
}

void
equip_me()
{
    clone_object(ROKEDIR + "wep/halberd")->move(TO);
    clone_object(ROKEDIR + "arm/coat")->move(TO);

    command("wear all");
    command("wield all");
}
