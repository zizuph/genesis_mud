//-*-C++-*-
// file name:     
// creator(s):    Lilith   01/26/97
// purpose:       Hunted; infidels
// note:          This file acts like 15 different npcs.
// last update:   Lilith   04/05/97
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster";

#include "/d/Avenir/include/relation.h"
#include "../holm.h"

#include <ss_types.h>
#include <language.h>

mixed *everyone = ({
    ({ "human",    ({ "emaciated", "filthy"}),     random(20) + 80, 
       "dark-brown",  "a matted mess", G_MALE }), 
    ({ "human",    ({ "frowning", "injured"}),     random(20) + 80, 
       "angry blue",  "in a top-knot", G_FEMALE }), 
    ({ "human",    ({ "grimacing", "crooked"}),     random(20) + 80, 
       "dark green",  "completely shaved off", G_MALE }), 
    ({ "gnome",    ({ "sad-faced", "limping" }),   random(20) + 60, 
       "medium brown", "covering most of her face", G_FEMALE }),
    ({ "gnome",    ({ "hairy", "deep-chested" }),   random(20) + 60, 
       "serene blue", "wildly tangled", G_MALE }),
    ({ "gnome",    ({ "one-armed", "ragged" }),    random(20) + 60, 
       "almost black", "shaved on the left side", G_MALE }),
    ({ "goblin",   ({ "shaggy", "pale-furred"}),   random(20) + 90,
       "the dull grayness of stone", "matted with filth", G_MALE }),
    ({ "goblin",   ({ "limping", "full-lipped"}),  random(20) + 85,
       "vacant and flat", "unravelling from its braid", G_FEMALE }),
    ({ "goblin",   ({ "broken-nosed", "scarred"}),   random(20) + 90,
       "queerly unfocused", "jumping with fleas", G_MALE }),
    ({ "dwarf",    ({ "one-eyed", "frightened" }), random(20) + 70, 
       "blue-black",  "braided and tied with sinew", G_MALE }),
    ({ "dwarf",    ({ "breathless", "grinning"}),  random(20) + 70, 
       "wide and black as deep pits", "matted with dirt", G_MALE }),
    ({ "elf",      ({ "grey-haired", "angry" }),   random(20) + 90, 
       "coal-black",  "black and surprisingly clean", G_MALE }),
    ({ "elf",      ({ "cold-eyed", "muscular" }),  random(20) + 90, 
       "steel-gray",  "tied in one long braid", G_FEMALE }),
    ({ "half-elf", ({ "desperate", "scarred" }),   random(20) + 90, 
       "dark gray",   "tangled and dirty", G_MALE }),
    ({ "half-elf", ({ "alert", "lithe" }),         random(20) + 90, 
       "terrifyingly black",   "auburn and tied back", G_MALE }),
});

string eyes, hair;
string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
void set_eyes(string str)   {    eyes = str;      }
void set_hair(string str)   {    hair = str;      }
string my_long();
int alarm_id;

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
    set_adj(someone[1]);    
    default_config_npc(someone[2]);    
    set_eyes(someone[3]);
    set_hair(someone[4]);
    set_gender(someone[5]);
}

