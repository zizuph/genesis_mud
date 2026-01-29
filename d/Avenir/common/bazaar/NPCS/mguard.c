
// Guards for the bazaar area.
// These are the ones who man the pillory on the hill with
//  Jadestone Doll.
// creator(s): Ilyian, May 1995
// purpose: To serve and to protect
// note: Modified by Mortricia, Oct 1995, to get the capturing work
// Revisions: Lilith May 2022: removed down-exit block. Removed
//        the call_for_help as they are the ones called.
// bug(s):
// to-do:  

inherit "/d/Avenir/inherit/monster.c";
inherit "/d/Avenir/inherit/helper";
// These are the ones called for help.
// inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/trigaction";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include <language.h>
#include <money.h>
#include </sys/ss_types.h>
#include <tasks.h>

string *randadjl;
string *randadjs;

void lock_the_pillory(object key);

void
create_monster()
{
    if(!IS_CLONE)
       return;

    randadjl = ({"gruff", "ugly", "large", "swarthy", "blue-eyed",
                 "short", "stumpy", "long-haired", "slender", 
                 "black-bearded", "short-legged", "brown-haired",
                 "long-nosed"});

    randadjs = ({"angry", "menacing", "brutal", "fierce", "calm", 
                 "unhappy", "jovial", "sad", "mean"});

        ::create_monster();

        set_name("guard");
        add_name("avenir_dwarf_id");  // like the ones at the outpost....
        set_race_name("dwarf");
        set_gender(G_MALE);
        set_adj(randadjl[random(sizeof(randadjl))]);
        add_adj(randadjs[random(sizeof(randadjs))]);

        set_long("This is one of the town guards, who walks around the " +
                "bazaar making sure all is in order, and that orders "+
                "are obeyed.\n");

        set_stats(({ 80+random(20), 90+random(20), 80+random(30),
                     50+random(10), 50+random(10), 80+random(30) }));

        set_skill(SS_WEP_SWORD, 100);
        set_skill(SS_DEFENCE, 60 + random (30));
        set_skill(SS_AWARENESS, 50);
        set_skill(SS_WEP_AXE, 100);
        set_skill(SS_WEP_POLEARM, 95);          
        set_skill(SS_BLIND_COMBAT, 50 );

     add_prop(NPC_I_NO_FEAR, 1);
     add_prop("_live_m_attack_thief", 1);
     NEVERKNOWN;

        set_act_time(5 + random (6));
     add_act("grin evilly");
     add_act("emote wipes some sweat from his brow.");
     add_act("growl .");
     add_act("yawn");
     add_act("stretch");
     add_act("emote paces back and forth.");
     add_act("peer hobbits");
     add_act("emote stares up at the source for a moment.");
     add_act("point human");
     add_act("whisper avenir_dwarf_id Thats the one they warned us about.");
     add_act("ask punisher Now? Should we do it now?");
     add_act("say What are you doing here?");
     add_act("say Be on your way.");
     add_act("say Bloody peasant scum.");
     add_act("say This shift lasts too long.");
     add_act("twirl sword");
     add_act("swing axe");

        set_cact_time(9 + random (20));
     add_cact("snicker");
     add_cact("spit enemy");
     add_cact("scream");
     add_cact("fume .");
     add_cact("glare angr enemy"); 
     add_cact("say The Punisher will take care of scum like you!");
     add_cact("twirl sword");
     add_cact("swing axe");
}

int special_attack(object enemy)
{
    ENV(TO)->being_killed(enemy);
    return 0;
}

/*  Bouncing attacks doesn't really work anymore. Removing.-Lilith.
void init_living()
{
   ::init_living();
   add_action("down","down");
}

int down(string str)
{
   if(query_attack() != TP || !interactive(TP) || !CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
    return 0;

   if(TP->resolve_task(TASK_DIFFICULT, ({TS_DEX, SS_SNEAK, SS_DEFENCE }), TO, ({TS_DEX}) ) > 0 )
      return 0;

   command("say Where the hell do you think you are going, "+TP->query_race_name()+"?");
   TP->catch_msg(QCTNAME(TO)+" blocks your way down.\n");
   say(QCTNAME(TO)+" blocks "+QTNAME(TP)+" retreat.\n");
   return 1;
}
*/
void
arm_me()
{
    object key;
    int which_weapon;

    seteuid(getuid());
    key = clone_object(BAZAAR + "Obj/misc/stockade_key");
    key -> move(TO);
/*    environment(TO)->lock_and_close(TO, key); */
    set_alarm(10.0, -1.0, "lock_the_pillory", key);


    which_weapon = random(2);
    if (which_weapon)
        clone_object (BAZAAR + "Obj/wield/gaxe")->move(this_object());
    else
        clone_object (BAZAAR + "Obj/wield/gsword")->move(this_object());
    command ("wield all");

    clone_object(BAZAAR + "Obj/worn/cloak") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/armour") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/bracers") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/helm") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/belt") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/codpiece") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/boots") -> move(TO, 1);
    command("wear all");
}

void lock_the_pillory(object key)
{
    environment(TO)->lock_and_close(TO, key);
}
