#include "/d/Immortal/std/domain.h"
#include <stdproperties.h>

#define ATTACK_TIME 20
#define TIME_VAR 10
#define ATTACK_CHANCE 100

inherit STDOBJECT;

void
create_object()
{
  ::create_object();
  set_name("_taiga_attack_object");
  add_name("t_attack");
  set_short("taiga attack object");

  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_M_NO_GIVE,1);
  add_prop(OBJ_I_INVIS,1);
}

void
init()
{
  ::init();
  set_alarm(10.0, 0.0, "check_attack");
}

int
in_taiga()
{
string where, a, b;

  where = file_name(environment(environment()));

  if(sscanf(where, "%staiga%s", a, b) != 2)
    return 0;
  else
    return 1;
}

void
make_new_attack()
{
int time;

  time = ATTACK_TIME - (TIME_VAR / 2) + random(TIME_VAR);

  set_alarm(itof(time), 0.0, "check_attack");
}


void
check_attack()
{
  if(!in_taiga())
    {
    remove_object();
    return;
    }

  if((random(100) + 1) > ATTACK_CHANCE)
    {
    make_new_attack();
    return;
    }

  environment()->catch_msg("If the forest attacks were installed in the attack "+
    "object, you'd be under attack now *grin*.\n");
  make_new_attack();
  return;
}
