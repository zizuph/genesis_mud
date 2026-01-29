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
   set_name("ratmonster");
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
   add_adj("monstrous");
   set_long("Its a monsterous rat! One of those cruel, ugly and "+
      "smelling beasts that tends to roam around anywhere humans "+
      "end up living.\n");
   set_stats(({20,44,32,10,5,50}));
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE,40);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_NO_INS,1);
   set_alignment(-100);
   set_knight_prestige(1);
   set_act_time(4);
   add_act("emote hurries over the floor.");
   add_act("emote squeaks.");
   add_act("emote makes some chilling chewing sounds.");
   add_act("emote sniffs in the air.");
   add_act("emote chews on a small rotten piece of meat.");
   set_cact_time(1);
   add_cact("emote bites after you.");
   add_cact("emote crawls up along you leg.");
   add_cact("emote tries to bite through your armour.");
   add_cact("emote crawls up on your back, and tries to bite your neck.");
   set_random_move(30);
   set_attack_unarmed(A_BITE, 15, 15, W_IMPALE, 100, "sharp teeth");
   set_hitloc_unarmed(H_BODY, ({ 8, 8, 16 }), 100, "body");
   trig_new("%w 'kicks' 'you' %s","got_kicked");
   trig_new("%w 'spits' 'on' 'you!\n' %s","got_spit_on");
   trig_new("%w 'spits' 'on' 'the' 'ground' %s","got_spit");
}

got_spit(string who, string dummy)
{
   who=lower_case(who);
   set_alarm(1.0,0.0,"get_irritated");
}

got_spit_on(string who,string dummy)
{
   who=lower_case(who);
   set_alarm(1.0,0.0,"get_irritated");
}


lick_it()
{
   command("emote licks the spit with a hungry look on its face.");
}

get_irritated()
{
   command("emote eyes seems to glow in a red fury at the spitter.");
}



got_kicked(string who, string dummy)
{
   who = lower_case(who);
   set_alarm(1.0,0.0,"leave_kicker",who);
}

leave_kicker(string who)
{
   object ob;
   if (ob = present(who, environment()))
      {
      command("emote flickers its sharp, white teeth in warning.");
      return;
   }
   command("emote licks its wound.");
}


help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("emote flicker some sharp white teeth at you.");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
