inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/5h","north",0,1

void reset_room();
int do_read(string str);
static object hob;

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 6;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    

   extraline = "This bedroom is smaller than the other two, and is probably "+
   "used mostly as a guest room, though the small desk here indicates "+
   "the room is also used as a book-keeping room.";

   add_item("desk","The desk is closed and locked, with only a few papers "+
   "scattered across the top.\n");
   add_item("papers","Perhaps read the papers?\n");

   add_exit(EXIT1);

   make_the_room();
   reset_room();
}

void
init()
{
    ::init();
    add_action("do_read","read",0);
}

int
do_read(string str)
{
   if(!str)
   notify_fail("Read what?");

   if(str != "papers")
   notify_fail("Read what?");

   write("You read the several papers, which are written in a very "+
   "spidery hand: \n"+
   "     Dear Gorbodoc,\n"+
   "\n\n"+
   "I will most enjoy your visit in a couple of weeks.\n"+
   "I look forward to your coming and will have the\n"+
   "guest bedroom made up for your trip.\n"+
   "\n\n"+
   "     Regards,\n"+
   "      Bingo.\n");
   return 1;

}
void
reset_room()
{
   if(random(3) > 0)
   {
    if(!hob)
    {
     hob = clone_object(ER_BASE_DIR + "npc/mhobbit");
     hob->arm_me();
     hob->move(TO);
    }
   }
}
