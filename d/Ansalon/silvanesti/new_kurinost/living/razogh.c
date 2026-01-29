/* Based on aurak_leader by Aridor */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/new_kurinost/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";
inherit AUTO_TEAM
inherit "/lib/unique";

#define TASK_NUMBER "_kurinost_raxx_task_number"
#define RAZOGH_KILLED "_kurinost_raxx_task_killed_razogh"

#define DEBUG(x)    find_player("arman")->catch_msg("[Kurinost] " + x + "\n")


void
create_da_monster()
{
    set_name("razogh");
    set_living_name("razogh");
    set_race_name("hobgoblin");
    add_adj("furious");

    set_title("First Lieutenant of the Silvanesti Invasionary Forces");
    set_long("This huge hobgoblin officer of the Green Dragonarmy is clearly full " +
        "of rage and frustration, to the point where his work crew attempting to " +
        "cut through the hedge surrounding the forest of Silvanesti avoid him at " +
        "all costs! He is heavily armoured with the exception of the head, where " +
        "he proudly leaves free a long braid of thick smelly black hair.\n");

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_AWARENESS, 70);
    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(CONT_I_HEIGHT, 165);
    set_all_hitloc_unarmed(20);
    set_alignment(-950);

    set_color("green");
    set_dragonarmy_rank(1, 2);

    set_act_time(10);
    add_act("emote hacks at the thorny hedge in fury.");
    add_act("emote roars: FREGGIN HEDGE! CUTZ IT GROWZ! BURNZ IT GROWZ! NO MORE GROWZ!");
    add_act("assist");
    add_act("emote stares around, daring any to face him.");
    add_act("shout YOU SMEG HERDERS! CUTZ HARDER!");
    add_act("say Elves are tricksy... use plants to stop us!");
    add_act("say Stupid Raxx!");

    set_cact_time(10);
    add_cact("emote yells: I rip out your gutz!");

    add_ask(({"hedge", "great hedge"}),
        "say Hedge tricksy! We cutz! It growz! We burnz! It growz! We cutz " +
        "and burnz, send draconians in to forest... and it growz! And growz! " +
        "No more draconians!", 1);
    add_ask(({"draconians","draconian losses","losses"}),
        "say Draconians now pin cushion for elf arrows. Tyberus will be furious! " +
        "All Raxx's fault! I send messenger to Tyberus in outpost to report failure.", 1);
    add_ask(({"messenger", "report"}),
        "say Messenger go to outpost to give report to Tyberus. Not heard back for " +
        "a while.\n", 1);
    add_ask(({"tyberus"}),
        "say Tyberus High Commander of Green Army here. Staying in outpost. He " +
        "will be furious with draconian losses.\n", 1);
    add_ask(({"scouting mission", "mission"}),
        "@@respond_mission");
    add_ask(({"raxx"}),
        "say Sneaky stupid Raxx! We loose lots of draconians in the forest " +
        "'cause of him! He send draconians through the hedge! Now he run away! " +
        "Tyberus will flay his hide!", 1);
    set_default_answer("@@default_answer");

    set_pick_up_team(({"aurak","sivak","hobgoblin"}));
    set_max_team_size_auto_join(8);
    arm_me();

    trig_new("%w 'introduces' %s","react_to_intro");
}

string
respond_mission()
{
    command("stare suspicious " +TP->query_real_name());
    command("say How you know about mission? You spy?");

    return "";
}

string
default_answer()
{
    command("stare angr " +TP->query_real_name());
    command("say No time for talks! More cuttingz!");

    return "";
}

arm_me()
{
    object ob;

    setuid();
    seteuid(getuid());

    if(!random(4))
    {
	ob = clone_object("/d/Krynn/solamn/splains/obj/bbattleaxe");
    }
    else
    {
	ob = clone_unique(RSWEAPON + "soulsplitter", 10, RSWEAPON + "woodaxe");
    }
    ob->move(TO, 1);


    ob = clone_object("/d/Ansalon/balifor/flotsam/obj/armour/bplatemail");
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bshinguard");
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bheavyboots");
    ob->move(TO, 1);

    command("wear all");
    command("wield all");
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

/*
 * Function:	attacked_by
 * Arguments:	attacker - The attacker
 * Description:	This function is called when somebody attacks this object 
 */

public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    command("say Assassins! Elven sympathisers! Attack!"); 
}

void
attack_object(object ob)
{
    command("say Fight time! Attack!");

    ::attack_object(ob);
}

void
attack_intruder(object enemy)
{
    if(!CAN_SEE(TO, enemy))
    {
	return;
    }

    if(TO->query_attack())
      return;

    command("kill " +enemy->query_real_name());
    return;
}

public void
stand_up(object enemy)
{
    if(enemy->query_race_name() == "elf")
    {
        command("shout Elves escaping da forest! Attack!");
        set_alarm(3.0, 0.0, &attack_intruder(TP));
    }
    else
    {
        command("glare suspic " + enemy->query_real_name());
        command("say to " + enemy->query_real_name()+
            " What are you doing here?");
    }

    return;
}

void
init_living()
{
    init_team_pickup();

    if(CAN_SEE(TO, TP) && (TP->query_race_name() != "hobgoblin"))
      set_alarm(3.0, 0.0, &stand_up(TP));

    ::init_living();
}

public void
do_die(object killer)
{
    object * teammates = killer->query_team_others();

    if (sizeof(teammates) > 0)
    {
        foreach(object mate: teammates)
        {
            if(mate->query_prop(TASK_NUMBER) == 7)
            {
                mate->add_prop(RAZOGH_KILLED, 1);
                TO->add_leftover(RSOBJS + "bloody_braid", "braid", 1,"", 0, 0);
            }
        }
    }

    if(killer->query_prop(TASK_NUMBER) == 7)
    {
        killer->add_prop(RAZOGH_KILLED, 1);
        TO->add_leftover(RSOBJS + "bloody_braid", "braid", 1,"", 0, 0);
    }

    ::do_die(killer);
}
