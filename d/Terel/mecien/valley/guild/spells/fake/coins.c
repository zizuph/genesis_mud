inherit "/std/coins";
#include <stdproperties.h>
#include <macros.h>

create_coins(){
   ::create_coins();
   set_coin_type("lead");
   add_prop(OBJ_I_VALUE, 0);
}

long()
{
   if((num_heap() < 2) ||
         (num_heap() >=1000))
   {
      return "It is " + short() + ", it looks rather worthless.\n";
   }
   else
      {
      return "There are " + short() + ", they look rather worthless.\n";
   }
}

