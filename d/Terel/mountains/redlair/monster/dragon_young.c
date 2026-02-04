/* This comment tells emacs to use c++-mode  -*- C++ -*- */

// Location: /d/Terel/mountains/redlair
// Filename: ~monster/dragon_young.c
// Creator:  Tomas  -- Feb. 2000
// Modification log: Updated level of difficulty (Gorboth, August 2012)
//                   Changed race "hatchling"->"dragon" (Gorboth, Oct, 2014)

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

#define DRAGONFIRE "_terel_dragonfire"

mixed benice();


/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name(({"hatchling"}));
    add_name(({"dragon"}));
    add_name("_terel_hatchling");
    set_short("dragon hatchling");
    set_pshort("dragon hatchlings");
    set_long("This young dragon does not yet have its wings. Its scaly dark " +
       "green and yellow colored skin looks quite durable. " +
       "You notice hardened knobs about the size of a humans " +
       "fist growing from the long spindly tail. Its teeth and " +
       "claws look very sharp.\n");
    set_adj(({"young", "hatchling", "dragon"}));
    set_race_name("dragon");
    set_alignment(-500 - random(200));

    set_stats(({random(75)+120, random(60)+175, 130, 30, 30, 150}));

    set_attack_unarmed(A_BITE,  45, 60, W_IMPALE, 10, "jaws");
    set_attack_unarmed(A_LCLAW, 50, 45, W_SLASH,  40, "left claw");
    set_attack_unarmed(A_RCLAW, 60, 45, W_SLASH, 40, "right claw");
    set_attack_unarmed(A_TAIL,  45, 35, W_BLUDGEON, 10, "tail");

    set_hitloc_unarmed(H_HEAD, 40, 20, "head");
    set_hitloc_unarmed(H_BODY, 60, 80, "body");
    set_hitloc_unarmed(H_TAIL, 60, 80, "tail");

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_MAGIC, 35);
    add_prop("_terel_hatchling",1);

    set_aggressive("@@benice");
    SET_MAX_HP;
    set_gender(NEUTER);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_DEFENCE, 85);
    BRAVE;
    add_prop(LIVE_I_SEE_DARK,100); 
    add_prop(LIVE_I_SEE_INVIS,100);

    set_restrain_path(MOUNTAIN_DIR + "redlair");
    set_random_move(5);

    set_act_time(20);
    add_act("emote roars ferociously.");
    add_act("emote bares its teeth at you.");
    add_act("emote swipes at you with its claws.");
    add_act("emote snarls savagely.");
}

mixed
benice()
{

    if (TP->query_wiz_level())
    {
        return 0;
    }

    if(TP->query_prop(OBJ_I_INVIS))
    {
        write("The hatchling sniffs the air, then sniffs "+
          "in your direction.\n");
        say("The hatchling sniffs the air.\n", TP);
   
        return 1;
    }
       
    if(TP->query_average_stat() <= 200)
    { 
      return 0;
    }
    return 1; 
}



int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int hurt = 0;
    int fire_resist;

    me = TO;
    
    if(random(10) < 4) {

        if(!enemy->query_prop(DRAGONFIRE)) {
            hurt = F_PENMOD(55, 40 + random(20));
        } else {
            hurt = F_PENMOD(40, 40+random(10));
        }
        
        hitresult = enemy->hit_me(hurt, MAGIC_DT, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly injured";
        if (hitresult[0] > 20)
            how = "rather damaged";
        if (hitresult[0] > 50)
            how = "brutally wounded";
        if (hitresult[0] > 100)
            how = "utterly devastated";
            
        tell_watcher(QCTNAME(me) + " strikes out at " + QTNAME(enemy) + ".\n", enemy); 
        enemy->catch_msg(QCTNAME(me) + " strikes you with its gaping jaws!\n");
        enemy->catch_msg("You feel " + how + ".\n");

        if(!enemy->query_prop(DRAGONFIRE) && random(10) < 5)
        {
            set_follow(enemy->query_real_name());
        }
        
        return 1;
    }

    return 0;
}


