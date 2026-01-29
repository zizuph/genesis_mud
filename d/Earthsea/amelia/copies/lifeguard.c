/* A baywatcher */

#pragma save_binary

inherit "/d/Krynn/open/monster/monster";

#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Roke/common/gont/re/bridgedefs.h"

check_pos();

create_monster()
{
    int i;

    add_prop(LIVE_I_ALWAYSKNOWN,1);

    set_name("george");
    set_living_name("george");
    set_long("This is the lifeguard. He is very muscular and tanned.\n"+
	     "He looks confident.\n");
    set_race_name("human");
    set_adj("muscular");

    add_act("smile");
    set_act_time(20);

    set_knight_prestige(-3);

    set_stats(({ 74,50,81,47,45,78 }));
    set_skill(SS_SWIM,100);
    set_skill(SS_UNARM_COMBAT,60);
    set_hp(10000);
    set_fatigue(1000);

    set_alignment(200);

    set_all_attack_unarmed(10, 8);
    set_all_hitloc_unarmed(2);

    trig_new("%w 'shouts:' %s","react_shout");

    ::create_monster();
}

rescue(object obj)
{
  command("dive");
  command("rescue "+obj->query_real_name());
  set_alarm(2.0, 0.0, check_pos);
}

pat(object obj)
{
  command("pat "+obj->query_real_name());
}


react_shout(string who,string what)
{
  object ob;

  if (extract(what,0,3)!="help")
    return;

  ob=present(lower_case(who),find_object(BRIDGEROOM));
  if (ob) {set_alarm(2.0, 0.0, &pat(ob));return;}
  
  ob=present(lower_case(who),find_object(WATERROOM));
  if (ob) {set_alarm(2.0, 0.0, &rescue(ob));return;}

}

check_pos()
{
  if (E(TO)!=find_object(BRIDGEROOM))
    {
      if (E(TO)==find_object(WATERROOM))
	{
	  command("up");
	}
      else
	{
	  move_living(BRIDGEROOM,"to his work");
	}
    }
}

