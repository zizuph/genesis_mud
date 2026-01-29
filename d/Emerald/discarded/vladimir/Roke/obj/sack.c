/*   An ordinary sack for the hardware store in Calia

    coder(s):   Maniac

    history:     31.1.94    created                         Maniac
    purpose:    hold items

    to do:      none
    bug:        none known
*/


inherit "/std/container";
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
#include <macros.h>


void
create_container()
{
    set_name("sack");
    set_pname("sacks");
   set_short("leather sack");
   set_pshort("leather sacks");
   set_adj("leather");
   set_long("This is a brown leather sack that looks like it can hold "+
           "a fair amount of you stuff. It has a symbol of two crossed "+
    "axes over a map of the world inscribed on the side.\n"
  + "Typing 'sacksell' will allow you to sell the sack.\n"
  + "Typing 'sackhold' will keep the sack from being sold.\n");

    add_prop(CONT_I_WEIGHT, 1750); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 75000); /* grams */
    add_prop(CONT_I_VOLUME, 2000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 75000); /* ml */

    add_prop(OBJ_I_VALUE, 225); 		/* Worth 225 cc */
    add_prop(OBJ_M_NO_SELL, "If you want to be able to sell this sack, " +
                            "type 'sacksell'.  After this you may sell " +
                            "it as normal.\n");
 
   add_name("_vladimir_shop_");

}



/* Enable player to sell the sack */
int
sacksell()

{
   object tp;

   tp = TP;
   
   tp->catch_msg("You may now sell the sack.\n"); 
   remove_prop(OBJ_M_NO_SELL); 
return 1;

}


int
sackhold()
{
  object tp;

  tp = TP;
  tp->catch_msg("The sack will now not be sold.\n");
  add_prop(OBJ_M_NO_SELL, "If you want to be able to sell this sack, " +
                          "type 'sacksell'.  After this you may sell " +
                          "it as normal.\n");
  return 1;
}


string
query_recover()

{
return MASTER;
}



void
init()
{
   ::init();
   add_action("sacksell", "sacksell");
   add_action("sackhold", "sackhold");

} 

void enter_inv(object ob, object from)
{
  if (ob->query_prop(CONT_I_IN))  {  /*containers*/
    set_alarmv(1.0, 0.0, "fail_message", ({ ob, from }) );
    ob->move(from);
  }
  else
    ::enter_inv(ob, from);
}


void fail_message(object ob, object from)
{
  from->catch_msg("The sack rejects the " + ob->short() + ".\n");
}

