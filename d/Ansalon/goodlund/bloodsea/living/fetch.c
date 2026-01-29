/* Navarre June 25th 2006, added heal when attacked.
 * to avoid bouncers.
 * Also auto remove after 30 minutes, to not allow
 * a large group to be left there to annoyance for
 * others.
 */


/* Navarre December 28th 2006,
 * Added check to ensure fetch cant hurt anyone that
 * isn't in the room with him
 *
 * Navarre December 16th 2011,
 * Added check for players in the room before removing the fetch.
 * People would fight him for 30 minutes and he would disappear.
 */

#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <money.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
inherit "/std/act/action.c";
inherit "/lib/unique";
inherit AM_FILE

void remove_me(object me);

void
create_krynn_monster()
{
    set_race_name("fetch");
    set_name("fetch");
    add_name("_fetch");
    set_long("An evil death-dealer that exists on the planes " +
       "of the Abyss.\n");

    set_stats(({100,100,100,100,100,100}));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);

    MONEY_MAKE(random(10),"gold")->move(TO,1);  

    set_alignment(-1200);
    set_knight_prestige(100);
    set_all_hitloc_unarmed(35);
    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 15);
    set_aggressive(1);
    set_exp_factor(120);  // Paralyze special attack.

    set_act_time(random(40));
    add_act("scream");
    add_act("cackle");
    add_act("grin");
    set_alarm(1800.0, 0.0, &remove_me(this_object()));
}

void
remove_me(object me)
{
  if (!me)
  {
	  return;
  }
  
  object* players = FILTER_PLAYERS(all_inventory(environment(me)));
  if (sizeof(players))
  {
	  set_alarm(1800.0, 0.0, &remove_me(me));
  }
  else
  {
      me->remove_object();
  }
}

void
arm_me()
{
    seteuid(getuid(TO)); 
    clone_object("/d/Krynn/icewall/plains/obj/claw")->move(TO, 1);
    clone_unique(BOBJ + "mag_greaves", 5)->move(TO, 1);

    command("wield all");
    command("wear all");
}

void print_msg(object me)
{
  tell_room(environment(me),QCTNAME(me)+" seems to grow stronger.\n");
}

public void
attacked_by(object ob)
{
  ::attacked_by(ob);
  set_alarm(0.0, 0.0, &print_msg(this_object()));
  this_object()->set_hp(query_max_hp());
}


int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    attacktype = random(7);

    hitloc = ({"left arm","right arm","body","left leg","right leg","head"});

    if(!present(enemy, environment(this_object())))
    {
        return 0;
    }

    if (attacktype == 1)
    {
        pen = random(200);
        hitres = enemy->hit_me(pen, 40, TO, -1);

        wloc = random(6);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "barely grazes";
        if(hitres[0] > 0)
            how = "just grazes";
        if(hitres[0] > 10)
            how = "grazes";
        if(hitres[0] > 20)
            how = "scratches";
        if (hitres[0] > 40)
            how = "deeply buries themselves into";
        if (hitres[0] > 60)
            how = "penetrates";

        enemy->catch_msg(QCTNAME(TO) + 
            " claws at you.  "+QCTNAME(TO)+ " "+how+" your "+ hitloc[wloc] +" with "+
             HIS(TO)+" claws.\n");

        tell_room(E(TO), QCTNAME(TO) + " claws " +
          "at " + QTNAME(enemy) + ". The claws " +
          how + " " + QTNAME(enemy) +
          "'s " + hitloc[wloc] + ".\n",({enemy, TO}));

         if(!P("ghoul_paralyze", enemy))
             clone_object("/d/Ansalon/dargaard/obj/ghoul_stun")->move(enemy);

        enemy->heal_hp(-pen);
        TO->heal_hp(pen);

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }
        return 1;
    }
    return 0;
}
