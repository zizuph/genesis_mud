#include "../local.h"

inherit SMIAL;

static object hob;

void
create_smial()
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

   add_exit(UT_DIR + "5c","north");
   add_exit(UT_DIR + "5e","southwest");

   reset_shire_room();
}

void
reset_shire_room()
{
   if (!hob)
   {
        hob = clone_object(HOBBITMAKER);
   	hob->set_type(CITIZEN);
	hob->set_power(120);
   	hob->move(TO);
   }

}
