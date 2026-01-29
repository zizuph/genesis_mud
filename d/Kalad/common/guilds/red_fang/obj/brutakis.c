/* 
 * /d/Kalad/common/wild/pass/goblin/guild/brutakis.c
 * Purpose    : Joinroom NPC, also rewards quest
 * Located    : Joinroom of the Red Fang
 * Created By : Sarr  ??.??.??
 * Modified By: Sarr 17.Apr.97
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"

#define QUEST "noble_keyquest"


void
create_monster()
{
    ::create_monster();
    set_name("brutakis");
    set_race_name("goblin");
    set_adj("grim");
    add_adj("battle-scarred");
    set_short("grim battle-scarred goblin");    
    set_long("This huge goblin looks down on you. His bulging muscles, fierce "+
    "blazing red eyes, and many battle scares mark him as veteran "+
    "warrior, one which you would not want to mess with. An aura of "+
    "great power surrounds him.\n");
    set_stats(({160,120,160,100,100,160}));
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_SNEAK,50);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_title("the Feared Supreme General of the Red Fang");
    set_act_time(6);
    add_act("emote growls something.");
    add_act("emote spits on the ground in hatred of human scum.");
    add_act("emote growls: That stupid Nomog has no idea what he "+
    "is doing!");
    add_act("emote stares at some maps.");
    add_prop(OBJ_M_NO_ATTACK,"Are you MAD? He would kill you in the "+
    "blink of an eye!\n");
    add_ask(({"guild","red fang","army"}),"Brutakis growls: "+
    "So, you want to join us eh? Well first read this book on the "+
    "table before you decide.\n"+
    "If you decide to join, just sign your name in.\n");
    set_default_answer("Brutakis growls: What? Don't bother me with "+
    "that garbage! I have more important things to do!\n");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

void
enter_inv(object ob, object from)
{
    if(MASTER_OB(ob) == "/d/Kalad/common/noble/obj/quest_map")
    {
        if(from->query_prop("_kalad_free_goblin_quest"))
        {
            set_alarm(3.0,0.0,"reward_map",TP,ob);
        }
        else
            command("drop "+ob->query_name());
    }
    else
        if(!ob->query_prop("kakaka"))
            if(!ob->id("_fang_"))
                command("drop "+ob->query_name());
}

void
reward_map(object ob, object map)
{
    object bad,obad;
    seteuid(getuid());
    if(ob->query_guild_name_race() == "Thanarian human race guild")
    {
        command("say Thank you, scum. Now get out of here!");
        command("laugh .");
    }
    if(ob->query_guild_name_race() == "Red Fang Guild")
    {
        if(ob->test_bit("Kalad",1,14))
            command("say Thank you again, brother!");
        else
        {
            command("emote salutes you sharply.");
            command("say You have done a great service to the "+
            "Red Fang.");
            command("say You will be honored among us.");
            bad = clone_object("/d/Kalad/common/guilds/red_fang/obj/fh_badge");
            obad = present("_fang_",TP);
            command("emote removes your "+obad->short()+".");
            obad->remove_object();
            bad->move(TP);
            command("emote gives you the "+bad->short()+".");
            TP->add_exp(5000);
            tell_object(TP,"You feel more experienced.\n");
            ob->set_bit(1,14);
            tell_object(TP,"You have been promoted a level in "+
            "the Red Fang.\n");
            command("shout Hail Red Fang! Rulers of Kalad!");
            log_file(QUEST, extract(ctime(time()),4,15) + " "+
           capitalize(TP->query_real_name()) + " rewarded by brutakis with 5000 xp,"+
               "<"+TP->query_average_stat()+"> average stats.\n");
         }
    }
    if(ob->query_race_name() == "human")
    {
        if(ob->test_bit("Kalad",1,14))
            command("say Hmm...thank you again, strange human.");
        else
        {
            command("peer "+ob->query_name());
            command("say Why have you helped us human?");
            command("say I do not understand....");
            command("say But, you have served us nevertheless.");
            TP->add_exp(5000);
            tell_object(TP,"You feel more experienced.\n");
            ob->set_bit(1,14);
            command("thank "+lower_case(ob->query_name()));
             log_file(QUEST, extract(ctime(time()),4,15) + " "+
           capitalize(TP->query_real_name()) + " rewarded by brutakis with 5000 xp,"+
               "<"+TP->query_average_stat()+"> average stats.\n");
         }
    }
    if(ob->query_race_name() == "goblin" && ob->query_guild_name_race() !=
    "Red Fang Guild")
    {
        if(ob->test_bit("Kalad",1,14))
            command("say Thank you again.");
        else
        {
            command("say Thank you, brother goblin.");
            command("say You have done a great deed for us.");
            command("say It is a strange wonder than you have not "+
            "joined us yet.");
            TP->add_exp(5000);
            tell_object(TP,"You feel more experienced.\n");
            ob->set_bit(1,14);
            command("thank "+lower_case(ob->query_name()));
         }
    }
    if(ob->query_race_name() != "human" && ob->query_race_name() != "goblin")
    {
        if(ob->test_bit("Kalad",1,14))
            command("say Thank you again.");
        else
        {
            command("say Thank you, "+ob->query_race_name()+".");
            command("say It is nice to see us demi-humans begining "+
            "to work together against these foul humans.");
            command("say I begin to see that it may be the only way "+
            "for our survival in the end....");
            TP->add_exp(5000);
            tell_object(TP,"You feel more experienced.\n");
            ob->set_bit(1,14);
            command("thank "+lower_case(ob->query_name()));
         }
    }
    map->remove_object();    
}        

void
arm_me()
{
    object wep,arm;
    seteuid(getuid(TO));
    wep = clone_object(FANG_DIR(obj/f_sword));
    wep->add_prop("kakaka",1);
    arm = clone_object(FANG_DIR(obj/f_armour2));
    arm->add_prop("kakaka",1);
    wep->move(TO,1);
    arm->move(TO,1);
    wep = clone_object(NOBLE(arm/pierce3));
    wep->add_prop("kakaka",1);
    arm = clone_object(NOBLE(arm/pair_rings));
    arm->add_prop("kakaka",1);
    wep->move(TO,1);
    arm->set_ring_metal("black-steel");
    arm->set_ring_metal("wolf-shaped bloodstone",1);
    arm->move(TO,1);
    arm = clone_object(FANG_DIR(obj/f_badge));
    arm->move(TO,1);
    command("wear all");
    command("wield all");
    command("wear badge");
    command("insert rings in both ears");
}
