inherit "/std/shadow";

/* this is in heartbeats */
#define TIME_TO_HEAL       2500
#define RANDOM_TIME_BONUS  random(750)

#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

static int init_age;
static int hit_points;
static object bleeding;

int *
query_bleeding_variables()
{
  return ({ hit_points, init_age });
}
void
set_bleeding_variables(int a, int b)
{
  hit_points = a;
  init_age = b;
}

void
heal_hp(int hp)
{
  int max = shadow_who->query_max_hp();

  hit_points += hp;
  if (hit_points < 0) hit_points = 0;
  if (hit_points > max) hit_points = max;
  shadow_who->set_hp(hit_points);
}

int
query_hp()
{
  shadow_who->set_hp(hit_points);
  if(!hit_points)
    shadow_who->heal_hp(-100000);
  return hit_points;
}

void
autoload_shadow(mixed arg){}

public varargs int
shadow_me(mixed to_shadow)
{
  if(stringp(to_shadow))
    to_shadow = find_player(to_shadow);
  if(!to_shadow)
    to_shadow = previous_object();
  if(to_shadow)
  {
    hit_points = to_shadow->query_hp();
    init_age = (to_shadow->query_age())-RANDOM_TIME_BONUS;
  }
  set_alarm(itof(60+random(120)), 0.0, "slowly_die");
  return ::shadow_me(to_shadow);
}

void
set_bleeding(object arg)
{
  bleeding = arg;
}

void 
do_die(object killer)
{
  if(query_hp() > 0) return;
  shadow_who->do_die(killer);
  set_alarm(2.0, 0.0, "end_this_bleeding");
}

void
end_this_bleeding()
{
  shadow_who->catch_msg("Your "+bleeding->short()+" finally heals.\n");
  shadow_who->set_stat_extra(SS_STR, 0);
  shadow_who->set_stat_extra(SS_DEX, 0);
  bleeding->remove_object();
}

void
slowly_die()
{
  string text = bleeding->query_bleeding_where();
  int aaa, b_stat, max_hp = shadow_who->query_max_hp();


  /*
   * Linkdead players can not be hurt.
   */
  if (!(shadow_who->query_npc()) && !query_ip_number(shadow_who))
  {
    set_alarm(itof(60+random(120)), 0.0, "slowly_die");
    init_age += 60; /* but they will not heal while LD either! */
    return;
  }

  if(init_age+TIME_TO_HEAL < shadow_who->query_age())
  {
    end_this_bleeding();
    return;
  }

  shadow_who->catch_msg("Your life runs out through the "+
             bleeding->short()+(text ? " on your "+text : "")+".\n");
  tell_room(ENV(shadow_who), QCTNAME(shadow_who)+"'s "+
	bleeding->short()+(text ? " on "+HIS(shadow_who)+" "+text : "")+
	" still does not heal.\n", shadow_who);

  shadow_who->drink_soft(-MIN(shadow_who->query_prop(LIVE_I_MAX_DRINK)/5, 
		              shadow_who->query_soaked()));

  if(!(shadow_who->query_soaked()))
    heal_hp(-max_hp / 15);

  b_stat = shadow_who->query_base_stat(SS_STR);
  aaa = (b_stat * (max_hp - hit_points)) / max_hp;
  shadow_who->set_stat_extra(SS_STR, -aaa);
  b_stat = shadow_who->query_base_stat(SS_DEX);
  aaa = (b_stat * (max_hp - hit_points)) / max_hp;
  shadow_who->set_stat_extra(SS_DEX,  -aaa);

  shadow_who->add_fatigue(-shadow_who->query_max_fatigue() / 10);

  if(query_hp() <= 0)
  {
    shadow_who->catch_msg("You bleed to death from the "+
             bleeding->short()+(text ? " on your "+text : "")+".\n");
    tell_room(ENV(shadow_who), QCTNAME(shadow_who)+
		" bleeds to death from the "+bleeding->short()+
		(text ? " on "+HIS(shadow_who)+" "+text : "")+".\n", 
		shadow_who);
    do_die(bleeding);
  }
  set_alarm(itof(60+random(120)), 0.0, "slowly_die");
}
