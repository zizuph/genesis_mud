#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include "const.h" 
#include "macros.h"

#define LEBENNIN_CORSAIR_BIT 133112

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

string give_task();
void reply_corsairs();
void reply_pelargir();
void reply_linhir();
void reply_felrek();
void reply_thurber();

void
create_monster()
{
    if (!IS_CLONE)
        return;
    
    set_name("dolmien");
    set_living_name("dolmien");
    set_race_name("human");
    set_gender(G_MALE);
    set_adj(({ "dusty", "tired" }));
    set_title("Retired guard Captain of Linhir");
    set_alignment(500);
    set_long("He has an air of sadness about him.\n");
    set_stats(({ 15, 10, 12, 14, 14, 12}));
    set_chat_time(35);
    add_chat("Those wretched corsairs have been acting up lately. Vermin!");
    add_chat("They say he was murdered on the road between Linhir "+
        "and Pelargir.");
    add_chat("There has to be someone brave enough to help us deal with the " +
        "corsair threat!");
    
    set_act_time(35);
    add_act("stretch");
    add_act("emote cleans the butcher's block with a rag.");
    add_act("emote sharpens his butcher's knife with a whetstone.");
    add_act("emote stares thoughtfully out through the window.");

    add_ask(({"task", "quest", "job", "help"}), give_task);
    add_ask(({"felrek", "murdered", "murder"}), reply_felrek);
    add_ask(({"corsair", "corsairs"}), reply_corsairs);
    add_ask(({"pelargir"}), reply_pelargir);
    add_ask(({"linhir"}), reply_linhir);
    add_ask(({"thurber", "warden"}), reply_thurber);
    equip(({AREA_DIR + "wroad/obj/dusty_cloak.c",
            AREA_DIR + "wroad/obj/butcher_knife.c"}));

    // Prevent attacking quest npc
    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
}

void 
lebennin_corsair()
{
    if (this_player()->query_prop("_lebennin_corsair_quest"))
    {
        command("say I've told you all I that I can about this.");
        command("say Please, go and talk to Thurber, the Warden of Linhir.");
        return;
    }
    command("say We live in bloody times, the wretched corsairs are roaming " +
        "the roads.");
    command("frown");
    command("say The latest news is that young Felrek, the Linhir smith " +
        "apprentice was murdered on the road from Pelargir.");
    command("say If you have the courage, seek out the Warden of Linhir, " +
        "Thurber.");
    command("say He needs assistance in dealing with the corsair threat.");
    this_player()->add_prop("_lebennin_corsair_quest",1);
    START_QUEST(this_player(), "LEBENNIN CORSAIR");
}

string
give_task()
{
    if (!this_player()->test_bit("Gondor", LEBENNIN_CORSAIR_BIT))
        lebennin_corsair();
    else
    {
        if (this_player()->test_bit(
            "Gondor, LEBENNIN_CORSAIR_BIT, LEBENNIN_CORSAIR_EVIL")
        ) {
            command("say You wretched creature, since you helped the " +
                "corsairs in their evil pursuits you are not welcome in " +
                "these lands, begone!");
        }
        if (this_player()->test_bit(
            "Gondor, LEBENNIN_CORSAIR_BIT, LEBENNIN_CORSAIR_GOOD")
        ) {
            command("say You have already helped us get rid of the wretched " +
                "corsairs.");
        }
        else
            command("say You have helped me already.");
    }
}

void
reply_corsairs()
{
    command("say The accursed corsairs of Umbar have been spotted near " +
        "Linhir lately. In league with the dark forces they prey upon the " +
        "weak of the lands. Thurber, the Warden of Linhir, is seeking brave " +
        "brave adventurers for aid in removing the corsair threat.");
}

void
reply_felrek()
{
    command("say Young Felrek was a competent apprentice for Thuoren, the " +
        "Smith of Linhir. Rumours say he was murdered by corsairs off the " +
        "road between Pelargir and Linhir. His mother is in anguish.");
}

void
reply_thurber()
{
    command("say Thurber is the Warden of Linhir. He is the administrative " +
        "head of Linhir. Lately I have heard he is seeking adventurers to " +
        "aid in dealing with a recent corsair threat.");
}

void
reply_pelargir()
{
    command("say The great harbour city of Pelargir lies west of here, at " +
        "the mouths of the Anduin.");
}

void
reply_linhir()
{
    command("say The city of Linhir lies to the west just beoynd the river " +
        "Gilraid. The people of Linhir is friendly and will accomodate your " +
        "needs for your next adventure.");
}

void
introduce(object player)
{
    command("nod slightly " + player->query_real_name());
    command("introduce myself to " + player->query_real_name());
}
