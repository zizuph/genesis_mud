inherit "/std/container";
 
#include "default.h"
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <macros.h>
 
/* prototypes */
int do_open(string str);
int do_opening(string str);
object wax, honey;
 
void
create_container()
{
   set_name("hive");
   add_adj("bee");
   set_short("bee hive");
   set_long("@@st_long");
   add_prop(CONT_I_MAX_WEIGHT, 20000);
   add_prop(CONT_I_MAX_VOLUME, 20000);
   add_prop(OBJ_M_NO_GET, 1);      /* Can't get it. */
   add_prop(CONT_I_RIGID, 1);      /* It's rigid. */
   add_prop(CONT_I_CLOSED, 1);     /* It's closed. */
   add_prop(CONT_I_WEIGHT, 3000);
   add_prop(CONT_I_VOLUME, 5000);
   add_prop(CONT_I_HEIGHT, 50);
   enable_reset();
}
 
string
st_long()
{
   string sm_st = "This hive is painted white, perhaps as a marker for the " +
       "bees? ";
   if(!query_prop(CONT_I_CLOSED))
       sm_st += "The top has been removed from the hive.";
   else
       sm_st += "You may be able to remove the top from it.";
   return sm_st + "\n";
}
 
void
init()
{
   ::init();
   add_action(do_open, "disconnect");
   add_action(do_open, "remove");
   add_action(do_opening, "open");
}
 
int
do_open(string str)
{
   NF(capitalize(query_verb()) + " what from what?\n");
 
   if (!str) return 0;
 
   if(!(parse_command(str, TP, " 'top' 'from' [bee] 'hive'")))
   {
      return 0;
   }
 
   if(!query_prop(CONT_I_CLOSED))
   {
      write("The hive is already open.\n");
      return 1;
   }
 
   write("You " + query_verb() + " the top from the hive.\n");
   say(QCTNAME(TP) + " " + query_verb() + "s the top from " +
             "the hive.\n");
   add_prop(CONT_I_CLOSED, 0);
   return 1;
 
}
 
int
do_opening(string str)
{
    if(str != "hive")
        return 0;
   if(!query_prop(CONT_I_CLOSED))
   {
 	write("The hive is already open.\n");
	return 1;
   }
 
   write("You " + query_verb() + " the hive.\n");
   say(QCTNAME(TP) + " " + query_verb() + "ed the hive.\n");
   add_prop(CONT_I_CLOSED, 0);
   return 1;
}
