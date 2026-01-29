/*
    young_noble.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
    Updated with add_name ("human/man/nobleman") and removed second
    set_race_name and added set_pname("noblemen") Meton 2021

 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"
#include <money.h>

#define QUEST "noble_ringquest"

void
create_kalad_monster()
{
    set_name("noble");
    set_adj("young");
    add_adj("rich");
    add_name("human");
    add_name("man");
    add_name("nobleman");
    set_pname("noblemen");
    set_race_name("human");
    set_short("young rich noble");
    set_long("This young man looks strong, and bright. He walks around "+
        "with an air of confidence, and power. He has long, blonde hair, with "+
        "sparkling blue eyes. A slight smile creaps on this young, handsome "+
        "face.\n");

    set_alignment(200);
    set_knight_prestige(-60);
    add_speak("I have lost my ring somewhere in the park here!\n");
    set_stats(({100,70,80,70,50,100}));
    set_skill(SS_WEP_KNIFE,70);
    set_skill(SS_DEFENSE,60);
    set_random_move(10);

    set_act_time(3);
    add_act("wink all");
    add_act("wiggle");
    add_act("say I wonder what happened to my beautiful ring !");
    add_act("dance all");
    add_act("say Oh my love!");
    add_ask("ring","@@noble_quest_ring@@",1);

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);

    add_equipment(({
        NOBLE + "arm/silk_tunic",
        NOBLE + "arm/leather_shoes",
        NOBLE + "arm/silver_pendant",
        NOBLE + "arm/ring",
        NOBLE + "arm/e_leather_pants",
        NOBLE + "wep/jeweled_dagger",
        }));

    MONEY_MAKE_GC(random(10))->move(TO);

    // Wield when attacked
    command("unwield all");
}

void
enter_inv(object ob, object from)
{
    if (from)
    {
    	if (MASTER_OB(ob) == (NOBLE + "obj/quest_ring"))
    	{
	        set_alarm(3.0, 0.0, "reward_ring", from, ob);
    	}
	    else
    	    command("drop " + OB_NAME(ob));
    }
}

void
reward_ring(object who, object ring)
{
    if(who->test_bit("Kalad",1,7))
    {
    	command("say Thank you again, bro!");
    	ring->remove_object();
    	return;
    }
    else
    {
    	command("say Thank you very much, " + who->query_name() + "!");
    	command("say I got to keep better track of that!");
    	who->catch_msg("You feel a little more experienced.\n");
    	who->add_exp(250);
    	who->set_bit(1,7);
    	ring->remove_object();
    	log_file(QUEST, extract(ctime(time()),4,15) + " "+
            capitalize(TP->query_real_name()) + " rewarded with 250 xp,"+
            "<"+TP->query_average_stat()+"> average stats.\n");
    	return;
    }
}

string
noble_quest_ring()
{
    set_alarm(4.0,0.0,"noble_quest_ring2");
    set_alarm(1.5,0.0,"guard_grin");
    return "say I was with this sweet young thing the other night.. "+
        "and well.... what can I say?\n";
}

void
guard_grin()
{
    object *ob;

    ob = query_team();
    if(sizeof(ob))
	ob[0]->command("grin " + OB_NAME(TO));
}

void
noble_quest_ring2()
{
    command("say My charm is irresistable, and during our passionate "+
        "loving, I seemed to have lost my ring...\n");
    command("say Only problem is, I was drunk off my ass that night, "+
        "and I don't know what I did with it. If you see it, I would be "+
        "grateful if you would return it to me.\n");
}

void
react_woman()
{
    command("say Hey cutie!");
    command("pinch "+lower_case(TP->query_name())+" bottom");
    TP->command("blush");
    command("say Why don't you stop by at my large house for "+
      "dinner tonight?");
    command("smile seduct");
}

void
init_living()
{
    ::init_living();
    if (TP->query_gender() == 1 && TP->query_race_name() == "human")
    	set_alarm(2.0, 0.0, react_woman);
}

void
attacked_by(object enemy)
{
    object *bodyguard;

    ::attacked_by(enemy);
    bodyguard = query_team();
    command("wield all");
    if (sizeof(bodyguard))
    {
    	if (present(bodyguard[0], ENV(TO)))
    	{
    	    command("eeks");
    	    command("emote hides behind his bodyguard.");
    	    enemy->attack_object(bodyguard[0]);
    	}
    }
}

void
help_friend(object ob)
{
    command("shout Get him, Thor!");
    attack_object(ob);
}

