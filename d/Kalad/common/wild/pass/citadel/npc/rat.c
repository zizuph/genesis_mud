inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include <wa_types.h>
#include <ss_types.h>
#define A_BITE 0
#define H_BODY 1
/* by korat */
/* this rat will swarm around in teams... */
create_monster()
{
   set_name("rat");
   set_race_name("rat");
   switch (random(9))
   {
      case 0: set_adj("brown"); break;
      case 1: set_adj("black"); break;
      case 2: set_adj("dirty"); break;
      case 3: set_adj("thick"); break;
      case 4: set_adj("vicious"); break;
      case 5: set_adj("smelling"); break;
      case 6: set_adj("ugly"); break;
      case 7: set_adj("thin"); break;
      default: set_adj("slick"); break;
   }
   set_long("Its a rat. One of those cruel, ugly and smelling beasts that "+
      "tends to roam around anywhere humans end up living.\n");
   set_stats(({20,20,15,3,3,30}));
   set_random_move(random(30)+50);
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE,20);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_NO_INS,1);
   set_alignment(-50);
   set_knight_prestige(1);
   set_act_time(4);
   add_act("emote hurries over the floor.");
   add_act("emote squeaks.");
   add_act("emote makes some chilling chewing sounds.");
   add_act("emote runs up to you, sniffs and runs away.");
   add_act("emote chews on a small rotten piece of meat.");
   set_cact_time(1);
   add_cact("emote bites after you.");
   add_cact("emote crawls up along you leg.");
   add_cact("emote tries to bite through your armour.");
   add_cact("emote crawls up on your back, and tries to bite your neck.");
   set_attack_unarmed(A_BITE, 10, 10, W_IMPALE, 100, "sharp teeth");
   set_hitloc_unarmed(H_BODY, ({ 4, 4, 8 }), 100, "small body");
   trig_new("%s 'died.\n'","eat_corpse");
}

eat_corpse(string who,string corpse)
{
   float time;
   time = itof(random(10)+2);
   command("emote runs toward the corpse.");
   set_alarm(time,0.0,"do_eating");
}

do_eating()
{
   switch (random(4))
   {
      case 0: command("emote rips some flesh of the corpse with its sharp teeth.");
      break;
      case 1: command("emote starts to chew its way through the chest of the corpse.");
      break;
      case 2: command("emote licks some blood from a deep wound in the corpse.");
      break;
      default: tell_room(TO,"You hear the chilling sound of a small bone being "+
         "crushed by a hungry rats teeth.\n");
      break;
   }
}

got_spit_on(object who)
{
   command("emote rubbs its left paw on the head to remove the spit.");
}

got_kicked(object who)
{
      command("emote runs to a corner to avoid the hurting boots.");
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("emote snatches at you wildly.");
      command("kill " + lower_case(ob->query_real_name()));
   }
}

void
emote_hook(string emote, object actor, string adverb)
{
   if (emote == "kick") set_alarm(1.0,0.0,"got_kicked",actor);
   if (emote == "spit") set_alarm(1.0,0.0,"got_spit_on",actor);
}
