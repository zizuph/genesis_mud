/* a note that can be found in the city council. */
/* made by korat */

inherit "/std/scroll";
#include <stdproperties.h>
#include "/d/Kalad/defs.h"
#include <filter_funs.h>

int times_burned;
int burn_id;
int extinguished;

void
create_scroll()
{
   set_name("sheet");
   set_adj("burning");
   add_adj("piece of a");
   set_short("burning piece of a sheet");
   set_long("Its a piece of paper that is slowly "+
      "being consumed by some small flames.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 20);
   burn_id=set_alarm(0.0,2.0,"burn_me");
   extinguished = 0;
}

void
init()
{
   ::init();
   add_action("read","read");
   add_action("extinguish","extinguish");
}

extinguish(string str)
{
   notify_fail("Extinguish what?\n");
   if (!str) return 0;
   if (str!="flames") return 0;
   if(!extinguished)
      {
      write("You extinguish the small flames that slowly burns the sheet away.\n");
      say(QCTNAME(TP)+" extinguishes the small flames that burns a sheet.\n");
      remove_alarm(burn_id);
      TO->set_long("It is a small piece of paper that has several burn-marks "+
         "on the edges. You can still read some of the text on it though.\n");
      TO->set_short("burned piece of a sheet");
      extinguished = 1;
      return 1;
   }
   write("But the sheet is not on fire!\n");
   return 1;
}

burn_me()
{
   object room;
   times_burned = times_burned+1;
   if(living(E(TO))) room = E(E(TO));
   else room = E(TO);
   if (times_burned>15)
      {
      tell_room(room,"The flames consumes the sheet, leaving nothing behind.\n");
      remove_alarm(burn_id);
      remove_object();
   }
   else
      {
      tell_room(room,"The flames slowly burns the sheet.\n");
   }
}


int
read(string str)
{
   notify_fail("Read what?\n");
   if (!str) 
      return 0;
   if (str!="sheet")
      return 0;
   if (!extinguished)
   {
      write("But you can't read it now! It is burning!\n");
      return 1;
   }
   say(QCTNAME(TP)+" reads a burned piece of paper.\n");
   write("You read the text.\n\n"+
      "... ust be de ... r he ... an damag ... even m ... "+
      "So, w ... troy him ... anages to ki ... "+
      "So I comma ... o deal wi ... Bocca..\n"+
      "                The Hig ... ord, Urian.\n");
   
   return 1;
}
