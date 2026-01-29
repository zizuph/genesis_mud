
inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"
#include "/d/Shire/sys/defs.h"

#define EXIT1 ER_BASE_DIR + "village/ut/5c","north",0,1
#define EXIT2 ER_BASE_DIR + "village/ut/5e","southwest",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Undertowers";		/*Name of village*/
   land          = "Westmarch";		/*Name of land   */
   roomtype  = 2;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
   
   extraline = "This drawing-room is rather small, but the "+
   "chairs and sofas are arranged in a semi-circle, so everyone "+
   "can huddle 'round the fireplace in cooler weather and still be "+
   "a bit spread out in warmer.  There is a bedroom to the southwest, "+
   "following the curve of the hill, and north is the dining room.";

   add_item(({"drawing-room","drawing room"}),
   "This is obviously where the hobbits of this burrow gather "+
   "to discuss the day's affairs and host guests.\n");

   add_item(({"fireplace","fire place"}),
   "The fireplace is just a hole in the west wall leading to "+
   "a chimney, not very decorative.\n");

  
   add_exit(EXIT1);
   add_exit(EXIT2);
   make_the_room();
   reset_room();
}

void
reset_room()
{
/*
    object bell;

        if (!present("bell",TO))
    {
        bell = clone_object("/d/Shire/scav_hunt/cow_bell");
        bell->add_prop(OBJ_I_HIDE, 10 + random(10));
        bell->move(TO);
    }
*/
   if (!hob)
   {
     hob = clone_object(ER_BASE_DIR +"npc/whobbit");
   	hob->arm_me();
   	hob->move(TO);
   }

}
