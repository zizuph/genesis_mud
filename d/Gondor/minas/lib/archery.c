inherit "/d/Gondor/common/lib/friend_or_foe";
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <tasks.h>
#include <composite.h>

#include "/d/Gondor/defs.h"

#define DID_ATTACK_HERE  "_attacked_here"
#define ARCHERY_PANIC  "_archery_panic"

int *total_panic,
     fire_id = 0;

void
hook_shout_fire()
{
  tell_room(TO, "Someone shouts: Fire!\n"+
    "A volley of arrows is fired from the top of the walls.\n");
}

void hook_log_killed(object pl)
{
  write_file(LOG_DIR + "goodkill",pl->query_name()+" ("+
    pl->query_average_stat()+ ") killed by archers in Gondor, on "+
    ctime(time())+ ".\n");
}

int hook_check_attacked_here(object pl)
{
  if (pl->query_prop(DID_ATTACK_HERE))
    return 1;
  return 0;
}

void hook_prepare_archers()
{
  tell_room(TO,"Several men with longbows appear upon the battlements.\n"+
    "A voice shouts: Prepare your longbows! Fire at my command!\n");
}

void hook_prepare_again()
{
  tell_room(TO,"Someone shouts: There they are again! Prepare your longbows!\n");
}

public void
may_panic(object pl)
{
  int il;
  object *tm;
  
  if (random(pl->query_panic()) > (10 + (int)pl->query_stat(SS_DIS) * 3))
  {
    tell_object(pl,"You panic!\n");
    tell_room(ENV(pl),QCTNAME(pl)+" panics!\n");
    tm = (object*)pl->query_team_others();
    for (il = 0; il < sizeof(tm); il++)
      if (ENV(pl) == ENV(tm[il]))
        tm[il]->add_panic(25);
    pl->run_away();
    }
}

void
do_whimpy(object pl)
{
  pl->run_away();
}

int filter_enemy(object enemy)
{
  if(!interactive(enemy))
    return 0;
  if(query_friend_or_foe(enemy) == -1)
    return 1;
  else return hook_check_attacked_here(enemy);
  return 0;
}

object *check_enemies()
{
  return filter(all_inventory(this_object()),"filter_enemy",this_object());
}

void
fire_volley_at_enemy()
{
    object *enemy,
           *victims = ({}),
            armour,
            co;
    int     n, i, j,
            dam,
           *hloc_id,
            hloc,
            hit,
            hurt,
            phurt,
            hp,
            tmp;
  int old_prop, cur_pan;
    mixed  *hloc_ac,
            ac;
    string  mstr;

    fire_id = 0;

    enemy = check_enemies();

    n = sizeof(enemy);
    if (!n)
        return;

    hook_shout_fire();
    
    for (i = 0; i < n; i++)
    {
        if ((hit = enemy[i]->resolve_task(TASK_DIFFICULT, ({SKILL_AVG, TS_DEX, 
            SS_AWARENESS, SS_ACROBAT, SS_PARRY, SKILL_END}))) < 0)
        {
            co = enemy[i]->query_combat_object();
            hloc_id = co->query_hitloc_id();
            tmp = random(100);
            for (j = 0, hloc = 0; hloc < sizeof(hloc_id); hloc++)
            {
                hloc_ac = co->query_hitloc(hloc_id[hloc]);
                if (!sizeof(hloc_ac))
                    break;
                j += hloc_ac[1];
                if (j >= tmp)
                    break;
            }
            if (hloc >= sizeof(hloc_id))
        	hloc = sizeof(hloc_id) - 1;

            ac = hloc_ac[3];
    
	    if (sizeof(ac))
	        ac = ac[0];
        if (floatp(ac))
            ac = ftoi(ac);
	    if (!intp(ac))
	        ac = 0;

	    dam = random(400);
 	    ac = random(ac);
	    dam = F_DAMAGE(dam, ac);

            if (dam < 1)
                dam = 0;

            hp = enemy[i]->query_hp();

    /*
     * Wizards are immortal. (immorale ??)
     */
            if ((int)enemy[i]->query_wiz_level() && dam >= hp)
            {
        	tell_object(enemy[i], "Your wizardhood protects you from death.\n");
                tell_room(environment(enemy[i]),
                    QCTNAME(enemy[i]) + " is immortal and fails to die!\n", enemy[i]);
            }
    
            if (dam > 0 && hp)
            {
                phurt = (100 * dam) / hp;
                if (dam && !phurt)
                    phurt = 1;     /* Less than 1% damage */
            }
            else if (dam > 0)
                phurt = 100;
            else
                phurt = -1;   /* Enemy missed */

            if (dam > 0)
                enemy[i]->heal_hp(-dam);
    
    /*
     * Adjust our panic level
     */
            if (phurt >= 0)
             {
               cur_pan = enemy[i]->query_panic();
               old_prop = enemy[i]->query_prop(ARCHERY_PANIC);
               enemy[i]->add_prop(ARCHERY_PANIC,old_prop + 2 + (phurt/5));
               enemy[i]->add_panic(enemy[i]->query_prop(ARCHERY_PANIC) - cur_pan);
                 }
    
            if (phurt == 0)
                mstr = "Several arrows strike the ground near your feet.\n";
            else if (phurt == 1)
                mstr = "An arrow tickles you.\n";
            else if (phurt < 5)
                mstr = "A couple of arrows tickles you.\n";
            else if (phurt < 10)
                mstr = "You are grazed by a couple of arrows.\n";
            else if (phurt < 20)
                mstr = "You are struck by a few arrows.\n";
             else if (phurt < 30)
                 mstr = "Several arrows pierce you.\n";
             else if (phurt < 50)
                 mstr = "You are hurt badly by a hail of arrows.\n";
            else if (phurt < 70)
                mstr = "You are seriously wounded by several well-aimed arrows.\n";
            else if (phurt < 90)
                mstr = "An arrow sinks deep into your body, inflicting a dangerous wound!\n";
             else
                 mstr = "Several arrows strike you, some sinking deep into your body.\n"+
                   "You are mortally wounded!\n";
            enemy[i]->catch_msg(mstr);
            may_panic(enemy[i]);
            if (enemy[i]->query_whimpy())
              if ((enemy[i]->query_hp()*100 / enemy[i]->query_max_hp()) < enemy[i]->query_whimpy()) 
                set_alarm(1.0, 0.0, "do_whimpy", enemy[i]);
            victims += ({enemy[i]});
        }
    }
    switch(sizeof(victims))
    {
        case 0:
            tell_room(TO, "The arrows miss.\n");
            break;
        case 1:
            tell_room(TO,QCTNAME(victims[0]) + " is hit by an arrow.\n", victims[0]);
            break;
        default:
            tell_room(TO,CAP(COMPOSITE_LIVE(victims)) + " are hit by arrows.\n", victims);
            break;
    }
    for (i = 0; i < sizeof(victims); i++)
    {
        if (victims[i]->query_hp() <= 0)
        {
            victims[i]->do_die(TO);
            hook_log_killed(victims[i]);
        }
    }
    if (!fire_id)
        fire_id = set_alarm(3.0 + 6.0*rnd(), 0.0, "fire_volley_at_enemy");
}

void start_archers(int i)
{
  if (fire_id) return;
  if (i) hook_prepare_again();
  else hook_prepare_archers();
  fire_id = set_alarm(3.0+6.0*rnd(),0.0,"fire_volley_at_enemy");
}

