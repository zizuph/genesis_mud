inherit "/std/object";
#include "/d/Kalad/common/ruins/defs.h"
#include <macros.h>
#define TO  this_object()
#define E(ob)   environment(ob)

query_auto_load()
{
   return MASTER;
}

create_object()
{
   set_name("pin");
   set_adj("red");
   add_name("bh_club");
   set_short("Pin of Baal");
   set_long("This is a pin that adorns clothing. Its possession is "
      +"a great honor, for it identifies you as a servant to the Lord" 
      +"Bhaal. It is red and tear shaped.\n");  
   add_prop(OBJ_I_NO_DROP,"You don't want to loose your pin, do you?\n");
}

public string
show_subloc(string subloc, object on, object for_obj)
{
   string data;
   
   if (for_obj == on)
      data = "You are ";
   else
      data = capitalize(environment(this_object())->query_pronoun()) + " is ";
   data+="a servile assassin of Baal.\n";
   return data;
}

enter_env(object dest,object old)
{
   remove_name("bh_club");
   if(present("bh_club",E(TO)))
      {
      tell_room(E(TO),"In a flash of light the pins meld together.\n");
      remove_object();
      return;
   }
   add_name("bh_club");
   if(living(E(TO)))
      dest->add_subloc("bh_club", this_object());
}
public void
leave_env(object from, object to)
{
   this_player()->remove_subloc("bh_club");
}
