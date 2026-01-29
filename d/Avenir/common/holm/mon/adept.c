//-*-C++-*-
// Adept          /d/Avenir/common/holm/mon/adept
// creator(s):    Lilith    1/26/97
// revised:       Lilith    3/19/97
// purpose:       
// note:          
// bug(s):
// to-do:

#pragma strict_types

inherit "/d/Avenir/inherit/sybarite";
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/common/holm/holm.h"
#include "/d/Genesis/gems/gem.h"

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <filter_funs.h>

#define 
mixed *everyone = ({
    ({ "human", "emaciated", random(20) + 80, "grey-streaked",
       "the colour of iron", G_MALE }), 
    ({ "human", "portly", random(20) + 75, "sable brown",
       "cinnamon brown and veiled by long black lashes", G_FEMALE }),
    ({ "elf", "thoughtful", random(20) + 90, "black and silky",
       "keen as those of a bird of prey", G_MALE }), 
    ({ "elf", "pensive", random(20) + 85, "dark reddish brown",
       "expectant with an ironic eloquence", G_FEMALE }),
    ({ "half-elf", "youthful", random(20) + 100, "curly and golden brown",
       "wise beyond their years", G_MALE }),
    ({ "half-elf", "enigmatic", random(20) + 95, "black as soot",
       "dark with pain and apprehension", G_FEMALE }), 
    ({ "half-elf", "erudite", random(20) + 90, "the colour of honey", 
       "candid, yet tinged with deep sadness", G_MALE }),
    ({ "gnome", "merry", random(20) + 60, "wiry and brown as bark",
       "bright with excitement", G_FEMALE }),
    ({ "dwarf", "morose", random(20) + 70, "deep auburn",
       "dark with mysterious knowledge", G_MALE })
    });

string eyes, hair;
string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
void set_eyes(string str)   {    eyes = str;      }
void set_hair(string str)   {    hair = str;      }

string my_long();

/* 
 * set_morph sets the various attributes of the 
 * npc, making it unique.
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
    set_hair(someone[3]);
    set_eyes(someone[4]);
    set_gender(someone[5]);
}

/* Create the npc */
void
create_monster()
{
    /* If I'm not a clone, do not proceed */
    if (!IS_CLONE)
        return;

    /* Lets make sure the sybarite stuff is initialized */
    ::create_sybarite();    
    
    /* Now lets individualize it */
    set_morph(random(sizeof(everyone)));

    set_name("adept");
    set_long(my_long);
    add_name(({"sorcerer"}));
    add_adj("sagacious");
    set_alignment(0);
    set_knight_prestige(100);   

    set_skill(SS_DEFENCE, random(20) + 50);
    set_skill(SS_AWARENESS, random(20)+ 80);
    set_skill(SS_WEP_KNIFE, random(20) + 40);
    set_skill(SS_BLIND_COMBAT, random(20)+ 30);
    set_all_attack_unarmed(30, 35);
    set_all_hitloc_unarmed(10);

    if (random(3))
        add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);
    add_leftover("/d/Avenir/inherit/leftover", "hand",1, "", 0,0);
   
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 150);

    set_act_time(5);
      add_act("emote studies a scroll.");
      add_act("put potion in pack");
      add_act("emote handles something in a pouch.");
      add_act("close pack");
      add_act("emote turns the page of a spellbook.");
      add_act("open pack");
      add_act("emote seems to be reciting something under "+
          POSSESS(TO) +" breath.");
      add_act("emote frowns ferociously.");
    set_cact_time(7);
      add_cact("emote calls the wrath of Zaren down upon your head.");
      add_cact("emote shoots sparks at you from "+ POSSESS(TO) + 
          " fingertips.");
      add_cact("emote smiles secretively at you.");

    add_ask(({"Hunt", "Hunting", "hunt", "hunting"}), VBFC_ME("hunt_ask"));
    add_ask(({"Rule", "rule" }), VBFC_ME("rule_ask"));
    add_ask(({"aclolthayr"}), VBFC_ME("aclo_ask"));
    add_ask(({"bazaar"}), "say The only thing I consider to "+
        "be of interest is the apothecary there.", 1);
    add_ask(({"city", "sybarus","forbidden city"}),
        "say It is a wonderous place!", 1);
    add_ask(({"holm", "park"}), "say This is the Holm of the Icondite. "+
        "Everyone and everything on it is fair game. Including you.", 1);
    add_ask(({"task", "job", "quest", "help"}),  VBFC_ME("give_task"));
    add_ask(({"infidel","infidels"}),
        "say Infidels are dangerous. They put us all at risk with "+
        "their blasphemous ways!", 1);
    add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
        "say Sybarites are the Faithful. We live to serve and "+
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
    poss = TO->query_possessive();

    str =  capitalize(TO->query_pronoun()) +" is "+ 
           LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += "The very air around this person is charged with magic!\n"+
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
    object burnous, dagger, gem, pouch, potion;
    string *randpouch;
    string *randsigil;

    seteuid(getuid());

    burnous = clone_object(HOLM_OBJ + "burnous");
    burnous->move(TO);

    randsigil = ({ "red spider on a black field, bordered in purple",
        "brown flail on a solid blue field, bordered in red",
        "nightshade flower on a white field, bordered in green",
        "silver dagger on a field of yellow, bordered in purple",
        "green serpent on a field of brown, bordered in green" });
    dagger = clone_object(HOLM_OBJ + "dagger");
    dagger->set_sigil(randsigil[random(sizeof(randsigil))]);
    dagger->move(TO);
   
    gem = RANDOM_GEM(GEM_EXTREMELY_RARE);
    gem->move(TO);   

    potion = clone_object(POTION + "somnan");
    potion->move(TO);

    randpouch = ({ "/d/Avenir/common/bazaar/Obj/worn/pouch_belt",
                   "/d/Avenir/common/bazaar/Obj/misc/qarraba",
                   "/d/Avenir/common/bazaar/Obj/worn/neckpouch" });
    pouch = clone_object(randpouch[random(sizeof(randpouch))]);
    pouch->move(TO);

    command("wear all");
    command("wield all");
}

