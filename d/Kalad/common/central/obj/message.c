/* a message to be found on a pigeon in CENTRAL(plaza/monument) */
/* made by korat */
/* Modified by Lucius - 3.17.2000 */

inherit "/std/scroll";
#include <stdproperties.h>
#include "/d/Kalad/defs.h"

static private int mess;

void
create_scroll()
{
   set_name("message");
   set_long("A small piece of paper with some text written down on it.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 20);

   mess = random(6);
}

void
read_it(string str)
{
   say(QCTNAME(this_player()) + " reads the " +
        QSHORT(this_object()) + ".\n");

   switch(mess)
   {
      case 0:
      write ("You read the message:\n\n"+
      "Come home fast! Your father is severely injured from "+
         "after a stupid act of heroism. He tried to free a slave!\n"+
      "     Your mother.\n");
      break;
      case 1:
      write ("You read the message:\n\n"+
         "Hi mom, dad. Life is hard here in "+
         "the guild. I train and work all I can, but "+
         "I often end up hungry when I go to bed. "+
         "So can you spare me some extra money? "+
         "\n       Your son, Borra.\n");
      break;
      case 2:
      write("You read the message:\n\n"+
         "I would like to order two sacks of flour, "+
         "one cag of bear, and four flasks of oil. I will pay "+
         "at delivery of the goods.\n"+
         "       Greetings from Harkov.\n");
      break;
      case 3:
      write("You read the message:\n\n"+
         "   My love, Hanna.\n"+
         "   How I miss you! Each night I long for your warm "+
         "skin and soft voice. I can hardly bear to be "+
         "so far away from you. But soon I will come home...\n"+
         "   Yours for ever, Pompark.\n");
      break;
      case 4:
      write("You read the message:\n\n"+
         "          Mr. Cosak.\n\n"+
         "     Regarding the unpaid bills. If you do not "+
         "pay within ten days, we will visit your home.\n"+
         "        Bossak, the trading company.\n");
      break;
      case 5:
      write("You read the message:\n\n"+
         "       Miss Henniesen.\n"+
         "   Your tickets for the ship to Grey havens "+
         "is in our office. As you asked for, we have "+
         "given you a cabin with room for a maid.\n"+
         "     Captain Bertwick.\n");
      break;
   }
}
