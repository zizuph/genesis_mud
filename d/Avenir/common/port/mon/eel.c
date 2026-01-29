 // Eel               (/d/Avenir/common/port/mon/eel.c)
 // creator(s):       Glinda may -95
 // last update:      Cirion, Feb 96: Fixed special attack, etc.
 // purpose:          Should live in the storeroom of th
 //                   shipwreck.
 // note:
 // bug(s):
 // to-do: Make a small quest where you need to bring a number of eels
 //        to the cook in the bazaar. It is difficult because they
 //        are tough to catch and to keep alive!

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include "/d/Avenir/common/common.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define H_HEAD 0
#define H_BODY 1
#define H_FIN  3

mixed check_get();
void  drown_in_air();
int   query_breathe();

create_creature()
{
    set_name("eel");
    add_name("_Avenir_underwater_eel");
    set_race_name("eel");
    set_short("tiny black eel");
    set_adj(({"tiny", "black"}));
    set_long("A tiny black eel. It looks quite delicious.\n");

    set_stats(({ 20, 35, 30, 20, 20, 35}));

    set_skill(SS_SWIM, 80);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_DEFENCE, 50);

    add_prop(OBJ_M_NO_GET, "@@check_get@@");
    add_prop(MAGIC_I_BREATH_WATER, 10);
    add_prop(CONT_I_WEIGHT, 85);
    add_prop(CONT_I_VOLUME, 100);
    NEVERKNOWN;

    set_hitloc_unarmed(H_HEAD, ({ 40, 35, 50 }), 30, "head");
    set_hitloc_unarmed(H_BODY, ({ 40, 35, 50 }), 20, "head");
    set_hitloc_unarmed(H_FIN, ({ 40, 30, 50 }), 50, "body");

    add_leftover("/std/leftover", "heart", 1, 0, 0, 0);
    add_leftover("/std/leftover", "fin", 2, 0, 0, 0);
    add_leftover("/std/leftover", "tail fin", 1, 0, 0, 0);

    set_act_time(20);
    add_act("emote swims around happily.");
    add_act("emote crackles with tiny sparks of blue electricity.");

    set_alarm(0.1, 0.0, &set_m_in("swims in."));
    set_alarm(0.1, 0.0, &set_m_out("swims"));
}

mixed check_get()
{
    object arm1, arm2;
    int protection;
    string held_in, str;

    arm1 = TP->query_armour(TS_LHAND);
    arm2 = TP->query_armour(TS_RHAND);

    if(arm1) held_in = arm1->short();
    if(arm2) held_in = arm2->short();

    if(TP->query_fatigue() < 6)
       return "You are to exhausted to try to grab it.\n";

    if(query_attack())
       return "The "+short()+" is moving around too quickly to grab.\n";

    if(TP->query_stat(SS_DEX) + TP->query_prop(LIVE_I_QUICKNESS) < random(260))
      {
       TP->add_fatigue(-5);
       return "The "+short()+" darts away from your hands.\n";
      }

    if( (arm1 || arm2) && 
        ( MAX(arm1->query_ac(), arm2->query_ac()) > 5 ) )
     {
       write("You manage to grasp the "+short()+" with your "
            +held_in+".\n");
       return 0;
     }
           
    if(TP->query_magic_res(MAGIC_I_RES_ELECTRICITY) > 40)
     {
       write("You manage to resist the shock the "+short()
            +" gives off.\n");
       return 0;
      }
    
    TP->heal_hp( -random(100) );
    if(!TP->query_hp())
      {
        write("The "+short()+" fries you with a burst of electricity!\n");
        TP->do_die(TO);
        return 1;
       }

    str = "";
    if(held_in)
      str += "Your "+held_in+" does not give enough protection against the "
        +short()+".\n";

    return str + "The " + short() + " shocks you badly when you try to pick it "
       +"up.\n";
}


static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
    object me;
    string how;
    int percent;
    int damage;

    me = this_object();

    percent = (100 - enemy->query_magic_res(MAGIC_I_RES_ELECTRICITY));
    if(percent < 0) percent = 0;
    if(percent > 100) percent = 100;

    damage = random(50) * (percent / 100);

    how = "without effect";
    if (damage > 7)            
        how = "with a shock";
    if (damage > 35)
        how = "stunningly";
    if (damage > 45)
        how = "searingly";

    enemy->reduce_hit_point(damage);

    me->catch_msg("Your electricity hits " + how + ".\n");
    enemy->catch_msg("A dart of electricity flies from the eel, striking " +
                  "you " + how + ".\n");
    tell_watcher("A dart of electricity flies from the eel, striking " +
                  QTNAME(enemy) + how + ".\n", enemy);

    if(enemy->query_hp() <= 0)
        enemy->do_die(me);

    return 1;
}

void drown_in_air()
{
   if(!query_breathe())
    {
     tell_room(ENV(TO), QCTNAME(TO) + " gasps for water one last time.\n");
     heal_hp(-query_max_hp());
     do_die(ENV(TO));
    }
}

/* NB query_breathe would need to be called in the eel
 * when the player leaves water. Ie, one would want to
 * do a deep_inventory search of the player upon leaving
 * and call query_breathe() in each eel it finds.
 */
int query_breathe()
{
   object dest;

   dest = ENV(TO);
   if(dest->query_prop(OBJ_I_CONTAIN_WATER))  return 1;

   if(!dest->query_prop(ROOM_I_IS))
    dest = ENV(dest);
   if(!dest->query_prop(ROOM_I_IS))
    dest = ENV(dest);
   if(!dest->query_prop(ROOM_I_IS))
    dest = ENV(dest);
   if(!dest->query_prop(ROOM_I_IS))
    dest = ENV(dest);  // I think 4 sub-containers is enough to check...

   if(dest->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER &&
      dest->query_prop(ROOM_I_TYPE) != ROOM_UNDER_WATER &&
     !dest->query_prop(OBJ_I_CONTAIN_WATER) )
       {
        set_alarm(5.0, 0.0, drown_in_air);
        return 0;
       }
   else
        return 1;
}

void enter_env(object dest, object old)
{
   ::enter_env(dest, old);

   if(!query_breathe())
    {
      tell_room(ENV(TO), QCTNAME(TO) + " starts to gasp for water.\n");
    }
}