/* Create the npc */
void
create_monster()
{
    set_morph(random(sizeof(everyone)));
    set_name("infidel");
    set_long(my_long);
    add_name(({"blasphemer", "prey", "hunted"}));
    set_alignment(0);

    set_knight_prestige(100);   

    MAKE_INFIDEL;
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

    set_restrain_path(({"/d/Avenir/common/holm", "/d/Avenir/common/park"}));
    set_monster_home("/d/Avenir/common/holm/jungle/lf13");
//    set_random_move(20, 0);

    set_act_time(10);
      add_act("sigh .");
      add_act("smile grim");
      add_act("emote breathes heavily.");
      add_act("emote fidgets nervously.");
      add_act("say I'm thirsty, but I dare not drink from the stream.");
      add_act("emote looks as though "+ PRONOUN(TO) +" is prepared "+
          "to flee at the slightest aggressive movement from you.");
      add_act("say Me either.");
      add_act("emote looks at you from the corner of "+ POSSESS(TO) +
          " eyes.");
    set_cact_time(7);
      add_cact("glare mercilessly enemy");
      add_cact("say When this Hunt is finished, who will remain "+
          "standing?");
      add_cact("say Flee from me and I will not follow. Your cowardice "+
          "will be greater even than my shame!");
      add_cact("say From whence thou came, so shall I return you.");
      add_cact("say Your blood and bones will feed this fertile soil.");
      add_cact("say I will feast upon your heart and piss upon your "+
          "corpse!");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"Hunt", "Hunting", "hunt", "hunting"}), VBFC_ME("hunt_ask"));
    add_ask(({"Rule", "rule" }), VBFC_ME("rule_ask"));
    add_ask(({"aclolthayr"}), VBFC_ME("aclo_ask"));
    add_ask(({"bath", "melchior's bath", "bathhouse"}),
        "say There is a bathhouse in the City. I won't be visiting "+
        "it again in this life.",1);
    add_ask(({"sybarus","bazaar"}),
        "say Its the main island, over yonder.",1);
    add_ask("city", "say You won't get anything from me!",1);
    add_ask(({"task", "job", "quest", "help"}),  VBFC_ME("give_task"));
    add_ask(({"infidel","infidels", "shame"}),
        "say I am one who is without rank, less than a slave. My only "+
        "redemption is to provide a good Hunt, and die. Only then will "+
        "Mascarvin welcome me into the afterlife, where I will nurse at "+
        "her paps until it is time for rebirth into a better life.", 1);
    add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
        "say Sybarites are the Faithful. Sybarites live to serve and "+
        "uphold the Pact, that the Source will always cast its illum"+
        "ination upon us.",1);
    add_ask(({"hizarbin", "omatu", "omatu hizarbin"}), 
        "say He is Omatu Hizabin, Lord of the Waters. "+
        "He is also the generous patron of fishermen and sailors.", 1);
    add_ask(({"sachluph", "mother"}),
        "say Sachluph shares the Eleventh hour with her "+
        "consort, Hizarbin. She is a great Lady of herbs, healing "+
        "and poison.", 1);
    add_ask(({"water", "whirlpool","stream", "pool", "sea" }),
        "say 'Ware sampling the waters without leave, for you may risk"+
        " Hizarbin's wrath. I've heard some have drowned in the "+
        "stream at the foot of the Spire.", 1);
    add_ask(({"wrath", "drown" }), "say Those who enter the waters "+
        "without leave are doomed to drown.", 1);
    add_ask(({"blessing", "leave" }), "say I have heard it rumoured "+
        "that if you make an offering at one of Hizarbin's altars, "+
        "and it is accepted, you will be blessed.", 1);

}

string
my_long()
{
    string  str, poss;
    poss =TO->query_possessive(); 

    str =  capitalize(TO->query_pronoun()) +" is "+ 
           LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += capitalize(TO->query_pronoun()) +" is "+ 
           "an infidel, banished to this island to be predator "+
           "and prey in the Hunt.\n"+ 
           capitalize(poss) +" hair is "+ query_hair() +".\n"+
           capitalize(poss) +" eyes are "+ query_eyes() +".\n";
    return str;
}

/*
 * equip_me is called in the npc when it is cloned by the 
 * placer module.
 */
void 
equip_me()
{
    object dagger;

    dagger = clone_object("/d/Avenir/common/obj/knife");
    dagger->move(TO);
    dagger = clone_object("/d/Avenir/common/obj/knife");
    dagger->move(TO);    
    command("wield all");
}

/* **** add_ask answers, including quest assignment, if any **** */
string 
aclo_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote trembles with fear.");        
        return "";
    }
    command("say to "+ TP->query_real_name() +
        " Aclolthayr is the patron goddess of the Hunt.");
        return "";
}
          
string
hunt_ask()
{
    if (IS_SYBARITE(TP) && CAN_SEE(TO, TP))
    {
        command("say to "+ TP->query_real_name() +
            " Are you on a Hunt?");
        command("say to "+ TP->query_real_name() +
            " If you're looking for prey, you're going to "+
            "find that I can put up quite a fight.");
        command("grin");
        return "";
    }
    if (CAN_SEE(TO, TP)) 
    {
        command("say to "+ TP->query_real_name() +
            " A true Hunt involves intelligent prey.");
        command("say to "+ TP->query_real_name() +
            " There is only one rule on the Holm: Everyone and "+
            "everything is fair game.");
        command("say to "+ TP->query_real_name() +
            " So you had best be careful, Outlander.");
        return "";
    }
    command("say The air speaks!");
    command("emote trembles fearfully.");
    return "";
}    