/* **** add_ask answers, including quest assignment, if any **** */
string 
aclo_ask()
{
    command("say Aclolthayr is the patron goddess of the Hunt.");
    command("say I've never Hunted, so I've had no occasion to "+
       "pay homage to her.");
        return "";

}
          
string
hunt_ask()
{
    command("say Are you on a Hunt?");
    command("say If so, I hope you'll pass me by. I won't "+
        "be very sporting prey.");
    return "";
}    

string
rule_ask()
{
    command("say A true Hunt involves intelligent prey.");
    command("say So there is only one rule on the Holm: Everyone and "+
        "everything is fair game.");
    return "";
}

string
give_task()
{
    command("hmm");
    command("say I can't think of anything at the moment.");
    return "";

}


/* **************** Used in Special Attack function  *************** */

int
give_potion()
{
    object apotion, spotion, lpotion;
    object *ob;
    object who;
    int pot;

    if (ENV(TO))
        ob = all_inventory(ENV(TO));

    if (!sizeof(ob))
        return 0;

    ob = FILTER_PLAYERS(ob);
    if (!sizeof(ob))
	return 0;

    who = one_of_list(ob);
    pot = random(5);

    if (pot == 0)
    {
        apotion = clone_object(POTION +"anarex");
        apotion->dest_effect();
        apotion->move(who, 1);   
        who->catch_msg(QCTNAME(TO) +" gives you a vial of "+
            "dark purple fluid.\n");        
        tell_room(ENV(TO), QCTNAME(TO) +" gives a vial of dark "+
            "purple fluid to "+ QTNAME(who), who);
        return 1;
    }

    if (pot == 2)
    {
        spotion = clone_object(POTION +"somnan");
        spotion->dest_effect();
        spotion->move(who, 1);   
        who->catch_msg(QCTNAME(TO) +" gives you a vial of "+
            "greenish gas.\n");        
        tell_room(ENV(TO), QCTNAME(TO) +" gives a vial of green"+
            "ish gas to "+ QTNAME(who) + ".\n", who);
        return 1;
    }
    if (pot == 3)
    {
        lpotion = clone_object(POTION +"lanthan");
        lpotion->dest_effect();
        lpotion->move(who, 1);
        who->catch_msg(QCTNAME(TO) +" gives you a blue vial.\n");        
        tell_room(ENV(TO), QCTNAME(TO) +" gives a blue vial to "+ 
            QTNAME(who), who);
        return 1;
    }
    return 0;        
}

  
int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
            return 1;
    }

    switch (random(5))
    {
        case 0: give_potion();
            return 0;
        case 1: command("punch");
            return 0;
        case 2: command("heal");
            return 0;
        case 3: command("punch");
            return 0;
        default: 
    }
    return 0;
}

