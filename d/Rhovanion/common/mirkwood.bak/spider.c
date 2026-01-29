/*
spiders are interesting creatures.  They can only bite.  But if they
bite you you have a random chance of being stunned, and they will try to
web you up.
*/

inherit "/std/creature";
inherit "/std/combat/unarmed"; 
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/std/act/attack";

#include "/d/Rhovanion/lib/kill_log.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include "/d/Rhovanion/defs.h"

#define RELATIVE_DIR    ({"forward","rightforward", \
                          "right","rightbackwards", \
                          "backwards","leftbackwards", \
                          "left","leftforward"})
#define STD_DIR     ({"north","northeast","east","southeast", \
                      "south","southwest","west","northwest"})

#define WEB     OBJ_DIR+"web"
#define LEG     OBJ_DIR+"spider_leg"

#define LEG_IS_LIVE "_leg_is_live"
/* this is to mark that leg was chopped from live spider */

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1

int number_of_legs_missing = 0;

create_creature()
{
    set_name("spider"); 
    set_race_name("spider");
    set_short("black spider");
    set_adj(({"black", "menacing" }));
    set_long("It looks rather menacing!\n"+"@@leg_desc@@");
    set_gender(G_NEUTER);

    /* 
    str, con, dex, int, wis, dis
    somebody tell me if these are good values
    */

    set_stats(({ 55, 150, 80, 29, 31, 100}));

    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 20, 25, 30, 20 }), 72, "body");

    set_hitloc_unarmed(2, ({ 30, 20, 20, 20 }), 1, "leg");
    set_hitloc_unarmed(3, ({ 30, 20, 20, 20 }), 1, "leg");
    set_hitloc_unarmed(4, ({ 30, 20, 20, 20 }), 1, "leg");
    set_hitloc_unarmed(5, ({ 30, 20, 20, 20 }), 1, "leg");
    set_hitloc_unarmed(6, ({ 30, 20, 20, 20 }), 1, "leg");
    set_hitloc_unarmed(7, ({ 30, 20, 20, 20 }), 1, "leg");
    set_hitloc_unarmed(8, ({ 30, 20, 20, 20 }), 1, "leg");
    set_hitloc_unarmed(9, ({ 30, 20, 20, 20 }), 1, "leg");

    set_skill(SS_DEFENCE, 100);

/* these values might be wrong */
    set_attack_unarmed(A_BITE,  15, 20, W_IMPALE, 100, "jaws");

    set_chat_time(2);
    add_chat("@@spider_chat@@");

    set_cchat_time(2);
    add_cchat("@@spider_cchat@@");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alarm(0.0, 0.0, "do_move");

    set_aggressive(1);

    add_leftover(LEG, "leg", 8, 0, 0, 0);
}
	
