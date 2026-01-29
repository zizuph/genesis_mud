/*
 *   /d/Gondor/pelargir/newbiecamp/npc/grub.c
 *
 *   A farmer who gives out a tour to the pelargir newbiecamp.
 *
 *   Alto, 02 December 2002
 */


#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <math.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "../ncamp_defs.h"

int quest_in_progress = 0;

void 	give_tour();
void 	reward_tour();

#define RIVERSTEAD_TOURING            "_riverstead_touring"
#define RIVERSTEAD_FOUND              "_riverstead_found"

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();
    set_adj("young");
    set_adj("frightened");
    set_living_name("grub");
    set_name("grub");
    add_name("boy");
    add_name("farmer");
    set_race_name("human");

    set_title("the Farmhand");
    set_long("This young boy is obviously of rural descent. He is dressed in "
        + "homespun garments and capped in a bag of sackcloth. He also looks "
        + "quite terrified. To have run from his farm all the way into the city "
        + "of Pelargir must have taken quite a fright to motivate. Maybe he could "
        + "use the help of an adventurer like you.\n");

    rnd = random(60);
    default_config_npc(60+rnd/2);
    set_base_stat(SS_DIS, 60 + rnd);
    set_alignment(350+rnd*10);
    set_skill(SS_WEP_SWORD, MIN(50, 75 + rnd));
    set_skill(SS_WEP_POLEARM, MIN(50, 75 + rnd));
    set_skill(SS_PARRY, MIN(50, 75 + rnd));
    set_skill(SS_DEFENCE, MIN(50, 75 + rnd));
    add_prop(CONT_I_HEIGHT,170+rnd);
    add_prop(CONT_I_WEIGHT,85000+rnd*500);
    add_prop(CONT_I_VOLUME,80000+rnd*500); 
    
    set_restrain_path("/d/Gondor/pelargir/docks/");
    set_monster_home("/d/Gondor/pelargir/docks/dock4");
    set_random_move(10);


    setuid();
    seteuid(getuid());

    clone_object(NCAMP_WEP + "ncamp_hclub.c")->move(TO);


    set_chat_time(15);
    add_chat("The orcs will surely destroy my village if no help arrives!");
    add_chat("I am so tired, but I dare not fail.");
    add_chat("I have not the strength to go back myself - nor the courage.");
    add_chat("Gondor must be warned!");
    add_chat("They are burning our homes!");
    add_chat("I barely escaped! If only someone could help us.");
    add_chat("The orcs have crossed the river!");
    add_chat("Help! Help!");
    add_chat("I heard there might be some new bees in this town. Are there any here "
        + "who would help a village in need?");
    add_chat("Are you a new bee? I heard I might find some here.\n");

    set_cchat_time(5);
    add_cchat("Attack a farm boy? What courage you have, scoundrel.");
    add_cchat("Better you than some orc, I suppose.");
    add_cchat("Help! Guards!");
    add_chat("It seems villains are everywhere in Gondor!");

    set_act_time(7);
    add_act("worry");
    add_act("sigh tiredly");
    add_act("pout");
    add_act("stare");
    add_act("emote glances to the southeast with a worried look in his eyes.");
    add_act("emote starts searching the area for new bees.");


    remove_prop(LIVE_I_NEVERKNOWN);

    set_default_answer( ({ "say Excuse me, I do not follow you.", "hmm" }) );

    add_ask_item(({"village", "settlement", "farm", "town"}), "say My village "
        + "is burning, set afire by orcs from beyond the Anduin!");
    add_ask_item(({"orc", "orcs", "villains"}), "say They are terrible! They "
        + "came from the east and surprised us. We are simple farmers, not "
        + "trained and hardened in battle!");
    add_ask_item(({"new bee", "bee", "newbie"}), "say I was told by someone "
        + "at the city gates that I should look for new bees to help me. Do you "
        + "know what those are? Are they some kind of great warrior?");
    add_ask_item(({"quest"}), "say Yes, I am on a quest to find some new bees. "
        + "Do you know any? I could use their help.");
    add_ask_item(({"news"}), "say News would be of great help.");
    add_ask_item(({"reward"}), "@@reward_tour");
    add_ask_item(({"help", "task", "tour"}), "@@give_tour");

    command("wield all");
    command("wear all");

    refresh_mobile();

}


