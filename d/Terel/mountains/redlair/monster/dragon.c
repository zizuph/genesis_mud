/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/* Updated level of difficulty - Gorboth, August 2012 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;
 
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#define KILL_LOG "/d/Terel/log/red_kills"
#define DRAGONFIRE "_terel_dragonfire"
#define BABIES   MOUNTAIN_DIR + "redlair/monster/dragon_young"

#define A_BITE    (0)
#define A_LCLAW   (1)
#define A_RCLAW   (2)

#define H_HEAD    (0)
#define H_BODY    (1)

mixed benice();
int berzerked = 0;


/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name(({"dragon"}));
    set_short("huge red dragon");
    set_long("A huge red dragon.\n" +
             "You can feel the heat from its sulphur-breath.\n"+
             "The dragon faces you with a calm expression, knowing it " +
             "has fought many battles against small creatures like you, " +
             "and won.\n");
    
    set_adj(({"enormous", "red", "vicious"}));
    set_race_name("dragon");
    set_alignment(-400 - random(1200));
    set_gender(NEUTER);    

    set_hitloc_unarmed(H_HEAD, 170, 25, "head");
    set_hitloc_unarmed(H_BODY, 170, 75, "body");

    set_stats( ({ 350, 300, 400, 200, 200, 300 }) );

    set_attack_unarmed(A_BITE, 75, 80, W_IMPALE, 10, "bite");
    set_attack_unarmed(A_LCLAW, 80, 75, W_SLASH,  40, "left claw");
    set_attack_unarmed(A_RCLAW, 80, 75, W_SLASH,  50, "right claw");
    set_exp_factor(200);

    set_aggressive("@@benice");
    SET_MAX_HP;
    BRAVE;
    set_skill(SS_AWARENESS,100);
    set_skill(SS_PARRY, 100);

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_MAGIC, 40);

    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(LIVE_I_SEE_INVIS,100);
    add_prop("_ranger_i_not_brawl", 1);
    add_prop("_union_i_adjust_diginity", 85);
    if(random(9) > 2)
        add_leftover(MOUNTAIN_DIR +"redlair/weapon/dtooth","tooth",1,0,1,1);

    trig_new("%s 'attacks' 'you!\n' %s","react_attacked");
}


react_attacked(s,ss)
{
  set_alarmv(1.0, 5.0, "att",({TP}));
  return 1;

}


att(s,ss)
{
  int qryhp;
  qryhp = (TO->query_max_hp() / 2);

  if(berzerked == 1)
  return 0;

  if(TO->query_hp() <= qryhp)
  {
   berzerked = 1;
   set_alarm(1.0, 0.0, "go_berzerk",({TP}));
   return 1;
  }
   return 0; 
}


public void
go_berzerk()
{
    /* I'm hurt, call for help! */

    int base_stat;
    int i;

    command("emote shrieks in fury.");

    FIX_EUID;
    clone_object(BABIES)->move_living("east", ETO, 0, 0);
    clone_object(BABIES)->move_living("east", ETO, 0, 0);
    clone_object(BABIES)->move_living("east", ETO, 0, 0);
    clone_object(BABIES)->move_living("east", ETO, 0, 0);
    clone_object(BABIES)->move_living("east", ETO, 0, 0);
    clone_object(BABIES)->move_living("east", ETO, 0, 0);

}



mixed
benice()
{

    if (TP->query_wiz_level())             /* Dont bite the hand that feeds me */
    {
        return 0;
    }

    if(TP->query_average_stat() <= 200)
    { 
      return 0;
    }

    if(TP->query_prop(OBJ_I_INVIS))
    {
        write("The " + short() + " sniffs the air, then sniffs " +
          "in your direction.\n");
        say("The " + short() + " sniffs the air.\n", TP);
        return 1;
    }

  return 1; 

}


int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, flame_room, *all;
    int hurt, i;
    int fire_resist;
    flame_room=find_object (MOUNTAIN_DIR+"redlair/cave11");

    me = TO;
    all = query_my_enemies();

    if(random(9) < 2) {

        flame_room->bake(me);

        for (i=0; i<sizeof(all); i++) {
            hurt = 2500;
            hurt -= hurt * all[i]->query_magic_res(MAGIC_I_RES_FIRE) / 100;
            if(all[i]->query_prop(DRAGONFIRE))
                hurt = 0;
     
            hitresult = all[i]->hit_me(hurt, MAGIC_DT, me, -1);

            how = "misses";
            if (hitresult[0] > 0)
                how = "singes";
            if (hitresult[0] > 20)
                how = "burns";
            if (hitresult[0] > 50)
                how = "ignites";
            if (hitresult[0] > 100)
                how = "incinerates";
            all[i]->catch_msg("The huge red dragon breathess fire throughout the cave!\n");
            all[i]->catch_msg("The fiery breath " + how + " you.\n");
            if(all[i]->query_hp() <= 0)
                all[i]->do_die(me);
            }
     return 1;
    }

    return 0;
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

