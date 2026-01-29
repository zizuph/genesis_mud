inherit "/std/object";
#include "/d/Kalad/common/zhent/defs.h"
#include <macros.h>
#define TO this_object()
#define E(ob)  environment(ob)

query_auto_load()
{
  return MASTER;
}

create_object()
{
  set_name("emblem");
  set_adj("sun-shaped");
  add_name("c_club");
  set_short("sun-shaped emblem");
  set_long("This is an emblem in the shape of a sun and made of "
	+"blackened steel. It identifies you as a follower of Cyric.\n");
  add_prop(OBJ_I_NO_DROP,"You don't want to loose your emblem, do you?\n");
}

public string
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (for_obj == on)
    data = "You are ";
  else
  data = capitalize(environment(this_object())->query_pronoun()) + " is ";
   data+="a slave to the Grand Liar.\n";
  return data;
}

enter_env(object dest,object old)
{
  remove_name("c_club");
  if(present("c_club",E(TO)))
    {
      tell_room(E(TO),"In a flash of light the emblems meld together.\n");
      remove_object();
      return;
    }
  add_name("c_club");
  if(living(E(TO)))
    dest->add_subloc("c_club", this_object());
}
public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("c_club");
}
