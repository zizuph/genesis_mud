#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

inherit "/d/Genesis/newmagic/spell_effect_object";

#define ROKE_I_HAS_DELIGO "_roke_i_has_deligo"

static float duration = 240.0;
int extra_slow = 0;

#define _DEBUG 1

#if _DEBUG
object wiz = find_player("ckrik");
#endif

public int
start()
{
#if _DEBUG
  /*
  if (stringp(result))
    {
      wiz->catch_msg("DEBUG: " + result + "\n");
    }
  */
#endif
  spell_target->add_prop(ROKE_I_HAS_DELIGO, 1);
  spell_target->add_prop(LIVE_I_QUICKNESS, 
			 spell_target->query_prop(LIVE_I_QUICKNESS) - 
			 extra_slow);
  set_alarm(duration, 0.0, dispel_spell_effect);

  return 1;
}

public void set_slow(int slow)
{
  extra_slow = slow;
}

public void set_duration(float sec)
{
  duration = sec;
}

varargs public int
dispel_spell_effect(object dispeller)
{
  say(QCTNAME(spell_target) + " seems to start moving freely again.\n",
      spell_target);
  spell_target->catch_msg("You start moving freely again.\n");
  spell_target->remove_prop(ROKE_I_HAS_DELIGO);
  spell_target->add_prop(LIVE_I_QUICKNESS, 
			 spell_target->query_prop(LIVE_I_QUICKNESS) +
			 extra_slow);
  remove_spell_effect_object();
}
