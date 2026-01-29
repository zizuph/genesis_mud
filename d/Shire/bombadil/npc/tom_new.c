/*
 *  Tom Bombadil, the happy fellow
 *  Recoded by Finwe, January 2002
 */
#include "/d/Shire/sys/defs.h"

inherit "/std/monster";
inherit "/lib/unique";
inherit KILL_LOGGER;

#include "../local.h"
#include "/d/Shire/private/shire_admin.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/common/monster/tobacco.h"
#include <tasks.h>

#define LILIES_QUEST_NAME   "lilies"
#define FEATHER_QUEST_NAME  "new_feather"
#define HP_HEAL_THRESHOLD   2500

string my_long();
void add_stuff();
string ask_quest();
void check_health();
int drink_withy_water();
void spawn_withy_water();

void create_monster()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("tom");
    add_name(({"bombadil"}));
    set_living_name("tom");
    set_title("Bombadil");
    set_race_name("man");
    set_adj(({"short","happy"}));
    set_long(&my_long ());

    add_prop(CONT_I_WEIGHT,67000);   /*  67 Kg */
    add_prop(CONT_I_HEIGHT,169);     /* 169 cm */
    add_prop(LIVE_I_ALWAYSKNOWN,1);  /* Always known by people */
    add_prop(LIVE_I_QUICKNESS, 150); /* speed up attacks */
    add_prop(LIVE_I_SEE_DARK, 90);   /* Night vision. */

    /* STR DEX CON INT WIS DIS */
    set_stats(({ 190+random(25),
                 210+random(25),
                 190+random(25),
                 200+random(25),
                 170+random(25),
                 150+random(25)} ));

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_ACROBAT, 100);

    clone_tobacco();
    set_aggressive(0);
    set_attack_chance(0);
    set_alignment(900);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(5);
    set_act_time(5);
    add_chat("Hey merry dol! Derry dol!");
    add_chat("Lighten up, my friend!");
    add_chat("Hey dol! merry dol! ring a dong dillo!");
    add_chat("Don't fear Old Man Willow, he means you no harm!");
    add_chat("Hey diddle-dillo, I'm Tom Bombadillo!");
    add_act("emote dances around merrily.");
    add_act("emote starts sing about the birds in the trees and " +
        "the clouds in the sky.");
    add_act("emote sings about something cheerful.");
    add_act("emote smiles happily and dances around with you.");
    add_act("emote sings about the lovely Goldberry.");
    add_act("emote smiles cheerfully.");

    set_cchat_time(5);
    add_cchat("It is not wise to fight me.");
    add_cchat("Did I do anything wrong?");
    add_cchat("Was it something I said?");
    add_stuff();

    add_prop("_live_m_no_drain", 1);
    add_prop("_ranger_i_not_disarm", 1);

    TELL_ADMIN("Tom Bombadill was cloned at " + ctime(time()));

    // log killers
    set_kill_log_name("bombadil");
   	set_kill_log_size(50000);

    // quest
    add_ask(({"quest","help", "quests"}), VBFC_ME("ask_quest"));
    add_ask(({"lilies","lily", "new lily"}), VBFC_ME("ask_lilies"));
    add_ask(({"feather", "new feather"}), VBFC_ME("ask_feather"));
}

string
my_long()
{
    if (notmet_me(this_player())) {
        this_player()->add_introduced("tom");
    }

    return "This is Tom Bombadil. He is a merry fellow with a " +
        "cheerful disposition. He's not quite as tall as human, " +
        "but is not a hobbit. He has bright blue eyes and a long " +
        "beard. His face is as red as a ripe apple and creased " +
        "with hundreds of laugh lines with a long brown beard. " +
        "This happy-go-lucky man can often be found wandering " +
        "around the forest, dancing and singing. Nonetheless, do " +
        "not underestimate him, for he is strong in his own right.\n";
}

void
add_stuff()
{
    object sword, water;
    object hat, boots, shirt, pants;

    FIXEUID;

    sword = clone_unique(
        WEP_DIR+"shortsword_new",
        MAX_UNIQUE_ITEMS,
        "/d/Shire/downs/wep/w_sword"
    );
    sword->move(this_object());

    hat = clone_object(ARM_DIR + "hat");
    hat->move(this_object());

    boots = clone_object(ARM_DIR + "boots");
    boots->move(this_object());

    pants = clone_object(ARM_DIR + "pants");
    pants->move(this_object());

    shirt = clone_object(ARM_DIR + "shirt");
    shirt->move(this_object());

    command("wear armours");
    command("wield sword");

    spawn_withy_water();
}

int
drink_withy_water()
{
    if (!present("_withy_water_", TO))
    {
        spawn_withy_water();

        TP->heal_hp(500);

        say("Tom looks refreshed.\n");

        return 0;
    }

    command("drink liquid");

    return 1;
}

void
spawn_withy_water()
{
    object water = clone_object(OBJ_DIR + "tomdrink");
    water->move(this_object());
}

void
check_health()
{
    /* changed threshold from 500 to 2500 */
    if (query_hp() <= (query_max_hp() - HP_HEAL_THRESHOLD))
    {
        command("emote says something in a sing-song language and dances " +
            "around with a quicker step in his stride.\n");
        heal_hp(1000 + random(1500));
    }
}

void
heal_hp(int dam)
{
    if (dam < 0) {
	   ::heal_hp(dam / 2);
    } else {
	   ::heal_hp(dam * 2);
    }
}

public void
give_back(object from, object obj)
{
    command("say This is nice, but I don't need it.");

    write("Tom gives it back to you.\n");

    obj->move(from);

    return;
}

