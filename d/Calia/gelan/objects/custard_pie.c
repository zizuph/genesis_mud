
/*
 *  A custard pie for the McCroissant bakery in Gelan 
 *  Coded by Maniac 
 *
 *  Parsing improved, Maniac, 30/5/98
 */

inherit "/std/food";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "object.h"


void
create_food() {
   set_name("pie");
   set_adj("custard");
   set_short("custard pie");
   set_pshort("custard pies");
   set_long("A thick layer of custard on top of a thin pastry base. " +
            "It looks tasty, but it strikes you that it would be as " + 
            "much fun to throw it at someone as to eat it!\n"); 

   set_amount(100);
}


int
live_check(object ob)
{
    return living(ob); 
}


/* For throwing the custard pie at someone. */
int
throw_pie(string str)
{
  object tp, pl;
  mixed arg;
 
  notify_fail("Throw the pie at whom?\n"); 

  if (!stringp(str) || !strlen(str)) 
      return 0;
 
  tp = TP;
  if (!(environment() == tp)) 
  { 
     NF("You don't have the " + query_short() + ".\n"); 
     return 0;
  }

  if (!parse_command(str, all_inventory(environment(tp)), 
                          "[the] [custard] [pie] [at] [the] %l", arg)) 
      return 0;

  arg = NORMAL_ACCESS(arg, "live_check", this_object()); 
  if (!sizeof(arg))
      return 0;

  if (sizeof(arg) > 1)  {
      NF("You can't throw the " + query_short() + " at more than one " +
         "person at once!\n"); 
      return 0;
  }

  pl = arg[0]; 

  if (pl == tp)
  {
     NF("You reconsider throwing the " + query_short() + " at yourself.\n");
     return 0;
  }
  
  set_heap_size(num_heap() - 1);

  if (random(40) > tp->query_stat(SS_DEX)) 
  {
     tp->catch_msg("You throw the " + query_short() + " at " + QTNAME(pl) + 
                   " but miss completely!\n");
     tell_room(environment(tp), QCTNAME(tp) + " throws a " + query_short() +
               " at " + QTNAME(pl) + " but misses completely!\n", 
               ({tp, pl}) );
     pl->catch_msg(QCTNAME(tp) + " throws a " + query_short() + " at you " +
                   "but misses completely!\n");
     return 1;
  }
 
  if (random(500) < pl->query_stat(SS_DEX))
  {
     tp->catch_msg("You throw the " + query_short() + " at " + QTNAME(pl) +
                   " but " + pl->query_pronoun() + " deftly ducks " +
                   "out of the way and it flies past!\n");
     tell_room(environment(tp), QCTNAME(tp) + " throws a " + query_short() +
             " at " + QTNAME(pl) + " but " + pl->query_pronoun() + 
             " deftly ducks out of the way and it flies past!\n", 
             ({tp, pl }) );
     pl->catch_msg(QCTNAME(tp) + " throws a " + query_short() + " at you " +
             "but you deftly duck out of the way and it flies past!\n"); 
              
     return 1;
  }

  tp->catch_msg("You throw the " + query_short() + " at " + QTNAME(pl) +
                " and hit " + pl->query_objective() + " smack in " +
                "the face, leaving " + pl->query_objective() + 
                " dripping with custard and looking very annoyed!\n");

  tell_room(environment(tp), QCTNAME(tp) + " throws a " + query_short() + 
            " at " + QTNAME(pl) + " and hits " + pl->query_objective() +
            " smack in the face, leaving " + pl->query_objective() +
            " dripping with custard and looking very annoyed!\n",
            ({ tp, pl }) );

  pl->catch_msg(QCTNAME(tp) + " throws a " + query_short() + " at you " +
            "and hits you smack in the face, leaving you dripping " +
            "with custard and looking very annoyed!\n");
  return 1; 

}


void
init()
{
  ::init();
  add_action(throw_pie, "throw");
}


