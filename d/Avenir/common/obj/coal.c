/* A lump of coal, styled after the torch for the Union */
inherit "/std/torch";
#include <stdproperties.h>
#include <macros.h>

void 
create_torch()
{
  set_name("_avenir_coal");
  add_name(({"coal", "lump"}));
  set_pname("lumps");
  set_short("lump of coal");
  set_pshort("lumps of coal");
  add_adj(({"lump", "coal"}));
  set_long("It is a lump of coal, a black stone that can be burned, "+
      "usually as a source of heat but also light.@@lit_desc@@\n");

  set_time(1800); // 1/2 hour rl
  set_strength(1);
  set_value(10 + random(25));
  add_prop(OBJ_I_VOLUME, 250);
  add_prop(OBJ_I_WEIGHT, 250);
  add_prop(OBJ_M_NO_SELL, "@@dont_sell@@");
}

mixed dont_sell()
{
  if(query_prop(OBJ_I_HAS_FIRE))
   return "Extinguish it first.\n";
  else
   return 0;
}

string lit_desc()
{
  if(!query_time())
     return " It doesn't look like there is much left to burn.";
  else if(!query_prop(OBJ_I_HAS_FIRE))
     return " It is glossy and rich with oil.";
  else
     return " It is very warm, with a faint, flickering orange "+
            "flame.";
}


void torch_tell()
{
  string  str;
  object  where;

  if(!query_lit(0))
    return;

  switch(random(3))
  {
    case 0:
     str = "issues forth a thin trail of black smoke.";
     break;
    case 1:
     str = "flickers with faint orange light.";
     break;
    case 2:
     str = "glows with warmth.";
     break;
    default:
     str = "glows with warmth.";
   }

   where = environment(this_object());
   if(!living(where))
    tell_room(where, "The " + QSHORT(this_object()) 
     + " " + str + "\n");
   else
   {
    where->catch_msg("Your " + QSHORT(this_object()) + " " + str + "\n");
    tell_room(environment(where), QCTNAME(where) + "'s "
      + QSHORT(this_object()) + " " + str + "\n", ({ where }));
   }

  set_alarm(itof(random(200) + 20), 0.0, torch_tell);
}

public 
int light_me_after_delay()
{
  ::light_me_after_delay();
  set_alarm(itof(random(200) + 20), 0.0, torch_tell);
  return 1;
}

