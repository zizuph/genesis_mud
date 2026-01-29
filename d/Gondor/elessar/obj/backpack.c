/*   An large backpack for the hardware store in Calia

    coder(s):   Maniac

    history:    31.1.94     created                         Maniac
    purpose:    hold items

    to do:      none
    bug:        none known
*/


inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"


int worn;

void
create_container()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("large backpack");
    set_pshort("large backpacks");
    set_adj("large");
    set_long("A large backpack ideal for the travelling warrior, " +
             "such as are common in Calia where it was made.  " +
             "It looks as though it can hold a lot of stuff.  " +
             "Typing 'packhelp' will give you a list of commands.\n");

    add_prop(CONT_I_WEIGHT, 4500); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

    add_prop(OBJ_I_VALUE, 450); 		/* Worth 450 cc */
    add_prop(OBJ_M_NO_SELL, "If you want to be able to sell this pack, " +
                            "type 'packsell'.  After this you may sell " +
                            "it as normal.\n");
 
    add_name("_calia_hardware_shop_");
    worn = 0;
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
  from->catch_msg("The backpack rejects the " + ob->short() + ".\n");
}


int
wear(string str)
{
    if (str != "backpack")
        return 0;

    if (!present(THIS, TP))
    {
        NF("You don't have it!\n");
        return 0;
    }

    if (worn)
    {
        NF("You are already wearing it!\n");
        return 0;
    }
  
    if (member_array("backpack", TP->query_sublocs()) > -1)
    { 
       NF("You already wear another backpack!\n");
       return 0;
    } 

    TP->add_subloc("backpack", THIS);
    write("You wear the large backpack on your back.\n");
    say(QCTNAME(TP) + " wears the large backpack on " + 
             TP->query_possessive() + " back.\n");
    add_prop(OBJ_M_NO_DROP, "Remove the backpack first!\n");
    worn = 1;
    THIS->set_no_show_composite(1); /*do not display in inventory */
    return 1;
    
}



int
remove(string str)
{
    if (str != "backpack")
        return 0;

    if (!present(THIS, TP))
    {
        NF("You don't have it!\n");
        return 0;
    }

    if (!worn)
    {
        NF("You are not wearing it!\n");
        return 0;
    }

    TP->remove_subloc("backpack");
    write("You remove the large backpack.\n");
    say(QCTNAME(TP) + " removes the large backpack.\n");
    remove_prop(OBJ_M_NO_DROP);
    worn = 0;
    THIS->set_no_show_composite(0);  /* display in inventory again */
    return 1;
}


void
leave_env(object dest, object old)
{
    TP->remove_subloc("backpack");
    remove_prop(OBJ_M_NO_DROP);
    ::leave_env(dest, old);
}



public string
show_subloc(string subloc, object on, object for_obj)

{
  string data;

  if(subloc=="backpack")
  {
    if (for_obj != on)
      data = capitalize(on->query_pronoun()) + 
           " is wearing a large backpack on " +
           on->query_possessive() + " back.\n";
    else
      data = "You are wearing a large backpack on your back.\n";
    return data;
  }
}



/* Filter out certain objects when shifting stuff in or out of backpack */
int
a_filter(object ob)
{

  if (ob->query_prop(OBJ_M_NO_SELL)) return 0;
  else if (ob->query_prop(OBJ_M_NO_GIVE)) return 0;
  else if (ob->query_prop(OBJ_M_NO_DROP)) return 0;
  else if (ob->query_prop(CONT_I_IN)) return 0;   /*containers*/
  else if (ob->query_worn()) return 0;
  else if (!(ob->query_prop(OBJ_I_VALUE))) return 0;
  else if (ob->query_wielded()) return 0;
  else if (ob->query_prop(LIVE_I_IS)) return 0;
  else if (ob->query_name() == "backpack") return 0;
  else return 1;
}




/* Enable player to sell the backpack */
int
packsell()

{
   object tp;

   tp = TP;
   
   tp->catch_msg("You may now sell the backpack.\n"); 
   remove_prop(OBJ_M_NO_SELL); 
   return 1;

}




/* Tell player about how to use the backpack */ 
int 
packhelp()

{
   object tp;

   tp = TP;

   tp->catch_msg("How to use the backpack:\n" +
       "'packsell' will make the backpack sellable, " +
       "'packhold' will make it non-sellable.  " +
       "'packstore' puts all unworn and unwielded items " +
       "excluding coins and other containers for example " +
       "into the backpack.  'packget' gets all such items " +
       "from the backpack into your main inventory.  " +  
       "'packhelp' gets this message.\n"); 
    
    return 1;

}




string
query_recover()

{
return MASTER;
}



/* Store selected items in the backpack */
int
packstore()

{
  object tp;
  object *conts, *moved;
  int x, y;


  tp = TP;

  conts = ({ });
  moved = ({ });

  conts = filter(all_inventory(tp), "a_filter", THIS);
  
  for (x = 0; x < sizeof(conts); x++)  {
      conts[x]->move(THIS); 
      if (present(conts[x], THIS))  {
         moved += ({ conts[x] }) ;   /*successful move */
      }
  }   
  
  if (sizeof(moved) == 0)
    tp->catch_msg("You didn't put anything in the backpack.\n");
  else {
    tp->catch_msg("You store " + COMPOSITE_DEAD(moved) + 
                                " in the large backpack.\n");
    tell_room(environment(tp), QCTNAME(tp) + " stores " + 
            COMPOSITE_DEAD(moved) + " in the large backpack.\n", tp);
  }

  return 1;
 
}




/* Retrieve selected items from the backpack */
int
packget()

{
  object tp;
  object *conts, *moved;
  int x;
  
  tp = TP;

  conts = ({ });
  moved = ({ });

  conts = filter(all_inventory(THIS), "a_filter", THIS);
  
  for (x = 0; x < sizeof(conts); x++)  {
      conts[x]->move(tp); 
      if (present(conts[x], tp))  {
         moved += ({ conts[x] }) ;   /*successful move */
      }
  }   

  if (sizeof(moved) == 0)
    tp->catch_msg("You didn't retrieve anything from the backpack.\n");
  else {
    tp->catch_msg("You retrieve " + COMPOSITE_DEAD(moved) + 
                                " from the large backpack.\n");
    tell_room(environment(tp), QCTNAME(tp) + " retrieves " + 
            COMPOSITE_DEAD(moved) + " from the large backpack.\n", tp);
  }

  return 1;

}





int
packhold()

{
  object tp;

  tp = TP;

  tp->catch_msg("The backpack is now non-sellable.\n"); 

  add_prop(OBJ_M_NO_SELL, "If you want to be able to sell this pack, " +
                          "type 'packsell'.  After this you may sell " +
                          "it as normal.\n");
  return 1;
}


void
init()
{
   ::init();
   add_action("packsell", "packsell");
   add_action("packhold", "packhold");
   add_action("packstore", "packstore");
   add_action("packget", "packget");
   add_action("packhelp", "packhelp"); 
   add_action("wear", "wear");
   add_action("remove", "remove");
} 


