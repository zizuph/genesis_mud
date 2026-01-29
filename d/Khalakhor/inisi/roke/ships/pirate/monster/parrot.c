#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";
#include <wa_types.h>

default_config_npc(int i)
{
  int j;
  for(j=0;j<6;j++)
    set_base_stat(j,i);
}

create_creature()
{
  set_name("parrot");
  
  default_config_npc(5);

  set_name("parrot");
  add_name("polly");
  set_race_name("parrot");
  set_short("green parrot");
  set_adj("green");
  set_gender(1);
  
  set_long("The parrot sits high up on one of the masts, and is chained\n"+
	   "to the mast by a tiny chain, preventing it from flying away.\n");

  add_act("emote flaps with her wings.\n");
  set_act_time(5);
  add_act("say Polly wants sugar!\n");
  add_act("say 13 45' N 12 16' E");
  add_act("emote cackles.\n");
  add_act("emote eats a small peanut.\n");
  add_act("say The treasure is burried on Gont.\n");

  set_attack_unarmed(0,  1, 1, W_IMPALE, 100, "claws");
  set_hitloc_unarmed(0, ({ 2 }), 20, "head");
  set_hitloc_unarmed(0, ({ 2 }), 80, "body");

}
