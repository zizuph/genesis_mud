//-*-C++-*-
// file name:     Avenir/common/holm/mon/priest.c
// creator(s):    Lilith    1/26/97
// purpose:       
// note:          This file acts like 5 different npcs.
// last update:   Lilith 19 March 1998: fixed ranger prop.
//                Liith May 2022: added more asks via god_asks.c
// bug(s):
// to-do:
#pragma strict_types
inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/log_asks";
inherit "/d/Avenir/common/gods/god_asks";
inherit "/lib/unique";

#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/common/holm/holm.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Genesis/gems/gem.h"
#include <ss_types.h>
#include <language.h>

string eyes, hair;
string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
void set_eyes(string str)   {    eyes = str;      }
void set_hair(string str)   {    hair = str;      }
string my_long();

mixed *everyone = ({
    ({ "human", "robust", random(20) + 80, "soot-black",
       "dark brown and unnaturally bright", 190 }), 
    ({ "elf", "angular", random(20) + 90, "dark brown and silky",
       "the colour of night", 210 }), 
    ({ "half-elf", "inscrutible", random(20) + 100, 
       "dark red and tightly curling", "piercing as a drawn dagger", 200 }),
    ({ "gnome", "grave", random(20) + 60, "mostly white with age",
       "regarding you with suspicion", 170 }),
    ({ "dwarf", "formidable", random(20) + 70, "kinky and silver-black",
       "as hard and gray as stone", 170 })
    });

/* 
 * set_morph sets the various attributes of the 
 * npc, making it unique 5 different ways.
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
    add_prop(CONT_I_HEIGHT, someone[5]);
}

/* Create the npc */
void
create_monster()
{
    /* If not a clone, do no proceed */
    if (!IS_CLONE)
        return;

    /* Make sure sybarite stuff is initialized */
    :: create_sybarite();

    /* You're all individuals! */    
    set_morph(random(sizeof(everyone)));

    set_name("priest");
    set_long(my_long);
    add_name(({"cleric"}));
    add_adj("priestly");
    set_alignment(0);

    set_knight_prestige(100);   

    if (random(3))
        set_gender(G_FEMALE);

    set_skill(SS_DEFENCE, random(20) + 60);
    set_skill(SS_WEP_POLEARM, random(20) + 70);
    set_skill(SS_AWARENESS, random(40)+ 20);
    set_skill(SS_BLIND_COMBAT, random(20)+ 30);
    set_all_attack_unarmed(35, 35);
    set_all_hitloc_unarmed(50);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    MAKE_SYBARITE;
    add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);

    set_act_time(10);
      add_act("emote rubs "+ TO->query_possessive() +" hand lovingly "+
          "along the length of "+ TO->query_possessive() +" staff.");
      add_act("emote smiles thoughtfully.");
      add_act("say 'Ware the waters, there is danger there!");
      add_act("emote appears to be deep in thought.");
      add_act("emote doesn't seem to notice your presence.");
    set_cact_time(7);
      add_cact("emote looks sadly at you and shakes "+ 
          TO->query_possessive() +" head.");

    set_default_answer("say The quality of my answer depends upon the "+
        "quality of your question. Try again.", 1);
    add_ask(({"Hunt", "Hunting", "hunt", "hunting"}), VBFC_ME("hunt_ask"));
    add_ask(({"Rule", "rule" }), VBFC_ME("rule_ask"));
    add_ask(({"aclolthayr"}), VBFC_ME("aclo_ask"));
    add_ask(({"sybarus","bazaar"}),
        "say There is an apothecary there.",1);
    add_ask("city", "say It is a wonderous place!",1);
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
    add_god_asks();

}

