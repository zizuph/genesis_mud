#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <filter_funs.h>
#include "../guild.h"

inherit AA_DIR+"npc/shield_guard";

void
create_monster()
{
  ::create_monster();
  set_name("dunhough");
  set_guard_race("human");
  set_guard_base_stat(90+random(30));
  set_long("This is the shopkeeper.\n");
  set_alarm(0.0, 0.0, "update_guard");
  remove_prop(LIVE_I_NEVERKNOWN);
  remove_prop(LIVE_I_SEE_DARK);

  set_act_time(5); 
  add_act("say Hello! Do you want to sell or buy something?"); 
  add_act("say Would you like some nice club? Or maybe rucksack? Lamp???"); 
  add_act("say Do you have nice loot?"); 
  add_act("shout Nice things for sale!!!"); 
  add_act("shout   Weapons!     Armours!     Hardware!"); 
  add_act("say How about spending some plats in my shop?");
}

void
return_intro(object ob)
{
    if(!present(ob, E(TO)))
    {
	return;
    }
    command("introduce me to "+ob->query_real_name());
}

void
add_introduced(string str)
{
  object ob = find_player(lower_case(str));
  if(ob && !ob->query_met(TO))
  {
	set_alarm(3.0, 0.0, &return_intro(ob));
  }
} 

void
init_attack()
{
  return;
}

void 
attacked_by(object ob)
{
  ::attacked_by(ob);
  command("shout Help!!! A "+ob->query_nonmet_name()+" wants to kill me!");
  set_alarm(2.0, 0.0, "second_life", ob);
  set_alarm(5.0, 0.0, "second_life", ob);
  set_alarm(15.0, 0.0, "second_life", ob);
}
