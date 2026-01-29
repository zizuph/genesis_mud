//-*-C++-*-
// file name: ~Avenir/common/dark/obj/flame.c
// creator(s):  Boriska Nov 1994
// last update: Mar 2 1995
//              Zizuph Aug 2022, notify_fail fixes and syntax improvements.
// purpose:  artifact, the goal of magic square quest
// note:
// bug(s):
// to-do:     

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Avenir/include/magic_square.h"

static int alarm_id = 0;

string
my_short()
{
  return environment()->this_room()
    ? "cold blue-white flame is floating here"
    : "cold blue-white flame";
}
string
my_pshort()
{
  return environment()->this_room()
    ? "cold blue-white flames are floating here"
    : "cold blue-white flames";
}

string
my_long() {
  return
    "A mysterious, cold, blue-white flame burning steadily without\n" +
    "any visible source. Living a life of its own, it cannot be\n" +
    "taken nor extinguished.\nIt can only be guided by a gentle hand.\n";
}

void
create_object()
{
  if (!IS_CLONE)
    return;
  
  set_name("flame");
  add_name(ARTIFACT_ID);
  set_short(my_short);
  set_pshort(my_pshort);
  set_long(my_long);
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 1);
  add_prop(OBJ_I_VALUE, 1);
  add_prop(OBJ_M_NO_SELL, "You do not feel like selling the flame.\n");
  add_prop(OBJ_M_NO_GET, "Cold flame flows through your fingers.\n");
  add_prop(MAGIC_AM_MAGIC, ({10,"illusion"}));
  add_prop(MAGIC_I_ILLUSION, 10);
  add_prop(OBJ_I_LIGHT, 3);

}

  
private void
burn_out()
{
  int light = query_prop (OBJ_I_LIGHT);
  object tp;
  object env = environment();
  
  light--;
  
  if (!light)
    {
      if (env->id(VIAL_ID) && living(tp = environment(env)))
	{
	  tp->catch_msg ("Your flame burns out.\n");
          tell_room  (environment(tp),
	  "The flame " + QCTNAME(tp) + " was carrying burns out.\n", tp);
	}
      else
	if (env->id(VIAL_ID)) // vial dropped in room
	  tell_room (environment(env),
		     "The flame inside the vial burns out.\n");
	else
	  tell_room (env, "The flame burns out.\n");
      
      remove_alarm (alarm_id);
      remove_object();
      return;
    }
  
  add_prop (OBJ_I_LIGHT, light);
  if (env->id(VIAL_ID) && living(tp = environment(env)))
    {
      tp->catch_msg ("The flame seems dimmer.\n");
      tell_room ( environment(tp),
      "The flame " + QCTNAME(tp) + " is carrying seems dimmer.\n", tp);
      tp->update_light();
    }
  else
    {
      if (env->id(VIAL_ID)) // vial dropped in room
	tell_room (environment(env),
		   "The flame inside the vial seems dimmer.\n");
      else
	tell_room (env, "The flame seems dimmer.\n");
      
      env->update_light();
    }
}


int
do_guide (string str)
{
  string foo;
  object tp = this_player();
  object vial;
  
  notify_fail ("Guide what where?\n");
  if (!str)
    return 0;

  notify_fail ("Guide what where?\n");
  if (!sscanf (str, "flame %s", foo))
    return 0;

  notify_fail("Guide flame into what? You need a certain something " +
  "to put it in.\n");
  if (!(vial = present(VIAL_ID, tp)))
    return 0;

  notify_fail ("But the vial is closed!\n");
  if (vial->query_prop (CONT_I_CLOSED))
    return 0;

  notify_fail("Guide flame where?\n");
  if (str != "flame into vial" && str != "flame with a gentle hand" &&
      str != "flame with a gentle hand into vial" && 
      str != "flame into vial with a gentle hand")
    return 0;

  tp->catch_msg (
       "Waving your hands, you create an air flow that guides the flame " +
       "into the vial. It starts shining with an unearthly glow.\n");
  say ("Waving " + tp->query_possessive() + " hands, " + QCTNAME(tp) +
      " creates an air flow that guides the flame " +
       "into a vial. It starts shining with an unearthly glow.\n");

  this_object()->move(vial);
  if (!alarm_id)
    alarm_id = set_alarm (150.0, 150.0, burn_out);
  return 1;
}

void
init ()
{
  ::init();
  add_action (do_guide, "guide");
}