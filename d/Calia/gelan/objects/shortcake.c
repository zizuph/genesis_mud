/*
 *   Shortcake for the McCroissant bakery in Gelan
 *   Coded by Maniac 
 */

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include "object.h"

create_food() {
   set_name("finger");
   add_name("shortcake");
   set_adj("shortcake");
   set_short("shortcake finger");
   set_pshort("shortcake fingers");
   set_long(
      "Delcious looking golden shortcake, baked in the perfect " +
     "shape to make a rude gesture at someone with! " + 
     "(Try 'sfinger <player>')\n");
   add_prop(OBJ_I_VALUE, 43);
   set_amount(150);
}



int
sfinger(string str)
{
  object pl, tp;
 
  
  if (!str) 
  {
    NF("Syntax: sfinger <player>\n");
    return 0;
  }
 
  tp = TP;
  if (!(environment() == tp)) 
  { 
     NF("You don't have the " + query_short() + ".\n"); 
     return 0;
  }

  pl = present(str, environment(tp)); 
  if (!pl)
  {
     NF("You don't see that person here.\n"); 
     return 0;
  }
 
  if (pl == tp)
  {
     NF("You reconsider making a rude gesture with the " + query_short() 
        + " at yourself.\n");
     return 0;
  }
  

  tp->catch_msg("You make a rude gesture at " + QTNAME(pl) +
                " with the " + query_short() + "!\n");

  tell_room(environment(tp), QCTNAME(tp) + " makes a rude gesture at " + 
            QTNAME(pl) + " with a " + query_short() + "!\n",
            ({ tp, pl }) );

  pl->catch_msg(QCTNAME(tp) + " makes a rude gesture at you with " +
               "a " + query_short() + "!\n");
  return 1; 

}




void
init()
{
  ::init();
  add_action("sfinger", "sfinger");
}








