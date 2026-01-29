inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

static float duration = 240.0;

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
  if (shadow_double("/d/Earthsea/guilds/roke/spells/occurrere_obj",
		    spell_target))
    {
      return 0;
    }
  if (!shadow_me(spell_target))
    {
#if _DEBUG
      spell_target->catch_msg("Your spell failed, cannot shadow.\n");
#endif
      return 0;
    }
  set_alarm(duration, 0.0, dispel_spell_effect);
  return 1;
}

public void set_duration(float sec)
{
  duration = sec;
}

/***** Mask to disable all spell casting *****/
public int
start_spell(string spell, mixed arg, object spellob)
{
  shadow_who->catch_msg("You feel utterly powerless right now.\n");
  return 0;
}

varargs public int
dispel_spell_effect(object dispeller)
{
  int i;

  if (!shadow_who)
    {
      remove_spell_effect_object();
      return 1;
    }
  shadow_who->catch_msg("You feel your magical powers returning.\n");
  remove_spell_effect_object();
}
