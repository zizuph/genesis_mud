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
   
   extraline = "Over the fireplace is a mantle, as expected, covered with "+
                     "many trinkets from far-off places.  The several chairs and "+
                     "benches are arranged in a manner suitable for conversation; "+
                     "it is evident the family spends a great deal of time here.";

   add_item(({"mantle","trinket","trinkets","places","mathoms"}),
   "The mantle is covered with a slight coat of dust as well as "+
   "several odds and ends brought possibly from as far away as "+
   "Michel Delving or Waymeet.  None of them look exceptionally "+
   "appealing however, as they were most likely given as mathoms "+
   "and will probably be given away in the same fashion.\n");

   add_item(({"chairs","benches"}),
   "The benches are on opposite walls and the chairs are "+
   "scattered about in a rough circle around them.\n");

   reset_shire_room();
  
   add_exit(UT_DIR + "ut1a","south");;
}

void
reset_shire_room()
{
   if (!hob)
     {
       hob = clone_object(HOBBITMAKER);
       hob->set_type(CITIZEN);
       hob->set_power(100);
       hob->move(TO);
     }
   
}
