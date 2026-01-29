// Stationary guards for the guardroom
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
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include <language.h>
#include <money.h>
#include </sys/ss_types.h>

int alarm_id;

string *randadjl;
string *randadjs;
void   set_helper();

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
                 "unhappy", "jovial", "sad", "mean", "bored"});

        ::create_monster();

        set_name("guard");
        add_name("avenir_dwarf_id");  // like the ones at the outpost....
        set_race_name("dwarf");
        set_gender(G_MALE);
        set_adj(randadjl[random(sizeof(randadjl))]);
        add_adj(randadjs[random(sizeof(randadjs))]);

        set_long("This is one of the town guards who is off-duty now. He "
                +"looks like he is rather bored.\n");

        set_stats(({ 80+random(20), 90+random(20), 80+random(30),
                     50+random(10), 50+random(10), 80+random(30) }));

        set_skill(SS_WEP_SWORD, 60 + random (30));
        set_skill(SS_DEFENCE, 60 + random (30));
        set_skill(SS_AWARENESS, 50);
        set_skill(SS_WEP_AXE, 60 + random (30) );
        set_skill(SS_WEP_POLEARM, 60 + random (30) );
        set_skill(SS_BLIND_COMBAT, 50 );

     NEVERKNOWN;
     add_prop(NPC_I_NO_FEAR, 1);

        set_act_time(5 + random (6));
     add_act("growl .");
     add_act("yawn");
     add_act("stretch");
     add_act("emote paces back and forth.");
     add_act("peer hobbit");
     add_act("point human");
     add_act("whisper avenir_dwarf_id Thats the one they warned us about.");
     add_act("say I'll be at the Bath soon.");
     add_act("say I'm almost happy the shift starts soon...");
     add_act("emote picks his teeth.");
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

arm_me()
{
    int which_weapon;

    which_weapon = random(2);
    if (which_weapon)
        clone_object (BAZAAR + "Obj/wield/gaxe")->move(this_object());
    else
        clone_object (BAZAAR + "Obj/wield/gsword")->move(this_object());

    command ("wield all");

  clone_object(BAZAAR + "Obj/worn/codpiece")-> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/armour") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/bracers") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/helm") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/belt") -> move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/boots") -> move(TO, 1);
    command("wear all");
}


void set_helper()
{
    string *actions = ({"shout You dare try killing me?",
                        "shout Where?",
                        "say You will die for this!"});

    set_helper_friends( ({"guard"}) );
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
               "We are resting. You should leave.");
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

