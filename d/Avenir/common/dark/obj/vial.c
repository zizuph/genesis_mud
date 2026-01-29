//-*-C++-*-
// file name: ~Avenir/common/dark/obj/vial.c
// creator(s):  Boriska Nov 1994
// last update: Mar 2 1995
// purpose:   container for artifact flame,  the goal of magic square quest
// note:
// bug(s):
// to-do:     


inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Avenir/include/magic_square.h"

void
create_receptacle()
{
  if (!IS_CLONE)
    return;
  
  set_name ("vial");
  add_name (VIAL_ID);
  set_short ("glass vial");
  add_adj("glass");
  set_long (
  "Very small and dusty glass vial. It could hold only something light.\n");
  add_prop (CONT_I_WEIGHT, 100);
  add_prop (CONT_I_VOLUME, 500);
  add_prop (OBJ_I_VALUE,  100);
  add_prop (CONT_I_MAX_WEIGHT, 500);
  add_prop (CONT_I_MAX_VOLUME, 1000);
  add_prop (CONT_I_TRANSP, 1);
  add_prop (CONT_I_RIGID, 1);
  add_prop (CONT_I_CLOSED, 1);
}

void
init()
{
  ::init();
  add_action ("do_guide", "guide");
}

int
do_guide (string str)
{
  string foo;
  object tp = this_player();
  object flame;
  
  notify_fail ("Guide what?\n");
  
  if (!str)
    return 0;

  if (!(flame = present(ARTIFACT_ID, this_object())))
    return 0;
  
  notify_fail ("Guide what where?\n");
  if (!sscanf (str, "flame %s", foo))
    return 0;

  notify_fail("Guide flame where?\n");

  if (str!= "flame from vial" )
    return 0;
    
  notify_fail ("But vial is closed!\n");

  if (query_prop (CONT_I_CLOSED))
    return 0;
  
  tp->catch_msg (
      "Blowing slight flow of air from your mouth you create a flow\n" +
      "that makes the flame to float out to the open air.\n");
  say (
      "Blowing slight flow of air from " + tp->query_possessive() + " mouth " +
      QCTNAME(tp) + " creates an air flow\n" +
      "that makes the flame to float out to the open air.\n");
  flame->move(environment(tp));
  return 1;
}






