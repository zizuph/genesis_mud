inherit "/std/object";
#include "/d/Avenir/common/common.h"

int my_time;
object who;

create_object()
{
  set_name("_card_invis_object");
  set_no_show();
  set_short("invisible object");
  add_prop(OBJ_I_NO_DROP, "Drop what?");
  add_prop(OBJ_I_WEIGHT, 0);
  add_prop(OBJ_I_VOLUME, 0);
}

make_visible()
{
  int myprop;
  myprop = who->query_prop(OBJ_I_INVIS);

  if(myprop > 1)
    {
      who->add_prop(OBJ_I_INVIS, myprop - 1);
      who->catch_msg("You feel a little more real.\n");
      remove_object();
      return;
    }
  else
    {
      who->remove_prop(OBJ_I_INVIS);
      who->catch_msg("You fade back into sight.\n");
      tell_room(ENV(who),QCTNAME(who)+" slowly fades into sight.\n",who);
      remove_object();
      return;
    }
}

start_me(object tp)
{
  who = tp;
  my_time = who->query_stat(4) / 3;
  
  who->catch_msg("You fade away.\n");
  tell_room(ENV(who),QCTNAME(who)+" slowly fades from sight.\n",who);

  who->add_prop(OBJ_I_INVIS,1);

  set_alarm(itof(my_time), 0.0, make_visible);

  return;
}
