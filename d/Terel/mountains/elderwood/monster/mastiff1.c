/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * mastiff1.c  
 *
 * One of Dolmoors dogs. Elderwood Forest. (based upon the bigwolf.c of the goblincaves
 * Tomas  -- June 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;
inherit "/lib/unique";


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

#define H_HEAD 0
#define H_BODY 1

mixed benice();
void dress_me();


/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_short("giant black mastiff");
    add_name("dog");
    set_pshort("giant black mastiffs");
    set_long("The giant black mastiff stands crouched upon " +
       "its huge paws. Its jaws dripping of sticky saliva through " +
       "its long white teeth. Stares at you through seemingly " +
       "intelligent eyes.\n");

    set_adj(({"giant", "black"}));
    set_race_name("mastiff");

    set_stats(({random(30)+70, random(50)+100, 140, 100, 50, 90}));

    set_attack_unarmed(A_BITE,  15, 12, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 20, 10, W_SLASH,  30, "left claw");
    set_attack_unarmed(A_RCLAW, 20, 10, W_IMPALE, 30, "right claw");

    set_hitloc_unarmed(H_HEAD, ({ -15, -25, -20, -20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  10,  15,  30,  20 }), 80, "body");

    set_aggressive("@@benice");
    SET_MAX_HP;
    set_gender(NEUTER);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE, 80);
    BRAVE;
    add_prop(LIVE_I_SEE_DARK,10); 
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_SEE_INVIS,100);            /* I smell you, I know you are there */
//    add_leftover(MOUNTAIN_DIR + "elderwood/armour/pcollar","collar", 1, "", 0, 1);

    set_restrain_path(MOUNTAIN_DIR + "elderwood");
  
    set_act_time(20);
    add_act("emote growls ferociously.");
    add_act("emote bares its teeth at you.");

    dress_me();
}


void
dress_me()
{
    seteuid(getuid(this_object()));     

    clone_object(MOUNTAIN_DIR + "elderwood/armour/mastiff_collar")->move(TO);
    
    TO->command("wear all");
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int hurt;
    int fire_resist;

    me = TO;
    
    if(random(10) < 3) {

        hurt = F_PENMOD(100, 80 + random(100));
        
        hitresult = enemy->hit_me(hurt, MAGIC_DT, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";
            
        tell_watcher(QCTNAME(me) + " crouches low then lunges at " + QTNAME(enemy) + 
        ".\n", enemy); 
        enemy->catch_msg(QCTNAME(me) + " quickly ducks under your defences, " +
        "then lunges crushing you in its massive jaws!\n");
        enemy->catch_msg("You feel " + how + ".\n");

      set_follow(enemy->query_real_name());

        
        return 1;
    }

    return 0;
}


mixed
benice()
{
       
    if(TP->query_prop("_dolmoor_attacked"))
    { 
      return 1;
    }

    if (TP->query_wiz_level())             /* Dont bite the hand that feeds me */
    {
       return 0;
    }

    if(TP->query_prop(OBJ_I_INVIS))        /* Invisible players doesn't mean they dont smell */
    {
        write("The "+short()+" raises his snout high in the air " +
          "sniffing in your direction.\n");
        say("The "+short()+" raises his snout as if smelling something.\n", TP);
        return 1;
    }
       
 
  return 1; 
}
