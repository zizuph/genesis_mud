// Torn fur which makes peope sneeze when worn. Cloned in l4/n21.
// Made by Boriska, Dec 1994

// Added the code to allow the wearer to sneeze as well as those
//  around him/her -Sirra March 1998.

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

inherit "/std/armour";

void
create_armour()
{
  set_name ("fur");
  set_short ("patched torn fur");
  add_adj (({"patched", "torn"}));
  set_long ("This fur coat covered with patches has cobweb threads\n" +
            "hanging from it! It appears to contain a ton of dust.\n");
   
  set_at(A_BODY);
  set_ac(7);
  
  add_prop (OBJ_I_WEIGHT, 5000);
  add_prop (OBJ_I_VOLUME, 1000);
}

mixed
wear_me()
{
  mixed res;
  object tp = this_player();

  res = (mixed) ::wear_me();

  tp->catch_msg ("A cloud of dust raises from the fur!\n");
  tell_room (environment(tp), "As " + QTNAME (tp) +
	     " tries to wear the fur, a cloud of dust raises from it!\n",tp);
 
  all_inventory(environment(this_object()) )->command("sneeze"); 
  all_inventory(environment(tp))->command ("sneeze");
  
  return res;
}
