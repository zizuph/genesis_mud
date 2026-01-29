/* High-grade charcoal */
inherit "/std/torch";
#include <stdproperties.h>
#include <macros.h>

void 
create_torch()
{
  set_name("charcoal");
  add_name(({"brick", "_crucible_component"}));
  set_pname("bricks");
  set_short("charcoal brick");
  set_pshort("charcoal bricks");
  add_adj(({"charcoal", "brick"}));
  set_long("It is a brick of high-grade charcoal.@@lit_desc@@\n");

  set_time(1800); // 1/2 hour rl
  set_strength(0);
  set_value(10 + random(25));
  add_prop(OBJ_I_VOLUME, 250);
  add_prop(OBJ_I_WEIGHT, 250);
  add_prop(OBJ_M_NO_SELL, "@@dont_sell@@");
}

mixed 
dont_sell()
{
  if(query_prop(OBJ_I_HAS_FIRE))
   return "Extinguish it first.\n";
  else
   return 0;
}

string 
lit_desc()
{
  if(!query_time())
     return " It doesn't look like there is much left to burn.";
  else if(!query_prop(OBJ_I_HAS_FIRE))
     return " Glossy black, it looks like it would burn "+
            "for a long while.";
  else
     return " It is very warm, with a faint, flickering blue "+
            "flame.";
}