/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = TO;
    ob = FILTER_LIVE(all_inventory(ENV(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 0 then there will be no
 * additional web attack.
 */
int
special_attack(object enemy)
{
  object me, paralyze, web;
  mixed weapon, *hitresult;
  int i;

  me = TO;

  if (present("_spider_paralyze_", enemy) && (number_of_legs_missing < 6))
  {
    if (random(4+number_of_legs_missing))
    {
      tell_room(ENV(TO), QCTNAME(me) + " failed to web " + 
                               QTNAME(enemy) + ".\n", enemy);
      return 1;
    }
    seteuid(getuid());
    web = clone_object(WEB);
    web->move(ENV(TO));

    enemy->catch_msg(QCTNAME(me) + " spins a web around you!\n");
    tell_room(ENV(TO), QCTNAME(me) + " spins a web around " + 
                             QTNAME(enemy) + ".\n", enemy);
    enemy->move(web);
    return 1;
  }

  if (random(7+number_of_legs_missing))
    return 0;

  hitresult = enemy->hit_me(F_PENMOD(20+random(20), 40+random(40)), 
                             W_IMPALE, me, -1);

  enemy->catch_msg(QCTNAME(me) + " stings you!\n");
  tell_watcher(QCTNAME(me)+" stings "+QTNAME(enemy)+".\n", enemy);

  if (hitresult[0] > 0)
  {
    enemy->catch_msg("You are stunned by " + QTNAME(me) + "'s bite.\n");
    tell_watcher(QCTNAME(enemy)+" is stunned by "+QTNAME(me)+"'s bite.\n", 
                  enemy);
    seteuid(getuid());
    paralyze = clone_object("/std/paralyze");
    paralyze->set_name("_spider_paralyze_");
    paralyze->set_no_show(1);
    paralyze->set_remove_time(MAX(1,hitresult[2]));
    paralyze->set_stop_message("You shake your head as you regain "+
                               "your senses!\n");
    paralyze->set_fail_message("You can't do that, you are still stunned!\n");
    paralyze->set_stop_verb("depart");	/* No command to stop the paralyze! */
    paralyze->set_stop_object(0);	/* Use the messages set above */
    
    if(weapon = enemy->query_weapon(W_RIGHT))
      if(!weapon->move(ENV(enemy)))
      {
        enemy->catch_msg("You drop "+weapon->query_short()+".\n");
        tell_room(ENV(enemy), QCTNAME(enemy)+" drops "+
                              weapon->query_short()+".\n", enemy);
      }
    if(weapon = enemy->query_weapon(W_LEFT))
      if(!weapon->move(ENV(enemy)))
      {
        enemy->catch_msg("You drop "+weapon->query_short()+".\n");
        tell_room(ENV(enemy), QCTNAME(enemy)+" drops "+
                              weapon->query_short()+".\n", enemy);
      }
    if(weapon = enemy->query_weapon(W_BOTH))
      if(!weapon->move(ENV(enemy)))
      {
        enemy->catch_msg("You drop "+weapon->query_short()+".\n");
        tell_room(ENV(enemy), QCTNAME(enemy)+" drops "+
                              weapon->query_short()+".\n", enemy);
      }

    paralyze->move(enemy, 1);	/* Now DO the paralyze */
    enemy->stop_fight(enemy->query_attack());
  }

  if(enemy->query_hp() <= 0)
    enemy->do_die(me);
    
  return 1;
}


void
set_living_name(string name)
{
    efun::set_living_name(name);
}


void
do_move()
{
  int i, j, s;
  string room, *exits;
  object paralyze, web, food, *inweb;
  mixed *hitresult;

  if(number_of_legs_missing > 5) return; /* spider cant move anymore */

  if(web = present("web",ENV(TO)))
  {
    if(sizeof(inweb=FILTER_LIVE(all_inventory(web))))
    {
      food = inweb[0];
      hitresult = food->hit_me(F_PENMOD(40+random(20), 50+random(40)), 
                                        W_IMPALE, TO, -1);

      food->catch_msg("Something stings you!\n");
      tell_watcher(QCTNAME(TO)+" stings web.\n", food);

      if(!present("_spider_paralyze_", food) && (hitresult[0] > 0))
      {
        food->catch_msg("You are stunned.\n");
        seteuid(getuid());
        paralyze = clone_object("/std/paralyze");
        paralyze->set_name("_spider_paralyze_");
        paralyze->set_no_show(1);
        paralyze->set_remove_time(MAX(1,hitresult[2]/2));
        paralyze->set_stop_message("You regain your senses!\n");
        paralyze->set_fail_message("You can't do that, you are stunned!\n");
        paralyze->set_stop_verb("depart");/* No command to stop paralyze! */
        paralyze->set_stop_object(0);	/* Use the messages set above */
        paralyze->move(food, 1);	/* Now DO the paralyze */
      }
      if(food->query_hp() <= 0)
      food->do_die(TO);
    }
    set_alarm(itof(random(20)+10), 0.0, "do_move");
    return;
  }
  if(query_attack())
  {
    set_alarm(itof(random(20)+10), 0.0, "do_move");
    return;
  }
  exits = ENV(TO)->query_exit_cmds() & STD_DIR;
  if(s = sizeof(exits))
  {
    i = random(s);
    for(j=0; j<s ; j++)
    {
      room=ENV(TO)->query_next_room_letter(TO,exits[(i+j) % s]);
      if(ENV(TO)->this_is_room(room) && 
         (member_array(room, ENV(TO)->query_no_spiders()) == -1))
      {
        command(exits[(i+j) % s]);
        set_alarm(itof(random(20)+10), 0.0, "do_move");
        return;
      }
    }
    set_alarm(itof(random(20)+10), 0.0, "do_move");
    return;  /* no exit suitable for spider */
  }
  else
  {
    exits = TO->local_cmd() & RELATIVE_DIR;
    if(s = sizeof(exits))
    {
      i = random(s);
      for(j=0; j<s ; j++)
      {
        room=ENV(TO)->query_next_room_letter(TO,exits[(i+j) % s]);
        if(ENV(TO)->this_is_room(room) && 
           (member_array(room, ENV(TO)->query_no_spiders()) == -1))
        {
          command(exits[(i+j) % s]);
          set_alarm(itof(random(20)+10), 0.0, "do_move");
          return;
        }
      }
    }
  }
}

void
init_attack()
{
    set_alarm(itof(random(5)+2), 0.0, "slow_init_attack", TP);
}

void
slow_init_attack(object tp)
{
    if (!tp || query_attack() || !present(tp, environment())) return;

    /* wizards aren't attacked... */
    if (tp->query_wiz_level()) return;

    /* Spiders aren't attacked either */
    if (tp->query_race_name() == "spider") return;

    aggressive_attack(tp);
}

string
spider_chat()
{
  string *list1, *list2;

  list1 = ({"I want to eat it now!", "I think it's dead now!", 
            "Shelob says you should hang them for days first.",
            "It's still wriggling!  It's not dead yet!",
            "I am hungry now!", "Are you sure this web will hold it?",
            "Why don't you sting it again?",
            "Why do we always have to do what you say anyhow?"});
  list2 = ({"I want something to eat!", "Plump and tasty!", 
            "I am hungry now!"});

  if(present("web",ENV(TO)))
    return ONE_OF_LIST(list1);
  return ONE_OF_LIST(list2);
}

string
spider_cchat()
{
  string *list;

  list = ({"Bite it!", "Sting it!", "Web it!", "It looks plump and tasty!"});

  return ONE_OF_LIST(list);
}

/*
 * Function name: cr_got_hit
 * Description:   Tells us that we got hit. It can be used to reduce the ac
 *                for a given hitlocation for each hit.
 * Arguments:     hid:   The hitloc id
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage in hit points
 */
void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
  if((hid > 1) && dam)
    set_alarmv(0.0,0.0,"my_remove_hitloc",({hid,att}));
  ::cr_got_hit(hid, ph, att, aid, dt, dam);
  return;
}

void
my_remove_hitloc(int id, object att)
{
  string text = (TO->query_combat_object())->query_hitloc(id)[2];
  object leg;

  if(remove_hitloc(id))
  {
    number_of_legs_missing += 1;
    remove_hitloc(H_BODY);
    set_hitloc_unarmed(H_BODY, ({ 20, 25, 30, 20 }), 
                               72+number_of_legs_missing, "body");

    TO->set_stat_extra(SS_DEX, 
             -number_of_legs_missing * TO->query_stat(SS_DEX) / 10);
    TO->set_skill_extra(SS_DEFENCE, 
             -number_of_legs_missing * TO->query_skill(SS_DEFENCE) / 10);

    add_leftover(LEG, "leg", 8-number_of_legs_missing, 0, 0, 0);

    leg = clone_object(LEG);
    leg->add_prop(LEG_IS_LIVE, 1);
    leg->move(ENV(TO));

    att->catch_msg("You chopped off the "+text+" from "+QTNAME(TO)+".\n");
    tell_room(ENV(TO),QCTNAME(att)+" chopped off the "+text+
                      " from "+QTNAME(TO)+".\n", att);
  }
  return;
}

string
leg_desc()
{
  string text;

  switch(number_of_legs_missing)
  {
    case 0:
      text = "";
      break;
    case 8:
      text = "This one doesn't have any legs left.\n";
      break;
    case 7:
      text = "This one has only one leg left.\n";
      break;
    default:
      text = "This one has only "+
             LANG_WNUM(8-number_of_legs_missing)+" legs left.\n";
  }
  return text;
}
