/*
 * This file is NCAMP_NPC + "ncamp_human.c"
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

#define WEP_ARRAY1 ({NCAMP_WEP + "ncamp_hclub", NCAMP_WEP + "ncamp_hscim", NCAMP_WEP + "ncamp_haxe"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY1 ({NCAMP_ARM + "hleather", NCAMP_ARM + "hmail"}) 
#define ARM_ARRAY2 ({NCAMP_ARM + "hshield", NCAMP_ARM + "hhelm"})
#define ARM_ARRAY3 ({ })


// Global variables:
static  string *Wep1,
               *Wep2,
               *Arm1,
               *Arm2,
               *Arm3;

public void
create_ncamp_human()
{
    set_race_name("human");
}

nomask void
create_monster()
{
    int rnd     = random(11);

    seteuid(getuid(TO));
    add_name("_ncamp_human");

    set_skill(SS_WEP_SWORD,   10);
    set_skill(SS_WEP_POLEARM, 10);
    set_skill(SS_WEP_AXE,     10);
    set_skill(SS_WEP_KNIFE,   10);
    set_skill(SS_WEP_CLUB,    10);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK,   2);

    set_aggressive(1);

    set_learn_pref( ({ 1, 1, 1, 0, 0, 1, }) );

    create_ncamp_human();
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
    if (TP->query_npc() && TP->query_race_name() == "orc")
        set_alarm(1.0, 0.0, &do_attack(TP));
}

string
alignlook() 
{
   string *alignlooks = ({"grim", "hale", "brave", "angry", "worried",
       "nervous", "noble", "mischievous", "calm", "haggard", "weary",
       "healthy","alert","attractive", "clever", "nimble","sluggish", "intelligent",
       "gentle", "tough", "courteous", "thoughtful", "battle-ready", "unprepared",
       "frightened", "cunning", "hardy", "stalwart",
       "sleepy", "disheveled", "courageous", "sturdy", "relentless"});
   return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
   string *alignlooks = ({"short", "long-legged", "blonde", "sandy-haired",
       "muscular", "brown-haired", "red-haired", "freckled", "pale", "tanned",
       "long-haired","grey-haired","tall", "skinny", "white-haired","long-nosed", 
       "big-eared", "stout", "barefoot", "knock-kneed", "lanky", "dimpled",
       "cleft-chinned", "regal", "common", "strong-chinned", "blue-eyed",
       "green-eyed", "brown-eyed", "hazel-eyed", "wide-eyed", "pug-nosed",
       "broad-shouldered", "slender", "portly", "stocky", "thin", "fat"});
   return ONE_OF_LIST(alignlooks);
}

int
human_acts()
{
    set_chat_time(15 + random(15));
    add_chat("Run while you can! There are orcs in the village!");
    add_chat("What do you want, stranger?.");
    add_chat("The Steward must be warned!");
    add_chat("I will die before I let these stinking orcs have my farm!");
    add_chat("They've started burning huts! Quick, get water!");
    add_chat("We have everything to lose. We will stand and fight!");
    add_chat("Bloody murderous orcs. Why don't they leave us in peace?");
    add_chat("We are simple farming folk. We never hurt anyone!");
    add_chat("If only Boromir were here. He would push them back across the river!");
    add_chat("Someone should fetch the Rangers! They always seem to know what "
        + "to do when evil is afoot.");
    add_chat("I hope they don't have any of those Morgul Mages with them. Those "
        + "black chaps give me the creeps.");
    add_chat("We should call up the Thornlin Militia and run these orcs out of "
        + "town!");
    add_chat("I hope my cousin shows up. He's pretty good in a fight.");
    add_chat("These orcs have messed with the wrong people this time.");
    add_chat("Enough is enough! First Osgiliath and now this? Fight, friends, "
        + "let us fight to the death for our homes!");
    add_chat("Someone ought to let Carastur in Pelargir know about this. First "
        + "its simple country folk, but these orcs will be beating on the "
        + "city gates soon enough.");
    add_chat("Hail in the name of the Free Peoples of Gondor!");
    add_chat("Have you come to join in the defence of our village?");
    add_chat("We could really use a good fighter like you.");


    set_cchat_time(5 + random(10));
    add_cchat("For Gondor!");
    add_cchat("Filthy traitor! Its bad enough we have orcs to deal with!");
    add_cchat("I don't have time for this!");
    add_cchat("Die, morgul-rat!");
    add_cchat("How dare you attack me!");
    add_cchat("Fear! Fire! Foes! Help me!");

    set_act_time(15 + random(15));	
    add_act("worry");
    add_act("get all from corpse");
    add_act("sigh");
    add_act("pace");		
    add_act("peer");		
    add_act("jump");		
    add_act("emote looks nervously in the direction of the river.");		
    add_act("emote stands very still, listening for signs of trouble.");		
    add_act("emote searches the ground for something to sharpen weapons with.");
    add_act("emote carefully inspects you for signs of mischief.");		
    add_act("emote glances warily at you, wondering if you are friend or foe.");	


    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("emote stands tall in defence of the village."); 
    add_cact("scowl"); 
    add_cact("frown"); 
    add_cact("grumble"); 

    return 1;
}

void
do_die(object killer)
{
    object room;
    
    room = ENV(TO);
    room->replace_humans(0);


    tell_room(ENV(TO), "The human crumples to the ground, one "
        + "less defender against the invading orcs.\n");

    ::do_die(killer);
}

