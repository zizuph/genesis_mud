/*
 *  Palmer 13 Aug 2006
 *  Base Black Numenorean npc
 */

#pragma strict_types

inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

static void    get_money();

public void
create_monster()
{
    set_name("black numenorean");
    add_name(({"traveller", "man", "adventurer"}));
    set_adj("Black");
    add_adj("Numenorean");
    set_race_name("human");
    set_long(BSN("This formidable Black Numenorean seems to be surverying the "
      + "area. He looks like a seafarer and "
      + "appears to be quite capable of defending himself should the need arise."));

    default_config_npc(80 +random(5));

    set_base_stat(SS_STR, 90 +random(5));
    set_base_stat(SS_CON, 90 +random(5));

    set_skill(SS_WEP_SWORD, 80 +random(5));
    set_skill(SS_DEFENSE, 80 +random(5));
    set_skill(SS_PARRY, 80 +random(5));
    set_skill(SS_AWARENESS, 75 +random(5));
    set_skill(SS_BLIND_COMBAT, 75 +random(5));

    set_alignment(-700);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 180 +random(30));
    add_prop(CONT_I_WEIGHT, 85000 +random(30*500));
    add_prop(CONT_I_VOLUME, 80000 +random(30 * 500));

    set_chat_time(4 +random(3));
    add_chat("Umbar is quite a lovely sea port.");
    add_chat("There is nothing like sailing on the open sea.");

    set_cchat_time(2);
    add_cchat("So be it! Death to you!");
    add_cchat("Is that all you've got?!");

    set_act_time(4 +random(3));
    add_act("yawn");
    add_act("get all from corpse");
    add_act("get all");
    add_act("snicker");
    add_act("time");

    set_cact_time(3);
    add_cact("growl @@query_enemy_name@@");
    add_cact("glare @@query_enemy_name@@");
    add_cact("scowl @@query_enemy_name@@");
    add_cact("explode @@query_enemy_name@@");
}

public void
arm_me()
{
    seteuid(getuid());

    clone_object(POROS_DIR + "weapons/broadsword")->move(this_object());
    command("wield all");

    clone_object(POROS_DIR + "armours/chainmail")->move(this_object());
    command("wear all");

    get_money();
}

static void
get_money()
{
    MONEY_MAKE_SC(20 + random(10))->move(TO);
    MONEY_MAKE_GC(3 +random(3))->move(TO);
}

int
query_knight_prestige() {return 700;}

public string
query_enemy_name()
{
    object  enemy = query_attack();

    if (objectp(enemy))
        return enemy->query_real_name();

    return "";
}

