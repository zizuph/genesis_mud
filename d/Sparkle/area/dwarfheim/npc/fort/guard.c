#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

/* wh|||!! A quest! */

void
create_monster()
{
    set_name("guard");
    set_adj("sturdy");
    add_name("dwarf");
    set_race_name("dwarf");

    set_long("The sturdy guard looks, well, rather sturdy.\n");
    set_short("honorary guard");

    set_act_time(30+random(30));
    add_act("emote stares at you, very suspiciously.");

    default_config_npc(50);

    set_skill(SS_WEP_AXE,50);
    set_skill(SS_PARRY,30);
    set_skill(SS_DEFENCE,20);
}

void
arm_me()
{
    clone_object(S_LOCAL_WEP_DIR+"axe_impressive")->move(TO);
    clone_object(S_LOCAL_ARM_DIR+"mail_iron")->move(TO);

    command("wield all");
    command("wear all");
}

