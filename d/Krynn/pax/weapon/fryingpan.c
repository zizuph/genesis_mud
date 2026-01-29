/*
   fryingpan.c
   -----------

   Coded ........: 95/03/26
   By ...........: Jeremiah

   Latest update : 95/07/03
   By ...........: Jeremiah

   Frying pan(weapon) for the gullies in Pax tharkas.

*/


inherit "/std/weapon";
#include "/d/Krynn/common/defs.h";
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

create_weapon()
{
    set_name(({"frying pan", "pan"}));
    set_adj("large");
    set_long("This is a large frying pan. It is dented in places, " +
             "indicating that maybe it has been used for other " +
             "purposes than cooking food. You could probabaly get a " +
             "good swing at someone with this pan.\n");
    set_short("large frying pan");
    set_default_weapon(10, 12, W_CLUB, W_BLUDGEON , W_ANYH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 4000);
}


void
init()
{
   ::init();
   add_action("do_swing", "swing");
}


int
do_swing()
{
   object *others, *no_msg;
   int i;

   if(!living(E(TO)))
      return 0;

   if(!query_wielded())
   {
      TP->catch_msg("Hmmm.. maybe you should wield the " + short() +
         " before trying that ?\n");
      return 1;
   }

   others = all_inventory(E(TP));
   others = FILTER_LIVE(others);
   others -= ({ TP }); 

   TP->catch_msg("You swing the " + short() + " uncontrollably " +
      "around over your head.\n");

   tell_room(E(TP), QCTNAME(TP) + " swings the " + short() + " " +
      "uncontrollably around over " + POSSESSIVE(TP) + " head.\n", TP);

   if(!sizeof(others))
      return 1;

   no_msg = ({ TP });

   for(i = 0; i < sizeof(others); i++)
   {
      no_msg += ({ others[i] });

      others[i]->catch_msg("You duck, hoping to avoid the " + short() +
         ".\n");
      TP->catch_msg(QCTNAME(others[i]) + " ducks to avoid your " +
         short() + ".\n");
      tell_room(E(TP), QCTNAME(others[i]) + " ducks to avoid the " +
         short() + ".\n", no_msg);

      no_msg -= ({ others[i] });
   }

   return 1;
}
