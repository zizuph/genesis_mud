inherit  "/std/torch";
inherit "/lib/keep";
#include <macros.h>


create_torch()
{
   set_name("torch");
   set_pname("torches");         
   set_adj("large");
   set_long("This is a large torch capable of burning for a good "+
                 "deal of time.\n");
    set_keep(1);
   set_time(1800);
   set_value(144);    
   set_strength(2);
   set_short("large torch");
   set_pshort("large torches");
}

query_recover()
{
   return MASTER + ":" + query_torch_recover();
}

init_recover(string arg)
{
   init_torch_recover(arg);
} 
