/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * house4_captain.c  
 * tomas - 11/19/1999
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>

#include <ss_types.h>
#include <money.h>
#define KILL_LOG CALATHIN_DIR+"log/captain_kills"
#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"



void dress_me();

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    
    set_name("korl");
    set_living_name("korl");
    set_adj("black-haired");
    set_adj("black-bearded");
    set_race_name("human"); 
    add_name("captain");
    set_title("Farun, Captain of the Calathin Guard");
    set_long("A strong man in his late thirties. His black-hair is tied "+
                   "in the back and his beard is well trimmed. He seems calm "+
                   "and collected.\n");
  
    set_stats(({190, 190, 190, 140, 140, 160}));
    SET_MAX_HP;
  
    set_skill(SS_UNARM_COMBAT,   75);
    set_skill(SS_WEP_SWORD,     100);
    set_skill(SS_WEP_POLEARM,     100);
    set_skill(SS_DEFENCE,        85);
    set_skill(SS_PARRY,         100);
    set_skill(SS_AWARENESS,      70);
    set_skill(SS_2H_COMBAT,     100);
    set_skill(SS_BLIND_COMBAT,  100);
    add_prop(OBJ_M_HAS_MONEY, ({1+random(3),10,5,0}) );


    set_act_time(20);   
    add_act("emote looks out the window.");
    add_act("say The Goblins will raid again once the snow clears some.");
    add_act("say Maskyr Keep's foul stench is beginning to spread farther.");
    add_act("say Please do not disturb me. I have work to do.");
    add_act("close door");
    add_act("say I hope our allies will come through.");
    
    set_all_hitloc_unarmed(30);
    enable_intro();

    PASSIVE;

  
    set_cact_time(3);
    add_cact("say By the Star, what are you thinking?");
    add_cact("say I may be old, but I've still fight in me.");
    add_cact("say You believe this will benefit you?");
  
    dress_me();
}
void dress_me()
{
    FIX_EUID;

    clone_object(CALATHIN_DIR+"weapon/silver_spear")->move(TO);
    command("wield spear");
    clone_object(CALATHIN_DIR+"armour/steel_chainmail")->move(TO);
    clone_object(CALATHIN_DIR+"armour/steel_greaves")->move(TO);
    clone_object(CALATHIN_DIR+"armour/steel_helm")->move(TO);
    clone_object(CALATHIN_DIR+"armour/steel_bracers")->move(TO);
    command("wear all");
}


public int
query_knight_prestige()
{
    return -4;
}

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies, kill_logger;
    
    if (query_hp() > 0) return;
    enemies = query_my_enemies();

    kill_logger = find_object(CALATHIN_DIR + "obj/kill_logger");
    kill_logger->add_killer(killer->query_name());
    
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    
    for (i=0; i<sizeof(enemies); i++) 
    {
        if (enemies[i] != killer)
        {
            str += ", " + enemies[i]->query_name() +
            "[" + enemies[i]->query_average_stat() + "]";
            kill_logger->add_killer(enemies[i]->query_name());
        }
    }
    write_file(KILL_LOG, str + " (" + ctime(time()) + ")\n");
    
    ::do_die(killer);
}


/* perform a special attack */
int
special_attack(object enemy)
{
    mixed* hitresult;
    string how, spattack, hdesc;
    object me, *enemies;
    int intox, hurt, hitloc;

    me = TO;
    /* Choose a hit location */
    if(random(8) < 1)
    {
        switch(random(4))
        {
            case 0:    hitloc = A_BODY;
                       hdesc = "body";
                       break;

            case 1:    hitloc = A_HEAD;
                       hdesc = "head";
                       break;

            case 2:    hitloc = A_LEGS;
                       hdesc = "legs";
                       break;

            case 3:    hitloc = A_R_ARM;
                       hdesc = "right arm";
                       break;

            case 1:    hitloc = A_L_ARM;
                       hdesc = "left arm";
                       break;
        }




        /* Figure a pen value, take drunken bastards into account */

        hurt = F_PENMOD(70 + (intox/3), 70 + (intox/3));

        /* Switch between three types of attack, stab, slash, and punch. */


        if(sizeof(me->query_weapon(-1)))
        {
              hitresult = enemy->hit_me(hurt, W_IMPALE, me, hitloc);
              spattack = "stabs";
        }
        else
        {
              hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, hitloc);
            spattack = "punches";
        }


          
        /* Determine how good a hit and describe it. */
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        /* Describe the attack. */
        if(spattack == "stabs")
        {
            tell_watcher(QCTNAME(me)+ " " +spattack+ " " +QCTNAME(enemy)+
                     " in "+POSSESSIVE(enemy)+" "+hdesc+" with "+POSSESSIVE(me)+
                     " wooden silver-tipped spear!\n",enemy);
            enemy->catch_tell(query_The_name(enemy) + " " + spattack + " you "+
                "in the "+hdesc+" with "+POSSESSIVE(me)+ " wooden silver-tipped spear!\n" +
                "You feel " + how + ".\n");
        }
        else
        {
            tell_watcher(QCTNAME(me)+ " " +spattack+ " " +QCTNAME(enemy)+
                     " in "+POSSESSIVE(enemy)+" "+hdesc+" with "+POSSESSIVE(me)+
                     " gauntleted fist!\n",enemy);
            enemy->catch_tell(query_The_name(enemy) + " " + spattack + " you "+
                "in the "+hdesc+" with "+POSSESSIVE(me)+ " gauntleted fist!\n" +
                "You feel " + how + ".\n");
        }

        /* Kill the bastard if he's got no hit points. */
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(me);
        }
        return 1;
    }
    return 0;
}



