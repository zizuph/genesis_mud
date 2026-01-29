inherit "/std/object";
#include "/d/Kalad/common/zhent/defs.h"
#include "/d/Roke/common/defs.h"
#include <macros.h>

query_auto_load()
{
  return MASTER;
}

create_object()
{
  set_name("insignia");
  set_adj("Bane's");
  add_name("b_club");
  set_short("small insignia");
  set_long("This insignia pins on your clothing. It is blood red and "
	+"has an inscription: My soul for Bane.\n");
  add_prop(OBJ_I_NO_DROP,"You don't want to loose your badge, do you?\n");
}

public string
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (for_obj == on)
    data = "You are ";
  else
  data = capitalize(environment(this_object())->query_pronoun()) + " is ";
   data+="an unholy servant to Bane.\n";
  return data;
}

enter_env(object dest,object old)
{
  remove_name("b_club");
  if(present("b_club",E(TO)))
    {
      tell_room(E(TO),"In a flash of light the insignias meld together.\n");
      remove_object();
      return;
    }
  add_name("b_club");
  if(living(E(TO)))
    dest->add_subloc("b_club", this_object());
}
public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("b_club");
}
