/* 
 * /d/Kalad/common/noble/npc/alexander.c
 * Purpose    : Head of the house of Alexander, he rewards the noble key quest
 * Located    : /d/Kalad/common/noble/alexander/
 * Created By : Sarr ??.??.96
 * Modified By: Fysix, 02-98, recoded
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "default.h"

#define QUEST "noble_keyquest"

void
create_kalad_monster()
{
    set_name("Lord Alexander");
    add_name("alexander");
    add_name("lord");
    set_adj("lord");
    add_adj("blond-haired");
    add_adj("blue-eyed");
    add_name("noble");
    set_race_name("human");
    set_short("blond-haired blue-eyed noble");
    set_long("You look at well-built, strong male human. His blond "+
        "hair flows down to his shoulders, and is only slightly streaked "+
        "with grey. His piercing blue eyes regard you sternly. He is well "+
        "dressed, and looks very commanding.\n");

    set_alignment(-400);
    set_knight_prestige(100);

    set_stats(({90,70,80,80,80,70}));

    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_PARRY, 80);
    set_skill(SS_DEFENSE,80);
    set_skill(SS_WEP_KNIFE,90);

    set_act_time(3);
    add_act("say Hail, what can I do for you?");
    add_act("emote studies his ring.");
    add_act("yawn");
    add_act("think");
    add_act("say What can I do for you?");
    add_act("emote ponders the state of things in the district.");

    set_title("the Count of Blaklose");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_equipment(({
        NOBLE + "arm/silk_tunic",
        NOBLE + "arm/e_leather_pants",
        NOBLE + "arm/ring",
        NOBLE + "arm/ring",
        CVAN + "thanar/symbol",
        NOBLE + "arm/leather_shoes",
        NOBLE + "wep/jeweled_dagger",
        }));
}

void
enter_inv(object ob, object from)
{
    if (MASTER_OB(ob) == (NOBLE + "obj/quest_map"))
    {
        if (TP->query_prop("_kalad_permission_arrest"))
            set_alarm(3.0, 0.0, "reward_map", TP, ob);
        else
            command("drop " + ob->query_name());
    }      
    ::enter_inv(ob, from);
}

void
reward_map(object ob, object key)
{
    if (ob->query_guild_name_race() == "Thanarian human race guild")
    {
        if (ob->test_bit("Kalad", 1, 14))
            command("say Thanks again brother!");
        else
        {
            command("say Hail Thanar! You have done a great service in "+
            "the name of the Almighty one! May you be blessed.");
            command("emote blesses you.");
            command("say He now looks favorable upon you.");
            ob->set_bit(1, 14);
            ob->add_exp(5000);
            tell_object(ob, "You feel more experienced.\n");
            tell_object(ob, "Thanar comes down beofre you and bestows "+
                "the title of Savior of Thanar upon you.\n");
            ob->add_prop("THANAR_SPECIAL_TITLE", 1);
            command("say Hail the allmighty one!");
            log_file(QUEST, extract(ctime(time()), 4, 15) + " " +
               capitalize(ob->query_real_name()) +
               " rewarded with 5000 xp by thanar," +
               "<" + ob->query_average_stat() + "> average stats.\n");
        }
        key->remove_object();
        return;
    }
    if (ob->query_race_name() == "human")
    {
        if(ob->test_bit("Kalad", 1, 14))
            command("say Thank you once again.");
        else
        {
            command("say Thank you, my friend. You have done a great "+
            "service for our God, Thanar.");
            command("say He is going to look favorable upon you, "+
            "perhaps, you should consider joining our cause?");
            command("smile");
            ob->set_bit(1, 14);
            ob->add_exp(5000);
            tell_object(ob, "You feel more experienced.\n");
            command("thank " + lower_case(ob->query_name()));
        }
        key->remove_object();
        return;
    }
    command("smile");
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command("shout Help! Guards!");
    call_other(NOBLE + "alexander/m17", "emergency", ob);
}
