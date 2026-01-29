#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/armour";

#define ROKE_I_HAS_ARMA "_roke_i_has_arma"
#define ARMA_GLOW_AURA "_arma_glow_aura"

#define REFRESH_INTERVAL 60.0
#define MANA_COST 10
static float duration = 240.0;

#define _DEBUG 1

#if _DEBUG
object wiz = find_player("ckrik");
#endif

void consume_mana()
{
  if (spell_target->query_mana() < MANA_COST)
  {
    dispel_spell_effect();
    return;
  }
  spell_target->add_mana(-MANA_COST);
  tell_room(environment(spell_target),
	    "The globe of light enveloping " + QTNAME(spell_target) +
	    " brightens for a moment and then returns to as before.\n",
	    spell_target, spell_target);
  spell_target->catch_msg("The globe of light enveloping you brightens " +
			  "for a moment and then returns to as before.\n");
  set_alarm(REFRESH_INTERVAL, 0.0, consume_mana);
}

public create_armour()
{
  set_name("globe");
  set_pname("globes");
  set_short("globe of force");
  set_pshort("globes of force");
  add_prop(OBJ_I_INVIS, 1);
  add_prop(OBJ_I_NO_GIVE, 1);
  add_prop(OBJ_I_NO_DROP,1);
  add_prop(OBJ_I_NO_STEAL, 1);
  add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
  add_prop(OBJ_S_WIZINFO, "A magical globe of force.\n");
  add_prop(MAGIC_AM_MAGIC, ({ 20, "conjured" }) );
  add_prop(OBJ_I_VOLUME, 0);
  add_prop(OBJ_I_WEIGHT, 0);
  add_prop(OBJ_I_VALUE, 0);
  set_no_show();
  set_default_armour(10, A_MAGIC);
  set_shield_slot(({A_HEAD, A_R_ARM, A_L_ARM, A_TORSO, A_LEGS}));
  add_prop(OBJ_I_LIGHT, 1);
}

public int
start()
{
  mixed result;
  spell_target->wear_arm(this_object());
#if _DEBUG
  /*
  if (stringp(result))
    {
      wiz->catch_msg("DEBUG: " + result + "\n");
    }
  */
#endif
  spell_target->add_subloc(ARMA_GLOW_AURA, this_object());
  spell_target->add_prop(ROKE_I_HAS_ARMA, 1);
  set_alarm(duration, 0.0, dispel_spell_effect);
  set_alarm(REFRESH_INTERVAL, 
	    0.0, consume_mana);
  return 1;
}

string
show_subloc(string subloc, object wearer, object for_obj)
{
  string str;
  if (wearer->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    return ""; /* don't show this subloc as inventory */
  if (for_obj == wearer)
    str = "You are protected by an enveloping globe of light.\n";
  else
    str = capitalize(wearer->query_pronoun())+
      " is protected by an enveloping globe of light.\n";
  return str;
}

public void set_duration(float sec)
{
  duration = sec;
}

varargs public int
dispel_spell_effect(object dispeller)
{
  say("The enveloping globe of light protecting " + 
      QTNAME(spell_target) + " disappears.\n");
  spell_target->catch_msg("The enveloping globe of light protecting you " +
			  "disappears.\n");
  spell_target->remove_subloc(ARMA_GLOW_AURA);
  spell_target->remove_prop(ROKE_I_HAS_ARMA);
  spell_target->remove_arm(this_object());
  remove_spell_effect_object();
}

int *
query_shield_slots()
{
  return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

