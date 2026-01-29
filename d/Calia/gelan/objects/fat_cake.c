/*
 *   A huge cake for the McCroissant bakery in Gelan
 *   Coded by Maniac
 */

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include "object.h"

create_food() {
   set_name("cake");
   set_adj(({ "fat bastard", "fat", "bastard" }) );
   set_short("fat bastard cake");
   set_pshort("fat bastard cakes");
   set_long(
      "The cake is huge and packed with lard, dried fruits and sugar. " +
      "You have no doubt that this is a cake for fat bastards! " +
      "In fact, you feel like sticking your face in it and gorging " +
      "yourself! (Try 'dive cake')\n");
   add_prop(OBJ_I_VALUE, 272);
   set_amount(400);
}




int
dive(string str)
{
  object tp;
 
  
  if ((!str) || (str != "cake")) 
  return 0;
 
  tp = TP;
  if (!(environment() == tp)) 
  { 
     NF("You don't have the " + query_short() + ".\n"); 
     return 0;
  }


  tp->catch_msg("You take a deep breath before sticking your face in the " 
                + query_short() + " and gorging yourself on it like " +
                "a real fat bastard!\n");

  tell_room(environment(tp), QCTNAME(tp) + " takes a deep breath before " +
            "sticking " + tp->query_possessive() + " face in a " +
            query_short() + " and gorging " + tp->query_objective() + 
            "self on it like a real fat bastard!\n", 
            ({ tp }) );

  tp->command("eat fat cake");
  return 1; 

}




void
init()
{
  ::init();
  add_action("dive", "dive");
}






