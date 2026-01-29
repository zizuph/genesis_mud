inherit "/std/poison_effect";

#include <poison_types.h>
#include <stdproperties.h>

#define DEBUG_WHO environment()
#define DEBUG_ON
#include "/d/Emerald/sys/debug.h"

static int started;

void create_poison_effect()
{
  set_interval(random(15));
  set_time(random(100) + 100);
  set_poison_type("frufru powder");
  set_damage(({ POISON_HP, random(200), POISON_USER_DEF }));
}

void special_damage(int damage)
{
  DEBUG("Special damage");
  environment()->cmdhooks_break_spell();
}

void enter_env(object env, object from)
{
  ::enter_env(env, from);

  if (!living(env))
  {    
    return;
  }

  start_poison();
  started = 1;
  env->add_prop(LIVE_I_SEE_INVIS, 
      env->query_prop(LIVE_I_SEE_INVIS) - 100);
  env->add_prop(LIVE_I_QUICKNESS, 
      env->query_prop(LIVE_I_QUICKNESS) - 50);      
}

void leave_env(object env, object to)
{
  ::leave_env(env, to);

  if (!started)
  {
    return;
  }

  started = 0;
  env->add_prop(LIVE_I_SEE_INVIS, 
      env->query_prop(LIVE_I_SEE_INVIS) + 100);
  env->add_prop(LIVE_I_QUICKNESS,
      env->query_prop(LIVE_I_QUICKNESS) + 50);
}    
