#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include "default.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>

#define WEAPON "/d/Earthsea/gont/beach/weapons/knife"
#define SHIRT "/d/Earthsea/gont/beach/armours/shirt"
#define PANTS "/d/Earthsea/gont/beach/armours/pants"

public void
create_earthsea_monster()
{
    set_name("shopkeeper");
    set_adj("grizzled");
    add_adj("old");
    set_race_name("human");
    set_gender(G_MALE);
    set_short("grizzled old human");
    set_long("A grizzled old man. He keeps a shop near the beach for " +
             "fishermen, but he would welcome any kind of business.\n");

    set_stats(({25, 20, 25, 45, 55, 15}));
    set_all_hitloc_unarmed(50);

    set_skill(SS_DEFENSE, 70);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_KNIFE, 75);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 50);

    set_act_time(50);
    add_act("emote coughs loudly.");
    add_act("say See anything you like around here?");
    add_act("say I give people the best deals around here.");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

public void
arm_me()
{
    object weapon, shirt, pants, to = this_object();

    weapon = clone_object(WEAPON);
    weapon->move(to);

    shirt = clone_object(SHIRT);
    shirt->move(to);

    pants = clone_object(PANTS);
    pants->move(to);

    command("wield knife");
    command("wear all");

    MONEY_MAKE_SC((random(10) + 1))->move(to);
}

public int
query_knight_prestige()
{
    return -30;
}
