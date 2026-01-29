// Sybarun torch (/d/Avenir/common/bazaar/obj/ptorch.c) 
// creator(s):   Tepisch  01 Aug 94
// last update:  
// purpose:      light
// note:         for wandering merchant(s) to sell.
// bug(s):
// to-do:



inherit  "/std/torch";
#include "../bazaar.h"

create_torch()
{
   set_name("torch");
   set_pname("torches");         
   set_adj("excellent");
   set_long("This Sybarun torch is made of seasoned hardwood. "
      +"As long as your arm, one third of its length is tightly "
      +"wrapped in oil-drenched cloth. It looks like it will "
      +"burn brightly for a very long while.\n");
   set_time(1800);
   set_value(144);    
   set_strength(2);
   set_short("excellent torch");
   set_pshort("excellent torches");
}

query_recover()
{
   return MASTER + ":" + query_torch_recover();
}

init_recover(string arg)
{
   init_torch_recover(arg);
} 
