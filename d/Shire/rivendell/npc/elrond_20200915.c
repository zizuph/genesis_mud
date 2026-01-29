/*
 * Elrond, Lord of Imladris
 * By Finwe, May 1998
 *
 * Added clone_unique to arms and weps
 * -- Finwe, February 2002
 */
#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>

#include "/d/Shire/rivendell/npc/elfmaker.h"

inherit "/d/Shire/rivendell/npc/elfmaker.c";
inherit KILL_LOGGER;
inherit "/lib/unique";

#include "/d/Shire/common/make_money.h"

#define ELLADAN_QUEST    "forest"

void
create_elf()
{
    if(!IS_CLONE)
        return;

    set_type(CITIZEN);
    set_name("elrond");
    set_living_name("elrond");
    set_adj("majestic");
    add_adj("dark-haired");
    set_title("Lord of Imladris");
    set_race_name("half-elf");
    set_gender(G_MALE);
    set_long("He is tall and majestic with slight elvish " +
        "features which show him to be one of the peredhil. " +
        "His face is ageless showing neither youth or age but " +
        "looks to know many things, both glad and sorrowful. " +
        "His hair is dark as the twilight and bears a circlet " +
        "of silver. His eyes are grey and clear as a quiet " +
        "evening yet burn with the light of stars. He appears " +
        "venerable, like a king who knows much and is tired " +
        "from countless battles, but is in the prime of his " +
        "strength. This is Elrond, Lord of Imladris and counted " +
        "mighty among both elves and men.\n");

    set_learn_pref(({ 0,0,0,1,1,1 }));

    set_stats(({200+random(20),200+random(20),190+random(20),
        220, 230, 150}));
    set_alignment(1200);
//    MAKE_MONEY;
    make_platinum(2+random(4));
    make_gold(6+random(10));

    set_base_stat(SS_OCCUP, query_average_stat()+random(20));
    set_skill(SS_WEP_SWORD,          70);
    set_skill(SS_DEFENCE,            80);
    set_skill(SS_PARRY,              80);
    set_skill(SS_AWARENESS,          70);
    set_skill(SS_SPELLCRAFT,        100);
    set_skill(SS_ELEMENT_EARTH,     100);
    set_skill(SS_ELEMENT_LIFE,      100);
    set_skill(SS_ELEMENT_FIRE,      100);
    set_skill(SS_FORM_CONJURATION,  100);
    set_skill(SS_FORM_ABJURATION,   100);
    set_skill(SS_FORM_DIVINATION,   100);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 100*1000);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(LIVE_I_SEE_DARK, 200);
    add_prop(OBJ_I_RES_MAGIC,   70);
    add_prop(OBJ_I_RES_DEATH,   70);
    add_prop(OBJ_I_RES_LIFE,    70);
    add_prop(OBJ_I_RES_LIGHT,   70);
    add_prop(OBJ_I_RES_WATER,   20);
    add_prop(OBJ_I_RES_AIR,     70);
    add_prop(OBJ_I_RES_EARTH,   40);
    add_prop(OBJ_I_RES_FIRE,    20);
    add_prop(OBJ_I_RES_COLD,    60);
    add_prop(OBJ_I_RES_POISON, 100);
    add_prop(OBJ_I_RES_ELECTRICITY, 30);

    add_prop(OBJ_I_NO_ATTACK,1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(OBJ_I_NO_MAGIC,1);
    add_prop(OBJ_M_NO_MAGIC,1);

    add_prop("_ranger_m_no_disarm_drop", 1);
    add_prop("_elladan_quest_",1);
    //add_prop(LIVE_I_QUICKNESS, 10);

    add_subloc("_special_look", TO);

    set_chat_time(4);
    add_chat("Welcome to Imladris.");
    add_chat("This valley is one of the last strongholds of elves.");
    add_chat("Feel free to relax here.");
    add_chat("Our strength is dwindling with every passing day.");
    add_chat("I hope your time here restores your spirits.");
    add_chat("The Shadow is growing daily.");
    add_chat("Orcs are gathering together again.");
    add_chat("Trolls were seen in the Misty Mountains. Be careful " +
        "if you go that way.");

    add_ask(({"quest", "task", "help"}), "@@ask_quest");

    set_alarm(2.0, 0.0, &arm_elf());
	set_kill_log_name("elrond");
   	set_kill_log_size(5000);

}


// Mask the original arm_elf routine
void
arm_elf()
{
    object arm,wep;
    seteuid(getuid(TO));

    wep = clone_unique(RWEP_DIR + "m_longsword", MAX_UNIQUE_ITEMS,
        RWEP_DIR+ "c_longsword");
    wep->set_hands(W_ANYH);
    wep->move(this_object());

    arm = clone_unique(RARM_DIR + "glow_helmet", MAX_UNIQUE_ITEMS,
        RARM_DIR+ "helmet");
    arm->move(this_object());

    arm = clone_unique(RARM_DIR + "m_greaves", MAX_UNIQUE_ITEMS,
        RARM_DIR+ "greaves");
    arm->move(this_object());

    arm = clone_unique(RARM_DIR + "glow_shield", MAX_UNIQUE_ITEMS);
    arm->move(this_object());

    arm = clone_unique(RARM_DIR + "glow_platemail", MAX_UNIQUE_ITEMS,
        RARM_DIR+ "chainmail");
    arm->move(this_object());

//    clone_object(RARM_DIR+"glow_platemail")->move(TO);

    command("wield sword");
    command("wear all");
}


