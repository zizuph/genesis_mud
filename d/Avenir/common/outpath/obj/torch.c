/* A torch for the newbie area. Cirion 042495 */
inherit "/std/torch";
#include "../outpath.h"

int smoke_alarm;

void smokey();

void create_torch()
{
  set_name("stick");
  add_name("wood");
  set_adj(({"long","wood","wooden","heavy","petrified"}));
  set_short("petrified stick of wood");
  set_long("It is a long and heavy stick of wood, petrified "
    +"over the ages. It tapers to a thin point at the "
    +"bottom. @@lit_desc@@.\n");

   set_time(1800); // 1/2 hour rl
   set_strength(1);
   set_value(100);
}

string lit_desc()
{
  if(!query_prop(OBJ_I_HAS_FIRE))
     return "The wood seems so dry that it might burn "
       +"if set alight";
  else
     return "A large, rich orange flame rises from it, "
       +"sending thick plumes of grey smoke into the air";
}

/*
 * Function name: short, pshort, long
 * Description:   We change the short, plural short and long description of
 *		  the torch if it's lit, default settings.
 * Returns:	  The description.
 */
public varargs string
short(object for_obj)
{
    if(!query_time())
      return "burnt-out stick of wood";

    return (query_prop(OBJ_I_HAS_FIRE) ?
	"burning" : "petrified") + " stick of wood";
}

int light_me_after_delay()
{
  ::light_me_after_delay();

  smoke_alarm = set_alarm(30.0, 60.0, smokey);
  return 1;
}

void smokey()
{
  string  msg;
  object  who,
          where;

  if(!query_prop(OBJ_I_HAS_FIRE))
  {
    remove_alarm(smoke_alarm);
    return;
  }

  who = ENV(TO);
  if(living(who) && ENV(who)->query_prop(ROOM_I_INSIDE))
  {
    where = ENV(who);
    switch(random(4))
    {
      case 0:
       who->catch_msg("A plume of thick dark smoke rises "
          +"up from your "+short()+".\n");
       tell_room(where, "A plume of thick dark smoke "
          +"rises up from "+QTNAME(who)+"'s "+short()+".\n", who);
       break;
      case 1:
       who->catch_msg("Your "+short()+" flickers slightly "
          +"in the breeze.\n");
       tell_room(where, QCTNAME(who)+"'s "+short()
          +" flickers slightly in the breeze.\n", who);
       break;
      case 2:
       who->catch_msg("The "+short()+" seems to dim slightly.\n");
       tell_room(where, QCTNAME(who)+"'s "+short()+" seems to "
          +"dim slightly.\n", who);
       break;
      default:
       who->catch_msg("Shadows from your "+short()
          +" play strange shapes upon the walls.\n");
       tell_room(where, "Shadows from "+QTNAME(who)+"'s "
          +short()+" play strange shapes upon the walls.\n", who);
      }
    }
}