void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}

void
reward_tour()
{
    object player;

    player = this_player();

    if (!present(player, ENV(TO)))
        {
        TO->command("say Huh? Who said that?!");
        return;
        }

    if (player->test_bit("gondor", RIVERSTEAD_TOUR_GROUP, RIVERSTEAD_TOUR_BIT))
        {
        TO->command("say You have already brought me plenty of news. "
            + "Thanks again!");
        return;
        }

    if (player->query_prop(RIVERSTEAD_FOUND))
        {
        player->set_bit(RIVERSTEAD_TOUR_GROUP, RIVERSTEAD_TOUR_BIT);
        player->add_exp_quest(RIVERSTEAD_TOUR_EXP);
        player->catch_msg("How nice of you to return to the poor farm boy with "
            + "news of his village!\n");
        player->catch_msg("You feel more experienced!\n");
        player->remove_prop(RIVERSTEAD_TOURING);
        player->remove_prop(RIVERSTEAD_FOUND);
        LOG_QUEST(player, RIVERSTEAD_TOUR_EXP, "RIVERSTEAD TOUR");
        return;
        }

    if (player->query_prop(RIVERSTEAD_TOURING))
        {
        TO->command("say I do wish you would bring news of my village! Please "
            + "hurry back, and I shall give you a reward.");
        return;
        }

    TO->command("say Perhaps you should help me first. Nothing in life is "
        + "free.");
        
    return;
}


void
give_tour()
{
    string who;
    object from;
    
    from = this_player();
    
    who = from->query_real_name();

    command("say How kind of you to take time to help a poor boy in need.\n");

    if (from->query_average_stat() > STAT_MAX)
    {
        TO->command("say I wouldn't want to trouble an old timer like you. I was "
            + "told to look for NEW bees, silly.");
        return;
    }
    

    if (from->test_bit("gondor", RIVERSTEAD_TOUR_GROUP, RIVERSTEAD_TOUR_BIT))
    {
        TO->command("say However, you have already brought me plenty of news. "
            + "Thanks again!");
        return;
    }

    if (from->query_prop(RIVERSTEAD_TOURING))
    {
        command("say I wish you would hurry, though!");
        return;
    }


    if(quest_in_progress)
        TO->command("say I already got one new bee to help me out, but maybe "
            + "you could bring back some better news.");

    command("emote shuffles his feet and looks imploringly at you.");
    set_alarm(1.0, 0.0, &command("frown"));
    set_alarm(3.0, 0.0, &command("say Orcs have crossed the Anduin and invaded my "
        + "village from the east!"));
    set_alarm(6.0, 0.0, &command("worry"));
    set_alarm(7.0, 0.0, &command("peer imploringly " + who));
    set_alarm(9.0, 0.0, &command("say I ran all the way to the city, but alas I can "
        + "find no great warriors to aid my people. I guess with the war coming on they "
        + "are all too busy."));
    set_alarm(14.0, 0.0, &command("say I've been gone for many hours on my quest. I wish "
        + "I had news of the fate of my village. I fear the worst."));
    set_alarm(17.0, 0.0, &command("worry"));
    set_alarm(19.0, 0.0, &command("say One of the guards at the city gates told me I "
        + "might get a new bee to run down to my village and gather news for me."));
    set_alarm(22.0, 0.0, &command("giggle"));
    set_alarm(23.0, 0.0, &command("say You fit the description, although you do not "
        + "look like any bee I ever saw."));
    set_alarm(25.0, 0.0, &command("smile sadly"));
    set_alarm(26.0, 0.0, &command("say But then bees were things of my innocent childhood, "
        + "which has come to a sorry end."));
    set_alarm(30.0, 0.0, &command("cry"));
    set_alarm(31.0, 0.0, &command("say Please, run to my village. Climb to the top of the "
        + "watchtower to gather news. Come back to me and I will reward you as well as "
        + "a poor farm boy can."));
    set_alarm(35.0, 0.0, &command("emote fidgets nervously."));

    from->add_prop(RIVERSTEAD_TOURING, 1);
    
    set_alarm(36.0, 0.0, &command("say Please hurry! I hope that the news is not bad."));
    set_alarm(44.0, 0.0, &command("wave"));

    quest_in_progress = 1;
    return;
}

public int
query_knight_prestige() { return -30; }

