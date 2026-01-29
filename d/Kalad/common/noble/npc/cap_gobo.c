/* 
 * /d/Kalad/common/noble/npc/cap_gobo.c
 * Purpose    : The captured goblin, must free him for a quest
 * Located    : /d/Kalad/common/noble/alexander/
 * Created By : Sarr ??.??.95
 * Modified By: Fysix, 2-98, recoded
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "default.h"
#include "/d/Kalad/sys/guild.h"

void
create_kalad_monster()
{
    set_name("tahkgris");
    set_adj("bruised");
    add_adj("bloodied");
    set_race_name("goblin");
    set_short("bruised bloodied goblin");
    set_long("This wretched goblin is covered with bruises and open "+
        "cuts and soars. His eyes are slightly unfocused, and is dripping "+
        "with sweat. He is chained to the wall.\n");
    add_prop(NPC_I_NO_RUN_AWAY,1);
    set_skill(SS_DEFENCE,50);
    set_stats(({110,60,100,70,70,70}));
    heal_hp(-500);

    set_act_time(5);
    add_act("moan");
    add_act("say I will...nn...never...tell....");
    add_act("emote coughs up some blood.");
    add_act("emote chokes up some blood.");
    add_act("emote groans and wheezes.");

    set_title("the Fierce Lieutenant of the Red Fang");

    set_default_answer(VBFC_ME("check_player"));
    add_speak("They'll never get the item from me...\n");
    add_ask(({"map","item"}),VBFC_ME("check_player_item"));
    add_ask(({"escape","chains","chain"}),VBFC_ME("check_player_esc"));
}

int
do_unchain(string str)
{
    object gob,key,guard;

    NF("Unchain who?\n");
    if(!parse_command("unchain "+str,ENV(TP),"'unchain' %o",gob))
        return 0;
    if(gob != TO)
        return 0;
    key = present("_kalad_free_goblin_quest_",TP);
    if(!key)
    {
        write("You don't have the right key.\n");
        return 1;
    }
    write("You unchain the "+short()+" using the "+key->short()+".\n");
    say(QCTNAME(TP)+" unchains the "+short()+" using the "+key->short()+
    ".\n");
    if(guard = present("guard",ENV(TO)))
    {
        guard->command("shout Hey!");
        guard->command("kill "+lower_case(TP->query_name()));
    }
    set_alarm(2.0,0.0,"free_goblin",TP);
    return 1;
}

void
free_goblin(object ob)
{
    if (ob->query_guild_name_race() == THANAR_GUILD_NAME)
    {
        command("say Thanks a lot, stupid Thanar!");
        command("laugh "+ob->query_name());
        command("climb out the window");
        remove_object();
        return;
    }
    ob->add_prop("_kalad_free_goblin_quest",1);
    command("say Thank you sir!");
    command("whisper to "+lower_case(TP->query_name())+
    " The key is under a flagstone in the High-Lords' castle, near "+
    "the grand staircase. Take that key, and find Seargent Khraal. "+
    "He will know what to do from there.\n");
    command("finger guard");
    command("climb out the window");
    remove_object();
    return;
}


int
do_slap(string str)
{
    object gob;
    if(!parse_command("slap "+str,ENV(TP),"'slap' %o",gob))
        return 0;
    if(gob != TO)
        return 0;
    write("You slap the "+short()+" hard with the back of your "+
    "hand, splattering blood against the wall.\n");
    say(QCTNAME(TP)+" slaps the "+short()+" hard with the back of "+
    HIS(TP)+" hand, splattering blood against the wall.\n");
    command("emote screams in pain.");
    TP->command("grin sad");
    return 1;
}

int
do_beat(string str)
{
    object gob;
    if(!parse_command("beat "+str,ENV(TP),"'beat' %o",gob))
        return 0;
    if(gob != TO)
        return 0;
    write("You beat on the "+short()+" with anger, pounding and "+
    "kicking him until he pukes out blood.\n");
    say(QCTNAME(TP)+" beats on the "+short()+" with anger, pounding "+
    "and kicking him until he pukes out blood.\n");
    command("emote wails and gurgles up blood on the floor.");
    TP->command("laugh sad");
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(do_beat, "beat");
    add_action(do_unchain, "unchain");
    add_action(do_slap, "slap");
}

string
check_player_esc()
{
    if (TP->query_guild_name_race() == FANG_GUILD_NAME)
        return "The "+short()+" mumbles: Yes brother...if you "+
       "can just get the key from Lord Alexander's goons, you "+
       "can unchain me, and we can head back to our home.\n";
    if (TP->query_guild_name_race() == THANAR_GUILD_NAME)
        return "The "+short()+" mumbles: Yes...just give me the "+
        "key, and I will reward you with all the gold you want!\n";

    return "The "+short()+" mumbles: Please...Lord Alexander's "+
    "goons have the key. Just get it, and unchain me, and we can go find "+
    "the map!\n";
}

string
check_player_item()
{
    if (TP->query_guild_name_race() == FANG_GUILD_NAME)
        return "The "+short()+" mumbles: The Thanar....they are after "+
        "a map I found that shows the way through the sewers to their secret "+
        "underground hideout. Help me escape, retrieve the map, and get "+
        "it back to Brutakis, and you will be greatly rewarded!\n";
    if (TP->query_guild_name_race() == THANAR_GUILD_NAME)
        return "The "+short()+" spits in your face.\n";
    return "The "+short()+" mumbles: The Thanar..they are after "+
     "a map I found that shows the way to their secret underground "+
     "hideout. If you can help me escape, get the map, and take it "+
     "to Brutakis, our leader of the Red Fang, you will be "+
     "greatly rewarded!\n";
}


string
check_player()
{
    if(TP->query_race_name() == "goblin" && TP->query_guild_name_race() ==
       FANG_GUILD_NAME)
        return "The "+short()+" mumbles: I'm not sure what you mean, "+
        "brother...but I can tell you about the item if you like.\n";
    if(TP->query_race_name() == "goblin")
        return "The "+short()+" mumbles: I'm not sure what you are talking "+
        "about goblin...\n";
    if(TP->query_guild_name_race() == THANAR_GUILD_NAME)
        return "The "+short()+" stares at you with hatred in its black "+
        "eyes.\nThe "+short()+" hisses: I have nothing to tell you, Thanar!\n";
    return "The "+short()+" mumbles: Wha...? Eh?\n";
}
