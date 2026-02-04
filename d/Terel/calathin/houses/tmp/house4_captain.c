/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * house4_captain.c  
 * tomas - 11/19/1999
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <options.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <money.h>

inherit "/lib/unique";
inherit "/d/Terel/include/log_asks";
#define KILL_LOG CALATHIN_DIR+"log/house4_capt_kills"


/* sets unarmed combat off, giving more sword attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}


public string
reply_lord()
{
   command("say My Lord, the one who pays us, is up North " +
       "looking into the reports of the goblin tribes massing " +
       "to the north.");
   return "";
}

public string
reply_sabre()
{
   command("say Ahh. You wish to know about my Sabre eh.. " +
      "Well forget it!");
   return "";
}

public string
reply_calathin()
{
   command("say We have nothing to do with those idiots!");
   return "";
}

public string
reply_quest()
{
   command("say I dont have anything for you. Try back later.");
   return "";
}



void dress_me();

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    
    set_name("arlenn");
    set_adj("sandy-haired");
    set_race_name("human"); 
    add_name("captain");
    set_title("Mercenary Captain of the Guard");
    set_long("This person looks quite sure of himself. " +
       "He holds himself as someone of authority.\n");
  
    set_stats(({190, 190, 190, 140, 140, 160}));
    SET_MAX_HP;
  
    set_skill(SS_UNARM_COMBAT,   75);
    set_skill(SS_WEP_SWORD,     100);
    set_skill(SS_DEFENCE,        85);
    set_skill(SS_PARRY,         100);
    set_skill(SS_AWARENESS,      70);
    set_skill(SS_2H_COMBAT,     100);
    set_skill(SS_BLIND_COMBAT,  100);
    set_intoxicated(30);
    add_prop(OBJ_M_HAS_MONEY, ({2+random(3),10,5,0}) );


    set_act_time(5);   
    add_act("smirk confident");
    add_act("emote adjusts his armour.");
    add_act("say You here for a job? Well forget it!");
    add_act("say Run along now. I have work to do.");
    add_act("close door");
    add_act("say Calathin expects us to lend a hand in " + 
       "protecting the city. BAH! Thats not why we are getting paid.");
    add_act("say I hope my Lord calls for reinforcements, I grow " +
       "tired of all of this waiting.");
    add_act("say A fight with me means a fight to the death.");
    add_act("say I'd sooner kill myself than let an enemy get away.");

    add_ask("lord", reply_lord, 1);
    add_ask("sabre", reply_sabre, 1);
    add_ask("calathin", reply_calathin, 1);
    add_ask(({"quest","task"}), reply_quest, 1);
        
    set_all_hitloc_unarmed(50);
    enable_intro();

    PASSIVE;
    set_attack_chance(0);
  
    set_cact_time(3);
    add_cact("say You clearly weren't thinking where you!");
    add_cact("say You have no chance at winning, i'm the finest swordsman " +
       "in all of Terel!");
    add_cact("say Have you a death wish?!");
    add_cact("say You disappoint me. Hardly worth the effort.");
    add_prop(LIVE_I_SEE_DARK,3);
  
    dress_me();
}
void dress_me()
{
    seteuid(getuid(this_object()));



    switch(random(2)) 
   {
        case 0 :  clone_unique(CALATHIN_DIR+"houses/weapon/isabre",5,
                     CALATHIN_DIR+"weapon/shortsword")->move(TO);
                     command("wield sabre");  
                  break;
        case 1 :  clone_unique(CALATHIN_DIR+"houses/weapon/abbasi",5,
                     CALATHIN_DIR+"weapon/shortsword")->move(TO);
                     command("wield abbasi"); 
                  break;
    }

    clone_object(CALATHIN_DIR+"weapon/shortsword")->move(TO);
    command("wield shortswords");
    clone_object(CALATHIN_DIR+"/houses/armour/chainmail")->move(TO);
    clone_object(CALATHIN_DIR+"/houses/armour/gboots")->move(TO);
    clone_object(CALATHIN_DIR+"/houses/armour/ghelmet")->move(TO);
    clone_object(CALATHIN_DIR+"/houses/armour/gcloak")->move(TO);
    command("wear all");
}


public int
query_knight_prestige()
{
    return 2;
}

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) {
       if (enemies[i] != killer)
           str += ", " + enemies[i]->query_name() +
           "[" + enemies[i]->query_average_stat() + "]";
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
    int intox, hurt, hitloc, goblinz;
    goblinz = 0;

    intox = enemy->query_intoxicated();

    if(enemy->query_race_name() == "goblin")
    {
        goblinz = 25;
    }



    me = TO;
    /* Choose a hit location */
    if(random(10) > 6) 
    {
        switch(random(5))
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

            case 4:    hitloc = A_L_ARM;
                       hdesc = "left arm";
                       break;


        }




        /* Figure a pen value, take drunken bastards into account */

        hurt = F_PENMOD(80  + goblinz + (intox / 3), 80 + goblinz + (intox /3));

        /* Switch between three types of attack, stab, slash, and punch. */

        switch(random(2)) 
        {
            case 0:  
                    if(sizeof(me->query_weapon(-1)))
                    {
                        hitresult = enemy->hit_me(hurt, W_IMPALE, me, hitloc);
                        spattack = "laughs confidently as he " +
                           "parries then thrusts forward stabing";
                    }
                    else
                    {
                        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, hitloc);
                        spattack = "smirks arrogantly as he backhands";
                    }
                    break;

            case 1:  
                    if(sizeof(me->query_weapon(-1)))
                    {
                        hitresult = enemy->hit_me(hurt, W_SLASH, me, hitloc);
                        spattack = "slashes";
                    }
                    else
                    {
                        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, hitloc);
                        spattack = "punches";
                    }
                    break;

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
        tell_watcher(QCTNAME(me)+ " " +spattack+ " " +QCTNAME(enemy)+
                     " in "+POSSESSIVE(enemy)+" "+hdesc+"!\n",enemy);
        enemy->catch_tell(query_The_name(enemy) + " " + spattack + " you "+
            "in the "+hdesc+"!\n" +
            "You feel " + how + ".\n");

        /* Kill the bastard if he's got no hit points. */
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(me);
            TO->command("get all from corpse");
        }
        return 1;
    }
    return 0;
}


