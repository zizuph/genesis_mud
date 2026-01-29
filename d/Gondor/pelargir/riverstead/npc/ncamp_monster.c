/*
 * This file is NCAMP_NPC + "ncamp_monster.c"
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_monster.c
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/lib/unique.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

#define WEP_ARRAY1 ({NCAMP_WEP + "ncamp_oclub", NCAMP_WEP + "ncamp_oscim", NCAMP_WEP + "ncamp_oaxe"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY1 ({ARM_DIR + "releather", ARM_DIR + "orcmail"}) 
#define ARM_ARRAY2 ({ARM_DIR + "reshield", ARM_DIR + "rehelm"})
#define ARM_ARRAY3 ({ })


// Global variables:
static  string *Wep1,
               *Wep2,
               *Arm1,
               *Arm2,
               *Arm3;

public void
create_ncamp_monster()
{
    set_race_name("orc");
}

nomask void
create_monster()
{
    int rnd     = random(11);

    seteuid(getuid(TO));
    add_name("_ncamp_monster");

    set_skill(SS_WEP_SWORD,   10);
    set_skill(SS_WEP_POLEARM, 10);
    set_skill(SS_WEP_AXE,     10);
    set_skill(SS_WEP_KNIFE,   10);
    set_skill(SS_WEP_CLUB,    10);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK,   2);

    set_aggressive(1);

    set_learn_pref( ({ 1, 1, 1, 0, 0, 1, }) );

    create_ncamp_monster();
}

static void
set_arm_arrays()
{
   Wep1 = WEP_ARRAY1;
   Wep2 = WEP_ARRAY2;
   Arm1 = ARM_ARRAY1;
   Arm2 = ARM_ARRAY2;
   Arm3 = ARM_ARRAY3;
}

static void
get_money() 
{
   MONEY_MAKE_CC( 10 + random(11))->move(TO);
   MONEY_MAKE_SC(  1 + random( 6))->move(TO);
}


public void
arm_me()
{
   int iw, is;
   
   set_arm_arrays();
   
   seteuid(getuid(TO));
   
   if (is = sizeof(Wep1))
   {
      iw = random(is);
      {
          clone_object(Wep1[iw])->move(TO);
      }
   }

   command("wield weapon");
   
   if (is = sizeof(Wep2))
   {
      iw = random(is);
      clone_object(Wep2[iw])->move(TO);
   }
   
   if (is = sizeof(Arm1))
   {
      iw = random(is);
      clone_object(Arm1[iw])->move(TO);
   }
   
   if (is = sizeof(Arm2))
   {
      iw = random(is);
      clone_object(Arm2[iw])->move(TO);
   }
   
   if (is = sizeof(Arm3))
   {
      iw = random(is);
      clone_object(Arm3[iw])->move(TO);
   }
   command("wield all");
   command("wear all");

   get_money();
}


public void
do_attack(object victim)
{
    if (objectp(query_attack()))
        return;
    if (!present(victim, ENV(TO)))
        return;

    command("kill " + victim->query_real_name());
}

public void
init_attack()
{
    if (objectp(query_attack()))
        return;
    if (TP->query_npc() && TP->query_race_name() == "human")
        set_alarm(1.0, 0.0, &do_attack(TP));
}

string
alignlook() 
{
   string *alignlooks = ({"grim", "grumpy", "cruel", "angry", "beastly",
       "mean", "dirty", "foul", "brutal", "battered", "sinister",
       "wicked","evil","savage", "ugly", "fierce","dangerous", "intelligent",
       "skulking", "furtive", "sneaky", "nervous", "snarling", "sniveling",
       "sickly", "lanky", "disoriented", "scabrous",
       "filthy", "drunken", "lazy", "frightened", "devious"});
   return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
   string *alignlooks = ({"short", "stooped", "crippled", "limping", "sleepy",
       "muscular", "hulking", "pensive", "huge", "twisted", "scarred",
       "greasy-haired","balding","tall", "skinny", "towering","bent-nosed", 
       "cross-eyed", "one-eyed", "hairless", "albino", "unstable", "psychotic",
       "skulking", "furtive", "sneaky", "nervous", "snarling",
       "murderous", "deceitful", "conniving", "whining", "raging",
       "slobbering", "drooling", "one-eared", "maniacal", "strange"});
   return ONE_OF_LIST(alignlooks);
}

int
orc_acts()
{
    set_chat_time(15 + random(15));
    add_chat("I want man flesh to eat!");
    add_chat("Those stinking morgul mages! They have the favour of the Eye, "
        + "oh yes.");
    add_chat("What are you looking at? Maybe I should kill you!");
    add_chat("I should take you back to Lugburz. There are some there who "
        + "might want to question you. Oh yes, and it will tickle, no doubt "
        + "about it.");
    add_chat("We've skulked about long enough. I want a fight!");
    add_chat("These squealing farmers. Better off dead, I say.");
    add_chat("Someone needs to sneak down into the village and see how many "
        + "of these farmers we need to slaughter.");
    add_chat("We'll burn Pelargir soon enough!");
    add_chat("Move along, else I might decide to sharpen my teeth on you.");
    add_chat("We killed us a ranger the other day. Stuffed sand in his ears and "
        + "broke his filthy hand.");
    add_chat("Why do rangers always sneak about? They must be afraid of "
        + "their own shadows.");
    add_chat("Filthy morgul mages. Always with their snot-noses in the air. "
        + "But the Eye loves them, so we endure it.");
    add_chat("The first dwarf I see is a dead dwarf. Gutter rats.");
    add_chat("It is long past supper, but I could still eat a hobbit or "
        + "three.");
    add_chat("The problem with hobbits is that you get hair stuck in your "
        + "teeth when you eat their feet.");
    add_chat("Just a matter of time before we stride upon the bones in Minas "
        + "Tirith.");
    add_chat("Free Peoples? I'll free them from their accursed lives.");
    add_chat("Nasty elves with their cursed glittering eyes. The Eye "
        + "will make them pay too.");
    add_chat("Me and some other lads plan to set up on our own after this "
        + "business with Gondor is finished.");


    set_cchat_time(5 + random(10));
    add_cchat("Die, scum!");
    add_cchat("I'll rip your throat out, maggot!");
    add_cchat("Hold still and it will hurt less!");
    add_cchat("Scum! I'll roast your heart on a stick!");
    add_cchat("Run while you can, little mouse!");
    add_cchat("I'm going to eat your liver, you know.");

    set_act_time(15 + random(15));	
    add_act("burp");
    add_act("get all from corpse");
    add_act("hiss");
    add_act("grin");		
    add_act("fart");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("emote grits his teeth and charges."); 
    add_cact("growl"); 
    add_cact("frown"); 
    add_cact("yawn"); 

    return 1;
}

void
do_die(object killer)
{
    object room;
    
    room = ENV(TO);
    room->replace_humans(1);


    tell_room(ENV(TO), "The orc staggers and falls dead, one "
        + "less invader to ravage the settlement.\n");

    ::do_die(killer);
}

