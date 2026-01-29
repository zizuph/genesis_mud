inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/5h","south",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 6;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    

   extraline = "This medium-sized bedroom is larger than the one across "+
   "the hall, though it has no window, and is rather dim, even with the "+
   "candles placed on the dresser. ";

   add_item("candles","The several candles are lit and sitting on the "+
   "dresser.  They look well-attached to some sort of stand.\n");
   add_item(({"dresser","stand"}),
   "The dresser apparently holds clothes, and placed on top of it is "+
   "a candle-stand with candles, which is firmly screwed into the "+
   "dresser-top.\n");

   add_exit(EXIT1);

   make_the_room();
   reset_room();
}

void
reset_room()
{
   if(random(3) > 0)
   {
    if(!hob)
    {
     hob = clone_object(ER_BASE_DIR + "npc/whobbit");
     hob->arm_me();
     hob->move(TO);
    }
   }
}
