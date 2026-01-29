inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/1d","north",0,1

void reset_room();
static object hob;

void
create_room()
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

   add_exit(EXIT1);

   make_the_room();
   reset_room();
}

void
reset_room()
{
   if(random(100) > 49)
   {
    if(!hob)
    {
     hob = clone_object(ER_BASE_DIR + "npc/bighobbit");
     hob->arm_me();
     hob->move(TO);
    }
   }
}