string
rule_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote trembles with fear.");        
        return "";
    }
    command("say to "+ TP->query_real_name() +
        " A true Hunt involves intelligent prey.");
    command("say to "+ TP->query_real_name() +
        " So there is only one rule on the Holm: Everyone and "+
        "everything is fair game.");
    command("say to "+ TP->query_real_name() +
        " If you're looking for prey, you're going to find "+
        "that I can put up quite a fight.");
    return "";
}

string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks fearfully about.");        
        return "";
    }
    command("say to "+ TP->query_real_name() +
        " Why bother me with such nonsense! I've better "+
        "things to do...Like getting through the day with my "+
        "heart still in my chest.");
    return "";
}
string
give_task()
{
    command("sigh");
    command("say What task could I possibly give you?");
    command("say There is no guarantee I will live out the "+
        "hour, so how could I possibly reward you?");
    return "";

}


/* **************** Used in Special Attack function  *************** */

void
herb_heal()
{
    object ob;
    int i, herb;
    seteuid(getuid());
    
    i = random(10);
    herb = 1;

    if (i > 7 && herb < 10)
    {
        ob = clone_object(HERB +"carlith");
        ob->move(TO);
        TO->command("eat herb");
        herb++;
    }
}

/* ***************** Punch attack ******************* */
void
punch_em(object victim)
{

    if (victim->query_not_attack_me(TO, -1))
    {
        return;
    }


    int hit = (random(10) + 30);
    int how;
    string *randhit = ({"face", "head", "nose", "eye", "chest"});
    mixed where;

    how = (random(sizeof(randhit)));    
    where = randhit[how];

    victim->catch_msg(QCTNAME(TO)+" dodges under your guard and gives "+
       "you a quick double-punch in the " + where +".\n");
    tell_room(ENV(TO), QCTNAME(TO)+" dodges under "+ QCTNAME(victim) + 
       "'s guard and gives "+ victim->query_objective() +" a quick "+
       "double-punch to the "+ where +"!\n", victim);
    victim->heal_hp(-hit);
}


int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
	return 1;
    }

    switch (random(4))
    {
        case 0: punch_em(victim);
            return 1;
        case 2: herb_heal();
            return 0;
        default: 
    }
    return 0;
}


void
too_small(object tp)
{
    if (!present(tp, environment(TO)))
        return;

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        command("say to "+ tp->query_real_name() +
            " You're too small to be a threat to me, but others might "+
            "not be so kind. You'd better leave the Holm, before you "+
            "die.");
    }
}    

void
check_meet(object tp)
{
    alarm_id = 0;

    if (!present(tp, environment(TO)))
        return;

    if (IS_SYBARITE(tp))
    {
        switch(random(10))
        {
            case 0:
            {
                command("say Justice be done! This day one of us "+
                    "will meet Mascarvin!");
                command("kill "+ tp->query_real_name());
            }
            break;
            case 1:
            {
                command("say Shall we commence the Hunt?");
                command("kill "+ tp->query_real_name());
            }
            break;
            case 2:
            {
                command("say I will assuage my shame with your "+
                    "blood upon my knife!");
                command("kill "+ tp->query_real_name());
            }
            break;
            case 3..9:
                command("kill "+ tp->query_real_name());
            break;
        }     
        return;
    }
    switch(random(15))
    {
        case 0:
        {
            command("say Today is a good day for you to die, Outlander!");
            command("kill "+ tp->query_real_name());            
        }
        break;    
        case 1:
        {
            command("say Knowingly or not, you have come upon your "+
               "place of death. May Mascarvin's Mercy permit the rebirth "+
               "of your soul!");
            command("kill "+ tp->query_real_name());            
        }
        break;           
        case 2:
        {
            command("say The Source burn your Outlander soul!");
            command("kill "+ tp->query_real_name());            
        }            
        break;    
        case 3:
        {
            command("say Ill was the wind that blew you my way!");
            command("kill "+ tp->query_real_name());            
        }
        break;
        case 4:
        {
            command("say I've better things to do than Hunt you. "+
                "There is a Sybarite Hunting me!");
        }
        break;
        case 5..14:
            command("kill "+ tp->query_real_name());
        break;
    }
    return;
}

void
init_living()
{
    ::init_living();

    if (TP->id("noble"))
    {
        run_away();
        run_away();
        return;
    }        
    if (alarm_id)
        return;
    if (TP->query_average_stat() < 40)
    {
        if (random(4))
            set_alarm(3.0, 0.0, &too_small(TP));
        return;
    }   
    if (interactive(TP) && CAN_SEE(TO, TP))
        set_alarm(2.0, 0.0, &check_meet(TP));
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
