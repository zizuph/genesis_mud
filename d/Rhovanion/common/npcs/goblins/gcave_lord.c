inherit "/d/Rhovanion/common/npcs/goblins/goblin.c";

#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <ss_types.h>

/* group and bit for finished prisoner quest */
#define GROUP   0
#define BIT     9

void set_lord_stats()
{
  set_base_stat(SS_STR,190+random(15));
  set_base_stat(SS_DEX,190+random(10));
  set_base_stat(SS_CON,200+random(20));
  set_base_stat(SS_INT,80);
  set_base_stat(SS_WIS,135);
  set_base_stat(SS_DIS,110);
  heal_hp(10000);
}

void create_goblin()
{
  set_base_gob(180);
  set_ran_gob(0);
//  set_ran_wep(({ "halberd" }));
  command("wear all");
  command("wield halberd in both hands");
  command("wield all");        
//  set_def_arm(({ "mail", "helm" }));
//  command("wear all");    
  set_looks(({ "lord" }));
  add_name("lord");
  set_chats(({ "Get out of here!!!  I have called NOBODY!!!",
              "Do I have to call guards or should I kill you myself?",
             "How did you get here???",
            "I will stop giving food to those stupid guards that let you in!"
            }));
  set_c_chats(({ "I will smash your head you stupid worm!",
                 "What do you think you are?" }));

//  set_alarm(1.0,0.0,&set_lord_stats());
}

int special_attack(object enemy)
{
  string what;
//  object bleeding;

  if((!random(15) && (enemy->test_bit("Rhovanion",GROUP,BIT))) ||
     (!random(40)))
  {
    what = ONE_OF_LIST(({"head","left arm","right arm","chest","stomach",
             "left shoulder","left leg","right shoulder",
             "right leg","neck"}));
    enemy->catch_msg(QCTNAME(TO)+" hits your "+what+" very hard.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" hits "+QTNAME(enemy)+"'s "+what+
        " very hard.\n", enemy);

/*    seteuid(getuid());
    bleeding = clone_object(OBJ_DIR+"bleeding");
    bleeding->set_bleeding_where(what);
    bleeding->move(enemy,1);*/

    return 1;
  }
  return 0;
}

varargs mixed
hit_me(int wcpen, int dt, object enemy, int
       attack_id, int target_hitloc)
{
 ENV(TO)->rescue_lord();

 return ::hit_me(wcpen,dt,enemy,attack_id,target_hitloc);
}