int
filter_enemy(object who)
{
    return (who->query_attack() == TO);
}


int
introduce_elf(string who)
{
    object ob;
    int i;

    ob = find_player(who);
    if (::introduce_me(who))
    {
        if (i == 0)
        {
            command("say Greetings and welcome to Imladris.");
        }
        else if (i == 1)
        {
            command("shake "+who);
            command("say Welcome "+CAP(who)+"!");
            command("smile serious "+who);
        }
        else if (i ==2)
        {
            command("say Greetings "+CAP(who)+".");
            command("say I hope your journey here was safe.");
        }
    }
}


string ask_quest()
{
    if (TP->query_prop("_elladan_quest_"))
    {
        command("say I have given you a task already. Perhaps " +
            "you're not strong enough to accomplish it after all.");
        command("emote looks to the west and sighs deeply.");
        return "";
    }

    if (CHECK_QUEST(TP, ELLADAN_QUEST))
    {
        command("say Thank you for your offer, we need all " +
            "the strength we can muster but you have already " +
            "assisted us.");
        return "";
    }

    command("say Allies of the Dark One are amassing on our " +
        "borders. Orcs, trolls, and other evil creatures are " +
        "seen more frequently as they gather near the forest. " +
        "We have sent patrols out to watch them and return and " +
        "report. However, one member, Elladan, has not " +
        "returned. This concerns me greatly. Please go out and " +
        "find him. If you do locate him, return with any " +
        "reports he has. Thank you.");

    TP->add_prop("_elladan_quest_", 1);
    command("say May the Valar protect and guide you.");

    return "";

}


void test_found_elladan_quest(object player, object obj)
{

/*
    if(!obj->id("_elladan_report_"))
    {
        command("emote examines the " + obj->short() + " for a moment.");
        command("say This " + obj->short() + " means nothing to " +
            "me. Are you sure this is what I need?");
	return;
    }
*/
    if (!REWARD_QUEST(player, ELLADAN_QUEST))
    {
	command("say Thank you for your concern, but you have helped me before.");
	return;
    }
    say(QCTNAME(player) + " gives something to Elrond.\n");
    command("emote looks over the report thoughtfully.");
    command("emote frowns.");
    command("emote sighs sadly.");
    command("emote looks up from the report.");
    command("say Thank you for bringing this report back. It is " +
        "not good news but it will aid us. For your efforts, " +
        "you shall be rewarded.");
    say(QCTNAME(player) + " gives something to Elrond.\n");
    tell_object(player, "Elrond rewards you. You feel more " +
        "experienced and enlightened.\n");
    say(QCTNAME(player) + " was rewarded.\n");
    player->remove_prop("_elladan_quest_");
    player->remove_prop("_elladan_report_given_");

}



public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if(!living(from))
        return;


    if(obj->id("_elladan_report_"))
	set_alarmv(3.0,0.0,"test_found_elladan_quest",({from, obj}));

   else
    {
	set_alarmv(3.0, 0.0,"give_back",({from, obj}));
	return;
    }


}

int
query_knight_prestige()
{
    return -30;
}



public void
give_back(object from, object obj)
{
    command("emote examines the " + obj->short() + " for a moment.");
    command("say This " + obj->short() + " means nothing to " +
        "me. Are you sure you want to give this to me?");
    write("Elrond gives it back to you.\n");
    obj->move(from);
    return;
}

special_attack(object enemy)
{
   object me;
   mixed* hitresult, *hit_type;
   string how;
   int x;

    hit_type=({"pummels", "decks", "crushes", "charges", "batter"});

    x = random(sizeof(hit_type));

   me = TO;
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(600 + random(400), W_BLUDGEON, me, -1);
   how = " without effect";
   if (hitresult[0] > 0)
      how == "lightly";
   if (hitresult[0] > 5)
      how = " hard";
   if (hitresult[0] > 10)
      how = " very hard";
   if (hitresult[0] > 15)
      how = " extremely hard";
   if (hitresult[0] > 20)
      how = " tremendously hard";
   if (hitresult[0] > 25)
      how = " so hard, bones crack";
   if (hitresult[0] > 30)
      how = " so terribly hard, blood begins to seep from the wounds";


   enemy -> catch_msg(QCTNAME(me) + " "+hit_type[x]+" you" + how + ".\n");
   tell_watcher(QCTNAME(me) + " "+hit_type[x]+" " + QTNAME(enemy) + " !\n"+
      capitalize(enemy->query_pronoun()) + " is hit"+
      how + ".\n", enemy);
   if (enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
