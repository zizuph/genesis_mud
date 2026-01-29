/*
 * Modified - Gwyneth (Nov 4, 2000) replaced ~elessar/lib/goodkill.h
 *            with /d/Gondor/common/lib/logkill.c
 * Modified - Tigerlily, 29 Oct 2003, set gender
 * Modified - Varian, March 2020, set_name added
 */
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "npc_ranger.c";

public void
introduce(object pl)
{
    command("say Pleased to meet you!");
    command("introduce me to " + OB_NAME(pl));
    command("say What can I do for you?");
}

public void
create_ranger() 
{
    set_living_name("isildil");
    set_name("isildil");
    add_name(({"shopkeeper", "ranger", "shopranger", "isildil"}));
    set_race_name("human");
    set_gender(G_MALE);
    set_adj(({"stocky", "dark-haired"}));
    set_title("the Shopkeeper of the Rangers of Ithilien");
    set_long("This is Isildil, the Ranger who takes care of the " +
        "Equipment store. He is probably quite competent with numbers " +
        "- trade is his speciality.\n");
    default_config_npc(64);
    set_base_stat(SS_CON, 95);
    set_base_stat(SS_STR, 95);
    set_skill(SS_WEP_SWORD, random(10) + 90);
    set_skill(SS_DEFENCE,   random(10) + 90);
    set_skill(SS_PARRY,     random(10) + 90);
    set_alignment(800 + random(200));
    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("This is the Rangers equipment store.");
    add_chat("I am Isildil, son of Anordil, Ranger of Ithilien.");
    add_chat("Have you got anything nice to sell?");
    add_chat("Perhaps you want to buy some nice equipment?");

    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");
}

public void
arm_me()
{
    FIX_EUID

    clone_object(WEP_DIR + "r_brsword")->move(TO);
    clone_object(ARM_DIR + "studlarm")->move(TO);
    clone_object(RANGERS_ITH_EMBLEM)->move(TO, 1);
    command("wield all");
    command("wear all");
}

/* solemnian prestige */
public int
query_knight_prestige()
{
    return -10;
}

