/* 
 * This is /d/Gondor/morgul/npc/centipede.c, copied 
 *  in parts from
 *  /d/Gondor/common/npc/midge.c.
 * Olorin, Nov 1993
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/trigaction";
inherit "/std/act/domove";

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define A_STING 0
#define A_MAND 1
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

#define STING_MAX      10
#define STING_MIN       6
#define VICTIM_SKILLS  ({TS_DEX,SS_DEFENCE,SS_ANI_HANDL})
#define CENTIP_SKILLS  ({TS_DEX,SS_UNARM_COMBAT,SS_BLIND_COMBAT,SS_AWARENESS})

#define POISON     (MORGUL_DIR + "obj/sting_poison")

int ta = 0,
    ts = 0,
    tf = 0,
    tp = 0,
    tpp = 0;

void
create_creature() 
{
   if (!IS_CLONE) return;

   set_name("centipede");
   add_name(({"insect"}));
   set_pname("centipedes");
   set_adj(({"black","giant"}));
   set_pshort(implode(query_adjs(), ", ") + " centipedes");
   set_race_name("centipede"); 
   set_long(BSN("A giant centipede, almost five inches high, more than a foot long, " +
       "with clicking mandibles at the head and a deadly looking sting at the tail."));
   set_gender(G_NEUTER);
   set_alignment(-50);
   add_prop(CONT_I_WEIGHT,500);
   add_prop(CONT_I_HEIGHT,10);
   add_prop(CONT_I_VOLUME,500);
   add_leftover(NPC_DIR + "centipede_body", "centipede body", 1, 0, 0, 0);
   add_leftover(NPC_DIR + "centipede_legs", "centipede legs", 20, 0, 0, 0);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,5);

   set_stats(({2,20,5,1,1,90}));
   set_hp(5000); /* Heal fully */

   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_AWARENESS, 40);
   set_skill(SS_BLIND_COMBAT, 60);

  set_attack_unarmed( A_STING, 70, 10, W_IMPALE,    80, "sting");
  set_attack_unarmed( A_MAND,  60,  5, W_SLASH,     30, "mandibles");
   
  set_hitloc_unarmed( H_HEAD, ({ 30, 25, 1}), 10, "head");
  set_hitloc_unarmed( H_BODY, ({ 40, 35, 1}), 80, "body");
  set_hitloc_unarmed( H_LEGS, ({ 30, 25, 1}), 10, "legs");

}

/* For the solamnic Knights */
query_knight_prestige() { return (100); }

void init_attack()
{
    if(query_attack())
        return;

    if(ENV(TO) == ENV(TP))
        command("kill " +TP->query_real_name());
}

varargs string
poison_sting(object victim)
{
  object sting;
  tp++;
  if(!victim)
    victim = TO->query_attack();

  if(!victim) return "";

  if (ENV(TO) == ENV(victim)) 
  {
    tpp++;
    victim->catch_msg(QCTNAME(TO)+" pricks you with its sting.\n"+
        "A dreadful chill runs down your spine!\n");
    tell_room(ENV(TO),QCTNAME(TO)+" pricks "+QTNAME(victim)+" with its sting.\n",victim);
    seteuid(getuid(TO));
    sting = clone_object(POISON);
    sting->move(victim);
    sting->start_poison();
    log_file("curses",victim->query_name()+
    " poisoned with sting of a centipede, "+ctime(time())+".\n");
  }
  return "";
}

int
special_attack(object victim)
{
  ta++;
/* How often do we have normal attacks? */
  if(random(STING_MAX) > STING_MIN )
    return 0;

  ts++;
/* can the victim evade the deadly sting? */
  if(victim->resolve_task(TASK_DIFFICULT,VICTIM_SKILLS, TO,CENTIP_SKILLS) > 0)
  {
    tf++;
    if (ENV(TO) == ENV(victim))
    {
      victim->catch_msg(QCTNAME(TO)+" tries to prick you with its sting, but misses.\n");
      tell_room(ENV(TO),QCTNAME(TO)+" tries to prick "+QTNAME(victim)+" with its sting, but misses.\n",victim);
    }
  }
  else
    poison_sting(victim);
  return 1;
}

void do_die(object killer)
{
  seteuid(getuid());

  write_file(LOG_DIR + "curses","CENTIPEDE killed by "+killer->query_name()+": "+ta+
    ", "+ts+", "+tf+", "+tp+", "+tpp+".\n");

  ::do_die(killer);
}
