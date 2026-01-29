
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BASE_GOB 120
#define RAN_GOB  40
#define RANDOM_WEAPONS  ({ "club" })
#define RANDOM_ARMOURS  ({ "shield" })
#define DEFAULT_ARMOURS ({ "mail", "helm" })
#define ALIGNLOOKS      ({ "lord" })

/* group and bit for finished prisoner quest */
#define GROUP               0
#define BIT_SOLVED          9    

#define CHAT_LIST ({ "Get out of here!!!  I have called NOBODY!!!", \
                 "Do I have to call guards or should I kill you myself?", \
             "How did you get here???", \
         "I will stop giving food to those stupid guards that let you in!" \
                  })
#define COMBAT_CHAT_LIST ({ "I will smash your head you stupid worm!", \
                            "What do you think you are?" })

#include "/d/Rhovanion/common/npcs/goblins/goblin.c"


int
special_attack(object enemy)
{
  string what;
  object bleeding;

  if(!random(30) && (enemy->test_bit("Rhovanion",GROUP,BIT_SOLVED)))
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
    bleeding->move(enemy);

    return 1;
  }
  return 0;
}
