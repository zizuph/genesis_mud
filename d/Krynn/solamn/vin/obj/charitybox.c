/* donation box
 * Aridor, 08/1996
 */

inherit "/std/container";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#define LIVE_I_TAKEN_FROM_CHARITY "_live_i_taken_from_charity"
#define NUM_ALLOWED               3

void
create_container()
{
  set_name("box");
  add_name("bin");
  set_adj("charity");
  
  set_short("charity box");   
  set_long("This is a wooden box with iron trimmings. Here you may " +
	   "deposit items for general use for everyone instead of " +
	   "selling them in the shop. Those who take items from the " +
	   "box should not take a filled box for granted. The box is " +
	   "mostly filled by people on their own free will, therefore " +
	   "items from the box are not intended just to be sold. Note " +
	   "that the number of items you may take from the box is limited.\n");
  
  add_item("trimmings", "Made of iron.\n"); 
  
  add_prop(CONT_I_MAX_WEIGHT,  2000000); /* 2000 kilos */
  add_prop(CONT_I_MAX_VOLUME,  2000000); /* 2000 liters */
  add_prop(CONT_I_WEIGHT, 20000);
  add_prop(CONT_I_VOLUME, 160000);
  add_prop(CONT_I_RIGID, 1);
  add_prop(CONT_I_NO_REM,"@@check_allowed@@");
  add_prop(OBJ_M_NO_GET, "The box is much too heavy to be lifted.\n");
}                               

void
leave_inv(object ob, object to)
{
  int prp = TP->query_prop(LIVE_I_TAKEN_FROM_CHARITY);
  to->add_prop(LIVE_I_TAKEN_FROM_CHARITY, prp+1);
  ::leave_inv(ob,to);
}

mixed
check_allowed()
{
  if (TP->query_average_stat() > 48 + random(3))
    return "You are already experienced enough to find your own equipment. " +
      "Sorry.\n";
  if (TP->query_prop(LIVE_I_TAKEN_FROM_CHARITY) >= NUM_ALLOWED)
    return "You have already taken your share of items from the box for " +
		    "today. Sorry.\n";
  return 0;
}

