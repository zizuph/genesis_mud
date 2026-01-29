//-*-C++-*-
// file name:     
// creator(s):    Lilith   12/01/2001
// purpose:       Prisoner in the Kestares.  Quest npc.
// note:          
// last update:   
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/log_asks";
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/common/bazaar/admin/admin.h"

#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

string my_long();

/* Create the npc */
void
create_monster()
{
    set_race_name("gnome");
    set_adj("hobbled");
    add_adj("adolescent");
    default_config_npc(random(20) + 80);    
    set_gender(G_MALE);
    set_name("norlayo");
    add_name("prisoner");
    set_long(my_long);
    set_alignment(0);
    add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);
    add_leftover("/d/Avenir/inherit/leftover", "intestine",1, "", 0,0);    

    set_skill(SS_DEFENCE, random(20) + 40);
    set_skill(SS_2H_COMBAT, random(20) + 40);
    set_skill(SS_WEP_SWORD, random(20) + 40);
    set_skill(SS_AWARENESS, random(40)+ 20);
    set_skill(SS_WEP_KNIFE, random(20) + 40);
    set_skill(SS_BLIND_COMBAT, random(20)+ 10);
    set_skill(SS_SNEAK, random(20) + 25);
    set_skill(SS_HIDE, random(20) + 25);
    set_all_attack_unarmed(10, 10);
    set_all_hitloc_unarmed(15);

    set_act_time(10);
      add_act("sigh .");
      add_act("smile grim");
      add_act("emote breathes heavily.");
      add_act("emote fidgets nervously.");
      add_act("emote looks at you from the corner of "+ POSSESS(TO) +
          " eyes.");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"task", "job", "quest", "question", "statue", 
        "about statue"}), VBFC_ME("quest_ask"));

}

string
my_long()
{
    string  str, poss;
    poss =TO->query_possessive(); 

    str =  capitalize(TO->query_pronoun()) +" is "+ 
           LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += capitalize(TO->query_pronoun()) +" looks "+ 
           "dazed and not a little frightened.\n"+
           capitalize(TO->query_pronoun()) +" is considered "+
           "a criminal unless "+ TO->query_pronoun() +" can "+
           "convince an adjudicator otherwise.\n";
    return str;
}


string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks fearfully about.");        
        return "";
    }
    switch(random(4))
    {
        case 0:
            command("say Leave me alone, please!");
            break;
        case 1:
            command("say Mascarvin deny you rebirth!");
            break;
        case 2:
            command("slaugh");
            break;
        case 3:
            command("say Are you trying to get me killed?");
            break;
    }
    return "";    
}

void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    switch(random(6))
    {
        case 0:
            command("emote gurgles: I will be avenged");
            break;
        case 1:
            command("emote gurgles: Cowards kill those who cannot defend themselves.");
            break;
        case 2:
            command("emote struggles to speak. Blood bubbles from "+
                POSSESS(TO) +" lips, instead.");
            break;
        case 3:
            command("emote gets a glazed look in "+ POSSESS(TO) +
                " eyes.");
            command("emote whispers: I am ready Mascarvin.");
            break;
        case 4:
            command("emote writhes in agony.");
            break;
        case 5:
            command("emote gurgles: May my death anger the Gods, "+
                "that my death me avenged with your blood.");
            break;
        case 6:
            command("emote vomits blood.");
            break;
    }
    ::do_die(killer);
}

string 
query_exp_title()
{
    return "the sybarite "+ ::query_exp_title();
}

string 
quest_ask()
{
    int qnum;
    qnum = QNUM(TP);

    command("introduce myself");

    switch(qnum)
    {
        case 1: 
        {
            command("say Dibron is the most qualified.");
            command("say Maxild has never worked with statuary.");
            command("say Dibron's first statement is false.");
        }
            break;
        case 2:
        {
            command("say I do not have all the necessary tools.");
            command("say Dibron is the most qualified.");
            command("say Maxild is experienced in this type of work.");
        }
            break;
        case 3: 
        {
            command("say Dibron is the most qualified.");
            command("say Brum does not have all the necessary tools.");
            command("say I have never worked with statuary.");
        }
            break;
        case 4: 
        {
            command("say I am experienced with this type of work.");
            command("say Dibron is most qualified.");
            command("say Maxild does not have the necessary tools");
        }
            break;

        default: 
        {
            command("say For some reason the Gods will not let "+
                "me answer you.");      
            SCROLLING_LOG(K_ERR_LOG, 
            capitalize(TP->query_real_name()) +
            " had a bad quest number: "+qnum +
            " for Repair.");
            break;

        }
    }
    return "";
}
