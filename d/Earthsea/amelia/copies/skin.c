#include "/d/Roke/common/defs.h"
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>

#pragma save_binary

inherit "/std/object";

#define LEFTOVER_DECAY_TIME 180

int timeleft;

create_object()
{
  timeleft = LEFTOVER_DECAY_TIME;

  add_prop("_skin_by_gresolle",1); /* why? dunno... */
}

leftover_init(string organ, string race)
{        
  set_name(organ);
  set_short(organ);
  set_adj(race);
  set_long("This is a "+organ+" from "+ LANG_ADDART(race)+".\n");
	
  add_prop(OBJ_I_WEIGHT,previous_object()->query_prop(OBJ_I_WEIGHT)/50);
  add_prop(OBJ_I_VOLUME,previous_object()->query_prop(OBJ_I_VOLUME)/1000);

  timeleft = LEFTOVER_DECAY_TIME;

}

enter_env(object dest,object old)
{
  if(!dest)
    return;

  if(!living(dest))
    call_out("decay_fun",timeleft);
}

leave_env(object from,object to)
{
  int snok;

  if(snok = find_call_out("decay_fun"))
    {
      timeleft = snok;
      remove_call_out("decay_fun");
    }
}

decay_fun()
{
  tell_room(E(TO),"The "+short()+" decays and leaves nothing behind.\n");
  remove_object();
}






