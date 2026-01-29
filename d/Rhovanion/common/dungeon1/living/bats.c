inherit "/std/monster";
inherit "/std/combat/unarmed";

#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <wa_types.h>

#define A_SWARM 0
#define H_MASS 0

/* 
* Global variables
*/
static int angry; // this is either true or false

void
create_monster()
{
   set_name("the bat swarm");
   add_name("swarm");
   set_living_name("bat swarm");
   set_race_name("bat swarm");
   set_short("bat swarm");
   set_long("@@dependent_angry");
   set_stats(({ 30, 45, 30, 20, 30, 60 }));
   set_gender(G_NEUTER);
   set_alignment(0);
   set_aggressive(0);
   set_hp(300);
   set_skill(SS_BLIND_COMBAT, 100);
   add_prop(CONT_I_WEIGHT, 20000);
   add_prop(CONT_I_HEIGHT,  1000);
   add_prop(CONT_I_VOLUME, 30000);
   set_attack_unarmed(A_SWARM, 50, 10, W_IMPALE, 100, "swarm");
   set_hitloc_unarmed(H_MASS, ({ 50, 25, 45, 50 }), 100, "mass");
   trig_new("%w 'says:' %s", "react_say");
   trig_new("%w 'rsays:' %s", "react_say");
   trig_new("%w 'shouts:' %s", "react_say");
}

public void
part_swarm(string target)
{
   seteuid(getuid(TO));
   
   angry = 1;
   
   TP->attack_object(find_player(target));
   command("kill " + target);
}

public string
dependent_angry()
{
   if (!angry)
      return "This horde of bats is currently sleeping, hanging " +
   "from the ceiling in an upside down fashion as bats of this nature " +
   "are prone to do.  They look peaceful and at rest, yet daunting and imposing " +
   "as if waiting for the slightest sound to set them into a frenzied " +
   "motion.  You'd better be quiet here...\n";
   
   return "Someone has disturbed this horde of bats so violently, that they are now swarming about seeking the blood of new victims!\n";
}
int
react_say(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_say",who);
      return 1;
   }
}
void
return_say(string who)
{
   object obj;
   int ran;
   if(obj = present(who,environment()))
      {
      angry = 1;
      command("emote swarms into a frenzy!");
      command("kill " + (obj->query_real_name()));
   }
}
void
attacked_by(object ob) {
   angry=1;
   set_alarm(1.0,0.0,"react_say");
}
