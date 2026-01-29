// Tent to hire messangers 
inherit "/std/room";
inherit "/lib/trade";
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "/d/Emerald/defs.h"

#define WAIF_VALUE 144
#define NUM sizeof(MONEY_TYPES) 
object messanger;

create_room()
{
	set_short("A place to hire messangers.");
	set_long("A large tent with a pen in the back room " +
	"the purpose of whcih seems to contain the aniimals the " +
	"natives have trained for the purposes of sending and receiving " +
	"desire.  A sign on the wall provides instructions, and a " +
	"young native woman waits to serve you.\n");
 
	add_item(({"native", "native woman", "woman"}), "A very beautiful " +
	"member of the tribe who is serving her tribe through her " +
	"knowledge of animal training.\n");
	add_item("sign", "The sign reads: Messangers for hire. Only " +
	"20 copper coins.\n");
add_prop(ROOM_I_INSIDE, 1);

   config_default_trade();
   set_money_give_out(   ({ 10000,    32,   2,    1 }));
   set_money_give_reduce(({     0,     4,   2,    1 })); 
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);

}      
init() {
   ::init();
   add_action("do_hire","hire",0);
}

do_hire(str) {
	object messenger, tp;
   string item_name, pay_type, get_type, str1, coin_pay_text, coin_get_text;
   int *money_arr;

   tp = this_player();

   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

if (!str)
{
	write("Hire what, a messanger?\n");
   return 1;
}
	if (!(item_name == "messanger"))
   {
      write("Hire what?\n");
      return 1;
   }

   if (sizeof(money_arr = pay(WAIF_VALUE, tp, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
	tell_room(this_object(), "The native woman says: I fear you can not affor a messanger " +
	TP->query_nonmet_name() +".\n");
         return 1;
      }
      if (money_arr[0] == 2)
      {
	tell_room(this_object(), "The native woman says: I fear you can not afford a messanger, "
	+ TP->query_nonmet_name() + ".\n");
         return 1;
      }
      else
      {
	tell_room(this_object(), "The native woman says:  I fear you can not afford a messanger, "
	+ TP->query_nonmet_name() + ".\n");
         return 1;
      }
   }

	messanger = clone_object(VOBJ + "messan.c");
   {
      write("You cannot carry that much!\n");
	messanger->remove_object();
      return 1;
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You pay " +coin_pay_text+ " and hire yourself a messenger.\n");
   if (coin_get_text)
	write("You get " + coin_get_text + " back from the native woman.\n");
   say(QCTNAME(tp) + " hires " + tp->query_objective()
     + "self a carrier messenger.\n");
   return 1;
}
