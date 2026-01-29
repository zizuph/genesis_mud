// Sybarun torch (/d/Avenir/common/obj/torch.c) 
// creator(s):   Tepisch  01 Aug 94
// last update:  Lilith June 2004 -- added tie functions
//               Lilith Dec 2021: added keepability
// purpose:      light for the utterdark
// note:         
// bug(s):
// to-do:

inherit  "/std/torch";
inherit "/lib/keep";
#include "/sys/macros.h"

void
create_torch()
{
   set_name("torch");
   set_pname("torches");         
   set_adj("excellent");
   set_long("This Sybarun torch is made of seasoned hardwood. "
      +"As long as your arm, one third of its length is tightly "
      +"wrapped in oil-drenched cloth. It looks like it will "
      +"burn brightly for a very long while.\n");
   set_keep(1);
   set_time(1800);
   set_value(144);    
   set_strength(2);
   set_short("excellent torch");
   set_pshort("excellent torches");
}

int
tie_object(object ob, string str)
{
    set_no_show_composite(1);
    return 1;
}

int
untie_object(object ob) 
{
    unset_no_show_composite();
    return 1;
}

string
query_recover()
{
   return MASTER + ":" + query_torch_recover();
}

void
init_recover(string arg)
{
   init_torch_recover(arg);
} 
