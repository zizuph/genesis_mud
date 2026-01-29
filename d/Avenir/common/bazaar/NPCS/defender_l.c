//-*-C++-*-
// file name:     
// creator(s):    Lilith   03/26/03
// purpose:       Defenders of Sybarus
// note:          This file acts like multiple npcs.
//                Clones paralyse object to infidels it comes into
//                contact with.
// last update:   27 May 2003 Lilith: changed to inherit call_for_help.
// bug(s):
// to-do:

// Call_for_help drags killers to the pillory.
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";
#include "/d/Avenir/include/relation.h"
#include "../bazaar.h"

#include <ss_types.h>
#include <language.h>

#define MORTAL_LOG "/d/Avenir/log/misc/malefactor"
#ifndef SHORT_LOG
#define SHORT_LOG(file, entry)   ((file_size(file) > 5000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, entry +" ("+ ctime(time()) + ")\n")))
#endif


mixed *everyone = ({
      /* race   adj         eyes      hair */
    ({ "elf", "intelligent",   "dark-brown",  "dark-brown" }), 
    ({ "elf", "graceful",      "dark-grey",   "light-brown" }), 
    ({ "elf", "swift",         "light-brown", "red-brown" }), 
    ({ "elf", "proud",         "brown",       "blond" }), 
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

    set_eyes(someone[2]);
    set_hair(someone[3]);
    set_gender(G_MALE);
}

/* Create the npc */
void
create_monster()
{

    set_morph(random(sizeof(everyone)));
    set_name("defender");
    set_long(my_long);
    add_name(({"defender of sybarus", "guard", "leader"}));
    set_alignment(0);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 210);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 
        "The Gods of Sybarus protect those who serve.\n");

    remove_prop(CONT_I_WEIGHT);

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

    default_config_npc(random(30) + 60);    
    set_restrain_path(({"/d/Avenir/common/bazaar", "/d/Avenir/common/city"}));
    set_monster_home("/d/Avenir/common/bazaar/admin/a18");

    set_cact_time(7);
      add_cact("glare mercilessly enemy");
      add_cact("say When this Hunt is finished, who will remain "+
          "standing?");
      add_cact("say Flee from me and I will not follow!");
      add_cact("say From whence thou came, so shall I return you.");

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
        "say Infidels are without rank, less than slaves. They have "+
        "acted against the Gods' Will, and rather than submit to "+
        "servitude or a dignified death, they have chosen to live "+
        "the rest of their lives in fear of death.", 1);
    add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
        "say Sybarites are the Faithful. Sybarites live to serve and "+
        "uphold the Pact, that the Source will always cast its illum"+
        "ination upon us.",1);

    seteuid(getuid());
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
           "a Defender of Sybarus.\n"+ 
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
    dagger = clone_object("/d/Avenir/common/bazaar/Obj/wield/bsword");
    dagger->move(TO);    
    command("wield all");
}

/* **** add_ask answers, including quest assignment, if any **** */
string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks suspiciously around.");        
        return "";
    }
    command("say to "+ TP->query_real_name() +
        " I'm on duty. Find someone else to answer your questions.");
    return "";
}
string
give_task()
{
    command("sigh");
    command("say There are lots of things needing doing.");
    command("say Have you tried Jadestone? The fishmonger? "+
        "The blacksmith? The apothecarist? Or the librarian?");
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
        case 1: command("neck");
            return 0;
        case 2: command("pommel");
            return 0;
        case 3: herb_heal();
            return 0;
        default: 
    }
    return 0;
}

/*
 *  This gets the time from the avenir_time object and returns the
 *  get_time_text string.
 */
string 
get_time()
{
    string str;
    "/d/Avenir/inherit/avenir_time"->start_avtime();
    str = "/d/Avenir/inherit/avenir_time"->get_time_text();
    return str;
}

void
grab_him(object tp)
{
    object pobj;
    string name, desc;

    seteuid(getuid());

    name = tp->query_real_name();
    desc = tp->query_nonmet_name();

    SHORT_LOG(MORTAL_LOG, capitalize(name) + break_string(
        "the "+ desc +" criminal, was captured entering "+
        "the City at "+ get_time() +" but escaped soon "+
        "afterward.",70, 2));

    pobj = clone_object("/d/Avenir/common/bazaar/Obj/misc/freeze");
    pobj->set_stop_verb("");
    pobj->set_remove_time(3600);
    pobj->set_fail_message("You are held by a guard. You cannot do that.\n");
    pobj->set_stop_message("You manage to wriggle free of the guard's grip!\n");
    if (!present(pobj, tp)) 
        pobj->move(tp, 1);

    tell_room(environment(this_object()), QCTNAME(this_object()) + 
        " grabs hold of " + QTNAME(tp) +" with a firm grip.\n", tp);
    tp->catch_msg(QCTNAME(this_object()) +" grabs hold of you in a "+
        "firm grip.\n");
    command("say to "+ tp->query_real_name() +" Sit tight and I'll bring "+
        "you to the Executioner's holding pen as soon as the shift changes.");
}
      



void
check_meet(object tp)
{
    object pobj;

    if (!present(tp, environment(TO)))
        return;

    if (IS_INFIDEL(tp))
    {

        command("shout Got one!");
        grab_him(tp);
        return;
    }
    return;
}

void
init_living()
{
    ::init_living();

    if (interactive(TP))
        set_alarm(0.2, 0.0, &check_meet(TP));
}  

public void
add_introduced(string str)
{
    set_alarm(itof(random(2)), 0.0, &command("nod ."));
}
