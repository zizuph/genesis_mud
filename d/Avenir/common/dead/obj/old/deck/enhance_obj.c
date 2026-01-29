inherit "/std/object";
#include "/d/Avenir/common/common.h"

int newstr, newdex, newcon, my_time;
object who;

create_object()
{
  set_name("_enhance_object");
  set_no_show();
   set_short("enhance object");
  add_prop(OBJ_I_NO_DROP, "Drop what?");
  add_prop(OBJ_I_WEIGHT, 0);
  add_prop(OBJ_I_VOLUME, 0);
}

remove_newstats()
{
// Undo what we have done....

  who->set_stat_extra(0, - newstr);
  who->set_stat_extra(1, - newdex);
  who->set_stat_extra(2, - newcon);

  who->catch_msg("You feel your old self again.\n");
  remove_object();
  return;
}

start_me(object tp)
{
  who = tp;

  newstr = who->query_stat(0) / 5;
  newdex = who->query_stat(1) / 5;
  newcon = who->query_stat(2) / 5;
  my_time = who->query_stat(4) / 3;
  
  who->catch_msg("You feel physically greater!\n");
  tell_room(ENV(who),QCTNAME(who)+" seems to grow before "
      +"your eyes.\n",who);
  who->set_stat_extra(0, newstr);
  who->set_stat_extra(1, newdex);
  who->set_stat_extra(2, newcon);

  set_alarm(itof(my_time), 0.0, remove_newstats);

  return;
}
