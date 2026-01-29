/*
 * This file is IGARD_NPC + "i_uruk_capn.c"
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_uruk.c
 *
 *	Olorin, July 1993
 *	General revision: Olorin, Feb 1996
 *
 * Last modified by Alto, 11 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/rohan/isengard/igard/npc/igard_monster.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

#define WEP_ARRAY1 ({IGARD_WEP + "i_largescim", IGARD_WEP + "i_largeaxe", IGARD_WEP + "i_largeclub", IGARD_WEP + "i_largehalberd", IGARD_WEP + "i_bestscim", IGARD_WEP + "i_bestaxe", IGARD_WEP + "i_besthalberd",})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY1 ({IGARD_ARM + "i_platemail"})
#define ARM_ARRAY2 ({IGARD_ARM + "i_helmet"})
#define ARM_ARRAY3 ({IGARD_ARM + "i_bracers"})

public int      find_home();
public int      go_back_home();

object HOME;


public void
create_igard_uruk()
{
    clone_object(IGARD_ARM + "i_shoes")->move(TO);
    clone_object(IGARD_ARM + "i_greaves")->move(TO);
}

nomask void
create_igard_monster()
{
    int     rnd = random(41);

    set_name("uruk");
    set_pname("uruks");
    set_race_name("uruk");
    set_adj(alignlook());
    add_adj(alignlook2());
    set_long("This " + (implode(query_adjs()," "))
       + " uruk is one of the largest orcs you have seen. He stands as tall "
       + "as most men, although his arms dangle below his knees. His legs are "
       + "straight and long, and his eyes are much less sallow than those of "
       + "his orc kindred. With a shudder, you realize this is one of the "
       + "more successful and unnatural products of the breeding warrens in "
       + "the pits of Isengard. He looks intelligent and disciplined. It "
       + "seems wise to avoid crossing his path.\n");
    
    default_config_npc(95 + rnd / 2);
    set_base_stat(SS_INT, 65 + rnd);
    set_base_stat(SS_WIS, 65 + rnd);

    set_alignment(-350-rnd*10);

    set_skill(SS_WEP_SWORD,   85 + rnd);
    set_skill(SS_WEP_POLEARM, 85 + rnd);
    set_skill(SS_WEP_CLUB,    85 + rnd);
    set_skill(SS_WEP_AXE,     85 + rnd);
    set_skill(SS_WEP_KNIFE,   85 + rnd);
    set_skill(SS_PARRY,       85 + rnd);
    set_skill(SS_DEFENCE,     85 + rnd);
    add_prop(CONT_I_HEIGHT,   170 + rnd);
    add_prop(CONT_I_WEIGHT, 90000 + rnd * 500);
    add_prop(CONT_I_VOLUME, 85000 + rnd * 500);    
    add_prop(LIVE_I_SEE_DARK, 5);

    set_chat_time(15 + random(15));
    add_chat("I report directly to the Boss. You would do well to curry "
        + "my favour, dog.");
    add_chat("Someday we'll no longer need all these filthy hill orcs. "
        + "What good are a brace of rats that cannot stand the light of day.");
    add_chat("What are you looking at? Move along!");
    add_chat("Those filthy orcs from Lugburz, they'll soon learn the "
        + "White Hand can punch the Eye until it is red, oh yes.");
    add_chat("When I find those lads that skipped the watch, there will be "
        + "blood spilled.");
    add_chat("My Uruk Hai will dispatch the horse boys soon enough.");
    add_chat("Get to work, you slackards! The Boss needs this job done "
        + "yesterday!");
    add_chat("I'm supposed to keep an eye out for that squeaker Grima. "
        + "Were it not that the Boss smiles on him, I would squish him without "
        + "a further thought.");
    add_chat("Do something useful or I'll have you clapped in the stockade.");
    add_chat("Any and all skulking rangers are to be killed immediately, "
        + "Boss's orders!");
    add_chat("Blasted rangers! I'd have them exterminated like the rats they "
        + "are if I could find a way to coax them out of their holes.");
    add_chat("We have no time for the clap-trap from Lugburz, and that goes "
        + "for orcs and mages alike.");
    add_chat("One of those muck-raking black-robed hooded mages tried to "
        + "order me about some time back. I wonder if the vultures enjoyed "
        + "his corpse?");
    add_chat("All dwarves are to be hauled below to work the mines, Boss's "
        + "orders!");
    add_chat("We have orders for halflings. The Boss has some questions for "
        + "the little squeakers that need answering.");
    add_chat("The lads have been told not to have sport with any halflings "
        + "we catch, but they'll get more than sport before the Boss is "
        + "done with them.");
    add_chat("The Boss has given me permission to raze the hovel of "
        + "Theoden when the time comes.");
    add_chat("There is work to be done! Where are those cursed hill orcs?");
    add_chat("All elves are to be captured for breeding experiments, Boss's "
        + "orders!");
    add_chat("We are the fighting Uruk Hai!");


    set_cchat_time(5 + random(10));
    add_cchat("You think to best me, runt? Come ahead, show me what you "
        + "have. It doesn't look like much from here.");
    add_cchat("That was your last mistake, mousie!");
    add_cchat("I'm glad this fight is taking so long. It gives me time to "
        + "decide which part of you to eat first.");
    add_cchat("I'll be scraping you off my shoes soon, runt.");
    add_cchat("Run while you can, little runt!");
    add_cchat("Uruk Hai!");

    set_act_time(15 + random(15));	
    add_act("grumble");
    add_act("get all from corpse");
    add_act("growl");
    add_act("stretch");		
    add_act("glare");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("growl"); 
    add_cact("frown"); 
    add_cact("yawn"); 

    set_alarm(1.0, 0.0, &find_home());

    create_igard_uruk();
}


static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
    Arm3 = ARM_ARRAY3;

    set_all_hitloc_unarmed(30);
}


int
find_home()
{
    HOME = environment(TO);
    return 1;
}

int
go_back_home()
{
    object foe;

    if (Victim->query_prop("_enemy_of_igard"))
    {
    foe = Victim;
    }

    if (environment(TO) == HOME)
    {
    return 1;
    }

    if ((TO->query_attack() != 0) || ((objectp(present(foe, ENV(TO))))
        && CAN_SEE(TO, foe)))
    {
    TO->command("kill " + foe->query_real_name());
    set_alarm(60.0, 0.0, &go_back_home());
    return 1;
    }

    tell_room(environment(TO), "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " adjusts his armours, peers dangerously around "
        + "and returns to his post.\n", ({TO}));

    tell_room(HOME, "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " arrives at his post, dusting off his "
        + "armours after a recent melee.\n");

    TO->move_living("M", HOME, 1, 0);

    return 1;
}
