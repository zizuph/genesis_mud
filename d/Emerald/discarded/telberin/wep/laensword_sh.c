/* laensword_sh.c created by Shiva@Genesis.
 * This file created to be used with the light-laen longsword (laensword.c)
 * It takes care of the sword's healing ability and causes the sword
 * to light when evil or undead livings arrive.
 */

inherit "/std/shadow";

#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/sys/macros.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define DEBUG_WHO shadow_who
#include DEBUGFILE

static private int    last_heal_hp;  // Last time I updated my hitpoints
static private int    start_flag;    // True if heal values initialized
static private int    light_flag;    // True if sword is lit
static private object sword;

static void calc_heal_amnt();

void remove_laensword_sh()
{
  DEBUG("Removing shadow");
  calc_heal_amnt();
  remove_shadow();
}

int query_laensword_sh()
{
  return 1;
}

void remove_light()
{
#ifdef LIGHT_SWORD
  object env;

  CP(sword, OBJ_I_LIGHT, -1);

  shadow_who->update_light(0);

  if (env = environment(shadow_who))
  {
    env->update_light(0);
  }
#endif

  light_flag = 0;
}  

void delay_msg()
{
  tell_room(environment(shadow_who), QCTNAME(shadow_who) + "'s longsword " +
      "glows momentarily with a blue aura.\n", shadow_who);
  shadow_who->catch_msg("Your longsword glows momentarily with a blue " +
      "aura.\n");
}

void init_living()
{
  object env;

  shadow_who->init_living();

  if (member_array(sword, shadow_who->query_weapon(-1)) < 0)
  {
    remove_laensword_sh();
    return;
  }  

  if (shadow_who->query_invis() && IS_WIZ(shadow_who))
  {
    return;
  }

  if (!IS_WIZ(TP) &&
      ((this_player()->query_alignment() < -500) ||
      (this_player()->query_prop(LIVE_I_UNDEAD) ||
      CREATURE_OF_VS(this_player()))))
  {
    if (!light_flag)
    {
      /* We have to delay a moment or our message will show up before
       * the room description or this_player()'s entrance message.
       */

      set_alarm(0.0, 0.0, delay_msg);

      shadow_who->reveal_me(1);
      TP->reveal_me(1);

#ifdef LIGHT_SWORD
      CP(sword, OBJ_I_LIGHT, 1);
      shadow_who->update_light(0);

      if (env = environment(shadow_who))
      {
        env->update_light(0);
      }
#endif

      set_alarm(2.0, 0.0, remove_light);
      light_flag = 1;
    }     
  }
}

static void start_heal()
{
  if (!start_flag)
  {
    last_heal_hp = time();
    start_flag = 1;
  }
}

static void calc_heal_amnt()
{
  int n;

  if (F_INTERVAL_BETWEEN_HP_HEALING)
  {
    n = (time() - last_heal_hp) / F_INTERVAL_BETWEEN_HP_HEALING;

    if (n > 0)
    {
      shadow_who->heal_hp(n * 6);
      DEBUG("(Sword) Healing " + (n * 20) + " hitpoints.");
      last_heal_hp += n * F_INTERVAL_BETWEEN_HP_HEALING;
    }
  }
}

int query_hp()
{
  if (member_array(sword, shadow_who->query_weapon(-1)) < 0)
  {
    set_alarm(0.5, 0.0, remove_laensword_sh);
  }
  else
  {
    calc_heal_amnt();
  }

  return shadow_who->query_hp();
}

int add_sword_sh(object who, object ob)
{
  int res;

  if ((sword = ob) && (res = shadow_me(who)))
  {
    DEBUG("Shadow added.\nSword: " + file_name(sword));
    start_heal();
  }
  else
  {
    remove_shadow();
  }

  return res;
}

void set_alignment(int a)
{
  shadow_who->set_alignment(a);
  sword->update_sword();
}
