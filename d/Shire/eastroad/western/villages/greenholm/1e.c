#include "../local.h"

inherit SMIAL;

static object hob;

void
create_smial()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 5;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    

   extraline = "This large bedroom has several beds in it, probably "+
   "the entire family sleeps in here.  A doorway leads north back to "+
   "the dining room and the rest of the burrow.";

   add_item("burrow","The burrow is the house you stand in.\n");
   add_item(({"doorway"}),"The doorway is guarded by a large "+
   "round door.\n");
   add_item(({ "beds", "bedroom" }),"There's not much to this "+
   "bedroom, merely an assortment of beds with pillows on them.\n");


   add_exit(GREENHOLM_DIR + "1d","north");
   reset_shire_room();
}

void
reset_shire_room()
{
   if(random(100) > 49)
   {
    if(!hob)
    {
     hob = clone_object(HOBBITMAKER);
     hob->set_type(MILITA);
     hob->set_power(160);
     hob->move(TO);
    }
   }
}
