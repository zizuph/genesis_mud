/*
 * std_goblin.c
 * Goblin Warrior for mountains/goblincave
 * Tomas -- Nov. 1999
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define ARM_DIR  (MOUNTAIN_DIR + "goblincave/armour/")
#define WEP_DIR  (MOUNTAIN_DIR + "goblincave/weapon/")


private string *adj1 = ({
    "black-haired","bald","muscular", "weak",
    "thick-armed","scarred","green-haired", "silver-haired",
    "red-haired", "pock-marked", "wiry"
});
private string *adj2 = ({
    "calm", "dumb", "smug", "stupid", "agile",
    "silly","ugly", "tanned","dark-skinned",
    "light-skinned","grey-eyed"
});

public string
query_mm_in()
{
    return "scrambles in.";
}

public void
create_monster()
{
    int power = 20+random(50);

    FIX_EUID;

    add_name("_terel_cave_goblin");
    set_race_name("goblin");
    set_adj(one_of_list(adj1));
    set_adj(one_of_list(adj2));
    set_long("One of the black-feather tribe goblins.\n");

    default_config_npc(power);
    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_CLUB, power);
    set_skill(SS_WEP_POLEARM, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, power);
    set_skill(SS_AWARENESS, power);
    set_skill(SS_2H_COMBAT, power);
    set_alignment(- random(200));
    set_gender(random(2));

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(50));
    add_prop(LIVE_I_SEE_DARK, 5);

    TO->dress_me();

    set_act_time(5 + random(20));
    add_act("emote rummages around.");
    add_act("glare");
    add_act("rsay The eldar knows whats good for us.");
    add_act("emote stares at you hungrily.");
    add_act("rsay You bring food for me?");
    add_act("rsay Our guards are strong! You better leave now!");
}

void
dress_me()
{
    clone_object(ARM_DIR + "furs")->move(TO);

    switch(random(2))
    {
    case 0:
        clone_object(WEP_DIR + "bone")->move(TO);
	break;
    case 1:
        clone_object(WEP_DIR + "knife")->move(TO);
	break;
    }
    command("wield weapons");
    command("wear armours");
}
