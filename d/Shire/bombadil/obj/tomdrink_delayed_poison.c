#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <poison_types.h>

#define MANA_DROP_EVIL 200
#define HEAL_EVIL      30

#define MANA_DROP_GOOD  100
#define HEAL_GOOD       350

public void do_poison (object who, int num)
{
  object poison, *poisons = ({});
  string race;
  int i;

  FIXEUID

  if (num)
  {
    for (i = 0 ; i < num ; i ++)
    {
      poison = clone_object("/std/poison_effect");
      poison -> set_interval(10);
      poison -> set_time(600);
      poison -> set_damage(({POISON_FATIGUE, 25, POISON_HP, 125}));
      poison -> set_poison_type("shire_withy_water");
      poison -> move(who, 1);
      poisons += ({ poison });
      who->add_mana(-MANA_DROP_EVIL);
    };

    write("You suddenly feel ill.\n");
    say(QCTNAME(who) + " breathes heavily realizing that " + 
    HE_SHE(who) + " has been poisoned!\n");
    poisons -> start_poison();
  };

  destruct ();
}