string
my_long()
{
    string  str, poss;
    poss = TO->query_possessive();
  
    str =  capitalize(TO->query_pronoun()) + " is "+ 
           LANG_ADDART(implode(query_adjs(), " ")) +" "+ 
           query_race_name()+".\n";

    str += "There is a distinctly ethereal air about this individual.\n"+
           "The hair at the crown of "+ poss +" head is pulled back "+
           "into a tail, and the rest is tonsured from just above "+
           "the ears around to the nape of "+ poss +" neck.\n"+ 
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
    object gloves, robe, sandals, staff, tunic;

    gloves = clone_unique(HOLM_OBJ + "m_gloves", 7,
	GEM_OBJ_DIR + "sea_agate", 1, 25);
    gloves->move(TO);

    robe = clone_object(HOLM_OBJ + "robe");
    robe->move(TO);

    sandals = clone_object(HOLM_OBJ + "sandals");
    sandals->move(TO);
    
    staff = clone_unique(HOLM_OBJ + "serpent_staff", 7,
	HOLM_OBJ + "staff_alt", 1, 25);
    staff->move(TO);
    if (staff->query_prop(MAGIC_AM_MAGIC))
        add_prop("_ranger_m_no_disarm_drop", 1);

    tunic = clone_object(HOLM_OBJ + "utunic");
    tunic->move(TO);

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
    command("say to "+ TP->query_real_name() + " Are you on a Hunt?");
    command("say to "+ TP->query_real_name() +
        " If so, I hope you'll pass me by. I won't "+
        "be very sporting prey.");
    return "";
}    

string
rule_ask()
{
    command("say to "+ TP->query_real_name() +
        " As you know, a true Hunt involves intelligent prey.");
    command("say to "+ TP->query_real_name() +
        " So there is only one rule on the Holm: Everyone and "+
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

void
wield_wep()
{
    // Sometimes ranger code doesn't work to cause re-wield
    TO->command("wield all");
}


/* ***************** Punch attack ******************* */
int
punch_em(object victim)
{

    if (victim->query_not_attack_me(this_object(), -1))
    {
        return 1;
    }

    int hit = (random(30) + 30);
    int whit = (random(30) + 60);
    int how;
    string str1, str2;
    string *randhit = ({"face", "head", "nose", "eye", "chest"});
    mixed *wep, where;

    how = (random(sizeof(randhit)));    
    where = randhit[how];
    wep = TO->query_weapon(-1);

    if (wep == ({ }))
    { 
        victim->catch_msg(QCTNAME(TO)+" dodges under your guard "+
            "and gives you a quick double-punch in the " + where +".\n");
        tell_room(ENV(TO), QCTNAME(TO)+" dodges under "+ QCTNAME(victim) + 
            "'s guard and gives "+ victim->query_objective() +
            " a quick double-punch to the "+ where +"!\n", victim);
        victim->heal_hp(-hit);
        return 1;
    }
    else
    {
        tell_room(ENV(TO), 
            QCTNAME(TO) +" whirls "+ TO->query_possessive() +" staff "+
            "in "+ TO->query_possessive() +" hands and attempts to "+
            "bring it down on "+ QCTNAME(victim) +"'s head!\n", victim);
        victim->catch_msg(QCTNAME(TO) +" whirls "+ TO->query_possessive() +
            " staff in "+ TO->query_possessive() +" hands and attempts "+
            "to bring it down on your head!\n");

        if (hit < 30)
        {
            str1 = "You manage to leap far enough out of the way "+
               "so that it just grazes";
	    str2 = "grazes";
	}
        else if (hit < 40)
        {
	    str1 = "You leap to the side, but it still manages to "+
               "bludgeon";
	    str2 = "bludgeons";
	}
        else if (hit < 50)
        {
            str1 = "You are unable to evade the staff and it badly "+
               "injures";
	    str2 = "badly injures";
	}
        else 
	{
	    str1 = "Despite your best efforts, the full brunt of the "+
               "blow lands and smashes";
            str2 = "smashes";
	}
        victim->catch_msg(QCTNAME(TO) +"'s staff makes a high, whistling " +
            "sound as it moves toward you. " + str1 + " your "+ where +"!\n");
	    victim->add_attack_delay((hit*2)/3, 1);
        tell_watcher(QCTNAME(TO) + " " + str2 + " " + QCTNAME(victim) +
	    " with "+ TO->query_possessive() +" staff.\n", victim);
        victim->heal_hp(-hit);
        if ((victim->query_hp() <= 0) && (!victim->query_ghost()))
            victim->do_die(TO);
        return 1;        
      }
    return 1;
}


int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
	return 1;
    }

    switch (random(7))
    {
        case 1: punch_em(victim);
            return 1;
        case 3: punch_em(victim);
            return 1;
        case 5: command("heal me");
            return 0;
        case 6: command("wield staff");
            return 0;
        default: 
    }
    return 0;
}

void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    object shawl;
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    STATSERV_LOG_EVENT("holm", "Priest killed");
    ::do_die(killer);
}