void
attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("Tom Bombadil was attacked by " + ob->query_cap_name() +
        "("+ob->query_average_stat()+") at " + ctime(time()));
}

int
special_attack(object ob)
{
    switch(random(2))
    {
        case 0:
            check_health();
            return 1;
        case 1:
            if (random(9))
            {
                return 0;
            }

            drink_withy_water();
            return 1;
        default:
            return 0;
    }
}

/****************************************************************
 * Quests                                                       *
 ***************************************************************/
string
ask_quest()
{
    // asks for 'quest'
    command("think");

    if ((!CHECK_QUEST(TP, LILIES_QUEST_NAME))
        && (!CHECK_QUEST(TP, FEATHER_QUEST_NAME)))
    {
        command("say Thank you for asking. I need help getting " +
            "a new lily for Goldberry, ");
        command("say and I need a new feather for my hat.");
	    return "";
    }

    if (!CHECK_QUEST(TP, LILIES_QUEST_NAME))
    {
        command("say Hiho, I need a lily for my Goldberry!");
        return "";
    }

    if (!CHECK_QUEST(TP, FEATHER_QUEST_NAME))
    {
        command("say Hiho, I need a new feather for my hat!");
        return "";
    }

    command("say Hiho, merry dol! But you have helped me already.");
    return "";
}

/*
 * Gives out lily quest
 */
string
ask_lilies()
{
    // player asks for quest again while doing it
    if (TP->query_prop(QUEST_LILY_PROP))
    {
        command("say Hey there. Merry Dol! Having a hard time finding " +
            "lilies?");
        command("emote dances around merrily.");
        command("say I think you can find lilies for my fair " +
            "Goldberry if you ");
        command("say try hard enough.");
        command("emote sings a merry tune.");
        return "";
    }

    // asks for quest again after completing it
    if (CHECK_QUEST(TP, LILIES_QUEST_NAME))
    {
        command("say Hiho, merry dol! But you have helped me already.");
        command("say Goldberry and I thank you for your help!");
        return "";
    }

    // gives out quest
    command("say Goldberry loves her lilies.");
    command("say They are as fair as she.");
    command("say Please help me and find some.");
    command("say She'll be as grateful as can be.");
    command("smile hopefully");

    // adds prop to player
    TP->add_prop(QUEST_LILY_PROP,1);

    return "";
}

void
test_lily(object player, object obj)
{
    // Is doing the quest ?
    if (player->query_prop(QUEST_LILY_PROP))
    {
        // Did this before ?
        if (!REWARD_QUEST(player, LILIES_QUEST_NAME))
        {
            command("say Thank you for the lily, but you have " +
                "helped me before.");
            return;
        }

        command("emote dances around gleefully.");
        command("say Oh, thank you, thank you, the lilies are " +
            "just beautiful!");
        command("say My Goldberry, she is gone right now.");
        command("say But I know her face will light up when I " +
            "tell her you brought them for her!");

        player->remove_prop(QUEST_LILY_PROP);
        tell_object(player,"You feel more experienced!\n");
        say(QCTNAME(player) + " was rewarded.\n");
        return;
    }

    // Not doing the quest ...
    command("say This is a nice item, but why give it to me?");
    command("drop " + OB_NAME (obj));
}

/*** End of lily quest ******************************************/

/*
 * Gives out new feather quest
 */
string ask_feather()
{
    if (TP->query_prop(QUEST_FEATHER_PROP))
    {
        command("say Merry dol! I didn't think you'd have a hard time.");
        command("emote dances around merrily.");
        command("say Try harder, I know you can do it!");
        command("say Go, try again!");
        command("emote sings a merry tune.");
        return "";
    }

    if (CHECK_QUEST(TP, FEATHER_QUEST_NAME))
    {
        command("say Hiho, merry dol! But you have helped me already.");
        command("say Thanks for the feather!");
        return "";
    }

    command("say The feather in my hat is looking a little old.");
    command("say Getting a good one is difficult sometimes.");
    command("say Please help me and get a pheasant feather.");
    command("say They are one of my favorites!");
    command("smile hopefully");

    TP->add_prop(QUEST_FEATHER_PROP,1);

    return "";
}

void
test_feather(object player, object obj)
{
    // Is doing the quest ?
    if (player->query_prop(QUEST_FEATHER_PROP))
    {
        // Did this before ?
        if (!REWARD_QUEST(player, FEATHER_QUEST_NAME))
        {
            command("say Thank you for the feather, but you have " +
                "helped me before.");
            return;
        }

        command("emote dances around excitedly.");
        command("say Oh, thank you, thank you!");
        command("say It looks beautiful!");
        command("say I shall take it home, clean it, and wear it tomorrow!");

        player->remove_prop(QUEST_FEATHER_PROP);
        tell_object(player,"You feel more experienced!\n");
        say(QCTNAME(player) + " was rewarded.\n");
        return;
    }

    // Not doing the quest ...
    command("say This is a nice item, but why give it to me?");
    command("drop " + OB_NAME (obj));
}
/*** End of new feather quest ***********************************/

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
    {
        return;
    }

    // If the object is a lily, test for lily quest.
    if (obj->id(LILY_PROP))
    {
        set_alarm (2.0, 0.0, &test_lily(from, obj));
        return;
    }

    // If the object is a feather, test for feather quest.
    if (obj->id(FEATHER_PROP))
    {
        set_alarm (2.0, 0.0, &test_feather(from, obj));
        return;
    }

    // Thanks, but give the item back to player. we don't want it.
    set_alarm(2.0,0.0, &give_back(from, obj));
}
