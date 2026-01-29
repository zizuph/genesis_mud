inherit "/d/Rhovanion/common/npcs/goblins/goblin.c";

#include "/d/Rhovanion/defs.h"
#include <macros.h>

/* group and bit for finished prisoner quest */
#define GROUP   0
#define BIT     9

void create_goblin()
{
  set_base_gob(120);
  set_ran_gob(40);
  set_ran_wep(({ "club" }));
  set_ran_arm(({ "shield" }));
  set_def_arm(({ "mail", "helm" }));
  set_looks(({ "lord" }));
  set_chats(({ "Get out of here!!!  I have called NOBODY!!!",
              "Do I have to call guards or should I kill you myself?",
             "How did you get here???",
            "I will stop giving food to those stupid guards that let you in!"
            }));
  set_c_chats(({ "I will smash your head you stupid worm!",
                 "What do you think you are?" }));
}

int special_attack(object enemy)
{
  string what;
  object bleeding;

  if(!random(30) && (enemy->test_bit("Rhovanion",GROUP,BIT)))
  {
    what = ONE_OF_LIST(({"head","left arm","right arm","chest","stomach",
             "left shoulder","left leg","right shoulder",
             "right leg","neck"}));
    enemy->catch_msg(QCTNAME(TO)+" hits your "+what+" very hard.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" hits "+QTNAME(enemy)+"'s "+what+
        " very hard.\n", enemy);

    seteuid(getuid());
    bleeding = clone_object(OBJ_DIR+"bleeding");
    bleeding->set_bleeding_where(what);
    bleeding->move(enemy,1);

    return 1;
  }
  return 0;
}
