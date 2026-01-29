#pragma save_binary

inherit "/d/Rhovanion/common/npcs/shield_guard";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <filter_funs.h>

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

  trig_new("%w 'introduces' %s", "react_introduce");
}

int
react_introduce(string who, string dummy) 
{
  call_out("return_introduce", 2);
  return 1;
}

void
return_introduce() {
 object *in_room;
 int i, met_me;
  in_room=FILTER_LIVE(all_inventory(environment()));
  met_me=1;
  for (i = 0; i < sizeof(in_room); i++) 
    if (!in_room[i]->query_met(TO->query_real_name())) met_me=0;
  if (!met_me) {
     command("introduce me");
     command("bow");
  }
  return;
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