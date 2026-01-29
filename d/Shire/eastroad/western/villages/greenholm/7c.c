#include "../local.h"

inherit SMIAL;

static object hob;

void
create_smial()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 4;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "Something seems to be cooking on the stove, "+
   "and a pantry is east.";

   add_item("something","The something is inside a pot, but it "+
   "sure smells good!\n");
   add_item("pot","It is cooking something on the stove.\n");
   add_item("pantry","The pantry is where the hobbits who "+
   "live here keep their food.\n");
  
   add_exit(GREENHOLM_DIR + "7","north");
   add_exit(GREENHOLM_DIR + "7d","south");
   add_exit(GREENHOLM_DIR + "7f","east");
   reset_shire_room();
}

void
reset_shire_room()
{
   if(random(10) > 1)
   {
     if(!hob)
     {
       hob = clone_object(HOBBITMAKER);
       hob->set_type(ELDER);
       hob->set_power(135);
       hob->move(TO);
     }
   }
}
