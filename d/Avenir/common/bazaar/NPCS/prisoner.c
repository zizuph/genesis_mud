//-*-C++-*-
// file name:     
// creator(s):    Lilith   01/26/97
// purpose:       Hunted; infidels
// note:          This file acts like 15 different npcs.
// last update:   Lilith   04/05/97
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/log_asks";
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"

#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

string *s_adj1  = ({ "bound","shackled","restrained" });
string *s_adj2  = ({ "defiant","cowed","frightened","injured","ragged",
                     "guilty-looking","shamed","sad-faced","sobbing",
                     "stoic","merchant","adolescent","one-eyed", 
                     "scarred","scared","frowning","desperate" });
mixed *everyone = ({
    ({ "human",  random(20) + 80, G_MALE }), 
    ({ "human",  random(20) + 80, G_FEMALE }), 
    ({ "gnome",  random(20) + 60, G_MALE }),
    ({ "gnome",  random(20) + 60, G_FEMALE }),
    ({ "goblin", random(20) + 90, G_MALE }),
    ({ "goblin", random(20) + 85, G_FEMALE }),
    ({ "dwarf",  random(20) + 70, G_FEMALE }),
    ({ "dwarf",  random(20) + 70, G_MALE }),
});

string adj1, adj2;
string my_long();

/* 
 * set_morph sets the various attributes of the 
 * npc, making it unique 10 different ways.
 */
void
set_morph(int who)
{
    mixed someone;

    if (who < 0 || who >= sizeof(everyone))
       who = (random(sizeof(everyone)));

    someone = everyone[who];
    set_race_name(someone[0]);
    set_adj(s_adj1[random(sizeof(s_adj1))]);
    add_adj(s_adj2[random(sizeof(s_adj2))]);
    default_config_npc(someone[1]);    
    set_gender(someone[2]);
}

/* Create the npc */
void
create_monster()
{
    set_morph(random(sizeof(everyone)));
    set_name("prisoner");
    set_long(my_long);
    set_alignment(0);

    set_knight_prestige(100);   

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
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
            command("emote gurgles: I have provided a good chase...");
            break;
        case 1:
            command("emote gurgles: I have redeemed myself upon this Hunt.");
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
            command("emote gurgles: May my death appease the Gods, "+
                "that my shame be lifted from my House.");
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
    if (random(4))
        return "infidel";
    else
        return "sybarite";
}
