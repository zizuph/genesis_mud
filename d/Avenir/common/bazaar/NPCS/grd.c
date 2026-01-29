// Wandering guards for the bazaar area.
// creator(s): Ilyian, May 1995
// purpose: To serve and to protect
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster.c";
inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/trigaction";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/include/relation.h"
#include <language.h>
#include <money.h>
#include </sys/ss_types.h>

int alarm_id;
string *randadjl;
string *randadjs;
void set_helper();

void
create_monster()
{
    if (!IS_CLONE)
        return;

    randadjl = ({"red-bearded", "ugly", "large", "swarthy", "blue-eyed",
                 "short", "stumpy", "long-haired", "slender", "squat",
                 "black-bearded", "short-legged", "brown-haired",
                 "long-nosed", "pale", "bandaged", "slim", "dark" });

    randadjs = ({"angry", "menacing", "brutal", "fierce", "calm",
                 "flustered", "efficient", "trustworthy", "jovial", 
                 "mean", "anti-social", "friendly", "ill-tempered",
                 "sad", "gruff", "gentle"});

    ::create_monster();
    set_name("guard");
    add_name("avenir_dwarf_id");  // like the ones at the outpost....
    add_name(({"peace keeper", "peacekeeper"}));
    set_race_name("dwarf");
    set_gender(G_MALE);
    set_adj(randadjl[random(sizeof(randadjl))]);
    add_adj(randadjs[random(sizeof(randadjs))]);

    set_long("This is one of the town guards, who walks around the " +
        "Bazaar making sure all is in order, and that orders "+
        "are obeyed.\n");

    set_stats(({ 40+random(60), 85+random(15), 40+random(50),
                 30+random(50), 30+random(50), 30+random(50) }));
    set_stat_extra(5, 50);
    set_skill(SS_WEP_SWORD, 60 + random (30));
    set_skill(SS_DEFENCE, 60 + random (30));
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_WEP_AXE, 60 + random (30) );
    set_skill(SS_WEP_POLEARM, 60 + random (30) );
    set_skill(SS_BLIND_COMBAT, 50 );
    set_scar(random(20));
    refresh_mobile();
    set_random_move(5);

     add_prop(NPC_I_NO_FEAR, 1);
    add_prop("_live_i_attack_thief", 1);
    NEVERKNOWN;
    set_chat_time(3 + random(3));
     add_chat("I eviscerated the last thief I found...");
     add_chat("...and I fed his thieving fingers to his children.");
     add_chat("Nygel made a balloon figure from his intestines.");
     add_chat("You're welcome here so long as you've coppers to spend.");
     add_chat("Be on your way.");
     add_chat("This shift lasts too long.");
     add_chat("If we get anymore tent shops, we're going to have "+
         "to increase our security.");
     add_chat("The baker is complaining that the infidels are "+
         "stealing food from her again.");
     add_chat("Almost quitting time!");

    set_act_time(5 + random (6));
     add_act("grin slow");
     add_act("emote wipes some sweat from his brow.");
     add_act("growl .");
     add_act("yawn");
     add_act("stretch");
     add_act("frown thought");
     add_act("emote paces back and forth.");
     add_act("peer at hobbit");
     add_act("emote stares up at the Source for a moment.");
     add_act("point at human");
     add_act("whisper avenir_dwarf_id Thats the one they warned us about.");
     add_act("ask punisher Now? Should we do it now?");
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

    set_helper();
}


void
arm_me()
{
    int which_weapon;
    refresh_living();

    which_weapon = random(2);
    if (which_weapon)
        clone_object (BAZAAR + "Obj/wield/gaxe")->move(this_object());
    else
        clone_object (BAZAAR + "Obj/wield/gsword")->move(this_object());
    command ("wield all");

    clone_object(BAZAAR + "Obj/worn/armour") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/bracers") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/helm") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/belt") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/boots") -> move(TO, 1);
    command("wear all");
}
void equip_me(){    arm_me();    }

void set_helper()
{
    string *actions = ({"shout Guards! Help me!",
                        "shout Hold strong! I'm coming!",
                        "say Your blood will stain my boots.",
                        "say You will die for this!"});

    set_helper_friends( ({}) );
    set_helper_actions( actions );
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i = random(10);
    alarm_id = 0;

    if (!present(tp, environment(TO)))
        return;

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 2)
            command("bow deep "+ tp->query_real_name());
        if (i == 4)
            command("say to "+ tp->query_real_name() +" I am "+
                "honoured by your presence!");
        if (i == 6)
            command("say to "+ tp->query_real_name() +" I can "+
                "assure you that everything is under control.");
        return;
    }
    if (IS_INFIDEL(tp))
    {        
        if (i < 6)
        {
            command("emote squints at you.");
            command("shout Infidel!");
            command("kill "+ tp->query_real_nme());
        }
        return;
    }    
    if (IS_DANCER(tp))
    {
        if (i == 0)
            command("whistle admir "+ tp->query_real_name());
        if (i == 3)
            command("ask "+ tp->query_real_name() +
                " I'm off-duty in a couple hours. Will you"+
                " honour me with your presence?");
        if (i == 6)
            command("bow gallant to "+ tp->query_real_name());
            return;
    }       
    else
    {
        if (i == 5)
            command("say to "+ tp->query_real_name() + " "+
               "Welcome to the Sybarus Bazaar, Outlander.");
        if (i == 7)
            command("say to "+ tp->query_real_name() + " "+
               "Spend your coppers in peace.");
        if (i == 9)
            command("say to "+ tp->query_real_name() + " "+
               "All are welcome who respect the peace.");
            return;
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        if (alarm_id)
            return;
        alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
    }
}  

