/* A torch for the Union tomb area. It last quite a long time. Cirion April 18, 1997 */
inherit "/std/torch";
#include "../defs.h"


void create_torch()
{
  set_name("torch");
  set_short("ivory torch");
  add_adj("ivory");
  set_long("It is a smooth, beautiful torch made from ivory, wrought "
     + "with veins of silver and platinum.@@lit_desc@@\n");

  set_time(3600); // 1 hour rl
  set_strength(2);
  set_value(800);
  add_prop(OBJ_I_VOLUME, 680);
  add_prop(OBJ_I_WEIGHT, 700);
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
     return " The resin at the top of the torch has burned out "
         + "completely.";
  else if(!query_prop(OBJ_I_HAS_FIRE))
     return " The top of the torch is coated with a sticky, "
         + "amber-coloured resin.";
  else
     return " A large, rich orange flame rises from it, "
       +"sending thick plumes of dark smoke into the air.";
}

/*
 * Function name: short, pshort, long
 * Description:   We change the short, plural short and long description of
 *		  the torch if it's lit, default settings.
 * Returns:	  The description.
 */
public varargs string
short(object for_obj)
{
  string desc;

  if(query_verb() == "light" || query_verb() == "extinguish")
     desc = "";
  else if(query_time(1) == query_max_time())
     desc = "unlit ";  // new torch, unlit
  else if(!query_lit(0) && query_time(1))
     desc = "unlit ";      // unlit torch, still good
  else if (query_time(1) > 1100 && query_lit(0))
     desc = "burning "; // lit torch, lots of time left
  else if (query_time(1) > 600 && query_lit(0))
     desc = "burning "; // lit torch, some time left
  else if (query_time(1) > 100 && query_lit(0))
     desc = "burning "; // lit torch, a little time left
  else if (query_time(1) && query_lit(0))
     desc = "charred "; // lit torch, very little time left
  else
     desc = "burnt-out "; // time's up!

  // double ::'s to get rid of the (lit) message
  return desc + ::short(for_obj);
}

