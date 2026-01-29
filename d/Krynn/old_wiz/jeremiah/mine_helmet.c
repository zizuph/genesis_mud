/*
    A helmet to wear while working in dark rooms.. Mining helmet.
  
*/

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

int    light_intens;
string ret_str;

void
create_armour()
{
   light_intens = 0;

   set_name("helmet");
   set_short("mining helmet");
   set_long("@@long_descr");

   set_ac(4);
   /*         impale, slash, bludgeon  */
   set_am(({   -2,     1,      1 }));
 

   set_at(A_HEAD); /* head protection */

   add_prop(OBJ_I_LIGHT, light_intens); 
}

void
init()
{
   ::init();
   add_action("light_helmet", "light");
   add_action("ext_helmet", "extinguish");
}


string
long_descr()
{
   ret_str = "This is a small mining helmet. It would probably protect " +
             "your head from taking damage from falling objects.\n";
   
   if (light_intens == 1)
   {
      ret_str = ret_str + "A bright small lantern is shining from the " +
                          "front of the helmet.\n";
   }
   else
   {
      ret_str = ret_str + "A small lantern has been placed on the front " +
                          "the helmet.\n";
   }
   return ret_str;
}


int
light_helmet(string what)
{
   if (what == "helmet")
   {
      if (light_intens == 0)
      {    
         light_intens = 1;
         write("You light the lantern on the front of your helmet.\n");
         say(QCTNAME(TP) + " lights the lantern on the front of " +
             POSSESSIVE(TP) + " mining helmet.\n");
         add_prop(OBJ_I_LIGHT, light_intens);
      }   
      else
      {
         write("light it again ? .. not possible!.\n");
      }
      return 1;
   }
   else
   {
      NF("light what?\n");
   }
}


int
ext_helmet(string what)
{
   if (what == "helmet")
   {
      if (light_intens == 1)
      {
         light_intens = 0;
         write("You extinguish the lantern on your helmet.\n");
         say(QCTNAME(TP) + " extinguishes the lantern on the front of " +
             POSSESSIVE(TP) + " mining helmet.\n");
         add_prop(OBJ_I_LIGHT, light_intens);
      }
      else
      {
         write("It look as if its already extinguished.\n");
      }
      return 1;
   }
   else
   {
      NF("extinguish what?\n");
      return 0;
   }
}
