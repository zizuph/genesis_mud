/* An evil priest in Tantallon, tent10 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>

inherit M_FILE

void
create_krynn_monster()
{
    int i;

    set_name("rasksahl");
    set_living_name("rasksahl");
    add_name("priest");
    add_name("ev_priest");
    set_adj("evil");
    set_race_name("human");
    set_short("evil priest");
    set_long("He is dressed in black robes. It seems he doesn't like you.\n");

    for (i = 0; i < 6; i++)
      set_base_stat(i, 60 + random(10));
    set_skill(SS_DEFENCE, 90);

    set_alignment(-400);
    set_knight_prestige(900);

    if (IS_CLONE)
    {
    	add_act("emote moves sligthly.");
	add_act("emote closes " + HIS(TO) + " eyes as in a prayer."); 
    	set_act_time(20);
    	add_cact("@@spell@@");
    	set_cact_time(5);
    }

    set_all_attack_unarmed(26, 25);
    set_all_hitloc_unarmed(87);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    clone_object(OBJ + "pr_robe")->move(TO);
    clone_object(OBJ + "small_gem")->move(TO);
    
    /* give him a pouch with some herbs */
}

void
init_living() 
{ 
  ::init_living();
    set_alarm(1.0,0.0,"message_first", TP); 
}

void
message_first(object ob)
{
  tell_object(ob, "The priest turns to look at you. You suddenly feel an " +
	      "urge to leave.\n");
  set_alarm(5.0,0.0,"message", ob);
} 

void
message(object ob)
{
  if (ob && environment(ob) == environment(TO))
    {
      command("say Begone or die you fool, stop disturbing my meditation!!");
      set_alarm(10.0,0.0,"attack_now", ob);
    }
}

void
attack_now(object ob)
{
  if (ob && environment(ob) == environment(TO))
    command("kill " + ob->query_real_name());
}

void
spell()
{
  object ob;
  
  if (ob = query_attack())
    {
      tell_room(environment(TO), 
		"The priest begins to chant in a strange language, it seems to " +
		"heal him.\n");
      heal_hp(1000);
    }
}
